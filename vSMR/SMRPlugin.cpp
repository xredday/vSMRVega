#include "stdafx.h"
#include "SMRPlugin.hpp"
#include "curl/curl.h"
#include "NetConf.h"

bool Logger::ENABLED;
string Logger::DLL_PATH;

bool BLINK = false;

clock_t timer;

string myfrequency;

using namespace SMRPluginSharedData;
char recv_buf[1024];

vector<CSMRRadar*> RadarScreensOpened;

CSMRPlugin::CSMRPlugin(void) :CPlugIn(EuroScopePlugIn::COMPATIBILITY_CODE, MY_PLUGIN_NAME, MY_PLUGIN_VERSION, MY_PLUGIN_DEVELOPER, MY_PLUGIN_COPYRIGHT) {
	Logger::DLL_PATH = "";
	Logger::ENABLED = false;

    curl_global_init(CURL_GLOBAL_ALL);

	//
	// Adding the SMR Display type
	//
	RegisterDisplayType(MY_PLUGIN_VIEW_AVISO, false, true, true, true);

	char DllPathFile[_MAX_PATH];
	string DllPath;

	GetModuleFileNameA(HINSTANCE(&__ImageBase), DllPathFile, sizeof(DllPathFile));
	DllPath = DllPathFile;
	DllPath.resize(DllPath.size() - strlen("vSMR.dll"));
	Logger::DLL_PATH = DllPath;

	thread urc{&CSMRPlugin::updateRunwayConfigurations, this};
	urc.detach();
    OnAirportRunwayActivityChanged();
}

