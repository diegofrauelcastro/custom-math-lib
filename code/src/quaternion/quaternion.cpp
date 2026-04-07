#include "math3dlib.h"

#include "quaternion/quaternion.h"

#include <iostream>
#include <math.h>
#include <string>
#include <cassert>
#include <cmath>

using namespace Maths;

const Quaternion Quaternion::zero = Quaternion();
const Quaternion Quaternion::identity = Quaternion(0.f, 0.f, 0.f, 1.f);

Quaternion::Quaternion()
	: x(0.f)
	, y(0.f)
	, z(0.f)
	, w(0.f)
{
}

Quaternion::Quaternion(float _x, float _y, float _z, float _w)
	: x(_x)
	, y(_y)
	, z(_z)
	, w(_w)
{
}

// Creates a quaternion representing a rotation of 'angle' degrees around 'axis'.
Quaternion::Quaternion(const Vector3& _axis, float _angleDeg)
{
	// Take half of the angle and convert to radians
	float halfAngleRad = (_angleDeg * DEG2RAD) / 2.f;
	float sinHalfAngle = sinf(halfAngleRad);
	Vector3 axisNormalized = _axis.Normalized();
	x = _axis.x * sinHalfAngle;
	y = _axis.y * sinHalfAngle;
	z = _axis.z * sinHalfAngle;
	w = cosf(halfAngleRad);
}

// Creates a simple quaternion with w and v = (x, y, z).
Quaternion::Quaternion(float _w, const Vector3& _v)
	: x(_v.x)
	, y(_v.y)
	, z(_v.z)
	, w(_w)
{
}

Quaternion::Quaternion(float _f)
	: x(_f)
	, y(_f)
	, z(_f)
	, w(_f)
{
}

Quaternion::Quaternion(const Quaternion& _copy)
	: x(_copy.x)
	, y(_copy.y)
	, z(_copy.z)
	, w(_copy.w)
{
}

Quaternion& Quaternion::operator=(const Quaternion& _copy)
{
	x = _copy.x;
	y = _copy.y;
	z = _copy.z;
	w = _copy.w;
	return *this;
}

float& Quaternion::operator[](int _index)
{
	assert(_index >= 0 && _index < 4);

	if (_index == 0)
		return x;
	else if (_index == 1)
		return y;
	else if (_index == 2)
		return z;
	else
		return w;
}

float& Quaternion::operator[](char _coord)
{
	assert(_coord == 'x' || _coord == 'y' || _coord == 'z' || _coord == 'w');

	if (_coord == 'x')
		return x;
	else if (_coord == 'y')
		return y;
	else if (_coord == 'z')
		return z;
	else
		return w;
}

float& Quaternion::operator[](const std::string& _coord)
{
	assert(_coord == "x" || _coord == "y" || _coord == "z" || _coord == "w");

	if (_coord == "x")
		return x;
	else if (_coord == "y")
		return y;
	else if (_coord == "z")
		return z;
	else
		return w;
}

float Quaternion::operator[](int _index) const
{
	assert(_index >= 0 && _index < 4);

	if (_index == 0)
		return x;
	else if (_index == 1)
		return y;
	else if (_index == 2)
		return z;
	else
		return w;
}

float Quaternion::operator[](char _coord) const
{
	assert(_coord == 'x' || _coord == 'y' || _coord == 'z' || _coord == 'w');

	if (_coord == 'x')
		return x;
	else if (_coord == 'y')
		return y;
	else if (_coord == 'z')
		return z;
	else
		return w;
}

float Quaternion::operator[](const std::string& _coord) const
{
	assert(_coord == "x" || _coord == "y" || _coord == "z" || _coord == "w");

	if (_coord == "x")
		return x;
	else if (_coord == "y")
		return y;
	else if (_coord == "z")
		return z;
	else
		return w;
}

Quaternion Quaternion::operator+(const float _f) const
{
	return Quaternion(x + _f, y + _f, z + _f, w + _f);
}

Quaternion& Quaternion::operator+=(const Quaternion& _v)
{
	AddEmplace(_v);
	return *this;
}

Quaternion& Quaternion::operator-=(const Quaternion& _v)
{
	AddEmplace(-_v);
	return *this;
}

Quaternion Quaternion::operator-() const
{
	return Quaternion(-x, -y, -z, -w);
}

Quaternion Quaternion::operator*(float _f) const
{
	return Scaled(_f);
}

