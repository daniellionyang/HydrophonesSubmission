#ifndef COMMON_STATE_HPP
#define COMMON_STATE_HPP

#include <cstddef>
#include <cstdio>

#include "common/matrix.hpp"

struct SubState
{
	SubState(float, float, float, float, float, float);
	SubState(FILE* in);
	
	void write(FILE* out) const;
	
	float x, y, depth, yaw, pitch, roll;
};

class State
{
public:
	State(FILE*);
	State(const Matrix& location, const Matrix& direction);
	void write(FILE*) const;

	Matrix location() const;
	Matrix direction() const;

private:
	Matrix m_location;
	Matrix m_direction;
};

#endif

