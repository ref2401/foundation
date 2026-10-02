module;
#include "foundation/unittests.h"


export module unittests.math:matrix_conversion;
import foundation.core;
import foundation.math;

namespace fnd::unittests {

export void unittests_math_matrix_conversion();

// Small values whose products are exact in binary, so == is reliable for
// products and copies.
constexpr float3x3_t kConversionA3x3{
    float3_t{2, 1, 0}, float3_t{-1, 3, 1}, float3_t{0.5f, 0, 4}};
constexpr float3x3_t kConversionB3x3{
    float3_t{1, 0, -1}, float3_t{2, 1, 0}, float3_t{0, -1, 2}};

constexpr float3x4_t kConversionA3x4{
    float3_t{1, 0, 2}, float3_t{0, 1, 0}, float3_t{-1, 0, 1},
    float3_t{4, 5, 6}};
constexpr float3x4_t kConversionB3x4{
    float3_t{2, -1, 0}, float3_t{0.5f, 3, 1}, float3_t{-2, 0, 4},
    float3_t{-1, 2, 0.5f}};

// Not affine: its bottom row is 4, 8, 12, 16.
constexpr float4x4_t kConversion4x4{
    float4_t{1, 2, 3, 4}, float4_t{5, 6, 7, 8}, float4_t{9, 10, 11, 12},
    float4_t{13, 14, 15, 16}};

// Normalized axes, and angles covering both signs and half a turn.
constexpr float3_t kConversionAxes[] = {float3_t::kUnitX,
    float3_t::kUnitY, float3_t::kUnitZ, float3_t{0.6f, 0, -0.8f},
    float3_t{0, 0.6f, 0.8f}, float3_t{0.48f, 0.6f, 0.64f}};
constexpr float_t kConversionAngles[] = {
    -2.5f, -0.01f, 0.75f, 2, 3, kFloatPi};

// q and -q are the same rotation.
bool_t is_same_rotation(const quat_t a, const quat_t b)
{
    return approx_equal(a, b) || approx_equal(a, -b);
}

void unittests_math_matrix_conversion_make_float3x3()
{
    // From a float3x4_t: the linear part; the translation is dropped.
    FND_TEST_TRUE(make_float3x3(kConversionA3x4)
        == float3x3_t{kConversionA3x4.col0, kConversionA3x4.col1,
            kConversionA3x4.col2});
    FND_TEST_TRUE(
        make_float3x3(float3x4_t::kIdentity) == float3x3_t::kIdentity);

    // From a float4x4_t: the upper-left 3x3; the translation and the bottom
    // row are dropped.
    FND_TEST_TRUE(make_float3x3(kConversion4x4)
        == float3x3_t{
            float3_t{1, 2, 3}, float3_t{5, 6, 7}, float3_t{9, 10, 11}});
    FND_TEST_TRUE(
        make_float3x3(float4x4_t::kIdentity) == float3x3_t::kIdentity);

    // Round trips through a larger type give m back, and going through a
    // float4x4_t drops the same as going straight from the float3x4_t.
    FND_TEST_TRUE(
        make_float3x3(make_float3x4(kConversionA3x3)) == kConversionA3x3);
    FND_TEST_TRUE(
        make_float3x3(make_float4x4(kConversionA3x3)) == kConversionA3x3);
    FND_TEST_TRUE(make_float3x3(make_float4x4(kConversionA3x4))
        == make_float3x3(kConversionA3x4));

    // From a quat_t: the rotation matrix.
    FND_TEST_TRUE(make_float3x3(quat_t::kIdentity) == float3x3_t::kIdentity);

    // Half a turn about each axis.
    FND_TEST_TRUE(make_float3x3(quat_t{1, 0, 0, 0})
        == float3x3_t{
            float3_t{1, 0, 0}, float3_t{0, -1, 0}, float3_t{0, 0, -1}});
    FND_TEST_TRUE(make_float3x3(quat_t{0, 1, 0, 0})
        == float3x3_t{
            float3_t{-1, 0, 0}, float3_t{0, 1, 0}, float3_t{0, 0, -1}});
    FND_TEST_TRUE(make_float3x3(quat_t{0, 0, 1, 0})
        == float3x3_t{
            float3_t{-1, 0, 0}, float3_t{0, -1, 0}, float3_t{0, 0, 1}});

    // The same rotation as make_float3x3_axis_angle and as mul(q, v); q and
    // -q give the same matrix.
    constexpr float3_t kVector{3, -4, 12};
    for (const float3_t axis : kConversionAxes) {
        for (const float_t angle : kConversionAngles) {
            const quat_t q = make_quat_axis_angle(axis, angle);
            const float3x3_t rm = make_float3x3(q);
            FND_TEST_TRUE(
                approx_equal(rm, make_float3x3_axis_angle(axis, angle)));
            FND_TEST_TRUE(
                all(approx_equal(mul(rm, kVector), mul(q, kVector), 1e-4f)));
            FND_TEST_TRUE(make_float3x3(-q) == rm);
        }
    }

    // A rotation: orthonormal with determinant 1. The conjugate is the
    // transpose, and the product of quaternions is the product of matrices.
    const quat_t q0 = make_quat_axis_angle(float3_t{0.6f, 0, -0.8f}, 2);
    const quat_t q1 = make_quat_axis_angle(float3_t{0, 0.6f, 0.8f}, -0.75f);
    const float3x3_t rm0 = make_float3x3(q0);
    FND_TEST_TRUE(approx_equal(rm0 * transpose(rm0), float3x3_t::kIdentity));
    FND_TEST_TRUE(approx_equal(determinant(rm0), 1.0f));
    FND_TEST_TRUE(approx_equal(make_float3x3(conjugate(q0)), transpose(rm0)));
    FND_TEST_TRUE(
        approx_equal(make_float3x3(q0 * q1), rm0 * make_float3x3(q1)));

    // Usable in constant expressions.
    static_assert(make_float3x3(kConversion4x4).col2.z == 11.0f);
}

void unittests_math_matrix_conversion_make_float3x4()
{
    // From a float3x3_t: m as the linear part, with no translation; the same
    // as the trs builder with a zero translation.
    FND_TEST_TRUE(make_float3x4(kConversionA3x3)
        == float3x4_t{kConversionA3x3.col0, kConversionA3x3.col1,
            kConversionA3x3.col2, float3_t::kZero});
    FND_TEST_TRUE(make_float3x4(kConversionA3x3)
        == make_float3x4_trs(float3_t::kZero, kConversionA3x3));
    FND_TEST_TRUE(
        make_float3x4(float3x3_t::kIdentity) == float3x4_t::kIdentity);

    // From a float4x4_t: the top three rows; the bottom row is dropped.
    FND_TEST_TRUE(make_float3x4(kConversion4x4)
        == float3x4_t{float3_t{1, 2, 3}, float3_t{5, 6, 7},
            float3_t{9, 10, 11}, float3_t{13, 14, 15}});
    FND_TEST_TRUE(
        make_float3x4(float4x4_t::kIdentity) == float3x4_t::kIdentity);

    // A round trip through a float4x4_t gives m back.
    FND_TEST_TRUE(
        make_float3x4(make_float4x4(kConversionA3x4)) == kConversionA3x4);

    // A float3x3_t is a transform with no translation: the conversion
    // commutes with the product, the inverse and the determinant, and the
    // transformed direction is the same.
    FND_TEST_TRUE(make_float3x4(kConversionA3x3 * kConversionB3x3)
        == make_float3x4(kConversionA3x3) * make_float3x4(kConversionB3x3));
    FND_TEST_TRUE(approx_equal(make_float3x4(inverse(kConversionA3x3)),
        inverse(make_float3x4(kConversionA3x3))));
    FND_TEST_TRUE(approx_equal(determinant(make_float3x4(kConversionA3x3)),
        determinant(kConversionA3x3)));
    constexpr float3_t kDirection{3, -4, 12};
    FND_TEST_TRUE(all(mul_direction(make_float3x4(kConversionA3x3), kDirection)
        == mul(kConversionA3x3, kDirection)));

    // From a quat_t: the float3x3_t rotation and no translation.
    const quat_t q = make_quat_axis_angle(float3_t{0.6f, 0, -0.8f}, 2);
    const float3x3_t rm = make_float3x3(q);
    FND_TEST_TRUE(make_float3x4(q)
        == float3x4_t{rm.col0, rm.col1, rm.col2, float3_t::kZero});
    FND_TEST_TRUE(make_float3x4(quat_t::kIdentity) == float3x4_t::kIdentity);

    // Points and directions are rotated as by mul(q, v).
    constexpr float3_t kVector{3, -4, 12};
    FND_TEST_TRUE(all(approx_equal(
        mul_point(make_float3x4(q), kVector), mul(q, kVector), 1e-4f)));
    FND_TEST_TRUE(all(approx_equal(
        mul_direction(make_float3x4(q), kVector), mul(q, kVector), 1e-4f)));

    // Usable in constant expressions.
    static_assert(make_float3x4(kConversion4x4).col3.z == 15.0f);
}

void unittests_math_matrix_conversion_make_float4x4()
{
    // From a float3x3_t: m as the upper-left 3x3, with no translation and the
    // bottom row 0, 0, 0, 1; the same as the trs builder with a zero
    // translation.
    FND_TEST_TRUE(make_float4x4(kConversionA3x3)
        == float4x4_t{float4_t{2, 1, 0, 0}, float4_t{-1, 3, 1, 0},
            float4_t{0.5f, 0, 4, 0}, float4_t{0, 0, 0, 1}});
    FND_TEST_TRUE(make_float4x4(kConversionA3x3)
        == make_float4x4_trs(float3_t::kZero, kConversionA3x3));
    FND_TEST_TRUE(
        make_float4x4(float3x3_t::kIdentity) == float4x4_t::kIdentity);

    // From a float3x4_t: m with its implicit bottom row 0, 0, 0, 1; the trs
    // builders agree.
    FND_TEST_TRUE(make_float4x4(kConversionA3x4)
        == float4x4_t{float4_t{1, 0, 2, 0}, float4_t{0, 1, 0, 0},
            float4_t{-1, 0, 1, 0}, float4_t{4, 5, 6, 1}});
    FND_TEST_TRUE(
        make_float4x4(float3x4_t::kIdentity) == float4x4_t::kIdentity);
    constexpr float3_t kTranslation{1, -2, 0.5f};
    FND_TEST_TRUE(
        make_float4x4(make_float3x4_trs(kTranslation, kConversionA3x3))
        == make_float4x4_trs(kTranslation, kConversionA3x3));

    // The float4x4_t is the same transform: the conversion commutes with the
    // product, the inverse and the determinant, and mul gives the same
    // vector, with w carried through.
    FND_TEST_TRUE(make_float4x4(kConversionA3x4 * kConversionB3x4)
        == make_float4x4(kConversionA3x4) * make_float4x4(kConversionB3x4));
    FND_TEST_TRUE(make_float4x4(kConversionA3x3 * kConversionB3x3)
        == make_float4x4(kConversionA3x3) * make_float4x4(kConversionB3x3));
    FND_TEST_TRUE(approx_equal(make_float4x4(inverse(kConversionB3x4)),
        inverse(make_float4x4(kConversionB3x4))));
    FND_TEST_TRUE(approx_equal(make_float4x4(inverse(kConversionA3x3)),
        inverse(make_float4x4(kConversionA3x3))));
    FND_TEST_TRUE(approx_equal(determinant(make_float4x4(kConversionB3x4)),
        determinant(kConversionB3x4)));
    FND_TEST_TRUE(approx_equal(determinant(make_float4x4(kConversionA3x3)),
        determinant(kConversionA3x3)));
    constexpr float4_t kPoint{3, -4, 12, 1};
    constexpr float4_t kDirection{3, -4, 12, 0};
    FND_TEST_TRUE(all(mul(make_float4x4(kConversionB3x4), kPoint)
        == float4(mul(kConversionB3x4, kPoint), 1)));
    FND_TEST_TRUE(all(mul(make_float4x4(kConversionB3x4), kDirection)
        == float4(mul(kConversionB3x4, kDirection), 0)));
    FND_TEST_TRUE(all(mul(make_float4x4(kConversionA3x3), kPoint)
        == float4(mul(kConversionA3x3, float3(kPoint)), 1)));

    // From a quat_t: the float3x3_t rotation, no translation and the bottom
    // row 0, 0, 0, 1.
    const quat_t q = make_quat_axis_angle(float3_t{0.6f, 0, -0.8f}, 2);
    const float3x3_t rm = make_float3x3(q);
    FND_TEST_TRUE(make_float4x4(q)
        == float4x4_t{float4(rm.col0, 0), float4(rm.col1, 0),
            float4(rm.col2, 0), float4_t::kUnitW});
    FND_TEST_TRUE(make_float4x4(quat_t::kIdentity) == float4x4_t::kIdentity);

    // Points are rotated as by mul(q, v) and keep w == 1.
    constexpr float3_t kVector{3, -4, 12};
    FND_TEST_TRUE(all(approx_equal(mul(make_float4x4(q), float4(kVector, 1)),
        float4(mul(q, kVector), 1), 1e-4f)));

    // Usable in constant expressions.
    static_assert(make_float4x4(kConversionA3x4).col3.w == 1.0f);
}

void unittests_math_matrix_conversion_make_quat()
{
    FND_TEST_TRUE(make_quat(float3x3_t::kIdentity) == quat_t::kIdentity);

    // Half a turn about each axis: diag(1, -1, -1) and the like, where the
    // trace is -1 and a diagonal component picks the branch.
    FND_TEST_TRUE(is_same_rotation(
        make_quat(make_float3x3_axis_angle(float3_t::kUnitX, kFloatPi)),
        quat_t(1, 0, 0, 0)));
    FND_TEST_TRUE(is_same_rotation(
        make_quat(make_float3x3_axis_angle(float3_t::kUnitY, kFloatPi)),
        quat_t(0, 1, 0, 0)));
    FND_TEST_TRUE(is_same_rotation(
        make_quat(make_float3x3_axis_angle(float3_t::kUnitZ, kFloatPi)),
        quat_t(0, 0, 1, 0)));

    // The same rotation as make_quat_axis_angle, normalized, and a round trip
    // through the matrix gives q or -q back. The axes and angles reach each
    // of the four branches.
    for (const float3_t axis : kConversionAxes) {
        for (const float_t angle : kConversionAngles) {
            const quat_t q = make_quat_axis_angle(axis, angle);
            const quat_t q_from_m
                = make_quat(make_float3x3_axis_angle(axis, angle));
            FND_TEST_TRUE(is_same_rotation(q_from_m, q));
            FND_TEST_TRUE(is_normalized(q_from_m, 1e-5f));
            FND_TEST_TRUE(is_same_rotation(make_quat(make_float3x3(q)), q));
        }
    }

    // A positive scale per axis is stripped: the rotation is the same.
    const float3x3_t rm = make_float3x3_axis_angle(float3_t{0.6f, 0, -0.8f}, 2);
    const quat_t q = make_quat(rm);
    FND_TEST_TRUE(is_same_rotation(
        make_quat(rm * make_float3x3_scale(float3_t{2, 3, 0.5f})), q));
    FND_TEST_TRUE(is_same_rotation(make_quat(rm * 10.0f), q));

    // From a float3x4_t or a float4x4_t: the translation and the bottom row
    // are dropped.
    constexpr float3_t kTranslation{1, -2, 0.5f};
    FND_TEST_TRUE(make_quat(make_float3x4_trs(kTranslation, rm)) == q);
    float4x4_t m = make_float4x4_trs(kTranslation, rm);
    set_row3(m, float4_t{1, 2, 3, 4});
    FND_TEST_TRUE(make_quat(m) == q);
}

void unittests_math_matrix_conversion()
{
    unittests_math_matrix_conversion_make_float3x3();
    unittests_math_matrix_conversion_make_float3x4();
    unittests_math_matrix_conversion_make_float4x4();
    unittests_math_matrix_conversion_make_quat();
}

} // namespace fnd::unittests
