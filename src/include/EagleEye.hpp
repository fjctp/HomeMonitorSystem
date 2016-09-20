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
  void thread_main();
  void process_loop();

  ImageProcessor ip;
  FrameWriter fw;

  Clock clock0;
  Timer timer0;
  Scheduler s;

  int cam_id;
  int record_sec;
  Status status;

  myMat frame;
  FrameGrabber camFrameGrabber;
};

#endif