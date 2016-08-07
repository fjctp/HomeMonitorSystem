#include <vector>
#include <opencv2/opencv.hpp>

#include "ImageProcessor.hpp"
#include "md_config.hpp"
#include "Settings.hpp"

using namespace std;

void ImageProcessor::combine(myMat lframe, myMat rframe, myMat& combined_frame) {
  cv::Size lsize = lframe.size();
  cv::Size rsize = rframe.size();
  combined_frame =  myMat(lsize.height, 2 * lsize.width, lframe.type());

  // since mesh is gray, need to convert it to color before combining frames
  myMat rframe_bgr;
  cv::cvtColor(rframe, rframe_bgr, cv::COLOR_GRAY2BGR);

  // copy the frames into the combined frame at the right place
  combined_frame.adjustROI(0, 0, 0, -rsize.width);
  lframe.copyTo(combined_frame);
  combined_frame.adjustROI(0, 0, -rsize.width, rsize.width);
  rframe_bgr.copyTo(combined_frame);
  combined_frame.adjustROI(0, 0, lsize.width, 0);

}

ImageProcessor::ImageProcessor() {

}
ImageProcessor::~ImageProcessor() {
  release();
}

void ImageProcessor::initialize(GeneralConfig newgcfg) {
  release();

  gcfg = newgcfg;
  ptr2mog2 = cv::createBackgroundSubtractorMOG2();
  cv::Size ksize = cv::Size(gcfg.kernel_size, gcfg.kernel_size);
  myKernel = cv::getStructuringElement(cv::MorphShapes::MORPH_ELLIPSE, ksize);
}

bool ImageProcessor::process(myMat frame) {
  // pre-processing
  cv::Size ss = frame.size();
  cv::Size s(ss.width / gcfg.reduction_factor, ss.height / gcfg.reduction_factor);
  cv::resize(frame, resizedFrame, s);

  // processing
  bool detected = detectMotion(resizedFrame);

  // post-processing
  colorFrame = frame;
  combine(resizedFrame, meshFrame, joinedFrame);

#if SHOW_WINDOWS
  cv::imshow("Org", frame);
  //cv::imshow("Resized", resizedFrame);
  //cv::imshow("Mesh", meshFrame);
  cv::imshow("Joined", joinedFrame);
  
  cv::waitKey(1); // call to update windows
#endif

  return detected;
}

void ImageProcessor::release() {
  if (!ptr2mog2.empty())
    ptr2mog2.release();
  if (!myKernel.empty())
    myKernel.release();
}

bool ImageProcessor::detectMotion(myMat frame) {
  ptr2mog2->apply(frame, meshFrame, gcfg.adaptive_rate);

  // noise reduction
  //cv::morphologyEx(meshFrame.clone(), meshFrame, cv::MORPH_OPEN, myKernel);
  cv::erode(meshFrame.clone(), meshFrame, myKernel, cv::Point(-1, -1), 2);
  //cv::dilate(meshFrame.clone(), meshFrame, myKernel);

  vector<myMat> contours;
  cv::findContours(meshFrame.clone(), contours, cv::RETR_EXTERNAL,
    cv::CHAIN_APPROX_SIMPLE);
  for (size_t i = 0; i<contours.size(); i++) {
    if (cv::contourArea(contours[i]) >= gcfg.min_contour_area) {
      return true;
    }
  }
  return false;

}