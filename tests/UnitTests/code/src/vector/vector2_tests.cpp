#include "math3dlib.h"

#include <gtest/gtest.h>

using namespace Maths;

TEST(Vector2, Constructors)
{
	Vector2 v1;
	EXPECT_FLOAT_EQ(v1.x, 0.f);
	EXPECT_FLOAT_EQ(v1.y, 0.f);

	Vector2 v2(1.f, 2.f);
	EXPECT_FLOAT_EQ(v2.x, 1.f);
	EXPECT_FLOAT_EQ(v2.y, 2.f);

	Vector2 v3(5.f);
	EXPECT_FLOAT_EQ(v3.x, 5.f);
	EXPECT_FLOAT_EQ(v3.y, 5.f);

	Vector2 v4(v2);
	EXPECT_FLOAT_EQ(v4.x, 1.f);
	EXPECT_FLOAT_EQ(v4.y, 2.f);
}

TEST(Vector2, DotProduct)
{
	Vector2 v1(1.f, 2.f);
	Vector2 v2(3.f, 4.f);

	float r = v1.DotProduct(v2);

	EXPECT_FLOAT_EQ(r, 11.f);
	EXPECT_FLOAT_EQ(v1 * v2, 11.f);
}

TEST(Vector2, CrossProduct)
{
	Vector2 v1(1.f, 0.f);
	Vector2 v2(0.f, 1.f);

	float r = v1.CrossProduct(v2);

	EXPECT_FLOAT_EQ(r, 1.f);
}

TEST(Vector2, Norm)
{
	Vector2 v(3.f, 4.f);

	EXPECT_FLOAT_EQ(v.Norm(), 5.f);
	EXPECT_FLOAT_EQ(v.GetMagnitude(), 5.f);
}

TEST(Vector2, SquaredNorm)
{
	Vector2 v(3.f, 4.f);

	EXPECT_FLOAT_EQ(v.SquaredNorm(), 25.f);
}

TEST(Vector2, Normalize)
{
	Vector2 v(3.f, 4.f);

	Vector2 r = v.Normalized();

	EXPECT_NEAR(r.x, 0.6f, EPS);
	EXPECT_NEAR(r.y, 0.8f, EPS);

	v.Normalize();

	EXPECT_NEAR(v.x, 0.6f, EPS);
	EXPECT_NEAR(v.y, 0.8f, EPS);
}

TEST(Vector2, Opposite)
{
	Vector2 v(1.f, -2.f);

	Vector2 r = v.GetOpposite();

	EXPECT_FLOAT_EQ(r.x, -1.f);
	EXPECT_FLOAT_EQ(r.y, 2.f);
}

TEST(Vector2, ElementWiseProduct)
{
	Vector2 v1(2.f, 3.f);
	Vector2 v2(4.f, 5.f);

	Vector2 r = v1.ElementWiseProduct(v2);

	EXPECT_FLOAT_EQ(r.x, 8.f);
	EXPECT_FLOAT_EQ(r.y, 15.f);
}

TEST(Vector2, MidPoint)
{
	Vector2 p1(0.f, 0.f);
	Vector2 p2(2.f, 2.f);

	Vector2 m = Vector2::MidPoint(p1, p2);

	EXPECT_FLOAT_EQ(m.x, 1.f);
	EXPECT_FLOAT_EQ(m.y, 1.f);
}

TEST(Vector2, Distance)
{
	Vector2 p1(0.f, 0.f);
	Vector2 p2(3.f, 4.f);

	EXPECT_FLOAT_EQ(Vector2::Distance(p1, p2), 5.f);
}

TEST(Vector2, AngleBetweenVectors)
{
	Vector2 v1(1.f, 0.f);
	Vector2 v2(0.f, 1.f);

	float rad = Vector2::AngleRadBetweenTwoVector2(v1, v2);
	float deg = Vector2::AngleDegBetweenTwoVector2(v1, v2);

	EXPECT_NEAR(rad, PI / 2.f, EPS);
	EXPECT_NEAR(deg, 90.f, APPROX_EPS);
}

TEST(Vector2, Rotate)
{
	Vector2 v(1.f, 0.f);

	Vector2 r = v.Rotated(90.f);

	EXPECT_NEAR(r.x, 0.f, EPS);
	EXPECT_NEAR(r.y, 1.f, EPS);

	v.Rotate(90.f);

	EXPECT_NEAR(v.x, 0.f, EPS);
	EXPECT_NEAR(v.y, 1.f, EPS);
}

// OPERATORS

TEST(Vector2, AssignmentOperator)
{
	Vector2 v1(1.f, 2.f);
	Vector2 v2;

	v2 = v1;

	EXPECT_FLOAT_EQ(v2.x, 1.f);
	EXPECT_FLOAT_EQ(v2.y, 2.f);
}

TEST(Vector2, BracketOperator)
{
	Vector2 v(1.f, 2.f);

	EXPECT_FLOAT_EQ(v[0], 1.f);
	EXPECT_FLOAT_EQ(v[1], 2.f);

	v[1] = 10.f;

	EXPECT_FLOAT_EQ(v[1], 10.f);
}

TEST(Vector2, OperatorPlusVector)
{
	Vector2 v1(1.f, 2.f);
	Vector2 v2(3.f, 4.f);

	Vector2 r = v1 + v2;

	EXPECT_FLOAT_EQ(r.x, 4.f);
	EXPECT_FLOAT_EQ(r.y, 6.f);
}