Quaternion& Quaternion::operator*=(float _f)
{
	Scale(_f);
	return *this;
}

Quaternion Quaternion::operator/(float _f) const
{
	assert(_f != 0.f);
	return Quaternion(x / _f, y / _f, z / _f, w / _f);
}

Quaternion& Quaternion::operator/=(float _f)
{
	assert(_f != 0.f);
	x /= _f;
	y /= _f;
	z /= _f;
	w /= _f;
	return *this;
}

void Quaternion::operator++(int _i)
{
	(void)_i;
	float length = GetMagnitude();
	assert(length > 0);
	x *= (length + 1) / length;
	y *= (length + 1) / length;
	z *= (length + 1) / length;
	w *= (length + 1) / length;
}

void Quaternion::operator--(int _i)
{
	(void)_i;
	float length = GetMagnitude();
	assert(length > 0);
	x *= (length - 1) / length;
	y *= (length - 1) / length;
	z *= (length - 1) / length;	
	w *= (length - 1) / length;
}

Quaternion Quaternion::operator*(const Quaternion& _v) const
{
	return Product(_v);
}

bool Quaternion::operator==(const Quaternion& _v) const
{
	return GetMagnitude() == _v.GetMagnitude();
}

bool Quaternion::operator!=(const Quaternion& _v) const
{
	return GetMagnitude() != _v.GetMagnitude();
}

bool Quaternion::operator<(const Quaternion& _v) const
{
	return GetMagnitude() < _v.GetMagnitude();
}

bool Quaternion::operator<=(const Quaternion& _v) const
{
	return GetMagnitude() <= _v.GetMagnitude();
}

bool Quaternion::operator>(const Quaternion& _v) const
{
	return GetMagnitude() > _v.GetMagnitude();
}

bool Quaternion::operator>=(const Quaternion& _v) const
{
	return GetMagnitude() >= _v.GetMagnitude();
}

Vector3 Quaternion::VectorXYZ() const
{
	return Vector3(x, y, z);
}

Quaternion Quaternion::Product(const Quaternion& _v) const
{
	float newW = w * _v.w - x * _v.x - y * _v.y - z * _v.z;
	float newX = w * _v.x + x * _v.w + y * _v.z - z * _v.y;
	float newY = w * _v.y - x * _v.z + y * _v.w + z * _v.x;
	float newZ = w * _v.z + x * _v.y - y * _v.x + z * _v.w;
	return Quaternion(newX, newY, newZ, newW);
}

float Quaternion::Dot(const Quaternion& _v) const
{
	return w * _v.w + x * _v.x + y * _v.y + z * _v.z;
}

Quaternion Quaternion::ElementWiseProduct(const Quaternion& _v) const
{
	return Quaternion(x * _v.x, y * _v.y, z * _v.z, w * _v.w);
}

Quaternion Quaternion::Inversed() const
{
	float squaredNorm = SquaredNorm();
	if (fabs(squaredNorm) < 0.0001f)
		return Quaternion(0, 0, 0, 0);

	return Conjugated() / squaredNorm;
}

Quaternion& Quaternion::Inverse()
{
	float squaredNorm = SquaredNorm();
	if (fabs(squaredNorm) < 0.0001f)
		*this = Quaternion::zero;
	Conjugate();
	*this /= squaredNorm;

	return *this;
}

Matrix4 Maths::Quaternion::ToRotationMatrix() const
{
	Matrix4 rotationMatrix;
	float xx = x * x;
	float yy = y * y;
	float zz = z * z;
	float xy = x * y;
	float xz = x * z;
	float yz = y * z;

	rotationMatrix[0] = 1 - 2 * (yy + zz);
	rotationMatrix[1] = 2 * (xy - z * w);
	rotationMatrix[2] = 2 * (xz + y * w);
	rotationMatrix[3] = 0;

	rotationMatrix[4] = 2 * (xy + z * w);
	rotationMatrix[5] = 1 - 2 * (xx + zz);
	rotationMatrix[6] = 2 * (yz - x * w);
	rotationMatrix[7] = 0;
		
	rotationMatrix[8] = 2 * (xz - y * w);
	rotationMatrix[9] = 2 * (yz + x * w);
	rotationMatrix[10] = 1 - 2 * (xx + yy);
	rotationMatrix[11] = 0;

	rotationMatrix[12] = 0;
	rotationMatrix[13] = 0;
	rotationMatrix[14] = 0;
	rotationMatrix[15] = 1;

	return rotationMatrix;
}

