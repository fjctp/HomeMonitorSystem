#include <string>
#include <atomic>

#include "Status.hpp"
#include "easylogging++.h"

using namespace std; 

Status::Status() {
  state = 0;
  ready = true;
}

Status::~Status() {

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

/*
  set the new state
*/
bool Status::set(int newState) {
  if (!check(States(-1))) {
    // set the new state, only if the current state is not TERMINATE
    LOG(DEBUG) << "From " << getName() << " Mode";
    state = newState;
    ready = false;
    LOG(DEBUG) << "Change to " << getName() << " Mode";
    return true;
  }
  return false;
}

/*
  confirm that it is in the new state
  used when in different threads
  thread 1 changed the state, but thread 2 may not know it immediately, 
  so thread 2 needs to confirm the change
*/
void Status::confirm() {
  LOG(INFO) << "In " << getName() << " Mode";
  ready = true;
}