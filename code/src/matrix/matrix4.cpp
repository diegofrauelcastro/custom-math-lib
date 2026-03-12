#include "math3dlib.h"

#include "matrix/matrix4.h"

#include <vector>
#include <cassert>
#include <math.h>
#include <iostream>
#include <ostream>
#include <sstream>

using namespace Maths;

Matrix4::Matrix4()
{
	for (int i = 0; i < 16; i++)
		m[i] = 0;
}

Matrix4::Matrix4(float _m[16])
{
	for (int i = 0; i < 16; i++)
		m[i] = _m[i];
}

Matrix4::Matrix4(const Vector4& _line1, const Vector4& _line2, const Vector4& _line3, const Vector4& _line4)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Vector4 currentV = _line4;
			if (i == 0)
				currentV = _line1;
			else if (i == 1)
				currentV = _line2;
			else if (i == 2)
				currentV = _line3;
			m[4 * i + j] = currentV[j];
		}
	}
}

Maths::Matrix4::Matrix4(const Matrix4& _copy)
{
	for (int i = 0; i < 16; i++)
		m[i] = _copy.m[i];
}

Matrix4 Matrix4::operator*(const Matrix4& _m) const
{
	return Multiplied(_m);
}

Vector4 Matrix4::operator*(const Vector4& _v) const
{
	return Multiply(_v);
}

Matrix4& Matrix4::operator=(const Matrix4& _copy)
{
	for (int i = 0; i < 16; i++)
		m[i] = _copy[i];
	return *this;
}

float& Matrix4::operator[](int _index)
{
	assert(0 <= _index && _index < 16);
	return m[_index];
}

float Matrix4::operator[](int _index) const
{
	assert(0 <= _index && _index < 16);
	return m[_index];
}

float Matrix4::GetAt(unsigned int _row, unsigned int _col) const
{
	assert(_row < 4 && _col < 4);
	return m[_row * 4 + _col];
}

void Matrix4::SetAt(unsigned int _row, unsigned int _col, float _val)
{
	assert(_row < 4 && _col < 4);
	m[_row * 4 + _col] = _val;
}

Vector4 Matrix4::GetDiagonal() const
{
	return Vector4(m[0], m[5], m[10], m[15]);
}

float Matrix4::GetTrace() const
{
	Vector4 diag = GetDiagonal();
	return diag.x + diag.y + diag.z + diag.w;
}

Matrix4 Matrix4::GetOpposite() const
{
	Matrix4 tempM = *this;
	for (int i = 0; i < 16; i++)
		tempM[i] = -tempM[i];
	return tempM;
}

float Matrix4::Det() const
{
	float line1 = m[3]*m[6]*m[9]*m[12]  + m[0]*m[5]*m[10]*m[15] - m[0]*m[5]*m[11]*m[14] - m[0]*m[6]*m[9] *m[15]  ;
	float line2 = m[0]*m[6]*m[11]*m[13] + m[0]*m[7]*m[9]*m[14]  - m[0]*m[7]*m[10]*m[13] - m[1]*m[4]*m[10]*m[15]  ;
	float line3 = m[1]*m[4]*m[11]*m[14] + m[1]*m[6]*m[8]*m[15]  - m[1]*m[6]*m[11]*m[12] - m[1]*m[7]*m[8] *m[14]  ;
	float line4 = m[1]*m[7]*m[10]*m[12] + m[2]*m[4]*m[9]*m[15]  - m[2]*m[4]*m[11]*m[13] - m[2]*m[5]*m[8] *m[15]  ;
	float line5 = m[2]*m[5]*m[11]*m[12] + m[2]*m[7]*m[8]*m[13]  - m[2]*m[7]*m[9] *m[12] - m[3]*m[4]*m[9] *m[14]  ;
	float line6 = m[3]*m[4]*m[10]*m[13] + m[3]*m[5]*m[8]*m[14]  - m[3]*m[5]*m[10]*m[12] - m[3]*m[6]*m[8] *m[13]  ;
	return line1 + line2 + line3 + line4 + line5 + line6;
}

