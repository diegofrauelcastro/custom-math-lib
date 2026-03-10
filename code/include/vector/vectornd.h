#pragma once

#include <vector>
#include <string>

namespace Maths
{
	class VectorND
	{
	public:
		// Constructors
		VectorND() = delete;
		VectorND(unsigned int _numDimensions, float _f = 0.f);
		VectorND(const VectorND& _copy);
		// Destructor
		~VectorND() = default;

		// Operators
		VectorND& operator=(const VectorND& _copy);
		float& operator[](unsigned int _index);
		float operator[](unsigned int _index) const;

		VectorND operator+(float _f) const;
		VectorND& operator+=(const VectorND& _v);
		VectorND& operator-=(const VectorND& _v);
		VectorND operator-() const;
		VectorND operator*(float _f) const;
		VectorND& operator*=(float _f);
		VectorND operator/(float _f) const;
		VectorND& operator/=(float _f);
		void operator++(int _i);
		void operator--(int _i);
		float operator*(const VectorND& _v) const;

		bool operator==(const VectorND& _v) const;
		bool operator!=(const VectorND& _v) const;
		bool operator<(const VectorND& _v) const;
		bool operator<=(const VectorND& _v) const;
		bool operator>(const VectorND& _v) const;
		bool operator>=(const VectorND& _v) const;

		// Getters
		float GetAt(unsigned int _index) const;
		unsigned int GetDimension() const;

		// Setter
		void SetAt(unsigned int _index, float _value);

		// Public methods
		float DotProduct(const VectorND& _v) const;
		VectorND GetOpposite() const;
		VectorND ElementWiseProduct(const VectorND& _v) const;
		float GetMagnitude() const;
		float SquaredNorm() const;

		VectorND Add(const VectorND& _v) const;
		VectorND& AddEmplace(const VectorND& _v);
		VectorND Scaled(float _f) const;
		VectorND& Scale(float _f);
		VectorND Normalized() const;
		VectorND& Normalize();

		// Static methods
		static VectorND MidPoint(const VectorND& _p1, const VectorND& _p2);
		static float Distance(const VectorND& _p1, const VectorND& _p2);
	private:
		// Private members
		std::vector<float> values;
		unsigned int numDimension;
	};

	std::ostream& operator<<(std::ostream& _os, const VectorND& _v);

	VectorND operator*(float _f, const VectorND& _v);
	VectorND operator/(float _f, const VectorND& _v);
	VectorND operator+(const VectorND& _v1, const VectorND& _v2);
	VectorND operator+(float _f, const VectorND& _v);
	VectorND operator-(const VectorND& _v1, const VectorND& _v2);
	VectorND operator-(float _f, const VectorND& _v);
}