float Quaternion::GetMagnitude() const
{
	return sqrt(x * x + y * y + z * z + w * w);
}

float Quaternion::Norm() const
{
	return GetMagnitude();
}

float Quaternion::SquaredNorm() const
{
	return x * x + y * y + z * z + w * w;
}

Quaternion Quaternion::Add(const Quaternion& _v) const
{
	return Quaternion(x + _v.x, y + _v.y, z + _v.z, w + _v.w);
}

Quaternion& Quaternion::AddEmplace(const Quaternion& _v)
{
	x += _v.x;
	y += _v.y;
	z += _v.z;
	w += _v.w;
	return *this;
}

Quaternion Quaternion::Scaled(float _f) const
{
	return Quaternion(x * _f, y * _f, z * _f, w * _f);
}

Quaternion& Quaternion::Scale(float _f)
{
	x *= _f;
	y *= _f;
	z *= _f;
	w *= _f;
	return *this;
}

Quaternion Quaternion::GetOpposite() const
{
	return -(*this);
}

Quaternion Quaternion::Conjugated() const
{
	return Quaternion(w, -VectorXYZ());
}

Quaternion& Quaternion::Conjugate()
{
	x = -x;
	y = -y;
	z = -z;
	w = w;
	return *this;
}

Quaternion Quaternion::Normalized() const
{
	float length = GetMagnitude();
	if (length > 0)
		return Quaternion(x / length, y / length, z / length, w / length);
	else
		return Quaternion::zero;
}

Quaternion& Quaternion::Normalize()
{
	float length = GetMagnitude();
	if (length > 0)
	{
		x /= length;
		y /= length;
		z /= length;
		w /= length;
	}
	else
		*this = Quaternion::zero;
	return *this;
}

Vector3 Quaternion::RotateVec3(const Vector3& _v) const
{
	// q * v * q^-1
	Quaternion p(0.f, _v);
	return (*this * p * Inversed()).VectorXYZ();
}

float Quaternion::Distance(const Quaternion& _p1, const Quaternion& _p2)
{
	return (_p2 - _p1).GetMagnitude();
}

std::ostream& Maths::operator<<(std::ostream& _os, const Quaternion& _v)
{
	return _os << _v.w << " + " << _v.x << "i + " << _v.y << "j + " << _v.z << "k";
}

std::string Maths::operator+(const std::string& _str, const Quaternion& _v)
{
	std::string result = _str;
	result += "a = ";
	result += std::to_string(_v.w);
	result += "b = ";
	result += std::to_string(_v.x);
	result += ", c = ";
	result += std::to_string(_v.y);
	result += ", d = ";
	result += std::to_string(_v.z);
	return result;
}

std::string& Maths::operator+=(std::string& _str, const Quaternion& _v)
{
	_str += "a = ";
	_str += std::to_string(_v.w);
	_str += "b = ";
	_str += std::to_string(_v.x);
	_str += ", c = ";
	_str += std::to_string(_v.y);
	_str += ", d = ";
	_str += std::to_string(_v.z);
	return _str;
}

Quaternion Maths::operator*(float _f, const Quaternion& _v)
{
	return Quaternion(_f * _v.x, _f * _v.y, _f * _v.z, _f * _v.w);
}

Quaternion Maths::operator/(float _f, const Quaternion& _v)
{
	assert(_v.x != 0.f);
	assert(_v.y != 0.f);
	assert(_v.z != 0.f);
	assert(_v.w != 0.f);
	return Quaternion(_f / _v.x, _f / _v.y, _f / _v.z, _f / _v.w);
}

Quaternion Maths::operator+(const Quaternion& _v1, const Quaternion& _v2)
{
	return _v1.Add(_v2);
}

Quaternion Maths::operator+(float _f, const Quaternion& _v)
{
	return Quaternion(_f + _v.x, _f + _v.y, _f + _v.z, _f + _v.w);
}

Quaternion Maths::operator-(const Quaternion& _v1, const Quaternion& _v2)
{
	return _v1.Add(-_v2);
}

Quaternion Maths::operator-(float _f, const Quaternion& _v)
{
	return Quaternion(_f - _v.x, _f - _v.y, _f - _v.z, _f - _v.w);
}

Vector3 Maths::operator*(const Vector3& _v, const Quaternion& _q)
{
	return _q.RotateVec3(_v);
}
