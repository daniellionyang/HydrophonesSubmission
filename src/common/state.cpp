#include "common/state.hpp"

State::State(FILE* in)
{
	fscanf(in, "s");
	m_location = Matrix(in);
	m_direction = Matrix(in);
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

