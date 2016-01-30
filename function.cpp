#include "function.hpp"

// <distance> <exponent> <origin vector>
Function::Function(FILE* in)
{
	distance = Distance(in);
	std::fscanf(in, "%f", &exponent);
	origin = Vector(in);
}

void Function::write(FILE* out)
{
	distance.write(out);
	std::fprintf(out, "%f ", exponent);
	origin.write(out);
	std::fprintf(out, "\n");
}

