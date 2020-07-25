#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace stereogram {

/**
 * Checks if file exists.
 */
bool FileExists(const std::string &filepath);

/**
 * Loads image from specified path and converts it to a single-channel Mat of
 * floats (normalized to <0;1>).
 */
cv::Mat LoadDepthMap(const std::string &filepath);

}  // namespace stereogram