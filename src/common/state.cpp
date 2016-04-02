#include "common/state.hpp"

State::State(FILE* in)
{
	fscanf(in, "s");
	m_location = Matrix(in);
	m_direction = Matrix(in);
}

State::State(const Matrix& location, const Matrix& direction) :
	m_location(location),
	m_direction(direction)
{
}

void State::write(FILE* out) const
{
	fprintf(out, "s\n");
	m_location.write(out);
	m_direction.write(out);
}

Matrix State::location() const
{
	return m_location;
}

Matrix State::direction() const
{
	return m_direction;
}

