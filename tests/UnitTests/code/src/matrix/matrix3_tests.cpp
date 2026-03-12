#include "math3dlib.h"

#include <gtest/gtest.h>

using namespace Maths;


// Helper to compare two matrices.
static void ExpectMatrix3Near(const Matrix3& _a, const Matrix3& _b, float _eps = EPS)
{
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            EXPECT_NEAR(_a.GetAt(r, c), _b.GetAt(r, c), _eps);
}


// CONSTRUCTOR AND OPERATOR TESTS

TEST(Matrix3, DefaultConstructor)
{
    Matrix3 m;

    for (int i = 0; i < 9; i++)
        EXPECT_FLOAT_EQ(m.m[i], 0.f);
}

TEST(Matrix3, ArrayConstructor)
{
    float m[9];
    for (int i = 0; i < 9; i++)
        m[i] = 1.f;

    Matrix3 mManualResult;
    for (int i = 0; i < 9; i++)
        mManualResult.m[i] = m[i];

    Matrix3 mRes(m);

    ExpectMatrix3Near(mManualResult, mRes);
}

TEST(Matrix3, CopyConstructor)
{
    Matrix3 m1;
    m1.m[0] = 1.f;
    m1.m[4] = 10.f;

    Matrix3 m2(m1);

    ExpectMatrix3Near(m1, m2);

    m1.m[4] = 1.f;
    EXPECT_FALSE(m1.m[4] == m2.m[4]);
}

TEST(Matrix3, Identity)
{
    Matrix3 I = Matrix3::Identity();

    for (int i = 0; i < 9; i++)
    {
        if (i % 4 == 0)
            EXPECT_FLOAT_EQ(I.m[i], 1.f);
        else
            EXPECT_FLOAT_EQ(I.m[i], 0.f);
    }
}

TEST(Matrix3, VectorConstructor)
{
    float f = 1.f;
    Vector3 l1 = { f, f, f };
    Vector3 l2 = { f, f, f };
    Vector3 l3 = { f, f, f};
    Matrix3 m(l1, l2, l3);

    for (int i = 0; i < 9; i++)
        EXPECT_FLOAT_EQ(m.m[i], f);
}


TEST(Matrix3, GetSetAt)
{
    Matrix3 m1;

    m1.m[0] = 1.f;
    m1.m[1] = 0.f;
    m1.m[4] = 1.f;

    EXPECT_FLOAT_EQ(m1.GetAt(0, 0), 1.f);
    EXPECT_FLOAT_EQ(m1.GetAt(1, 1), 1.f);
    EXPECT_FLOAT_EQ(m1.GetAt(0, 1), 0.f);

    m1.SetAt(1, 1, 0.f);

    EXPECT_FLOAT_EQ(m1.GetAt(1, 1), 0.f);
}

TEST(Matrix3, DiagonalAndTrace)
{
    Matrix3 m1;

    m1.m[0] = 1.f;
    m1.m[4] = 1.5f;
    m1.m[8] = 4.f;

    Vector3 diag(m1.GetDiagonal());

    EXPECT_FLOAT_EQ(diag.x, m1.m[0]);
    EXPECT_FLOAT_EQ(diag.y, m1.m[4]);
    EXPECT_FLOAT_EQ(diag.z, m1.m[8]);

    float trace = diag.x + diag.y + diag.z;

    EXPECT_FLOAT_EQ(trace, m1.GetTrace());
}

TEST(Matrix3, Opposite)
{
    Matrix3 m1;

    m1.m[0] = 1.f;
    m1.m[1] = 2.f;
    m1.m[3] = 1.5f;
    m1.m[8] = 7.f;

    Matrix3 oppositeSample;

    for (int i = 0; i < 9; i++)
        oppositeSample.m[i] = -m1.m[i];

    ExpectMatrix3Near(oppositeSample, m1.GetOpposite());
}

TEST(Matrix3, Determinant)
{
    Matrix3 m1;

    m1.m[0] = 1.f;  m1.m[1] = 2.f;  m1.m[2] = 3.f;
    m1.m[3] = 0.f;  m1.m[4] = 4.f;  m1.m[5] = 5.f;
    m1.m[6] = 1.f;  m1.m[7] = 0.f;  m1.m[8] = 6.f;

    float det = 22.f; // Pre-computed

    EXPECT_FLOAT_EQ(det, m1.Det());
}

