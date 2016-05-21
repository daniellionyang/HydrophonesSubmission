#ifndef MISSION_CONFIG_HPP
#define MISSION_CONFIG_HPP

#include "common/defs.hpp"
#include "mission/goal.hpp"
#include "mission/action.hpp"

#define DEFAULTMINDIST 5

std::vector<Goal> defaultGoals();

std::vector<Action> gateActions(float);
std::vector<Action> buoyActions();
std::vector<Action> lgateActions(float);
std::vector<Action> binsActions(float);
std::vector<Action> pingerActions();
std::vector<Action> hydrophoneActions();

#endif

