#include "modeling/system.hpp"

#include <algorithm>

System::System()
{
}

// <max # distributions> <# distributions> <dist 1> <dist 2> ...
System::System(FILE* in)
{
	int size;
	std::fscanf(in, "%i %i", &maxSize, &size);
	for (int i = 0; i < size; i++)
		distributions.push_back(Distribution(in));
}

void System::write(FILE* out)
{
	std::fprintf(out, "%i %i\n", maxSize, distributions.size());
	for (Distribution d : distributions)
		d.write(out);
	std::fprintf(out, "\n");
}

Matrix System::mode()
{
	return Matrix();
}

System System::operator*=(const System& b)
{
	// the new system of distributions
	std::vector<Distribution> newSystem;

	// foil
	for (auto av : distributions)
		for (auto bv : b.distributions)
			newSystem.push_back(av * bv);

	// pruning
	if (newSystem.size() > maxSize)
	{
		std::sort(newSystem.begin(), newSystem.end());
		newSystem.erase(newSystem.begin() + maxSize, newSystem.end());
	}

	distributions = newSystem;
	return *this;
}

System operator*(const System& a, const System& b)
{
	auto res = a;
	res *= b;
	return res;
}

