#include "interface/config.hpp"

std::vector<Connection> defaultConnections()
{
	return
	{
		// function  input                output              args
		{  control,  "pipe/control_out",  "pipe/control_in"  },
		{  mission,  "pipe/mission_out",  "pipe/mission_in"  },
		{  modeling, "pipe/modeling_out", "pipe/modeling_in" },

		{  camera,   "pipe/camera_f_out", "pipe/camera_f_in", I_FRONT },
		{  camera,   "pipe/camera_d_out", "pipe/camera_d_in", I_DOWN  },
	};
}

Matrix initialModel()
{
	return
	{
		0, 12, -6, 20, -10, 10, 22, -8, 11, 21, -9, 10.5, 29, -15, 22, -26, 23, -26, 26, -26, 0, 0, 0, 0, 0, 0, 0, 0, 42, -25,
	};
}

Matrix initialVariance()
{
	return
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};
}

