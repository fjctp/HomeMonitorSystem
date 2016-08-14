
#include <chrono>
//#include <easylogging++.h>
#include "Timer.hpp"

Timer::Timer() {
  reset();
}
void Timer::initialize() {
  reset();
}

void Timer::reset() {
  t0 = std::chrono::high_resolution_clock::now();
  //LOG(INFO) << "RESET";
}
long long Timer::get_dt_mircosec()
{
  std::chrono::high_resolution_clock::time_point t = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::microseconds>(t - t0).count();
}
long long Timer::get_dt_millisec() {
  std::chrono::high_resolution_clock::time_point t = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(t - t0).count();
}
long long Timer::get_dt_sec() {
  std::chrono::high_resolution_clock::time_point t = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::seconds>(t - t0).count();
}