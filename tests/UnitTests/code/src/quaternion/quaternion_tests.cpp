#include "math3dlib.h"

#include <gtest/gtest.h>

using namespace Maths;

TEST(Quaternion, Constructors)
{
	Quaternion q1;
	EXPECT_FLOAT_EQ(q1.x, 0.f);
	EXPECT_FLOAT_EQ(q1.y, 0.f);
	EXPECT_FLOAT_EQ(q1.z, 0.f);
	EXPECT_FLOAT_EQ(q1.w, 0.f);

	Quaternion q2(1.f, 2.f, 3.f, 4.f);
	EXPECT_FLOAT_EQ(q2.x, 1.f);
	EXPECT_FLOAT_EQ(q2.y, 2.f);
	EXPECT_FLOAT_EQ(q2.z, 3.f);
	EXPECT_FLOAT_EQ(q2.w, 4.f);

	Quaternion q3(5.f);
	EXPECT_FLOAT_EQ(q3.x, 5.f);
	EXPECT_FLOAT_EQ(q3.y, 5.f);
	EXPECT_FLOAT_EQ(q3.z, 5.f);
	EXPECT_FLOAT_EQ(q3.w, 5.f);

	Quaternion q4(q2);
	EXPECT_FLOAT_EQ(q4.x, 1.f);
	EXPECT_FLOAT_EQ(q4.y, 2.f);
	EXPECT_FLOAT_EQ(q4.z, 3.f);
	EXPECT_FLOAT_EQ(q4.w, 4.f);
}

TEST(Quaternion, Product)
{
	Quaternion q1(1, 0, 0, 0);
	Quaternion q2(0, 1, 0, 0);

	Quaternion r = q1 * q2;

	Quaternion r2 = q1.Product(q2);

	EXPECT_FLOAT_EQ(r.x, r2.x);
	EXPECT_FLOAT_EQ(r.y, r2.y);
	EXPECT_FLOAT_EQ(r.z, r2.z);
	EXPECT_FLOAT_EQ(r.w, r2.w);
}

TEST(Quaternion, Norm)
{
	Quaternion q(1, 2, 3, 4);

	float n = q.Norm();

	EXPECT_NEAR(n, sqrtf(30.f), EPS);
	EXPECT_NEAR(q.GetMagnitude(), n, EPS);
}

TEST(Quaternion, SquaredNorm)
{
	Quaternion q(1, 2, 3, 4);

	EXPECT_FLOAT_EQ(q.SquaredNorm(), 30.f);
}

TEST(Quaternion, Normalize)
{
	Quaternion q(1, 2, 3, 4);

	Quaternion r = q.Normalized();

	EXPECT_NEAR(r.GetMagnitude(), 1.f, EPS);

	q.Normalize();

	EXPECT_NEAR(q.GetMagnitude(), 1.f, EPS);
}

TEST(Quaternion, Conjugate)
{
	Quaternion q(1, 2, 3, 4);

	Quaternion r = q.Conjugated();

	EXPECT_FLOAT_EQ(r.x, -1);
	EXPECT_FLOAT_EQ(r.y, -2);
	EXPECT_FLOAT_EQ(r.z, -3);
	EXPECT_FLOAT_EQ(r.w, 4);
}

TEST(Quaternion, Inverse)
{
	Quaternion q(1, 2, 3, 4);

	Quaternion inv = q.Inversed();

	Quaternion identity = q * inv;

	EXPECT_NEAR(identity.w, 1.f, EPS);
}

TEST(Quaternion, DotProduct)
{
	Quaternion q1(1, 2, 3, 4);
	Quaternion q2(5, 6, 7, 8);

	float d = q1.Dot(q2);

	EXPECT_FLOAT_EQ(d, 70.f);
}

TEST(Quaternion, VectorXYZ)
{
	Quaternion q(1, 2, 3, 4);

	Vector3 v = q.VectorXYZ();

	EXPECT_FLOAT_EQ(v.x, 1);
	EXPECT_FLOAT_EQ(v.y, 2);
	EXPECT_FLOAT_EQ(v.z, 3);
}

TEST(Quaternion, RotateVector)
{
	Vector3 axis(0, 0, 1);
	Quaternion q(axis, 90.f);

	Vector3 v(1, 0, 0);

	Vector3 r = q.RotateVec3(v);

	EXPECT_NEAR(r.x, 0.f, EPS);
	EXPECT_NEAR(r.y, 1.f, EPS);
	EXPECT_NEAR(r.z, 0.f, EPS);
}

