#ifndef INTERFACE_FUNCTIONS_HPP
#define INTERFACE_FUNCTIONS_HPP

#include "interface/data.hpp"

bool camera_f(FILE*, FILE*, Data*);
bool camera_d(FILE*, FILE*, Data*);

bool mission(FILE*, FILE*, Data*);
bool modeling(FILE*, FILE*, Data*);
bool control(FILE*, FILE*, Data*);

#endif

