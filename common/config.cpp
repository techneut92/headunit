#include <fstream>
#include "hu_aap.h"
#include "config.h"

//default settings
std::string config::configFile = "/tmp/root/headunit.json";
bool config::launchOnDevice = true;
bool config::carGPS = true;
HU_TRANSPORT_TYPE config::transport_type = HU_TRANSPORT_TYPE::USB;
std::string config::phoneIpAddress = "192.168.43.1";
bool config::reverseGPS = false;
bool config::fullscreen = false;
int config::resolution = 1;
int config::resolutionX = 800;
int config::resolutionY = 480;
int config::dpi = 140;

std::string config::car_unit_name = "mazda";
std::string config::car_model = "Mazda";
std::string config::car_year = "2016";
std::string config::car_serial = "0001";
std::string config::car_headunit_make = "Mazda";
std::string config::car_headunit_model = "Connect";
std::string config::car_sw_build = "SWB1";
std::string config::car_sw_version = "SWV1";
bool config::car_can_play_native_media_during_vr = false;
bool config::car_hide_clock = false;

void config::parseJson(json config_json)
{
    if (config_json["launchOnDevice"].is_boolean())
    {
        config::launchOnDevice = config_json["launchOnDevice"];
    }
    if (config_json["carGPS"].is_boolean())
    {
        config::carGPS = config_json["carGPS"];
    }
    if (config_json["wifiTransport"].is_boolean())
    {
        config::transport_type = config_json["wifiTransport"] ? HU_TRANSPORT_TYPE::WIFI : HU_TRANSPORT_TYPE::USB;
    }
    if (config_json["phoneIpAddress"].is_string())
    {
        config::phoneIpAddress = config_json["phoneIpAddress"];
    }
    if (config_json["reverseGPS"].is_boolean())
    {
        config::reverseGPS = config_json["reverseGPS"];
    }
    if (config_json["video"]["resolution"].is_number_integer()){
        config::resolution = config_json["video"]["resolution"];
        if (config_json["resolution"] == 2) {
            config::resolutionX = 1280;
            config::resolutionY = 720;
        }
        else if (config_json["video"]["resolution"] == 3) {
            config::resolutionX = 1920;
            config::resolutionY = 1080;
        }
        else {
            config::resolutionX = 800;
            config::resolutionY = 480;
            config::resolution = 1;
        }
    }
    if (config_json["video"]["fullscreen"].is_boolean())
    {
        config::fullscreen = config_json["video"]["fullscreen"];
    }
    if (config_json["video"]["dpi"].is_number_integer())
    {
        config::dpi = config_json["video"]["dpi"];
    }

    // car
    if (config_json["car"]["unit_name"].is_string()){
        config::car_unit_name = config_json["car"]["unit_name"];
    }
    if (config_json["car"]["car_model"].is_string()){
        config::car_model = config_json["car"]["car_model"];
    }
    if (config_json["car"]["car_year"].is_string()){
        config::car_year = config_json["car"]["car_year"];
    }
    if (config_json["car"]["car_serial"].is_string()){
        config::car_serial = config_json["car"]["car_serial"];
    }
    if (config_json["car"]["headunit_make"].is_string()){
        config::car_headunit_make = config_json["car"]["headunit_make"];
    }
    if (config_json["car"]["headunit_model"].is_string()){
        config::car_headunit_model = config_json["car"]["headunit_model"];
    }
    if (config_json["car"]["sw_build"].is_string()){
        config::car_sw_build = config_json["car"]["sw_build"];
    }
    if (config_json["car"]["sw_version"].is_string()){
        config::car_sw_version = config_json["car"]["sw_version"];
    }
    if (config_json["car"]["can_play_native_media_during_vr"].is_boolean()){
        config::car_can_play_native_media_during_vr = config_json["car"]["can_play_native_media_during_vr"];
    }
    if (config_json["car"]["hide_clock"].is_boolean()){
        config::car_hide_clock = config_json["car"]["hide_clock"];
    }
    printf("json config parsed\n");
}

json config::readConfigFile()
{
    std::ifstream ifs(config::configFile);
    json config_json;
    //config file exists, read it
    if (ifs.good())
    {
        try
        {
            ifs >> config_json;
        }catch (...)
        {
            printf("couldn't parse config file. possible corruption\n");
            config_json = nullptr;
            ifs.close();
        }
        ifs.close();
    }
    else
    {
        printf("couldn't read config file. check permissions\n");
    }
    return config_json;
}

void config::readConfig()
{
    json config_json = readConfigFile();
    if (config_json == nullptr) return;

    config::parseJson(config_json);
}

void config::writeConfigFile(json config_json)
{
    std::ofstream out_file(config::configFile);
    if (out_file.good())
    {
        out_file << std::setw(4) << config_json << std::endl;
        out_file.close();
        printf("config file written\n");
    }
    else
    {
        printf("couldn't write config file. check permissions\n");
    }
}

void config::updateConfigString(std::string parameter, std::string value)
{
    printf("updating parameter [%s] = [%s]\n", parameter.c_str(), value.c_str());
    json config_json = readConfigFile();
    if (config_json == nullptr) return;

    config_json[parameter]=value;
    writeConfigFile(config_json);
    config::parseJson(config_json);
}

void config::updateConfigBool(std::string parameter, bool value)
{
    printf("updating parameter [%s] = [%s]\n", parameter.c_str(), value ? "true" : "false");
    json config_json = readConfigFile();
    if (config_json == nullptr) return;

    config_json[parameter]=value;
    writeConfigFile(config_json);
    config::parseJson(config_json);
}
