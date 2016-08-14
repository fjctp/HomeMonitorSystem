#ifndef FRAMEWRITER_HPP
#define FRAMEWRITER_HPP
#include <string>
#include <opencv2/opencv.hpp>

#include "md_config.hpp"
#include "Settings.hpp"

using namespace std;

class FrameWriter {
public:
  FrameWriter();
  ~FrameWriter();

  void initialize(OutputConfig newCfg);

  void save(string timestamp_str, myMat frame);
  void record(string timestamp_str, myMat frame, double fps);
  void stop();

  void release();
  
protected:
  string get_fullpath(string timestamp_str, string extension);

  cv::VideoWriter vWriter;
  OutputConfig cfg;

};


#endif