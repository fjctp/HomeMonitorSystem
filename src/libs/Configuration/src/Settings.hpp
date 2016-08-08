#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <vector>
#include <string>
#include "yaml-cpp/yaml.h"

// Data type
struct TimeSlot {
  unsigned int startHour;
  unsigned int startMinute;
  unsigned int endHour;
  unsigned int endMinute;
};

struct DayConfig {
  std::string name;
  std::vector<TimeSlot> timeslots;
};

struct ScheduleConfig {
  std::vector<DayConfig> weekdays;
};

struct OutputConfig {
  std::string dir;
  std::string prefix;
  std::string format_string;
  std::string picture_ext;
  std::string video_ext;
};

struct GeneralConfig {
  unsigned int camera_id;
  float record_sec;
  unsigned int reduction_factor;
  unsigned int min_contour_area;
  float adaptive_rate;
  unsigned int kernel_size;
};

struct Setting {
  GeneralConfig general;
  OutputConfig output;
  ScheduleConfig schedule;
};


// extraction operator for the structures
void operator >> (const YAML::Node& node, TimeSlot& ts);
void operator >> (const YAML::Node& node, DayConfig& dcfg);
void operator >> (const YAML::Node& node, ScheduleConfig& scfg);
void operator >> (const YAML::Node& node, OutputConfig& ocfg);
void operator >> (const YAML::Node& node, GeneralConfig& gcfg);
void operator >> (const YAML::Node& node, Setting& syscfg);

#endif // !SETTINGS_HPP
