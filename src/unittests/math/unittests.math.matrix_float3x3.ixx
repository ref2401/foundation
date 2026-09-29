module;
#include "foundation/unittests.h"


export module unittests.math:matrix_float3x3;
import foundation.core;
import foundation.math;

namespace fnd::unittests {

export void unittests_math_matrix_float3x3();

// The columns are {1, 2, 3}, {4, 5, 6} and {7, 8, 9}.
constexpr float3x3_t kMatrixA{
    float3_t{1, 2, 3}, float3_t{4, 5, 6},
    float3_t{7, 8, 9}};

// The columns are {1, 0, 2}, {0, 1, 0} and {-1, 0, 1}.
constexpr float3x3_t kMatrixB{
    float3_t{1, 0, 2}, float3_t{0, 1, 0},
    float3_t{-1, 0, 1}};

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
        float3x3_t::kZero, float3_t{0, 0, 0},
        float3_t{0, 0, 0}, float3_t{0, 0, 0}));
    FND_TEST_TRUE(test_columns(
        float3x3_t::kIdentity, float3_t{1, 0, 0},
        float3_t{0, 1, 0}, float3_t{0, 0, 1}));
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
    const float3x3_t zero;
    FND_TEST_TRUE(
        test_columns(zero, float3_t{0}, float3_t{0}, float3_t{0}));
    FND_TEST_TRUE(test_columns(
        float3x3_t{}, float3_t{0}, float3_t{0}, float3_t{0}));

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
        m, float3_t{1, 2, 3}, float3_t{4, 5, 6},
        float3_t{7, 8, 9}));
    FND_TEST_TRUE(m == kMatrixA);
    // Each argument lands in its own component: the 8th is m12, which is row
    // 1 of column 2.
    const float3x3_t e{0, 0, 0, 0, 0, 0, 0, 1, 0};
    FND_TEST_TRUE(test_columns(
        e, float3_t{0}, float3_t{0}, float3_t{0, 1, 0}));
}

void unittests_math_matrix_float3x3_unary_minus_operator()
{
    FND_TEST_TRUE(test_columns(
        -kMatrixA, float3_t{-1, -2, -3}, float3_t{-4, -5, -6},
        float3_t{-7, -8, -9}));
    FND_TEST_TRUE(-(-kMatrixA) == kMatrixA);
    // -0 equals +0.
    FND_TEST_TRUE(-float3x3_t::kZero == float3x3_t::kZero);
}

void unittests_math_matrix_float3x3_scalar_compound_assignment_operators()
{
    float3x3_t m = kMatrixA;

    // Each operator returns a reference to its left operand.
    FND_TEST_TRUE(&(m *= 2.0f) == &m);
    FND_TEST_TRUE(test_columns(
        m, float3_t{2, 4, 6}, float3_t{8, 10, 12},
        float3_t{14, 16, 18}));
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
    float3x3_t m = kMatrixA;

    // The operator returns a reference to its left operand.
    FND_TEST_TRUE(&(m *= kMatrixB) == &m);
    FND_TEST_TRUE(test_columns(
        m, float3_t{15, 18, 21}, float3_t{4, 5, 6},
        float3_t{6, 6, 6}));
    // The product is computed before it is stored, so m *= m works.
    m = kMatrixA;
    m *= m;
    FND_TEST_TRUE(test_columns(
        m, float3_t{30, 36, 42}, float3_t{66, 81, 96},
        float3_t{102, 126, 150}));
}

void unittests_math_matrix_float3x3_scalar_compound_assignment_matches_operators()
{
    // m op= s must give the same result as m op s.
    float3x3_t m = kMatrixA;
    m *= 2.5f;
    FND_TEST_TRUE(m == kMatrixA * 2.5f);

    m = kMatrixA;
    m /= 2.5f;
    FND_TEST_TRUE(m == kMatrixA / 2.5f);
}

void unittests_math_matrix_float3x3_matrix_compound_assignment_matches_operators()
{
    // a *= b must give the same result as a * b.
    float3x3_t m = kMatrixA;
    m *= kMatrixB;
    FND_TEST_TRUE(m == kMatrixA * kMatrixB);

    m = kMatrixB;
    m *= kMatrixA;
    FND_TEST_TRUE(m == kMatrixB * kMatrixA);
}