TEST(Matrix3, CopyOperator)
{
    Matrix3 m1;

    m1.m[0] = 1.f;
    m1.m[8] = -12.3f;

    Matrix3 m2 = m1;

    ExpectMatrix3Near(m1, m2);

    m2.m[0] = 10.f;

    EXPECT_FALSE(m1.m[0] == m2.m[0]);
}

TEST(Matrix3, BracketOperator)
{
    Matrix3 m1;

    m1.m[0] = 1.f;
    m1.m[1] = 2.f;
    m1.m[2] = -0.5f;

    EXPECT_FLOAT_EQ(m1[0], 1.f);
    EXPECT_FLOAT_EQ(m1[1], 2.f);

    m1[1] = 5.f;

    EXPECT_FLOAT_EQ(m1[1], 5.f);
}

TEST(Matrix3, EqualsOperator)
{
    Matrix3 m1;
    m1.m[0] = 1.f;
    m1.m[3] = 1.f;
    m1.m[5] = 1.f;

    Matrix3 m2;
    m2.m[0] = 1.f;
    m2.m[3] = 1.f;
    m2.m[5] = 1.f;

    Matrix3 m3;
    m3.m[0] = 4.f;
    m3.m[3] = 4.f;
    m3.m[5] = 4.f;

    EXPECT_TRUE(m1 == m2);
    EXPECT_FALSE(m1 == m3);
}


TEST(Matrix3, Transpose)
{
    Matrix3 m1;

    m1.m[0] = 1.f; m1.m[1] = 2.f; m1.m[2] = 3.f;
    m1.m[3] = 4.f; m1.m[4] = 5.f; m1.m[5] = 6.f;
    m1.m[6] = 7.f; m1.m[7] = 8.f; m1.m[8] = 9.f;

    Matrix3 m2;

    m2.m[0] = 1.f; m2.m[1] = 4.f; m2.m[2] = 7.f;
    m2.m[3] = 2.f; m2.m[4] = 5.f; m2.m[5] = 8.f;
    m2.m[6] = 3.f; m2.m[7] = 6.f; m2.m[8] = 9.f;

    Matrix3 mResultTransposed(m1.Transposed());

    m1.Transpose();

    ExpectMatrix3Near(m2, m1);
    ExpectMatrix3Near(m2, mResultTransposed);
}

TEST(Matrix3, Add)
{
    Matrix3 m1;
    Matrix3 m2;

    m1.m[0] = 1.f;
    m1.m[1] = 2.f;
    m1.m[8] = 3.f;

    m2.m[0] = 1.f;
    m2.m[1] = 2.f;
    m2.m[8] = 3.f;

    Matrix3 mManualResult;

    for (int i = 0; i < 9; i++)
        mManualResult.m[i] = m1[i] + m2[i];

    Matrix3 mRes(m1.Add(m2));

    m1.AddEmplace(m2);

    ExpectMatrix3Near(mManualResult, m1);
    ExpectMatrix3Near(mManualResult, mRes);
}

TEST(Matrix3, Scale)
{
    Matrix3 m1;

    m1.m[0] = 1.f;
    m1.m[1] = 2.f;
    m1.m[2] = -0.5f;
    m1.m[8] = 3.f;

    float f = 10.f;

    Matrix3 mManualResult;

    for (int i = 0; i < 9; i++)
        mManualResult.m[i] = m1.m[i] * f;

    Matrix3 mRes(m1.Scaled(f));

    m1.Scale(f);

    ExpectMatrix3Near(mManualResult, m1);
    ExpectMatrix3Near(mManualResult, mRes);
}

TEST(Matrix3, MultiplyByMatOperator)
{
    Matrix3 m1;
    Matrix3 m2;

    m1.m[0] = 1.f; m1.m[1] = 2.f; m1.m[2] = 3.f;
    m1.m[3] = 4.f; m1.m[4] = 5.f; m1.m[5] = 6.f;
    m1.m[6] = 7.f; m1.m[7] = 8.f; m1.m[8] = 9.f;

    m2 = m1;

    Matrix3 mManualResult;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            mManualResult[3 * i + j] =
                m1[3 * i] * m2.m[j] +
                m1[3 * i + 1] * m2.m[3 + j] +
                m1[3 * i + 2] * m2.m[6 + j];
        }
    }

    Matrix3 mRes(m1 * m2);

    ExpectMatrix3Near(mManualResult, mRes);
}

