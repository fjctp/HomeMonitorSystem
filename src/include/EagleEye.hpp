#ifndef EAGLEEYE_HPP
#define EAGLEEYE_HPP
#include <thread>
#include <string>

#include "Settings.hpp"
#include "Camera.hpp"
#include "Scheduler.hpp"
#include "ImageProcessor.hpp"
#include "FrameWriter.hpp"
#include "Status.hpp"
#include "Timer.hpp"

using namespace std;

class EagleEye {
public:
  EagleEye();
  ~EagleEye();

  thread::id start(GeneralConfig newgcfg, OutputConfig newocfg, ScheduleConfig newscfg);
  void release();

protected:
  /*
   * thread        runs schedule_loop until the program/system shuts down
   * schedule_loop runs process_loop until current time is not on the schedule
   * process_loop  never stops
   */
  void thread_main();
  void thread_loop();

  ImageProcessor ip;
  FrameWriter fw;

  Clock clock0;
  Timer timer0;
  Scheduler s;
  Status status;

  unsigned int cam_id;
  float record_sec;
  myMat frame;
  Camera cam;
};

#endif