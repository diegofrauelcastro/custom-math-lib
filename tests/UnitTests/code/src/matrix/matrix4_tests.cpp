#include "math3dlib.h"

#include <gtest/gtest.h>

using namespace Maths;


// Helper to compare two matrices.
static void ExpectMatrix4Near(const Matrix4& _a, const Matrix4& _b, float _eps = EPS)
{
    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 4; c++)
            EXPECT_NEAR(_a.GetAt(r, c), _b.GetAt(r, c), _eps);
}


// CONSTRUCTOR AND OPERATOR TESTS

TEST(Matrix4, DefaultConstructor)
{
    Matrix4 m;

    for (int i = 0; i < 16; i++)
        EXPECT_FLOAT_EQ(m.m[i], 0.f);
}

TEST(Matrix4, ArrayConstructor)
{
    float m[16];
    for (int i = 0; i < 16; i++)
        m[i] = 1.f;

    Matrix4 mManualResult;
    for (int i = 0; i < 16; i++)
        mManualResult.m[i] = m[i];

    Matrix4 mRes(m);
    ExpectMatrix4Near(mManualResult, mRes);
}

TEST(Matrix4, CopyConstructor)
{
    Matrix4 m1;
    m1.m[0] = 1.f;
    m1.m[5] = 10.f;
    Matrix4 m2(m1);

    ExpectMatrix4Near(m1, m2);

    m1.m[5] = 1.f;
    EXPECT_FALSE(m1.m[5] == m2.m[5]);
}

TEST(Matrix4, VectorConstructor)
{
    float f = 1.f;
    Vector4 l1 = { f, f, f, f };
    Vector4 l2 = { f, f, f, f };
    Vector4 l3 = { f, f, f, f };
    Vector4 l4 = { f, f, f, f };
    Matrix4 m(l1, l2, l3, l4);

    for (int i = 0; i < 16; i++)
        EXPECT_FLOAT_EQ(m.m[i], f);
}

TEST(Matrix4, Identity)
{
    Matrix4 I = Matrix4::Identity();

    for (int i = 0; i < 16; i++)
    {
        if (i % 5 == 0) EXPECT_FLOAT_EQ(I.m[i], 1.f);
        else EXPECT_FLOAT_EQ(I.m[i], 0.f);
    }
}

TEST(Matrix4, GetSetAt)
{
    Matrix4 m1;
    m1.m[0] = 1.f;
    m1.m[1] = 0.f;
    m1.m[5] = 1.f;
    m1.m[15] = 0.f;

    EXPECT_FLOAT_EQ(m1.GetAt(0, 0), 1.f);
    EXPECT_FLOAT_EQ(m1.GetAt(1, 1), 1.f);
    EXPECT_FLOAT_EQ(m1.GetAt(0, 1), 0.f);
    EXPECT_FLOAT_EQ(m1.GetAt(3, 3), 0.f);

    m1.SetAt(1, 1, 0.f);
    EXPECT_FLOAT_EQ(m1.m[3], 0.f);
}

TEST(Matrix4, DiagonalAndTrace)
{
    Matrix4 m1;
    m1.m[0] = 1.f;
    m1.m[5] = 1.5f;
    m1.m[10] = 4.f;
    m1.m[15] = 2.2f;

    Vector4 diag(m1.GetDiagonal());
    EXPECT_FLOAT_EQ(diag.x, m1.m[0]);
    EXPECT_FLOAT_EQ(diag.y, m1.m[5]);
    EXPECT_FLOAT_EQ(diag.z, m1.m[10]);
    EXPECT_FLOAT_EQ(diag.w, m1.m[15]);

    float trace = diag.x + diag.y + diag.z + diag.w;
    EXPECT_FLOAT_EQ(trace, m1.GetTrace());
}

TEST(Matrix4, Opposite)
{
    Matrix4 m1;
    m1.m[0] = 1.f;
    m1.m[1] = 2.f;
    m1.m[3] = 1.5f;
    m1.m[10] = 7.f;
    m1.m[13] = -10.f;
    m1.m[14] = 0.f;

    Matrix4 oppositeSample;
    for (int i = 0; i < 16; i++)
        oppositeSample.m[i] = -m1.m[i];

    ExpectMatrix4Near(oppositeSample, m1.GetOpposite());
}