Matrix4 Matrix4::Transposed() const
{
	Matrix4 res = Matrix4();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			res[4*i + j] = m[4*j + i];
	}
	return res;
}

Matrix4& Matrix4::Transpose()
{
	Matrix4 tempM = Matrix4();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			tempM[4 * i + j] = m[4 * j + i];
	}
	(*this) = tempM;
	return *this;
}

Matrix4 Matrix4::Add(const Matrix4& _m2) const
{
	Matrix4 res = _m2;
	for (int i = 0; i < 16; i++)
		res[i] += m[i];
	return res;
}

Matrix4& Matrix4::AddEmplace(const Matrix4& _m2)
{
	for (int i = 0; i < 16; i++)
		m[i] += _m2[i];
	return *this;
}

Matrix4 Matrix4::Scaled(float _f) const
{
	Matrix4 res = *this;
	for (int i = 0; i < 16; i++)
		res[i] *= _f;
	return res;
}

Matrix4& Matrix4::Scale(float _f)
{
	for (int i = 0; i < 16; i++)
		m[i] *= _f;
	return *this;
}

Matrix4 Matrix4::GaussJordan() const
{
	Matrix4 copy = *this;
	return copy.GaussJordanEmplace();
}

Matrix4& Matrix4::GaussJordanEmplace()
{
	int r = -1;
	// j is the column
	for (int j = 0; j < 4; j++)
	{
		// We look for the index k (the row) of the maximum num in this column. i is the current row.
		int k = 4 * (r+1) + j;
		for (int i = r+1; i < 4; i++)
		{
			if (fabs(m[4*i + j]) > fabs(m[k]))
				k = 4*i + j;
		}
		k = k / 4;

		// We operate based on the pivot m[k,j] <=> m[4k + j] here
		if (m[4 * k + j] != 0)
		{
			r++;
			// Normalization of the row by the pivot
			float pivot = m[4 * k + j];
			for (int tempCol = 0; tempCol < 4; tempCol++)
				m[4 * k + tempCol] /= pivot;

			// Swapping k row and r row if they are not the same number
			if (k != r)
			{
				// Storing k row
				float temp[4] = { m[4 * k], m[4 * k + 1] , m[4 * k + 2] , m[4 * k + 3] };
				// Storing r row into k row
				m[4*k] = m[4*r]; m[4*k+1] = m[4*r+1]; m[4*k+2] = m[4*r+2]; m[4*k+3] = m[4*r+3];
				// Inject temporary k row into r row
				m[4*r] = temp[0]; m[4*r+1] = temp[1]; m[4*r+2] = temp[2]; m[4*r+3] = temp[3];
			}
			for (int i = 0; i < 4; i++)
			{
				// Subtract (row r * m[4*i + j]) from row i
				if (i != r)
				{
					float factor = m[4 * i + j];
					for (int tempCol = 0; tempCol < 4; tempCol++)
						m[4*i+tempCol] -= m[4*r+tempCol] * factor;
				}
			}
		}
	}
	return *this;
}

