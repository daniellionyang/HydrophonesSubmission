#ifndef MISSION_ACTION_HPP
#define MISSION_ACTION_HPP

#include <time.h>

#include "common/matrix.hpp"
#include "common/state.hpp"

#define DEFAULTMINDIST 5

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

class Move : public virtual Action
{
public:
	Move(FILE* config);
	Move(const State&, float);
	
	virtual bool run(FILE*, FILE*);

private:
	State target;
	float surge, strafe, depth;
	float minDistance;
};

class MoveTo : public virtual Action
{
public:
	MoveTo(FILE* config);
	MoveTo(const State&, float);
	
	virtual bool run(FILE*, FILE*);
	
private:
	State target;
	float minDistance;
};

class Turn : public virtual Action
{
public:
	Turn(float, float, float, float = DEFAULTMINDIST);
	Turn(FILE*);
	
	virtual bool run(FILE*, FILE*);

private:
	float yaw, pitch, roll;
	float minDistance;
};

class OpenBin : public virtual Action
{
public:
	OpenBin(float);
	
	virtual bool run(FILE*, FILE*);

private:
	float height;
};

class DropDat : public virtual Action
{
public:
	DropDat();
	
	virtual bool run(FILE*, FILE*);
	
};

Action* getaction(FILE*);

#endif

