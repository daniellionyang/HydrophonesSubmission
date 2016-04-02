#include "mission/mission.hpp"

#include <vector>
#include <algorithm>

#include "mission/command.hpp"
#include "mission/query.hpp"
#include "mission/task.hpp"

int mission(FILE* in, FILE* out, FILE* config)
{
	int numTasks = 0;
	fscanf(config, "%i", &numTasks);
	auto tasks = std::vector<Task>();
	for (size_t i = 0; i < numTasks; i++)
		tasks.push_back(Task(in));

	bool quit = false;
	while (!quit)
	{
		// get current state
		Matrix location = getState(in, out);
		Matrix model = model_mode(in, out);

		// select task
		float speed = 1;
		std::sort(tasks.begin(), tasks.end(), [&](const Task& a, const Task& b)
		{
			auto value = [&](const Task& t)
			{
				return t.value() * t.certainty() / (t.time() + (t.location(model) - location).magnitude() / speed);
			};
			return value(a) < value(b); // descending order
		});
		auto task = tasks.back();

		// if close enough, begin task
		auto taskLoc = task.location(model);
		if ((taskLoc - location).magnitude() < 10)
		{
			if (task.run()) tasks.pop_back();
		}
		// otherwise approach task (but continue loop so we can switch later if we want)
		else
			move(out, location, taskLoc);

		if (tasks.empty()) quit = true;
	}

	return 0;
}

