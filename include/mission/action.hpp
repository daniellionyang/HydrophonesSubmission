#ifndef MISSION_ACTION_HPP
#define MISSION_ACTION_HPP

#include "common/matrix.hpp"

class Action
{
public:
	virtual bool run(FILE*, FILE*) = 0;
};

class MoveTo : public virtual Action
{
public:
	MoveTo(const Matrix&, float);

	virtual bool run(FILE*, FILE*);

private:
	Matrix target;
	float minDistance;
};

#endif

