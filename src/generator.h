#pragma once

#include <opencv2/core.hpp>

namespace stereogram {

class Generator {
 public:
  ~Generator() = default;

  /**
   * Generates single image stereogram.
   */
  virtual cv::Mat Generate() = 0;
};

}  // namespace stereogram