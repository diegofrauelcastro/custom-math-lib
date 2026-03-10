#include "math3dlib.h"

#include "vector/vectornd.h"

#include <cassert>
#include <math.h>
#include <iostream>
#include <ostream>
#include <sstream>

using namespace Maths;

VectorND::VectorND(unsigned int _numDimensions, float _f)
	: numDimension(_numDimensions)
	, values()
{
	values = std::vector<float>(numDimension, _f);
}

VectorND::VectorND(const VectorND& _copy)
	: numDimension(_copy.numDimension)
	, values(_copy.values)
{
}

VectorND& VectorND::operator=(const VectorND& _copy)
{
	numDimension = _copy.numDimension;
	values = _copy.values;
	return *this;
}

float& VectorND::operator[](unsigned int _index)
{
	assert(_index >= 0 && _index < numDimension);
	return values[_index];
}

float VectorND::operator[](unsigned int _index) const
{
	assert(_index >= 0 && _index < numDimension);
	return values[_index];
}

VectorND VectorND::operator+(const float _f) const
{
	VectorND res(*this);
	for (float val : res.values)
		val += _f;
	return res;
}

VectorND& VectorND::operator+=(const VectorND& _v)
{
	Add(_v);
	return *this;
}

VectorND& VectorND::operator-=(const VectorND& _v)
{
	Add(-_v);
	return *this;
}

VectorND VectorND::operator-() const
{
	VectorND res(*this);
	for (float val : res.values)
		val = -val;
	return res;
}

VectorND VectorND::operator*(float _f) const
{
	return Scaled(_f);
}

VectorND& VectorND::operator*=(float _f)
{
	Scale(_f);
	return *this;
}

VectorND VectorND::operator/(float _f) const
{
	assert(fabs(_f) > 0.000001f);
	VectorND res(*this);
	for (float val : res.values)
		val /= _f;
	return res;
}

VectorND& VectorND::operator/=(float _f)
{
	assert(fabs(_f) > 0.000001f);
	for (float val : values)
		val /= _f;
	return *this;
}

void VectorND::operator++(int _i)
{
	(void)_i;
	float length = GetMagnitude();
	assert(fabs(length) > 0.000001f);
	for (float val : values)
		val *= (length + 1) / length;
}

void VectorND::operator--(int _i)
{
	(void)_i;
	float length = GetMagnitude();
	assert(fabs(length) > 0.000001f);
	for (float val : values)
		val *= (length - 1) / length;
}

float VectorND::operator*(const VectorND& _v) const
{
	return DotProduct(_v);
}

bool VectorND::operator==(const VectorND& _v) const
{
	return GetMagnitude() == _v.GetMagnitude();
}

bool VectorND::operator!=(const VectorND& _v) const
{
	return GetMagnitude() != _v.GetMagnitude();
}

bool VectorND::operator<(const VectorND& _v) const
{
	return GetMagnitude() < _v.GetMagnitude();
}

bool VectorND::operator<=(const VectorND& _v) const
{
	return GetMagnitude() <= _v.GetMagnitude();
}

bool VectorND::operator>(const VectorND& _v) const
{
	return GetMagnitude() > _v.GetMagnitude();
}

bool VectorND::operator>=(const VectorND& _v) const
{
	return GetMagnitude() >= _v.GetMagnitude();
}

float VectorND::DotProduct(const VectorND& _v) const
{
	float res = 0;
	assert(_v.numDimension == numDimension);
	for (unsigned int i = 0; i < numDimension; i++)
		res += values[i]*_v[i];
	return res;
}

VectorND VectorND::ElementWiseProduct(const VectorND& _v) const
{
	VectorND res = _v;
	assert(_v.numDimension == numDimension);
	for (unsigned int i = 0; i < numDimension; i++)
		res[i] *= values[i];
	return res;
}

float VectorND::GetMagnitude() const
{
	return sqrt(SquaredNorm());
}

float VectorND::SquaredNorm() const
{
	float res = 0;
	for (float val : values)
		res += val * val;
	return res;
}

VectorND VectorND::Add(const VectorND& _v) const
{
	VectorND res = *this;
	assert(_v.numDimension == numDimension);
	for (unsigned int i = 0; i < numDimension; i++)
		res[i] += _v[i];
	return res;
}

VectorND& VectorND::AddEmplace(const VectorND& _v)
{
	assert(_v.numDimension == numDimension);
	for (unsigned int i = 0; i < numDimension; i++)
		values[i] += _v[i];
	return *this;
}

VectorND VectorND::Scaled(float _f) const
{
	VectorND res = *this;
	for (unsigned int i = 0; i < numDimension; i++)
		res[i] *= _f;
	return res;
}

VectorND& VectorND::Scale(float _f)
{
	for (unsigned int i = 0; i < numDimension; i++)
		values[i] *= _f;
	return *this;
}

VectorND VectorND::GetOpposite() const
{
	return -(*this);
}

VectorND VectorND::Normalized() const
{
	VectorND res = *this;
	float length = GetMagnitude();
	assert(fabs(length) > 0.000001f);
	for (float val : res.values)
		val /= length;
	return res;
}

VectorND& VectorND::Normalize()
{
	float length = GetMagnitude();
	assert(fabs(length) > 0.000001f);
	for (float val : values)
		val *= (length - 1) / length;
	return *this;
}

VectorND VectorND::MidPoint(const VectorND& _p1, const VectorND& _p2)
{
	return (_p1 + _p2) / 2;
}

float VectorND::Distance(const VectorND& _p1, const VectorND& _p2)
{
	return (_p2 - _p1).GetMagnitude();
}

float VectorND::GetAt(unsigned int _index) const
{
	return values[_index];
}

unsigned int VectorND::GetDimension() const
{
	return numDimension;
}

void VectorND::SetAt(unsigned int _index, float _value)
{
	values[_index] = _value;
}

std::ostream& Maths::operator<<(std::ostream& _os, const VectorND& _v)
{
	std::stringstream res;
	for (unsigned int i = 0; i < _v.GetDimension(); i++)
	{
		res << _v[i];
		if (i < _v.GetDimension() - 1)
			res << " ; ";
	}
	return _os << res.str();
}

VectorND Maths::operator*(float _f, const VectorND& _v)
{
	VectorND res = _v;
	for (unsigned int i = 0; i < res.GetDimension(); i++)
		res[i] = res[i] * _f;
	return res;
}

VectorND Maths::operator/(float _f, const VectorND& _v)
{
	VectorND res = _v;
	for (unsigned int i = 0; i < res.GetDimension(); i++)
	{
		assert(fabs(res[i]) > 0.000001f);
		res[i] = _f / res[i];
	}
	return res;
}

VectorND Maths::operator+(const VectorND& _v1, const VectorND& _v2)
{
	return _v1.Add(_v2);
}

VectorND Maths::operator+(float _f, const VectorND& _v)
{
	VectorND res = _v;
	for (unsigned int i = 0; i < res.GetDimension(); i++)
		res[i] = _f + res[i];
	return res;
}

VectorND Maths::operator-(const VectorND& _v1, const VectorND& _v2)
{
	return _v1.Add(-_v2);
}

VectorND Maths::operator-(float _f, const VectorND& _v)
{
	VectorND res = _v;
	for (unsigned int i = 0; i < res.GetDimension(); i++)
		res[i] = _f - res[i];
	return res;
}
