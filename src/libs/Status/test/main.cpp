#include <iostream>

#include "Status.hpp"

using namespace std;

void printStatus(Status& ss, int check) {
  cout << check << "? " << (ss.check(check)?"True":"False") << endl;
  cout << "ID and Name: " << ss.getId() << ":" << ss.getName() << endl;
}

int main(int argc, char** argv) {

  Status ss;

  printStatus(ss, ss.STANDBY);
  ss.set(ss.MONITOR);
  printStatus(ss, ss.MONITOR);
  ss.confirm();
  printStatus(ss, ss.MONITOR);

  return 0;
}