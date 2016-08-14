#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <ctime>
#include <string>

class Clock {
public:
  Clock();
  virtual ~Clock();
  virtual void initialize(std::string new_format_str = "%m%d%y_%H%M%S");
  virtual std::string now2string();

protected:
  virtual void update();
  virtual std::string time2string(const time_t t);

  std::string format_str;
  time_t now;
};

#endif