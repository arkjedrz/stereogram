#pragma once

#include <opencv2/core.hpp>

namespace stereogram {

class Generator {
 public:
  ~Generator() = default;

  /**
   * Generates single image stereogram.
   */
  cv::Mat Generate();
};

}  // namespace stereogram