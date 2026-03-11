#include "math3dlib.h"

#include <gtest/gtest.h>

using namespace Maths;


// Helper to compare two matrices.
static void ExpectMatrix2Near(const Matrix2& _a, const Matrix2& _b, float _eps = EPS)
{
    for (int r = 0; r < 2; r++)
        for (int c = 0; c < 2; c++)
            EXPECT_NEAR(_a.GetAt(r, c), _b.GetAt(r, c), _eps);
}


// CONSTRUCTOR AND OPERATOR TESTS

TEST(Matrix2, DefaultConstructor)
{
    Matrix2 m;

    EXPECT_FLOAT_EQ(m.m[0], 0.f);
    EXPECT_FLOAT_EQ(m.m[1], 0.f);
    EXPECT_FLOAT_EQ(m.m[2], 0.f);
    EXPECT_FLOAT_EQ(m.m[3], 0.f);
}

TEST(Matrix2, ArrayConstructor)
{
    float m[4];
    for (int i = 0; i < 4; i++)
        m[i] = 1.f;

    Matrix2 mManualResult;
    for (int i = 0; i < 4; i++)
        mManualResult.m[i] = m[i];

    Matrix2 mRes(m);
    ExpectMatrix2Near(mManualResult, mRes);
}

TEST(Matrix2, FillConstructor)
{
    float f = 10.f;
    Matrix2 floatM(f);
    for (int i = 0; i < 4; i++)
        EXPECT_FLOAT_EQ(floatM.m[i], f);
}

TEST(Matrix2, CopyConstructor)
{
    Matrix2 m1;
    m1.m[0] = 1.f;
    Matrix2 m2(m1);

    ExpectMatrix2Near(m1, m2);
    m1.m[0] = 10.f;
    EXPECT_FALSE(m1.m[0] == m2.m[0]);
}

TEST(Matrix2, VectorConstructor)
{
    float f = 1.f;
    Vector2 l1 = { f, f };
    Vector2 l2 = { f, f };
    Matrix2 m(l1, l2);

    for (int i = 0; i < 4; i++)
        EXPECT_FLOAT_EQ(m.m[i], f);
}

TEST(Matrix2, Identity)
{
    Matrix2 I = Matrix2::Identity();

    EXPECT_FLOAT_EQ(I.m[0], 1.f);
    EXPECT_FLOAT_EQ(I.m[3], 1.f);
    EXPECT_FLOAT_EQ(I.m[1], 0.f);
    EXPECT_FLOAT_EQ(I.m[2], 0.f);
}

TEST(Matrix2, GetSetAt)
{
    Matrix2 m1;
    m1.m[0] = 1.f;
    m1.m[3] = 1.f;
    
    EXPECT_FLOAT_EQ(m1.GetAt(0, 0), 1.f);
    EXPECT_FLOAT_EQ(m1.GetAt(1, 1), 1.f);
    EXPECT_FLOAT_EQ(m1.GetAt(0, 1), 0.f);
    EXPECT_FLOAT_EQ(m1.GetAt(1, 0), 0.f);
    
    m1.SetAt(1, 1, 0.f);
    EXPECT_FLOAT_EQ(m1.m[3], 0.f);
}

TEST(Matrix2, DiagonalAndTrace)
{
    Matrix2 m1;
    m1.m[0] = 1.f;
    m1.m[3] = 1.5f;

    Vector2 diag(m1.GetDiagonal());
    EXPECT_FLOAT_EQ(diag.x, m1.m[0]);
    EXPECT_FLOAT_EQ(diag.y, m1.m[3]);
    
    float trace = diag.x + diag.y;
    EXPECT_FLOAT_EQ(trace, m1.GetTrace());
}

TEST(Matrix2, Opposite)
{
    Matrix2 m1;
    m1.m[0] = 1.f;
    m1.m[1] = 2.f;
    m1.m[3] = 1.5f;

    Matrix2 oppositeSample;
    for (int i = 0; i < 4; i++)
        oppositeSample.m[i] = -m1.m[i];

    ExpectMatrix2Near(oppositeSample, m1.GetOpposite());
}

