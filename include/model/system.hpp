#ifndef MODEL_SYSTEM_HPP
#define MODEL_SYSTEM_HPP

#include <cstdio>
#include <vector>

#include "common/matrix.hpp"
#include "model/hypothesis.hpp"

class System
{
public:
	System();
	System(FILE*);

	size_t write(FILE*) const;

	Matrix mode();

	void add(Evidence);

private:
	size_t maxSize;
	std::vector<Hypothesis> hypotheses;
};

#endif

