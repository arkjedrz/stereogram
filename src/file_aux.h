#pragma once

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

namespace stereogram {

/**
 * Loads image from specified path and converts it to a single-channel Mat of floats (normalized to <0;1>).
 */
cv::Mat load_depth_map(const std::string& filepath);

}