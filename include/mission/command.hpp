#ifndef MISSION_COMMAND_HPP
#define MISSION_COMMAND_HPP

#include "common/matrix.hpp"
#include "common/state.hpp"

void stop(FILE*, FILE*);
void move(FILE*, const State&, const State&); // wrapper for state
void setState(FILE*, const State&);
void shoot(FILE*, char);
void drop(FILE*);
void grab(FILE*); // TODO add support for both front and down grabber
void release(FILE*);
void setFlag(FILE*, size_t, float);
void addVariance(FILE*, size_t, float);
void maxThrust(FILE*, float);
void speed(FILE*, float);

#endif

