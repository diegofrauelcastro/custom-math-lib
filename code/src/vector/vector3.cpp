#include "math3dlib.h"

#include "vector/vector3.h"

#include <cassert>
#include <math.h>
#include <iostream>
#include <ostream>
#include <sstream>
#include <cmath>

using namespace Maths;

const Vector3 Vector3::zero = Vector3();
const Vector3 Vector3::one = Vector3(1.f, 1.f, 1.f);
const Vector3 Vector3::right = Vector3(1.f, 0.f, 0.f);
const Vector3 Vector3::left = Vector3(-1.f, 0.f, 0.f);
const Vector3 Vector3::up = Vector3(0.f, 1.f, 0.f);
const Vector3 Vector3::down = Vector3(0.f, -1.f, 0.f);
const Vector3 Vector3::forward = Vector3(0.f, 0.f, 1.f);
const Vector3 Vector3::back = Vector3(0.f, 0.f, -1.f);

Vector3::Vector3()
	: x(0.f)
	, y(0.f)
	, z(0.f)
{
}

Vector3::Vector3(float _x, float _y, float _z)
	: x(_x)
	, y(_y)
	, z(_z)
{
}

Vector3::Vector3(float _f)
	: x(_f)
	, y(_f)
	, z(_f)
{
}

Vector3::Vector3(const Vector3& _copy)
	: x(_copy.x)
	, y(_copy.y)
	, z(_copy.z)
{
}

Vector3& Vector3::operator=(const Vector3& _copy)
{
	x = _copy.x;
	y = _copy.y;
	z = _copy.z;
	return *this;
}

float& Vector3::operator[](int _index)
{
	assert(_index == 0 || _index == 1 || _index == 2);

	if (_index == 0)
		return x;
	else if (_index == 1)
		return y;
	else
		return z;
}

float& Vector3::operator[](char _coord)
{
	assert(_coord == 'x' || _coord == 'y' || _coord == 'z');

	if (_coord == 'x')
		return x;
	else if (_coord == 'y')
		return y;
	else
		return z;
}

float& Vector3::operator[](const std::string& _coord)
{
	assert(_coord == "x" || _coord == "y" || _coord == "z");

	if (_coord == "x")
		return x;
	else if (_coord == "y")
		return y;
	else
		return z;
}

float Vector3::operator[](int _index) const
{
	assert(_index == 0 || _index == 1 || _index == 2);

	if (_index == 0)
		return x;
	else if (_index == 1)
		return y;
	else
		return z;
}

float Vector3::operator[](char _coord) const
{
	assert(_coord == 'x' || _coord == 'y' || _coord == 'z');

	if (_coord == 'x')
		return x;
	else if (_coord == 'y')
		return y;
	else
		return z;
}

float Vector3::operator[](const std::string& _coord) const
{
	assert(_coord == "x" || _coord == "y" || _coord == "z");

	if (_coord == "x")
		return x;
	else if (_coord == "y")
		return y;
	else
		return z;
}

Vector3 Vector3::operator+(const float _f) const
{
	return Vector3(x + _f, y + _f, z + _f);
}

Vector3& Vector3::operator+=(const Vector3& _v)
{
	AddEmplace(_v);
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& _v)
{
	AddEmplace(-_v);
	return *this;
}

Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator*(float _f) const
{
	return Scaled(_f);
}

Vector3& Vector3::operator*=(float _f)
{
	Scale(_f);
	return *this;
}

Vector3 Vector3::operator/(float _f) const
{
	assert(_f != 0.f);
	return Vector3(x / _f, y / _f, z / _f);
}

Vector3& Vector3::operator/=(float _f)
{
	assert(_f != 0.f);
	x /= _f;
	y /= _f;
	z /= _f;
	return *this;
}

void Vector3::operator++(int _i)
{
	(void)_i;
	float length = GetMagnitude();
	assert(length > 0);
	x *= (length + 1) / length;
	y *= (length + 1) / length;
	z *= (length + 1) / length;
}

void Vector3::operator--(int _i)
{
	(void)_i;
	float length = GetMagnitude();
	assert(length > 0);
	x *= (length - 1) / length;
	y *= (length - 1) / length;
	z *= (length - 1) / length;
}

float Vector3::operator*(const Vector3& _v) const
{
	return DotProduct(_v);
}

bool Vector3::operator==(const Vector3& _v) const
{
	return GetMagnitude() == _v.GetMagnitude();
}

bool Vector3::operator!=(const Vector3& _v) const
{
	return GetMagnitude() != _v.GetMagnitude();
}

bool Vector3::operator<(const Vector3& _v) const
{
	return GetMagnitude() < _v.GetMagnitude();
}

bool Vector3::operator<=(const Vector3& _v) const
{
	return GetMagnitude() <= _v.GetMagnitude();
}

bool Vector3::operator>(const Vector3& _v) const
{
	return GetMagnitude() > _v.GetMagnitude();
}

bool Vector3::operator>=(const Vector3& _v) const
{
	return GetMagnitude() >= _v.GetMagnitude();
}

float Vector3::DotProduct(const Vector3& _v) const
{
	return x * _v.x + y * _v.y + z * _v.z;
}

Vector3 Vector3::CrossProduct(const Vector3& _v) const
{
	return Vector3(y*_v.z - z*_v.y, z*_v.x - x*_v.z, x*_v.y - y*_v.x);
}

