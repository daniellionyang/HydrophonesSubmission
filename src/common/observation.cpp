#include "common/observation.hpp"

Observation::Observation(int x_idx, int y_idx, int d_idx, float theta, float phi, float rho) :
	x_idx(x_idx),
	y_idx(y_idx),
	d_idx(d_idx),
	theta(theta),
	phi(phi),
	rho(rho)
{
}

Observation::Observation(FILE* in)
{
	fscanf(in, " %i %i %i %f %f %f",
		&x_idx, &y_idx, &d_idx,
		&theta, &phi,   &rho
	);
}

size_t Observation::write(FILE* out)
{
	size_t bytes = fprintf(out, "%i %i %i %f %f %f\n",
		x_idx, y_idx, d_idx,
		theta, phi,   rho
	);
	fflush(out);
	return bytes;
}