void unittests_math_matrix_float3x3_equality_operators()
{
    FND_TEST_TRUE(kMatrixA == kMatrixA);
    FND_TEST_FALSE(kMatrixA != kMatrixA);
    FND_TEST_TRUE(float3x3_t::kZero == float3x3_t::kZero);

    // A difference in any one of the nine components makes them unequal.
    for (uint_t col = 0; col < 3; ++col) {
        for (uint_t row = 0; row < 3; ++row) {
            float3x3_t m = kMatrixA;
            component(m, col, row) += 0.5f;
            FND_TEST_FALSE(m == kMatrixA);
            FND_TEST_TRUE(m != kMatrixA);
        }
    }

    // -0 equals +0; a NaN component makes a matrix unequal to itself.
    float3x3_t z{};
    component(z, 1, 2) = -0.0f;
    FND_TEST_TRUE(z == float3x3_t::kZero);
    float3x3_t n = kMatrixA;
    component(n, 2, 0) = kFloatNaN;
    FND_TEST_FALSE(n == n);
    FND_TEST_TRUE(n != n);
}

void unittests_math_matrix_float3x3_scalar_multiplication_operator()
{
    FND_TEST_TRUE(test_columns(
        kMatrixA * 2.0f, float3_t{2, 4, 6},
        float3_t{8, 10, 12}, float3_t{14, 16, 18}));
    FND_TEST_TRUE(test_columns(
        0.5f * kMatrixA, float3_t{0.5f, 1.0f, 1.5f}, float3_t{2.0f, 2.5f, 3.0f},
        float3_t{3.5f, 4.0f, 4.5f}));
    FND_TEST_TRUE(kMatrixA * 1.0f == kMatrixA);
    FND_TEST_TRUE(kMatrixA * -1.0f == -kMatrixA);
    FND_TEST_TRUE(kMatrixA * 0.0f == float3x3_t::kZero);
    FND_TEST_TRUE(kMatrixA * 3.0f == 3.0f * kMatrixA);
    // Overflow gives infinity.
    const float3x3_t big = kMatrixA * kFloatMaxValue;
    FND_TEST_TRUE(all(isinf(big.col1)));
}

void unittests_math_matrix_float3x3_matrix_multiplication_operator()
{
    // Matrix product: column j of a * b is a times column j of b.
    FND_TEST_TRUE(test_columns(
        kMatrixA * kMatrixB, float3_t{15, 18, 21},
        float3_t{4, 5, 6}, float3_t{6, 6, 6}));
    FND_TEST_TRUE(test_columns(
        kMatrixB * kMatrixA, float3_t{-2, 2, 5},
        float3_t{-2, 5, 14}, float3_t{-2, 8, 23}));
    // The product does not commute.
    FND_TEST_TRUE(kMatrixA * kMatrixB != kMatrixB * kMatrixA);
    // The identity is neutral on both sides, the zero matrix absorbs.
    FND_TEST_TRUE(kMatrixA * float3x3_t::kIdentity == kMatrixA);
    FND_TEST_TRUE(float3x3_t::kIdentity * kMatrixA == kMatrixA);
    FND_TEST_TRUE(kMatrixA * float3x3_t::kZero == float3x3_t::kZero);
    FND_TEST_TRUE(float3x3_t::kZero * kMatrixA == float3x3_t::kZero);
    // Associative, scalars factor out, and transpose reverses the order.
    const float3x3_t c{
        float3_t{2, -1, 0}, float3_t{0.5f, 3.0f, 1.0f},
        float3_t{-2, 0, 4}};
    FND_TEST_TRUE((kMatrixA * kMatrixB) * c == kMatrixA * (kMatrixB * c));
    FND_TEST_TRUE((kMatrixA * 2.0f) * kMatrixB == 2.0f * (kMatrixA * kMatrixB));
    FND_TEST_TRUE(
        transpose(kMatrixA * kMatrixB)
        == transpose(kMatrixB) * transpose(kMatrixA));
}

void unittests_math_matrix_float3x3_division_operator()
{
    FND_TEST_TRUE(test_columns(
        kMatrixA / 2.0f, float3_t{0.5f, 1.0f, 1.5f}, float3_t{2.0f, 2.5f, 3.0f},
        float3_t{3.5f, 4.0f, 4.5f}));
    FND_TEST_TRUE(test_columns(
        kMatrixA / 0.5f, float3_t{2, 4, 6},
        float3_t{8, 10, 12}, float3_t{14, 16, 18}));
    FND_TEST_TRUE(kMatrixA / 1.0f == kMatrixA);
    FND_TEST_TRUE(kMatrixA / -1.0f == -kMatrixA);
    FND_TEST_TRUE(kMatrixA / kFloatInfinity == float3x3_t::kZero);
}

