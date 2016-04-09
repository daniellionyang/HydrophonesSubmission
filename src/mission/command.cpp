#include "mission/command.hpp"

#include <cmath>

#include "common/state.hpp"

void move(FILE* out, const Matrix& from, const Matrix& to)
{
	Matrix dist = to - from;
	Matrix direction;
	direction.set(0, std::atan2(dist.get(1), dist.get(0)));
	direction.set(1, 0);
	direction.set(2, 0);

	setState(out, State(to, direction));
}

void setState(FILE* out, const State& state)
{
	fprintf(out, "c s\n");
	state.write(out);
}

void shoot(FILE* out, char side)
{
	fprintf(out, "c t %c\n", side);
}

void drop(FILE* out)
{
	fprintf(out, "c d\n");
}

void grab(FILE* out)
{
	fprintf(out, "c g g\n");
}

void release(FILE* out)
{
	fprintf(out, "c g r\n");
}

