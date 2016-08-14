#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP
#include <string>

#include "Clock.hpp"
#include "Settings.hpp"

class Scheduler: private Clock {
public:
  Scheduler();
  virtual ~Scheduler();

  void initialize(ScheduleConfig newscfg, std::string new_format_str = "%m%d%y_%H%M%S");
  bool check(bool force = false);

private:
  void update();

  bool check_weekday();
  bool check_time();

  ScheduleConfig scfg;
  DayConfig dcfg;

  struct tm *now_info;
  const std::string weekdays[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
};

#endif