void unittests_math_matrix_float3x3_approx_equal()
{
    FND_TEST_TRUE(approx_equal(kMatrixA, kMatrixA));
    FND_TEST_TRUE(approx_equal(kMatrixA, kMatrixA * 1.0000001f));

    // A difference in any one of the nine components is detected.
    for (uint_t col = 0; col < 3; ++col) {
        for (uint_t row = 0; row < 3; ++row) {
            float3x3_t m = kMatrixA;
            component(m, col, row) += 0.25f;
            FND_TEST_FALSE(approx_equal(m, kMatrixA));
            // max_abs_diff; the boundary is inclusive.
            FND_TEST_TRUE(approx_equal(m, kMatrixA, 0.25f));
            FND_TEST_FALSE(approx_equal(m, kMatrixA, 0.125f));
        }
    }

    // inf equals inf and NaN equals nothing, as for the float_t approx_equal.
    float3x3_t inf = kMatrixA;
    component(inf, 0, 1) = kFloatInfinity;
    FND_TEST_TRUE(approx_equal(inf, inf));
    float3x3_t n = kMatrixA;
    component(n, 1, 1) = kFloatNaN;
    FND_TEST_FALSE(approx_equal(n, n));
}

void unittests_math_matrix_float3x3_cmax()
{
    FND_TEST_TRUE(cmax(kMatrixA) == 9.0f);
    FND_TEST_TRUE(cmax(-kMatrixA) == -1.0f);
    FND_TEST_TRUE(cmax(float3x3_t::kZero) == 0.0f);
    FND_TEST_TRUE(cmax(float3x3_t::kIdentity) == 1.0f);

    // The largest component is found in any of the nine positions.
    for (uint_t col = 0; col < 3; ++col) {
        for (uint_t row = 0; row < 3; ++row) {
            float3x3_t m = kMatrixA;
            component(m, col, row) = 100.0f;
            FND_TEST_TRUE(cmax(m) == 100.0f);
        }
    }

    // A NaN component is ignored, as for the float_t max; inf wins.
    float3x3_t m = kMatrixA;
    component(m, 2, 2) = kFloatNaN;
    FND_TEST_TRUE(cmax(m) == 8.0f);
    component(m, 0, 1) = kFloatInfinity;
    FND_TEST_TRUE(cmax(m) == kFloatInfinity);
}

void unittests_math_matrix_float3x3_cmin()
{
    FND_TEST_TRUE(cmin(kMatrixA) == 1.0f);
    FND_TEST_TRUE(cmin(-kMatrixA) == -9.0f);
    FND_TEST_TRUE(cmin(float3x3_t::kZero) == 0.0f);
    FND_TEST_TRUE(cmin(float3x3_t::kIdentity) == 0.0f);

    // The smallest component is found in any of the nine positions.
    for (uint_t col = 0; col < 3; ++col) {
        for (uint_t row = 0; row < 3; ++row) {
            float3x3_t m = kMatrixA;
            component(m, col, row) = -100.0f;
            FND_TEST_TRUE(cmin(m) == -100.0f);
        }
    }

    // A NaN component is ignored, as for the float_t min; -inf wins.
    float3x3_t m = kMatrixA;
    component(m, 0, 0) = kFloatNaN;
    FND_TEST_TRUE(cmin(m) == 2.0f);
    component(m, 1, 2) = -kFloatInfinity;
    FND_TEST_TRUE(cmin(m) == -kFloatInfinity);
}

void unittests_math_matrix_float3x3_column()
{
    FND_TEST_TRUE(all(column0(kMatrixA) == float3_t{1, 2, 3}));
    FND_TEST_TRUE(all(column1(kMatrixA) == float3_t{4, 5, 6}));
    FND_TEST_TRUE(all(column2(kMatrixA) == float3_t{7, 8, 9}));
    FND_TEST_TRUE(all(column2(kMatrixB) == kMatrixB.col2));
    // Usable in constant expressions.
    static_assert(column2(kMatrixA).z == 9.0f);
}