TEST(Quaternion, Distance)
{
	Quaternion q1(0, 0, 0, 1);
	Quaternion q2(0, 0, 0, 2);

	EXPECT_FLOAT_EQ(Quaternion::Distance(q1, q2), 1.f);
}

// OPERATORS

TEST(Quaternion, AssignmentOperator)
{
	Quaternion q1(1.f, 2.f, 3.f, 4.f);
	Quaternion q2;

	q2 = q1;

	EXPECT_FLOAT_EQ(q2.x, 1.f);
	EXPECT_FLOAT_EQ(q2.y, 2.f);
	EXPECT_FLOAT_EQ(q2.z, 3.f);
	EXPECT_FLOAT_EQ(q2.w, 4.f);
}

TEST(Quaternion, BracketOperator)
{
	Quaternion q(1.f, 2.f, 3.f, 4.f);

	EXPECT_FLOAT_EQ(q[0], 1.f);
	EXPECT_FLOAT_EQ(q[1], 2.f);
	EXPECT_FLOAT_EQ(q[2], 3.f);
	EXPECT_FLOAT_EQ(q[3], 4.f);

	q[0] = 10.f;
	EXPECT_FLOAT_EQ(q.x, 10.f);
}

TEST(Quaternion, OperatorPlusQuaternion)
{
	Quaternion q1(1, 2, 3, 4);
	Quaternion q2(4, 3, 2, 1);

	Quaternion r = q1 + q2;

	EXPECT_FLOAT_EQ(r.x, 5);
	EXPECT_FLOAT_EQ(r.y, 5);
	EXPECT_FLOAT_EQ(r.z, 5);
	EXPECT_FLOAT_EQ(r.w, 5);
}

TEST(Quaternion, OperatorMinusQuaternion)
{
	Quaternion q1(5, 6, 7, 8);
	Quaternion q2(1, 2, 3, 4);

	Quaternion r = q1 - q2;

	EXPECT_FLOAT_EQ(r.x, 4);
	EXPECT_FLOAT_EQ(r.y, 4);
	EXPECT_FLOAT_EQ(r.z, 4);
	EXPECT_FLOAT_EQ(r.w, 4);
}

TEST(Quaternion, OperatorMultiplyScalar)
{
	Quaternion q(1, 2, 3, 4);

	Quaternion r = q * 2.f;

	EXPECT_FLOAT_EQ(r.x, 2);
	EXPECT_FLOAT_EQ(r.y, 4);
	EXPECT_FLOAT_EQ(r.z, 6);
	EXPECT_FLOAT_EQ(r.w, 8);
}

TEST(Quaternion, OperatorDivideScalar)
{
	Quaternion q(2, 4, 6, 8);

	Quaternion r = q / 2.f;

	EXPECT_FLOAT_EQ(r.x, 1);
	EXPECT_FLOAT_EQ(r.y, 2);
	EXPECT_FLOAT_EQ(r.z, 3);
	EXPECT_FLOAT_EQ(r.w, 4);
}

TEST(Quaternion, OperatorPlusEqual)
{
	Quaternion q1(1, 2, 3, 4);
	Quaternion q2(1, 1, 1, 1);

	q1 += q2;

	EXPECT_FLOAT_EQ(q1.x, 2);
	EXPECT_FLOAT_EQ(q1.y, 3);
	EXPECT_FLOAT_EQ(q1.z, 4);
	EXPECT_FLOAT_EQ(q1.w, 5);
}

TEST(Quaternion, OperatorMinusEqual)
{
	Quaternion q1(5, 6, 7, 8);
	Quaternion q2(1, 2, 3, 4);

	q1 -= q2;

	EXPECT_FLOAT_EQ(q1.x, 4);
	EXPECT_FLOAT_EQ(q1.y, 4);
	EXPECT_FLOAT_EQ(q1.z, 4);
	EXPECT_FLOAT_EQ(q1.w, 4);
}

TEST(Quaternion, ComparisonOperators)
{
	Quaternion q1(1, 2, 3, 4);
	Quaternion q2(1, 2, 3, 4);
	Quaternion q3(5, 6, 7, 8);

	EXPECT_TRUE(q1 == q2);
	EXPECT_TRUE(q1 != q3);
}

TEST(Quaternion, Print)
{
	Quaternion q(1, 2, 3, 4);

	std::cout << q << std::endl;
}