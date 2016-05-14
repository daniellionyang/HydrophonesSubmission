#include <cstdio>

#include "mission/mission.hpp"

int main(int argc, char** argv)
{
	FILE* in = stdin;
	FILE* out = stdout;
	FILE* config;

	if (argc < 2) config = fopen("config/tasks.conf", "r");
	else config = fopen(argv[1], "r");
	if (!config)
	{
		fprintf(stderr, "error: unable to open config file\n");
		return 1;
	}

	if (argc >= 4)
	{
		in = fopen(argv[2], "r");
		out = fopen(argv[3], "r");
	}
	return mission(in, out, config);
}

