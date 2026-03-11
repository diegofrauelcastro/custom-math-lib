#pragma once

#include "vector/vector2.h"

#include <string>

namespace Maths
{
	class Matrix2
	{
	public:
		// Public member
		float m[4];

		// Constructors
		Matrix2(float _m[4]);
		Matrix2(float _f = 0.f);
		Matrix2(const Matrix2& _copy);
		Matrix2(const Vector2& _line1, const Vector2& _line2);
		// Destructor
		~Matrix2() = default;

		// Operators
		Matrix2 operator*(const Matrix2& _m) const;
		Vector2 operator*(const Vector2& _v) const;

		Matrix2& operator=(const Matrix2& _copy);
		bool operator==(const Matrix2& _other) const;
		float& operator[](unsigned int _index);
		float operator[](unsigned int _index) const;

		// Getters
		float GetAt(unsigned int _row, unsigned int _col) const;
		// Setter
		void SetAt(unsigned int _row, unsigned int _col, float _val);

		// Public methods
		Vector2 GetDiagonal() const;
		float GetTrace() const;
		float Det() const;
		Matrix2 GetOpposite() const;

		Matrix2 Transposed() const;
		Matrix2& Transpose();
		Matrix2 Add(const Matrix2& _m2) const;
		Matrix2& AddEmplace(const Matrix2& _m2);
		Matrix2 Scaled(float _f) const;
		Matrix2& Scale(float _f);
		Matrix2 Multiplied(const Matrix2& _m2) const;
		Matrix2& Multiply(const Matrix2& _m2);
		Vector2 Multiply(const Vector2& _v2) const;
		Matrix2 GaussJordan() const;		// REMAINS UNTESTED
		Matrix2& GaussJordanEmplace();		// REMAINS UNTESTED

		// Static methods
		static Matrix2 Identity();
		static Matrix2 CreateScaleMatrix(const Vector2& _scale);
		static Matrix2 CreateRotationMatrix(float _angleDeg);
		static Vector2 RotatePointAroundAnchor(float _angleDeg, const Vector2& _p, const Vector2& _anchor = Vector2(0.f, 0.f));
	};

	std::ostream& operator<<(std::ostream& _os, const Matrix2& _m);
}
