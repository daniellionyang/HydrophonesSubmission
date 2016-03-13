#ifndef __SYSTEM_HPP__
#define __SYSTEM_HPP__

#include <cstdio>
#include <vector>

#include "matrix.hpp"
#include "distribution.hpp"

class System
{
public:
	System();

	System(FILE*);
	Matrix mode();
	System operator*=(const System&);
	void write(FILE*);

private:
	size_t maxSize;
	std::vector<Distribution> distributions;
};

System operator*(const System&, const System&);

#endif

