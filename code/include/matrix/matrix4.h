#pragma once

#include "vector/vector4.h"

#include <string>

namespace Maths
{
	class Quaternion;

	class Matrix4
	{
	public:
		// Public member
		float m[16];

		// Constructors
		Matrix4();
		Matrix4(float _m[16]);
		Matrix4(const Vector4& _line1, const Vector4& _line2, const Vector4& _line3, const Vector4& _line4);
		Matrix4(const Matrix4& _copy);
		// Destructor
		~Matrix4() = default;

		// Operators
		Matrix4 operator*(const Matrix4& _m) const;
		Vector4 operator*(const Vector4& _v) const;

		Matrix4& operator=(const Matrix4& _copy);
		float& operator[](int _index);
		float operator[](int _index) const;

		// Getters
		float GetAt(unsigned int _row, unsigned int _col) const;
		// Setter
		void SetAt(unsigned int _row, unsigned int _col, float _val);

		// Public methods
		Vector4 GetDiagonal() const;
		Vector3 GetTranslation() const;
		float GetTrace() const;
		float Det() const;
		Matrix4 GetOpposite() const;
		bool IsOrthogonal() const;

		Matrix4 Transposed() const;
		Matrix4& Transpose();
		Matrix4 Add(const Matrix4& _m2) const;
		Matrix4& AddEmplace(const Matrix4& _m2);
		Matrix4 Scaled(float _f) const;
		Matrix4& Scale(float _f);
		Matrix4 Multiplied(const Matrix4& _m2) const;
		Matrix4& Multiply(const Matrix4& _m2);
		Vector4 Multiply(const Vector4& _v2) const;
		Matrix4 GaussJordan() const;		// REMAINS UNTESTED
		Matrix4& GaussJordanEmplace();		// REMAINS UNTESTED
		Matrix4& Inverse();
		Matrix4 Inversed() const;

		// Static methods
		static Matrix4 Identity();
		static Matrix4 CreateTransformMatrix(const Vector3& _position, const Vector3& _rotationDeg, const Vector3& _scale);
		static Matrix4 CreateTransformMatrix(const Vector3& _position, const Quaternion& _rotation, const Vector3& _scale);
		static Matrix4 CreateTranslationMatrix(const Vector3& _translation);
		static Matrix4 CreateScaleMatrix(const Vector3& _scale);
		static Matrix4 CreateXRotationMatrix(float _angleDeg);
		static Matrix4 CreateYRotationMatrix(float _angleDeg);
		static Matrix4 CreateZRotationMatrix(float _angleDeg);
		static Vector3 RotatePointAroundThreeAxis(Vector3& _anglesDegPerAxis, const Vector3& _p, const Vector3 _anchor = Vector3(0.f, 0.f, 0.f));
		static Vector4 RotatePointAroundThreeAxis(Vector3& _anglesDegPerAxis, const Vector4& _p, const Vector3 _anchor = Vector3(0.f, 0.f, 0.f));
	};

	std::ostream& operator<<(std::ostream& _os, const Matrix4& _m);
}
