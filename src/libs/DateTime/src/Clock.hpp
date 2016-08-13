#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <ctime>
#include <string>

using namespace std;

class Clock {
public:
  Clock();
  virtual ~Clock();
  virtual void initialize(string new_format_str = "%m%d%y_%H%M%S");
  virtual string now2string();

protected:
  virtual void update();
  virtual string time2string(const time_t t);

  string format_str;
  time_t now;
};

#endif