TEST(Matrix2, Determinant)
{
    Matrix2 m1;
    m1.m[0] = 1.f;
    m1.m[1] = 2.f;
    m1.m[2] = -0.5f;
    m1.m[3] = 1.5f;
    float det = m1.m[0] * m1.m[3] - m1.m[2] * m1.m[1];

    EXPECT_FLOAT_EQ(det, m1.Det());
}

TEST(Matrix2, CopyOperator)
{
    Matrix2 m1;
    m1.m[0] = 1.f;
    Matrix2 m2 = m1;
    ExpectMatrix2Near(m1, m2);

    m2.m[0] = 10.f;
    EXPECT_FALSE(m1.m[0] == m2.m[0]);
}

TEST(Matrix2, EqualsOperator)
{
    Matrix2 m1;
    m1.m[0] = 1.f;
    m1.m[3] = 1.f;

    Matrix2 m2;
    m2.m[0] = 1.f;
    m2.m[3] = 1.f;

    Matrix2 m3;
    m3.m[0] = 4.f;
    m3.m[3] = 4.f;

    EXPECT_TRUE(m1 == m2);
    EXPECT_FALSE(m1 == m3);
}

TEST(Matrix2, BracketOperator)
{
    Matrix2 m1;
    m1.m[0] = 1.f;
    m1.m[1] = 2.f;
    m1.m[2] = -0.5f;
    m1.m[3] = 1.5f;

    EXPECT_FLOAT_EQ(m1[0], 1.f);
    EXPECT_FLOAT_EQ(m1[1], 2.f);

    m1[1] = 5.f;
    EXPECT_FLOAT_EQ(m1[1], 5.f);
}

TEST(Matrix2, MultiplyByMatOperator)
{
    Matrix2 m1;
    m1.m[0] = 1.f;
    m1.m[1] = 2.f;
    m1.m[2] = -0.5f;
    m1.m[3] = 1.5f;

    Matrix2 m2;
    m2.m[0] = 1.f;
    m2.m[1] = 2.f;
    m2.m[2] = -0.5f;
    m2.m[3] = 1.5f;

    Matrix2 mManualResult;
    mManualResult.m[0] = m1.m[0] * m2.m[0] + m1.m[1] * m2.m[2];
    mManualResult.m[1] = m1.m[0] * m2[1] + m1.m[1] * m2.m[3];
    mManualResult.m[2] = m1.m[2] * m2[0] + m1.m[3] * m2[2];
    mManualResult.m[3] = m1.m[2] * m2[1] + m1.m[3] * m2[3];

    Matrix2 mRes(m1 * m2);
    ExpectMatrix2Near(mManualResult, mRes);
}

TEST(Matrix2, MultiplyByVectorOperator)
{
    Vector2 v1 = { 0.f, 5.f };
    Matrix2 m1;
    m1.m[0] = 1.f;
    m1.m[1] = 2.f;
    m1.m[2] = -0.5f;
    m1.m[3] = 1.5f;

    float newX = m1.m[0] * v1.x + m1.m[1] * v1.y;
    float newY = m1.m[2] * v1.x + m1.m[3] * v1.y;
    Vector2 vRes = m1 * v1;

    EXPECT_FLOAT_EQ(newX, vRes.x);
    EXPECT_FLOAT_EQ(newY, vRes.y);
}

TEST(Matrix2, Transpose)
{
    Matrix2 m1;
    m1.m[0] = 1.f;
    m1.m[1] = 2.f;
    m1.m[2] = -0.5f;
    m1.m[3] = 1.5f;

    Matrix2 mManuallyTransposed;
    mManuallyTransposed.m[0] = 1.f;
    mManuallyTransposed.m[1] = -0.5f;
    mManuallyTransposed.m[2] = 2.f;
    mManuallyTransposed.m[3] = 1.5f;

    Matrix2 mResultTransposed(m1.Transposed());

    m1.Transpose();
    ExpectMatrix2Near(mManuallyTransposed, m1);
    ExpectMatrix2Near(mManuallyTransposed, mResultTransposed);
}

