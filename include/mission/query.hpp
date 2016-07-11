#ifndef MISSION_QUERY_HPP
#define MISSION_QUERY_HPP

#include <cstdio>

#include "common/matrix.hpp"
#include "common/state.hpp"
#include "model/system.hpp"
#include "image/image.hpp"

State getState(FILE*, FILE*);

cv::Mat image(FILE*, FILE*, char, float res = 1, float hcrop = 1, float vcrop = 1);

Matrix getModel(FILE*, FILE*);
System getSystem(FILE*, FILE*);
float getCertainty(FILE*, FILE*);

float getFlag(FILE*, FILE*, size_t);

bool alive(FILE*, FILE*);

#endif

