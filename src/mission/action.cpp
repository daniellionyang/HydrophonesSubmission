#include "mission/action.hpp"
#include "mission/command.hpp"
#include "mission/query.hpp"

#include <cmath>

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

MoveTo::MoveTo(int ox, float x, int oy, float y, int oz, float z, float minDistance) :
	xnum(ox), offx(x), ynum(oy), offy(y), znum(oz), offz(z),
	minDistance(minDistance)
{
}

MoveTo::MoveTo(FILE* config)
{
	MoveTo(0,0,0,0,0,0);
	float tempmin;
	fprintf(config, "%f %f %f %f %f %f %f", &xnum, &offx, &ynum, &offy, &znum, &offz, &tempmin);
	if(tempmin > 0){minDistance = tempmin;}
}

bool MoveTo::run(FILE* in, FILE* out)
{
	bool close = false;
	while (!close)
	{
		State state = getState(in, out);
		Matrix location = state.location();

		float dist = move(in, out, location.get(xnum) + offx, location.get(ynum) + offy, location.get(znum) + offz);

		if (dist < minDistance)
			close = true;
	}
	return true;
}

Move::Move(float dsurge, float dstrafe, float ddepth, float minDistance) :
	surge(dsurge), strafe(dstrafe), depth(ddepth), minDistance(minDistance)
{
}

Move::Move(FILE* config)
{
	Move(0,0,0);
	float tempmin;
	fprintf(config, "%f %f %f %f ", &surge, &strafe, &depth, &tempmin);
	if(tempmin > 0){minDistance = tempmin;}
}

void Move::convert(FILE* in, FILE* out)
{
	SubState state = getSubState(in, out); //TODO
	float tx, ty, tz;
	tx = state.x + surge*std::cos(state.yaw) + strafe*std::sin(state.yaw);
	ty = state.y + surge*std::sin(state.yaw) + strafe*std::cos(state.yaw);
	tz = state.depth + depth;
	surge = tx; strafe = ty; depth = tz;
}

bool Move::run(FILE* in, FILE* out)
{
	convert(in, out);
	bool close = false;
	while (!close)
	{
		float dist = move(in, out, surge, strafe, depth);

		if (dist < minDistance)
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
	SubState state = getSubState(in, out); //TODO
	yaw += state.yaw;
	pitch += state.pitch;
	roll += state.roll;
	bool close = false;
	while(!close)
	{
		float error = turn(in, out, yaw, pitch, roll);
		
		if (error < minDistance)
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
	MoveTo(CBINX, 0, CBINY, 0, BINZ, height).run(in, out);
	grab(out);
	Move(10, 0, -height);
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
		return new MoveTo(config);
	default:
		return new Wait(0);
	}
}
