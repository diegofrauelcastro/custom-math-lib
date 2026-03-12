#include "math3dlib.h"

#include <gtest/gtest.h>

using namespace Maths;

TEST(VectorND, Constructors)
{
	VectorND v1(3);
	EXPECT_EQ(v1.GetDimension(), 3u);
	EXPECT_FLOAT_EQ(v1[0], 0.f);
	EXPECT_FLOAT_EQ(v1[1], 0.f);
	EXPECT_FLOAT_EQ(v1[2], 0.f);

	VectorND v2(4, 2.f);
	EXPECT_EQ(v2.GetDimension(), 4u);
	EXPECT_FLOAT_EQ(v2[0], 2.f);
	EXPECT_FLOAT_EQ(v2[3], 2.f);

	VectorND v3(v2);
	EXPECT_EQ(v3.GetDimension(), 4u);
	EXPECT_FLOAT_EQ(v3[2], 2.f);
}

TEST(VectorND, GetterSetter)
{
	VectorND v(3);

	v.SetAt(0, 5.f);
	v.SetAt(1, 6.f);
	v.SetAt(2, 7.f);

	EXPECT_FLOAT_EQ(v.GetAt(0), 5.f);
	EXPECT_FLOAT_EQ(v.GetAt(1), 6.f);
	EXPECT_FLOAT_EQ(v.GetAt(2), 7.f);
}

TEST(VectorND, DotProduct)
{
	VectorND v1(3);
	VectorND v2(3);

	v1[0] = 1; v1[1] = 2; v1[2] = 3;
	v2[0] = 4; v2[1] = 5; v2[2] = 6;

	float r = v1.DotProduct(v2);

	EXPECT_FLOAT_EQ(r, 32.f);
	EXPECT_FLOAT_EQ(v1 * v2, 32.f);
}

TEST(VectorND, Opposite)
{
	VectorND v(3, 2.f);

	VectorND r = v.GetOpposite();
	std::cout << r << std::endl;

	EXPECT_FLOAT_EQ(r[0], -2.f);
	EXPECT_FLOAT_EQ(r[1], -2.f);
	EXPECT_FLOAT_EQ(r[2], -2.f);
}

TEST(VectorND, ElementWiseProduct)
{
	VectorND v1(3);
	VectorND v2(3);

	v1[0] = 1; v1[1] = 2; v1[2] = 3;
	v2[0] = 4; v2[1] = 5; v2[2] = 6;

	VectorND r = v1.ElementWiseProduct(v2);

	EXPECT_FLOAT_EQ(r[0], 4.f);
	EXPECT_FLOAT_EQ(r[1], 10.f);
	EXPECT_FLOAT_EQ(r[2], 18.f);
}

TEST(VectorND, Norm)
{
	VectorND v(3);
	v[0] = 3; v[1] = 4; v[2] = 0;

	EXPECT_FLOAT_EQ(v.GetMagnitude(), 5.f);
	EXPECT_FLOAT_EQ(v.SquaredNorm(), 25.f);
}

TEST(VectorND, Normalize)
{
	VectorND v(2);
	v[0] = 3;
	v[1] = 4;

	VectorND r = v.Normalized();

	EXPECT_NEAR(r[0], 0.6f, EPS);
	EXPECT_NEAR(r[1], 0.8f, EPS);

	v.Normalize();

	EXPECT_NEAR(v[0], 0.6f, EPS);
	EXPECT_NEAR(v[1], 0.8f, EPS);
}

TEST(VectorND, MidPoint)
{
	VectorND p1(2);
	VectorND p2(2);

	p1[0] = 0; p1[1] = 0;
	p2[0] = 2; p2[1] = 2;

	VectorND m = VectorND::MidPoint(p1, p2);

	EXPECT_FLOAT_EQ(m[0], 1.f);
	EXPECT_FLOAT_EQ(m[1], 1.f);
}

TEST(VectorND, Distance)
{
	VectorND p1(2);
	VectorND p2(2);

	p1[0] = 0; p1[1] = 0;
	p2[0] = 3; p2[1] = 4;

	EXPECT_FLOAT_EQ(VectorND::Distance(p1, p2), 5.f);
}

// OPERATORS

TEST(VectorND, AssignmentOperator)
{
	VectorND v1(3, 5.f);
	VectorND v2(3);

	v2 = v1;

	EXPECT_EQ(v2.GetDimension(), 3u);
	EXPECT_FLOAT_EQ(v2[0], 5.f);
	EXPECT_FLOAT_EQ(v2[1], 5.f);
	EXPECT_FLOAT_EQ(v2[2], 5.f);
}

TEST(VectorND, BracketOperator)
{
	VectorND v(3);

	v[0] = 1.f;
	v[1] = 2.f;
	v[2] = 3.f;

	EXPECT_FLOAT_EQ(v[0], 1.f);
	EXPECT_FLOAT_EQ(v[1], 2.f);
	EXPECT_FLOAT_EQ(v[2], 3.f);
}

TEST(VectorND, OperatorPlusVector)
{
	VectorND v1(3, 1.f);
	VectorND v2(3, 2.f);

	VectorND r = v1 + v2;

	EXPECT_FLOAT_EQ(r[0], 3.f);
	EXPECT_FLOAT_EQ(r[1], 3.f);
	EXPECT_FLOAT_EQ(r[2], 3.f);
}

TEST(VectorND, OperatorMinusVector)
{
	VectorND v1(3, 5.f);
	VectorND v2(3, 2.f);

	VectorND r = v1 - v2;

	EXPECT_FLOAT_EQ(r[0], 3.f);
	EXPECT_FLOAT_EQ(r[1], 3.f);
	EXPECT_FLOAT_EQ(r[2], 3.f);
}

