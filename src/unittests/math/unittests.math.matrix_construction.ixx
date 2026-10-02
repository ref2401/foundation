module;
#include "foundation/unittests.h"


export module unittests.math:matrix_construction;
import foundation.core;
import foundation.math;

namespace fnd::unittests {

export void unittests_math_matrix_construction();

void unittests_math_matrix_construction_make_float3x3_axis_angle()
{
    const float_t quarter = kFloatPi / 2;
    const float3_t x = float3_t::kUnitX;
    const float3_t y = float3_t::kUnitY;
    const float3_t z = float3_t::kUnitZ;

    // Quarter turns about the axes are right-handed: counter-clockwise when
    // looking from the tip of the axis toward the origin.
    const float3x3_t rm_x = make_float3x3_axis_angle(x, quarter);
    FND_TEST_TRUE(all(approx_equal(mul(rm_x, y), z)));
    FND_TEST_TRUE(all(approx_equal(mul(rm_x, z), -y)));
    const float3x3_t rm_y = make_float3x3_axis_angle(y, quarter);
    FND_TEST_TRUE(all(approx_equal(mul(rm_y, z), x)));
    FND_TEST_TRUE(all(approx_equal(mul(rm_y, x), -z)));
    const float3x3_t rm_z = make_float3x3_axis_angle(z, quarter);
    FND_TEST_TRUE(all(approx_equal(mul(rm_z, x), y)));
    FND_TEST_TRUE(all(approx_equal(mul(rm_z, y), -x)));
    FND_TEST_TRUE(approx_equal(
        rm_z,
        float3x3_t{float3_t{0, 1, 0}, float3_t{-1, 0, 0}, float3_t{0, 0, 1}}));

    // A third of a turn about the diagonal cycles x -> y -> z -> x.
    const float3x3_t rm_diag = make_float3x3_axis_angle(
        normalize(float3_t{1, 1, 1}), 2 * kFloatPi / 3);
    FND_TEST_TRUE(all(approx_equal(mul(rm_diag, x), y)));
    FND_TEST_TRUE(all(approx_equal(mul(rm_diag, y), z)));
    FND_TEST_TRUE(all(approx_equal(mul(rm_diag, z), x)));

    // Angle 0 and a full turn give the identity.
    const float3_t axis = normalize(float3_t{2, -1, 2});
    FND_TEST_TRUE(
        approx_equal(make_float3x3_axis_angle(axis, 0), float3x3_t::kIdentity));
    FND_TEST_TRUE(approx_equal(
        make_float3x3_axis_angle(axis, 2 * kFloatPi), float3x3_t::kIdentity));

    // The axis is left unchanged, and a rotation is orthonormal with
    // determinant 1: its inverse is its transpose.
    const float3x3_t rm = make_float3x3_axis_angle(axis, 0.75f);
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
        approx_equal(make_float3x3_axis_angle(axis, -0.75f), transpose(rm)));
    FND_TEST_TRUE(approx_equal(
        rm * make_float3x3_axis_angle(axis, -0.75f), float3x3_t::kIdentity));
    FND_TEST_TRUE(approx_equal(
        rm * make_float3x3_axis_angle(axis, 0.5f),
        make_float3x3_axis_angle(axis, 1.25f)));
}

