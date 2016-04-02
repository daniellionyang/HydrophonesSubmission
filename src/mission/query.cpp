#include "mission/query.hpp"

State getState(FILE* in, FILE* out)
{
	fprintf(out, "q s\n");
	return State(in);
}

cv::Mat image(FILE* in, FILE* out, char dir, float res, float hcrop, float vcrop)
{
	fprintf(out, "q i %c %f %f %f\n", dir, res, hcrop, vcrop);
	return imageRead(in);
}

Matrix model_mode(FILE* in, FILE* out)
{
	fprintf(out, "q m m\n");
	return Matrix(in);
}

System model_system(FILE* in, FILE* out)
{
	fprintf(out, "q m s\n");
	return System(in);
}

float model_certainty(FILE* in, FILE* out)
{
	fprintf(out, "q m c\n");
	float certainty;
	fscanf(in, "%f", &certainty);
	return certainty;
}