// https://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix - Answer by @willnode (Jun 8, 2017)
Matrix4& Matrix4::Inverse()
{
	float A2323 = m[10] * m[15] - m[11] * m[14];
	float A1323 = m[9] * m[15] - m[11] * m[13];
	float A1223 = m[9] * m[14] - m[10] * m[13];
	float A0323 = m[8] * m[15] - m[11] * m[12];
	float A0223 = m[8] * m[14] - m[10] * m[12];
	float A0123 = m[8] * m[13] - m[9] * m[12];
	float A2313 = m[6] * m[15] - m[7] * m[14];
	float A1313 = m[5] * m[15] - m[7] * m[13];
	float A1213 = m[5] * m[14] - m[6] * m[13];
	float A2312 = m[6] * m[11] - m[7] * m[10];
	float A1312 = m[5] * m[11] - m[7] * m[9];
	float A1212 = m[5] * m[10] - m[6] * m[9];
	float A0313 = m[4] * m[15] - m[7] * m[12];
	float A0213 = m[4] * m[14] - m[6] * m[12];
	float A0312 = m[4] * m[11] - m[7] * m[8];
	float A0212 = m[4] * m[10] - m[6] * m[8];
	float A0113 = m[4] * m[13] - m[5] * m[12];
	float A0112 = m[4] * m[9] - m[5] * m[8];

	float det = m[0] * (m[5] * A2323 - m[6] * A1323 + m[7] * A1223)
		- m[1] * (m[4] * A2323 - m[6] * A0323 + m[7] * A0223)
		+ m[2] * (m[4] * A1323 - m[5] * A0323 + m[7] * A0123)
		- m[3] * (m[4] * A1223 - m[5] * A0223 + m[6] * A0123);
	det = 1 / det;

	Matrix4 res = *this;
	res[0] = det *   (m[5] * A2323 - m[6] * A1323 + m[7] * A1223);
	res[1] = det *  -(m[1] * A2323 - m[2] * A1323 + m[3] * A1223);
	res[2] = det *   (m[1] * A2313 - m[2] * A1313 + m[3] * A1213);
	res[3] = det *  -(m[1] * A2312 - m[2] * A1312 + m[3] * A1212);
	res[4] = det *  -(m[4] * A2323 - m[6] * A0323 + m[7] * A0223);
	res[5] = det *   (m[0] * A2323 - m[2] * A0323 + m[3] * A0223);
	res[6] = det *  -(m[0] * A2313 - m[2] * A0313 + m[3] * A0213);
	res[7] = det *   (m[0] * A2312 - m[2] * A0312 + m[3] * A0212);
	res[8] = det *   (m[4] * A1323 - m[5] * A0323 + m[7] * A0123);
	res[9] = det *  -(m[0] * A1323 - m[1] * A0323 + m[3] * A0123);
	res[10] = det *  (m[0] * A1313 - m[1] * A0313 + m[3] * A0113);
	res[11] = det * -(m[0] * A1312 - m[1] * A0312 + m[3] * A0112);
	res[12] = det * -(m[4] * A1223 - m[5] * A0223 + m[6] * A0123);
	res[13] = det *  (m[0] * A1223 - m[1] * A0223 + m[2] * A0123);
	res[14] = det * -(m[0] * A1213 - m[1] * A0213 + m[2] * A0113);
	res[15] = det *  (m[0] * A1212 - m[1] * A0212 + m[2] * A0112);
	for (int i = 0; i < 16; i++)
		m[i] = res[i];
	return *this;
}

Matrix4 Matrix4::Inversed() const
{
	Matrix4 inverse = *this;
	return inverse.Inverse();
}

Matrix4 Matrix4::Multiplied(const Matrix4& _m2) const
{
	Matrix4 res = *this;
	return res.Multiply(_m2);
}

Matrix4& Matrix4::Multiply(const Matrix4& _m2)
{
	Matrix4 mRes;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			mRes[4*i + j] = m[4*i]*_m2.m[j] + m[4*i+1]*_m2.m[4+j] + m[4*i+2]*_m2.m[8+j] + m[4*i+3]*_m2.m[12+j];
	}
	(*this) = mRes;
	return *this;
}

Vector4 Matrix4::Multiply(const Vector4& v) const
{
	return Vector4(
		m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3] * v[3],
		m[4] * v[0] + m[5] * v[1] + m[6] * v[2] + m[7] * v[3],
		m[8] * v[0] + m[9] * v[1] + m[10] * v[2] + m[11] * v[3],
		m[12] * v[0] + m[13] * v[1] + m[14] * v[2] + m[15] * v[3]
	);
}

std::ostream& Maths::operator<<(std::ostream& _os, const Matrix4& _m)
{
	for (int i = 0; i < 16; i++)
	{
		if (i % 4 == 0)
			_os << "\n";
		_os << _m.m[i] << " ";
	}
	return _os;
}

Matrix4 Matrix4::Identity()
{
	Matrix4 id;
	for (int i = 0; i < 4; i++)
		id[4 * i + i] = 1;
	return id;
}

