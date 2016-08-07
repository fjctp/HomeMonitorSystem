#include <string>
#include <atomic>

#include "Status.hpp"
#include "easylogging++.h"

using namespace std; 

Status::Status() {
  state = 0;
  ready = true;
}

void Status::initialize() {
  set(0);
  confirm();
}

bool Status::check(int checkState) {
  return (getId() == checkState) && ready.load();
}
int Status::getId() {
  return state.load();
}
string Status::getName() {
  // index starts from -1
  return states_name[getId()+1];
}
bool Status::set(int newState) {
  LOG(DEBUG) << "From " << getName() << " Mode";
  if (!check(States(-1))) {
    state = newState;
    ready = false;
    //LOG(INFO) << "Change to " << getName() << " Mode";
    return true;
  }
  return false;
}

void Status::confirm() {
  LOG(INFO) << "In " << getName() << " Mode";
  ready = true;
}