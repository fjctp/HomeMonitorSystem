#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <thread>
#include <opencv2/opencv.hpp>

#include "Timer.hpp"
#include "md_config.hpp"

class Camera {
public:
  Camera();
  ~Camera();

  bool initialize(int8_t newCameraId=0, float newFrameRatePerSec=30.0);
  bool isOpened();
  void release();

  int ready();
  void get(myMat& mat);

private:
  void thread_update();
  void set();

  void resetCount();
  void incrementCount();

  thread::id tid;

  int8_t cameraId;
  float frameRateSecPerFrame;
  int count;

  Timer timer0;
  myMat frame;
  cv::VideoCapture cam;
};

void operator >> (Camera& cam, myMat& mat);

#endif // !CAMERA_HPP
