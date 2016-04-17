#ifndef MISSION_ACTION_HPP
#define MISSION_ACTION_HPP

#include <time.h>

#include "common/matrix.hpp"

class Action
{
public:
	virtual bool run(FILE*, FILE*) = 0;
};

class Wait : public virtual Action
{
public:
	Wait(long long);
	
	virtual bool run(FILE*, FILE*);

private:
	clock_t start;
	long long wtime;
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

class DoBins : public virtual Action
{
public:
	DoBins();
	
	virtual bool run(FILE*, FILE*);

private:
	void PosBin(const Matrix&);
};

Action* getaction(FILE*);

#endif

