#pragma once

#include <opencv2/core.hpp>
#include "generator.h"

namespace stereogram {

class SirdsGenerator : public Generator {
 public:
  SirdsGenerator(cv::Mat depth_map, int dpi);

  cv::Mat Generate();

 private:
  cv::Mat depth_map_;
  int dpi_;
  double eye_separation_;
  const double mu_ = 1 / 3.0;

  double Separation(double depth);
};

}  // namespace stereogram
