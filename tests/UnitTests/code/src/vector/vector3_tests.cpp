#include "math3dlib.h"

#include <gtest/gtest.h>

using namespace Maths;

TEST(Vector3, Constructors)
{
	Vector3 v1;
	EXPECT_FLOAT_EQ(v1.x, 0.f);
	EXPECT_FLOAT_EQ(v1.y, 0.f);
	EXPECT_FLOAT_EQ(v1.z, 0.f);

	Vector3 v2(1.f, 2.f, 3.f);
	EXPECT_FLOAT_EQ(v2.x, 1.f);
	EXPECT_FLOAT_EQ(v2.y, 2.f);
	EXPECT_FLOAT_EQ(v2.z, 3.f);

	Vector3 v3(5.f);
	EXPECT_FLOAT_EQ(v3.x, 5.f);
	EXPECT_FLOAT_EQ(v3.y, 5.f);
	EXPECT_FLOAT_EQ(v3.z, 5.f);

	Vector3 v4(v2);
	EXPECT_FLOAT_EQ(v4.x, 1.f);
	EXPECT_FLOAT_EQ(v4.y, 2.f);
	EXPECT_FLOAT_EQ(v4.z, 3.f);
}

TEST(Vector3, Add)
{
	Vector3 v1(1.f, 2.f, 3.f);
	Vector3 v2(4.f, 5.f, 6.f);

	Vector3 manual(5.f, 7.f, 9.f);

	Vector3 res = v1.Add(v2);

	v1.AddEmplace(v2);

	EXPECT_FLOAT_EQ(v1.x, manual.x);
	EXPECT_FLOAT_EQ(v1.y, manual.y);
	EXPECT_FLOAT_EQ(v1.z, manual.z);

	EXPECT_FLOAT_EQ(res.x, manual.x);
	EXPECT_FLOAT_EQ(res.y, manual.y);
	EXPECT_FLOAT_EQ(res.z, manual.z);
}

TEST(Vector3, Scale)
{
	Vector3 v1(1.f, 2.f, 3.f);

	float f = 3.f;

	Vector3 manual(3.f, 6.f, 9.f);

	Vector3 res = v1.Scaled(f);

	v1.Scale(f);

	EXPECT_FLOAT_EQ(v1.x, manual.x);
	EXPECT_FLOAT_EQ(v1.y, manual.y);
	EXPECT_FLOAT_EQ(v1.z, manual.z);

	EXPECT_FLOAT_EQ(res.x, manual.x);
	EXPECT_FLOAT_EQ(res.y, manual.y);
	EXPECT_FLOAT_EQ(res.z, manual.z);
}

TEST(Vector3, Opposite)
{
	Vector3 v(1.f, -2.f, 3.f);

	Vector3 res = v.GetOpposite();

	EXPECT_FLOAT_EQ(res.x, -1.f);
	EXPECT_FLOAT_EQ(res.y, 2.f);
	EXPECT_FLOAT_EQ(res.z, -3.f);
}

TEST(Vector3, DotProduct)
{
	Vector3 v1(1.f, 2.f, 3.f);
	Vector3 v2(4.f, 5.f, 6.f);

	float manual = 1 * 4 + 2 * 5 + 3 * 6;

	EXPECT_FLOAT_EQ(v1.DotProduct(v2), manual);
	EXPECT_FLOAT_EQ(v1 * v2, manual);
}

TEST(Vector3, CrossProduct)
{
	Vector3 v1(1.f, 0.f, 0.f);
	Vector3 v2(0.f, 1.f, 0.f);

	Vector3 cross = v1.CrossProduct(v2);

	EXPECT_FLOAT_EQ(cross.x, 0.f);
	EXPECT_FLOAT_EQ(cross.y, 0.f);
	EXPECT_FLOAT_EQ(cross.z, 1.f);
}

TEST(Vector3, ElementWiseProduct)
{
	Vector3 v1(1.f, 2.f, 3.f);
	Vector3 v2(4.f, 5.f, 6.f);

	Vector3 res = v1.ElementWiseProduct(v2);

	EXPECT_FLOAT_EQ(res.x, 4.f);
	EXPECT_FLOAT_EQ(res.y, 10.f);
	EXPECT_FLOAT_EQ(res.z, 18.f);
}

TEST(Vector3, Norm)
{
	Vector3 v(1.f, 2.f, 2.f);

	float manual = sqrtf(1 + 4 + 4);

	EXPECT_FLOAT_EQ(v.Norm(), manual);
	EXPECT_FLOAT_EQ(v.GetMagnitude(), manual);
}

TEST(Vector3, SquaredNorm)
{
	Vector3 v(1.f, 2.f, 3.f);

	EXPECT_FLOAT_EQ(v.SquaredNorm(), 14.f);
}