TEST(Matrix4, Determinant)
{
    Matrix4 m1;
    m1.m[0] = 3.f; m1.m[1] = 0.f; m1.m[2] = 2.f; m1.m[3] = -1.f;
    m1.m[4] = 1.f; m1.m[5] = 2.f; m1.m[6] = 0.f; m1.m[7] = -2.f;
    m1.m[8] = 4.f; m1.m[9] = 0.f; m1.m[10] = 6.f; m1.m[11] = -3.f;
    m1.m[12] = 5.f; m1.m[13] = 0.f; m1.m[14] = 2.f; m1.m[15] = 0.f;
    float det = 20.f; // Pre-calculated by hand.

    EXPECT_FLOAT_EQ(det, m1.Det());
}

TEST(Matrix4, CopyOperator)
{
    Matrix4 m1;
    m1.m[0] = 1.f;
    m1.m[10] = -310.23f;
    m1.m[3] = 17.f;
    Matrix4 m2 = m1;
    ExpectMatrix4Near(m1, m2);

    m2.m[0] = 10.f;
    EXPECT_FALSE(m1.m[0] == m2.m[0]);
}

TEST(Matrix4, BracketOperator)
{
    Matrix4 m1;
    m1.m[0] = 1.f;
    m1.m[1] = 2.f;
    m1.m[2] = -0.5f;
    m1.m[3] = 1.5f;

    EXPECT_FLOAT_EQ(m1[0], 1.f);
    EXPECT_FLOAT_EQ(m1[1], 2.f);

    m1[1] = 5.f;
    EXPECT_FLOAT_EQ(m1[1], 5.f);
}

TEST(Matrix4, Transpose)
{
    Matrix4 m1;
    m1.m[0] = 3.f; m1.m[1] = 0.f; m1.m[2] = 2.f; m1.m[3] = -1.f;
    m1.m[4] = 1.f; m1.m[5] = 2.f; m1.m[6] = 0.f; m1.m[7] = -2.f;
    m1.m[8] = 4.f; m1.m[9] = 0.f; m1.m[10] = 6.f; m1.m[11] = -3.f;
    m1.m[12] = 5.f; m1.m[13] = 0.f; m1.m[14] = 2.f; m1.m[15] = 0.f;

    Matrix4 m2;
    m2.m[0] = 3.f; m2.m[1] = 1.f; m2.m[2] = 4.f; m2.m[3] = 5.f;
    m2.m[4] = 0.f; m2.m[5] = 2.f; m2.m[6] = 0.f; m2.m[7] = 0.f;
    m2.m[8] = 2.f; m2.m[9] = 0.f; m2.m[10] = 6.f; m2.m[11] = 2.f;
    m2.m[12] = -1.f; m2.m[13] = -2.f; m2.m[14] = -3.f; m2.m[15] = 0.f;

    Matrix4 mResultTransposed(m1.Transposed());

    m1.Transpose();
    ExpectMatrix4Near(m2, m1);
    ExpectMatrix4Near(m2, mResultTransposed);
}

TEST(Matrix4, Add)
{
    Matrix4 m1;
    m1.m[0] = 1.f;
    m1.m[1] = 2.f;
    m1.m[2] = -0.5f;
    m1.m[3] = 1.5f;
    m1.m[14] = -1.5f;
    m1.m[15] = 6.2f;

    Matrix4 m2;
    m2.m[0] = 1.f;
    m2.m[1] = 2.f;
    m2.m[2] = -0.5f;
    m2.m[3] = 1.5f;
    m2.m[14] = -1.5f;
    m2.m[15] = 6.2f;

    Matrix4 mManualResult;
    for (int i = 0; i < 16; i++)
        mManualResult.m[i] = m1[i] + m2[i];

    Matrix4 mRes(m1.Add(m2));

    m1.AddEmplace(m2);
    ExpectMatrix4Near(mManualResult, m1);
    ExpectMatrix4Near(mManualResult, mRes);
}

