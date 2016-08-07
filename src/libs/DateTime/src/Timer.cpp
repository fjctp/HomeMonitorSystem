
#include <ctime>
#include "Clock.hpp"
#include "Timer.hpp"

Timer::Timer() {
  reset();
}
void Timer::initialize() {
  reset();
}

void Timer::reset() {
  t0 = clock();
}
float Timer::get_dt_msec()
{
  return get_dt_msec()*1000.0;
}
float Timer::get_dt_sec() {
  return ((float)clock() - (float)t0) / CLOCKS_PER_SEC;
}