#ifndef MISSION_COMMAND_HPP
#define MISSION_COMMAND_HPP

#include "common/matrix.hpp"
#include "common/state.hpp"

float move(FILE*, FILE*, float, float, float); // wrapper for state
float turn(FILE*, FILE*, float, float, float);
void setState(FILE*, const SubState&);
void shoot(FILE*, char);
void drop(FILE*);
void grab(FILE*);
void release(FILE*);

#endif