Matrix4 Matrix4::CreateTransformMatrix(const Vector3& _position, const Vector3& _rotationDeg, const Vector3& _scale)
{
	Matrix4 mTranslate = CreateTranslationMatrix(_position);
	Matrix4 mRotationY = CreateYRotationMatrix(_rotationDeg.y);
	Matrix4 mRotationX = CreateXRotationMatrix(_rotationDeg.x);
	Matrix4 mRotationZ = CreateZRotationMatrix(_rotationDeg.z);
	Matrix4 mScale = CreateScaleMatrix(_scale);
	return mTranslate * mRotationY * mRotationX * mRotationZ * mScale;
}

Matrix4 Matrix4::CreateTranslationMatrix(const Vector3& _translation)
{
	Matrix4 m = Matrix4::Identity();
	for (int i = 0; i < 3; i++)
		m[4*(i+1)-1] = _translation[i];
	return m;
}

Matrix4 Matrix4::CreateScaleMatrix(const Vector3& _scale)
{
	Matrix4 m = Matrix4::Identity();
	for (int i = 0; i < 3; i++)
		m[4*i+i] = _scale[i];
	return m;
}

Matrix4 Matrix4::CreateXRotationMatrix(float _angleDeg)
{
	_angleDeg *= DEG2RAD;
	Matrix4 m = Matrix4::Identity();
	float cosAngle = cosf(_angleDeg);
	float sinAngle = sinf(_angleDeg);
	m[5] = cosAngle; m[6] = -sinAngle;
	m[9] = sinAngle; m[10] = cosAngle;
	return m;
}

Matrix4 Matrix4::CreateYRotationMatrix(float _angleDeg)
{
	_angleDeg *= DEG2RAD;
	Matrix4 m = Matrix4::Identity();
	float cosAngle = cosf(_angleDeg);
	float sinAngle = sinf(_angleDeg);
	m[0] = cosAngle; m[2] = sinAngle;
	m[8] = -sinAngle; m[10] = cosAngle;
	return m;
}

Matrix4 Matrix4::CreateZRotationMatrix(float _angleDeg)
{
	_angleDeg *= DEG2RAD;
	Matrix4 m = Matrix4::Identity();
	float cosAngle = cosf(_angleDeg);
	float sinAngle = sinf(_angleDeg);
	m[0] = cosAngle; m[1] = -sinAngle;
	m[4] = sinAngle; m[5] = cosAngle;
	return m;
}

Vector3 Matrix4::RotatePointAroundThreeAxis(Vector3& _anglesDegPerAxis, const Vector3& _p, const Vector3 _anchor)
{
	Vector4 vec4P(_p);
	Vector4 result = Matrix4::RotatePointAroundThreeAxis(_anglesDegPerAxis, vec4P, _anchor);
	return Vector3(result.x, result.y, result.z);
}

Vector4 Matrix4::RotatePointAroundThreeAxis(Vector3& _anglesDegPerAxis, const Vector4& _p, const Vector3 _anchor)
{
	Matrix4 matX = Matrix4::CreateXRotationMatrix(_anglesDegPerAxis.x);
	Matrix4 matY = Matrix4::CreateYRotationMatrix(_anglesDegPerAxis.y);
	Matrix4 matZ = Matrix4::CreateZRotationMatrix(_anglesDegPerAxis.z);
	Matrix4 matTranslate = Matrix4::CreateTranslationMatrix(_anchor);
	Matrix4 matTranslateInverse = Matrix4::CreateTranslationMatrix(-_anchor);
	Matrix4 rotMatOrigin = matZ * matY * matX;
	Matrix4 rotMatAroundAnchor = matTranslate * rotMatOrigin * matTranslateInverse;
	return rotMatAroundAnchor * _p;
}

Matrix4 Matrix4::GetPerspectiveMatrix(unsigned int _width, unsigned int _height, float _near, float _far, float _fovYDeg) 
{
	Matrix4 result;

	float q = 1.0f / tan(0.5f * _fovYDeg * DEG2RAD);
	float a = q / ((float)_width/_height);

	float b = (_near + _far) / (_near - _far);
	float c = (2.0f * _near * _far) / (_near - _far);

	result[0] = a;
	result[5] = q;
	result[10] = b;
	result[14] = -1.0f;
	result[11] = c;

	return result;
}
