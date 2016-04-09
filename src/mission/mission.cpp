#include "mission/mission.hpp"

#include <vector>
#include <algorithm>

#include "mission/command.hpp"
#include "mission/query.hpp"
#include "mission/goal.hpp"

int mission(FILE* in, FILE* out, FILE* config)
{
	int numGoals = 0;
	fscanf(config, "%i", &numGoals);
	if(numGoals < 1) return 0;
	auto goals = std::vector<Goal*>();
	for (size_t i = 0; i < numGoals; i++)
		goals.push_back(new Goal(config));

	bool quit = false;
	while (!quit)
	{
		// get current state
		State state = getState(in, out);
		Matrix location = state.location();
		Matrix model = model_mode(in, out);

		// select goal
		float speed = 1;
		std::sort(goals.begin(), goals.end(), [&](const Goal* a, const Goal* b)
		{
			auto value = [&](const Goal* t)
			{
				return t->value() * t->certainty() / (t->time() + (t->location(model) - location).magnitude() / speed);
			};
			return value(a) < value(b); // descending order
		});
		auto goal = *goals.back();

		// if close enough, begin goal
		auto goalLoc = goal.location(model);
		if ((goalLoc - location).magnitude() < 10)
		{
			if (goal.run(in, out)) goals.pop_back();
			else goal.failed();
		}
		// otherwise approach goal (but continue loop so we can switch later if we want)
		else
			move(out, location, goalLoc);

		if (goals.empty()) quit = true;
	}

	return 0;
}

