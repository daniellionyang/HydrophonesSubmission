#ifndef MISSION_DEFS_HPP
#define MISSION_DEFS_HPP

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

enum
{
	M_ZERO,
	M_GATE_X,      M_GATE_Y,
	M_RBUOY_X,     M_RBUOY_Y,     M_RBUOY_D,
	M_GBUOY_X,     M_GBUOY_Y,     M_GBUOY_D,
	M_YBUOY_X,     M_YBUOY_Y,     M_YBUOY_D,
	M_PVC_X,       M_PVC_Y,
	M_OBIN_X,      M_OBIN_Y,
	M_CBIN_X,      M_CBIN_Y,
	M_TORP_T_D,    M_TORP_B_D,
	M_TORP_L_X,    M_TORP_L_Y,
	M_TORP_R_X,    M_TORP_R_Y,
	M_PINGER_X,    M_PINGER_Y,
	NUM_VARS
};

enum
{
	C_POOL_D,
	C_PVC_D,
	C_OCTAGON_X,   C_OCTAGON_Y,
};

enum
{
	I_FRONT,
	I_DOWN,
	NUM_IMAGES
};

enum
{
	F_BUOYS,
	F_BINS,
	F_TORPS,
	F_PVC,
	F_PINGER,
	F_OCTAGON, // assume pinger is under octagon
	NUM_FLAGS
};

#endif

