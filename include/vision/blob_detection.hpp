//based on "A linear-time component-labeling algorithm using contour tracing technique" by Chang, et al.

#ifndef VISION_BLOB_DETECTION_H
#define VISION_BLOB_DETECTION_H

#include <cv.h>
#include <vector>

#include "vision/blob.hpp"

// detects gray blobs on black background
std::vector<Blob> blob_detection(const cv::Mat&);

#endif
