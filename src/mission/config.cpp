#include "mission/config.hpp"

#include "common/config.hpp"

const std::vector<Goal> initialGoals =
{
	// v       t  xi      yi      zi      xo yo zo mindist  actions
	{  100000, 0, M_ZERO, M_ZERO, M_ZERO, 0, 0, 1, 400,     {
		// gate
		{ lprintf, "gate\n" },
		{ moveModel, M_GATE_X, M_GATE_Y, M_ZERO, 0, 0, 1, 1 },
		{ moveDir, State(3.5, 0, 0, 0, 0, 0), 1 },

		{ flag, F_BUOYS, 1 },

		// red buoy
		{ lprintf, "rbuoy\n" },
		{ moveModel, M_RBUOY_X, M_RBUOY_Y, M_RBUOY_D, 0, 0, 0, 1 },
		{ flag, F_BUOYS, 0 },
		{ moveDir, State(2, 0, 0, 0, 0, 0), 1 },
		{ moveDir, State(-4, 0, 0, 0, 0, 0), 1 },
		{ flag, F_BUOYS, 1 },

		// green buoy
		{ lprintf, "gbuoy\n" },
		{ moveModel, M_GBUOY_X, M_GBUOY_Y, M_GBUOY_D, 0, 0, 0, 1 },
		{ flag, F_BUOYS, 0 },
		{ moveDir, State(2, 0, 0, 0, 0, 0), 1 },
		{ moveDir, State(-4, 0, 0, 0, 0, 0), 1 },
		{ flag, F_BUOYS, 1 },

		// yellow buoy
		{ lprintf, "ybuoy\n" },
		{ moveModel, M_YBUOY_X, M_YBUOY_Y, M_YBUOY_D, 0, 0, 0, 1 },
		{ flag, F_BUOYS, 0 },
		{ moveDir, State(2, 0, -.5, 0, 0, 0), 1 },
		{ moveDir, State(0, 0, .8, 0, 0, 0), 1 },
		{ moveDir, State(2, 1, 0, 0, 0, 0), 1 },

		{ flag, F_PINGER, 1 }, // activate pinger early
		{ flag, F_PVC, 1 },

		// pvc
		{ lprintf, "pvc\n" },
		{ moveModel, M_PVC_X, M_PVC_Y, M_ZERO, 0, 0, 2.3, 2 },
		{ moveDir, State(5, 0, 0, 0, 0, 2), 1 }, // barrel roll
		{ moveDir, State(3, 0, 0, 0, 0, 0), 1 },

		{ flag, F_PVC, 0 },

		// pinger
		{ lprintf, "pinger\n" },
		{ moveModel, M_PINGER_X, M_PINGER_Y, M_ZERO, 0, 0, 3, 1 },
	}},

	{  1, 0, M_CBIN_X, M_CBIN_Y, M_ZERO, 0, 0, 1, 400, {
		{ moveModel, M_PINGER_X, M_PINGER_Y, M_ZERO, 0, 0, 3, 1 }, // approach area

		{ flag, F_PINGER, 0 },
		{ flag, F_BINS, 1 },

		// droppers
		{ lprintf, "dropper\n" },
		{ moveModel, M_PINGER_X, M_PINGER_Y, M_ZERO, 0, 0, 1, 1 }, // look around
		{ wait, 3 },
		{ variance, M_CBIN_X, 4 },
		{ variance, M_CBIN_Y, 4 },
		{ wait, 3 },
		{ moveModel, M_CBIN_X, M_CBIN_Y, M_ZERO, 0, 0, 4, .1 },
		{ variance, M_CBIN_X, 4 },
		{ variance, M_CBIN_Y, 4 },
		{ wait, 3 },
		{ moveModel, M_CBIN_X, M_CBIN_Y, M_ZERO, 0, 0, 4, .03 },
		{ flag, F_BINS, 0 },
		{ uncoverBin },
		{ moveModel, M_CBIN_X, M_CBIN_Y, M_ZERO, 0, 0, 3, .1 },
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
		{ moveModel, M_TORP_R_X, M_TORP_R_Y, M_TORP_B_D, 0, 0, 0, 2 }, // approach
		{ moveToHole, M_TORP_R_X, M_TORP_R_Y, M_TORP_B_D, 1, .1 },
		{ wait, 3 },
		{ moveToHole, M_TORP_R_X, M_TORP_R_Y, M_TORP_B_D, .5, .1 },
		{ moveDir, State(.3, 0, 0, 0, 0, 0), .1 }, // remove cover
		{ moveDir, State(0, .5, 0, 0, 0, 0), .1 },
		{ moveToHole, M_TORP_L_X, M_TORP_L_Y, M_TORP_T_D, 1, .1 },
		{ wait, 3 },
		{ moveToHole, M_TORP_L_X, M_TORP_L_Y, M_TORP_T_D, .5, .1 },
		{ shootInHole, 'r' },
		{ wait, 3 },
		{ moveToHole, M_TORP_R_X, M_TORP_R_Y, M_TORP_B_D, 1, .1 },
		{ wait, 3 },
		{ moveToHole, M_TORP_R_X, M_TORP_R_Y, M_TORP_B_D, .5, .1 },
		{ shootInHole, 'l' },
		{ wait, 3 },

		{ flag, F_TORPS, 0 },
		{ wait, 10 },
	}},

	{  1, 0, M_ZERO, M_ZERO, M_ZERO, constants.get(C_OCTAGON_X), constants.get(C_OCTAGON_Y), 3, 400, {
		// octagon
		{ lprintf, "octagon\n" },
		{ moveModel, M_PINGER_X, M_PINGER_Y, M_ZERO, 0, 0, 3, .1 },
		{ moveModel, M_PINGER_X, M_PINGER_Y, M_ZERO, 0, 0, -10, .1 },
		{ moveDir, State(0, 0, 3, 0, 0, 0), 1 },
		{ variance, M_PINGER_X, 400 },
		{ variance, M_PINGER_Y, 400 },
		{ wait, 10 },
	}},
};

