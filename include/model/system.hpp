#ifndef MODEL_SYSTEM_HPP
#define MODEL_SYSTEM_HPP

#include <cstdio>
#include <vector>

#include "common/matrix.hpp"
#include "model/distribution.hpp"

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

