#include "math3dlib.h"

#include "matrix/matrix2.h"

#include <vector>
#include <cassert>
#include <math.h>
#include <iostream>
#include <ostream>
#include <sstream>

using namespace Maths;

Matrix2::Matrix2(float _m[4])
{
	for (int i = 0; i < 4; i++)
		m[i] = _m[i];
}

Matrix2::Matrix2(float _f)
{
	for (int i = 0; i < 4; i++)
		m[i] = _f;
}

Matrix2::Matrix2(const Matrix2& _copy)
{
	for (int i = 0; i < 4; i++)
		m[i] = _copy[i];
}

Matrix2::Matrix2(const Vector2& _line1, const Vector2& _line2)
{
	m[0] = _line1[0]; m[1] = _line1[1];
	m[2] = _line2[0]; m[3] = _line2[1];
}

Matrix2 Matrix2::operator*(const Matrix2& _m) const
{
	return Multiplied(_m);
}

Vector2 Matrix2::operator*(const Vector2& _v) const
{
	return Multiply(_v);
}

Matrix2& Matrix2::operator=(const Matrix2& _copy)
{
	for (int i = 0; i < 4; i++)
		m[i] = _copy[i];
	return *this;
}

bool Matrix2::operator==(const Matrix2& _other) const
{
	bool isEqual = true;
	for (unsigned int i = 0; i < 4 && isEqual; i++)
	{
		if (fabs(m[i] - _other[i]) > 0.0000001f)
			isEqual = false;
	}
	return isEqual;
}

float& Matrix2::operator[](unsigned int _index)
{
	assert(_index < 4);
	return m[_index];
}

float Matrix2::operator[](unsigned int _index) const
{
	assert(_index < 4);
	return m[_index];
}

float Matrix2::GetAt(unsigned int _row, unsigned int _col) const
{
	assert(_row < 2 && _col < 2);
	return m[_row * 2 + _col];
}

void Matrix2::SetAt(unsigned int _row, unsigned int _col, float _val)
{
	assert(_row < 2 && _col < 2);
	m[_row * 2 + _col] = _val;
}

Vector2 Matrix2::GetDiagonal() const
{
	return Vector2(m[0], m[3]);
}

float Matrix2::GetTrace() const
{
	return m[0] + m[3];
}

float Matrix2::Det() const
{
	return m[0] * m[3] - m[1] * m[2];
}

Matrix2 Matrix2::GetOpposite() const
{
	Matrix2 tempM = *this;
	for (unsigned int i = 0; i < 4; i++)
		tempM[i] = -tempM[i];
	return tempM;
}

Matrix2 Matrix2::Transposed() const
{
	Matrix2 res(0.f);
	for (unsigned int i = 0; i < 2; i++)
	{
		for (unsigned int j = 0; j < 2; j++)
			res.SetAt(j, i, GetAt(i, j));
	}
	return res;
}

Matrix2& Matrix2::Transpose()
{
	Matrix2 tempM(0.f);
	for (unsigned int i = 0; i < 2; i++)
	{
		for (unsigned int j = 0; j < 2; j++)
			tempM.SetAt(j, i, GetAt(i, j));
	}
	(*this) = tempM;
	return *this;
}

Matrix2 Matrix2::Add(const Matrix2& _m2) const
{
	Matrix2 res = _m2;
	for (unsigned int i = 0; i < 4; i++)
		res[i] = m[i] + res[i];
	return res;
}

Matrix2& Matrix2::AddEmplace(const Matrix2& _m2)
{
	for (unsigned int i = 0; i < 4; i++)
		m[i] += _m2[i];
	return *this;
}

Matrix2 Matrix2::Scaled(float _f) const
{
	Matrix2 res = *this;
	for (unsigned int i = 0; i < 4; i++)
		res[i] *= _f;
	return res;
}

Matrix2& Matrix2::Scale(float _f)
{
	for (unsigned int i = 0; i < 4; i++)
		m[i] *= _f;
	return *this;
}

Matrix2 Matrix2::GaussJordan() const
{
	Matrix2 copy = *this;
	return copy.GaussJordanEmplace();
}

