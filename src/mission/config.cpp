#include "mission/config.hpp"

std::vector<Goal> defaultGoals()
{
	return
	{
		// v  t  xi yi zi xo yo zo
		{  1000, 200, M_ZERO, M_ZERO, M_ZERO, 0, 0, 0,
			{
				// f     args
				{  wait, 100 },
			},
		},
		{  100, 0, M_GATE_X, M_GATE_X, M_GATE_X, 0, 0, 0,
			gateActions(),
		},
		{  800, 0, M_RBUOY_X, M_RBUOY_Y, M_RBUOY_D, 0, 0, 0,
			buoyActions(),
		},
		{  1400, 0, M_PVC_X, M_PVC_Y, M_ZERO, 0, 0, 0,
			pvcActions(),
		},
		{  2900, 0, M_CBIN_X, M_CBIN_Y, M_ZERO, 0, 0, 0,
			binsActions(),
		},
		{  1000, 0, M_PINGER_X, M_PINGER_Y, M_ZERO, 0, 0, POOL_D,
			pingerActions(),
		},
	};
}

//after each action move up

std::vector<Action> gateActions()
{
	return
	{
		{  moveModelRel, M_GATE_X, M_GATE_Y, M_ZERO, 0, 0, 1, DEFAULTMINDIST },
	};
}

std::vector<Action> buoyActions()
{
	return
	{
		{  moveModelRel, M_RBUOY_X, M_RBUOY_Y, M_RBUOY_D, 0.01, 0, 0, DEFAULTMINDIST },
		{  moveModelRel, M_GBUOY_X, M_GBUOY_Y, M_GBUOY_D, 0.01, 0, 0, DEFAULTMINDIST },
	};
}

std::vector<Action> pvcActions()
{
	return
	{
		{  moveModelRel, M_PVC_X, M_PVC_Y, M_ZERO, 1, 0, 1, DEFAULTMINDIST },
		//move past
		//barrel rolls
	};
}

std::vector<Action> binsActions()
{
	return
	{
		{  moveModelRel, M_CBIN_X, M_CBIN_Y, M_ZERO, 0, 0, 0, DEFAULTMINDIST },
		{  uncoverBin },
		{  dropInBin },
	};
}

std::vector<Action> pingerActions()
{
	return
	{
		{  moveModelRel, M_PINGER_X, M_PINGER_Y, M_ZERO, 0, 0, POOL_D, DEFAULTMINDIST },
	};
}

//torpedo action: remember which one to shoot into in terms of top-left/bottom-right, then shoot in that order regardless
