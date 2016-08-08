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

thread::id EagleEye::start(GeneralConfig newgcfg, OutputConfig newocfg, ScheduleConfig newscfg) {
  cam_id = newgcfg.camera_id;
  record_sec = newgcfg.record_sec;

  cam.initialize(cam_id, 30); // hard coded for 30 FPS
  if (!cam.isOpened()) {
    LOG(WARNING) << "Cannot start camera id " << cam_id;
    return this_thread::get_id(); // return parent id
  }

  ip.initialize(newgcfg);
  fw.initialize(newocfg);
  s.initialize(newscfg, newocfg.format_string);

  status.initialize();
  clock0.initialize(newocfg.format_string);
  timer0.initialize();

  thread t1(&EagleEye::thread_main, this);
  thread::id id = t1.get_id();
  t1.detach();
  return id; // return child id
}

void EagleEye::release() {
  LOG(INFO) << "Release resources";
  ip.release();
  fw.release();
  if (cam.isOpened())
    cam.release();
}

void EagleEye::thread_main() {
  LOG(INFO) << "EagleEye started using camera id " << cam_id;
  timer0.reset();

  while (!status.check(status.TERMINATE)) {
    while (s.check() && !status.check(status.TERMINATE)) {
      if (status.check(status.STANDBY)) {
        status.set(status.MONITOR);
        status.confirm();
      }
      thread_loop();
    }

    // Not in schedule
    // slow down to preserve resource
    if (!status.check(status.STANDBY)) {
      status.set(status.STANDBY);
      status.confirm();
    }
    this_thread::sleep_for(1s);
  }
  
  // exiting the thread, clean up
  release();
}

void EagleEye::thread_loop() {
  if (cam.ready() > 0) {
    cam >> frame;
    bool detected = ip.process(frame);

    // switch to record mode and save sanpshot if motion detected
    string filetimestamp;
    if (detected && (!status.check(status.RECORD))) {
      status.set(status.RECORD);
      status.confirm();
      LOG(DEBUG) << "motion detected";

      timer0.reset();
      filetimestamp = clock0.now2string();
      fw.save(filetimestamp, ip.joinedFrame);
    }

    // stop recording after X sec (defined in condig.yaml)
    if ((timer0.get_dt_sec() >= record_sec)
      && (status.check(status.RECORD))) {
      status.set(status.MONITOR);
      status.confirm();
    }

    // continue saving video if in RECORD mode, 
    // otherwise close the file
    if (status.check(status.RECORD))
      fw.record(filetimestamp, frame);
    else if (!status.check(status.RECORD))
      fw.stop();
  }
  this_thread::sleep_for(1ms);
}