TEST(VectorND, OperatorPlusScalar)
{
	VectorND v(3, 1.f);

	VectorND r = v + 2.f;

	EXPECT_FLOAT_EQ(r[0], 3.f);
	EXPECT_FLOAT_EQ(r[1], 3.f);
	EXPECT_FLOAT_EQ(r[2], 3.f);
}

TEST(VectorND, OperatorScalarPlusVector)
{
	VectorND v(3, 1.f);

	VectorND r = 2.f + v;

	EXPECT_FLOAT_EQ(r[0], 3.f);
	EXPECT_FLOAT_EQ(r[1], 3.f);
	EXPECT_FLOAT_EQ(r[2], 3.f);
}

TEST(VectorND, OperatorUnaryMinus)
{
	VectorND v(3, 2.f);

	VectorND r = -v;

	EXPECT_FLOAT_EQ(r[0], -2.f);
	EXPECT_FLOAT_EQ(r[1], -2.f);
	EXPECT_FLOAT_EQ(r[2], -2.f);
}

TEST(VectorND, OperatorMultiplyScalar)
{
	VectorND v(3, 2.f);

	VectorND r = v * 3.f;

	EXPECT_FLOAT_EQ(r[0], 6.f);
	EXPECT_FLOAT_EQ(r[1], 6.f);
	EXPECT_FLOAT_EQ(r[2], 6.f);
}

TEST(VectorND, OperatorScalarMultiplyVector)
{
	VectorND v(3, 2.f);

	VectorND r = 3.f * v;

	EXPECT_FLOAT_EQ(r[0], 6.f);
	EXPECT_FLOAT_EQ(r[1], 6.f);
	EXPECT_FLOAT_EQ(r[2], 6.f);
}

TEST(VectorND, OperatorDivideScalar)
{
	VectorND v(3, 6.f);

	VectorND r = v / 2.f;

	EXPECT_FLOAT_EQ(r[0], 3.f);
	EXPECT_FLOAT_EQ(r[1], 3.f);
	EXPECT_FLOAT_EQ(r[2], 3.f);
}

TEST(VectorND, OperatorScalarDivideVector)
{
	VectorND v(3, 2.f);

	VectorND r = 8.f / v;

	EXPECT_FLOAT_EQ(r[0], 4.f);
	EXPECT_FLOAT_EQ(r[1], 4.f);
	EXPECT_FLOAT_EQ(r[2], 4.f);
}

TEST(VectorND, OperatorPlusEqual)
{
	VectorND v1(3, 1.f);
	VectorND v2(3, 2.f);

	v1 += v2;

	EXPECT_FLOAT_EQ(v1[0], 3.f);
	EXPECT_FLOAT_EQ(v1[1], 3.f);
	EXPECT_FLOAT_EQ(v1[2], 3.f);
}

TEST(VectorND, OperatorMinusEqual)
{
	VectorND v1(3, 5.f);
	VectorND v2(3, 2.f);

	v1 -= v2;

	EXPECT_FLOAT_EQ(v1[0], 3.f);
	EXPECT_FLOAT_EQ(v1[1], 3.f);
	EXPECT_FLOAT_EQ(v1[2], 3.f);
}

TEST(VectorND, OperatorMultiplyEqual)
{
	VectorND v(3, 2.f);

	v *= 2.f;

	EXPECT_FLOAT_EQ(v[0], 4.f);
	EXPECT_FLOAT_EQ(v[1], 4.f);
	EXPECT_FLOAT_EQ(v[2], 4.f);
}

TEST(VectorND, OperatorDivideEqual)
{
	VectorND v(3, 6.f);

	v /= 2.f;

	EXPECT_FLOAT_EQ(v[0], 3.f);
	EXPECT_FLOAT_EQ(v[1], 3.f);
	EXPECT_FLOAT_EQ(v[2], 3.f);
}

TEST(VectorND, OperatorIncrement)
{
	VectorND v(3);
	v[0] = 1.f;
	v[1] = 2.f;
	v[2] = 2.f; // length = 3

	float originalLength = v.GetMagnitude();

	v++;

	float newLength = v.GetMagnitude();

	// magnitude increased by 1
	EXPECT_NEAR(newLength, originalLength + 1.f, EPS);

	// direction unchanged
	EXPECT_NEAR(v[0] / newLength, 1.f / 3.f, EPS);
	EXPECT_NEAR(v[1] / newLength, 2.f / 3.f, EPS);
	EXPECT_NEAR(v[2] / newLength, 2.f / 3.f, EPS);
}

TEST(VectorND, OperatorDecrement)
{
	VectorND v(3);
	v[0] = 1.f;
	v[1] = 2.f;
	v[2] = 2.f; // length = 3

	float originalLength = v.GetMagnitude();

	v--;

	float newLength = v.GetMagnitude();

	// magnitude decreased by 1
	EXPECT_NEAR(newLength, originalLength - 1.f, EPS);

	// direction unchanged
	EXPECT_NEAR(v[0] / newLength, 1.f / 3.f, EPS);
	EXPECT_NEAR(v[1] / newLength, 2.f / 3.f, EPS);
	EXPECT_NEAR(v[2] / newLength, 2.f / 3.f, EPS);
}
TEST(VectorND, ComparisonOperators)
{
	VectorND v1(3, 1.f);
	VectorND v2(3, 1.f);
	VectorND v3(3, 2.f);

	EXPECT_TRUE(v1 == v2);
	EXPECT_TRUE(v1 != v3);
	EXPECT_TRUE(v3 > v1);
	EXPECT_TRUE(v1 < v3);
	EXPECT_TRUE(v3 >= v1);
	EXPECT_TRUE(v1 <= v2);
}

TEST(VectorND, Print)
{
	VectorND v(3, 1.f);

	std::cout << v << std::endl;
}