#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <cstddef>
#include <cstdio>

class Vector
{
public:
	Vector();

	Vector(FILE*);
	void write(FILE*);

	size_t size();
	float get(size_t);
private:
	size_t m_size;
	float* m_vector;
};

#endif

