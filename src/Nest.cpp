#include <thread>
#include <chrono>
#include "easylogging++.h"

#include "Nest.hpp"
#include "EagleEye.hpp"
#include "Settings.hpp"

using namespace std;

Nest::Nest() {
  ptid = this_thread::get_id();
}
Nest::~Nest() {
  release();
}

void Nest::start(Setting s) {
  EagleEye e;

  thread::id id = e.start(s.general, s.output, s.schedule);
  if (id != ptid)
    tids.push_back(id);

  LOG(DEBUG) << "Parent ID: " << ptid;
  for (size_t i = 0; i < tids.size(); i++) {
    LOG(DEBUG) << "Child ID: " << tids[i];
  }

  // main loop, not doing anything
  // slow down to preserve resource
  while (true) {
    this_thread::sleep_for(1s);
  }
  LOG(INFO) << "Exit";
}

void Nest::release() {
  // TODO: release all EagleEye objects
}