#include "mission/command.hpp"

#include <cmath>

#include "common/state.hpp"
#include "mission/query.hpp"

void stop(FILE* in, FILE* out)
{
	setState(out, getState(in, out));
}

void move(FILE* out, const State& from, const State& to)
{
	auto dx = to.x() - from.x();
	auto dy = to.y() - from.y();

	setState(out, State(to.x(), to.y(), to.depth(), std::atan2(dy, dx) / (2 * M_PI), 0, 0));
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

void setFlag(FILE* out, size_t idx, float value)
{
	fprintf(out, "c f %z %f\n", idx, value);
}

void addVariance(FILE* out, size_t idx, float value)
{
	fprintf(out, "c v %z %f\n", idx, value);
}

