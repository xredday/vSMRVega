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

	if (Counter % 60 == 0) {
		thread urc{&CSMRPlugin::updateRunwayConfigurations, this};
		urc.detach();
	}
};

CRadarScreen * CSMRPlugin::OnRadarScreenCreated(const char * sDisplayName, bool NeedRadarContent, bool GeoReferenced, bool CanBeSaved, bool CanBeCreated)
{
	Logger::info(string(__FUNCSIG__));
	if (!strcmp(sDisplayName, MY_PLUGIN_VIEW_AVISO)) {
		CSMRRadar* rd = new CSMRRadar();
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
	} catch (runtime_error &e) {
		Logger::info(string{"Failed to update runway configurations: "} + e.what());
	} catch (domain_error &e) {
		Logger::info(string{"Failed to update runway configurations: "} + e.what());
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