#include "file_helpers.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace stereogram;

bool stereogram::FileExists(const std::string &filepath) {
  if (FILE *file = fopen(filepath.c_str(), "r")) {
    fclose(file);
    return true;
  } else {
    return false;
  }
}

cv::Mat stereogram::LoadDepthMap(const std::string &filepath) {
  // Read from file.
  cv::Mat input = cv::imread(filepath, cv::ImreadModes::IMREAD_GRAYSCALE);
  // Convert input to floating point.
  cv::Mat input_f32(input.rows, input.cols, CV_32FC1);
  input.convertTo(input_f32, CV_32FC1);
  // Normalize to <0; 1>.
  input_f32.forEach<float>(
      [](float &pixel, const int *index) { pixel /= 255.0; });

  return input_f32;
}
