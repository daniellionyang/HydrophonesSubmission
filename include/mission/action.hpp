#ifndef MISSION_ACTION_HPP
#define MISSION_ACTION_HPP

#include "common/state.hpp"

class Action
{
public:
	virtual bool run(FILE*, FILE*) = 0;
};

class MoveTo : public virtual Action
{
public:
	MoveTo(const State&, float);

	virtual bool run(FILE*, FILE*);

private:
	State target;
	float minDistance;
};

#endif

