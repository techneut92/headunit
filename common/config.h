#pragma once

#include "json/json.hpp"
using json = nlohmann::json;

class config {
public:

    static void readConfig();
    static void updateConfigString(std::string parameter, std::string value);
    static void updateConfigBool(std::string parameter, bool value);

    static std::string configFile;
    static bool launchOnDevice;
    static bool carGPS;
    static HU_TRANSPORT_TYPE transport_type;
    static std::string phoneIpAddress;
    static bool reverseGPS;

    // video
    static bool fullscreen;
    static int resolution; // 1: 800x480, 2: 1280x720, 3: 1920x1080
    static int resolutionX; // set by resolution
    static int resolutionY; // set by resolution
    static int dpi;

    // car
    static std::string car_unit_name;
    static std::string car_model;
    static std::string car_year;
    static std::string car_serial;
    static std::string car_headunit_make;
    static std::string car_headunit_model;
    static std::string car_sw_build;
    static std::string car_sw_version;
    static bool car_can_play_native_media_during_vr;
    static bool car_hide_clock;

private:
    static json readConfigFile();
    static void writeConfigFile(json config_json);
    static void parseJson(json config_json);
};

