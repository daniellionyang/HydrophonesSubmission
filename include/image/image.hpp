#ifndef IMAGE_IMAGE_HPP
#define IMAGE_IMAGE_HPP

#include <cv.h>
#include <cstdio>

cv::Mat imageRead(FILE*);
void imageWrite(FILE*, const cv::Mat&);

#endif

