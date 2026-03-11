#include "math3dlib.h"

#include <gtest/gtest.h>

using namespace Maths;


// Helper to compare two matrices
static void ExpectMatrixNear(const MatrixMxN& _a, const MatrixMxN& _b, float _eps = EPS)
{
	Vector2 aDim = _a.GetDimensions();
	Vector2 bDim = _a.GetDimensions();
	ASSERT_EQ(aDim.x, bDim.x);
	ASSERT_EQ(aDim.y, bDim.y);

	for (unsigned int r = 0; r < aDim.x; r++)
		for (unsigned int c = 0; c < aDim.y; c++)
			EXPECT_NEAR(_a.GetAt(r, c), _b.GetAt(r, c), _eps);
}


// CONSTRUCTOR AND OPERATOR TESTS

TEST(MatrixMxN, Constructor)
{
	MatrixMxN m(3, 4);

	Vector2 dims = m.GetDimensions();
	EXPECT_EQ(dims.x, 3);
	EXPECT_EQ(dims.y, 4);

	for (int i = 0; i < 12; i++)
		EXPECT_FLOAT_EQ(m.matrix[i], 0.f);
}

TEST(MatrixMxN, CopyConstructor)
{
	MatrixMxN m1(2, 3);

	m1.SetAt(0, 0, 1.f);
	m1.SetAt(1, 2, 5.f);

	MatrixMxN m2(m1);

	ExpectMatrixNear(m1, m2);

	m1.SetAt(0, 0, 10.f);

	EXPECT_FALSE(m1.GetAt(0, 0) == m2.GetAt(0, 0));
}

TEST(MatrixMxN, Identity)
{
	MatrixMxN I = MatrixMxN::Identity(3);

	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			if (r == c)
				EXPECT_FLOAT_EQ(I.GetAt(r, c), 1.f);
			else
				EXPECT_FLOAT_EQ(I.GetAt(r, c), 0.f);
		}
	}
}

TEST(MatrixMxN, GetSetAt)
{
	MatrixMxN m(3, 4);

	m.SetAt(1, 2, 7.f);

	EXPECT_FLOAT_EQ(m.GetAt(1, 2), 7.f);

	m.SetAt(1, 2, -3.f);

	EXPECT_FLOAT_EQ(m.GetAt(1, 2), -3.f);
}

TEST(MatrixMxN, DiagonalAndTrace)
{
	MatrixMxN m(3, 3);

	m.SetAt(0, 0, 1.f);
	m.SetAt(1, 1, 1.5f);
	m.SetAt(2, 2, 4.f);

	VectorND diag(m.GetDiagonal());

	EXPECT_FLOAT_EQ(diag[0], m.matrix[0]);
	EXPECT_FLOAT_EQ(diag[1], m.matrix[4]);
	EXPECT_FLOAT_EQ(diag[2], m.matrix[8]);

	float trace = diag[0] + diag[1] + diag[2];

	EXPECT_FLOAT_EQ(trace, m.GetTrace());
}

TEST(MatrixMxN, Opposite)
{
	MatrixMxN m1(2, 3);

	m1.SetAt(0, 0, 1.f);
	m1.SetAt(0, 1, 2.f);
	m1.SetAt(1, 0, 1.5f);
	m1.SetAt(1, 2, 7.f);

	MatrixMxN oppositeSample(2, 3);

	for (int i = 0; i < 6; i++)
		oppositeSample.matrix[i] = -m1.matrix[i];

	ExpectMatrixNear(oppositeSample, m1.GetOpposite());
}

TEST(MatrixMxN, CopyOperator)
{
	MatrixMxN m1(2, 2);

	m1.SetAt(0, 0, 1.f);
	m1.SetAt(1, 1, -12.3f);

	MatrixMxN m2 = m1;

	ExpectMatrixNear(m1, m2);

	m2.SetAt(0, 0, 10.f);

	EXPECT_FALSE(m1.GetAt(0, 0) == m2.GetAt(0, 0));
}

TEST(MatrixMxN, BracketOperator)
{
	MatrixMxN m1(2, 2);

	m1.matrix[0] = 1.f;
	m1.matrix[1] = 2.f;
	m1.matrix[2] = -0.5f;

	EXPECT_FLOAT_EQ(m1[0], 1.f);
	EXPECT_FLOAT_EQ(m1[1], 2.f);

	m1[1] = 5.f;

	EXPECT_FLOAT_EQ(m1[1], 5.f);
}

