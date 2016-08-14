#include <string>
#include <opencv2/opencv.hpp>

#include "FrameWriter.hpp"
#include "md_config.hpp"
#include "Settings.hpp"

using namespace std; 

FrameWriter::FrameWriter() {

}
FrameWriter::~FrameWriter() {
  stop();
}


void FrameWriter::initialize(OutputConfig newCfg) {
  cfg = newCfg;
}

void FrameWriter::save(string timestamp_str, myMat frame) {
  string fullpath = get_fullpath(timestamp_str, cfg.picture_ext);
  cv::imwrite(fullpath, frame);
}
void FrameWriter::record(string timestamp_str, myMat frame) {
  if (!vWriter.isOpened()) {
    string fullpath = get_fullpath(timestamp_str, cfg.video_ext);
    //int fourcc = cv::VideoWriter::fourcc('M', 'J', 'P', 'G'); // W5000kb
    int fourcc = cv::VideoWriter::fourcc('W', 'M', 'V', '1'); // W600kb
    //int fourcc = cv::VideoWriter::fourcc('W', 'M', 'V', '2'); // W600kb
    //int fourcc = cv::VideoWriter::fourcc('W', 'M', 'V', '3'); // WError
    //int fourcc = cv::VideoWriter::fourcc('X', '2', '6', '4'); // WError
    //int fourcc = cv::VideoWriter::fourcc('H', '2', '6', '4'); // WError
    //int fourcc = cv::VideoWriter::fourcc('X', 'V', 'I', 'D'); // W700kb
    //int fourcc = cv::VideoWriter::fourcc('D', 'I', 'V', 'X'); // W600kb
    bool success = vWriter.open(fullpath, fourcc, 10, frame.size(), true);
  }

  // convert from myMat (Mat/UMat) to Mat, VideoWriter accepts Mat only
  cv::Mat tmp_frame;
  frame.copyTo(tmp_frame);
  vWriter << tmp_frame;
}
void FrameWriter::stop() {
  if (vWriter.isOpened())
    vWriter.release();
}

void FrameWriter::release() {
  stop();
}

string FrameWriter::get_fullpath(string timestamp_str, string extension) {
  string fullpath = "";
  return fullpath.append(cfg.dir)
    .append(cfg.prefix)
    .append(timestamp_str)
    .append(extension);
}