TEST(Vector3, Normalize)
{
	Vector3 v(1.f, 2.f, 2.f);

	Vector3 res = v.Normalized();

	float n = sqrtf(9.f);

	EXPECT_NEAR(res.x, 1.f / n, EPS);
	EXPECT_NEAR(res.y, 2.f / n, EPS);
	EXPECT_NEAR(res.z, 2.f / n, EPS);

	v.Normalize();

	EXPECT_NEAR(v.x, 1.f / n, EPS);
	EXPECT_NEAR(v.y, 2.f / n, EPS);
	EXPECT_NEAR(v.z, 2.f / n, EPS);
}

TEST(Vector3, MidPoint)
{
	Vector3 p1(0.f, 0.f, 0.f);
	Vector3 p2(2.f, 2.f, 2.f);

	Vector3 mid = Vector3::MidPoint(p1, p2);

	EXPECT_FLOAT_EQ(mid.x, 1.f);
	EXPECT_FLOAT_EQ(mid.y, 1.f);
	EXPECT_FLOAT_EQ(mid.z, 1.f);
}

TEST(Vector3, Distance)
{
	Vector3 p1(0.f, 0.f, 0.f);
	Vector3 p2(3.f, 4.f, 0.f);

	float d = Vector3::Distance(p1, p2);

	EXPECT_FLOAT_EQ(d, 5.f);
}

TEST(Vector3, AngleBetweenVectors)
{
	Vector3 v1(1.f, 0.f, 0.f);
	Vector3 v2(0.f, 1.f, 0.f);

	float rad = Vector3::AngleRadBetweenTwoVector3(v1, v2);
	float deg = Vector3::AngleDegBetweenTwoVector3(v1, v2);

	EXPECT_NEAR(rad, PI / 2.f, EPS);
	EXPECT_NEAR(deg, 90.f, APPROX_EPS);
}

TEST(Vector3, RandomUnitVector)
{
	Vector3 v = Vector3::GenerateRandomUnitVector3();

	EXPECT_NEAR(v.Norm(), 1.f, EPS);
}

TEST(Vector3, RandomOnHemisphere)
{
	Vector3 normal(0.f, 1.f, 0.f);

	Vector3 v = Vector3::GenerateRandomOnHemisphere(normal);

	EXPECT_GE(v.DotProduct(normal), 0.f);
}

// OPERATORS

TEST(Vector3, AssignmentOperator)
{
	Vector3 v1(1.f, 2.f, 3.f);
	Vector3 v2;

	v2 = v1;

	EXPECT_FLOAT_EQ(v2.x, 1.f);
	EXPECT_FLOAT_EQ(v2.y, 2.f);
	EXPECT_FLOAT_EQ(v2.z, 3.f);
}

TEST(Vector3, BracketOperator)
{
	Vector3 v(1.f, 2.f, 3.f);

	EXPECT_FLOAT_EQ(v[0], 1.f);
	EXPECT_FLOAT_EQ(v[1], 2.f);
	EXPECT_FLOAT_EQ(v[2], 3.f);

	v[1] = 10.f;

	EXPECT_FLOAT_EQ(v[1], 10.f);
}

TEST(Vector3, OperatorPlusVector)
{
	Vector3 v1(1.f, 2.f, 3.f);
	Vector3 v2(4.f, 5.f, 6.f);

	Vector3 res = v1 + v2;

	EXPECT_FLOAT_EQ(res.x, 5.f);
	EXPECT_FLOAT_EQ(res.y, 7.f);
	EXPECT_FLOAT_EQ(res.z, 9.f);
}

TEST(Vector3, OperatorMinusVector)
{
	Vector3 v1(5.f, 7.f, 9.f);
	Vector3 v2(1.f, 2.f, 3.f);

	Vector3 res = v1 - v2;

	EXPECT_FLOAT_EQ(res.x, 4.f);
	EXPECT_FLOAT_EQ(res.y, 5.f);
	EXPECT_FLOAT_EQ(res.z, 6.f);
}

TEST(Vector3, OperatorPlusScalar)
{
	Vector3 v(1.f, 2.f, 3.f);

	Vector3 res = v + 2.f;

	EXPECT_FLOAT_EQ(res.x, 3.f);
	EXPECT_FLOAT_EQ(res.y, 4.f);
	EXPECT_FLOAT_EQ(res.z, 5.f);
}

TEST(Vector3, OperatorScalarPlusVector)
{
	Vector3 v(1.f, 2.f, 3.f);

	Vector3 res = 2.f + v;

	EXPECT_FLOAT_EQ(res.x, 3.f);
	EXPECT_FLOAT_EQ(res.y, 4.f);
	EXPECT_FLOAT_EQ(res.z, 5.f);
}

TEST(Vector3, OperatorMinusScalar)
{
	Vector3 v(5.f, 6.f, 7.f);

	Vector3 res = 2.f - v;

	EXPECT_FLOAT_EQ(res.x, -3.f);
	EXPECT_FLOAT_EQ(res.y, -4.f);
	EXPECT_FLOAT_EQ(res.z, -5.f);
}

