#pragma once

#include "vector/vector3.h"
#include "matrix/matrix4.h"

#include <string>

namespace Maths
{
	class Quaternion
	{
	public:
		// Public members
		float x = 0.f;
		float y = 0.f;
		float z = 0.f;
		float w = 1.f;

		// Static members
		const static Quaternion zero;
		const static Quaternion identity;

		// Constructors
		Quaternion();
		Quaternion(float _x, float _y, float _z, float _w);
		Quaternion(const Vector3& _eulerAngles);
		Quaternion(const Vector3& _axis, float _angleDeg);
		Quaternion(float _w, const Vector3& _v);
		Quaternion(float _f);
		Quaternion(const Quaternion& _copy);
		// Destructor
		~Quaternion() = default;

		// Operators
		Quaternion& operator=(const Quaternion& _copy);
		float& operator[](int _index);
		float& operator[](char _coord);
		float& operator[](const std::string& _coord);
		float operator[](int _index) const;
		float operator[](char _coord) const;
		float operator[](const std::string& _coord) const;

		Quaternion operator+(float _f) const;
		Quaternion& operator+=(const Quaternion& _v);
		Quaternion& operator-=(const Quaternion& _v);
		Quaternion operator-() const;
		Quaternion operator*(float _f) const;
		Quaternion& operator*=(float _f);
		Quaternion operator/(float _f) const;
		Quaternion& operator/=(float f_);
		void operator++(int _i);
		void operator--(int _i);
		Quaternion operator*(const Quaternion& _v) const;

		bool operator==(const Quaternion& _v) const;
		bool operator!=(const Quaternion& _v) const;
		bool operator<(const Quaternion& _v) const;
		bool operator<=(const Quaternion& _v) const;
		bool operator>(const Quaternion& _v) const;
		bool operator>=(const Quaternion& _v) const;


		// Public methods
		Quaternion Product(const Quaternion& _v) const;
		float Dot(const Quaternion& _v) const;
		Quaternion ElementWiseProduct(const Quaternion& _v) const;
		Quaternion GetOpposite() const;
		float GetMagnitude() const;
		float Norm() const;
		float SquaredNorm() const;

		Quaternion Add(const Quaternion& _v) const;
		Quaternion& AddEmplace(const Quaternion& _v);
		Quaternion Scaled(float _f) const;
		Quaternion& Scale(float _f);
		Quaternion Normalized() const;
		Quaternion& Normalize();
		Quaternion Conjugated() const;
		Quaternion& Conjugate();
		Quaternion Inversed() const;
		Quaternion& Inverse();
		Matrix4 ToRotationMatrix() const;
		Vector3 RotateVec3(const Vector3& _v) const;
		Vector3 VectorXYZ() const;

		// Static methods
		static float Distance(const Quaternion& _p1, const Quaternion& _p2);
	};

	std::ostream& operator<<(std::ostream& _os, const Quaternion& _v);
	std::string operator+(const std::string& _str, const Quaternion& _v);
	std::string& operator+=(std::string& _str, const Quaternion& _v);

	Quaternion operator*(float _f, const Quaternion& _v);
	Quaternion operator/(float _f, const Quaternion& _v);
	Quaternion operator+(const Quaternion& _v1, const Quaternion& _v2);
	Quaternion operator+(float _f, const Quaternion& _v);
	Quaternion operator-(const Quaternion& _v1, const Quaternion& _v2);
	Quaternion operator-(float _f, const Quaternion& _v);
	Vector3 operator*(const Vector3& _v, const Quaternion& _q);
}
