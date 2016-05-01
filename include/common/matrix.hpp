#ifndef COMMON_MATRIX_HPP
#define COMMON_MATRIX_HPP

#include <cstddef>
#include <cstdio>

enum Model
{
	UNDEF,
	SUBX,
	SUBY,
	SUBZ,
	SUBYAW,
	SUBPITCH,
	SUBROLL,
	RBUOYX,
	RBUOYY,
	RBUOYZ,
	GBUOYX,
	GBUOYY,
	GBUOYZ,
	YBUOYX,
	YBUOYY,
	YBUOYZ,
	LGATEX,
	LGATEY,
	LGATEZ,
	BIGX,
	BIGY,
	BIGZ,
	SMALLX,
	SMALLY,
	SMALLZ,
	CBINX,
	CBINY,
	OBINX,
	OBINY,
	BINZ,
	PINGERX,
	PINGERY
};

class Matrix
{
public:
	Matrix();
	Matrix(const Matrix&);
	Matrix(size_t, size_t);

	Matrix(FILE*);
	void write(FILE*) const;

	size_t rows() const;
	size_t cols() const;
	size_t size() const;

	float get(size_t, size_t) const;
	float get(size_t) const;

	float set(size_t, size_t, float);
	float set(size_t, float);

	float magnitude() const;

	Matrix operator*(const Matrix&) const;
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

