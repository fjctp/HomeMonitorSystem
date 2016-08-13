#include <ctime>
#include <string>
#include "Clock.hpp"

using namespace std;

Clock::Clock() {
  update();
}
Clock::~Clock() {
  
}

void Clock::initialize(string new_format_str) {
  format_str = new_format_str;
}

string Clock::now2string() {
  update();
  return time2string(now);
}

void Clock::update() {
  time(&now);
}

string Clock::time2string(const time_t t) {
  struct tm* timeinfo = localtime(&t);

  char buffer[256];
  strftime(buffer, 256, format_str.c_str(), timeinfo);
  return string(buffer);
}
