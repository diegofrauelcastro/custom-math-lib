#include "math3dlib.h"

#include "matrix/matrixmxn.h"

#include <vector>
#include <cassert>
#include <math.h>
#include <iostream>
#include <ostream>
#include <sstream>
#include <cmath>

using namespace Maths;

MatrixMxN::MatrixMxN(unsigned int _m, unsigned int _n, float _f)
	: m(_m)
	, n(_n)
{
	matrix = std::vector<float>(_m * _n, _f);
}

MatrixMxN::MatrixMxN(Maths::Vector2 _dimensions, float _f)
	: m(unsigned(_dimensions.x))
	, n(unsigned(_dimensions.y))
{
	matrix = std::vector<float>(m * n, _f);
}

MatrixMxN::MatrixMxN(const MatrixMxN& _copy)
	: m(_copy.m)
	, n(_copy.n)
	, matrix(_copy.matrix)
{
}

MatrixMxN::MatrixMxN(const Maths::Matrix3& _m3)
	: m(3)
	, n(3)
{
	for (int i = 0; i < 9; i++)
		matrix.push_back(_m3[i]);
}

MatrixMxN::MatrixMxN(const Maths::Matrix4& _m4)
	: m(4)
	, n(4)
{
	for (int i = 0; i < 16; i++)
		matrix.push_back(_m4[i]);
}

MatrixMxN MatrixMxN::operator*(const MatrixMxN& _m) const
{
	return Multiplied(_m);
}

VectorND MatrixMxN::operator*(const VectorND& _v) const
{
	return Multiply(_v);
}

MatrixMxN& MatrixMxN::operator=(const MatrixMxN& _copy)
{
	m = _copy.m;
	n = _copy.n;
	matrix = _copy.matrix;
	return *this;
}

bool MatrixMxN::operator==(const MatrixMxN& _other) const
{
	if (m != _other.m || n != _other.n)
		return false;

	bool isEqual = true;
	for (unsigned int i = 0; i < m * n && isEqual; i++)
	{
		if (fabs(matrix[i] - _other[i]) > 0.000001f)
			isEqual = false;
	}
	return isEqual;
}

float& MatrixMxN::operator[](unsigned int _index)
{
	assert(_index < m * n);
	return matrix[_index];
}

float MatrixMxN::operator[](unsigned int _index) const
{
	assert(_index < m * n);
	return matrix[_index];
}

float MatrixMxN::GetAt(unsigned int _row, unsigned int _col) const
{
	assert(_row < m && _col < n);
	return matrix[_row * n + _col];
}

Vector2 MatrixMxN::GetDimensions() const
{
	return Vector2((float)m, (float)n);
}

void MatrixMxN::SetAt(unsigned int _row, unsigned int _col, float _val)
{
	assert(_row < m && _col < n);
	matrix[_row * n + _col] = _val;
}

VectorND MatrixMxN::GetDiagonal() const
{
	// Get all values where i = j
	std::vector<float> diagValues;
	for (unsigned int i = 0; i < m && i < n; i++)
		diagValues.push_back(GetAt(i, i));
	// Create a n dimensions vector with the values of the diagonal
	VectorND res((unsigned int)diagValues.size(), 0);
	for (unsigned int i = 0; i < res.GetDimension(); i++)
		res[i] = diagValues[i];
	return res;
}

float MatrixMxN::GetTrace() const
{
	VectorND diag = GetDiagonal();
	float res = 0.f;
	for (unsigned int i = 0; i < diag.GetDimension(); i++)
		res += diag[i];
	return res;
}

MatrixMxN MatrixMxN::GetOpposite() const
{
	MatrixMxN tempM = *this;
	for (unsigned int i = 0; i < m*n; i++)
		tempM[i] = -tempM[i];
	return tempM;
}

MatrixMxN MatrixMxN::Transposed() const
{
	MatrixMxN res(n, m, 0.f);
	for (unsigned int i = 0; i < m; i++)
	{
		for (unsigned int j = 0; j < n; j++)
			res.SetAt(j, i, GetAt(i, j));
	}
	return res;
}

MatrixMxN& MatrixMxN::Transpose()
{
	MatrixMxN tempM(n, m, 0.f);
	for (unsigned int i = 0; i < m; i++)
	{
		for (unsigned int j = 0; j < n; j++)
			tempM.SetAt(j, i, GetAt(i, j));
	}
	(*this) = tempM;
	return *this;
}

MatrixMxN MatrixMxN::Add(const MatrixMxN& _m2) const
{
	assert(m == _m2.GetDimensions().x && n == _m2.GetDimensions().y);
	MatrixMxN res = _m2;
	for (unsigned int i = 0; i < m*n; i++)
		res[i] = matrix[i] + res[i];
	return res;
}

MatrixMxN& MatrixMxN::AddEmplace(const MatrixMxN& _m2)
{
	assert(m == _m2.GetDimensions().x && n == _m2.GetDimensions().y);
	for (unsigned int i = 0; i < m*n; i++)
		matrix[i] += _m2[i];
	return *this;
}

MatrixMxN MatrixMxN::Scaled(float _f) const
{
	MatrixMxN res = *this;
	for (unsigned int i = 0; i < m*n; i++)
		res[i] *= _f;
	return res;
}

MatrixMxN& MatrixMxN::Scale(float _f)
{
	for (unsigned int i = 0; i < m*n; i++)
		matrix[i] *= _f;
	return *this;
}

MatrixMxN MatrixMxN::GaussJordan() const
{
	MatrixMxN copy = *this;
	return copy.GaussJordanEmplace();
}

