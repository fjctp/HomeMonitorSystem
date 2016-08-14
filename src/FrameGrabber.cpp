
#include <chrono>
#include <thread>
#include <opencv2/opencv.hpp>
#include "easylogging++.h"

#include "FrameGrabber.hpp"
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

/*
  Called by a thread to get a new frame from the camera
  every X sec (related to FPS setting).
  @private
*/
void FrameGrabber::thread_update() {
  //timer0.reset();
  while (true) {
    //if (timer0.get_dt_mircosec() > grabFramePeriodMicroSec.count()) {
      grabFrameFromCam();
      this_thread::sleep_for(grabFramePeriodMicroSec);
    //}
    //this_thread::sleep_for(chrono::milliseconds(1));
  }
}

/*
  Get frame from the camera and increase the counter.
  @private
*/
void FrameGrabber::grabFrameFromCam() {
  cam >> frame;
  LOG(WARNING) << "FPS: " << fps++;
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