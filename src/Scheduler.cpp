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

  bool check_time_result = check_time();
  LOG(DEBUG) << ">>>>check_time: " << check_time_result;
  return check_weekday() && check_time_result;
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
bool Scheduler::check_time()
{
  LOG(DEBUG) << "CHECK_TIME";
  for (size_t i = 0; i < dcfg.timeslots.size(); i++) {
    unsigned int nowHour = (unsigned int)now_info->tm_hour;
    unsigned int nowMinute = (unsigned int)now_info->tm_min;

    unsigned int startHour = dcfg.timeslots[i].startHour;
    unsigned int endHour = dcfg.timeslots[i].endHour;
    unsigned int startMinute = dcfg.timeslots[i].startMinute;
    unsigned int endMinute = dcfg.timeslots[i].endMinute;

    LOG(DEBUG) << ">>" << i;
    LOG(DEBUG) << "Now: " << nowHour << ":" << nowMinute;
    LOG(DEBUG) << "Hour: " << startHour << "->" << endHour;
    LOG(DEBUG) << "Minute: " << startMinute << "->" << endMinute;

    LOG(DEBUG) << check_hour(nowHour, startHour, endHour);
    LOG(DEBUG) << check_minute(nowMinute, startMinute, endMinute);

    bool hour_minute_result = (check_hour(nowHour, startHour, endHour) &&
      check_minute(nowMinute, startMinute, endMinute));
    bool hour_result = check_hour(nowHour, startHour, endHour);

    LOG(DEBUG) << "hour_minute_result: " << hour_minute_result;
    LOG(DEBUG) << "hour_result: " << hour_result;

    if (((nowHour == startHour) || (nowHour == endHour)) && hour_minute_result)
      // at the starting or ending point, check hour and minute
      return true;
    else if (((nowHour >= startHour) && (nowHour < endHour)) && hour_result)
      // in between the schedule, check hour only
      return true;
  }
  return false;
}
bool Scheduler::check_hour(unsigned int nowHour, unsigned int startHour, unsigned int endHour)
{
  if((startHour <= nowHour) && (nowHour >= endHour))
    return true;
  return false;
}
bool Scheduler::check_minute(unsigned int nowMinute, unsigned int startMinute, unsigned int endMinute)
{
  if ((startMinute <= nowMinute) && (nowMinute <= endMinute))
    return true;
  return false;
}