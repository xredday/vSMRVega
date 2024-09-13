#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "GdiPlus.h"

using namespace std;
using namespace rapidjson;

class VegaIcons {
public:
    VegaIcons::VegaIcons(string iconsPath);

    bool hasIcon(string icon);
    const Value &getIcon(string icon);
    Gdiplus::Point *getIconPoints(string icon);
    int getIconPointSize(string icon);

    Document document;

protected:
    string icons_path;

    void loadIcons();
};

