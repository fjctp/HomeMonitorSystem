#ifndef FRAMEWRITER_HPP
#define FRAMEWRITER_HPP
#include <string>
#include <opencv2/opencv.hpp>

#include "md_config.hpp"
#include "Settings.hpp"

class FrameWriter {
public:
  FrameWriter();
  ~FrameWriter();

  void initialize(OutputConfig newCfg);

  void save(std::string timestamp_str, myMat frame);
  void record(std::string timestamp_str, myMat frame, double fps);
  void stop();

  void release();
  
protected:
  std::string get_fullpath(std::string timestamp_str, std::string extension);

  cv::VideoWriter vWriter;
  OutputConfig cfg;

};


#endif