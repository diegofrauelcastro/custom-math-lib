#pragma once

#include "vector/vector3.h"
#include "vector/vector2.h"

#include <string>

namespace Maths
{
	class Matrix3
	{
	public:
		// Public member
		float m[9];

		// Constructors
		Matrix3(float _m[9]);
		Matrix3(float _f = 0.f);
		Matrix3(const Matrix3& _copy);
		Matrix3(const Vector3& _line1, const Vector3& _line2, const Vector3& _line3);
		// Destructor
		~Matrix3() = default;

		// Operators
		Matrix3 operator*(const Matrix3& _m) const;
		Vector3 operator*(const Vector3& _v) const;

		Matrix3& operator=(const Matrix3& _copy);
		bool operator==(const Matrix3& _other) const;
		float& operator[](unsigned int _index);
		float operator[](unsigned int _index) const;

		// Getters
		float GetAt(unsigned int _row, unsigned int _col) const;
		// Setter
		void SetAt(unsigned int _row, unsigned int _col, float _val);

		// Public methods
		Vector3 GetDiagonal() const;
		float GetTrace() const;
		float Det() const;
		Matrix3 GetOpposite() const;

		Matrix3 Transposed() const;
		Matrix3& Transpose();
		Matrix3 Add(const Matrix3& _m2) const;
		Matrix3& AddEmplace(const Matrix3& _m2);
		Matrix3 Scaled(float _f) const;
		Matrix3& Scale(float _f);
		Matrix3 Multiplied(const Matrix3& _m2) const;
		Matrix3& Multiply(const Matrix3& _m2);
		Vector3 Multiply(const Vector3& _v2) const;
		Matrix3 GaussJordan() const;
		Matrix3& GaussJordanEmplace();

		static Matrix3 Identity();
		static Matrix3 CreateTranslationMatrix(const Vector2& _translation);
		static Matrix3 CreateScaleMatrix(const Vector2& _scale);
		static Matrix3 CreateXRotationMatrix(float _angleDeg);
		static Matrix3 CreateYRotationMatrix(float _angleDeg);
		static Matrix3 CreateZRotationMatrix(float _angleDeg);
	};

	std::ostream& operator<<(std::ostream& _os, const Matrix3& _m);
}
