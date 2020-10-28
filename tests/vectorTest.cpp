/* @author G. Hemingway, copyright 2020 - All rights reserved */
#include <Vector.h>
#include <cmath>
#include <gtest/gtest.h>
#include <random>

typedef Vector<3UL> vector3;
typedef Vector<4UL> vector4;
const double data[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

// Returns a random double between 0 and max that can be represented exactly via
// IEE 754
double getRandom(int max)
{
    std::random_device rd;
    std::mt19937_64 generator(rd());
    std::uniform_real_distribution<> dist(0, max);
    return dist(generator);
}

template <uint32_t DIM> void createBasis(Vector<DIM>* array)
{
    for (uint32_t v = 0; v < DIM; ++v)
        for (uint32_t comp = 0; comp < DIM; ++comp)
            array[v][comp] = v == comp ? 1 : 0;
}

template <uint32_t DIM> Vector<DIM> createVector()
{
    Vector<DIM> basis[DIM];
    createBasis(basis);

    Vector<DIM> combo;

    for (uint32_t i = 0; i < DIM; ++i)
        combo += basis[i] * getRandom(10);
    return combo;
}

// The fixture for testing the vector class
class VectorTest : public ::testing::Test {
};

TEST_F(VectorTest, OperatorEquals)
{
    vector3 v1;
    vector3 v2 = createVector<3>();
    v1 = v2;
    EXPECT_EQ(v1, v2);
    vector3 v3(v2);
    EXPECT_EQ(v2, v3);
}

TEST_F(VectorTest, ToString)
{
    const vector3 v1;
    EXPECT_EQ(v1.toString(), "[0 0 0]");

    vector3 v2(data);
    EXPECT_EQ(v2.toString(), "[0 1 2]");

    vector3 v3(data + 1);
    EXPECT_EQ(v3.toString(), "[1 2 3]");

    vector3 v4(data + 7);
    EXPECT_EQ(v4.toString(), "[7 8 9]");

    vector3 v5(v4);
    EXPECT_EQ(v5.toString(), "[7 8 9]");

    v5 = v1;
    EXPECT_EQ(v5.toString(), "[0 0 0]");
}

TEST_F(VectorTest, Subscript)
{
    vector3 v1;
    v1[1] = 1;
    v1[2] = 2;
    EXPECT_EQ(v1.toString(), "[0 1 2]");

    vector3 v2(v1);
    EXPECT_DOUBLE_EQ(v2[0], 0);
    EXPECT_DOUBLE_EQ(v2[1], 1);
    EXPECT_DOUBLE_EQ(v2[2], 2);

    v2[0]++;
    v2[1]++;
    v2[2]++;
    EXPECT_DOUBLE_EQ(v2[0], 1);
    EXPECT_DOUBLE_EQ(v2[1], 2);
    EXPECT_DOUBLE_EQ(v2[2], 3);
    EXPECT_DOUBLE_EQ(v1[0], 0);
    EXPECT_DOUBLE_EQ(v1[1], 1);
    EXPECT_DOUBLE_EQ(v1[2], 2);

    const vector3 v3(v2);
    EXPECT_DOUBLE_EQ(v3[0], 1);
    EXPECT_DOUBLE_EQ(v3[1], 2);
    EXPECT_DOUBLE_EQ(v3[2], 3);
}

TEST_F(VectorTest, Equality)
{
    vector3 v1 = createVector<3>();
    EXPECT_TRUE(v1 == v1);
    EXPECT_FALSE(v1 != v1);

    const vector3 v2(v1);
    EXPECT_TRUE(v1 == v2);

    // Test the next two lines if you would like, but we do not expect your
    // code to range-check situations like this
    // Note: this may corrupt memory and cause a segfault
    // v1[3] = 0;
    // EXPECT_TRUE(v1 == v2);

    v1[0] = 1;
    EXPECT_TRUE(v1 != v2);

    v1 = v2;
    EXPECT_TRUE(v1 == v2);
}

template <uint32_t DIM> void SimpleAddSub()
{
    const Vector<DIM> a = createVector<DIM>();
    const Vector<DIM> b = createVector<DIM>();

    const Vector<DIM> add = a + b;
    const Vector<DIM> sub = a - b;

    for (uint32_t i = 0; i < DIM; ++i) {
        EXPECT_DOUBLE_EQ(add[i], a[i] + b[i]);
        EXPECT_DOUBLE_EQ(sub[i], a[i] - b[i]);
    }
}

TEST_F(VectorTest, SimpleAddSub)
{
    SimpleAddSub<1>();
    SimpleAddSub<2>();
    SimpleAddSub<3>();
    SimpleAddSub<4>();
    SimpleAddSub<10>();
}

TEST_F(VectorTest, SpaceOps)
{
    const double basis[] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
    const vector3 zero;
    const vector3 x(basis);
    const vector3 y(basis + 3);
    const vector3 z(basis + 6);

    vector3 v1 = -x;
    EXPECT_EQ(v1.toString(), "[-1 -0 -0]");

    EXPECT_EQ((v1 + -v1), zero); // Tests additive inverse.

    double a = 1, b = 2.5, c = 3;
    vector3 combo1 = x * a + y * b + z * c;
    EXPECT_EQ(combo1.toString(), "[1 2.5 3]");

    vector3 combo2 = a * x + b * y + c * z; // Tests commutativity
    EXPECT_EQ(combo2, combo1);

    vector3 sum = combo1 + combo2;
    EXPECT_EQ(sum, 2 * combo1);
    EXPECT_EQ(sum, combo2 * 2);
    EXPECT_EQ(combo1 - combo2, zero);

    for (double scale = 0; scale < 2.0; scale += 0.2) {
        EXPECT_EQ(scale * sum, sum * scale);
    }

    v1 = zero;
    for (int i = 1; i < 5; ++i) {
        EXPECT_EQ((v1 += x), i * x);
    }
    ((v1 -= x) -= x) -= x;
    EXPECT_EQ(v1, x);

    for (int i = 1; i < 5; ++i)
        EXPECT_EQ((v1 *= 2.0), std::pow(2.0, i) * x);

    v1 = v1 / 2;
    EXPECT_EQ(v1, x * 8);

    (((v1 /= 2) /= 2) /= 2) /= 2;
    EXPECT_EQ(v1, 0.5 * x);

    EXPECT_NO_THROW({
        v1 = v1 / 0.0;
        EXPECT_TRUE(std::isinf(v1[0]));
        EXPECT_TRUE(std::isnan(v1[1]));
        EXPECT_TRUE(std::isnan(v1[2]));
    });
}

TEST_F(VectorTest, MoreSpaceOps)
{
    const double basis[] = { 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9 };
    const vector3 zero;
    const vector3 x(basis);
    const vector3 a(x);
    const vector3 y(basis + 3);
    const vector3 z(basis + 6);

    vector3 combo = x.add(y.add(z.add(zero)));
    EXPECT_EQ(combo.toString(), "[13.2 16.5 19.8]");
    EXPECT_EQ(a, x);

    const vector3 invCombo = combo.invert();
    EXPECT_NE(invCombo, combo);
    EXPECT_EQ(invCombo.toString(), "[-13.2 -16.5 -19.8]");

    const vector3 piCombo = combo.scale(3.141529);
    EXPECT_NE(piCombo, combo);
    EXPECT_EQ(piCombo.toString(), "[41.4682 51.8352 62.2023]");

    vector3 anotherPi(piCombo);
    for (uint32_t i = 0; i < 5; ++i) {
        anotherPi *= 3.141529;
    }
    EXPECT_EQ(anotherPi.toString(), "[12688.8 15861 19033.2]");
}

template <uint32_t DIM> double correctDotProduct(const Vector<DIM>& v1, const Vector<DIM>& v2)
{
    double sum = 0;
    for (uint32_t i = 0; i < DIM; ++i)
        sum += v1[i] * v2[i];
    return sum;
}

TEST_F(VectorTest, DotProduct)
{
    const std::string str[] = { "[0 1 2 3]", "[1 2 3 4]", "[2 3 4 5]", "[3 4 5 6]", "[4 5 6 7]",
        "[5 6 7 8]", "[6 7 8 9]" };

    vector4 vArray[7];
    for (int i = 0; i < 7; ++i) {
        vArray[i] = vector4(data + i);
        EXPECT_EQ(vArray[i].toString(), str[i]);
    }
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            vector4& a = vArray[i];
            vector4& b = vArray[j];
            double dot = correctDotProduct(a, b);
            double leftDot = a.dot(b);
            double rightDot = b.dot(a);
            EXPECT_DOUBLE_EQ(dot, leftDot);
            EXPECT_DOUBLE_EQ(leftDot, rightDot);
            EXPECT_DOUBLE_EQ(dot, a * b);
            EXPECT_DOUBLE_EQ(dot, b * a);
        }
    }
    // Property tests.
    // 1. Commutativity was tested above
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            for (int k = 0; k < 7; ++k) {
                vector4& a = vArray[i];
                vector4& b = vArray[j];
                vector4& c = vArray[k];
                // 2. Distributivity
                EXPECT_DOUBLE_EQ((a * (b + c)), (a * b + a * c));
                // 3. Bilinearity (part 1)
                double c1 = getRandom(10);
                EXPECT_DOUBLE_EQ((a * ((c1 * b) + c)), ((c1 * (a * b)) + (a * c)));
                // 4. Bilinearity (part 2)
                double c2 = getRandom(10);
                EXPECT_DOUBLE_EQ((c1 * a) * (c2 * b), (c1 * c2) * (a * b));
            }
        }
    }
}

