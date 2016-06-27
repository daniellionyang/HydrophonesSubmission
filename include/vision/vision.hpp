#ifndef VISION_VISION_HPP
#define VISION_VISION_HPP

#include <functional>

#include <opencv2/core/core.hpp>

cv::Mat generateDiffMap(cv::Mat&, int, bool = false);

cv::Mat colorize(cv::Mat&, std::function<float(int, int, int)>);

cv::Mat scaleIntensity(const cv::Mat&);

#endif

