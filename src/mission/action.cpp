#include "mission/action.hpp"
#include "mission/command.hpp"
#include "mission/query.hpp"

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

Action* getaction(FILE* config)
{
	int tnum;
	fscanf(config, "%i", &tnum);
	switch(tnum)
	{
	default:
		return new Wait(0);
	}
}
