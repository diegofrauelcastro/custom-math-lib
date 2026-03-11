#include "math3dlib.h"

#include <gtest/gtest.h>

using namespace Maths;

TEST(Vector4, Constructors)
{
	Vector4 v1;
	EXPECT_FLOAT_EQ(v1.x, 0.f);
	EXPECT_FLOAT_EQ(v1.y, 0.f);
	EXPECT_FLOAT_EQ(v1.z, 0.f);
	EXPECT_FLOAT_EQ(v1.w, 0.f);

	Vector4 v2(1.f, 2.f, 3.f, 4.f);
	EXPECT_FLOAT_EQ(v2.x, 1.f);
	EXPECT_FLOAT_EQ(v2.y, 2.f);
	EXPECT_FLOAT_EQ(v2.z, 3.f);
	EXPECT_FLOAT_EQ(v2.w, 4.f);

	Vector4 v3(5.f);
	EXPECT_FLOAT_EQ(v3.x, 5.f);
	EXPECT_FLOAT_EQ(v3.y, 5.f);
	EXPECT_FLOAT_EQ(v3.z, 5.f);
	EXPECT_FLOAT_EQ(v3.w, 5.f);

	Vector4 v4(v2);
	EXPECT_FLOAT_EQ(v4.x, 1.f);
	EXPECT_FLOAT_EQ(v4.y, 2.f);
	EXPECT_FLOAT_EQ(v4.z, 3.f);
	EXPECT_FLOAT_EQ(v4.w, 4.f);

	Vector3 v3d(7.f, 8.f, 9.f);
	Vector4 v5(v3d, 2.f);
	EXPECT_FLOAT_EQ(v5.x, 7.f);
	EXPECT_FLOAT_EQ(v5.y, 8.f);
	EXPECT_FLOAT_EQ(v5.z, 9.f);
	EXPECT_FLOAT_EQ(v5.w, 2.f);
}

TEST(Vector4, AssignmentOperator)
{
	Vector4 v1(1.f, 2.f, 3.f, 4.f);
	Vector4 v2;

	v2 = v1;

	EXPECT_FLOAT_EQ(v2.x, 1.f);
	EXPECT_FLOAT_EQ(v2.y, 2.f);
	EXPECT_FLOAT_EQ(v2.z, 3.f);
	EXPECT_FLOAT_EQ(v2.w, 4.f);
}

TEST(Vector4, BracketOperator)
{
	Vector4 v(1.f, 2.f, 3.f, 4.f);

	EXPECT_FLOAT_EQ(v[0], 1.f);
	EXPECT_FLOAT_EQ(v[1], 2.f);
	EXPECT_FLOAT_EQ(v[2], 3.f);
	EXPECT_FLOAT_EQ(v[3], 4.f);

	v[2] = 10.f;

	EXPECT_FLOAT_EQ(v[2], 10.f);
}

TEST(Vector4, Add)
{
	Vector4 v1(1.f, 2.f, 3.f, 4.f);
	Vector4 v2(4.f, 3.f, 2.f, 1.f);

	Vector4 manual(5.f, 5.f, 5.f, 5.f);

	Vector4 res = v1.Add(v2);

	v1.AddEmplace(v2);

	EXPECT_FLOAT_EQ(v1.x, manual.x);
	EXPECT_FLOAT_EQ(v1.y, manual.y);
	EXPECT_FLOAT_EQ(v1.z, manual.z);
	EXPECT_FLOAT_EQ(v1.w, manual.w);

	EXPECT_FLOAT_EQ(res.x, manual.x);
	EXPECT_FLOAT_EQ(res.y, manual.y);
	EXPECT_FLOAT_EQ(res.z, manual.z);
	EXPECT_FLOAT_EQ(res.w, manual.w);
}

TEST(Vector4, Scale)
{
	Vector4 v1(1.f, 2.f, 3.f, 4.f);

	float f = 2.f;

	Vector4 manual(2.f, 4.f, 6.f, 8.f);

	Vector4 res = v1.Scaled(f);

	v1.Scale(f);

	EXPECT_FLOAT_EQ(v1.x, manual.x);
	EXPECT_FLOAT_EQ(v1.y, manual.y);
	EXPECT_FLOAT_EQ(v1.z, manual.z);
	EXPECT_FLOAT_EQ(v1.w, manual.w);

	EXPECT_FLOAT_EQ(res.x, manual.x);
	EXPECT_FLOAT_EQ(res.y, manual.y);
	EXPECT_FLOAT_EQ(res.z, manual.z);
	EXPECT_FLOAT_EQ(res.w, manual.w);
}

