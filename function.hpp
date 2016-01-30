#ifndef __FUNCTION_HPP__
#define __FUNCTION_HPP__

#include <cstdio>

#include "vector.hpp"
#include "distance.hpp"

class Function
{
public:
	Function(FILE*);
	void write(FILE*);

private:
	Distance distance;
	float exponent;
	Vector origin;
};

#endif

