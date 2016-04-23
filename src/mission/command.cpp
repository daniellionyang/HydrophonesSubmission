#include "mission/command.hpp"

#include <cmath>

#include "common/state.hpp"
#include "mission/query.hpp"

float move(FILE* in, FILE* out, float tx, float ty, float tdepth)
{
	SubState state = getSubState(in, out);
	float dx, dy, ddepth;
	dx = tx - state.x;
	dy = ty - state.y;
	ddepth = tdepth - state.depth;
	
	float tyaw = std::atan2(dy, dx);

	setState(out, SubState(tx, ty, tdepth, tyaw, 0, 0));
	return(std::sqrt(dx*dx + dy*dy + ddepth*ddepth));
}

void setState(FILE* out, const SubState& state)
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

