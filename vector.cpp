#include "vector.hpp"

Vector::Vector()
{
}

// <size> <element 1> <element 2> ...
Vector::Vector(FILE* in)
{
	std::fscanf(in, "%i", &m_size);
	m_vector = new float[m_size];
	for (int i = 0; i < m_size; i++)
		std::fscanf(in, "%f", m_vector[i]);
}

void Vector::write(FILE* out)
{
	std::fprintf(out, "%i ", m_size);
	for (int i = 0; i < m_size; i++)
		std::fprintf(out, "%f ", m_vector[i]);
	std::fprintf(out, "\n");
}

size_t Vector::size()
{
	return m_size;
}

float Vector::get(size_t i)
{
	return m_vector[i];
}