template <uint32_t DIM> double normSq(const Vector<DIM>& v)
{
    double acc = 0;
    for (uint32_t i = 0; i < DIM; ++i)
        acc += v[i] * v[i];
    return acc;
}

template <uint32_t DIM> void testNorm()
{
    const vector3 zero;
    EXPECT_DOUBLE_EQ(zero.norm(), 0.0);

    Vector<DIM> basis[DIM];
    createBasis(basis);

    for (uint32_t i = 0; i < DIM; ++i)
        EXPECT_DOUBLE_EQ(basis[i].norm(), 1.0);

    for (int i = 0; i < 100; ++i) {
        Vector<DIM> v = createVector<DIM>();

        double n2 = v.normSq();
        EXPECT_DOUBLE_EQ(n2, v * v);
        EXPECT_DOUBLE_EQ(n2, normSq(v));

        const Vector<DIM> a = createVector<DIM>();
        EXPECT_DOUBLE_EQ(std::sqrt(a.normSq()), a.norm());
    }
}

TEST_F(VectorTest, Norm)
{
    testNorm<1>();
    testNorm<2>();
    testNorm<3>();
    testNorm<10>();
}

template <uint32_t DIM> void testNormalize()
{
    const Vector<DIM> a = createVector<DIM>();
    Vector<DIM> normy = a.normalize();
    EXPECT_DOUBLE_EQ(normy.norm(), 1.00);
    EXPECT_NE(a, normy);
}