TEST(Matrix4, Scale)
{
    Matrix4 m1;
    m1.m[0] = 1.f;
    m1.m[1] = 2.f;
    m1.m[2] = -0.5f;
    m1.m[3] = 1.5f;
    m1.m[14] = -1.5f;
    m1.m[15] = 6.2f;

    float f = 10.f;

    Matrix4 mManualResult;
    for (int i = 0; i < 16; i++)
        mManualResult.m[i] = m1.m[i] * f;

    Matrix4 mRes(m1.Scaled(f));

    m1.Scale(f);
    ExpectMatrix4Near(mManualResult, m1);
    ExpectMatrix4Near(mManualResult, mRes);
}

TEST(Matrix4, IsOrthogonal)
{
    // Identity matrix
    Matrix4 I = Matrix4::Identity();
    EXPECT_TRUE(I.IsOrthogonal());

    // Pure rotation: 90° around Z
    Matrix4 R = Matrix4::CreateZRotationMatrix(90.f);
    EXPECT_TRUE(R.IsOrthogonal());

    // Uniform scale (scale factor 2)
    Matrix4 S = Matrix4::CreateScaleMatrix({ 2.f, 2.f, 2.f });
    EXPECT_FALSE(S.IsOrthogonal());

    // Non-uniform scale
    Matrix4 NS = Matrix4::CreateScaleMatrix({ 2.f, 3.f, 1.f });
    EXPECT_FALSE(NS.IsOrthogonal());

    // Rotation + non-uniform scale
    Matrix4 RNS = R * NS;
    EXPECT_FALSE(RNS.IsOrthogonal());
}

TEST(Matrix4, MultiplyByMatOperator)
{
    Matrix4 m1;
    m1.m[0] = 1.f;
    m1.m[1] = 2.f;
    m1.m[2] = -0.5f;
    m1.m[3] = 1.5f;
    m1.m[14] = -1.5f;
    m1.m[15] = 6.2f;

    Matrix4 m2;
    m2.m[0] = 1.f;
    m2.m[1] = 2.f;
    m2.m[2] = -0.5f;
    m2.m[3] = 1.5f;
    m2.m[14] = -1.5f;
    m2.m[15] = 6.2f;

    Matrix4 mManualResult;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            mManualResult[4 * i + j] = m1[4 * i] * m2.m[j] + m1[4 * i + 1] * m2.m[4 + j] + m1[4 * i + 2] * m2.m[8 + j] + m1[4 * i + 3] * m2.m[12 + j];
    }

    Matrix4 mRes(m1 * m2);
    ExpectMatrix4Near(mManualResult, mRes);
}

TEST(Matrix4, MultiplyByVectorOperator)
{
    Vector4 v1 = { 0.f, 5.f, 1.5f, 0.25f };
    Matrix4 m1;
    m1.m[0] = 1.f;
    m1.m[1] = 2.f;
    m1.m[2] = -0.5f;
    m1.m[3] = 1.5f;
    m1.m[14] = -1.5f;
    m1.m[15] = 6.2f;

    float newX = m1.m[0] * v1.x + m1.m[1] * v1.y + m1.m[2] * v1.z + m1.m[3] * v1.w;
    float newY = m1.m[4] * v1.x + m1.m[5] * v1.y + m1.m[6] * v1.z + m1.m[7] * v1.w;
    float newZ = m1.m[8] * v1.x + m1.m[9] * v1.y + m1.m[10] * v1.z + m1.m[11] * v1.w;
    float newW = m1.m[12] * v1.x + m1.m[13] * v1.y + m1.m[14] * v1.z + m1.m[15] * v1.w;
    Vector4 vRes = m1 * v1;

    EXPECT_FLOAT_EQ(newX, vRes.x);
    EXPECT_FLOAT_EQ(newY, vRes.y);
    EXPECT_FLOAT_EQ(newZ, vRes.z);
    EXPECT_FLOAT_EQ(newW, vRes.w);
}

