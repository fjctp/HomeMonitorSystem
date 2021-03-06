#include <thread>
#include <chrono>
#include <string>
#include "easylogging++.h"

#include "EagleEye.hpp"
#include "Settings.hpp"

using namespace std;

EagleEye::EagleEye() {
  
}

EagleEye::~EagleEye() {
  release();
}

/*
  setup and start a thread for the camera
  @public
*/
thread::id EagleEye::start(GeneralConfig newgcfg, OutputConfig newocfg, ScheduleConfig newscfg) {
  cam_id = newgcfg.camera_id;
  record_sec = newgcfg.record_sec;

  camFrameGrabber.initialize(cam_id, 15.0); // hard coded for 15 FPS
  if (!camFrameGrabber.isOpened()) {
    LOG(WARNING) << "Cannot start camera " << cam_id;
    return this_thread::get_id(); // return parent id
  }

  ip.initialize(newgcfg);
  fw.initialize(newocfg);
  s.initialize(newscfg, newocfg.format_string);

  status.initialize();
  clock0.initialize(newocfg.format_string);
  timer0.initialize();

  // start the thread
  thread t1(&EagleEye::thread_main, this);
  thread::id id = t1.get_id();
  t1.detach();
  return id; // return child id
}

/*
  release resource
  @public
*/
void EagleEye::release() {
  LOG(INFO) << "Releasing camera " << cam_id;
  ip.release();
  fw.release();
  if (camFrameGrabber.isOpened())
    camFrameGrabber.release();
}

/*
  Thread's main function
  if the program is not in Terminate mode and
  the current is defined in the schedule, run image processing loop
  @private
*/
void EagleEye::thread_main() {
  LOG(INFO) << "EagleEye started using camera " << cam_id;
  timer0.reset();

  while (!status.check(status.TERMINATE)) {
    // main loop
    while (s.check() && !status.check(status.TERMINATE)) {
      // schedule loop

      /* if switched from STANDBY
         change the current mode to MONITOR  */
      if (status.check(status.STANDBY)) {
        status.set(status.MONITOR);
        status.confirm();
      }

      // grab frame and process it
      process_loop();
      this_thread::sleep_for(chrono::milliseconds(1));
    }

    // Not in schedule, switch to STANDBY
    if (!status.check(status.STANDBY)) {
      status.set(status.STANDBY);
      status.confirm();
    }

    // Not in schedule, slow down to preserve resource
    this_thread::sleep_for(chrono::seconds(1));
  }
  
  // exiting the thread, clean up
  release();
}

/*
  Image processing loop
  get a frame from the camera, and check if motion is detected.
  If yes, take a snapshot and start recording.
  @private
*/
void EagleEye::process_loop() {
  if (camFrameGrabber.ready() > 0) {
    camFrameGrabber >> frame;
    double detected_contour_area = ip.process(frame);
    if (detected_contour_area>0)
      LOG(INFO) << "<CONTOUR_AREA>, " << detected_contour_area;

    // switch to record mode and save sanpshot if motion detected
    string filetimestamp;
    if ((detected_contour_area>0) && (!status.check(status.RECORD))) {
      status.set(status.RECORD);
      status.confirm();

      timer0.reset();
      filetimestamp = clock0.now2string();
      fw.save(filetimestamp, ip.joinedFrame);
    }

    // stop recording after X sec (defined in condig.yaml)
    if ((timer0.get_dt_sec() > record_sec)
      && (status.check(status.RECORD))) {
      status.set(status.MONITOR);
      status.confirm();
    }

    // continue saving video if in RECORD mode, 
    // otherwise close the file
    if (status.check(status.RECORD))
      fw.record(filetimestamp, frame, camFrameGrabber.getFPS());
    else if (!status.check(status.RECORD))
      fw.stop();
  }
}
