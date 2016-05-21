#include "interface/config.hpp"

std::vector<Connection> defaultConnections()
{
	return
	{
		// function  input                output
		{  control,  "pipe/control_out",  "pipe/control_in"  },
		{  mission,  "pipe/mission_out",  "pipe/mission_in"  },
		{  modeling, "pipe/modeling_out", "pipe/modeling_in" },
	};
}

