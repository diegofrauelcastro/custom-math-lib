#include "math3dlib.h"

#include "vector/vector2.h"

#include <cassert>
#include <math.h>
#include <iostream>
#include <ostream>
#include <sstream>
#include <cmath>

using namespace Maths;

const Vector2 Vector2::zero = Vector2();
const Vector2 Vector2::one = Vector2(1.f, 1.f);
const Vector2 Vector2::right = Vector2(1.f, 0.f);
const Vector2 Vector2::left = Vector2(- 1.f, 0.f);
const Vector2 Vector2::up = Vector2(1.f, 0.f);
const Vector2 Vector2::down = Vector2(-1.f, 0.f);

Vector2::Vector2()
	: x(0.f)
	, y(0.f)
{
}

Vector2::Vector2(float _x, float _y)
	: x(_x)
	, y(_y)
{
}

Vector2::Vector2(float _f)
	: x(_f)
	, y(_f)
{
}

Vector2::Vector2(const Vector2& _copy)
	: x(_copy.x)
	, y(_copy.y)
{
}

Vector2& Vector2::operator=(const Vector2& _copy)
{
	x = _copy.x;
	y = _copy.y;
	return *this;
}

float& Vector2::operator[](int _index)
{
	assert(_index == 0 || _index == 1);

	if (_index == 0)
		return x;
	else
		return y;
}

float& Vector2::operator[](char _coord)
{
	assert(_coord == 'x' || _coord == 'y');

	if (_coord == 'x')
		return x;
	else
		return y;
}

float& Vector2::operator[](const std::string& _coord)
{
	assert(_coord == "x" || _coord == "y");

	if (_coord == "x")
		return x;
	else
		return y;
}

float Vector2::operator[](int _index) const
{
	assert(_index == 0 || _index == 1);

	if (_index == 0)
		return x;
	else
		return y;
}

float Vector2::operator[](char _coord) const
{
	assert(_coord == 'x' || _coord == 'y');

	if (_coord == 'x')
		return x;
	else
		return y;
}

float Vector2::operator[](const std::string& _coord) const
{
	assert(_coord == "x" || _coord == "y");

	if (_coord == "x")
		return x;
	else
		return y;
}

Vector2 Vector2::operator+(const float _f) const
{
	return Vector2(x + _f, y + _f);
}

Vector2& Vector2::operator+=(const Vector2& _v)
{
	AddEmplace(_v);
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& _v)
{
	AddEmplace(-_v);
	return *this;
}

Vector2 Vector2::operator-() const
{
	return Vector2(-x, -y);
}

Vector2 Vector2::operator*(float _f) const
{
	return Scaled(_f);
}

Vector2& Vector2::operator*=(float _f)
{
	Scale(_f);
	return *this;
}

Vector2 Vector2::operator/(float _f) const
{
	assert(_f != 0.f);
	return Vector2(x / _f, y / _f);
}

Vector2& Vector2::operator/=(float _f)
{
	assert(_f != 0.f);
	x /= _f;
	y /= _f;
	return *this;
}

void Vector2::operator++(int _i)
{
	(void)_i;
	float length = GetMagnitude();
	assert(length > 0);
	x *= (length + 1) / length;
	y *= (length + 1) / length;
}

void Vector2::operator--(int _i)
{
	(void)_i;
	float length = GetMagnitude();
	assert(length > 0);
	x *= (length - 1) / length;
	y *= (length - 1) / length;
}

float Vector2::operator*(const Vector2& _v) const
{
	return DotProduct(_v);
}

bool Vector2::operator==(const Vector2& _v) const
{
	return GetMagnitude() == _v.GetMagnitude();
}

bool Vector2::operator!=(const Vector2& _v) const
{
	return GetMagnitude() != _v.GetMagnitude();
}

bool Vector2::operator<(const Vector2& _v) const
{
	return GetMagnitude() < _v.GetMagnitude();
}

bool Vector2::operator<=(const Vector2& _v) const
{
	return GetMagnitude() <= _v.GetMagnitude();
}

bool Vector2::operator>(const Vector2& _v) const
{
	return GetMagnitude() > _v.GetMagnitude();
}

bool Vector2::operator>=(const Vector2& _v) const
{
	return GetMagnitude() >= _v.GetMagnitude();
}

float Vector2::DotProduct(const Vector2& _v) const
{
	return x * _v.x + y * _v.y;
}

float Vector2::CrossProduct(const Vector2& _v) const
{
	return x * _v.y - y * _v.x;
}

Vector2 Vector2::ElementWiseProduct(const Vector2& _v) const
{
	return Vector2(x * _v.x, y * _v.y);
}

float Vector2::GetMagnitude() const
{
	return sqrt(x * x + y * y);
}

