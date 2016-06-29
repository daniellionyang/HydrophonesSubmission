#ifndef COMMON_OBSERVATION_HPP
#define COMMON_OBSERVATION_HPP

#include <cstdio>

struct Observation
{
	Observation(int, int, int, float, float, float);
	Observation(FILE*);
	size_t write(FILE*);

	int x_idx;
	int y_idx;
	int d_idx;
	float theta;
	float phi;
	float rho;
};

#endif

