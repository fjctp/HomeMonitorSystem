#ifndef EYES_HPP
#define EYES_HPP

#include <thread>
#include <vector>
#include "Settings.hpp"
#include "EagleEye.hpp"

class Nest {
public:
  Nest();
  ~Nest();

  void start(Setting s); // TODO: update it to be a vector, support multi camera
  void release();

private:
  std::thread::id ptid;
  std::vector<std::thread::id> tids;
};

#endif