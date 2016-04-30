#include "mission/action.hpp"

#include "mission/command.hpp"
#include "mission/query.hpp"

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