CSMRPlugin::~CSMRPlugin() {
	// NOTE: 'SaveDataToSettings()' doesn't actually write data anywhere in a file, contrary to what the name freaking suggests.
	try {
		io_service.stop();
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
    curl_global_cleanup();
}

bool CSMRPlugin::OnCompileCommand(const char * sCommandLine) {
	return false;
}

void CSMRPlugin::OnGetTagItem(CFlightPlan FlightPlan, CRadarTarget RadarTarget, int ItemCode, int TagData, char sItemString[16], int * pColorCode, COLORREF * pRGB, double * pFontSize) {
	Logger::info(string(__FUNCSIG__));
}

void CSMRPlugin::OnFunctionCall(int FunctionId, const char * sItemString, POINT Pt, RECT Area) {
	Logger::info(string(__FUNCSIG__));
}

void CSMRPlugin::OnFlightPlanDisconnect(CFlightPlan FlightPlan)
{
	Logger::info(string(__FUNCSIG__));
	CRadarTarget rt = RadarTargetSelect(FlightPlan.GetCallsign());

	if (std::find(ReleasedTracks.begin(), ReleasedTracks.end(), rt.GetSystemID()) != ReleasedTracks.end())
		ReleasedTracks.erase(std::find(ReleasedTracks.begin(), ReleasedTracks.end(), rt.GetSystemID()));

	if (std::find(ManuallyCorrelated.begin(), ManuallyCorrelated.end(), rt.GetSystemID()) != ManuallyCorrelated.end())
		ManuallyCorrelated.erase(std::find(ManuallyCorrelated.begin(), ManuallyCorrelated.end(), rt.GetSystemID()));
}

void CSMRPlugin::OnTimer(int Counter) {
	Logger::info(string(__FUNCSIG__));
	BLINK = !BLINK;

	if (Counter % 30 == 0) {
		thread urc{&CSMRPlugin::updateRunwayConfigurations, this};
		urc.detach();
	}
};

void CSMRPlugin::OnAirportRunwayActivityChanged() {
	Logger::info(string(__FUNCSIG__));
	for (CSectorElement e = SectorFileElementSelectFirst(SECTOR_ELEMENT_RUNWAY); e.IsValid(); e = SectorFileElementSelectNext(e, SECTOR_ELEMENT_RUNWAY)) {
		string ap = string{e.GetAirportName()}.substr(0, 4);
		string rwy1 = e.GetRunwayName(0);
		if (e.IsElementActive(true, 0) || e.IsElementActive(false, 0)) activeRunways[ap][rwy1] = make_pair(e.IsElementActive(true, 0), e.IsElementActive(false, 0));
		else activeRunways[ap].erase(rwy1);
		string rwy2 = e.GetRunwayName(1);
		if (e.IsElementActive(true, 1) || e.IsElementActive(false, 1)) activeRunways[ap][rwy2] = make_pair(e.IsElementActive(true, 1), e.IsElementActive(false, 1));
		else activeRunways[ap].erase(rwy2);
		if (activeRunways[ap].empty()) activeRunways.erase(ap);
	}
}

bool CSMRPlugin::isRunwayMatch(string airport) {
	lock_guard<mutex> lock(runwayConfigMutex);
	if (RunwayConfigurations.find(airport) == RunwayConfigurations.end()) return true;
    map<string, int> serverConfig = RunwayConfigurations[airport];
    map<string, pair<bool, bool>> airportActiveRunways = activeRunways[airport];
	for (auto const& [rwy, config] : serverConfig) {
        if (config != 0 && airportActiveRunways.count(rwy) == 0) return false;
        if (config == 0 && airportActiveRunways.count(rwy) == 0) continue;
        pair<bool, bool> active = airportActiveRunways[rwy];
		if (config == 0 && (active.first || active.second)) return false;
        if (config == 1 && (!active.first || active.second)) return false;
        if (config == 2 && (active.first || !active.second)) return false;
		if (config == 3 && (!active.first || !active.second)) return false;
    }
	for (auto const& [rwy, active] : airportActiveRunways) {
		if (serverConfig.count(rwy) == 0 && (active.first || active.second)) return false;
    }
	return true;
}

pair<string, string> CSMRPlugin::getNeededRunwayConfiguration(string airport) {
	lock_guard<mutex> lock(runwayConfigMutex);
	if (RunwayConfigurations.find(airport) == RunwayConfigurations.end()) return make_pair("?", "?");
	map<string, int> serverConfig = RunwayConfigurations[airport];
	string dep, arr;
	for (auto const& [rwy, config] : serverConfig) {
		if (config == 1 || config == 3) {
            if (dep.length() > 0) dep += ", ";
            dep += rwy;
		}
		if (config == 2 || config == 3) {
            if (arr.length() > 0) arr += ", ";
            arr += rwy;
		}
	}
	return make_pair(dep, arr);
}

CRadarScreen * CSMRPlugin::OnRadarScreenCreated(const char * sDisplayName, bool NeedRadarContent, bool GeoReferenced, bool CanBeSaved, bool CanBeCreated)
{
	Logger::info(string(__FUNCSIG__));
	if (!strcmp(sDisplayName, MY_PLUGIN_VIEW_AVISO)) {
		CSMRRadar* rd = new CSMRRadar(this);
		RadarScreensOpened.push_back(rd);
		return rd;
	}

	return NULL;
}

static size_t WriteCurlCallback(void *contents, size_t size, size_t nmemb, void *userp) {
	((string *) userp)->append((char *) contents, size * nmemb);
	return size * nmemb;
}

string CSMRPlugin::makeCURLGetRequest(string endpoint) {
	CURL *curl = curl_easy_init();
	string readBuffer;
	if (curl == NULL) throw runtime_error("Failed to load CURL!");
	curl_easy_setopt(curl, CURLOPT_URL, string{RWYAPI_SERVER_URL + endpoint}.c_str());
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCurlCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

	CURLcode res = curl_easy_perform(curl);
	long httpCode = 0;
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
	curl_easy_cleanup(curl);
	if (res != CURLE_OK)
		throw runtime_error(curl_easy_strerror(res));
	else if (httpCode != 200)
		throw domain_error(string{"HTTP error code: " + to_string(httpCode)});
	else
		return readBuffer;
}

vector<string> CSMRPlugin::splitString(string s, string delim) {
	size_t last = 0;
	size_t next = 0;
	vector<string> result;

	while ((next = s.find(delim, last)) != string::npos) {
		result.push_back(s.substr(last, next - last));
		last = next + delim.length();
	}
	result.push_back(s.substr(last));
	return result;
}

void CSMRPlugin::updateRunwayConfigurations() {
	try {
		string response = makeCURLGetRequest("get.php");
        vector<string> lines = splitString(response, "\n");
        map<string, map<string, int>> newRunwayConfigurations;
		for (string line : lines) {
			vector<string> parts = splitString(line, ",");
			if (parts.size() != 3) continue;
			newRunwayConfigurations[parts[0]][parts[1]] = stoi(parts[2]);
		}
		lock_guard<mutex> lock(runwayConfigMutex);
		RunwayConfigurations = newRunwayConfigurations;
        wasLastRunwayConfigUpdateSuccessful = true;
	} catch (runtime_error &e) {
		Logger::info(string{"Failed to update runway configurations: "} + e.what());
        wasLastRunwayConfigUpdateSuccessful = false;
	} catch (domain_error &e) {
		Logger::info(string{"Failed to update runway configurations: "} + e.what());
        wasLastRunwayConfigUpdateSuccessful = false;
	}
}

//---EuroScopePlugInExit-----------------------------------------------

void __declspec (dllexport) EuroScopePlugInExit(void)
{
	for each (auto var in RadarScreensOpened)
	{
		var->EuroScopePlugInExitCustom();
	}
}