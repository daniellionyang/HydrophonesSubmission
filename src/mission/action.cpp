#include "mission/action.hpp"
#include "mission/command.hpp"
#include "mission/query.hpp"

Wait::Wait(long long time) :
	wtime(time)
{
}

bool Wait::run(FILE* in, FILE* out)
{
	start = clock();
	while((clock()-start) < wtime)
	{
		continue;
	}
}

MoveTo::MoveTo(const State& target, float minDistance) :
	target(target),
	minDistance(minDistance)
{
}

bool MoveTo::run(FILE* in, FILE* out)
{
	bool close = false;
	while (!close)
	{
		State state = getState(in, out);

		move(out, state, target);

		if (state.distanceTo(target) < minDistance)
			close = true;
	}
	return true;
}

Move::Move(const State& target, float minDistance) :
	target(target),
	minDistance(minDistance)
{
}

bool Move::run(FILE* in, FILE* out)
{
	bool close = false;
	while (!close)
	{
		close = true;
	}
	return true;
}

Turn::Turn(float dyaw, float dpitch, float droll, float minDistance) :
	yaw(dyaw), pitch(dpitch), roll(droll),
	minDistance(minDistance)
{
}

bool Turn::run(FILE* in, FILE* out)
{
	bool close = false;
	while(!close)
	{
		close = true;
	}
	return true;
}

OpenBin::OpenBin(float height) :
	height(height)
{
}

bool OpenBin::run(FILE* in, FILE* out)
{
	//MoveTo(CBINX, 0, CBINY, 0, BINZ, height).run(in, out);
	grab(out);
	//Move(10, 0, -height);
	grab(out);
	return true;
}

DropDat::DropDat()
{
}

bool DropDat::run(FILE* in, FILE* out)
{
	drop(out);
	return true;
}

Matrix gettarget(char obj)
{
	return Matrix();
}

Action* getaction(FILE* config)
{
	int tnum;
	fscanf(config, "%i", &tnum);
	switch(tnum)
	{
	case 0:
		//return new MoveTo(config);
	default:
		return new Wait(0);
	}
}
