module;
#include "foundation/unittests.h"


export module unittests.math:matrix_float3x4;
import foundation.core;
import foundation.math;

namespace fnd::unittests {

export void unittests_math_matrix_float3x4();

// The linear part has the columns {1, 0, 2}, {0, 1, 0} and {-1, 0, 1}
// (determinant 3); the translation is {4, 5, 6}.
constexpr float3x4_t kMatrixA3x4{
    float3_t{1, 0, 2}, float3_t{0, 1, 0}, float3_t{-1, 0, 1},
    float3_t{4, 5, 6}};

// The linear part has the columns {2, -1, 0}, {0.5, 3, 1} and {-2, 0, 4}
// (determinant 28); the translation is {-1, 2, 0.5}.
constexpr float3x4_t kMatrixB3x4{
    float3_t{2, -1, 0}, float3_t{0.5f, 3, 1}, float3_t{-2, 0, 4},
    float3_t{-1, 2, 0.5f}};

// All expected values below are exact in binary, so == is reliable.
constexpr bool_t test_columns(const float3x4_t& m, const float3_t c0,
    const float3_t c1, const float3_t c2, const float3_t c3)
{
    return all(m.col0 == c0) && all(m.col1 == c1) && all(m.col2 == c2)
        && all(m.col3 == c3);
}

// Returns a reference to component row of column col.
float_t& component(float3x4_t& m, const uint_t col, const uint_t row)
{
    float3_t* const cols[] = {&m.col0, &m.col1, &m.col2, &m.col3};
    return (*cols[col])[row];
}

void unittests_math_matrix_float3x4_constants()
{
    FND_TEST_TRUE(test_columns(float3x4_t::kZero, float3_t{0}, float3_t{0},
        float3_t{0}, float3_t{0}));
    FND_TEST_TRUE(test_columns(float3x4_t::kIdentity, float3_t{1, 0, 0},
        float3_t{0, 1, 0}, float3_t{0, 0, 1}, float3_t{0}));
    FND_TEST_TRUE(float3x4_t::kZero == float3x4_t{});

    // The identity leaves points and directions unchanged.
    constexpr float3_t kPoint{3, -4, 12};
    FND_TEST_TRUE(all(mul_point(float3x4_t::kIdentity, kPoint) == kPoint));
    FND_TEST_TRUE(
        all(mul_direction(float3x4_t::kIdentity, kPoint) == kPoint));
    // The constants are usable in constant expressions.
    static_assert(float3x4_t::kIdentity.col2.z == 1.0f);
}

void unittests_math_matrix_float3x4_constructors()
{
    // The default ctor gives the zero matrix.
    const float3x4_t m_zero;
    FND_TEST_TRUE(test_columns(
        m_zero, float3_t{0}, float3_t{0}, float3_t{0}, float3_t{0}));

    // From four columns.
    constexpr float3_t kC0{1, 2, 3};
    constexpr float3_t kC1{-4, 5.5f, 0};
    constexpr float3_t kC2{kFloatMaxValue, kFloatMinValue, -0.25f};
    constexpr float3_t kC3{7, -8, 9};
    FND_TEST_TRUE(
        test_columns(float3x4_t{kC0, kC1, kC2, kC3}, kC0, kC1, kC2, kC3));
    FND_TEST_TRUE(
        test_columns(float3x4_t{kC3, kC2, kC1, kC0}, kC3, kC2, kC1, kC0));

    // From twelve floats in column-major order: each group of three is a
    // column.
    const float3x4_t m{1, 0, 2, 0, 1, 0, -1, 0, 1, 4, 5, 6};
    FND_TEST_TRUE(m == kMatrixA3x4);
    // Each argument lands in its own component: the 11th is m13, which is
    // row 1 of column 3.
    const float3x4_t m_e{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0};
    FND_TEST_TRUE(test_columns(
        m_e, float3_t{0}, float3_t{0}, float3_t{0}, float3_t{0, 1, 0}));
}

void unittests_math_matrix_float3x4_unary_minus_operator()
{
    FND_TEST_TRUE(test_columns(-kMatrixA3x4, -kMatrixA3x4.col0,
        -kMatrixA3x4.col1, -kMatrixA3x4.col2, -kMatrixA3x4.col3));
    FND_TEST_TRUE(-(-kMatrixA3x4) == kMatrixA3x4);
    // -0 equals +0.
    FND_TEST_TRUE(-float3x4_t::kZero == float3x4_t::kZero);
}

void unittests_math_matrix_float3x4_equality_operators()
{
    FND_TEST_TRUE(kMatrixA3x4 == kMatrixA3x4);
    FND_TEST_FALSE(kMatrixA3x4 != kMatrixA3x4);
    FND_TEST_FALSE(kMatrixA3x4 == kMatrixB3x4);
    FND_TEST_TRUE(kMatrixA3x4 != kMatrixB3x4);

    // A difference in any one of the twelve components makes them unequal.
    for (uint_t col = 0; col < 4; ++col) {
        for (uint_t row = 0; row < 3; ++row) {
            float3x4_t m = kMatrixA3x4;
            component(m, col, row) += 0.5f;
            FND_TEST_FALSE(m == kMatrixA3x4);
            FND_TEST_TRUE(m != kMatrixA3x4);
        }
    }

    // -0 equals +0; a NaN component makes a matrix unequal to itself.
    float3x4_t m_zero{};
    component(m_zero, 3, 2) = -0.0f;
    FND_TEST_TRUE(m_zero == float3x4_t::kZero);
    float3x4_t m_nan = kMatrixA3x4;
    component(m_nan, 3, 0) = kFloatNaN;
    FND_TEST_FALSE(m_nan == m_nan);
    FND_TEST_TRUE(m_nan != m_nan);
}

void unittests_math_matrix_float3x4_scalar_multiplication_operator()
{
    // Every column is scaled, the translation included.
    constexpr float_t kFactor = 2;
    FND_TEST_TRUE(test_columns(kMatrixA3x4 * kFactor,
        kMatrixA3x4.col0 * kFactor, kMatrixA3x4.col1 * kFactor,
        kMatrixA3x4.col2 * kFactor, kMatrixA3x4.col3 * kFactor));
    FND_TEST_TRUE(kFactor * kMatrixA3x4 == kMatrixA3x4 * kFactor);
    FND_TEST_TRUE(kMatrixA3x4 * 1.0f == kMatrixA3x4);
    FND_TEST_TRUE(kMatrixA3x4 * -1.0f == -kMatrixA3x4);
    FND_TEST_TRUE(kMatrixA3x4 * 0.0f == float3x4_t::kZero);
    // Overflow gives infinity.
    const float3x4_t m_big = kMatrixA3x4 * kFloatMaxValue;
    FND_TEST_TRUE(all(isinf(m_big.col3)));
}

void unittests_math_matrix_float3x4_matrix_multiplication_operator()
{
    // Composition as 4x4 matrices: the linear parts multiply, and the
    // translation is a.linear * b.col3 + a.col3.
    FND_TEST_TRUE(test_columns(kMatrixA3x4 * kMatrixB3x4,
        float3_t{2, -1, 4}, float3_t{-0.5f, 3, 2}, float3_t{-6, 0, 0},
        float3_t{2.5f, 7, 4.5f}));

    // a * b applies b first, then a.
    constexpr float3_t kPoint{3, -4, 12};
    FND_TEST_TRUE(all(mul_point(kMatrixA3x4 * kMatrixB3x4, kPoint)
        == mul_point(kMatrixA3x4, mul_point(kMatrixB3x4, kPoint))));
    FND_TEST_TRUE(all(mul_direction(kMatrixA3x4 * kMatrixB3x4, kPoint)
        == mul_direction(kMatrixA3x4, mul_direction(kMatrixB3x4, kPoint))));

    // Translate after scaling vs. scale after translating.
    constexpr float3_t kScale{2, 3, 4};
    constexpr float3_t kTranslation{1, -2, 0.5f};
    const float3x4_t sm = make_float3x4_scale(kScale);
    const float3x4_t tm = make_float3x4_translation(kTranslation);
    FND_TEST_TRUE(
        all(mul_point(tm * sm, kPoint) == kScale * kPoint + kTranslation));
    FND_TEST_TRUE(
        all(mul_point(sm * tm, kPoint) == kScale * (kPoint + kTranslation)));
    // The product does not commute.
    FND_TEST_TRUE(tm * sm != sm * tm);
    FND_TEST_TRUE(kMatrixA3x4 * kMatrixB3x4 != kMatrixB3x4 * kMatrixA3x4);

    // The identity is neutral on both sides; the product is associative.
    FND_TEST_TRUE(kMatrixA3x4 * float3x4_t::kIdentity == kMatrixA3x4);
    FND_TEST_TRUE(float3x4_t::kIdentity * kMatrixA3x4 == kMatrixA3x4);
    FND_TEST_TRUE((kMatrixA3x4 * kMatrixB3x4) * tm
        == kMatrixA3x4 * (kMatrixB3x4 * tm));
}

void unittests_math_matrix_float3x4_division_operator()
{
    constexpr float_t kDivisor = 2;
    FND_TEST_TRUE(test_columns(kMatrixA3x4 / kDivisor,
        kMatrixA3x4.col0 / kDivisor, kMatrixA3x4.col1 / kDivisor,
        kMatrixA3x4.col2 / kDivisor, kMatrixA3x4.col3 / kDivisor));
    FND_TEST_TRUE(kMatrixA3x4 / 0.5f == kMatrixA3x4 * 2.0f);
    FND_TEST_TRUE(kMatrixA3x4 / 1.0f == kMatrixA3x4);
    FND_TEST_TRUE(kMatrixA3x4 / -1.0f == -kMatrixA3x4);
    FND_TEST_TRUE(kMatrixA3x4 / kFloatInfinity == float3x4_t::kZero);
}

void unittests_math_matrix_float3x4_scalar_compound_assignment_operators()
{
    float3x4_t m = kMatrixA3x4;

    // Each operator returns a reference to its left operand.
    FND_TEST_TRUE(&(m *= 2.0f) == &m);
    FND_TEST_TRUE(m == kMatrixA3x4 * 2.0f);
    FND_TEST_TRUE(&(m /= 4.0f) == &m);
    FND_TEST_TRUE(m == kMatrixA3x4 * 0.5f);
}

void unittests_math_matrix_float3x4_matrix_compound_assignment_operators()
{
    float3x4_t m = kMatrixA3x4;

    // The operator returns a reference to its left operand.
    FND_TEST_TRUE(&(m *= kMatrixB3x4) == &m);
    FND_TEST_TRUE(test_columns(m, float3_t{2, -1, 4}, float3_t{-0.5f, 3, 2},
        float3_t{-6, 0, 0}, float3_t{2.5f, 7, 4.5f}));
    // The product is computed before it is stored, so m *= m works.
    m = kMatrixA3x4;
    m *= m;
    FND_TEST_TRUE(m == kMatrixA3x4 * kMatrixA3x4);
}

void unittests_math_matrix_float3x4_scalar_compound_assignment_matches_operators()
{
    // m op= s must give the same result as m op s.
    float3x4_t m = kMatrixA3x4;
    m *= 2.5f;
    FND_TEST_TRUE(m == kMatrixA3x4 * 2.5f);

    m = kMatrixA3x4;
    m /= 2.5f;
    FND_TEST_TRUE(m == kMatrixA3x4 / 2.5f);
}

void unittests_math_matrix_float3x4_matrix_compound_assignment_matches_operators()
{
    // a *= b must give the same result as a * b.
    float3x4_t m = kMatrixA3x4;
    m *= kMatrixB3x4;
    FND_TEST_TRUE(m == kMatrixA3x4 * kMatrixB3x4);

    m = kMatrixB3x4;
    m *= kMatrixA3x4;
    FND_TEST_TRUE(m == kMatrixB3x4 * kMatrixA3x4);
}

void unittests_math_matrix_float3x4_approx_equal()
{
    FND_TEST_TRUE(approx_equal(kMatrixA3x4, kMatrixA3x4));
    FND_TEST_TRUE(approx_equal(kMatrixA3x4, kMatrixA3x4 * 1.0000001f));

    // A difference in any one of the twelve components is detected.
    for (uint_t col = 0; col < 4; ++col) {
        for (uint_t row = 0; row < 3; ++row) {
            float3x4_t m = kMatrixA3x4;
            component(m, col, row) += 0.25f;
            FND_TEST_FALSE(approx_equal(m, kMatrixA3x4));
            // max_abs_diff; the boundary is inclusive.
            FND_TEST_TRUE(approx_equal(m, kMatrixA3x4, 0.25f));
            FND_TEST_FALSE(approx_equal(m, kMatrixA3x4, 0.125f));
        }
    }

    // inf equals inf and NaN equals nothing, as for the float_t approx_equal.
    float3x4_t m_inf = kMatrixA3x4;
    component(m_inf, 3, 1) = kFloatInfinity;
    FND_TEST_TRUE(approx_equal(m_inf, m_inf));
    float3x4_t m_nan = kMatrixA3x4;
    component(m_nan, 1, 1) = kFloatNaN;
    FND_TEST_FALSE(approx_equal(m_nan, m_nan));
}

void unittests_math_matrix_float3x4_column()
{
    FND_TEST_TRUE(all(column0(kMatrixA3x4) == float3_t{1, 0, 2}));
    FND_TEST_TRUE(all(column1(kMatrixA3x4) == float3_t{0, 1, 0}));
    FND_TEST_TRUE(all(column2(kMatrixA3x4) == float3_t{-1, 0, 1}));
    FND_TEST_TRUE(all(column3(kMatrixA3x4) == float3_t{4, 5, 6}));
    // Usable in constant expressions.
    static_assert(column3(kMatrixA3x4).z == 6.0f);
}

void unittests_math_matrix_float3x4_determinant()
{
    FND_TEST_TRUE(determinant(float3x4_t::kIdentity) == 1.0f);
    FND_TEST_TRUE(determinant(float3x4_t::kZero) == 0.0f);
    FND_TEST_TRUE(determinant(kMatrixA3x4) == 3.0f);
    FND_TEST_TRUE(determinant(kMatrixB3x4) == 28.0f);

    // As a 4x4 matrix with the bottom row 0, 0, 0, 1, the translation does
    // not change the determinant.
    constexpr float3_t kTranslation{1, -2, 0.5f};
    float3x4_t m = kMatrixA3x4;
    set_column3(m, kTranslation);
    FND_TEST_TRUE(determinant(m) == determinant(kMatrixA3x4));
    FND_TEST_TRUE(
        determinant(make_float3x4_translation(kTranslation)) == 1.0f);

    // A scale has the product of its factors; det(a * b) == det(a) * det(b).
    constexpr float3_t kScale{2, -0.5f, 4};
    FND_TEST_TRUE(
        determinant(make_float3x4_scale(kScale)) == cmul(kScale));
    FND_TEST_TRUE(approx_equal(determinant(kMatrixA3x4 * kMatrixB3x4),
        determinant(kMatrixA3x4) * determinant(kMatrixB3x4)));
    // Usable in constant expressions.
    static_assert(determinant(float3x4_t::kIdentity) == 1.0f);
}

void unittests_math_matrix_float3x4_inverse()
{
    FND_TEST_TRUE(inverse(float3x4_t::kIdentity) == float3x4_t::kIdentity);

    // A translation is undone by the opposite translation, a scale by the
    // reciprocal scale (exact for powers of two).
    constexpr float3_t kTranslation{1, -2, 0.5f};
    FND_TEST_TRUE(inverse(make_float3x4_translation(kTranslation))
        == make_float3x4_translation(-kTranslation));
    constexpr float3_t kScale{2, -0.5f, 4};
    FND_TEST_TRUE(inverse(make_float3x4_scale(kScale))
        == make_float3x4_scale(rcp(kScale)));

    // m * inverse(m) and inverse(m) * m are the identity.
    const float3x4_t m_inv_a = inverse(kMatrixA3x4);
    FND_TEST_TRUE(
        approx_equal(kMatrixA3x4 * m_inv_a, float3x4_t::kIdentity));
    FND_TEST_TRUE(
        approx_equal(m_inv_a * kMatrixA3x4, float3x4_t::kIdentity));
    FND_TEST_TRUE(approx_equal(inverse(m_inv_a), kMatrixA3x4));

    // The inverse transform undoes the transform of a point.
    constexpr float3_t kPoint{3, -4, 12};
    FND_TEST_TRUE(all(approx_equal(
        mul_point(m_inv_a, mul_point(kMatrixA3x4, kPoint)), kPoint)));

    // The determinant of the inverse is the reciprocal of the determinant,
    // and the inverse of a product is the product of the inverses, reversed.
    FND_TEST_TRUE(approx_equal(
        determinant(inverse(kMatrixB3x4)), 1.0f / determinant(kMatrixB3x4)));
    FND_TEST_TRUE(approx_equal(inverse(kMatrixA3x4 * kMatrixB3x4),
        inverse(kMatrixB3x4) * inverse(kMatrixA3x4)));
}

void unittests_math_matrix_float3x4_make_float3x4_rotation()
{
    // The linear part is the float3x3_t rotation; there is no translation.
    constexpr float3_t kAxis{0.6f, 0, -0.8f};
    constexpr float_t kAngle = 0.75f;
    const float3x3_t rm3 = make_float3x3_rotation(kAxis, kAngle);
    const float3x4_t rm = make_float3x4_rotation(kAxis, kAngle);
    FND_TEST_TRUE(
        test_columns(rm, rm3.col0, rm3.col1, rm3.col2, float3_t::kZero));

    // A quarter turn about z maps x to y, for points and directions alike.
    const float3x4_t rm_z
        = make_float3x4_rotation(float3_t::kUnitZ, kFloatPi / 2);
    FND_TEST_TRUE(all(approx_equal(
        mul_point(rm_z, float3_t::kUnitX), float3_t::kUnitY)));
    FND_TEST_TRUE(all(approx_equal(
        mul_direction(rm_z, float3_t::kUnitX), float3_t::kUnitY)));
    // The origin stays in place; the determinant is 1; the inverse rotates
    // back by -angle.
    FND_TEST_TRUE(all(mul_point(rm, float3_t::kZero) == float3_t::kZero));
    FND_TEST_TRUE(approx_equal(determinant(rm), 1.0f));
    FND_TEST_TRUE(
        approx_equal(inverse(rm), make_float3x4_rotation(kAxis, -kAngle)));
}

void unittests_math_matrix_float3x4_make_float3x4_scale()
{
    // A diagonal linear part and no translation.
    constexpr float3_t kScale0{2, -0.5f, 4};
    const float3x4_t sm0 = make_float3x4_scale(kScale0);
    FND_TEST_TRUE(test_columns(sm0, float3_t{kScale0.x, 0, 0},
        float3_t{0, kScale0.y, 0}, float3_t{0, 0, kScale0.z}, float3_t{0}));
    FND_TEST_TRUE(make_float3x4_scale(float3_t{1}) == float3x4_t::kIdentity);

    // Points and directions are scaled per component.
    constexpr float3_t kPoint{1, 2, 3};
    FND_TEST_TRUE(all(mul_point(sm0, kPoint) == kScale0 * kPoint));
    FND_TEST_TRUE(all(mul_direction(sm0, kPoint) == kScale0 * kPoint));

    // Scales combine by multiplying their factors, in either order.
    constexpr float3_t kScale1{3, 4, -1};
    const float3x4_t sm1 = make_float3x4_scale(kScale1);
    FND_TEST_TRUE(sm0 * sm1 == make_float3x4_scale(kScale0 * kScale1));
    FND_TEST_TRUE(sm0 * sm1 == sm1 * sm0);
    // Usable in constant expressions.
    static_assert(make_float3x4_scale(float3_t{2, 3, 4}).col2.z == 4.0f);
}

void unittests_math_matrix_float3x4_make_float3x4_translation()
{
    // The identity linear part and the translation in col3.
    constexpr float3_t kTranslation0{1, -2, 0.5f};
    const float3x4_t tm0 = make_float3x4_translation(kTranslation0);
    FND_TEST_TRUE(test_columns(tm0, float3_t::kUnitX, float3_t::kUnitY,
        float3_t::kUnitZ, kTranslation0));

    // Points are moved, directions are not.
    constexpr float3_t kPoint{3, -4, 12};
    FND_TEST_TRUE(all(mul_point(tm0, kPoint) == kPoint + kTranslation0));
    FND_TEST_TRUE(all(mul_direction(tm0, kPoint) == kPoint));

    // Translations combine by adding, in either order.
    constexpr float3_t kTranslation1{-3, 4, 8};
    const float3x4_t tm1 = make_float3x4_translation(kTranslation1);
    FND_TEST_TRUE(
        tm0 * tm1 == make_float3x4_translation(kTranslation0 + kTranslation1));
    FND_TEST_TRUE(tm0 * tm1 == tm1 * tm0);
    // Usable in constant expressions.
    static_assert(make_float3x4_translation(kTranslation0).col3.y == -2.0f);
}

void unittests_math_matrix_float3x4_make_float3x4_trs()
{
    // mrs is the linear part and t the translation.
    constexpr float3_t kTranslation{1, -2, 0.5f};
    constexpr float3_t kScale{2, 3, 4};
    const float3x3_t mrs = make_float3x3_rotation(float3_t::kUnitZ, 0.75f)
        * make_float3x3_scale(kScale);
    const float3x4_t m = make_float3x4_trs(kTranslation, mrs);
    FND_TEST_TRUE(test_columns(m, mrs.col0, mrs.col1, mrs.col2, kTranslation));

    // mrs is applied first, then t: the same as the composition T * RS.
    const float3x4_t m_rs{mrs.col0, mrs.col1, mrs.col2, float3_t::kZero};
    FND_TEST_TRUE(m == make_float3x4_translation(kTranslation) * m_rs);
    constexpr float3_t kPoint{3, -4, 12};
    FND_TEST_TRUE(all(approx_equal(
        mul_point(m, kPoint), mul(mrs, kPoint) + kTranslation)));
    // Directions are not translated.
    FND_TEST_TRUE(
        all(approx_equal(mul_direction(m, kPoint), mul(mrs, kPoint))));

    // With the identity it is a pure translation; with a zero translation it
    // is the linear part alone.
    FND_TEST_TRUE(make_float3x4_trs(kTranslation, float3x3_t::kIdentity)
        == make_float3x4_translation(kTranslation));
    const float3x3_t sm = make_float3x3_scale(kScale);
    FND_TEST_TRUE(
        make_float3x4_trs(float3_t::kZero, sm) == make_float3x4_scale(kScale));

    // The inverse transform takes a transformed point back.
    FND_TEST_TRUE(all(approx_equal(
        mul_point(inverse(m), mul_point(m, kPoint)), kPoint)));
    // Usable in constant expressions.
    static_assert(
        make_float3x4_trs(kTranslation, float3x3_t::kIdentity).col3.z == 0.5f);
}

void unittests_math_matrix_float3x4_mul()
{
    // w == 1 transforms a point, w == 0 a direction.
    constexpr float3_t kPoint{3, -4, 12};
    FND_TEST_TRUE(all(mul(kMatrixA3x4, float4(kPoint, 1))
        == mul_point(kMatrixA3x4, kPoint)));
    FND_TEST_TRUE(all(mul(kMatrixA3x4, float4(kPoint, 0))
        == mul_direction(kMatrixA3x4, kPoint)));
    // Any other w scales the translation.
    constexpr float_t kW = -2;
    FND_TEST_TRUE(all(mul(kMatrixA3x4, float4(kPoint, kW))
        == mul_direction(kMatrixA3x4, kPoint) + kMatrixA3x4.col3 * kW));

    // The unit vectors pick the columns.
    FND_TEST_TRUE(all(mul(kMatrixA3x4, float4_t::kUnitX) == kMatrixA3x4.col0));
    FND_TEST_TRUE(all(mul(kMatrixA3x4, float4_t::kUnitW) == kMatrixA3x4.col3));
    // Usable in constant expressions.
    static_assert(mul(float3x4_t::kIdentity, float4_t::kUnitZ).z == 1.0f);
}

void unittests_math_matrix_float3x4_mul_direction()
{
    // The linear part only: the unit vectors pick col0-col2, and the
    // translation is ignored.
    FND_TEST_TRUE(all(
        mul_direction(kMatrixA3x4, float3_t::kUnitX) == kMatrixA3x4.col0));
    FND_TEST_TRUE(all(
        mul_direction(kMatrixA3x4, float3_t::kUnitY) == kMatrixA3x4.col1));
    FND_TEST_TRUE(all(
        mul_direction(kMatrixA3x4, float3_t::kUnitZ) == kMatrixA3x4.col2));
    FND_TEST_TRUE(all(
        mul_direction(kMatrixA3x4, float3_t::kZero) == float3_t::kZero));

    // It is the float3x3_t product with the linear part.
    constexpr float3_t kDirection{3, -4, 12};
    const float3x3_t m3{kMatrixA3x4.col0, kMatrixA3x4.col1, kMatrixA3x4.col2};
    FND_TEST_TRUE(
        all(mul_direction(kMatrixA3x4, kDirection) == mul(m3, kDirection)));
}

void unittests_math_matrix_float3x4_mul_point()
{
    // The origin goes to the translation; a point is transformed by the
    // linear part and then moved by the translation.
    FND_TEST_TRUE(
        all(mul_point(kMatrixA3x4, float3_t::kZero) == kMatrixA3x4.col3));
    FND_TEST_TRUE(all(mul_point(kMatrixA3x4, float3_t::kUnitX)
        == kMatrixA3x4.col0 + kMatrixA3x4.col3));

    constexpr float3_t kPoint{3, -4, 12};
    FND_TEST_TRUE(all(mul_point(kMatrixA3x4, kPoint)
        == mul_direction(kMatrixA3x4, kPoint) + kMatrixA3x4.col3));
    FND_TEST_TRUE(all(mul_point(kMatrixA3x4, kPoint) == float3_t{-5, 1, 24}));
}

void unittests_math_matrix_float3x4_row()
{
    FND_TEST_TRUE(all(row0(kMatrixA3x4) == float4_t{1, 0, -1, 4}));
    FND_TEST_TRUE(all(row1(kMatrixA3x4) == float4_t{0, 1, 0, 5}));
    FND_TEST_TRUE(all(row2(kMatrixA3x4) == float4_t{2, 0, 1, 6}));
    // A row times {p, 1} is that component of the transformed point.
    constexpr float3_t kPoint{3, -4, 12};
    const float4_t p = float4(kPoint, 1);
    FND_TEST_TRUE(
        dot(row1(kMatrixA3x4), p) == mul_point(kMatrixA3x4, kPoint).y);
    static_assert(row2(kMatrixA3x4).w == 6.0f);
}

void unittests_math_matrix_float3x4_set_column()
{
    // Each setter replaces its own column and leaves the others alone.
    constexpr float3_t kColumn{-7, -8, -9};
    float3x4_t m = kMatrixA3x4;
    set_column0(m, kColumn);
    FND_TEST_TRUE(test_columns(m, kColumn, kMatrixA3x4.col1,
        kMatrixA3x4.col2, kMatrixA3x4.col3));
    m = kMatrixA3x4;
    set_column1(m, kColumn);
    FND_TEST_TRUE(test_columns(m, kMatrixA3x4.col0, kColumn,
        kMatrixA3x4.col2, kMatrixA3x4.col3));
    m = kMatrixA3x4;
    set_column2(m, kColumn);
    FND_TEST_TRUE(test_columns(m, kMatrixA3x4.col0, kMatrixA3x4.col1,
        kColumn, kMatrixA3x4.col3));
    m = kMatrixA3x4;
    set_column3(m, kColumn);
    FND_TEST_TRUE(test_columns(m, kMatrixA3x4.col0, kMatrixA3x4.col1,
        kMatrixA3x4.col2, kColumn));

    // Setting every column rebuilds the matrix.
    m = float3x4_t::kZero;
    set_column0(m, column0(kMatrixB3x4));
    set_column1(m, column1(kMatrixB3x4));
    set_column2(m, column2(kMatrixB3x4));
    set_column3(m, column3(kMatrixB3x4));
    FND_TEST_TRUE(m == kMatrixB3x4);
}

void unittests_math_matrix_float3x4_set_row()
{
    // Each setter replaces its own row and leaves the others alone.
    constexpr float4_t kRow{-1, -2, -3, -4};
    float3x4_t m = kMatrixA3x4;
    set_row0(m, kRow);
    FND_TEST_TRUE(all(row0(m) == kRow));
    FND_TEST_TRUE(all(row1(m) == row1(kMatrixA3x4)));
    FND_TEST_TRUE(all(row2(m) == row2(kMatrixA3x4)));
    m = kMatrixA3x4;
    set_row1(m, kRow);
    FND_TEST_TRUE(all(row0(m) == row0(kMatrixA3x4)));
    FND_TEST_TRUE(all(row1(m) == kRow));
    FND_TEST_TRUE(all(row2(m) == row2(kMatrixA3x4)));
    m = kMatrixA3x4;
    set_row2(m, kRow);
    FND_TEST_TRUE(all(row0(m) == row0(kMatrixA3x4)));
    FND_TEST_TRUE(all(row1(m) == row1(kMatrixA3x4)));
    FND_TEST_TRUE(all(row2(m) == kRow));

    // Setting every row rebuilds the matrix.
    m = float3x4_t::kZero;
    set_row0(m, row0(kMatrixB3x4));
    set_row1(m, row1(kMatrixB3x4));
    set_row2(m, row2(kMatrixB3x4));
    FND_TEST_TRUE(m == kMatrixB3x4);
}

void unittests_math_matrix_float3x4()
{
    unittests_math_matrix_float3x4_constants();
    unittests_math_matrix_float3x4_constructors();
    unittests_math_matrix_float3x4_unary_minus_operator();
    unittests_math_matrix_float3x4_equality_operators();
    unittests_math_matrix_float3x4_scalar_multiplication_operator();
    unittests_math_matrix_float3x4_matrix_multiplication_operator();
    unittests_math_matrix_float3x4_division_operator();
    unittests_math_matrix_float3x4_scalar_compound_assignment_operators();
    unittests_math_matrix_float3x4_matrix_compound_assignment_operators();
    unittests_math_matrix_float3x4_scalar_compound_assignment_matches_operators();
    unittests_math_matrix_float3x4_matrix_compound_assignment_matches_operators();
    unittests_math_matrix_float3x4_approx_equal();
    unittests_math_matrix_float3x4_column();
    unittests_math_matrix_float3x4_determinant();
    unittests_math_matrix_float3x4_inverse();
    unittests_math_matrix_float3x4_make_float3x4_rotation();
    unittests_math_matrix_float3x4_make_float3x4_scale();
    unittests_math_matrix_float3x4_make_float3x4_translation();
    unittests_math_matrix_float3x4_make_float3x4_trs();
    unittests_math_matrix_float3x4_mul();
    unittests_math_matrix_float3x4_mul_direction();
    unittests_math_matrix_float3x4_mul_point();
    unittests_math_matrix_float3x4_row();
    unittests_math_matrix_float3x4_set_column();
    unittests_math_matrix_float3x4_set_row();
}

} // namespace fnd::unittests
