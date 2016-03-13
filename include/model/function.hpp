#ifndef MODEL_FUNCTION_HPP
#define MODEL_FUNCTION_HPP

#include <cstdio>
#include <vector>

#include "model/matrix.hpp"

class Function
{
public:
	Function(FILE*);
	void write(FILE*);

private:
	float exponent;
	std::vector<int> dimensions;
	Matrix mean;
	Matrix rotation;
	Matrix multiplier;
};

#endif

