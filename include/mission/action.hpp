#ifndef MISSION_ACTION_HPP
#define MISSION_ACTION_HPP

#include <time.h>

#include "common/matrix.hpp"

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

class MoveTo : public virtual Action
{
public:
	MoveTo(int, float, int, float, int, float, float = DEFAULTMINDIST);
	MoveTo(FILE*);

	virtual bool run(FILE*, FILE*);

private:
	int xnum, ynum, znum;
	float offx, offy, offz;
	float minDistance;
};

class Move : public virtual Action
{
public:
	Move(float, float, float, float = DEFAULTMINDIST);
	Move(FILE*);
	
	virtual bool run(FILE*, FILE*);

private:
	void convert(FILE*, FILE*);
	
	float surge, strafe, depth;
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
	OpenBin();
	
	virtual bool run(FILE*, FILE*);
};

class DropDat : public virtual Action
{
public:
	
};

Action* getaction(FILE*);

#endif

