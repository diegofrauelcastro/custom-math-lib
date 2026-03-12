#include "math3dlib.h"

#include "vector/vector4.h"

#include <cassert>
#include <math.h>
#include <iostream>
#include <ostream>
#include <sstream>

using namespace Maths;

const Vector4 Vector4::zero = Vector4();

Vector4::Vector4()
	: x(0.f)
	, y(0.f)
	, z(0.f)
	, w(0.f)
{
}

Vector4::Vector4(float _x, float _y, float _z, float _w)
	: x(_x)
	, y(_y)
	, z(_z)
	, w(_w)
{
}

Vector4::Vector4(const Maths::Vector3& _vec3, float _w)
	: x(_vec3.x)
	, y(_vec3.y)
	, z(_vec3.z)
	, w(_w)
{
}

Vector4::Vector4(float _f)
	: x(_f)
	, y(_f)
	, z(_f)
	, w(_f)
{
}

Vector4::Vector4(const Vector4& _copy)
	: x(_copy.x)
	, y(_copy.y)
	, z(_copy.z)
	, w(_copy.w)
{
}

Vector4::operator Vector3()
{
	return Vector3(x, y, z);
}

Vector4& Vector4::operator=(const Vector4& _copy)
{
	x = _copy.x;
	y = _copy.y;
	z = _copy.z;
	w = _copy.w;
	return *this;
}

float& Vector4::operator[](int _index)
{
	assert(_index == 0 || _index == 1 || _index == 2 || _index == 3);

	if (_index == 0)
		return x;
	else if (_index == 1)
		return y;
	else if (_index == 2)
		return z;
	else
		return w;
}

float& Vector4::operator[](char _coord)
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

float& Vector4::operator[](const std::string& _coord)
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

float Vector4::operator[](int _index) const
{
	assert(_index == 0 || _index == 1 || _index == 2 || _index == 3);

	if (_index == 0)
		return x;
	else if (_index == 1)
		return y;
	else if (_index == 2)
		return z;
	else
		return w;
}

float Vector4::operator[](char _coord) const
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

float Vector4::operator[](const std::string& _coord) const
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

Vector4 Vector4::operator+(const float _f) const
{
	return Vector4(x + _f, y + _f, z + _f, w + _f);
}

Vector4& Vector4::operator+=(const Vector4& _v)
{
	AddEmplace(_v);
	return *this;
}

Vector4& Vector4::operator-=(const Vector4& _v)
{
	AddEmplace(-_v);
	return *this;
}

Vector4 Vector4::operator-() const
{
	return Vector4(-x, -y, -z, -w);
}

Vector4 Vector4::operator*(float _f) const
{
	return Scaled(_f);
}

Vector4& Vector4::operator*=(float _f)
{
	Scale(_f);
	return *this;
}

Vector4 Vector4::operator/(float _f) const
{
	assert(_f != 0.f);
	return Vector4(x / _f, y / _f, z / _f, w / _f);
}

Vector4& Vector4::operator/=(float _f)
{
	assert(_f != 0.f);
	x /= _f;
	y /= _f;
	z /= _f;
	w /= _f;
	return *this;
}

void Vector4::operator++(int _i)
{
	(void)_i;
	float length = GetMagnitude();
	assert(length > 0);
	x *= (length + 1) / length;
	y *= (length + 1) / length;
	z *= (length + 1) / length;
	w *= (length + 1) / length;
}

void Vector4::operator--(int _i)
{
	(void)_i;
	float length = GetMagnitude();
	assert(length > 0);
	x *= (length - 1) / length;
	y *= (length - 1) / length;
	z *= (length - 1) / length;
	w *= (length - 1) / length;
}

float Vector4::operator*(const Vector4& _v) const
{
	return DotProduct(_v);
}

bool Vector4::operator==(const Vector4& _v) const
{
	return GetMagnitude() == _v.GetMagnitude();
}

bool Vector4::operator!=(const Vector4& _v) const
{
	return GetMagnitude() != _v.GetMagnitude();
}

bool Vector4::operator<(const Vector4& _v) const
{
	return GetMagnitude() < _v.GetMagnitude();
}

bool Vector4::operator<=(const Vector4& _v) const
{
	return GetMagnitude() <= _v.GetMagnitude();
}

bool Vector4::operator>(const Vector4& _v) const
{
	return GetMagnitude() > _v.GetMagnitude();
}

