#include "mission/action.hpp"
#include "mission/command.hpp"
#include "mission/query.hpp"

#include <cmath>

/*
struct Model
{
	Model(Matrix vec)
	{
		rBuoy[0] = vec.get(0);
		rBuoy[1] = vec.get(1);
		rBuoy[2] = vec.get(2);
		gBuoy[0] = vec.get(3);
		gBuoy[1] = vec.get(4);
		gBuoy[2] = vec.get(5);
		yBuoy[0] = vec.get(6);
		yBuoy[1] = vec.get(7);
		yBuoy[2] = vec.get(8);

		pvc[0] = vec.get(9);
		pvc[1] = vec.get(10);
		pvc[2] = vec.get(11);

		board[0] = vec.get(12);
		board[1] = vec.get(13);
		board[2] = vec.get(14);

		coveredBin[0] = vec.get(15);
		coveredBin[1] = vec.get(16);
		openBin[0] = vec.get(17);
		openBin[1] = vec.get(18);

		pinger[0] = vec.get(19);
		pinger[1] = vec.get(20);
	}

	std::array<float, 3>
		rBuoy, gBuoy, yBuoy,
		pvc, // maneuvering
		board; // torpedoes
	std::array<float, 2>
		coveredBin, openBin,
		pinger;
};
*/

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
		int x, y, z;
		float ox, oy, oz, min;
		fscanf(config, "%i %f %i %f %i %f %f", &x, &ox, &y, &oy, &z, &oz, &min);
		return (min > 0) ? new MoveTo(z, ox, y, oy, z, oz, min) : new MoveTo(z, ox, y, oy, z, oz);
	default:
		return new Wait(0);
	}
}
