#ifndef TIMER_HPP
#define TIMER_HPP

#include <ctime>
#include "Clock.hpp"

class Timer{
public:
  Timer();
  virtual void initialize();

  virtual void reset();
  virtual double get_dt_msec();
  virtual double get_dt_sec();

private:
  clock_t t0;
};

#endif