bool Vector4::operator>=(const Vector4& _v) const
{
	return GetMagnitude() >= _v.GetMagnitude();
}

float Vector4::DotProduct(const Vector4& _v) const
{
	return x * _v.x + y * _v.y + z * _v.z + w * _v.w;
}

Vector4 Vector4::ElementWiseProduct(const Vector4& _v) const
{
	return Vector4(x * _v.x, y * _v.y, z * _v.z, w * _v.w);
}

float Vector4::GetMagnitude() const
{
	return sqrt(x*x + y*y + z*z + w*w);
}

float Vector4::Norm() const
{
	return GetMagnitude();
}

float Vector4::SquaredNorm() const
{
	return x*x + y*y + z*z + w*w;
}

Vector4 Vector4::Add(const Vector4& _v) const
{
	return Vector4(x + _v.x, y + _v.y, z + _v.z, w + _v.w);
}

Vector4& Vector4::AddEmplace(const Vector4& _v)
{
	x += _v.x;
	y += _v.y;
	z += _v.z;
	w += _v.w;
	return *this;
}

Vector4 Vector4::Scaled(float _f) const
{
	return Vector4(x * _f, y * _f, z * _f, w * _f);
}

Vector4& Vector4::Scale(float _f)
{
	x *= _f;
	y *= _f;
	z *= _f;
	w *= _f;
	return *this;
}

Vector4 Vector4::GetOpposite() const
{
	return -(*this);
}

Vector4 Vector4::Normalized() const
{
	float length = GetMagnitude();
	assert(length > 0);
	return Vector4(x / length, y / length, z / length, w / length);
}

Vector4& Vector4::Normalize()
{
	float length = GetMagnitude();
	assert(length > 0);
	x /= length;
	y /= length;
	z /= length;
	w /= length;
	return *this;
}

Vector4 Vector4::MidPoint(const Vector4& _p1, const Vector4& _p2)
{
	return (_p1 + _p2) / 2;
}

float Vector4::Distance(const Vector4& _p1, const Vector4& _p2)
{
	return (_p2 - _p1).GetMagnitude();
}

void Vector4::Homogenize()
{
	if (w != 0)
	{
		x /= w;
		y /= w;
		z /= w;
		w = 1.f;
	}
}

std::ostream& Maths::operator<<(std::ostream& _os, const Vector4& _v)
{
	return _os << _v.x << " ; " << _v.y << " ; " << _v.z << " ; " << _v.w;
}

std::string Maths::operator+(const std::string& _str, const Vector4& _v)
{
	std::string result = _str;
	result += "x = ";
	result += std::to_string(_v.x);
	result += ", y = ";
	result += std::to_string(_v.y);
	result += ", z = ";
	result += std::to_string(_v.z);
	result += ", w = ";
	result += std::to_string(_v.w);
	return result;
}

std::string& Maths::operator+=(std::string& _str, const Vector4& _v)
{
	_str += "x = ";
	_str += std::to_string(_v.x);
	_str += ", y = ";
	_str += std::to_string(_v.y);
	_str += ", z = ";
	_str += std::to_string(_v.z);
	_str += ", w = ";
	_str += std::to_string(_v.w);
	return _str;
}

Vector4 Maths::operator*(float _f, const Vector4& _v)
{
	return Vector4(_f * _v.x, _f * _v.y, _f * _v.z, _f * _v.w);
}

Vector4 Maths::operator/(float _f, const Vector4& _v)
{
	assert(_v.x != 0.f);
	assert(_v.y != 0.f);
	assert(_v.z != 0.f);
	assert(_v.w != 0.f);
	return Vector4(_f / _v.x, _f / _v.y, _f / _v.z, _f / _v.w);
}

Vector4 Maths::operator+(const Vector4& _v1, const Vector4& _v2)
{
	return _v1.Add(_v2);
}

Vector4 Maths::operator+(float _f, const Vector4& _v)
{
	return Vector4(_f + _v.x, _f + _v.y, _f + _v.z, _f + _v.w);
}

Vector4 Maths::operator-(const Vector4& _v1, const Vector4& _v2)
{
	return _v1.Add(-_v2);
}

Vector4 Maths::operator-(float _f, const Vector4& _v)
{
	return Vector4(_f - _v.x, _f - _v.y, _f - _v.z, _f - _v.w);
}