void unittests_math_matrix_float3x3_row()
{
    FND_TEST_TRUE(all(row0(kMatrixA) == float3_t{1, 4, 7}));
    FND_TEST_TRUE(all(row1(kMatrixA) == float3_t{2, 5, 8}));
    FND_TEST_TRUE(all(row2(kMatrixA) == float3_t{3, 6, 9}));
    // Row i of a matrix is column i of its transpose.
    const float3x3_t t = transpose(kMatrixB);
    FND_TEST_TRUE(all(row0(kMatrixB) == column0(t)));
    FND_TEST_TRUE(all(row1(kMatrixB) == column1(t)));
    FND_TEST_TRUE(all(row2(kMatrixB) == column2(t)));
    static_assert(row2(kMatrixA).x == 3.0f);
}

void unittests_math_matrix_float3x3_set_column()
{
    // Each setter replaces its own column and leaves the others alone.
    float3x3_t m = kMatrixA;
    set_column0(m, float3_t{-1, -2, -3});
    FND_TEST_TRUE(test_columns(
        m, float3_t{-1, -2, -3}, float3_t{4, 5, 6}, float3_t{7, 8, 9}));
    m = kMatrixA;
    set_column1(m, float3_t{-4, -5, -6});
    FND_TEST_TRUE(test_columns(
        m, float3_t{1, 2, 3}, float3_t{-4, -5, -6}, float3_t{7, 8, 9}));
    m = kMatrixA;
    set_column2(m, float3_t{-7, -8, -9});
    FND_TEST_TRUE(test_columns(
        m, float3_t{1, 2, 3}, float3_t{4, 5, 6}, float3_t{-7, -8, -9}));

    // Setting every column rebuilds the matrix.
    m = float3x3_t::kZero;
    set_column0(m, column0(kMatrixB));
    set_column1(m, column1(kMatrixB));
    set_column2(m, column2(kMatrixB));
    FND_TEST_TRUE(m == kMatrixB);
}

void unittests_math_matrix_float3x3_set_row()
{
    // Each setter replaces its own row and leaves the others alone.
    float3x3_t m = kMatrixA;
    set_row0(m, float3_t{-1, -4, -7});
    FND_TEST_TRUE(test_columns(
        m, float3_t{-1, 2, 3}, float3_t{-4, 5, 6}, float3_t{-7, 8, 9}));
    m = kMatrixA;
    set_row1(m, float3_t{-2, -5, -8});
    FND_TEST_TRUE(test_columns(
        m, float3_t{1, -2, 3}, float3_t{4, -5, 6}, float3_t{7, -8, 9}));
    m = kMatrixA;
    set_row2(m, float3_t{-3, -6, -9});
    FND_TEST_TRUE(test_columns(
        m, float3_t{1, 2, -3}, float3_t{4, 5, -6}, float3_t{7, 8, -9}));

    // Setting every row rebuilds the matrix; rows round-trip through row().
    m = float3x3_t::kZero;
    set_row0(m, row0(kMatrixB));
    set_row1(m, row1(kMatrixB));
    set_row2(m, row2(kMatrixB));
    FND_TEST_TRUE(m == kMatrixB);
    set_row1(m, float3_t{0.5f, -0.25f, 8});
    FND_TEST_TRUE(all(row1(m) == float3_t{0.5f, -0.25f, 8}));
}

void unittests_math_matrix_float3x3_transpose()
{
    // The columns of the result are the rows of the argument.
    FND_TEST_TRUE(test_columns(
        transpose(kMatrixA), float3_t{1, 4, 7},
        float3_t{2, 5, 8}, float3_t{3, 6, 9}));
    FND_TEST_TRUE(transpose(transpose(kMatrixA)) == kMatrixA);
    FND_TEST_TRUE(transpose(float3x3_t::kZero) == float3x3_t::kZero);

    // A symmetric matrix is its own transpose.
    const float3x3_t sym{
        float3_t{1, 2, 3}, float3_t{2, 4, 5},
        float3_t{3, 5, 6}};
    FND_TEST_TRUE(transpose(sym) == sym);

    // Transposing commutes with scaling.
    FND_TEST_TRUE(transpose(kMatrixA * 2.0f) == transpose(kMatrixA) * 2.0f);
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
    unittests_math_matrix_float3x3_row();
    unittests_math_matrix_float3x3_set_column();
    unittests_math_matrix_float3x3_set_row();
    unittests_math_matrix_float3x3_transpose();
}

} // namespace fnd::unittests
