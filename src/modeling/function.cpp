#include "function.hpp"

// <distance> <exponent> <origin vector>
Function::Function(FILE* in)
{
	int dim;
	std::fscanf(in, "%f %i", &exponent, &dim);
	for (int i = 0; i < dim; i++)
	{
		int d;
		std::fscanf(in, "%i", &d);
		dimensions.push_back(d);
	}
	mean = Matrix(in);
	rotation = Matrix(in);
	multiplier = Matrix(in);
}

void Function::write(FILE* out)
{
	std::fprintf(out, "%f %i ", exponent, dimensions.size());
	for (auto d : dimensions)
		std::fprintf(out, "%i ", d);
	mean.write(out);
	rotation.write(out);
	multiplier.write(out);
	std::fprintf(out, "\n");
}

