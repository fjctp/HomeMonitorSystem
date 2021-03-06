#ifndef FRAMEGRABBER_HPP
#define FRAMEGRABBER_HPP

#include <atomic>
#include <thread>
#include <opencv2/opencv.hpp>

#include "md_config.hpp"

class FrameGrabber {
public:
  FrameGrabber();
  ~FrameGrabber();

  bool initialize(int newCameraId=0, double newFPS=15.0);
  bool isOpened();
  void release();

  int ready();
  void get(myMat& mat);
  double getFPS();

private:
  void thread_update();
  void grabFrameFromCam();

  void resetCount();
  void incrementCount();

  std::thread::id tid;

  int cameraId;
  std::chrono::microseconds grabFramePeriodMicroSec;

  std::atomic_int count;
  std::atomic_int fps;

  myMat frame;
  cv::VideoCapture cam;
};

void operator >> (FrameGrabber& grabber, myMat& mat);

#endif // !FRAMEGRABBER_HPP
