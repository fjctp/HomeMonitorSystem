#ifndef EYES_HPP
#define EYES_HPP

#include <thread>
#include <vector>
#include "Settings.hpp"
#include "EagleEye.hpp"

using namespace std;

class Nest {
public:
  Nest();
  ~Nest();

  void start(Setting s); // TODO: update it to be a vector, support multi camera
  void release();

private:
  thread::id ptid;
  vector<thread::id> tids;
};

#endif