#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <cstddef>
#include <cstdio>

class Matrix
{
public:
	Matrix();
	Matrix(const Matrix&);

	Matrix(FILE*);
	void write(FILE*);

	size_t rows() const;
	size_t cols() const;
	size_t size() const;

	float get(size_t, size_t) const;
	float get(size_t) const;

	Matrix operator*(const Matrix&);
	Matrix operator*=(const Matrix&);
	Matrix operator+=(const Matrix&);
	Matrix operator-=(const Matrix&);

private:
	size_t m_rows, m_cols;
	float* m_data;
};

Matrix operator+(const Matrix&, const Matrix&);
Matrix operator-(const Matrix&, const Matrix&);

#endif

