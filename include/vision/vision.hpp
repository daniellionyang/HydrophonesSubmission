#ifndef VISION_VISION_HPP
#define VISION_VISION_HPP

#include <cv.h>
#include <functional>

float hAngle(const cv::Mat&, float);
float vAngle(const cv::Mat&, float);

cv::Mat generateDiffMap(cv::Mat&, int, bool = false);
cv::Mat filter(const cv::Mat&, std::function<float(float, float, float)>);
cv::Mat scaleIntensity(const cv::Mat&);
int floodFill(const cv::Mat&, std::vector<std::vector<bool> >&, int, int, float);

#endif