TEST(Vector2, OperatorMinusVector)
{
	Vector2 v1(5.f, 6.f);
	Vector2 v2(2.f, 3.f);

	Vector2 r = v1 - v2;

	EXPECT_FLOAT_EQ(r.x, 3.f);
	EXPECT_FLOAT_EQ(r.y, 3.f);
}

TEST(Vector2, OperatorPlusScalar)
{
	Vector2 v(1.f, 2.f);

	Vector2 r = v + 2.f;

	EXPECT_FLOAT_EQ(r.x, 3.f);
	EXPECT_FLOAT_EQ(r.y, 4.f);
}

TEST(Vector2, OperatorScalarPlusVector)
{
	Vector2 v(1.f, 2.f);

	Vector2 r = 2.f + v;

	EXPECT_FLOAT_EQ(r.x, 3.f);
	EXPECT_FLOAT_EQ(r.y, 4.f);
}

TEST(Vector2, OperatorMinusScalar)
{
	Vector2 v(3.f, 4.f);

	Vector2 r = 2.f - v;

	EXPECT_FLOAT_EQ(r.x, -1.f);
	EXPECT_FLOAT_EQ(r.y, -2.f);
}

TEST(Vector2, OperatorUnaryMinus)
{
	Vector2 v(1.f, -2.f);

	Vector2 r = -v;

	EXPECT_FLOAT_EQ(r.x, -1.f);
	EXPECT_FLOAT_EQ(r.y, 2.f);
}

TEST(Vector2, OperatorMultiplyScalar)
{
	Vector2 v(1.f, 2.f);

	Vector2 r = v * 3.f;

	EXPECT_FLOAT_EQ(r.x, 3.f);
	EXPECT_FLOAT_EQ(r.y, 6.f);
}

TEST(Vector2, OperatorScalarMultiplyVector)
{
	Vector2 v(1.f, 2.f);

	Vector2 r = 3.f * v;

	EXPECT_FLOAT_EQ(r.x, 3.f);
	EXPECT_FLOAT_EQ(r.y, 6.f);
}

TEST(Vector2, OperatorDivideScalar)
{
	Vector2 v(6.f, 8.f);

	Vector2 r = v / 2.f;

	EXPECT_FLOAT_EQ(r.x, 3.f);
	EXPECT_FLOAT_EQ(r.y, 4.f);
}

TEST(Vector2, OperatorScalarDivideVector)
{
	Vector2 v(2.f, 4.f);

	Vector2 r = 8.f / v;

	EXPECT_FLOAT_EQ(r.x, 4.f);
	EXPECT_FLOAT_EQ(r.y, 2.f);
}

TEST(Vector2, OperatorPlusEqual)
{
	Vector2 v1(1.f, 2.f);
	Vector2 v2(2.f, 3.f);

	v1 += v2;

	EXPECT_FLOAT_EQ(v1.x, 3.f);
	EXPECT_FLOAT_EQ(v1.y, 5.f);
}

TEST(Vector2, OperatorMinusEqual)
{
	Vector2 v1(5.f, 6.f);
	Vector2 v2(1.f, 2.f);

	v1 -= v2;

	EXPECT_FLOAT_EQ(v1.x, 4.f);
	EXPECT_FLOAT_EQ(v1.y, 4.f);
}

TEST(Vector2, OperatorMultiplyEqual)
{
	Vector2 v(2.f, 3.f);

	v *= 2.f;

	EXPECT_FLOAT_EQ(v.x, 4.f);
	EXPECT_FLOAT_EQ(v.y, 6.f);
}

TEST(Vector2, OperatorDivideEqual)
{
	Vector2 v(6.f, 8.f);

	v /= 2.f;

	EXPECT_FLOAT_EQ(v.x, 3.f);
	EXPECT_FLOAT_EQ(v.y, 4.f);
}

TEST(Vector2, OperatorIncrement)
{
	Vector2 v(3.f, 4.f); // length = 5
	float originalLength = v.GetMagnitude();

	v++;

	float newLength = v.GetMagnitude();

	EXPECT_NEAR(newLength, originalLength + 1.f, EPS);

	// direction preserved
	EXPECT_NEAR(v.x / newLength, 3.f / 5.f, EPS);
	EXPECT_NEAR(v.y / newLength, 4.f / 5.f, EPS);
}

TEST(Vector2, OperatorDecrement)
{
	Vector2 v(3.f, 4.f); // length = 5
	float originalLength = v.GetMagnitude();

	v--;

	float newLength = v.GetMagnitude();

	EXPECT_NEAR(newLength, originalLength - 1.f, EPS);

	EXPECT_NEAR(v.x / newLength, 3.f / 5.f, EPS);
	EXPECT_NEAR(v.y / newLength, 4.f / 5.f, EPS);
}

TEST(Vector2, ComparisonOperators)
{
	Vector2 v1(1, 2);
	Vector2 v2(1, 2);
	Vector2 v3(3, 4);

	EXPECT_TRUE(v1 == v2);
	EXPECT_TRUE(v1 != v3);
	EXPECT_TRUE(v3 > v1);
	EXPECT_TRUE(v1 < v3);
	EXPECT_TRUE(v3 >= v1);
	EXPECT_TRUE(v1 <= v2);
}

TEST(Vector2, Print)
{
	Vector2 v(1.f, 2.f);

	std::cout << v << std::endl;
}