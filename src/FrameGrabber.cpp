
#include <chrono>
#include <thread>
#include <opencv2/opencv.hpp>
#include "easylogging++.h"

#include "FrameGrabber.hpp"
#include "Timer.hpp"
#include "md_config.hpp"

using namespace std;

FrameGrabber::FrameGrabber() {
  cameraId = 0;
  grabFramePeriodMicroSec = chrono::microseconds(0);
  fps = 0;
  resetCount();
}
FrameGrabber::~FrameGrabber() {
  if (isOpened())
    release();
}

/*
  Initialize with settings and start a new thread to get frame from the camera.
  Since IO operations are slow, we do not want to block other operations.
*/
bool FrameGrabber::initialize(int newCameraId, double newFPS) {
  cameraId = newCameraId;
  grabFramePeriodMicroSec = chrono::microseconds(
    (int)floor(1.0/newFPS*1e6));
  resetCount();

  if (cam.isOpened())
    cam.release();
  cam.open(cameraId);

  //timer0.initialize();
  if (cam.isOpened()) {
    cam.set(cv::CAP_PROP_FPS, newFPS);
    thread t1(&FrameGrabber::thread_update, this);
    tid = t1.get_id();
    t1.detach();
    return true;
  }
  return false;
}

/*
  Check if the FrameGrabber is opened for reading.
  @public
*/
bool FrameGrabber::isOpened() {
  return cam.isOpened();
}

/*
  Release resource.
  @public
*/
void FrameGrabber::release() {
  if (isOpened())
    cam.release();
}

/*
  Return frame count that are ready
  This class keeps the latest frame only. If the count is greater than 1,
  it means some frames are missed.
  @public
*/
int FrameGrabber::ready() {
  return count.load();
}

/*
  Get the latest frame from the camera and reset the counter.
  @public
*/
void FrameGrabber::get(myMat& mat) {
  frame.copyTo(mat);
  resetCount();
}

double FrameGrabber::getFPS() {
  return (double) fps.load();
}

/*
  Called by a thread to get a new frame from the camera
  every X sec (related to FPS setting).
  @private
*/
void FrameGrabber::thread_update() {
  const long long calc_sample_time = 500ll;
  const int gain = 2;
  int fps_count = 0;

  Timer timer0 = Timer();
  timer0.initialize();
  timer0.reset();

  while (true) {
    grabFrameFromCam(); // get latest frame from cam

    // calculate FPS
    fps_count++;
    if (timer0.get_dt_millisec() > calc_sample_time) {
      fps = fps_count*gain;
      fps_count = 0;
      timer0.reset();
      //LOG(WARNING) << "FPS: " << getFPS();
    }

    // wait for a certain time (defined as FPS) before getting new frame
    this_thread::sleep_for(grabFramePeriodMicroSec);
  }
}

/*
  Get frame from the camera and increase the counter.
  @private
*/
void FrameGrabber::grabFrameFromCam() {
  cam >> frame;
  incrementCount();
}

void FrameGrabber::resetCount() {
  count = 0;
}

void FrameGrabber::incrementCount() {
  count++;
}

void operator >> (FrameGrabber & grabber, myMat & mat) {
  grabber.get(mat);
}