Matrix2& Matrix2::GaussJordanEmplace()
{
	int r = -1;
	// j is the column
	for (unsigned int j = 0; j < 2; j++)
	{
		// We look for the index k (the row) of the maximum num in this column. i is the current row.
		float max = 0; int k = 0;
		for (unsigned int i = r + 1; r + 1 < 2 && i < 2; i++)
		{
			if (fabs(GetAt(i, j)) > fabs(max))
			{
				k = i;
				max = GetAt(i, j);
			}
		}

		// We operate based on the pivot m[k,j] <=> m[2*k + j] here
		float pivot = GetAt(k, j);
		if (pivot != 0 && r + 1 < 2)
		{
			r++;
			// Normalization of the row by the pivot
			for (unsigned int tempCol = 0; tempCol < 2; tempCol++)
				SetAt(k, tempCol, GetAt(k, tempCol) / pivot);

			// Swapping k row and r row if they are not the same number
			if (k != r)
			{
				// Storing k row temporarily
				std::vector<float> temp;
				for (unsigned int tempI = 0; tempI < 2; tempI++)
					temp.push_back(GetAt(k, tempI));
				// Storing r row into k row
				for (unsigned int tempI = 0; tempI < 2; tempI++)
					SetAt(k, tempI, GetAt(r, tempI));
				// Inject temporary k row into r row
				for (unsigned int tempI = 0; tempI < 2; tempI++)
					SetAt(r, tempI, temp[tempI]);
			}
			for (unsigned int i = 0; i < 2; i++)
			{
				// Subtract (row r * m[2*i + j]) from row i
				if (i != r)
				{
					float factor = GetAt(i, j);
					for (unsigned int tempCol = 0; tempCol < 2; tempCol++)
						SetAt(i, tempCol, GetAt(i, tempCol) - GetAt(r, tempCol) * factor);
				}
			}
		}
	}
	return *this;
}

Matrix2 Matrix2::Multiplied(const Matrix2& _m2) const
{
	Matrix2 res = *this;
	return res.Multiply(_m2);
}

Matrix2& Matrix2::Multiply(const Matrix2& _m2)
{
	Matrix2 mRes(0.f);
	for (unsigned int i1 = 0; i1 < 2; i1++)
	{
		for (unsigned int j2 = 0; j2 < 2; j2++)
		{
			for (unsigned int commonI = 0; commonI < 2; commonI++)
			{
				float resValue = GetAt(i1, commonI) * _m2.GetAt(commonI, j2);
				mRes.SetAt(i1, j2, mRes.GetAt(i1, j2) + resValue);
			}
		}
	}
	(*this) = mRes;
	return *this;
}

Vector2 Matrix2::Multiply(const Vector2& _v2) const
{
	Vector2 vRes(0.f);
	std::vector<float> resValues;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
			vRes[i] += GetAt(i, j) * _v2[j];
	}
	return vRes;
}

std::ostream& Maths::operator<<(std::ostream& _os, const Matrix2& _m)
{
	for (unsigned int i = 0; i < 4; i++)
	{
		if (i % 2 == 0)
			_os << "\n";
		_os << _m[i] << " ";
	}
	return _os;
}

Matrix2 Matrix2::Identity()
{
	Matrix2 id(0.f);
	for (unsigned int i = 0; i < 2; i++)
		id.SetAt(i, i, 1);
	return id;
}

Matrix2 Matrix2::CreateScaleMatrix(const Vector2& _scale)
{
	Matrix2 scaleMat = Matrix2::Identity();
	scaleMat[0] = _scale.x;
	scaleMat[3] = _scale.y;
	return scaleMat;
}

Matrix2 Matrix2::CreateRotationMatrix(float _angleDeg)
{
	_angleDeg *= DEG2RAD;
	Matrix2 rotMat = Matrix2::Identity();
	rotMat[0] = cosf(_angleDeg); rotMat[1] = -sinf(_angleDeg);
	rotMat[2] = sinf(_angleDeg); rotMat[3] = cosf(_angleDeg);
	return rotMat;
}

Vector2 Matrix2::RotatePointAroundAnchor(float _angleDeg, const Vector2& _p, const Vector2& _anchor)
{
	_angleDeg *= DEG2RAD;
	float x = _anchor.x + cosf(_angleDeg) * (_p.x - _anchor.x) - sinf(_angleDeg) * (_p.y - _anchor.y);
	float y = _anchor.y + sinf(_angleDeg) * (_p.x - _anchor.x) + cosf(_angleDeg) * (_p.y - _anchor.y);
	return Vector2(x, y);
}
