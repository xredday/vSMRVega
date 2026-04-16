#pragma once
#include "EuroScopePlugIn.h"
#include "HttpHelper.hpp"
#include <string>
#include <algorithm>
#include "Constant.hpp"
#include "Mmsystem.h"
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include "SMRRadar.hpp"
#include "Logger.h"

#define MY_PLUGIN_NAME      "vSMR Vega"
#define MY_PLUGIN_VERSION   "2.3.3"
#define MY_PLUGIN_DEVELOPER "Ivan N. Buev, Pierre Ferran, Even Rognlien, Lionel Bischof, Daniel Lange, Juha Holopainen, Keanu Czirjak"
#define MY_PLUGIN_COPYRIGHT "GPL v3"
#define MY_PLUGIN_VIEW_AVISO  "SMR radar display"

using namespace std;
using namespace EuroScopePlugIn;

class CSMRPlugin : public EuroScopePlugIn::CPlugIn {
public:
	CSMRPlugin();
	virtual ~CSMRPlugin();

	//---OnCompileCommand------------------------------------------

	virtual bool OnCompileCommand(const char * sCommandLine);

	//---OnFunctionCall------------------------------------------

	virtual void OnFunctionCall(int FunctionId, const char * sItemString, POINT Pt, RECT Area);

	//---OnGetTagItem------------------------------------------

	virtual void OnGetTagItem(CFlightPlan FlightPlan, CRadarTarget RadarTarget, int ItemCode, int TagData, char sItemString[16], int * pColorCode, COLORREF * pRGB, double * pFontSize);

	//---OnFlightPlanDisconnect------------------------------------------

	virtual void OnFlightPlanDisconnect(CFlightPlan FlightPlan);

	//---OnTimer------------------------------------------

	virtual void OnTimer(int Counter);

	virtual void OnAirportRunwayActivityChanged();

	//---OnRadarScreenCreated------------------------------------------

	virtual CRadarScreen * OnRadarScreenCreated(const char * sDisplayName, bool NeedRadarContent, bool GeoReferenced, bool CanBeSaved, bool CanBeCreated);

    bool getWasLastRunwayConfigUpdateSuccessful() { return wasLastRunwayConfigUpdateSuccessful; }
    pair<string, string> getNeededRunwayConfiguration(string airport);
	bool isRunwayMatch(string airport);

private:
    map<string, map<string, pair<bool, bool>>> activeRunways;
    map<string, map<string, int>> RunwayConfigurations;
    mutex runwayConfigMutex;
	atomic<bool> wasLastRunwayConfigUpdateSuccessful = true;

	string makeCURLGetRequest(string endpoint);
	vector<string> splitString(string s, string delim);
    void updateRunwayConfigurations();
};

