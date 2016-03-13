#ifndef __FUNCTION_HPP__
#define __FUNCTION_HPP__

#include <cstdio>
#include <vector>

#include "modeling/matrix.hpp"

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