TEST(MatrixMxN, Transpose)
{
	MatrixMxN m1(2, 3);

	m1.SetAt(0, 0, 1.f);
	m1.SetAt(0, 1, 2.f);
	m1.SetAt(0, 2, 3.f);
	m1.SetAt(1, 0, 4.f);
	m1.SetAt(1, 1, 5.f);
	m1.SetAt(1, 2, 6.f);

	MatrixMxN m2(3, 2);

	m2.SetAt(0, 0, 1.f);
	m2.SetAt(0, 1, 4.f);
	m2.SetAt(1, 0, 2.f);
	m2.SetAt(1, 1, 5.f);
	m2.SetAt(2, 0, 3.f);
	m2.SetAt(2, 1, 6.f);

	MatrixMxN mResultTransposed(m1.Transposed());

	m1.Transpose();

	ExpectMatrixNear(m2, m1);
	ExpectMatrixNear(m2, mResultTransposed);
}

TEST(MatrixMxN, Add)
{
	MatrixMxN m1(2, 2);
	MatrixMxN m2(2, 2);

	m1.SetAt(0, 0, 1.f);
	m1.SetAt(0, 1, 2.f);
	m1.SetAt(1, 1, 3.f);

	m2.SetAt(0, 0, 1.f);
	m2.SetAt(0, 1, 2.f);
	m2.SetAt(1, 1, 3.f);

	MatrixMxN mManualResult(2, 2);

	for (int i = 0; i < 4; i++)
		mManualResult.matrix[i] = m1[i] + m2[i];

	MatrixMxN mRes(m1.Add(m2));

	m1.AddEmplace(m2);

	ExpectMatrixNear(mManualResult, m1);
	ExpectMatrixNear(mManualResult, mRes);
}

TEST(MatrixMxN, Scale)
{
	MatrixMxN m1(2, 2);

	m1.SetAt(0, 0, 1.f);
	m1.SetAt(0, 1, 2.f);
	m1.SetAt(1, 0, -0.5f);
	m1.SetAt(1, 1, 3.f);

	float f = 10.f;

	MatrixMxN mManualResult(2, 2);

	for (int i = 0; i < 4; i++)
		mManualResult.matrix[i] = m1.matrix[i] * f;

	MatrixMxN mRes(m1.Scaled(f));

	m1.Scale(f);

	ExpectMatrixNear(mManualResult, m1);
	ExpectMatrixNear(mManualResult, mRes);
}

TEST(MatrixMxN, MultiplyByMatOperator)
{
	MatrixMxN m1(2, 3);
	MatrixMxN m2(3, 2);

	m1.SetAt(0, 0, 1.f);
	m1.SetAt(0, 1, 2.f);
	m1.SetAt(0, 2, 3.f);
	m1.SetAt(1, 0, 4.f);
	m1.SetAt(1, 1, 5.f);
	m1.SetAt(1, 2, 6.f);

	m2.SetAt(0, 0, 1.f);
	m2.SetAt(0, 1, 2.f);
	m2.SetAt(1, 0, 3.f);
	m2.SetAt(1, 1, 4.f);
	m2.SetAt(2, 0, 5.f);
	m2.SetAt(2, 1, 6.f);

	MatrixMxN mManualResult(2, 2);

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			float sum = 0.f;

			for (int k = 0; k < 3; k++)
				sum += m1.GetAt(i, k) * m2.GetAt(k, j);

			mManualResult.SetAt(i, j, sum);
		}
	}

	MatrixMxN mRes(m1 * m2);

	ExpectMatrixNear(mManualResult, mRes);
}

TEST(MatrixMxN, Print)
{
	MatrixMxN m1(2, 4);

	m1.SetAt(0, 0, 1.f);
	m1.SetAt(0, 1, 2.f);
	m1.SetAt(1, 0, 3.f);
	m1.SetAt(1, 1, 4.f);
	m1.SetAt(0, 2, -10.f);
	m1.SetAt(0, 3, 4.5f);
	m1.SetAt(1, 2, -1.f);
	m1.SetAt(1, 3, 0.2f);

	std::cout << m1 << std::endl;
}