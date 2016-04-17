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

MoveTo::MoveTo(const Matrix& target, float minDistance) :
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
		Matrix location = state.location();

		move(out, location, target);

		if ((target - location).magnitude() < minDistance)
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
		char t; float m;
		fscanf(config, "%c %f", &t, &m);
		return new MoveTo(gettarget(t), m);
	default:
		return new Wait(0);
	}
}
