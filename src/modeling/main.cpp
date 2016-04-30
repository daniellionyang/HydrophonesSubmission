#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <time.h>

#include "model/system.hpp"

int process(FILE* in, FILE* out)
{
	srand(time(NULL));

	System system;

	bool quit = false;
	while (!quit)
	{
		char c = fgetc(in);
		switch (c)
		{
			case 's': // set
				system = System(in);
				break;
			case 'g': // get
				system.write(out);
				break;
			case 'm': // mode
				system.mode().write(out);
				break;
			case 'e': // evidence
				system.add(Evidence(in));
				break;
			case 'q': // quit
				quit = true;
				break;
		}
	}

	return 0;
};

int main()
{
	return process(stdin, stdout);
}

