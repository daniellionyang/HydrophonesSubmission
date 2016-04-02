#ifndef MISSION_COMMAND_HPP
#define MISSION_COMMAND_HPP

#include "common/matrix.hpp"
#include "common/state.hpp"

void move(FILE*, const Matrix&, const Matrix&); // wrapper for state
void setState(FILE*, const State&);
void shoot(FILE*, char);
void drop(FILE*);
void grab(FILE*);
void release(FILE*);

#endif