Vector3 Vector3::ElementWiseProduct(const Vector3& _v) const
{
	return Vector3(x * _v.x, y * _v.y, z * _v.z);
}

float Vector3::GetMagnitude() const
{
	return sqrt(x * x + y * y + z * z);
}

float Vector3::Norm() const
{
	return GetMagnitude();
}

float Vector3::SquaredNorm() const
{
	return x * x + y * y + z * z;
}

Vector3 Vector3::Add(const Vector3& _v) const
{
	return Vector3(x + _v.x, y + _v.y, z + _v.z);
}

Vector3& Vector3::AddEmplace(const Vector3& _v)
{
	x += _v.x;
	y += _v.y;
	z += _v.z;
	return *this;
}

Vector3 Vector3::Scaled(float _f) const
{
	return Vector3(x * _f, y * _f, z * _f);
}

Vector3& Vector3::Scale(float _f)
{
	x *= _f;
	y *= _f;
	z *= _f;
	return *this;
}

Vector3 Vector3::GetOpposite() const
{
	return -(*this);
}

Vector3 Vector3::Normalized() const
{
	float length = GetMagnitude();
	assert(length > 0);
	return Vector3(x / length, y / length, z / length);
}

Vector3& Vector3::Normalize()
{
	float length = GetMagnitude();
	assert(length > 0);
	x /= length;
	y /= length;
	z /= length;
	return *this;
}

Vector3 Vector3::MidPoint(const Vector3& _p1, const Vector3& _p2)
{
	return (_p1 + _p2) / 2;
}

float Vector3::Distance(const Vector3& _p1, const Vector3& _p2)
{
	return (_p2 - _p1).GetMagnitude();
}

float Vector3::AngleRadBetweenTwoVector3(const Vector3& _v1, const Vector3& _v2)
{
	float productNorms = _v1.GetMagnitude() * _v2.GetMagnitude();
	// Avoid division by zero
	if (productNorms < 0.001)
		return 0;
	float dotProduct = _v1.DotProduct(_v2);
	float angle = acosf(dotProduct / productNorms);
	return isnan(angle) ? 0 : angle;
}

float Maths::Vector3::AngleDegBetweenTwoVector3(const Vector3& _v1, const Vector3& _v2)
{
	float productNorms = _v1.GetMagnitude() * _v2.GetMagnitude();
	// Avoid division by zero
	if (productNorms < 0.001)
		return 0;
	float dotProduct = _v1.DotProduct(_v2);
	float angle = acosf(dotProduct / productNorms);
	return isnan(angle) ? 0 : angle * RAD2DEG;
}

Vector3 Maths::Vector3::GenerateRandomUnitVector3()
{
	// Generate a random point on the surface of a sphere using spherical coordinates.
	//
	// Z
	float z = 2.f * static_cast<float>(rand()) / RAND_MAX - 1.f;
	// Angles
	float theta = 2.f * static_cast<float>(rand()) / RAND_MAX * 3.14159265f;
	float phi = sqrtf(1.f - z * z);
	// X and Y
	float x = phi * cosf(theta); // x coordinate
	float y = phi * sinf(theta); // y coordinate
	return Vector3(x, y, z);
}

Vector3 Maths::Vector3::GenerateRandomOnHemisphere(const Vector3& _normal)
{
	Vector3 res = GenerateRandomUnitVector3();
	if (res.DotProduct(_normal) > 0.0f) return res;
	else return -res;
}

std::ostream& Maths::operator<<(std::ostream& _os, const Vector3& _v)
{
	return _os << _v.x << " ; " << _v.y << " ; " << _v.z;
}

std::string Maths::operator+(const std::string& _str, const Vector3& _v)
{
	std::string result = _str;
	result += "x = ";
	result += std::to_string(_v.x);
	result += ", y = ";
	result += std::to_string(_v.y);
	result += ", z = ";
	result += std::to_string(_v.z);
	return result;
}

std::string& Maths::operator+=(std::string& _str, const Vector3& _v)
{
	_str += "x = ";
	_str += std::to_string(_v.x);
	_str += ", y = ";
	_str += std::to_string(_v.y);
	_str += ", z = ";
	_str += std::to_string(_v.z);
	return _str;
}

Vector3 Maths::operator*(float _f, const Vector3& _v)
{
	return Vector3(_f * _v.x, _f * _v.y, _f * _v.z);
}

Vector3 Maths::operator/(float _f, const Vector3& _v)
{
	assert(_v.x != 0.f);
	assert(_v.y != 0.f);
	assert(_v.z != 0.f);
	return Vector3(_f / _v.x, _f / _v.y, _f / _v.z);
}

Vector3 Maths::operator+(const Vector3& _v1, const Vector3& _v2)
{
	return _v1.Add(_v2);
}

Vector3 Maths::operator+(float _f, const Vector3& _v)
{
	return Vector3(_f + _v.x, _f + _v.y, _f + _v.z);
}

Vector3 Maths::operator-(const Vector3& _v1, const Vector3& _v2)
{
	return _v1.Add(-_v2);
}

Vector3 Maths::operator-(float _f, const Vector3& _v)
{
	return Vector3(_f - _v.x, _f - _v.y, _f - _v.z);
}
