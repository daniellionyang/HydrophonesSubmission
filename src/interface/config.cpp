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

