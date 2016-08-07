#include <ctime>
#include <string>
#include "easylogging++.h"

#include "Scheduler.hpp"
#include "Clock.hpp"
#include "Settings.hpp"


Scheduler::Scheduler() : Clock() {

}

// set "ScheduleConfig" and timestamp format string
void Scheduler::initialize(ScheduleConfig newscfg, string new_format_str) {
  Clock::initialize(new_format_str);
  scfg = newscfg;
  check(true); // force check to initialize internal variables
}

// if current time is on the schedule, return true
bool Scheduler::check(bool force) {
  update(); // update current time

  // get current weekday's config from setting
  if (force || (now_info->tm_hour==0)) {
    for (size_t i = 0; i < scfg.weekdays.size(); i++) {
      if ((int) scfg.weekdays[i].name.find(weekdays[now_info->tm_wday]) > -1) {
        dcfg = scfg.weekdays[i];
        break;
      }
    }
  }

  //LOG(DEBUG) << weekdays[now_info->tm_wday] << "==" << dcfg.name << "?";
  return check_weekday() && check_hour() && check_minute();
}

// call to update object's variables with current time
void Scheduler::update() {
  Clock::update();
  now_info = localtime(&now);
}

bool Scheduler::check_weekday() {
  if((int) dcfg.name.find(weekdays[now_info->tm_wday]) > -1)
    return true;
  return false;
}
bool Scheduler::check_hour() {
  for (size_t i = 0; i < dcfg.timeslots.size(); i++) {
    if ((dcfg.timeslots[i].start <= (unsigned int)now_info->tm_hour) &&
      ((unsigned int)now_info->tm_hour < dcfg.timeslots[i].end)) {
      return true;
    }
  }
  return false;
}
bool Scheduler::check_minute() {
  return true;
}
