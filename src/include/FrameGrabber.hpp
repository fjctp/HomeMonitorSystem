#ifndef FRAMEGRABBER_HPP
#define FRAMEGRABBER_HPP

#include <atomic>
#include <thread>
#include <opencv2/opencv.hpp>

//#include "Timer.hpp"
#include "md_config.hpp"

using namespace std;

class FrameGrabber {
public:
  FrameGrabber();
  ~FrameGrabber();

  bool initialize(int newCameraId=0, double newFPS=15.0);
  bool isOpened();
  void release();

  int ready();
  void get(myMat& mat);

private:
  void thread_update();
  void grabFrameFromCam();

  void resetCount();
  void incrementCount();

  thread::id tid;

  int cameraId;
  chrono::microseconds grabFramePeriodMicroSec;
  //Timer timer0;

  atomic_int count;
  atomic_int fps; // for debug

  myMat frame;
  cv::VideoCapture cam;
};

void operator >> (FrameGrabber& grabber, myMat& mat);

#endif // !FRAMEGRABBER_HPP