TEST(Vector4, Opposite)
{
	Vector4 v1(1.f, -2.f, 3.f, -4.f);

	Vector4 manual(-1.f, 2.f, -3.f, 4.f);

	Vector4 res = v1.GetOpposite();

	EXPECT_FLOAT_EQ(res.x, manual.x);
	EXPECT_FLOAT_EQ(res.y, manual.y);
	EXPECT_FLOAT_EQ(res.z, manual.z);
	EXPECT_FLOAT_EQ(res.w, manual.w);
}

TEST(Vector4, DotProduct)
{
	Vector4 v1(1.f, 2.f, 3.f, 4.f);
	Vector4 v2(4.f, 3.f, 2.f, 1.f);

	float manual = 1 * 4 + 2 * 3 + 3 * 2 + 4 * 1;

	EXPECT_FLOAT_EQ(v1.DotProduct(v2), manual);
	EXPECT_FLOAT_EQ(v1 * v2, manual);
}

TEST(Vector4, ElementWiseProduct)
{
	Vector4 v1(1.f, 2.f, 3.f, 4.f);
	Vector4 v2(4.f, 3.f, 2.f, 1.f);

	Vector4 manual(4.f, 6.f, 6.f, 4.f);

	Vector4 res = v1.ElementWiseProduct(v2);

	EXPECT_FLOAT_EQ(res.x, manual.x);
	EXPECT_FLOAT_EQ(res.y, manual.y);
	EXPECT_FLOAT_EQ(res.z, manual.z);
	EXPECT_FLOAT_EQ(res.w, manual.w);
}

TEST(Vector4, Norm)
{
	Vector4 v(1.f, 2.f, 2.f, 1.f);

	float manual = sqrtf(1 + 4 + 4 + 1);

	EXPECT_FLOAT_EQ(v.Norm(), manual);
	EXPECT_FLOAT_EQ(v.GetMagnitude(), manual);
}

TEST(Vector4, SquaredNorm)
{
	Vector4 v(1.f, 2.f, 3.f, 4.f);

	float manual = 1 + 4 + 9 + 16;

	EXPECT_FLOAT_EQ(v.SquaredNorm(), manual);
}

TEST(Vector4, Normalize)
{
	Vector4 v(1.f, 2.f, 2.f, 1.f);

	Vector4 res = v.Normalized();

	float n = sqrtf(10.f);

	EXPECT_NEAR(res.x, 1.f / n, EPS);
	EXPECT_NEAR(res.y, 2.f / n, EPS);
	EXPECT_NEAR(res.z, 2.f / n, EPS);
	EXPECT_NEAR(res.w, 1.f / n, EPS);

	v.Normalize();

	EXPECT_NEAR(v.x, 1.f / n, EPS);
	EXPECT_NEAR(v.y, 2.f / n, EPS);
	EXPECT_NEAR(v.z, 2.f / n, EPS);
	EXPECT_NEAR(v.w, 1.f / n, EPS);
}

TEST(Vector4, Homogenize)
{
	Vector4 v(2.f, 4.f, 6.f, 2.f);

	v.Homogenize();

	EXPECT_FLOAT_EQ(v.x, 1.f);
	EXPECT_FLOAT_EQ(v.y, 2.f);
	EXPECT_FLOAT_EQ(v.z, 3.f);
	EXPECT_FLOAT_EQ(v.w, 1.f);
}

TEST(Vector4, MidPoint)
{
	Vector4 p1(0.f, 0.f, 0.f, 1.f);
	Vector4 p2(2.f, 2.f, 2.f, 1.f);

	Vector4 mid = Vector4::MidPoint(p1, p2);

	EXPECT_FLOAT_EQ(mid.x, 1.f);
	EXPECT_FLOAT_EQ(mid.y, 1.f);
	EXPECT_FLOAT_EQ(mid.z, 1.f);
}

TEST(Vector4, Distance)
{
	Vector4 p1(0.f, 0.f, 0.f, 1.f);
	Vector4 p2(3.f, 4.f, 0.f, 1.f);

	float d = Vector4::Distance(p1, p2);

	EXPECT_FLOAT_EQ(d, 5.f);
}

TEST(Vector4, ComparisonOperators)
{
	Vector4 v1(1, 2, 3, 4);
	Vector4 v2(1, 2, 3, 4);
	Vector4 v3(2, 3, 4, 5);

	EXPECT_TRUE(v1 == v2);
	EXPECT_TRUE(v1 != v3);
	EXPECT_TRUE(v3 > v1);
	EXPECT_TRUE(v1 < v3);
	EXPECT_TRUE(v3 >= v1);
	EXPECT_TRUE(v1 <= v2);
}

TEST(Vector4, Print)
{
	Vector4 v(1.f, 2.f, 3.f, 4.f);

	std::cout << v << std::endl;
}