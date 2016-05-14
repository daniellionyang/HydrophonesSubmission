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
		{  1, 1, M_GATE_X, M_GATE_Y, 0, 0, 0, 100,
				gateActions(100),
		},
	};
}

std::vector<Action> gateActions(float height)
{
	return
	{
		{  moveModelRel, M_GATE_X, M_GATE_Y, 0, 10, 0, height, DEFAULTMINDIST }
	};
}

std::vector<Action> buoyActions()
{
	return
	{
		{  moveModelRel, M_RBUOY_X, M_RBUOY_Y, M_RBUOY_D, 0.5, 0, 0, DEFAULTMINDIST },
		{  moveModelRel, M_GBUOY_X, M_GBUOY_Y, M_GBUOY_D, 0.5, 0, 0, DEFAULTMINDIST }
	};
}

std::vector<Action> lgateActions(float height)
{
	return
	{
		{  moveModelRel, M_PVC_X, M_PVC_Y, 0, 10, 0, height, DEFAULTMINDIST }
	};
}

std::vector<Action> binsActions(float height)
{
	return
	{
		{  moveModelRel, M_CBIN_X, M_CBIN_Y, 0, 0, 0, height, DEFAULTMINDIST },
		{  uncoverBin },
		{  dropInBin }
	};
}
