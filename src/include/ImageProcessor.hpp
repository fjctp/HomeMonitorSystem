#ifndef IMAGEPROCESSOR_HPP
#define IMAGEPROCESSOR_HPP

#include <opencv2/opencv.hpp>
#include "md_config.hpp"
#include "Settings.hpp"

class ImageProcessor {
public:
  static void combine(myMat lframe, myMat rframe, myMat& combined_frame);

  ImageProcessor();
  ~ImageProcessor();

  void initialize(GeneralConfig newgcfg);
  double process(myMat frame);
  void release();
  
  myMat colorFrame;
  myMat resizedFrame;
  myMat meshFrame;
  myMat joinedFrame;
  
  cv::Mat myKernel;

protected:
  double detectMotion(myMat frame);
  
  GeneralConfig gcfg;
  cv::Ptr<cv::BackgroundSubtractorMOG2> ptr2mog2;
};

#endif