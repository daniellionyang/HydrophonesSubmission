#ifndef MODEL_EVIDENCE_HPP
#define MODEL_EVIDENCE_HPP

#include <cstdio>
#include <vector>
#include <tuple>

struct Variable
{
	int index;
	float value;
	float variance;
};

class Evidence
{
public:
	Evidence();
	Evidence(const std::vector<Variable>&);
	Evidence(FILE*);

	size_t write(FILE*) const;

	std::vector<Variable> variables;
};

#endif

