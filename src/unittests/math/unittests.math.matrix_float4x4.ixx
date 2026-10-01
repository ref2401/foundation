module;
#include "foundation/unittests.h"


export module unittests.math:matrix_float4x4;
import foundation.core;
import foundation.math;

namespace fnd::unittests {

export void unittests_math_matrix_float4x4();

// A general (not affine) matrix: its bottom row is 0, 1, 0, 1. The rows are
// {1, 0, -1, 4}, {0, 1, 0, 5}, {2, 0, 1, 6} and {0, 1, 0, 1}; determinant -12.
constexpr float4x4_t kMatrixA4x4{
    float4_t{1, 0, 2, 0}, float4_t{0, 1, 0, 1}, float4_t{-1, 0, 1, 0},
    float4_t{4, 5, 6, 1}};

// A general matrix with determinant 64.25.
constexpr float4x4_t kMatrixB4x4{
    float4_t{2, -1, 0, 0.5f}, float4_t{0.5f, 3, 1, 0}, float4_t{-2, 0, 4, 1},
    float4_t{-1, 2, 0.5f, 2}};

// All expected values below are exact in binary, so == is reliable.
constexpr bool_t test_columns(const float4x4_t& m, const float4_t c0,
    const float4_t c1, const float4_t c2, const float4_t c3)
{
    return all(m.col0 == c0) && all(m.col1 == c1) && all(m.col2 == c2)
        && all(m.col3 == c3);
}

// Returns a reference to component row of column col.
float_t& component(float4x4_t& m, const uint_t col, const uint_t row)
{
    float4_t* const cols[] = {&m.col0, &m.col1, &m.col2, &m.col3};
    return (*cols[col])[row];
}

void unittests_math_matrix_float4x4_constants()
{
    FND_TEST_TRUE(test_columns(float4x4_t::kZero, float4_t{0}, float4_t{0},
        float4_t{0}, float4_t{0}));
    FND_TEST_TRUE(test_columns(float4x4_t::kIdentity, float4_t{1, 0, 0, 0},
        float4_t{0, 1, 0, 0}, float4_t{0, 0, 1, 0}, float4_t{0, 0, 0, 1}));
    FND_TEST_TRUE(float4x4_t::kZero == float4x4_t{});
    FND_TEST_TRUE(
        transpose(float4x4_t::kIdentity) == float4x4_t::kIdentity);
    // The constants are usable in constant expressions.
    static_assert(float4x4_t::kIdentity.col3.w == 1.0f);
}

void unittests_math_matrix_float4x4_constructors()
{
    // The default ctor gives the zero matrix.
    const float4x4_t m_zero;
    FND_TEST_TRUE(test_columns(
        m_zero, float4_t{0}, float4_t{0}, float4_t{0}, float4_t{0}));

    // From four columns.
    constexpr float4_t kC0{1, 2, 3, 4};
    constexpr float4_t kC1{-4, 5.5f, 0, -1};
    constexpr float4_t kC2{kFloatMaxValue, kFloatMinValue, -0.25f, 0};
    constexpr float4_t kC3{7, -8, 9, 10};
    FND_TEST_TRUE(
        test_columns(float4x4_t{kC0, kC1, kC2, kC3}, kC0, kC1, kC2, kC3));
    FND_TEST_TRUE(
        test_columns(float4x4_t{kC3, kC2, kC1, kC0}, kC3, kC2, kC1, kC0));

    // From sixteen floats in column-major order: each group of four is a
    // column.
    const float4x4_t m{1, 0, 2, 0, 0, 1, 0, 1, -1, 0, 1, 0, 4, 5, 6, 1};
    FND_TEST_TRUE(m == kMatrixA4x4);
    // Each argument lands in its own component: the 15th is m23, which is
    // row 2 of column 3.
    const float4x4_t m_e{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0};
    FND_TEST_TRUE(test_columns(
        m_e, float4_t{0}, float4_t{0}, float4_t{0}, float4_t{0, 0, 1, 0}));
}

void unittests_math_matrix_float4x4_unary_minus_operator()
{
    FND_TEST_TRUE(test_columns(-kMatrixA4x4, -kMatrixA4x4.col0,
        -kMatrixA4x4.col1, -kMatrixA4x4.col2, -kMatrixA4x4.col3));
    FND_TEST_TRUE(-(-kMatrixA4x4) == kMatrixA4x4);
    // -0 equals +0.
    FND_TEST_TRUE(-float4x4_t::kZero == float4x4_t::kZero);
}

void unittests_math_matrix_float4x4_equality_operators()
{
    FND_TEST_TRUE(kMatrixA4x4 == kMatrixA4x4);
    FND_TEST_FALSE(kMatrixA4x4 != kMatrixA4x4);
    FND_TEST_FALSE(kMatrixA4x4 == kMatrixB4x4);
    FND_TEST_TRUE(kMatrixA4x4 != kMatrixB4x4);

    // A difference in any one of the sixteen components makes them unequal.
    for (uint_t col = 0; col < 4; ++col) {
        for (uint_t row = 0; row < 4; ++row) {
            float4x4_t m = kMatrixA4x4;
            component(m, col, row) += 0.5f;
            FND_TEST_FALSE(m == kMatrixA4x4);
            FND_TEST_TRUE(m != kMatrixA4x4);
        }
    }

    // -0 equals +0; a NaN component makes a matrix unequal to itself.
    float4x4_t m_zero{};
    component(m_zero, 3, 3) = -0.0f;
    FND_TEST_TRUE(m_zero == float4x4_t::kZero);
    float4x4_t m_nan = kMatrixA4x4;
    component(m_nan, 2, 3) = kFloatNaN;
    FND_TEST_FALSE(m_nan == m_nan);
    FND_TEST_TRUE(m_nan != m_nan);
}

void unittests_math_matrix_float4x4_scalar_multiplication_operator()
{
    // Every component is scaled.
    constexpr float_t kFactor = 2;
    FND_TEST_TRUE(test_columns(kMatrixA4x4 * kFactor,
        kMatrixA4x4.col0 * kFactor, kMatrixA4x4.col1 * kFactor,
        kMatrixA4x4.col2 * kFactor, kMatrixA4x4.col3 * kFactor));
    FND_TEST_TRUE(kFactor * kMatrixA4x4 == kMatrixA4x4 * kFactor);
    FND_TEST_TRUE(kMatrixA4x4 * 1.0f == kMatrixA4x4);
    FND_TEST_TRUE(kMatrixA4x4 * -1.0f == -kMatrixA4x4);
    FND_TEST_TRUE(kMatrixA4x4 * 0.0f == float4x4_t::kZero);
    // Overflow gives infinity: col3 is {4, 5, 6, 1}, so only w stays finite.
    const float4x4_t m_big = kMatrixA4x4 * kFloatMaxValue;
    FND_TEST_TRUE(all(isinf(float3(m_big.col3))));
    FND_TEST_TRUE(m_big.col3.w == kFloatMaxValue);
}

void unittests_math_matrix_float4x4_matrix_multiplication_operator()
{
    // Column j of a * b is a times column j of b.
    FND_TEST_TRUE(test_columns(kMatrixA4x4 * kMatrixB4x4,
        float4_t{4, 1.5f, 7, -0.5f}, float4_t{-0.5f, 3, 2, 3},
        float4_t{-2, 5, 6, 1}, float4_t{6.5f, 12, 10.5f, 4}));
    FND_TEST_TRUE(test_columns(kMatrixB4x4 * kMatrixA4x4,
        float4_t{-2, -1, 8, 2.5f}, float4_t{-0.5f, 5, 1.5f, 2},
        float4_t{-4, 1, 4, 0.5f}, float4_t{-2.5f, 13, 29.5f, 10}));
    // The product does not commute.
    FND_TEST_TRUE(kMatrixA4x4 * kMatrixB4x4 != kMatrixB4x4 * kMatrixA4x4);

    // a * b applied to v is a applied to (b applied to v).
    constexpr float4_t kV{3, -4, 12, 1};
    FND_TEST_TRUE(all(mul(kMatrixA4x4 * kMatrixB4x4, kV)
        == mul(kMatrixA4x4, mul(kMatrixB4x4, kV))));

    // The identity is neutral on both sides; the zero matrix gives zero.
    FND_TEST_TRUE(kMatrixA4x4 * float4x4_t::kIdentity == kMatrixA4x4);
    FND_TEST_TRUE(float4x4_t::kIdentity * kMatrixA4x4 == kMatrixA4x4);
    FND_TEST_TRUE(kMatrixA4x4 * float4x4_t::kZero == float4x4_t::kZero);

    // Associative, scalars factor out, and transpose reverses the order.
    const float4x4_t m_ab = kMatrixA4x4 * kMatrixB4x4;
    FND_TEST_TRUE(
        m_ab * kMatrixA4x4 == kMatrixA4x4 * (kMatrixB4x4 * kMatrixA4x4));
    FND_TEST_TRUE(
        (kMatrixA4x4 * 2.0f) * kMatrixB4x4 == 2.0f * m_ab);
    FND_TEST_TRUE(
        transpose(m_ab) == transpose(kMatrixB4x4) * transpose(kMatrixA4x4));

    // The parameters are copies, so m * m reads m before the result exists.
    float4x4_t m = kMatrixA4x4;
    m = m * m;
    FND_TEST_TRUE(test_columns(m, float4_t{-1, 0, 4, 0},
        float4_t{4, 6, 6, 2}, float4_t{-2, 0, -1, 0}, float4_t{2, 10, 20, 6}));
}

void unittests_math_matrix_float4x4_division_operator()
{
    constexpr float_t kDivisor = 2;
    FND_TEST_TRUE(test_columns(kMatrixA4x4 / kDivisor,
        kMatrixA4x4.col0 / kDivisor, kMatrixA4x4.col1 / kDivisor,
        kMatrixA4x4.col2 / kDivisor, kMatrixA4x4.col3 / kDivisor));
    FND_TEST_TRUE(kMatrixA4x4 / 0.5f == kMatrixA4x4 * 2.0f);
    FND_TEST_TRUE(kMatrixA4x4 / 1.0f == kMatrixA4x4);
    FND_TEST_TRUE(kMatrixA4x4 / -1.0f == -kMatrixA4x4);
    FND_TEST_TRUE(kMatrixA4x4 / kFloatInfinity == float4x4_t::kZero);
}

void unittests_math_matrix_float4x4_scalar_compound_assignment_operators()
{
    float4x4_t m = kMatrixA4x4;

    // Each operator returns a reference to its left operand.
    FND_TEST_TRUE(&(m *= 2.0f) == &m);
    FND_TEST_TRUE(m == kMatrixA4x4 * 2.0f);
    FND_TEST_TRUE(&(m /= 4.0f) == &m);
    FND_TEST_TRUE(m == kMatrixA4x4 * 0.5f);
}

void unittests_math_matrix_float4x4_matrix_compound_assignment_operators()
{
    float4x4_t m = kMatrixA4x4;

    // The operator returns a reference to its left operand.
    FND_TEST_TRUE(&(m *= kMatrixB4x4) == &m);
    FND_TEST_TRUE(m == kMatrixA4x4 * kMatrixB4x4);
    // m *= m works: the product is computed before it is stored.
    m = kMatrixA4x4;
    m *= m;
    FND_TEST_TRUE(m == kMatrixA4x4 * kMatrixA4x4);
}

void unittests_math_matrix_float4x4_scalar_compound_assignment_matches_operators()
{
    // m op= s must give the same result as m op s.
    float4x4_t m = kMatrixA4x4;
    m *= 2.5f;
    FND_TEST_TRUE(m == kMatrixA4x4 * 2.5f);

    m = kMatrixA4x4;
    m /= 2.5f;
    FND_TEST_TRUE(m == kMatrixA4x4 / 2.5f);
}

void unittests_math_matrix_float4x4_matrix_compound_assignment_matches_operators()
{
    // a *= b must give the same result as a * b.
    float4x4_t m = kMatrixA4x4;
    m *= kMatrixB4x4;
    FND_TEST_TRUE(m == kMatrixA4x4 * kMatrixB4x4);

    m = kMatrixB4x4;
    m *= kMatrixA4x4;
    FND_TEST_TRUE(m == kMatrixB4x4 * kMatrixA4x4);
}

void unittests_math_matrix_float4x4_approx_equal()
{
    FND_TEST_TRUE(approx_equal(kMatrixA4x4, kMatrixA4x4));
    FND_TEST_TRUE(approx_equal(kMatrixA4x4, kMatrixA4x4 * 1.0000001f));

    // A difference in any one of the sixteen components is detected.
    for (uint_t col = 0; col < 4; ++col) {
        for (uint_t row = 0; row < 4; ++row) {
            float4x4_t m = kMatrixA4x4;
            component(m, col, row) += 0.25f;
            FND_TEST_FALSE(approx_equal(m, kMatrixA4x4));
            // max_abs_diff; the boundary is inclusive.
            FND_TEST_TRUE(approx_equal(m, kMatrixA4x4, 0.25f));
            FND_TEST_FALSE(approx_equal(m, kMatrixA4x4, 0.125f));
        }
    }

    // inf equals inf and NaN equals nothing, as for the float_t approx_equal.
    float4x4_t m_inf = kMatrixA4x4;
    component(m_inf, 3, 3) = kFloatInfinity;
    FND_TEST_TRUE(approx_equal(m_inf, m_inf));
    float4x4_t m_nan = kMatrixA4x4;
    component(m_nan, 1, 2) = kFloatNaN;
    FND_TEST_FALSE(approx_equal(m_nan, m_nan));
}

void unittests_math_matrix_float4x4_cmax()
{
    FND_TEST_TRUE(cmax(kMatrixA4x4) == 6.0f);
    FND_TEST_TRUE(cmax(-kMatrixA4x4) == 1.0f);
    FND_TEST_TRUE(cmax(float4x4_t::kZero) == 0.0f);
    FND_TEST_TRUE(cmax(float4x4_t::kIdentity) == 1.0f);

    // The largest component is found in any of the sixteen positions.
    for (uint_t col = 0; col < 4; ++col) {
        for (uint_t row = 0; row < 4; ++row) {
            float4x4_t m = kMatrixA4x4;
            component(m, col, row) = 100.0f;
            FND_TEST_TRUE(cmax(m) == 100.0f);
        }
    }

    // A NaN component is ignored, as for the float_t max; inf wins.
    float4x4_t m = kMatrixA4x4;
    component(m, 3, 2) = kFloatNaN;
    FND_TEST_TRUE(cmax(m) == 5.0f);
    component(m, 0, 1) = kFloatInfinity;
    FND_TEST_TRUE(cmax(m) == kFloatInfinity);
}

void unittests_math_matrix_float4x4_cmin()
{
    FND_TEST_TRUE(cmin(kMatrixA4x4) == -1.0f);
    FND_TEST_TRUE(cmin(-kMatrixA4x4) == -6.0f);
    FND_TEST_TRUE(cmin(float4x4_t::kZero) == 0.0f);
    FND_TEST_TRUE(cmin(float4x4_t::kIdentity) == 0.0f);

    // The smallest component is found in any of the sixteen positions.
    for (uint_t col = 0; col < 4; ++col) {
        for (uint_t row = 0; row < 4; ++row) {
            float4x4_t m = kMatrixA4x4;
            component(m, col, row) = -100.0f;
            FND_TEST_TRUE(cmin(m) == -100.0f);
        }
    }

    // A NaN component is ignored, as for the float_t min; -inf wins.
    float4x4_t m = kMatrixA4x4;
    component(m, 2, 0) = kFloatNaN;
    FND_TEST_TRUE(cmin(m) == 0.0f);
    component(m, 1, 3) = -kFloatInfinity;
    FND_TEST_TRUE(cmin(m) == -kFloatInfinity);
}

void unittests_math_matrix_float4x4_column()
{
    FND_TEST_TRUE(all(column0(kMatrixA4x4) == float4_t{1, 0, 2, 0}));
    FND_TEST_TRUE(all(column1(kMatrixA4x4) == float4_t{0, 1, 0, 1}));
    FND_TEST_TRUE(all(column2(kMatrixA4x4) == float4_t{-1, 0, 1, 0}));
    FND_TEST_TRUE(all(column3(kMatrixA4x4) == float4_t{4, 5, 6, 1}));
    // Usable in constant expressions.
    static_assert(column3(kMatrixA4x4).z == 6.0f);
}

void unittests_math_matrix_float4x4_determinant()
{
    FND_TEST_TRUE(determinant(float4x4_t::kIdentity) == 1.0f);
    FND_TEST_TRUE(determinant(float4x4_t::kZero) == 0.0f);
    FND_TEST_TRUE(determinant(kMatrixA4x4) == -12.0f);
    FND_TEST_TRUE(determinant(kMatrixB4x4) == 64.25f);

    // Transposing keeps it, swapping two columns negates it, scaling a column
    // scales it, and scaling the matrix scales it by the fourth power.
    FND_TEST_TRUE(determinant(transpose(kMatrixB4x4)) == 64.25f);
    const float4x4_t m_swapped{kMatrixB4x4.col1, kMatrixB4x4.col0,
        kMatrixB4x4.col2, kMatrixB4x4.col3};
    FND_TEST_TRUE(determinant(m_swapped) == -64.25f);
    const float4x4_t m_scaled{kMatrixB4x4.col0 * 2.0f, kMatrixB4x4.col1,
        kMatrixB4x4.col2, kMatrixB4x4.col3};
    FND_TEST_TRUE(determinant(m_scaled) == 128.5f);
    FND_TEST_TRUE(determinant(kMatrixB4x4 * 2.0f) == 16 * 64.25f);

    // det(a * b) == det(a) * det(b).
    FND_TEST_TRUE(determinant(kMatrixA4x4 * kMatrixB4x4)
        == determinant(kMatrixA4x4) * determinant(kMatrixB4x4));

    // An affine matrix has the determinant of its linear part.
    constexpr float3_t kScale{2, 3, 4};
    constexpr float3_t kTranslation{1, -2, 0.5f};
    const float3x3_t mrs = make_float3x3_axis_angle(float3_t::kUnitZ, 0.75f)
        * make_float3x3_scale(kScale);
    FND_TEST_TRUE(approx_equal(
        determinant(make_float4x4_trs(kTranslation, mrs)), determinant(mrs)));
    FND_TEST_TRUE(
        determinant(make_float4x4_translation(kTranslation)) == 1.0f);
    // Usable in constant expressions.
    static_assert(determinant(float4x4_t::kIdentity) == 1.0f);
}

void unittests_math_matrix_float4x4_inverse()
{
    FND_TEST_TRUE(inverse(float4x4_t::kIdentity) == float4x4_t::kIdentity);

    // A translation is undone by the opposite translation, a scale by the
    // reciprocal scale (exact for powers of two).
    constexpr float3_t kTranslation{1, -2, 0.5f};
    FND_TEST_TRUE(inverse(make_float4x4_translation(kTranslation))
        == make_float4x4_translation(-kTranslation));
    constexpr float3_t kScale{2, -0.5f, 4};
    FND_TEST_TRUE(inverse(make_float4x4_scale(kScale))
        == make_float4x4_scale(rcp(kScale)));

    // m * inverse(m) and inverse(m) * m are the identity, and inverting twice
    // gives m back.
    const float4x4_t m_inv_a = inverse(kMatrixA4x4);
    FND_TEST_TRUE(approx_equal(kMatrixA4x4 * m_inv_a, float4x4_t::kIdentity));
    FND_TEST_TRUE(approx_equal(m_inv_a * kMatrixA4x4, float4x4_t::kIdentity));
    FND_TEST_TRUE(approx_equal(inverse(m_inv_a), kMatrixA4x4));
    const float4x4_t m_inv_b = inverse(kMatrixB4x4);
    FND_TEST_TRUE(approx_equal(kMatrixB4x4 * m_inv_b, float4x4_t::kIdentity));
    FND_TEST_TRUE(approx_equal(m_inv_b * kMatrixB4x4, float4x4_t::kIdentity));
    FND_TEST_TRUE(approx_equal(inverse(m_inv_b), kMatrixB4x4));

    // Inverting commutes with transposing, the determinant of the inverse is
    // the reciprocal of the determinant, and the inverse of a product is the
    // product of the inverses, reversed.
    FND_TEST_TRUE(approx_equal(
        inverse(transpose(kMatrixB4x4)), transpose(inverse(kMatrixB4x4))));
    FND_TEST_TRUE(approx_equal(
        determinant(m_inv_b), 1.0f / determinant(kMatrixB4x4)));
    FND_TEST_TRUE(approx_equal(
        inverse(kMatrixA4x4 * kMatrixB4x4), m_inv_b * m_inv_a));

    // An affine matrix has the inverse of the same float3x4_t transform, with
    // the bottom row 0, 0, 0, 1.
    const float3x3_t mrs = make_float3x3_axis_angle(float3_t::kUnitZ, 0.75f)
        * make_float3x3_scale(kScale);
    const float3x4_t m_inv_affine
        = inverse(make_float3x4_trs(kTranslation, mrs));
    FND_TEST_TRUE(approx_equal(inverse(make_float4x4_trs(kTranslation, mrs)),
        float4x4_t{float4(m_inv_affine.col0, 0), float4(m_inv_affine.col1, 0),
            float4(m_inv_affine.col2, 0), float4(m_inv_affine.col3, 1)}));

    // A perspective projection (focal length 2, near 1, far 2, depth to
    // [-1, 1]); its bottom row is 0, 0, -1, 0. The rows of its inverse are
    // {0.5, 0, 0, 0}, {0, 0.5, 0, 0}, {0, 0, 0, -1} and {0, 0, -0.25, 0.75}.
    constexpr float4x4_t kProjection{
        float4_t{2, 0, 0, 0}, float4_t{0, 2, 0, 0}, float4_t{0, 0, -3, -1},
        float4_t{0, 0, -4, 0}};
    FND_TEST_TRUE(approx_equal(inverse(kProjection),
        float4x4_t{float4_t{0.5f, 0, 0, 0}, float4_t{0, 0.5f, 0, 0},
            float4_t{0, 0, 0, -0.25f}, float4_t{0, 0, -1, 0.75f}}));
}

void unittests_math_matrix_float4x4_make_float4x4_axis_angle()
{
    // The float3x3_t rotation in the upper-left 3x3; no translation, bottom
    // row 0, 0, 0, 1.
    constexpr float3_t kAxis{0.6f, 0, -0.8f};
    constexpr float_t kAngle = 0.75f;
    const float3x3_t rm3 = make_float3x3_axis_angle(kAxis, kAngle);
    const float4x4_t rm = make_float4x4_axis_angle(kAxis, kAngle);
    FND_TEST_TRUE(test_columns(rm, float4(rm3.col0, 0), float4(rm3.col1, 0),
        float4(rm3.col2, 0), float4_t::kUnitW));

    // A quarter turn about z maps x to y.
    const float4x4_t rm_z
        = make_float4x4_axis_angle(float3_t::kUnitZ, kFloatPi / 2);
    FND_TEST_TRUE(all(approx_equal(
        mul(rm_z, float4_t::kUnitX), float4_t::kUnitY)));

    // Orthonormal with determinant 1: its transpose is its inverse, and
    // rotating by -angle undoes it.
    FND_TEST_TRUE(approx_equal(determinant(rm), 1.0f));
    FND_TEST_TRUE(approx_equal(transpose(rm) * rm, float4x4_t::kIdentity));
    FND_TEST_TRUE(approx_equal(
        rm * make_float4x4_axis_angle(kAxis, -kAngle), float4x4_t::kIdentity));
}

void unittests_math_matrix_float4x4_make_float4x4_scale()
{
    // A diagonal matrix with 1 in the bottom-right corner.
    constexpr float3_t kScale0{2, -0.5f, 4};
    const float4x4_t sm0 = make_float4x4_scale(kScale0);
    FND_TEST_TRUE(test_columns(sm0, float4_t{kScale0.x, 0, 0, 0},
        float4_t{0, kScale0.y, 0, 0}, float4_t{0, 0, kScale0.z, 0},
        float4_t::kUnitW));
    FND_TEST_TRUE(make_float4x4_scale(float3_t{1}) == float4x4_t::kIdentity);

    // Points are scaled per component and keep w == 1.
    constexpr float3_t kPoint{1, 2, 3};
    FND_TEST_TRUE(all(
        mul(sm0, float4(kPoint, 1)) == float4(kScale0 * kPoint, 1)));

    // The determinant is the product of the factors; scales combine by
    // multiplying their factors, in either order.
    FND_TEST_TRUE(determinant(sm0) == cmul(kScale0));
    constexpr float3_t kScale1{3, 4, -1};
    const float4x4_t sm1 = make_float4x4_scale(kScale1);
    FND_TEST_TRUE(sm0 * sm1 == make_float4x4_scale(kScale0 * kScale1));
    FND_TEST_TRUE(sm0 * sm1 == sm1 * sm0);
    // Usable in constant expressions.
    static_assert(make_float4x4_scale(float3_t{2, 3, 4}).col2.z == 4.0f);
}

void unittests_math_matrix_float4x4_make_float4x4_translation()
{
    // The identity with {t, 1} as the last column.
    constexpr float3_t kTranslation0{1, -2, 0.5f};
    const float4x4_t tm0 = make_float4x4_translation(kTranslation0);
    FND_TEST_TRUE(test_columns(tm0, float4_t::kUnitX, float4_t::kUnitY,
        float4_t::kUnitZ, float4(kTranslation0, 1)));

    // Points (w == 1) are moved, directions (w == 0) are not.
    constexpr float3_t kPoint{3, -4, 12};
    FND_TEST_TRUE(all(mul(tm0, float4(kPoint, 1))
        == float4(kPoint + kTranslation0, 1)));
    FND_TEST_TRUE(all(mul(tm0, float4(kPoint, 0)) == float4(kPoint, 0)));

    // Translations combine by adding, in either order.
    constexpr float3_t kTranslation1{-3, 4, 8};
    const float4x4_t tm1 = make_float4x4_translation(kTranslation1);
    FND_TEST_TRUE(
        tm0 * tm1 == make_float4x4_translation(kTranslation0 + kTranslation1));
    FND_TEST_TRUE(tm0 * tm1 == tm1 * tm0);
    // Usable in constant expressions.
    static_assert(make_float4x4_translation(kTranslation0).col3.w == 1.0f);
}

void unittests_math_matrix_float4x4_make_float4x4_trs()
{
    // mrs in the upper-left 3x3, {t, 1} as the last column.
    constexpr float3_t kTranslation{1, -2, 0.5f};
    constexpr float3_t kScale{2, 3, 4};
    const float3x3_t mrs = make_float3x3_axis_angle(float3_t::kUnitZ, 0.75f)
        * make_float3x3_scale(kScale);
    const float4x4_t m = make_float4x4_trs(kTranslation, mrs);
    FND_TEST_TRUE(test_columns(m, float4(mrs.col0, 0), float4(mrs.col1, 0),
        float4(mrs.col2, 0), float4(kTranslation, 1)));

    // mrs is applied first, then t: the same as T * RS.
    FND_TEST_TRUE(m
        == make_float4x4_translation(kTranslation)
            * make_float4x4_trs(float3_t::kZero, mrs));
    constexpr float3_t kPoint{3, -4, 12};
    FND_TEST_TRUE(all(approx_equal(mul(m, float4(kPoint, 1)),
        float4(mul(mrs, kPoint) + kTranslation, 1))));

    // With the identity it is a pure translation; with a zero translation
    // and a scale it is that scale.
    FND_TEST_TRUE(make_float4x4_trs(kTranslation, float3x3_t::kIdentity)
        == make_float4x4_translation(kTranslation));
    FND_TEST_TRUE(
        make_float4x4_trs(float3_t::kZero, make_float3x3_scale(kScale))
        == make_float4x4_scale(kScale));
    // Usable in constant expressions.
    static_assert(
        make_float4x4_trs(kTranslation, float3x3_t::kIdentity).col3.z == 0.5f);
}

void unittests_math_matrix_float4x4_mul()
{
    constexpr float4_t kV{3, -4, 12, 1};
    FND_TEST_TRUE(all(mul(float4x4_t::kIdentity, kV) == kV));
    FND_TEST_TRUE(all(mul(float4x4_t::kZero, kV) == float4_t::kZero));

    // The unit vectors pick the columns.
    FND_TEST_TRUE(all(mul(kMatrixA4x4, float4_t::kUnitX) == kMatrixA4x4.col0));
    FND_TEST_TRUE(all(mul(kMatrixA4x4, float4_t::kUnitY) == kMatrixA4x4.col1));
    FND_TEST_TRUE(all(mul(kMatrixA4x4, float4_t::kUnitZ) == kMatrixA4x4.col2));
    FND_TEST_TRUE(all(mul(kMatrixA4x4, float4_t::kUnitW) == kMatrixA4x4.col3));

    // Each component is the dot product of a row with v. kMatrixA4x4 is not
    // affine: its bottom row 0, 1, 0, 1 gives w = v.y + v.w, and the result is
    // not divided by it.
    FND_TEST_TRUE(all(mul(kMatrixA4x4, kV) == float4_t{-5, 1, 24, -3}));
    FND_TEST_TRUE(all(mul(kMatrixA4x4, kV)
        == float4_t{dot(row0(kMatrixA4x4), kV), dot(row1(kMatrixA4x4), kV),
            dot(row2(kMatrixA4x4), kV), dot(row3(kMatrixA4x4), kV)}));
    // Usable in constant expressions.
    static_assert(mul(float4x4_t::kIdentity, float4_t::kUnitZ).z == 1.0f);
}

void unittests_math_matrix_float4x4_row()
{
    FND_TEST_TRUE(all(row0(kMatrixA4x4) == float4_t{1, 0, -1, 4}));
    FND_TEST_TRUE(all(row1(kMatrixA4x4) == float4_t{0, 1, 0, 5}));
    FND_TEST_TRUE(all(row2(kMatrixA4x4) == float4_t{2, 0, 1, 6}));
    FND_TEST_TRUE(all(row3(kMatrixA4x4) == float4_t{0, 1, 0, 1}));
    // Row i of a matrix is column i of its transpose.
    const float4x4_t mt = transpose(kMatrixB4x4);
    FND_TEST_TRUE(all(row0(kMatrixB4x4) == column0(mt)));
    FND_TEST_TRUE(all(row3(kMatrixB4x4) == column3(mt)));
    static_assert(row3(kMatrixA4x4).y == 1.0f);
}

void unittests_math_matrix_float4x4_set_column()
{
    // Each setter replaces its own column and leaves the others alone.
    constexpr float4_t kColumn{-7, -8, -9, -10};
    float4x4_t m = kMatrixA4x4;
    set_column0(m, kColumn);
    FND_TEST_TRUE(test_columns(m, kColumn, kMatrixA4x4.col1,
        kMatrixA4x4.col2, kMatrixA4x4.col3));
    m = kMatrixA4x4;
    set_column1(m, kColumn);
    FND_TEST_TRUE(test_columns(m, kMatrixA4x4.col0, kColumn,
        kMatrixA4x4.col2, kMatrixA4x4.col3));
    m = kMatrixA4x4;
    set_column2(m, kColumn);
    FND_TEST_TRUE(test_columns(m, kMatrixA4x4.col0, kMatrixA4x4.col1,
        kColumn, kMatrixA4x4.col3));
    m = kMatrixA4x4;
    set_column3(m, kColumn);
    FND_TEST_TRUE(test_columns(m, kMatrixA4x4.col0, kMatrixA4x4.col1,
        kMatrixA4x4.col2, kColumn));

    // Setting every column rebuilds the matrix.
    m = float4x4_t::kZero;
    set_column0(m, column0(kMatrixB4x4));
    set_column1(m, column1(kMatrixB4x4));
    set_column2(m, column2(kMatrixB4x4));
    set_column3(m, column3(kMatrixB4x4));
    FND_TEST_TRUE(m == kMatrixB4x4);
}

void unittests_math_matrix_float4x4_set_row()
{
    // Each setter replaces its own row and leaves the others alone.
    constexpr float4_t kRow{-1, -2, -3, -4};
    float4x4_t m = kMatrixA4x4;
    set_row0(m, kRow);
    FND_TEST_TRUE(all(row0(m) == kRow));
    FND_TEST_TRUE(all(row1(m) == row1(kMatrixA4x4)));
    m = kMatrixA4x4;
    set_row1(m, kRow);
    FND_TEST_TRUE(all(row1(m) == kRow));
    FND_TEST_TRUE(all(row2(m) == row2(kMatrixA4x4)));
    m = kMatrixA4x4;
    set_row2(m, kRow);
    FND_TEST_TRUE(all(row2(m) == kRow));
    FND_TEST_TRUE(all(row3(m) == row3(kMatrixA4x4)));
    m = kMatrixA4x4;
    set_row3(m, kRow);
    FND_TEST_TRUE(all(row3(m) == kRow));
    FND_TEST_TRUE(all(row0(m) == row0(kMatrixA4x4)));

    // Setting every row rebuilds the matrix.
    m = float4x4_t::kZero;
    set_row0(m, row0(kMatrixB4x4));
    set_row1(m, row1(kMatrixB4x4));
    set_row2(m, row2(kMatrixB4x4));
    set_row3(m, row3(kMatrixB4x4));
    FND_TEST_TRUE(m == kMatrixB4x4);
}

void unittests_math_matrix_float4x4_transpose()
{
    // The columns of the result are the rows of the argument.
    FND_TEST_TRUE(test_columns(transpose(kMatrixA4x4), float4_t{1, 0, -1, 4},
        float4_t{0, 1, 0, 5}, float4_t{2, 0, 1, 6}, float4_t{0, 1, 0, 1}));
    FND_TEST_TRUE(transpose(transpose(kMatrixA4x4)) == kMatrixA4x4);
    FND_TEST_TRUE(transpose(float4x4_t::kZero) == float4x4_t::kZero);

    // A symmetric matrix is its own transpose.
    const float4x4_t m_sym{float4_t{1, 2, 3, 4}, float4_t{2, 5, 6, 7},
        float4_t{3, 6, 8, 9}, float4_t{4, 7, 9, 10}};
    FND_TEST_TRUE(transpose(m_sym) == m_sym);
    // Transposing commutes with scaling.
    FND_TEST_TRUE(
        transpose(kMatrixA4x4 * 2.0f) == transpose(kMatrixA4x4) * 2.0f);
    static_assert(transpose(kMatrixA4x4).col0.w == 4.0f);
}

void unittests_math_matrix_float4x4()
{
    unittests_math_matrix_float4x4_constants();
    unittests_math_matrix_float4x4_constructors();
    unittests_math_matrix_float4x4_unary_minus_operator();
    unittests_math_matrix_float4x4_equality_operators();
    unittests_math_matrix_float4x4_scalar_multiplication_operator();
    unittests_math_matrix_float4x4_matrix_multiplication_operator();
    unittests_math_matrix_float4x4_division_operator();
    unittests_math_matrix_float4x4_scalar_compound_assignment_operators();
    unittests_math_matrix_float4x4_matrix_compound_assignment_operators();
    unittests_math_matrix_float4x4_scalar_compound_assignment_matches_operators();
    unittests_math_matrix_float4x4_matrix_compound_assignment_matches_operators();
    unittests_math_matrix_float4x4_approx_equal();
    unittests_math_matrix_float4x4_cmax();
    unittests_math_matrix_float4x4_cmin();
    unittests_math_matrix_float4x4_column();
    unittests_math_matrix_float4x4_determinant();
    unittests_math_matrix_float4x4_inverse();
    unittests_math_matrix_float4x4_make_float4x4_axis_angle();
    unittests_math_matrix_float4x4_make_float4x4_scale();
    unittests_math_matrix_float4x4_make_float4x4_translation();
    unittests_math_matrix_float4x4_make_float4x4_trs();
    unittests_math_matrix_float4x4_mul();
    unittests_math_matrix_float4x4_row();
    unittests_math_matrix_float4x4_set_column();
    unittests_math_matrix_float4x4_set_row();
    unittests_math_matrix_float4x4_transpose();
}

} // namespace fnd::unittests
