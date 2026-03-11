#pragma once

#include <string>

namespace Maths
{
	class Vector3
	{
	public:
		// Public members
		float x = 0.f;
		float y = 0.f;
		float z = 0.f;

		// Static members
		const static Vector3 zero;
		const static Vector3 one;
		const static Vector3 right;
		const static Vector3 left;
		const static Vector3 up;
		const static Vector3 down;
		const static Vector3 forward;
		const static Vector3 back;

		// Constructors
		Vector3();
		Vector3(float _x, float _y, float _z);
		Vector3(float _f);
		Vector3(const Vector3& _copy);
		// Destructor
		~Vector3() = default;

		// Operators
		Vector3& operator=(const Vector3& _copy);
		float& operator[](int _index);
		float& operator[](char _coord);
		float& operator[](const std::string& _coord);
		float operator[](int _index) const;
		float operator[](char _coord) const;
		float operator[](const std::string& _coord) const;

		Vector3 operator+(float _f) const;
		Vector3& operator+=(const Vector3& _v);
		Vector3& operator-=(const Vector3& v_);
		Vector3 operator-() const;
		Vector3 operator*(float _f) const;
		Vector3& operator*=(float _f);
		Vector3 operator/(float _f) const;
		Vector3& operator/=(float _f);
		void operator++(int _i);
		void operator--(int _i);
		float operator*(const Vector3& _v) const;

		bool operator==(const Vector3& _v) const;
		bool operator!=(const Vector3& _v) const;
		bool operator<(const Vector3& _v) const;
		bool operator<=(const Vector3& _v) const;
		bool operator>(const Vector3& _v) const;
		bool operator>=(const Vector3& _v) const;

		// Public methods
		float DotProduct(const Vector3& _v) const;
		Vector3 CrossProduct(const Vector3& _v) const;
		Vector3 GetOpposite() const;
		Vector3 ElementWiseProduct(const Vector3& _v) const;
		float GetMagnitude() const;
		float Norm() const;
		float SquaredNorm() const;

		Vector3 Add(const Vector3& _v) const;
		Vector3& AddEmplace(const Vector3& _v);
		Vector3 Scaled(float _f) const;
		Vector3& Scale(float _f);
		Vector3 Normalized() const;
		Vector3& Normalize();

		// Static methods
		static Vector3 MidPoint(const Vector3& _p1, const Vector3& _p2);
		static float Distance(const Vector3& _p1, const Vector3& _p2);
		static float AngleRadBetweenTwoVector3(const Vector3& _v1, const Vector3& _v2);
		static float AngleDegBetweenTwoVector3(const Vector3& _v1, const Vector3& _v2);
		static Vector3 GenerateRandomUnitVector3();
		static Vector3 GenerateRandomOnHemisphere(const Vector3& _normal);
	};

	std::ostream& operator<<(std::ostream& _os, const Vector3& _v);
	std::string operator+(const std::string& _str, const Vector3& _v);
	std::string& operator+=(std::string& _str, const Vector3& v);

	Vector3 operator*(float _f, const Vector3& _v);
	Vector3 operator/(float _f, const Vector3& _v);
	Vector3 operator+(const Vector3& _v1, const Vector3& _v2);
	Vector3 operator+(float _f, const Vector3& _v);
	Vector3 operator-(const Vector3& _v1, const Vector3& _v2);
	Vector3 operator-(float _f, const Vector3& _v);
}
