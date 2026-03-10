#include "vector4.h"
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

Vector4::Vector4(const Maths::Vector3& vec3, float _w)
	: x(vec3.x)
	, y(vec3.y)
	, z(vec3.z)
	, w(_w)
{
}

Vector4::Vector4(float f)
	: x(f)
	, y(f)
	, z(f)
	, w(f)
{
}

Vector4::Vector4(const Vector4& copy)
	: x(copy.x)
	, y(copy.y)
	, z(copy.z)
	, w(copy.w)
{
}

Vector4::operator Vector3()
{
	return Vector3(x, y, z);
}

Vector4& Vector4::operator=(const Vector4& copy)
{
	x = copy.x;
	y = copy.y;
	z = copy.z;
	w = copy.w;
	return *this;
}

float& Vector4::operator[](int index)
{
	assert(index == 0 || index == 1 || index == 2 || index == 3);

	if (index == 0)
		return x;
	else if (index == 1)
		return y;
	else if (index == 2)
		return z;
	else
		return w;
}

float& Vector4::operator[](char coord)
{
	assert(coord == 'x' || coord == 'y' || coord == 'z' || coord == 'w');

	if (coord == 'x')
		return x;
	else if (coord == 'y')
		return y;
	else if (coord == 'z')
		return z;
	else
		return w;
}

float& Vector4::operator[](const std::string& coord)
{
	assert(coord == "x" || coord == "y" || coord == "z" || coord == "w");

	if (coord == "x")
		return x;
	else if (coord == "y")
		return y;
	else if (coord == "z")
		return z;
	else
		return w;
}

float Vector4::operator[](int index) const
{
	assert(index == 0 || index == 1 || index == 2 || index == 3);

	if (index == 0)
		return x;
	else if (index == 1)
		return y;
	else if (index == 2)
		return z;
	else
		return w;
}

float Vector4::operator[](char coord) const
{
	assert(coord == 'x' || coord == 'y' || coord == 'z' || coord == 'w');

	if (coord == 'x')
		return x;
	else if (coord == 'y')
		return y;
	else if (coord == 'z')
		return z;
	else
		return w;
}

float Vector4::operator[](const std::string& coord) const
{
	assert(coord == "x" || coord == "y" || coord == "z" || coord == "w");

	if (coord == "x")
		return x;
	else if (coord == "y")
		return y;
	else if (coord == "z")
		return z;
	else
		return w;
}

Vector4 Vector4::operator+(const float f) const
{
	return Vector4(x + f, y + f, z + f, w + f);
}

Vector4& Vector4::operator+=(const Vector4& v)
{
	Add(v);
	return *this;
}

Vector4& Vector4::operator-=(const Vector4& v)
{
	Add(-v);
	return *this;
}

Vector4 Vector4::operator-() const
{
	return Vector4(-x, -y, -z, -w);
}

Vector4 Vector4::operator*(float f) const
{
	return Scaled(f);
}

Vector4& Vector4::operator*=(float f)
{
	Scale(f);
	return *this;
}

Vector4 Vector4::operator/(float f) const
{
	assert(f != 0.f);
	return Vector4(x / f, y / f, z / f, w / f);
}

Vector4& Vector4::operator/=(float f)
{
	assert(f != 0.f);
	x /= f;
	y /= f;
	z /= f;
	w /= f;
	return *this;
}

void Vector4::operator++(int i)
{
	(void)i;
	float length = GetMagnitude();
	assert(length > 0);
	x *= (length + 1) / length;
	y *= (length + 1) / length;
	z *= (length + 1) / length;
	w *= (length + 1) / length;
}

void Vector4::operator--(int i)
{
	(void)i;
	float length = GetMagnitude();
	assert(length > 0);
	x *= (length - 1) / length;
	y *= (length - 1) / length;
	z *= (length - 1) / length;
	w *= (length - 1) / length;
}

float Vector4::operator*(const Vector4& v) const
{
	return DotProduct(v);
}

