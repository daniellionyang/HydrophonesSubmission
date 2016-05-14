#include "mission/config.hpp"

std::vector<Goal> defaultGoals()
{
	return
	{
		// v  t  xi yi zi xo yo zo
		{  1, 1, 0, 0, 0, 0, 0, 0,
			{
				// f     args
				{  wait, 10 },
			},
		},
	};
}

