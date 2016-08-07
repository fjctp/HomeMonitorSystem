#include <vector>
#include <string>
#include "yaml-cpp/yaml.h"
#include "easylogging++.h"
#include "Settings.hpp"


// extraction operator for the structures
void operator >> (const YAML::Node& node, TimeSlot& ts) {
  LOG(DEBUG) << "Parsing timeslot";
  ts.start = node["start"].as<unsigned int>();
  ts.end = node["end"].as<unsigned int>();
}

void operator >> (const YAML::Node& node, DayConfig& dcfg) {
  dcfg.name = node["weekday"].as<std::string>();
  LOG(DEBUG) << "Parsing schedule for " << dcfg.name;

  const YAML::Node& sn = node["timeslots"];
  for (size_t i = 0; i < sn.size(); i++) {
    TimeSlot ts;
    sn[i] >> ts;
    dcfg.timeslots.push_back(ts);
  }
}

void operator >> (const YAML::Node& node, ScheduleConfig& scfg) {
  LOG(DEBUG) << "Parsing schedule";
  for (size_t i = 0; i < node.size(); i++) {
    DayConfig dcfg;
    node[i] >> dcfg;
    scfg.weekdays.push_back(dcfg);
  }
}

void operator >> (const YAML::Node& node, OutputConfig& ocfg) {
  LOG(DEBUG) << "Parsing output settings";

  // directory setting
  ocfg.dir = node["dir"].as<std::string>();

  // file setting (picture and video)
  ocfg.prefix = node["filename_prefix"].as<std::string>();
  ocfg.format_string = node["filename_format_string"].as<std::string>();
  ocfg.picture_ext = node["picture_ext"].as<std::string>();
  ocfg.video_ext = node["video_ext"].as<std::string>();
}

void operator >> (const YAML::Node& node, GeneralConfig& gcfg) {
  LOG(DEBUG) << "Parsing general settings";
  gcfg.camera_id = node["camera_id"].as<unsigned int>();
  gcfg.record_sec = node["record_sec"].as<unsigned int>();
  gcfg.reduction_factor = node["reduction_factor"].as<unsigned int>();
  gcfg.min_contour_area = node["min_contour_area"].as<unsigned int>();
  gcfg.adaptive_rate = node["adaptive_rate"].as<float>();
  gcfg.kernel_size = node["kernel_size"].as<unsigned int>();
}

void operator >> (const YAML::Node& node, Setting& syscfg) {
  LOG(DEBUG) << "Parsing root";
  node["general"] >> syscfg.general;
  node["output"] >> syscfg.output;
  node["schedules"] >> syscfg.schedule;
}

