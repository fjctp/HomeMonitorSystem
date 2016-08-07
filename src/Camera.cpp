
#include <cstdint>
#include <chrono>
#include <thread>
#include <opencv2/opencv.hpp>
#include "easylogging++.h"

#include "Camera.hpp"
#include "md_config.hpp"

Camera::Camera()
{
  cameraId = 0;
  frameRateSecPerFrame = 0;
  resetCount();
}
Camera::~Camera()
{
  if (isOpened())
    release();
}

bool Camera::initialize(int8_t newCameraId, float newFrameRatePerSec)
{
  cameraId = newCameraId;
  frameRateSecPerFrame = (float) 1.0/newFrameRatePerSec;
  resetCount();

  if (cam.isOpened())
    cam.release();
  cam.open(cameraId);

  timer0.initialize();
  if (cam.isOpened()) {
    thread t1(&Camera::thread_update, this);
    tid = t1.get_id();
    t1.detach();
    return true;
  }
  return false;
}

bool Camera::isOpened()
{
  return cam.isOpened();
}

void Camera::release()
{
  if (isOpened())
    cam.release();
}

int Camera::ready()
{
  return (int) count;
}

void Camera::get(myMat& mat)
{
  frame.copyTo(mat);
  resetCount();
}

void Camera::thread_update()
{
  while (true) {
    if (timer0.get_dt_sec()>=frameRateSecPerFrame)
      set();
    this_thread::sleep_for(1ms);
  }
}

void Camera::set()
{
  cam >> frame;
  timer0.reset();
  incrementCount();
}

void Camera::resetCount()
{
  count = 0;
}

void Camera::incrementCount()
{
  count++;
}

void operator >> (Camera & cam, myMat & mat)
{
  cam.get(mat);
}