TEST(Matrix3, MultiplyByVector)
{
    Vector3 v = { 1.f, 2.f, 3.f };

    Matrix3 m;

    m.m[0] = 1.f; m.m[1] = 2.f; m.m[2] = 3.f;
    m.m[3] = 4.f; m.m[4] = 5.f; m.m[5] = 6.f;
    m.m[6] = 7.f; m.m[7] = 8.f; m.m[8] = 9.f;

    float newX = m.m[0] * v.x + m.m[1] * v.y + m.m[2] * v.z;
    float newY = m.m[3] * v.x + m.m[4] * v.y + m.m[5] * v.z;
    float newZ = m.m[6] * v.x + m.m[7] * v.y + m.m[8] * v.z;

    Vector3 vRes = m.Multiply(v);

    EXPECT_FLOAT_EQ(newX, vRes.x);
    EXPECT_FLOAT_EQ(newY, vRes.y);
    EXPECT_FLOAT_EQ(newZ, vRes.z);
}

TEST(Matrix3, CreateTranslationMatrix)
{
    Vector2 t(3.f, -2.f);

    Matrix3 m = Matrix3::CreateTranslationMatrix(t);

    Matrix3 mManualResult;

    mManualResult.m[0] = 1.f; mManualResult.m[1] = 0.f; mManualResult.m[2] = t.x;
    mManualResult.m[3] = 0.f; mManualResult.m[4] = 1.f; mManualResult.m[5] = t.y;
    mManualResult.m[6] = 0.f; mManualResult.m[7] = 0.f; mManualResult.m[8] = 1.f;

    ExpectMatrix3Near(mManualResult, m);
}

TEST(Matrix3, CreateScaleMatrix)
{
    Vector2 s = { 2.f, 3.f };
    Matrix3 m = Matrix3::CreateScaleMatrix(s);

    Matrix3 mManualResult;

    mManualResult.m[0] = s.x; mManualResult.m[1] = 0.f; mManualResult.m[2] = 0.f;
    mManualResult.m[3] = 0.f; mManualResult.m[4] = s.y; mManualResult.m[5] = 0.f;
    mManualResult.m[6] = 0.f; mManualResult.m[7] = 0.f; mManualResult.m[8] = 1.f;

    ExpectMatrix3Near(mManualResult, m);
}

TEST(Matrix3, CreateXRotationMatrix)
{
    float angleDeg = 90.f;

    Matrix3 m = Matrix3::CreateXRotationMatrix(angleDeg);

    float c = cosf(angleDeg * DEG2RAD);
    float s = sinf(angleDeg * DEG2RAD);

    Matrix3 mManualResult;

    mManualResult.m[0] = 1.f; mManualResult.m[1] = 0.f; mManualResult.m[2] = 0.f;
    mManualResult.m[3] = 0.f; mManualResult.m[4] = c;   mManualResult.m[5] = -s;
    mManualResult.m[6] = 0.f; mManualResult.m[7] = s;   mManualResult.m[8] = c;

    ExpectMatrix3Near(mManualResult, m);
}

TEST(Matrix3, CreateYRotationMatrix)
{
    float angleDeg = 90.f;

    Matrix3 m = Matrix3::CreateYRotationMatrix(angleDeg);

    float c = cosf(angleDeg * DEG2RAD);
    float s = sinf(angleDeg * DEG2RAD);

    Matrix3 mManualResult;

    mManualResult.m[0] = c;   mManualResult.m[1] = 0.f; mManualResult.m[2] = s;
    mManualResult.m[3] = 0.f; mManualResult.m[4] = 1.f; mManualResult.m[5] = 0.f;
    mManualResult.m[6] = -s;  mManualResult.m[7] = 0.f; mManualResult.m[8] = c;

    ExpectMatrix3Near(mManualResult, m);
}

TEST(Matrix3, CreateZRotationMatrix)
{
    float angleDeg = 90.f;

    Matrix3 m = Matrix3::CreateZRotationMatrix(angleDeg);

    float c = cosf(angleDeg * DEG2RAD);
    float s = sinf(angleDeg * DEG2RAD);

    Matrix3 mManualResult;

    mManualResult.m[0] = c;   mManualResult.m[1] = -s;  mManualResult.m[2] = 0.f;
    mManualResult.m[3] = s;   mManualResult.m[4] = c;   mManualResult.m[5] = 0.f;
    mManualResult.m[6] = 0.f; mManualResult.m[7] = 0.f; mManualResult.m[8] = 1.f;

    ExpectMatrix3Near(mManualResult, m);
}

TEST(Matrix3, Print)
{
    Matrix3 m1;

    m1.m[0] = 1.f;
    m1.m[1] = 2.f;
    m1.m[2] = -0.5f;

    std::cout << m1 << std::endl;
}