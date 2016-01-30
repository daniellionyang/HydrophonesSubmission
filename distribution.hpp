#ifndef __DISTRIBUTION_HPP__
#define __DISTRIBUTION_HPP__

#include <cstdio>
#include <vector>

#include "function.hpp"

class Distribution
{
public:
	Distribution(FILE*);
	void write(FILE*);

	Distribution operator*=(const Distribution&);

	float integral() const;
	float integral(float, float) const;

private:
	size_t maxSize;
	// e^-(f1 + f2 + f3 ...)
	std::vector<Function> functions;
};

Distribution operator*(const Distribution&, const Distribution&);

bool operator<(const Distribution&, const Distribution&);

#endif

