
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
  t0 = chrono::high_resolution_clock::now();
  //LOG(INFO) << "RESET";
}
long long Timer::get_dt_mircosec()
{
  chrono::high_resolution_clock::time_point t = chrono::high_resolution_clock::now();
  return chrono::duration_cast<chrono::microseconds>(t - t0).count();
}
long long Timer::get_dt_millisec() {
  chrono::high_resolution_clock::time_point t = chrono::high_resolution_clock::now();
  return chrono::duration_cast<chrono::milliseconds>(t - t0).count();
}
long long Timer::get_dt_sec() {
  chrono::high_resolution_clock::time_point t = chrono::high_resolution_clock::now();
  //LOG(INFO) << "get_dt_sec" << chrono::duration_cast<chrono::seconds>(t - t0).count();
  return chrono::duration_cast<chrono::seconds>(t - t0).count();
}