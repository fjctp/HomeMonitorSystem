
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
double Timer::get_dt_msec()
{
  return get_dt_msec()*1000.0;
}
double Timer::get_dt_sec() {
  return ((double)clock() - (double)t0) / (double) CLOCKS_PER_SEC;
}