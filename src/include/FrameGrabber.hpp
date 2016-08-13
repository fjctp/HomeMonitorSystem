#ifndef FRAMEGRABBER_HPP
#define FRAMEGRABBER_HPP

#include <atomic>
#include <thread>
#include <opencv2/opencv.hpp>

#include "Timer.hpp"
#include "md_config.hpp"

class FrameGrabber {
public:
  FrameGrabber();
  ~FrameGrabber();

  bool initialize(int newCameraId=0, double newFPS=30.0);
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
  double grabFramePeriod;
  atomic_int count;

  Timer timer0;
  myMat frame;
  cv::VideoCapture cam;
};

void operator >> (FrameGrabber& cam, myMat& mat);

#endif // !FRAMEGRABBER_HPP
