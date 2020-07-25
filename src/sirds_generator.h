#pragma once

#include <opencv2/core.hpp>

namespace stereogram {
    
cv::Mat generate_sirds(cv::Mat depth_map, int dpi);

} // namespace stereogram
