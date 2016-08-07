#ifndef STATUS_HPP
#define STATUS_HPP
#include <string>
#include <atomic>

using namespace std;

class Status {
public:
  // Assumptions: -1: exit mode, 0: idle mode
  // Default: 0
  enum States { TERMINATE = -1, STANDBY, MONITOR, RECORD };

  Status();
  virtual void initialize();

  virtual bool set(int newState);
  virtual void confirm();

  virtual bool check(int checkState);
  virtual int getId();
  virtual string getName();

protected:
  atomic_int state;
  atomic_bool ready;

  const string states_name[4] = {"Terminate", "Standby", "Monitor", "Record"};
};

#endif //STATUS_HPP