TEST(Matrix2, Add)
{
    Matrix2 m1;
    m1.m[0] = 1.f;
    m1.m[1] = 2.f;
    m1.m[2] = -0.5f;
    m1.m[3] = 1.5f;

    Matrix2 m2;
    m2.m[0] = 1.f;
    m2.m[1] = 2.f;
    m2.m[2] = -0.5f;
    m2.m[3] = 1.5f;

    Matrix2 mManualResult;
    mManualResult.m[0] = m1.m[0] + m2.m[0];
    mManualResult.m[1] = m1.m[1] + m2.m[1];
    mManualResult.m[2] = m1.m[2] + m2.m[2];
    mManualResult.m[3] = m1.m[3] + m2.m[3];

    Matrix2 mRes(m1.Add(m2));

    m1.AddEmplace(m2);
    ExpectMatrix2Near(mManualResult, m1);
    ExpectMatrix2Near(mManualResult, mRes);
}

TEST(Matrix2, Scale)
{
    Matrix2 m1;
    m1.m[0] = 1.f;
    m1.m[1] = 2.f;
    m1.m[2] = -0.5f;
    m1.m[3] = 1.5f;

    float f = 10.f;

    Matrix2 mManualResult;
    for (int i = 0; i < 4; i++)
        mManualResult.m[i] = m1.m[i] * f;

    Matrix2 mRes(m1.Scaled(f));

    m1.Scale(f);
    ExpectMatrix2Near(mManualResult, m1);
    ExpectMatrix2Near(mManualResult, mRes);
}

TEST(Matrix2, MultiplyByMatrix)
{
    Matrix2 m1;
    m1.m[0] = 1.f;
    m1.m[1] = 2.f;
    m1.m[2] = -0.5f;
    m1.m[3] = 1.5f;

    Matrix2 m2;
    m2.m[0] = 1.f;
    m2.m[1] = 2.f;
    m2.m[2] = -0.5f;
    m2.m[3] = 1.5f;

    Matrix2 mManualResult;
    mManualResult.m[0] = m1.m[0] * m2.m[0] + m1.m[1] * m2.m[2];
    mManualResult.m[1] = m1.m[0] * m2[1] + m1.m[1] * m2.m[3];
    mManualResult.m[2] = m1.m[2] * m2[0] + m1.m[3] * m2[2];
    mManualResult.m[3] = m1.m[2] * m2[1] + m1.m[3] * m2[3];

    Matrix2 mRes(m1.Multiplied(m2));

    m1.Multiply(m2);
    ExpectMatrix2Near(mManualResult, m1);
    ExpectMatrix2Near(mManualResult, mRes);
}

TEST(Matrix2, MultiplyByVector)
{
    Vector2 v1 = { 0.f, 5.f };
    Matrix2 m1;
    m1.m[0] = 1.f;
    m1.m[1] = 2.f;
    m1.m[2] = -0.5f;
    m1.m[3] = 1.5f;

    float newX = m1.m[0] * v1.x + m1.m[1] * v1.y;
    float newY = m1.m[2] * v1.x + m1.m[3] * v1.y;
    Vector2 vRes = m1.Multiply(v1);
    
    EXPECT_FLOAT_EQ(newX, vRes.x);
    EXPECT_FLOAT_EQ(newY, vRes.y);
}

TEST(Matrix2, ScaleMatrix)
{
    float scaleX = 1.5f;
    float scaleY = 10.2f;
    Matrix2 m1(Matrix2::CreateScaleMatrix({scaleX, scaleY}));

    Matrix2 mManualResult;
    mManualResult.m[0] = scaleX;
    mManualResult.m[1] = 0.f;
    mManualResult.m[2] = 0.f;
    mManualResult.m[3] = scaleY;

    ExpectMatrix2Near(mManualResult, m1);
}

TEST(Matrix2, RotationMatrix)
{
    float angleDeg = 90.f;
    float angleRad = angleDeg * DEG2RAD;
    Matrix2 m1(Matrix2::CreateRotationMatrix(angleDeg));

    Matrix2 mManualResult;
    mManualResult[0] = cosf(angleRad); mManualResult[1] = -sinf(angleRad);
    mManualResult[2] = sinf(angleRad); mManualResult[3] = cosf(angleRad);

    ExpectMatrix2Near(mManualResult, m1);
}

TEST(Matrix2, Print)
{
    Matrix2 m1;
    m1.m[0] = 1.f;
    m1.m[1] = 2.f;
    m1.m[2] = -0.5f;
    m1.m[3] = 1.5f;

    std::cout << m1 << std::endl;
}