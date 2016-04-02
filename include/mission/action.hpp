#ifndef MISSION_ACTION_HPP
#define MISSION_ACTION_HPP

#include <functional>
#include <cstdio>

std::function<bool(FILE*, FILE*)> getaction(FILE*);

#endif

