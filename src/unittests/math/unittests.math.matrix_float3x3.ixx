module;
#include "foundation/unittests.h"


export module unittests.math:matrix_float3x3;
import foundation.core;
import foundation.math;

// Some tests overflow to infinity on purpose. In Release, /GL lets the
// optimizer fold their constant inputs, and it reports C4756 at the
// library line it inlined rather than here.
#pragma warning(disable: 4756)

namespace fnd::unittests {

export void unittests_math_matrix_float3x3();

// The columns are {1, 2, 3}, {4, 5, 6} and {7, 8, 9}.
constexpr float3x3_t kMatrixA3x3{
    float3_t{1, 2, 3}, float3_t{4, 5, 6}, float3_t{7, 8, 9}};

// The columns are {1, 0, 2}, {0, 1, 0} and {-1, 0, 1}.
constexpr float3x3_t kMatrixB3x3{
    float3_t{1, 0, 2}, float3_t{0, 1, 0}, float3_t{-1, 0, 1}};

// The columns are {2, -1, 0}, {0.5, 3, 1} and {-2, 0, 4}; its determinant is
// 28.
constexpr float3x3_t kMatrixC3x3{
    float3_t{2, -1, 0}, float3_t{0.5f, 3, 1}, float3_t{-2, 0, 4}};

// All expected values below are exact in binary, so == is reliable.
constexpr bool_t test_columns(
    const float3x3_t& m, const float3_t c0, const float3_t c1,
    const float3_t c2)
{
    return all(m.col0 == c0) && all(m.col1 == c1) && all(m.col2 == c2);
}

// Returns a reference to component row of column col.
float_t& component(float3x3_t& m, const uint_t col, const uint_t row)
{
    float3_t* const cols[] = {&m.col0, &m.col1, &m.col2};
    return (*cols[col])[row];
}

void unittests_math_matrix_float3x3_constants()
{
    FND_TEST_TRUE(test_columns(
        float3x3_t::kZero, float3_t{0, 0, 0}, float3_t{0, 0, 0},
        float3_t{0, 0, 0}));
    FND_TEST_TRUE(test_columns(
        float3x3_t::kIdentity, float3_t{1, 0, 0}, float3_t{0, 1, 0},
        float3_t{0, 0, 1}));
    // kZero is the default-constructed matrix; the identity is its own
    // transpose.
    FND_TEST_TRUE(float3x3_t::kZero == float3x3_t{});
    FND_TEST_TRUE(transpose(float3x3_t::kIdentity) == float3x3_t::kIdentity);
    // The constants are usable in constant expressions.
    static_assert(float3x3_t::kIdentity.col2.z == 1.0f);
}

void unittests_math_matrix_float3x3_constructors()
{
    // The default ctor gives the zero matrix.
    const float3x3_t m_zero;
    FND_TEST_TRUE(test_columns(m_zero, float3_t{0}, float3_t{0}, float3_t{0}));
    FND_TEST_TRUE(
        test_columns(float3x3_t{}, float3_t{0}, float3_t{0}, float3_t{0}));

    // From three columns.
    const float3_t c0{1, 2, 3};
    const float3_t c1{-4.0f, 5.5f, 0.0f};
    const float3_t c2{kFloatMaxValue, kFloatMinValue, -0.25f};
    FND_TEST_TRUE(test_columns(float3x3_t{c0, c1, c2}, c0, c1, c2));
    FND_TEST_TRUE(test_columns(float3x3_t{c2, c0, c1}, c2, c0, c1));

    // From nine floats in column-major order: each group of three is a
    // column.
    const float3x3_t m{1, 2, 3, 4, 5, 6, 7, 8, 9};
    FND_TEST_TRUE(test_columns(
        m, float3_t{1, 2, 3}, float3_t{4, 5, 6}, float3_t{7, 8, 9}));
    FND_TEST_TRUE(m == kMatrixA3x3);
    // Each argument lands in its own component: the 8th is m12, which is row
    // 1 of column 2.
    const float3x3_t m_e{0, 0, 0, 0, 0, 0, 0, 1, 0};
    FND_TEST_TRUE(
        test_columns(m_e, float3_t{0}, float3_t{0}, float3_t{0, 1, 0}));
}

void unittests_math_matrix_float3x3_unary_minus_operator()
{
    FND_TEST_TRUE(test_columns(
        -kMatrixA3x3, float3_t{-1, -2, -3}, float3_t{-4, -5, -6},
        float3_t{-7, -8, -9}));
    FND_TEST_TRUE(-(-kMatrixA3x3) == kMatrixA3x3);
    // -0 equals +0.
    FND_TEST_TRUE(-float3x3_t::kZero == float3x3_t::kZero);
}

void unittests_math_matrix_float3x3_scalar_compound_assignment_operators()
{
    float3x3_t m = kMatrixA3x3;

    // Each operator returns a reference to its left operand.
    FND_TEST_TRUE(&(m *= 2.0f) == &m);
    FND_TEST_TRUE(test_columns(
        m, float3_t{2, 4, 6}, float3_t{8, 10, 12}, float3_t{14, 16, 18}));
    FND_TEST_TRUE(&(m /= 4.0f) == &m);
    FND_TEST_TRUE(test_columns(
        m, float3_t{0.5f, 1.0f, 1.5f}, float3_t{2.0f, 2.5f, 3.0f},
        float3_t{3.5f, 4.0f, 4.5f}));
    FND_TEST_TRUE(test_columns(
        m *= -1.0f, float3_t{-0.5f, -1.0f, -1.5f},
        float3_t{-2.0f, -2.5f, -3.0f}, float3_t{-3.5f, -4.0f, -4.5f}));
    FND_TEST_TRUE(test_columns(
        m /= 0.5f, float3_t{-1, -2, -3}, float3_t{-4, -5, -6},
        float3_t{-7, -8, -9}));
}

void unittests_math_matrix_float3x3_matrix_compound_assignment_operators()
{
    float3x3_t m = kMatrixA3x3;

    // The operator returns a reference to its left operand.
    FND_TEST_TRUE(&(m *= kMatrixB3x3) == &m);
    FND_TEST_TRUE(test_columns(
        m, float3_t{15, 18, 21}, float3_t{4, 5, 6}, float3_t{6, 6, 6}));
    // The product is computed before it is stored, so m *= m works.
    m = kMatrixA3x3;
    m *= m;
    FND_TEST_TRUE(test_columns(
        m, float3_t{30, 36, 42}, float3_t{66, 81, 96},
        float3_t{102, 126, 150}));
}

void unittests_math_matrix_float3x3_scalar_compound_assignment_matches_operators()
{
    // m op= s must give the same result as m op s.
    float3x3_t m = kMatrixA3x3;
    m *= 2.5f;
    FND_TEST_TRUE(m == kMatrixA3x3 * 2.5f);

    m = kMatrixA3x3;
    m /= 2.5f;
    FND_TEST_TRUE(m == kMatrixA3x3 / 2.5f);
}

void unittests_math_matrix_float3x3_matrix_compound_assignment_matches_operators()
{
    // a *= b must give the same result as a * b.
    float3x3_t m = kMatrixA3x3;
    m *= kMatrixB3x3;
    FND_TEST_TRUE(m == kMatrixA3x3 * kMatrixB3x3);

    m = kMatrixB3x3;
    m *= kMatrixA3x3;
    FND_TEST_TRUE(m == kMatrixB3x3 * kMatrixA3x3);
}

void unittests_math_matrix_float3x3_equality_operators()
{
    FND_TEST_TRUE(kMatrixA3x3 == kMatrixA3x3);
    FND_TEST_FALSE(kMatrixA3x3 != kMatrixA3x3);
    FND_TEST_TRUE(float3x3_t::kZero == float3x3_t::kZero);

    // A difference in any one of the nine components makes them unequal.
    for (uint_t col = 0; col < 3; ++col) {
        for (uint_t row = 0; row < 3; ++row) {
            float3x3_t m = kMatrixA3x3;
            component(m, col, row) += 0.5f;
            FND_TEST_FALSE(m == kMatrixA3x3);
            FND_TEST_TRUE(m != kMatrixA3x3);
        }
    }

    // -0 equals +0; a NaN component makes a matrix unequal to itself.
    float3x3_t z{};
    component(z, 1, 2) = -0.0f;
    FND_TEST_TRUE(z == float3x3_t::kZero);
    float3x3_t m_nan = kMatrixA3x3;
    component(m_nan, 2, 0) = kFloatNaN;
    FND_TEST_FALSE(m_nan == m_nan);
    FND_TEST_TRUE(m_nan != m_nan);
}

void unittests_math_matrix_float3x3_scalar_multiplication_operator()
{
    FND_TEST_TRUE(test_columns(
        kMatrixA3x3 * 2.0f, float3_t{2, 4, 6}, float3_t{8, 10, 12},
        float3_t{14, 16, 18}));
    FND_TEST_TRUE(test_columns(
        0.5f * kMatrixA3x3, float3_t{0.5f, 1.0f, 1.5f}, float3_t{2.0f, 2.5f, 3.0f},
        float3_t{3.5f, 4.0f, 4.5f}));
    FND_TEST_TRUE(kMatrixA3x3 * 1.0f == kMatrixA3x3);
    FND_TEST_TRUE(kMatrixA3x3 * -1.0f == -kMatrixA3x3);
    FND_TEST_TRUE(kMatrixA3x3 * 0.0f == float3x3_t::kZero);
    FND_TEST_TRUE(kMatrixA3x3 * 3.0f == 3.0f * kMatrixA3x3);
    // Overflow gives infinity.
    const float3x3_t m_big = kMatrixA3x3 * kFloatMaxValue;
    FND_TEST_TRUE(all(isinf(m_big.col1)));
}

void unittests_math_matrix_float3x3_matrix_multiplication_operator()
{
    // Matrix product: column j of a * b is a times column j of b.
    FND_TEST_TRUE(test_columns(
        kMatrixA3x3 * kMatrixB3x3, float3_t{15, 18, 21}, float3_t{4, 5, 6},
        float3_t{6, 6, 6}));
    FND_TEST_TRUE(test_columns(
        kMatrixB3x3 * kMatrixA3x3, float3_t{-2, 2, 5}, float3_t{-2, 5, 14},
        float3_t{-2, 8, 23}));
    // The product does not commute.
    FND_TEST_TRUE(kMatrixA3x3 * kMatrixB3x3 != kMatrixB3x3 * kMatrixA3x3);
    // The identity is neutral on both sides, the zero matrix absorbs.
    FND_TEST_TRUE(kMatrixA3x3 * float3x3_t::kIdentity == kMatrixA3x3);
    FND_TEST_TRUE(float3x3_t::kIdentity * kMatrixA3x3 == kMatrixA3x3);
    FND_TEST_TRUE(kMatrixA3x3 * float3x3_t::kZero == float3x3_t::kZero);
    FND_TEST_TRUE(float3x3_t::kZero * kMatrixA3x3 == float3x3_t::kZero);
    // Associative, scalars factor out, and transpose reverses the order.
    FND_TEST_TRUE(
        (kMatrixA3x3 * kMatrixB3x3) * kMatrixC3x3
        == kMatrixA3x3 * (kMatrixB3x3 * kMatrixC3x3));
    FND_TEST_TRUE((kMatrixA3x3 * 2.0f) * kMatrixB3x3 == 2.0f * (kMatrixA3x3 * kMatrixB3x3));
    FND_TEST_TRUE(
        transpose(kMatrixA3x3 * kMatrixB3x3)
        == transpose(kMatrixB3x3) * transpose(kMatrixA3x3));
}

void unittests_math_matrix_float3x3_division_operator()
{
    FND_TEST_TRUE(test_columns(
        kMatrixA3x3 / 2.0f, float3_t{0.5f, 1.0f, 1.5f}, float3_t{2.0f, 2.5f, 3.0f},
        float3_t{3.5f, 4.0f, 4.5f}));
    FND_TEST_TRUE(test_columns(
        kMatrixA3x3 / 0.5f, float3_t{2, 4, 6}, float3_t{8, 10, 12},
        float3_t{14, 16, 18}));
    FND_TEST_TRUE(kMatrixA3x3 / 1.0f == kMatrixA3x3);
    FND_TEST_TRUE(kMatrixA3x3 / -1.0f == -kMatrixA3x3);
    FND_TEST_TRUE(kMatrixA3x3 / kFloatInfinity == float3x3_t::kZero);
}

void unittests_math_matrix_float3x3_approx_equal()
{
    FND_TEST_TRUE(approx_equal(kMatrixA3x3, kMatrixA3x3));
    FND_TEST_TRUE(approx_equal(kMatrixA3x3, kMatrixA3x3 * 1.0000001f));

    // A difference in any one of the nine components is detected.
    for (uint_t col = 0; col < 3; ++col) {
        for (uint_t row = 0; row < 3; ++row) {
            float3x3_t m = kMatrixA3x3;
            component(m, col, row) += 0.25f;
            FND_TEST_FALSE(approx_equal(m, kMatrixA3x3));
            // max_abs_diff; the boundary is inclusive.
            FND_TEST_TRUE(approx_equal(m, kMatrixA3x3, 0.25f));
            FND_TEST_FALSE(approx_equal(m, kMatrixA3x3, 0.125f));
        }
    }

    // inf equals inf and NaN equals nothing, as for the float_t approx_equal.
    float3x3_t m_inf = kMatrixA3x3;
    component(m_inf, 0, 1) = kFloatInfinity;
    FND_TEST_TRUE(approx_equal(m_inf, m_inf));
    float3x3_t m_nan = kMatrixA3x3;
    component(m_nan, 1, 1) = kFloatNaN;
    FND_TEST_FALSE(approx_equal(m_nan, m_nan));
}

void unittests_math_matrix_float3x3_cmax()
{
    FND_TEST_TRUE(cmax(kMatrixA3x3) == 9.0f);
    FND_TEST_TRUE(cmax(-kMatrixA3x3) == -1.0f);
    FND_TEST_TRUE(cmax(float3x3_t::kZero) == 0.0f);
    FND_TEST_TRUE(cmax(float3x3_t::kIdentity) == 1.0f);

    // The largest component is found in any of the nine positions.
    for (uint_t col = 0; col < 3; ++col) {
        for (uint_t row = 0; row < 3; ++row) {
            float3x3_t m = kMatrixA3x3;
            component(m, col, row) = 100.0f;
            FND_TEST_TRUE(cmax(m) == 100.0f);
        }
    }

    // A NaN component is ignored, as for the float_t max; inf wins.
    float3x3_t m = kMatrixA3x3;
    component(m, 2, 2) = kFloatNaN;
    FND_TEST_TRUE(cmax(m) == 8.0f);
    component(m, 0, 1) = kFloatInfinity;
    FND_TEST_TRUE(cmax(m) == kFloatInfinity);
}

void unittests_math_matrix_float3x3_cmin()
{
    FND_TEST_TRUE(cmin(kMatrixA3x3) == 1.0f);
    FND_TEST_TRUE(cmin(-kMatrixA3x3) == -9.0f);
    FND_TEST_TRUE(cmin(float3x3_t::kZero) == 0.0f);
    FND_TEST_TRUE(cmin(float3x3_t::kIdentity) == 0.0f);

    // The smallest component is found in any of the nine positions.
    for (uint_t col = 0; col < 3; ++col) {
        for (uint_t row = 0; row < 3; ++row) {
            float3x3_t m = kMatrixA3x3;
            component(m, col, row) = -100.0f;
            FND_TEST_TRUE(cmin(m) == -100.0f);
        }
    }

    // A NaN component is ignored, as for the float_t min; -inf wins.
    float3x3_t m = kMatrixA3x3;
    component(m, 0, 0) = kFloatNaN;
    FND_TEST_TRUE(cmin(m) == 2.0f);
    component(m, 1, 2) = -kFloatInfinity;
    FND_TEST_TRUE(cmin(m) == -kFloatInfinity);
}

void unittests_math_matrix_float3x3_column()
{
    FND_TEST_TRUE(all(column0(kMatrixA3x3) == float3_t{1, 2, 3}));
    FND_TEST_TRUE(all(column1(kMatrixA3x3) == float3_t{4, 5, 6}));
    FND_TEST_TRUE(all(column2(kMatrixA3x3) == float3_t{7, 8, 9}));
    FND_TEST_TRUE(all(column2(kMatrixB3x3) == kMatrixB3x3.col2));
    // Usable in constant expressions.
    static_assert(column2(kMatrixA3x3).z == 9.0f);
}

void unittests_math_matrix_float3x3_determinant()
{
    FND_TEST_TRUE(determinant(float3x3_t::kZero) == 0.0f);
    FND_TEST_TRUE(determinant(float3x3_t::kIdentity) == 1.0f);
    FND_TEST_TRUE(determinant(float3x3_t{2, 0, 0, 0, 3, 0, 0, 0, 4}) == 24.0f);
    // The columns of kMatrixA3x3 are linearly dependent: it is singular.
    FND_TEST_TRUE(determinant(kMatrixA3x3) == 0.0f);
    FND_TEST_TRUE(determinant(kMatrixB3x3) == 3.0f);

    // Transposing keeps it, swapping two columns negates it, scaling a column
    // scales it, and scaling the matrix scales it by the cube.
    FND_TEST_TRUE(determinant(transpose(kMatrixB3x3)) == 3.0f);
    FND_TEST_TRUE(
        determinant(float3x3_t{kMatrixB3x3.col1, kMatrixB3x3.col0, kMatrixB3x3.col2})
        == -3.0f);
    const float3x3_t m_scaled{
        kMatrixB3x3.col0 * 2.0f, kMatrixB3x3.col1, kMatrixB3x3.col2};
    FND_TEST_TRUE(determinant(m_scaled) == 6.0f);
    FND_TEST_TRUE(determinant(kMatrixB3x3 * 2.0f) == 24.0f);

    // det(a * b) == det(a) * det(b).
    FND_TEST_TRUE(determinant(kMatrixC3x3) == 28.0f);
    FND_TEST_TRUE(approx_equal(
        determinant(kMatrixB3x3 * kMatrixC3x3),
        determinant(kMatrixB3x3) * determinant(kMatrixC3x3)));
    // Usable in constant expressions.
    static_assert(determinant(float3x3_t::kIdentity) == 1.0f);
}

void unittests_math_matrix_float3x3_inverse()
{
    FND_TEST_TRUE(inverse(float3x3_t::kIdentity) == float3x3_t::kIdentity);
    // A diagonal matrix of powers of two inverts exactly.
    FND_TEST_TRUE(
        inverse(float3x3_t{2, 0, 0, 0, 4, 0, 0, 0, 0.5f})
        == float3x3_t{0.5f, 0, 0, 0, 0.25f, 0, 0, 0, 2});

    // The rows of the inverse of kMatrixB3x3 are {1, 0, 1}, {0, 3, 0} and
    // {-2, 0, 1}, divided by its determinant, 3.
    const float3x3_t m_inv_b = inverse(kMatrixB3x3);
    const float3x3_t m_inv_b_expected = float3x3_t{
        float3_t{1.0f / 3, 0, -2.0f / 3}, float3_t{0, 1, 0},
        float3_t{1.0f / 3, 0, 1.0f / 3}};
    FND_TEST_TRUE(approx_equal(m_inv_b, m_inv_b_expected));

    // m * inverse(m) and inverse(m) * m are the identity.
    FND_TEST_TRUE(approx_equal(kMatrixB3x3 * m_inv_b, float3x3_t::kIdentity));
    FND_TEST_TRUE(approx_equal(m_inv_b * kMatrixB3x3, float3x3_t::kIdentity));

    const float3x3_t m_inv_c = inverse(kMatrixC3x3);
    FND_TEST_TRUE(approx_equal(kMatrixC3x3 * m_inv_c, float3x3_t::kIdentity));
    FND_TEST_TRUE(approx_equal(inverse(m_inv_c), kMatrixC3x3));
    FND_TEST_TRUE(approx_equal(
        inverse(transpose(kMatrixC3x3)), transpose(inverse(kMatrixC3x3))));

    const float_t det_c = determinant(kMatrixC3x3);
    const float_t det_inv_c = determinant(m_inv_c);
    FND_TEST_TRUE(approx_equal(1.0f / det_c, det_inv_c));
    FND_TEST_TRUE(approx_equal(
        inverse(kMatrixB3x3 * kMatrixC3x3),
        inverse(kMatrixC3x3) * inverse(kMatrixB3x3)));
}

void unittests_math_matrix_float3x3_make_float3x3_rotation()
{
    const float_t quarter = kFloatPi / 2;
    const float3_t x = float3_t::kUnitX;
    const float3_t y = float3_t::kUnitY;
    const float3_t z = float3_t::kUnitZ;

    // Quarter turns about the axes are right-handed: counter-clockwise when
    // looking from the tip of the axis toward the origin.
    const float3x3_t rm_x = make_float3x3_rotation(x, quarter);
    FND_TEST_TRUE(all(approx_equal(mul(rm_x, y), z)));
    FND_TEST_TRUE(all(approx_equal(mul(rm_x, z), -y)));
    const float3x3_t rm_y = make_float3x3_rotation(y, quarter);
    FND_TEST_TRUE(all(approx_equal(mul(rm_y, z), x)));
    FND_TEST_TRUE(all(approx_equal(mul(rm_y, x), -z)));
    const float3x3_t rm_z = make_float3x3_rotation(z, quarter);
    FND_TEST_TRUE(all(approx_equal(mul(rm_z, x), y)));
    FND_TEST_TRUE(all(approx_equal(mul(rm_z, y), -x)));
    FND_TEST_TRUE(approx_equal(
        rm_z,
        float3x3_t{float3_t{0, 1, 0}, float3_t{-1, 0, 0}, float3_t{0, 0, 1}}));

    // A third of a turn about the diagonal cycles x -> y -> z -> x.
    const float3x3_t rm_diag = make_float3x3_rotation(
        normalize(float3_t{1, 1, 1}), 2 * kFloatPi / 3);
    FND_TEST_TRUE(all(approx_equal(mul(rm_diag, x), y)));
    FND_TEST_TRUE(all(approx_equal(mul(rm_diag, y), z)));
    FND_TEST_TRUE(all(approx_equal(mul(rm_diag, z), x)));

    // Angle 0 and a full turn give the identity.
    const float3_t axis = normalize(float3_t{2, -1, 2});
    FND_TEST_TRUE(
        approx_equal(make_float3x3_rotation(axis, 0), float3x3_t::kIdentity));
    FND_TEST_TRUE(approx_equal(
        make_float3x3_rotation(axis, 2 * kFloatPi), float3x3_t::kIdentity));

    // The axis is left unchanged, and a rotation is orthonormal with
    // determinant 1: its inverse is its transpose.
    const float3x3_t rm = make_float3x3_rotation(axis, 0.75f);
    FND_TEST_TRUE(all(approx_equal(mul(rm, axis), axis)));
    FND_TEST_TRUE(approx_equal(rm * transpose(rm), float3x3_t::kIdentity));
    FND_TEST_TRUE(approx_equal(determinant(rm), 1.0f));
    FND_TEST_TRUE(approx_equal(inverse(rm), transpose(rm)));
    // Lengths are preserved.
    const float3_t v{3, -4, 12};
    FND_TEST_TRUE(approx_equal(length(mul(rm, v)), 13.0f));

    // Rotating back by -angle undoes it, and rotations about the same axis
    // add up: R(a) * R(b) == R(a + b).
    FND_TEST_TRUE(
        approx_equal(make_float3x3_rotation(axis, -0.75f), transpose(rm)));
    FND_TEST_TRUE(approx_equal(
        rm * make_float3x3_rotation(axis, -0.75f), float3x3_t::kIdentity));
    FND_TEST_TRUE(approx_equal(
        rm * make_float3x3_rotation(axis, 0.5f),
        make_float3x3_rotation(axis, 1.25f)));
}

void unittests_math_matrix_float3x3_make_float3x3_scale()
{
    // A diagonal matrix.
    FND_TEST_TRUE(test_columns(
        make_float3x3_scale(float3_t{2, 3, 4}), float3_t{2, 0, 0},
        float3_t{0, 3, 0}, float3_t{0, 0, 4}));
    FND_TEST_TRUE(make_float3x3_scale(float3_t{1}) == float3x3_t::kIdentity);
    FND_TEST_TRUE(make_float3x3_scale(float3_t::kZero) == float3x3_t::kZero);

    constexpr float3_t kScale0{2, -0.5f, 4};
    const float3x3_t sm0 = make_float3x3_scale(kScale0);
    FND_TEST_TRUE(determinant(sm0) == cmul(kScale0));
    FND_TEST_TRUE(inverse(sm0) == make_float3x3_scale(rcp(kScale0)));

    FND_TEST_TRUE(all(mul(sm0, float3_t{1, 2, 3}) == float3_t{2, -1, 12}));
    FND_TEST_TRUE(all(mul(sm0, float3_t::kUnitY) == float3_t{0, -0.5f, 0}));

    // Scales combine by multiplying their factors, in either order.
    constexpr float3_t kScale1{3, 4, -1};
    const float3x3_t sm1 = make_float3x3_scale(kScale1);
    FND_TEST_TRUE(sm0 * sm1 == make_float3x3_scale(kScale0 * kScale1));
    FND_TEST_TRUE(sm0 * sm1 == sm1 * sm0);
    // A scale is its own transpose.
    FND_TEST_TRUE(transpose(sm0) == sm0);
    // Usable in constant expressions.
    static_assert(make_float3x3_scale(float3_t{2, 3, 4}).col2.z == 4.0f);
}

void unittests_math_matrix_float3x3_mul()
{
    const float3_t v{1, 2, 3};
    FND_TEST_TRUE(all(mul(float3x3_t::kIdentity, v) == v));
    FND_TEST_TRUE(all(mul(float3x3_t::kZero, v) == float3_t::kZero));
    FND_TEST_TRUE(all(mul(kMatrixA3x3, float3_t::kZero) == float3_t::kZero));

    FND_TEST_TRUE(all(mul(kMatrixA3x3, float3_t::kUnitX) == kMatrixA3x3.col0));
    FND_TEST_TRUE(all(mul(kMatrixA3x3, float3_t::kUnitY) == kMatrixA3x3.col1));
    FND_TEST_TRUE(all(mul(kMatrixA3x3, float3_t::kUnitZ) == kMatrixA3x3.col2));

    const float3_t expected_product{
        dot(row0(kMatrixA3x3), v), dot(row1(kMatrixA3x3), v), dot(row2(kMatrixA3x3), v)};
    FND_TEST_TRUE(all(mul(kMatrixA3x3, v) == expected_product));

    FND_TEST_TRUE(
        all(mul(kMatrixA3x3 * kMatrixB3x3, v) == mul(kMatrixA3x3, mul(kMatrixB3x3, v))));
    FND_TEST_TRUE(
        all(approx_equal(mul(inverse(kMatrixB3x3), mul(kMatrixB3x3, v)), v)));
    // Usable in constant expressions.
    static_assert(mul(float3x3_t::kIdentity, float3_t::kUnitZ).z == 1.0f);
}

void unittests_math_matrix_float3x3_row()
{
    FND_TEST_TRUE(all(row0(kMatrixA3x3) == float3_t{1, 4, 7}));
    FND_TEST_TRUE(all(row1(kMatrixA3x3) == float3_t{2, 5, 8}));
    FND_TEST_TRUE(all(row2(kMatrixA3x3) == float3_t{3, 6, 9}));
    // Row i of a matrix is column i of its transpose.
    const float3x3_t mt = transpose(kMatrixB3x3);
    FND_TEST_TRUE(all(row0(kMatrixB3x3) == column0(mt)));
    FND_TEST_TRUE(all(row1(kMatrixB3x3) == column1(mt)));
    FND_TEST_TRUE(all(row2(kMatrixB3x3) == column2(mt)));
    static_assert(row2(kMatrixA3x3).x == 3.0f);
}

void unittests_math_matrix_float3x3_set_column()
{
    // Each setter replaces its own column and leaves the others alone.
    float3x3_t m = kMatrixA3x3;
    set_column0(m, float3_t{-1, -2, -3});
    FND_TEST_TRUE(test_columns(
        m, float3_t{-1, -2, -3}, float3_t{4, 5, 6}, float3_t{7, 8, 9}));
    m = kMatrixA3x3;
    set_column1(m, float3_t{-4, -5, -6});
    FND_TEST_TRUE(test_columns(
        m, float3_t{1, 2, 3}, float3_t{-4, -5, -6}, float3_t{7, 8, 9}));
    m = kMatrixA3x3;
    set_column2(m, float3_t{-7, -8, -9});
    FND_TEST_TRUE(test_columns(
        m, float3_t{1, 2, 3}, float3_t{4, 5, 6}, float3_t{-7, -8, -9}));

    // Setting every column rebuilds the matrix.
    m = float3x3_t::kZero;
    set_column0(m, column0(kMatrixB3x3));
    set_column1(m, column1(kMatrixB3x3));
    set_column2(m, column2(kMatrixB3x3));
    FND_TEST_TRUE(m == kMatrixB3x3);
}

void unittests_math_matrix_float3x3_set_row()
{
    // Each setter replaces its own row and leaves the others alone.
    float3x3_t m = kMatrixA3x3;
    set_row0(m, float3_t{-1, -4, -7});
    FND_TEST_TRUE(test_columns(
        m, float3_t{-1, 2, 3}, float3_t{-4, 5, 6}, float3_t{-7, 8, 9}));
    m = kMatrixA3x3;
    set_row1(m, float3_t{-2, -5, -8});
    FND_TEST_TRUE(test_columns(
        m, float3_t{1, -2, 3}, float3_t{4, -5, 6}, float3_t{7, -8, 9}));
    m = kMatrixA3x3;
    set_row2(m, float3_t{-3, -6, -9});
    FND_TEST_TRUE(test_columns(
        m, float3_t{1, 2, -3}, float3_t{4, 5, -6}, float3_t{7, 8, -9}));

    // Setting every row rebuilds the matrix; rows round-trip through row().
    m = float3x3_t::kZero;
    set_row0(m, row0(kMatrixB3x3));
    set_row1(m, row1(kMatrixB3x3));
    set_row2(m, row2(kMatrixB3x3));
    FND_TEST_TRUE(m == kMatrixB3x3);
    set_row1(m, float3_t{0.5f, -0.25f, 8});
    FND_TEST_TRUE(all(row1(m) == float3_t{0.5f, -0.25f, 8}));
}

void unittests_math_matrix_float3x3_transpose()
{
    // The columns of the result are the rows of the argument.
    FND_TEST_TRUE(test_columns(
        transpose(kMatrixA3x3), float3_t{1, 4, 7}, float3_t{2, 5, 8},
        float3_t{3, 6, 9}));
    FND_TEST_TRUE(transpose(transpose(kMatrixA3x3)) == kMatrixA3x3);
    FND_TEST_TRUE(transpose(float3x3_t::kZero) == float3x3_t::kZero);

    // A symmetric matrix is its own transpose.
    const float3x3_t m_sym{
        float3_t{1, 2, 3}, float3_t{2, 4, 5}, float3_t{3, 5, 6}};
    FND_TEST_TRUE(transpose(m_sym) == m_sym);

    // Transposing commutes with scaling.
    FND_TEST_TRUE(transpose(kMatrixA3x3 * 2.0f) == transpose(kMatrixA3x3) * 2.0f);
}

void unittests_math_matrix_float3x3()
{
    unittests_math_matrix_float3x3_constants();
    unittests_math_matrix_float3x3_constructors();
    unittests_math_matrix_float3x3_unary_minus_operator();
    unittests_math_matrix_float3x3_scalar_compound_assignment_operators();
    unittests_math_matrix_float3x3_matrix_compound_assignment_operators();
    unittests_math_matrix_float3x3_scalar_compound_assignment_matches_operators();
    unittests_math_matrix_float3x3_matrix_compound_assignment_matches_operators();
    unittests_math_matrix_float3x3_equality_operators();
    unittests_math_matrix_float3x3_scalar_multiplication_operator();
    unittests_math_matrix_float3x3_matrix_multiplication_operator();
    unittests_math_matrix_float3x3_division_operator();
    unittests_math_matrix_float3x3_approx_equal();
    unittests_math_matrix_float3x3_cmax();
    unittests_math_matrix_float3x3_cmin();
    unittests_math_matrix_float3x3_column();
    unittests_math_matrix_float3x3_determinant();
    unittests_math_matrix_float3x3_inverse();
    unittests_math_matrix_float3x3_make_float3x3_rotation();
    unittests_math_matrix_float3x3_make_float3x3_scale();
    unittests_math_matrix_float3x3_mul();
    unittests_math_matrix_float3x3_row();
    unittests_math_matrix_float3x3_set_column();
    unittests_math_matrix_float3x3_set_row();
    unittests_math_matrix_float3x3_transpose();
}

} // namespace fnd::unittests