void unittests_math_matrix_construction_make_float3x3_scale()
{
    // A diagonal matrix.
    FND_TEST_TRUE(make_float3x3_scale(float3_t{2, 3, 4})
        == float3x3_t{
            float3_t{2, 0, 0}, float3_t{0, 3, 0}, float3_t{0, 0, 4}});
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

void unittests_math_matrix_construction_make_float3x4_axis_angle()
{
    // The linear part is the float3x3_t rotation; there is no translation.
    constexpr float3_t kAxis{0.6f, 0, -0.8f};
    constexpr float_t kAngle = 0.75f;
    const float3x3_t rm3 = make_float3x3_axis_angle(kAxis, kAngle);
    const float3x4_t rm = make_float3x4_axis_angle(kAxis, kAngle);
    FND_TEST_TRUE(
        rm == float3x4_t{rm3.col0, rm3.col1, rm3.col2, float3_t::kZero});

    // A quarter turn about z maps x to y, for points and directions alike.
    const float3x4_t rm_z
        = make_float3x4_axis_angle(float3_t::kUnitZ, kFloatPi / 2);
    FND_TEST_TRUE(all(approx_equal(
        mul_point(rm_z, float3_t::kUnitX), float3_t::kUnitY)));
    FND_TEST_TRUE(all(approx_equal(
        mul_direction(rm_z, float3_t::kUnitX), float3_t::kUnitY)));
    // The origin stays in place; the determinant is 1; the inverse rotates
    // back by -angle.
    FND_TEST_TRUE(all(mul_point(rm, float3_t::kZero) == float3_t::kZero));
    FND_TEST_TRUE(approx_equal(determinant(rm), 1.0f));
    FND_TEST_TRUE(
        approx_equal(inverse(rm), make_float3x4_axis_angle(kAxis, -kAngle)));
}

void unittests_math_matrix_construction_make_float3x4_scale()
{
    // A diagonal linear part and no translation.
    constexpr float3_t kScale0{2, -0.5f, 4};
    const float3x4_t sm0 = make_float3x4_scale(kScale0);
    FND_TEST_TRUE(sm0 == float3x4_t{float3_t{kScale0.x, 0, 0},
        float3_t{0, kScale0.y, 0}, float3_t{0, 0, kScale0.z}, float3_t{0}});
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

void unittests_math_matrix_construction_make_float3x4_translation()
{
    // The identity linear part and the translation in col3.
    constexpr float3_t kTranslation0{1, -2, 0.5f};
    const float3x4_t tm0 = make_float3x4_translation(kTranslation0);
    FND_TEST_TRUE(tm0 == float3x4_t{float3_t::kUnitX, float3_t::kUnitY,
        float3_t::kUnitZ, kTranslation0});

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

void unittests_math_matrix_construction_make_float3x4_trs()
{
    // mrs is the linear part and t the translation.
    constexpr float3_t kTranslation{1, -2, 0.5f};
    constexpr float3_t kScale{2, 3, 4};
    const float3x3_t mrs = make_float3x3_axis_angle(float3_t::kUnitZ, 0.75f)
        * make_float3x3_scale(kScale);
    const float3x4_t m = make_float3x4_trs(kTranslation, mrs);
    FND_TEST_TRUE(m == float3x4_t{mrs.col0, mrs.col1, mrs.col2, kTranslation});

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

    // From a translation, a quaternion rotation and a scale: the same as mrs
    // = make_float3x3(r) * make_float3x3_scale(s).
    const quat_t r = make_quat_axis_angle(float3_t{0.6f, 0, -0.8f}, 2);
    const float3x4_t m_trs = make_float3x4_trs(kTranslation, r, kScale);
    FND_TEST_TRUE(m_trs
        == make_float3x4_trs(
            kTranslation, make_float3x3(r) * make_float3x3_scale(kScale)));
    // s is applied first, then r, then t.
    FND_TEST_TRUE(all(approx_equal(mul_point(m_trs, kPoint),
        mul(r, kScale * kPoint) + kTranslation, 1e-4f)));
    // Each part alone.
    FND_TEST_TRUE(
        make_float3x4_trs(kTranslation, quat_t::kIdentity, float3_t{1})
        == make_float3x4_translation(kTranslation));
    FND_TEST_TRUE(
        make_float3x4_trs(float3_t::kZero, quat_t::kIdentity, kScale)
        == make_float3x4_scale(kScale));
    FND_TEST_TRUE(make_float3x4_trs(float3_t::kZero, r, float3_t{1})
        == make_float3x4(r));

    // Usable in constant expressions.
    static_assert(
        make_float3x4_trs(kTranslation, float3x3_t::kIdentity).col3.z == 0.5f);
}

void unittests_math_matrix_construction_make_float4x4_axis_angle()
{
    // The float3x3_t rotation in the upper-left 3x3; no translation, bottom
    // row 0, 0, 0, 1.
    constexpr float3_t kAxis{0.6f, 0, -0.8f};
    constexpr float_t kAngle = 0.75f;
    const float3x3_t rm3 = make_float3x3_axis_angle(kAxis, kAngle);
    const float4x4_t rm = make_float4x4_axis_angle(kAxis, kAngle);
    FND_TEST_TRUE(rm == float4x4_t{float4(rm3.col0, 0), float4(rm3.col1, 0),
        float4(rm3.col2, 0), float4_t::kUnitW});

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

void unittests_math_matrix_construction_make_float4x4_scale()
{
    // A diagonal matrix with 1 in the bottom-right corner.
    constexpr float3_t kScale0{2, -0.5f, 4};
    const float4x4_t sm0 = make_float4x4_scale(kScale0);
    FND_TEST_TRUE(sm0 == float4x4_t{float4_t{kScale0.x, 0, 0, 0},
        float4_t{0, kScale0.y, 0, 0}, float4_t{0, 0, kScale0.z, 0},
        float4_t::kUnitW});
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

void unittests_math_matrix_construction_make_float4x4_translation()
{
    // The identity with {t, 1} as the last column.
    constexpr float3_t kTranslation0{1, -2, 0.5f};
    const float4x4_t tm0 = make_float4x4_translation(kTranslation0);
    FND_TEST_TRUE(tm0 == float4x4_t{float4_t::kUnitX, float4_t::kUnitY,
        float4_t::kUnitZ, float4(kTranslation0, 1)});

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

void unittests_math_matrix_construction_make_float4x4_trs()
{
    // mrs in the upper-left 3x3, {t, 1} as the last column.
    constexpr float3_t kTranslation{1, -2, 0.5f};
    constexpr float3_t kScale{2, 3, 4};
    const float3x3_t mrs = make_float3x3_axis_angle(float3_t::kUnitZ, 0.75f)
        * make_float3x3_scale(kScale);
    const float4x4_t m = make_float4x4_trs(kTranslation, mrs);
    FND_TEST_TRUE(m == float4x4_t{float4(mrs.col0, 0), float4(mrs.col1, 0),
        float4(mrs.col2, 0), float4(kTranslation, 1)});

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

    // From a translation, a quaternion rotation and a scale: the same as mrs
    // = make_float3x3(r) * make_float3x3_scale(s).
    const quat_t r = make_quat_axis_angle(float3_t{0.6f, 0, -0.8f}, 2);
    const float4x4_t m_trs = make_float4x4_trs(kTranslation, r, kScale);
    FND_TEST_TRUE(m_trs
        == make_float4x4_trs(
            kTranslation, make_float3x3(r) * make_float3x3_scale(kScale)));
    // s is applied first, then r, then t; w stays 1.
    FND_TEST_TRUE(all(approx_equal(mul(m_trs, float4(kPoint, 1)),
        float4(mul(r, kScale * kPoint) + kTranslation, 1), 1e-4f)));
    // Each part alone.
    FND_TEST_TRUE(
        make_float4x4_trs(kTranslation, quat_t::kIdentity, float3_t{1})
        == make_float4x4_translation(kTranslation));
    FND_TEST_TRUE(
        make_float4x4_trs(float3_t::kZero, quat_t::kIdentity, kScale)
        == make_float4x4_scale(kScale));
    FND_TEST_TRUE(make_float4x4_trs(float3_t::kZero, r, float3_t{1})
        == make_float4x4(r));

    // Usable in constant expressions.
    static_assert(
        make_float4x4_trs(kTranslation, float3x3_t::kIdentity).col3.z == 0.5f);
}

void unittests_math_matrix_construction()
{
    unittests_math_matrix_construction_make_float3x3_axis_angle();
    unittests_math_matrix_construction_make_float3x3_scale();
    unittests_math_matrix_construction_make_float3x4_axis_angle();
    unittests_math_matrix_construction_make_float3x4_scale();
    unittests_math_matrix_construction_make_float3x4_translation();
    unittests_math_matrix_construction_make_float3x4_trs();
    unittests_math_matrix_construction_make_float4x4_axis_angle();
    unittests_math_matrix_construction_make_float4x4_scale();
    unittests_math_matrix_construction_make_float4x4_translation();
    unittests_math_matrix_construction_make_float4x4_trs();
}

} // namespace fnd::unittests
