#pragma once

#include "vector/vectornd.h"
#include "vector/vector2.h"
#include "matrix/matrix3.h"
#include "matrix/matrix4.h"

#include <vector>
#include <string>

namespace Maths
{
	class MatrixMxN
	{
	public:
		// Constructors
		MatrixMxN() = delete;
		MatrixMxN(unsigned int _m, unsigned int _n, float _f = 0.f);
		MatrixMxN(Vector2 _dimensions, float _f = 0.f);
		MatrixMxN(const MatrixMxN& _copy);
		MatrixMxN(const Maths::Matrix3& _m3);
		MatrixMxN(const Maths::Matrix4& _m4);
		// Destructor
		~MatrixMxN() = default;

		// Operators
		MatrixMxN operator*(const MatrixMxN& _m) const;
		VectorND operator*(const VectorND& _v) const;

		MatrixMxN& operator=(const MatrixMxN& _copy);
		bool operator==(const MatrixMxN& _other) const;
		float& operator[](unsigned int _index);
		float operator[](unsigned int _index) const;

		// Getters
		float GetAt(unsigned int _row, unsigned int _col) const;
		Vector2 GetDimensions() const;
		// Setter
		void SetAt(unsigned int _row, unsigned int _col, float _val);

		// Public methods
		VectorND GetDiagonal() const;
		float GetTrace() const;
		MatrixMxN GetOpposite() const;

		MatrixMxN Transposed() const;
		MatrixMxN& Transpose();
		MatrixMxN Add(const MatrixMxN& m2) const;
		MatrixMxN& AddEmplace(const MatrixMxN& _m2);
		MatrixMxN Scaled(float _f) const;
		MatrixMxN& Scale(float _f);
		MatrixMxN Multiplied(const MatrixMxN& _m2) const;
		MatrixMxN& Multiply(const MatrixMxN& _m2);
		VectorND Multiply(const VectorND& _v2) const;
		MatrixMxN GaussJordan() const;
		MatrixMxN& GaussJordanEmplace();
		MatrixMxN& Augment(const MatrixMxN& _other);
		MatrixMxN Augmented(const MatrixMxN& _other) const;
		MatrixMxN& Inverse();
		MatrixMxN Inversed() const;

		static MatrixMxN Identity(unsigned int _m);
	private:
		// Private member
		std::vector<float> matrix;
		unsigned int m;
		unsigned int n;
	};

	std::ostream& operator<<(std::ostream& _os, const MatrixMxN& _m);
}
