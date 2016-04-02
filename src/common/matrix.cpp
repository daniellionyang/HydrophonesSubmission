#include "common/matrix.hpp"

#include <stdexcept>
#include <cstring>
#include <cmath>

Matrix::Matrix()
{
}

Matrix::Matrix(const Matrix& a) :
	m_rows(a.rows()),
	m_cols(a.cols()),
	m_data(new float[a.size()])
{
	std::memcpy(m_data, a.m_data, size());
}

// <size> <element 1> <element 2> ...
Matrix::Matrix(FILE* in)
{
	std::fscanf(in, "%i %i", &m_rows, &m_cols);
	m_data = new float[m_rows * m_cols];
	for (int i = 0; i < m_rows * m_cols; i++)
		std::fscanf(in, "%f", m_data[i]);
}

void Matrix::write(FILE* out) const
{
	std::fprintf(out, "%i %i ", m_rows, m_cols);
	for (int i = 0; i < m_rows * m_cols; i++)
		std::fprintf(out, "%f ", m_data[i]);
	std::fprintf(out, "\n");
}

size_t Matrix::rows() const
{
	return m_rows;
}

size_t Matrix::cols() const
{
	return m_cols;
}

size_t Matrix::size() const
{
	return m_rows * m_cols;
}

float Matrix::get(size_t i, size_t j) const
{
	return m_data[i * m_cols + j];
}

float Matrix::get(size_t i) const
{
	return m_data[i];
}

float Matrix::magnitude() const
{
	float sum = 0;
	for (size_t i = 0; i < size(); i++)
		sum += std::pow(get(i), 2);
	return std::sqrt(sum);
}

Matrix Matrix::operator*(const Matrix& a) const
{
	if (cols() != a.rows()) throw std::runtime_error("incompatible size");

	Matrix res;
	res.m_rows = rows();
	res.m_cols = a.cols();

	for (int i = 0; i < res.rows(); i++)
	{
		for (int j = 0; j < res.cols(); j++)
		{
			m_data[i * res.cols() + j] = 0;
			for (int k = 0; k < cols(); k++)
				res.m_data[i * res.cols() + j] += get(i, j) * a.get(k, j);
		}
	}

	return res;
}

Matrix Matrix::operator*=(const Matrix& a)
{
	return *this = *this * a;
}

Matrix operator+(const Matrix& a, const Matrix& b)
{
	Matrix res = a;
	res += b;
	return res;
}

Matrix Matrix::operator+=(const Matrix& a)
{
	if (size() != a.size()) throw std::runtime_error("incompatible size");
	for (int i = 0; i < size(); i++)
		m_data[i] += a.m_data[i];
	return *this;
}

Matrix operator-(const Matrix& a, const Matrix& b)
{
	Matrix res = a;
	res -= b;
	return res;
}

Matrix Matrix::operator-=(const Matrix& a)
{
	if (size() != a.size()) throw std::runtime_error("incompatible size");
	for (int i = 0; i < size(); i++)
		m_data[i] -= a.get(i);
	return *this;
}