TEST(Matrix4, MultiplyByMat)
{
    Matrix4 m1;
    m1.m[0] = 1.f;
    m1.m[1] = 2.f;
    m1.m[2] = -0.5f;
    m1.m[3] = 1.5f;
    m1.m[14] = -1.5f;
    m1.m[15] = 6.2f;

    Matrix4 m2;
    m2.m[0] = 1.f;
    m2.m[1] = 2.f;
    m2.m[2] = -0.5f;
    m2.m[3] = 1.5f;
    m2.m[14] = -1.5f;
    m2.m[15] = 6.2f;

    Matrix4 mManualResult;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            mManualResult[4 * i + j] = m1[4 * i] * m2.m[j] + m1[4 * i + 1] * m2.m[4 + j] + m1[4 * i + 2] * m2.m[8 + j] + m1[4 * i + 3] * m2.m[12 + j];
    }

    Matrix4 mRes(m1.Multiplied(m2));

    m1.Multiply(m2);
    ExpectMatrix4Near(mManualResult, m1);
    ExpectMatrix4Near(mManualResult, mRes);
}

TEST(Matrix4, MultiplyByVector)
{
    Vector4 v1 = { 0.f, 5.f, 1.5f, 0.25f };
    Matrix4 m1;
    m1.m[0] = 1.f;
    m1.m[1] = 2.f;
    m1.m[2] = -0.5f;
    m1.m[3] = 1.5f;
    m1.m[14] = -1.5f;
    m1.m[15] = 6.2f;

    float newX = m1.m[0] * v1.x + m1.m[1] * v1.y + m1.m[2] * v1.z + m1.m[3] * v1.w;
    float newY = m1.m[4] * v1.x + m1.m[5] * v1.y + m1.m[6] * v1.z + m1.m[7] * v1.w;
    float newZ = m1.m[8] * v1.x + m1.m[9] * v1.y + m1.m[10] * v1.z + m1.m[11] * v1.w;
    float newW = m1.m[12] * v1.x + m1.m[13] * v1.y + m1.m[14] * v1.z + m1.m[15] * v1.w;
    Vector4 vRes = m1.Multiply(v1);

    EXPECT_FLOAT_EQ(newX, vRes.x);
    EXPECT_FLOAT_EQ(newY, vRes.y);
    EXPECT_FLOAT_EQ(newZ, vRes.z);
    EXPECT_FLOAT_EQ(newW, vRes.w);
}

TEST(Matrix4, ScaleMatrix)
{
    float scaleX = 1.5f;
    float scaleY = 10.2f;
    float scaleZ = 5.f;
    Matrix4 m1(Matrix4::CreateScaleMatrix({ scaleX, scaleY, scaleZ }));

    Matrix4 mManualResult;
    for (int i = 0; i < 16; i++)
        mManualResult.m[i];
    mManualResult.m[0] = scaleX;
    mManualResult.m[5] = scaleY;
    mManualResult.m[10] = scaleZ;
    mManualResult.m[15] = 1.f;

    ExpectMatrix4Near(mManualResult, m1);
}

TEST(Matrix4, TranslationMatrix)
{
    float posX = 1.f;
    float posY = 5.f;
    float posZ = -2.5f;
    Matrix4 m1(Matrix4::CreateTranslationMatrix({ posX, posY, posZ }));

    Matrix4 mManualResult;
    mManualResult[3] = posX;
    mManualResult[7] = posY;
    mManualResult[11] = posZ;
    mManualResult[0] = 1.f; mManualResult[5] = 1.f; mManualResult[10] = 1.f; mManualResult[15] = 1.f;

    ExpectMatrix4Near(mManualResult, m1);
}

TEST(Matrix4, Print)
{
    Matrix4 m1;
    m1.m[0] = 1.f;
    m1.m[1] = 2.f;
    m1.m[2] = -0.5f;
    m1.m[3] = 1.5f;
    m1.m[14] = -1.5f;
    m1.m[15] = 7.f;

    std::cout << m1 << std::endl;
}