#include "sirds_generator.h"
#include <opencv2/core.hpp>
#include <iostream>

namespace {

double round(double x) {
    return (int)(x + 0.5);
}

double E(int dpi) {
    return round(2.5 * dpi);
}

double mu() {
    return 1 / 3.0;
}

double separation(double z, int dpi) {
    return round((1 - mu() * z) * E(dpi) / (2 - mu() * z));
}

}

using namespace stereogram;

cv::Mat stereogram::generate_sirds(cv::Mat depth_map, int dpi) {
    cv::Mat output(depth_map.rows, depth_map.cols, CV_8UC1, cv::Scalar(0));

    for (int y = 0; y < depth_map.rows; ++y) {
        std::unique_ptr<int[]> same = std::make_unique<int[]>(depth_map.cols);
        std::unique_ptr<uchar[]> pix = std::make_unique<uchar[]>(depth_map.cols);

        for (int x = 0; x < depth_map.cols; ++x) {
            same[x] = x;
        }

        for (int x = 0; x < depth_map.cols; ++x) {
            int s = separation(depth_map.at<float>(y, x), dpi);
            int left = x - s / 2;
            int right = left + s;

            if (0 <= left && right < depth_map.cols) {
                bool visible;
                int t = 1;
                float zt;

                do {
                    float depth = depth_map.at<float>(y, x);
                    zt = depth + 2 * (2 - mu() * depth) * t / (mu() * E(dpi));
                    visible = depth_map.at<float>(y, x - t) < zt && depth_map.at<float>(y, x + t) < zt;
                    ++t;
                }
                while (visible && zt < 1);

                if (visible) {
                    int l = same[left];
                    while (l != left && l != right) {
                        if (l < right) {
                            left = l;
                            l = same[left];
                        }
                        else {
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
        
        for (int x = depth_map.cols - 1; x >= 0; --x) {
            if (same[x] == x) {
                // TODO: better random.
                pix[x] = rand() % 255 > 127 ? 255 : 0;
            }
            else {
                pix[x] = pix[same[x]]; 
            }
            output.at<uchar>(y, x) = pix[x];
        }
    }
    return output;
}
