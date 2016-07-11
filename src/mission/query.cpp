#include "mission/query.hpp"

State getState(FILE* in, FILE* out)
{
	fprintf(out, "q s\n");
	fflush(out);
	return State(in);
}

cv::Mat image(FILE* in, FILE* out, char dir, float res, float hcrop, float vcrop)
{
	fprintf(out, "q i %c %f %f %f\n", dir, res, hcrop, vcrop);
	fflush(out);
	return imageRead(in);
}

Matrix getModel(FILE* in, FILE* out)
{
	fprintf(out, "q m m\n");
	fflush(out);
	return Matrix(in);
}

System getSystem(FILE* in, FILE* out)
{
	fprintf(out, "q m s\n");
	fflush(out);
	return System(in);
}

float getCertainty(FILE* in, FILE* out)
{
	fprintf(out, "q m c\n");
	fflush(out);
	float certainty;
	fscanf(in, " %f", &certainty);
	return certainty;
}

float getFlag(FILE* in, FILE* out, size_t idx)
{
	fprintf(out, "q f %zu\n", idx);
	fflush(out);
	float value;
	fscanf(in, " %f", &value);
	return value;
}

bool alive(FILE* in, FILE* out)
{
	fprintf(out, "q a\n");
	fflush(out);
	int value;
	fscanf(in, " %i", &value);
	return value != 0;
}

