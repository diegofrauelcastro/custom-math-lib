#pragma once

#include "vector/vector3.h"

#include <string>

namespace Maths
{
	class Vector4
	{
	public:
		// Public members
		float x = 0.f;
		float y = 0.f;
		float z = 0.f;
		float w = 0.f;

		// Static members
		const static Vector4 zero;

		// Constructors
		Vector4();
		Vector4(float _x, float _y, float _z, float _w);
		Vector4(const Vector3& _vec3, float _w = 1.0f);
		Vector4(float _f);
		Vector4(const Vector4& _copy);
		// Destructor
		~Vector4() = default;

		// Operators
		operator Vector3();
		Vector4& operator=(const Vector4& _copy);
		float& operator[](int _index);
		float& operator[](char _coord);
		float& operator[](const std::string& _coord);
		float operator[](int _index) const;
		float operator[](char _coord) const;
		float operator[](const std::string& _coord) const;

		Vector4 operator+(float _f) const;
		Vector4& operator+=(const Vector4& _v);
		Vector4& operator-=(const Vector4& _v);
		Vector4 operator-() const;
		Vector4 operator*(float _f) const;
		Vector4& operator*=(float _f);
		Vector4 operator/(float _f) const;
		Vector4& operator/=(float _f);
		void operator++(int _i);
		void operator--(int _i);
		float operator*(const Vector4& _v) const;

		bool operator==(const Vector4& _v) const;
		bool operator!=(const Vector4& _v) const;
		bool operator<(const Vector4& _v) const;
		bool operator<=(const Vector4& _v) const;
		bool operator>(const Vector4& _v) const;
		bool operator>=(const Vector4& _v) const;

		// Public methods
		float DotProduct(const Vector4& _v) const;
		Vector4 GetOpposite() const;
		Vector4 ElementWiseProduct(const Vector4& _v) const;
		float GetMagnitude() const;
		float Norm() const;
		float SquaredNorm(bool _homogenize = false) const;

		Vector4 Add(const Vector4& _v) const;
		Vector4& AddEmplace(const Vector4& _v);
		Vector4 Scaled(float _f) const;
		Vector4& Scale(float _f);
		Vector4 Normalized() const;
		Vector4& Normalize();
		void Homogenize();

		// Static methods
		static Vector4 MidPoint(const Vector4& _p1, const Vector4& _p2);
		static float Distance(const Vector4& _p1, const Vector4& _p2);
	};

	std::ostream& operator<<(std::ostream& _os, const Vector4& _v);
	std::string operator+(const std::string& _str, const Vector4& _v);
	std::string& operator+=(std::string& _str, const Vector4& _v);

	Vector4 operator*(float _f, const Vector4& _v);
	Vector4 operator/(float _f, const Vector4& _v);
	Vector4 operator+(const Vector4& _v1, const Vector4& _v2);
	Vector4 operator+(float _f, const Vector4& _v);
	Vector4 operator-(const Vector4& _v1, const Vector4& _v2);
	Vector4 operator-(float _f, const Vector4& _v);
}