float Vector2::Norm() const
{
	return GetMagnitude();
}

float Vector2::SquaredNorm() const
{
	return x * x + y * y;
}

Vector2 Vector2::Add(const Vector2& _v) const
{
	return Vector2(x + _v.x, y + _v.y);
}

Vector2& Vector2::AddEmplace(const Vector2& _v)
{
	x += _v.x;
	y += _v.y;
	return *this;
}

Vector2 Vector2::Scaled(float _f) const
{
	return Vector2(x * _f, y * _f);
}

Vector2& Vector2::Scale(float _f)
{
	x *= _f;
	y *= _f;
	return *this;
}

Vector2 Vector2::GetOpposite() const
{
	return -(*this);
}

Vector2 Vector2::Normalized() const
{
	float length = GetMagnitude();
	assert(length > 0);
	return Vector2(x / length, y / length);
}

Vector2& Vector2::Normalize()
{
	float length = GetMagnitude();
	assert(length > 0);
	x /= length;
	y /= length;
	return *this;
}

Vector2 Vector2::Rotated(float _angleDeg, const Vector2& _origin) const
{
	_angleDeg *= DEG2RAD;
	float newX = cosf(_angleDeg) * (x - _origin.x) - sinf(_angleDeg) * (y - _origin.y) + _origin.x;
	float newY = sinf(_angleDeg) * (x - _origin.x) + cosf(_angleDeg) * (y - _origin.y) + _origin.y;
	return Vector2(newX, newY);
}

Vector2& Vector2::Rotate(float _angleDeg, const Vector2& _origin)
{
	_angleDeg *= DEG2RAD;
	float oldX = x; float oldY = y;
	x = cosf(_angleDeg) * (oldX - _origin.x) - sinf(_angleDeg) * (oldY - _origin.y) + _origin.x;
	y = sinf(_angleDeg) * (oldX - _origin.x) + cosf(_angleDeg) * (oldY - _origin.y) + _origin.y;
	return *this;
}

Vector2 Vector2::MidPoint(const Vector2& _p1, const Vector2& _p2)
{
	return (_p1 + _p2) / 2;
}

float Vector2::Distance(const Vector2& _p1, const Vector2& _p2)
{
	return (_p2 - _p1).GetMagnitude();
}

float Vector2::AngleDegBetweenTwoVector2(const Vector2& _v1, const Vector2& _v2)
{
	float productNorms = _v1.GetMagnitude() * _v2.GetMagnitude();
	// Avoid division by zero
	if (productNorms < 0.001)
		return 0;
	float dotProduct = _v1.DotProduct(_v2);
	float angle = acosf(dotProduct / productNorms);
	return isnan(angle) ? 0 : (angle*RAD2DEG);
}
float Vector2::AngleRadBetweenTwoVector2(const Vector2& _v1, const Vector2& _v2)
{
	float productNorms = _v1.GetMagnitude() * _v2.GetMagnitude();
	// Avoid division by zero
	if (productNorms < 0.001)
		return 0;
	float dotProduct = _v1.DotProduct(_v2);
	float angle = acosf(dotProduct / productNorms);
	return isnan(angle) ? 0 : angle;
}

std::ostream& Maths::operator<<(std::ostream& _os, const Vector2& _v)
{
	return _os << _v.x << " ; " << _v.y;
}

std::string Maths::operator+(const std::string& _str, const Vector2& _v)
{
	std::string result = _str;
	result += "x = ";
	result += std::to_string(_v.x);
	result += ", y = ";
	result += std::to_string(_v.y);
	return result;
}

std::string& Maths::operator+=(std::string& _str, const Vector2& _v)
{
	_str += "x = ";
	_str += std::to_string(_v.x);
	_str += ", y = ";
	_str += std::to_string(_v.y);
	return _str;
}

Vector2 Maths::operator*(float _f, const Vector2& _v)
{
	return Vector2(_f * _v.x, _f * _v.y);
}

Vector2 Maths::operator/(float _f, const Vector2& _v)
{
	assert(_v.x != 0.f);
	assert(_v.y != 0.f);
	return Vector2(_f / _v.x, _f / _v.y);
}

Vector2 Maths::operator+(const Vector2& _v1, const Vector2& _v2)
{
	return _v1.Add(_v2);
}

Vector2 Maths::operator+(float _f, const Vector2& _v)
{
	return Vector2(_f + _v.x, _f + _v.y);
}

Vector2 Maths::operator-(const Vector2& _v1, const Vector2& _v2)
{
	return _v1.Add(-_v2);
}

Vector2 Maths::operator-(float _f, const Vector2& _v)
{
	return Vector2(_f - _v.x, _f - _v.y);
}
