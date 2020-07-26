#include "sirds_generator.h"
#include <cmath>
#include <opencv2/core.hpp>
#include <random>

using namespace stereogram;

SirdsGenerator::SirdsGenerator(cv::Mat depth_map, int dpi)
    : depth_map_{depth_map}, dpi_{dpi} {
  eye_separation_ = round(2.5 * dpi_);
}

cv::Mat SirdsGenerator::Generate() {
  srand(time(nullptr));
  cv::Mat output(depth_map_.rows, depth_map_.cols, CV_8UC1);

  for (int y = 0; y < depth_map_.rows; ++y) {
    std::unique_ptr<int[]> same = std::make_unique<int[]>(depth_map_.cols);
    std::unique_ptr<uchar[]> pix = std::make_unique<uchar[]>(depth_map_.cols);

    for (int x = 0; x < depth_map_.cols; ++x) {
      same[x] = x;
    }

    for (int x = 0; x < depth_map_.cols; ++x) {
      int s = Separation(depth_map_.at<float>(y, x));
      int left = x - s / 2;
      int right = left + s;

      if (0 <= left && right < depth_map_.cols) {
        bool visible;
        int t = 1;
        float zt;

        do {
          float depth = depth_map_.at<float>(y, x);
          zt = depth + 2 * (2 - mu_ * depth) * t / (mu_ * eye_separation_);
          visible = depth_map_.at<float>(y, x - t) < zt &&
                    depth_map_.at<float>(y, x + t) < zt;
          ++t;
        } while (visible && zt < 1);

        if (visible) {
          int l = same[left];
          while (l != left && l != right) {
            if (l < right) {
              left = l;
              l = same[left];
            } else {
              same[left] = right;
              left = right;
              l = same[left];
              right = l;
            }
          }
          same[left] = right;
        }
      }
    }

    for (int x = depth_map_.cols - 1; x >= 0; --x) {
      if (same[x] == x) {
        pix[x] = rand() > (RAND_MAX / 2) ? 255 : 0;
      } else {
        pix[x] = pix[same[x]];
      }
      output.at<uchar>(y, x) = pix[x];
    }
  }
  return output;
}

double SirdsGenerator::Separation(double depth) const {
  return round((1 - mu_ * depth) * eye_separation_ / (2 - mu_ * depth));
}