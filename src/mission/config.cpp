#include "mission/config.hpp"

#include "common/config.hpp"

const std::vector<Goal> initialGoals =
{
	// v       t  xi      yi      zi      xo yo zo mindist  actions
	{  100000, 0, M_ZERO, M_ZERO, M_ZERO, 0, 0, 1, 400,     {
		{ setMaxThrust, 1.f },
		{ setSpeed, .1f },

		// gate
		{ lprintf, "gate\n" },
		{ setSpeed, .1f },
		{ moveAbsolute, State(0, 0, 1, 0, 0, 0), .2 },
		{ setSpeed, .8f },
		{ moveModel, M_GATE_X, M_GATE_Y, M_ZERO, 0, 0, 1, 1 },
		{ moveDir, State(3.5, 0, 0, 0, 0, 0), 1 },

		{ flag, F_BUOYS, 1 },

		// red buoy
		{ lprintf, "rbuoy\n" },
		{ setSpeed, .2f },
		{ moveModel, M_RBUOY_X, M_RBUOY_Y, M_RBUOY_D, 0, 0, 0, 1 },
		{ flag, F_BUOYS, 0 },
		{ moveDir, State(2, 0, 0, 0, 0, 0), 1 },
		{ moveDir, State(-3, 0, 0, 0, 0, 0), 1 },
		{ flag, F_BUOYS, 1 },

		// green buoy
		{ lprintf, "gbuoy\n" },
		{ moveModel, M_GBUOY_X, M_GBUOY_Y, M_GBUOY_D, 0, 0, 0, 1 },
		{ flag, F_BUOYS, 0 },
		{ moveDir, State(2, 0, 0, 0, 0, 0), 1 },
		{ moveDir, State(-3, 0, 0, 0, 0, 0), 1 },
		{ flag, F_BUOYS, 1 },

		// yellow buoy
		{ lprintf, "ybuoy\n" },
		{ moveModel, M_YBUOY_X, M_YBUOY_Y, M_YBUOY_D, 0, 0, 0, 1 },
		{ flag, F_BUOYS, 0 },
		{ moveDir, State(1, 0, -.5, 0, 0, 0), .1 },
		{ moveDir, State(0, 0, 1.2, 0, 0, 0), .1 },
		{ moveExt, 0, 3, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1 },

		{ flag, F_PINGER, 1 }, // activate pinger early
		{ flag, F_PVC, 1 },

		// pvc
		{ lprintf, "pvc\n" },
		{ setSpeed, .5f },
		{ wait, 3 },
		{ turnTo, M_PVC_X, M_PVC_Y },
		{ moveExt, 0, 0, M_PVC_X, 0, 0, 0, M_PVC_Y, 0, 2.3, 0, 0, 0, 0, 1, 0, 0, .1 },
		{ setSpeed, .1f },
		{ moveDir, State(5, 0, 0, 0, 0, 2), 1 }, // barrel roll
		{ setSpeed, .3f },
		{ moveDir, State(3, 0, 0, 0, 0, 0), 1 },

		{ flag, F_PVC, 0 },

		// pinger
		{ lprintf, "pinger\n" },
		{ moveModel, M_PINGER_X, M_PINGER_Y, M_ZERO, 0, 0, 3, 1 },
	}},

	{  1, 0, M_CBIN_X, M_CBIN_Y, M_ZERO, 0, 0, 1, 400, {
		{ setSpeed, .1f },
		{ moveModel, M_PINGER_X, M_PINGER_Y, M_ZERO, 0, 0, 3, 1 }, // approach area

		{ flag, F_PINGER, 0 },
		{ flag, F_BINS, 1 },

		// droppers
		{ lprintf, "dropper\n" },
		{ setSpeed, .1f },
		{ moveModel, M_PINGER_X, M_PINGER_Y, M_ZERO, 0, 0, 1, 2 }, // look around
		{ variance, M_CBIN_X, 4 },
		{ variance, M_CBIN_Y, 4 },
		{ wait, 3 },
		{ moveExt, 0, 0, M_CBIN_X, 0, 0, 0, M_CBIN_Y, 0, 3, 0, 0, 0, 0, 1, 0, 0, .1 },
		{ variance, M_CBIN_X, 4 },
		{ variance, M_CBIN_Y, 4 },
		{ wait, 3 },
		{ moveExt, 0, 0, M_CBIN_X, 0, 0, 0, M_CBIN_Y, 0, 4, 0, 0, 0, 0, 1, 0, 0, .03 },
		{ flag, F_BINS, 0 },
		{ uncoverBin },
		{ moveExt, 0, 0, M_CBIN_X, 0, 0, 0, M_CBIN_Y, 0, 3, 0, 0, 0, 0, 1, 0, 0, .1 },
		{ dropInBin },
		{ wait, 1 },
		{ dropInBin },
		{ wait, 1 },

		{ variance, M_PINGER_X, 400 },
		{ variance, M_PINGER_Y, 400 },
		{ flag, F_PINGER, 1 },

		{ flag, F_TORPS, 1 },

		// torpedoes
		{ lprintf, "torpedoes\n" },
		{ moveDir, State(0, 0, 0, 0, 0, 0), .1 }, // scan
		{ wait, .3 },
		{ moveDir, State(0, 0, 0, .25, 0, 0), .1 },
		{ wait, .3 },
		{ moveDir, State(0, 0, 0, .5, 0, 0), .1 },
		{ wait, .3 },
		{ moveDir, State(0, 0, 0, .75, 0, 0), .1 },
		{ wait, .3 },
		{ moveModel, M_TORP_X, M_TORP_Y, M_TORP_D, 0, 0, 0, 2 }, // approach
		{ moveToHole, M_TORP_X, M_TORP_Y, M_TORP_D, 1, .1 },
		{ wait, 3 },
		{ moveToHole, M_TORP_X, M_TORP_Y, M_TORP_D, .3, .1 },
		{ moveDir, State(.4, 0, 0, 0, 0, 0), .1 }, // remove cover
		{ moveDir, State(0, .3, 0, 0, 0, 0), .1 },
		{ wait, 3 },
		{ moveDir, State(0, -.3, 0, 0, 0, 0), .1 },
		{ shootInHole, 'r' },
		{ wait, 3 },
		{ shootInHole, 'l' },
		{ wait, 3 },

		{ flag, F_TORPS, 0 },
		{ wait, 10 },
	}},

	{  1, 0, M_ZERO, M_ZERO, M_ZERO, constants.get(C_OCTAGON_X), constants.get(C_OCTAGON_Y), 3, 400, {
		// octagon
		{ lprintf, "octagon\n" },
		{ setSpeed, .5f },
		{ moveModel, M_PINGER_X, M_PINGER_Y, M_ZERO, 0, 0, 3, .1 },
		{ setSpeed, .1f },
		{ moveModel, M_PINGER_X, M_PINGER_Y, M_ZERO, 0, 0, -10, 20 },
		{ wait, 10 },
		{ moveDir, State(0, 0, 3, 0, 0, 0), 1 },
		{ variance, M_PINGER_X, 400 },
		{ variance, M_PINGER_Y, 400 },
		{ wait, 10 },
	}},
};

