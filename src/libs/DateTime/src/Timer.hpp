#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include "Clock.hpp"

using namespace std;

class Timer{
public:
  Timer();
  virtual void initialize();

  virtual void reset();
  virtual long long get_dt_mircosec();
  virtual long long get_dt_millisec();
  virtual long long get_dt_sec();

private:
  chrono::high_resolution_clock::time_point t0;
};

#endif