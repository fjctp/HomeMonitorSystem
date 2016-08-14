#include <ctime>
#include <string>
#include "easylogging++.h"

#include "Scheduler.hpp"
#include "Clock.hpp"
#include "Settings.hpp"


Scheduler::Scheduler() : Clock() {

}

Scheduler::~Scheduler() {

}

// set "ScheduleConfig" and timestamp format string
void Scheduler::initialize(ScheduleConfig newscfg, std::string new_format_str) {
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

  bool check_time_result = check_time();
  LOG(DEBUG) << "<CHECK>," << check_time_result;
  return check_weekday() && check_time_result;
}

// update internal time
void Scheduler::update() {
  Clock::update();
  now_info = localtime(&now);
}

bool Scheduler::check_weekday() {
  if((int) dcfg.name.find(weekdays[now_info->tm_wday]) > -1)
    return true;
  return false;
}
bool Scheduler::check_time()
{
  for (size_t i = 0; i < dcfg.timeslots.size(); i++) {
    int nowTime = (now_info->tm_hour*100) + now_info->tm_min;

    int startTime = dcfg.timeslots[i].startTime;
    int endTime = dcfg.timeslots[i].endTime;

    LOG(DEBUG) << "<CHECK_TIME>," << i << ",N," << nowTime << 
      ",S," << startTime << ",E," << endTime;

    if ((nowTime >= startTime) && (nowTime < endTime))
      return true;
  }
  return false;
}