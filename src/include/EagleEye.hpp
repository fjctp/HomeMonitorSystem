#ifndef EAGLEEYE_HPP
#define EAGLEEYE_HPP
#include <thread>

#include "Settings.hpp"
#include "FrameGrabber.hpp"
#include "Scheduler.hpp"
#include "ImageProcessor.hpp"
#include "FrameWriter.hpp"
#include "Status.hpp"
#include "Timer.hpp"

class EagleEye {
public:
  EagleEye();
  ~EagleEye();

  std::thread::id start(GeneralConfig newgcfg, OutputConfig newocfg, ScheduleConfig newscfg);
  void release();

private:
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

  int cam_id;
  int record_sec;
  myMat frame;
  FrameGrabber camFrameGrabber;
};

#endif