#include "mission/command.hpp"

void move(FILE* out, const Matrix& from, const Matrix& to)
{
	// construct state matrix from position
	Matrix state;
	setState(out, state);
}

void setState(FILE* out, const Matrix& state)
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