MatrixMxN& MatrixMxN::GaussJordanEmplace()
{
	int r = -1;
	// j is the column
	for (unsigned int j = 0; j < n; j++)
	{
		// We look for the index k (the row) of the maximum num in this column. i is the current row.
		float max = 0; int k = 0;
		for (unsigned int i = r + 1; r+1 < int(m) && i < m; i++)
		{
			if (fabs(GetAt(i, j)) > fabs(max))
			{
				k = i;
				max = GetAt(i, j);
			}
		}

		// We operate based on the pivot m[k,j] <=> m[n*k + j] here
		float pivot = GetAt(k, j);
		if (pivot != 0 && r+1 < int(m))
		{
			r++;
			// Normalization of the row by the pivot
			for (unsigned int tempCol = 0; tempCol < n; tempCol++)
				SetAt(k, tempCol, GetAt(k, tempCol)/pivot);

			// Swapping k row and r row if they are not the same number
			if (k != r)
			{
				// Storing k row temporarily
				std::vector<float> temp;
				for (unsigned int tempI = 0; tempI < n; tempI++)
					temp.push_back(GetAt(k, tempI));
				// Storing r row into k row
				for (unsigned int tempI = 0; tempI < n; tempI++)
					SetAt(k, tempI, GetAt(r, tempI));
				// Inject temporary k row into r row
				for (unsigned int tempI = 0; tempI < n; tempI++)
					SetAt(r, tempI, temp[tempI]);
			}
			for (unsigned int i = 0; i < m; i++)
			{
				// Subtract (row r * m[n*i + j]) from row i
				if (i != r)
				{
					float factor = GetAt(i, j);
					for (unsigned int tempCol = 0; tempCol < n; tempCol++)
						SetAt(i, tempCol, GetAt(i, tempCol) - GetAt(r, tempCol) * factor);
				}
			}
		}
	}
	return *this;
}

MatrixMxN& MatrixMxN::Augment(const MatrixMxN& _other)
{
	MatrixMxN copy = (*this).Augmented(_other);
	(*this) = copy;
	return *this;
}

MatrixMxN MatrixMxN::Augmented(const MatrixMxN& _other) const
{
	assert(_other.m == m);
	MatrixMxN res(m, n + _other.m);
	for (unsigned int row = 0; row < m; row++)
	{
		for (unsigned int col = 0; col < n; col++)
			res.SetAt(row, col, GetAt(row, col));
		for (unsigned int colOther = 0; colOther < _other.n; colOther++)
			res.SetAt(row, n + colOther, _other.GetAt(row, colOther));
	}
	return res;
}

MatrixMxN& MatrixMxN::Inverse()
{
	assert(m == n);
	// Storing a copy of the original matrix
	MatrixMxN copyOriginal = *this;
	// Use Gauss-Jordan elimination after augmenting the matrix with the identity matrix.
	MatrixMxN leftPart(GetDimensions());
	MatrixMxN rightPart(GetDimensions());
	Augment(MatrixMxN::Identity(m));
	GaussJordan();
	// Splitting the resulting matrix in two matrices.
	unsigned int half = n/2;
	for (unsigned int row = 0; row < m; row++)
	{
		for (unsigned int col = 0; col < n; col++)
		{
			if (col < half)
				leftPart.SetAt(row, col, GetAt(row, col));
			else
				rightPart.SetAt(row, col-half, GetAt(row, col));
		}
	}
	// Checking if the left part is the identity matrix.
	if (leftPart == MatrixMxN::Identity(leftPart.m))
		(*this) = rightPart;
	// If not, we rollback to the original matrix.
	else
		(*this) = copyOriginal;

	return *this;
}

MatrixMxN MatrixMxN::Inversed() const
{
	MatrixMxN copy = *this;
	copy.Inverse();
	return copy;
}

MatrixMxN MatrixMxN::Multiplied(const MatrixMxN& _m2) const
{
	MatrixMxN res = *this;
	return res.Multiply(_m2);
}

MatrixMxN& MatrixMxN::Multiply(const MatrixMxN& _m2)
{
	Vector2 m2Dim = _m2.GetDimensions();
	assert(n == m2Dim.x);
	MatrixMxN mRes(m, int(m2Dim.y));
	for (unsigned int i1 = 0; i1 < m; i1++)
	{
		for (unsigned int j2 = 0; j2 < _m2.n; j2++)
		{
			for (unsigned int commonI = 0; commonI < n; commonI++)
			{
				float resValue = GetAt(i1, commonI) * _m2.GetAt(commonI, j2);
				mRes.SetAt(i1, j2, mRes.GetAt(i1, j2) + resValue);
			}
		}
	}
	(*this) = mRes;
	return *this;
}


VectorND MatrixMxN::Multiply(const VectorND& _v2) const
{
	assert(n == _v2.GetDimension());
	VectorND vRes(_v2.GetDimension());
	std::vector<float> resValues;
	for (unsigned int i = 0; i < m; i++)
	{
		for (unsigned int j = 0; j < n; j++)
			vRes[j] += GetAt(i, j) * _v2[j];
	}
	return vRes;
}

std::ostream& Maths::operator<<(std::ostream& _os, const MatrixMxN& _m)
{
	for (unsigned int i = 0; i < _m.GetDimensions().x*_m.GetDimensions().y; i++)
	{
		if (i % int(_m.GetDimensions().y) == 0)
			_os << "\n";
		_os << _m[i] << " ";
	}
	return _os;
}

MatrixMxN MatrixMxN::Identity(unsigned int _m)
{
	MatrixMxN id(_m, _m);
	for (unsigned int i = 0; i < _m; i++)
		id.SetAt(i, i, 1);
	return id;
}
