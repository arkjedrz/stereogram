#pragma once

#include <opencv2/core.hpp>
#include "generator.h"

namespace stereogram {

class SirdsGenerator : public Generator {
 public:
  explicit SirdsGenerator(cv::Mat depth_map, int dpi);

  cv::Mat Generate() override;

 private:
  cv::Mat depth_map_;
  int dpi_;
  double eye_separation_;
  const double mu_ = 1 / 3.0;

  double Separation(double depth) const;
};

}  // namespace stereogram
