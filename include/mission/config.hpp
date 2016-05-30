#ifndef MISSION_CONFIG_HPP
#define MISSION_CONFIG_HPP

#include "common/defs.hpp"
#include "mission/goal.hpp"
#include "mission/action.hpp"

#define DEFAULTMINDIST 0.5

std::vector<Goal> defaultGoals();

std::vector<Action> gateActions();
std::vector<Action> buoyActions();
std::vector<Action> pvcActions();
std::vector<Action> binsActions();
std::vector<Action> pingerActions();
std::vector<Action> torpedoActions();

#endif

