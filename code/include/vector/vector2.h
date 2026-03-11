#pragma once

#include <string>

namespace Maths
{
	class Vector2
	{
	public:
		// Public members
		float x = 0.f;
		float y = 0.f;

		// Static members
		const static Vector2 zero;
		const static Vector2 one;
		const static Vector2 up;
		const static Vector2 down;
		const static Vector2 left;
		const static Vector2 right;

		// Constructors
		Vector2();
		Vector2(float _x, float _y);
		Vector2(float _f);
		Vector2(const Vector2& _copy);
		// Destructor
		~Vector2() = default;

		// Operators
		Vector2& operator=(const Vector2& _copy);
		float& operator[](int _index);
		float& operator[](char _coord);
		float& operator[](const std::string& _coord);
		float operator[](int _index) const;
		float operator[](char _coord) const;
		float operator[](const std::string& _coord) const;

		Vector2 operator+(float _f) const;
		Vector2& operator+=(const Vector2& _v);
		Vector2& operator-=(const Vector2& _v);
		Vector2 operator-() const;
		Vector2 operator*(float _f) const;
		Vector2& operator*=(float _f);
		Vector2 operator/(float _f) const;
		Vector2& operator/=(float _f);
		void operator++(int _i);
		void operator--(int _i);
		float operator*(const Vector2& _v) const;

		bool operator==(const Vector2& _v) const;
		bool operator!=(const Vector2& _v) const;
		bool operator<(const Vector2& _v) const;
		bool operator<=(const Vector2& _v) const;
		bool operator>(const Vector2& _v) const;
		bool operator>=(const Vector2& _v) const;

		// Public methods
		float DotProduct(const Vector2& _v) const;
		float CrossProduct(const Vector2& _v) const;
		Vector2 GetOpposite() const;
		Vector2 ElementWiseProduct(const Vector2& _v) const;
		float GetMagnitude() const;
		float Norm() const;
		float SquaredNorm() const;

		Vector2 Add(const Vector2& _v) const;
		Vector2& AddEmplace(const Vector2& _v);
		Vector2 Scaled(float _f) const;
		Vector2& Scale(float _f);
		Vector2 Normalized() const;
		Vector2& Normalize();
		Vector2 Rotated(float _angleDeg, const Vector2& _origin = Vector2::zero) const;
		Vector2& Rotate(float _angleDeg, const Vector2& _origin = Vector2::zero);

		// Static methods
		static Vector2 MidPoint(const Vector2& _p1, const Vector2& _p2);
		static float Distance(const Vector2& _p1, const Vector2& _p2);
		static float AngleRadBetweenTwoVector2(const Vector2& _v1, const Vector2& _v2);
		static float AngleDegBetweenTwoVector2(const Vector2& _v1, const Vector2& _v2);
	};


	std::ostream& operator<<(std::ostream& _os, const Vector2& _v);
	std::string operator+(const std::string& _str, const Vector2& _v);
	std::string& operator+=(std::string& _str, const Vector2& _v);

	Vector2 operator*(float _f, const Vector2& _v);
	Vector2 operator/(float _f, const Vector2& _v);
	Vector2 operator+(const Vector2& _v1, const Vector2& _v2);
	Vector2 operator+(float _f, const Vector2& _v);
	Vector2 operator-(const Vector2& _v1, const Vector2& _v2);
	Vector2 operator-(float _f, const Vector2& _v);
}
