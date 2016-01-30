#include "distribution.hpp"

#include <algorithm>

// <max # functions> <# functions> <func 1> <func 2> ...
Distribution::Distribution(FILE* in)
{
	int size;
	std::fscanf(in, "%i %i", &maxSize, &size);
	for (int i = 0; i < size; i++)
		functions.push_back(Function(in));
}

void Distribution::write(FILE* out)
{
	std::fprintf(out, "%i %i\n", maxSize, functions.size());
	for (Function f : functions)
		f.write(out);
	std::fprintf(out, "\n");
}

Distribution Distribution::operator*=(const Distribution& b)
{
	// multiply by adding the exponents
	functions.insert(functions.end(), b.functions.begin(), b.functions.end());

	// pruning
	if (functions.size() > maxSize)
	{
		std::sort(functions.begin(), functions.end(), [=](const Function& a, const Function& b)
		{
			return true;
//			return this->remove(a).integral() < this->remove(b).integral();
		});

		functions.erase(functions.begin() + maxSize, functions.end());
	}

	return *this;
}

float Distribution::integral() const
{
	return 0;
}

float Distribution::integral(float a, float b) const
{
	return 0;
}

Distribution operator*(const Distribution& a, const Distribution& b)
{
	auto res = a;
	res *= b;
	return b;
}

bool operator<(const Distribution& a, const Distribution& b)
{
	return a.integral() < b.integral();
}

