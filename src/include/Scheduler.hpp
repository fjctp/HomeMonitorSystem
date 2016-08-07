#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP
#include <string>

#include "Clock.hpp"
#include "Settings.hpp"

using namespace std;

class Scheduler: public Clock {
public:
  Scheduler();

  void initialize(ScheduleConfig newscfg, string new_format_str = "%m%d%y_%H%M%S");
  bool check(bool force = false);

private:
  void update();

  bool check_weekday();
  bool check_hour();
  bool check_minute();

  ScheduleConfig scfg;
  DayConfig dcfg;

  struct tm *now_info;
  const string weekdays[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
};

#endif