TEST_F(VectorTest, Normalize)
{
    testNormalize<1>();
    testNormalize<2>();
    testNormalize<3>();
    testNormalize<10>();

    vector3 a;
    EXPECT_THROW({ a.normalize(); }, std::overflow_error);
}

TEST_F(VectorTest, CrossProduct)
{
    vector4 v4, v5;
    v4[0] = 1;
    v5[1] = 1;
    EXPECT_THROW(
        {
            v5.cross(v5);
            assert(!"The above should have thrown an exception");
        },
        std::domain_error);

    vector3 basis[3];
    createBasis(basis);
    const vector3 zero;
    const vector3 x = basis[0];
    const vector3 y = basis[1];
    const vector3 z = basis[2];
    EXPECT_EQ(x.cross(y), z);

    for (int i = 0; i < 100; ++i) {
        double a1 = getRandom(10);
        double b1 = getRandom(10);
        double c1 = getRandom(10);
        double a2 = getRandom(10);
        double b2 = getRandom(10);
        double c2 = getRandom(10);
        double a3 = getRandom(10);
        double b3 = getRandom(10);
        double c3 = getRandom(10);
        vector3 u = a1 * x + b1 * y + c1 * z;
        vector3 v = a2 * x + b2 * y + c2 * z;
        vector3 w = a3 * x + b3 * y + c3 * z;
        EXPECT_EQ(u.cross(v), (u ^ v));
        EXPECT_EQ((u ^ v), -(v ^ u));
        // Jacobi identity
        EXPECT_EQ((u ^ (v ^ w)) + (v ^ (w ^ u)) + (w ^ (u ^ v)), zero);
    }
}

// Uncommenting either of these individual blocks should result in a failure to compile
TEST_F(VectorTest, CompilationFailures)
{
    /*
        double *newData; // This is wrong - should fail to compile if uncommented
        vector3 foo = newData; // This is wrong - should fail to compile if uncommented
     */
    /*
        // const vector3 bar = createVector<3>(); // This is wrong - should fail to compile if
       uncommented
        // bar *= 3.0; // This is wrong - should fail to compile if uncommented
    */
}