bool Vector4::operator==(const Vector4& v) const
{
	return GetMagnitude() == v.GetMagnitude();
}

bool Vector4::operator!=(const Vector4& v) const
{
	return GetMagnitude() != v.GetMagnitude();
}

bool Vector4::operator<(const Vector4& v) const
{
	return GetMagnitude() < v.GetMagnitude();
}

bool Vector4::operator<=(const Vector4& v) const
{
	return GetMagnitude() <= v.GetMagnitude();
}

bool Vector4::operator>(const Vector4& v) const
{
	return GetMagnitude() > v.GetMagnitude();
}

bool Vector4::operator>=(const Vector4& v) const
{
	return GetMagnitude() >= v.GetMagnitude();
}

float Vector4::DotProduct(const Vector4& v) const
{
	return x * v.x + y * v.y + z * v.z + w * v.w;
}

Vector4 Vector4::ElementWiseProduct(const Vector4& v) const
{
	return Vector4(x * v.x, y * v.y, z * v.z, w * v.w);
}

float Vector4::GetMagnitude() const
{
	return sqrt(SquaredNorm());
}

float Vector4::Norm() const
{
	return GetMagnitude();
}

float Vector4::SquaredNorm(bool homogenize) const
{
	Vector4 tempV = *this;
	if (homogenize)
		tempV.Homogenize();
	return tempV.x * tempV.x + tempV.y * tempV.y + tempV.z * tempV.z;
}

Vector4 Vector4::Add(const Vector4& v) const
{
	return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
}

Vector4& Vector4::AddEmplace(const Vector4& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

Vector4 Vector4::Scaled(float f) const
{
	return Vector4(x * f, y * f, z * f, w * f);
}

Vector4& Vector4::Scale(float f)
{
	x *= f;
	y *= f;
	z *= f;
	w *= f;
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

Vector4 Vector4::MidPoint(const Vector4& p1, const Vector4& p2)
{
	return (p1 + p2) / 2;
}

float Vector4::Distance(const Vector4& p1, const Vector4& p2)
{
	return (p2 - p1).GetMagnitude();
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

std::ostream& Maths::operator<<(std::ostream& os, const Vector4& v)
{
	return os << v.x << " ; " << v.y << " ; " << v.z << " ; " << v.w;
}

std::string Maths::operator+(const std::string& str, const Vector4& v)
{
	std::string result = str;
	result += "x = ";
	result += std::to_string(v.x);
	result += ", y = ";
	result += std::to_string(v.y);
	result += ", z = ";
	result += std::to_string(v.z);
	result += ", w = ";
	result += std::to_string(v.w);
	return result;
}

std::string& Maths::operator+=(std::string& str, const Vector4& v)
{
	str += "x = ";
	str += std::to_string(v.x);
	str += ", y = ";
	str += std::to_string(v.y);
	str += ", z = ";
	str += std::to_string(v.z);
	str += ", w = ";
	str += std::to_string(v.w);
	return str;
}

Vector4 Maths::operator*(float f, const Vector4& v)
{
	return Vector4(f * v.x, f * v.y, f * v.z, f * v.w);
}

Vector4 Maths::operator/(float f, const Vector4& v)
{
	assert(v.x != 0.f);
	assert(v.y != 0.f);
	assert(v.z != 0.f);
	assert(v.w != 0.f);
	return Vector4(f / v.x, f / v.y, f / v.z, f / v.w);
}

Vector4 Maths::operator+(const Vector4& v1, const Vector4& v2)
{
	return v1.Add(v2);
}

Vector4 Maths::operator+(float f, const Vector4& v)
{
	return Vector4(f + v.x, f + v.y, f + v.z, f + v.w);
}

Vector4 Maths::operator-(const Vector4& v1, const Vector4& v2)
{
	return v1.Add(-v2);
}

Vector4 Maths::operator-(float f, const Vector4& v)
{
	return Vector4(f - v.x, f - v.y, f - v.z, f - v.w);
}