TEST(Vector3, OperatorUnaryMinus)
{
	Vector3 v(1.f, -2.f, 3.f);

	Vector3 res = -v;

	EXPECT_FLOAT_EQ(res.x, -1.f);
	EXPECT_FLOAT_EQ(res.y, 2.f);
	EXPECT_FLOAT_EQ(res.z, -3.f);
}

TEST(Vector3, OperatorMultiplyScalar)
{
	Vector3 v(1.f, 2.f, 3.f);

	Vector3 res = v * 3.f;

	EXPECT_FLOAT_EQ(res.x, 3.f);
	EXPECT_FLOAT_EQ(res.y, 6.f);
	EXPECT_FLOAT_EQ(res.z, 9.f);
}

TEST(Vector3, OperatorScalarMultiplyVector)
{
	Vector3 v(1.f, 2.f, 3.f);

	Vector3 res = 3.f * v;

	EXPECT_FLOAT_EQ(res.x, 3.f);
	EXPECT_FLOAT_EQ(res.y, 6.f);
	EXPECT_FLOAT_EQ(res.z, 9.f);
}

TEST(Vector3, OperatorDivideScalar)
{
	Vector3 v(6.f, 9.f, 12.f);

	Vector3 res = v / 3.f;

	EXPECT_FLOAT_EQ(res.x, 2.f);
	EXPECT_FLOAT_EQ(res.y, 3.f);
	EXPECT_FLOAT_EQ(res.z, 4.f);
}

TEST(Vector3, OperatorScalarDivideVector)
{
	Vector3 v(1.f, 2.f, 4.f);

	Vector3 res = 8.f / v;

	EXPECT_FLOAT_EQ(res.x, 8.f);
	EXPECT_FLOAT_EQ(res.y, 4.f);
	EXPECT_FLOAT_EQ(res.z, 2.f);
}

TEST(Vector3, OperatorPlusEqual)
{
	Vector3 v1(1.f, 2.f, 3.f);
	Vector3 v2(2.f, 3.f, 4.f);

	v1 += v2;

	EXPECT_FLOAT_EQ(v1.x, 3.f);
	EXPECT_FLOAT_EQ(v1.y, 5.f);
	EXPECT_FLOAT_EQ(v1.z, 7.f);
}

TEST(Vector3, OperatorMinusEqual)
{
	Vector3 v1(5.f, 6.f, 7.f);
	Vector3 v2(1.f, 2.f, 3.f);

	v1 -= v2;

	EXPECT_FLOAT_EQ(v1.x, 4.f);
	EXPECT_FLOAT_EQ(v1.y, 4.f);
	EXPECT_FLOAT_EQ(v1.z, 4.f);
}

TEST(Vector3, OperatorMultiplyEqual)
{
	Vector3 v(1.f, 2.f, 3.f);

	v *= 2.f;

	EXPECT_FLOAT_EQ(v.x, 2.f);
	EXPECT_FLOAT_EQ(v.y, 4.f);
	EXPECT_FLOAT_EQ(v.z, 6.f);
}

TEST(Vector3, OperatorDivideEqual)
{
	Vector3 v(6.f, 8.f, 10.f);

	v /= 2.f;

	EXPECT_FLOAT_EQ(v.x, 3.f);
	EXPECT_FLOAT_EQ(v.y, 4.f);
	EXPECT_FLOAT_EQ(v.z, 5.f);
}

TEST(Vector3, OperatorIncrement)
{
	Vector3 v(1.f, 2.f, 2.f); // length = 3
	float originalLength = v.GetMagnitude();

	v++;

	float newLength = v.GetMagnitude();

	EXPECT_NEAR(newLength, originalLength + 1.f, EPS);

	EXPECT_NEAR(v.x / newLength, 1.f / 3.f, EPS);
	EXPECT_NEAR(v.y / newLength, 2.f / 3.f, EPS);
	EXPECT_NEAR(v.z / newLength, 2.f / 3.f, EPS);
}

TEST(Vector3, OperatorDecrement)
{
	Vector3 v(1.f, 2.f, 2.f); // length = 3
	float originalLength = v.GetMagnitude();

	v--;

	float newLength = v.GetMagnitude();

	EXPECT_NEAR(newLength, originalLength - 1.f, EPS);

	EXPECT_NEAR(v.x / newLength, 1.f / 3.f, EPS);
	EXPECT_NEAR(v.y / newLength, 2.f / 3.f, EPS);
	EXPECT_NEAR(v.z / newLength, 2.f / 3.f, EPS);
}

TEST(Vector3, ComparisonOperators)
{
	Vector3 v1(1, 2, 3);
	Vector3 v2(1, 2, 3);
	Vector3 v3(4, 5, 6);

	EXPECT_TRUE(v1 == v2);
	EXPECT_TRUE(v1 != v3);
	EXPECT_TRUE(v3 > v1);
	EXPECT_TRUE(v1 < v3);
	EXPECT_TRUE(v3 >= v1);
	EXPECT_TRUE(v1 <= v2);
}

TEST(Vector3, Print)
{
	Vector3 v(1.f, 2.f, 3.f);

	std::cout << v << std::endl;
}
