#include <cstdio>
#include <cmath>
#include <cstdint>

#include "common/defs.hpp"
#include "common/config.hpp"
#include "common/observation.hpp"

const size_t num_inputs = 4;

struct Triangle
{
	size_t base;
	size_t leg1;
	size_t leg2;

	float dist1;
	float dist2;

	float angle;
};

Triangle horizontal =
{
	0,
	1,
	2,

	1.f,
	1.f,

	.0f,
};

Triangle vertical =
{
	0,
	2,
	3,

	1.f,
	1.f,

	.0f,
};

int main()
{
	FILE* in = stdin;
	FILE* out = stdout;

	bool quit = false;
	while (!quit)
	{
		// each packet preceded by -2^15
		// ignore 0xFF aligning bytes before header
		int c = fgetc(in);
		if (c == 0x00)
		{
			int c = fgetc(in);
			if (c == 0x80)
			{
				bool bad = false;

				// time between input i and input 0
				// don't read any bytes for toa 0 because it is always 0
				int toa[num_inputs] = {0};
				for (size_t i = 1; i < num_inputs; i++)
				{
					// read data
					int l = fgetc(in);
					int h = fgetc(in);

					// detect eof
					if (l == -1 || h == -1) bad = true;

					// convert to int
					toa[i] = [](int l, int h)
					{
						uint16_t v = static_cast<uint16_t>(l);
						v |= static_cast<uint16_t>(h << 8);
						return (v & (1U << 15))     ?
							-static_cast<int>(-v) :
							static_cast<int>(v)   ;
					}(l, h);
				}

				// time between input i and input j
				int tdoa[num_inputs][num_inputs];
				for (size_t i = 0; i < num_inputs; i++)
				{
					for (size_t j = 0; j < num_inputs; j++)
					{
						tdoa[i][j] = toa[i] - toa[j];

						if (std::abs(tdoa[i][j]) > 333) bad = true;
					}
				}

				if (bad) continue;

				// compute angles
				auto computeAngle = [&](Triangle t)
				{
					return static_cast<float>(std::atan2(
						- t.leg1  * t.dist2,
						- t.dist1 * t.leg2
					));
				};
				float theta = computeAngle(horizontal);
				float phi   = computeAngle(vertical);

				if (
					theta > -.5f &&
					theta <  .5f &&
					phi   >  .0f &&
					phi   <  .5f &&

					!bad &&

					true
				)
					Observation(
					{
						M_PINGER_X,
						M_PINGER_Y,
						-1,
						theta,
						phi,
						constants.get(C_POOL_D),
					}).write(out);
			}
		}
	}

	return 0;
}

