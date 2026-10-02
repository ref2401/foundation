module;
#include "foundation/unittests.h"


export module unittests.math:quat_conversion;
import foundation.core;
import foundation.math;

namespace fnd::unittests {

export void unittests_math_quat_conversion();

// Normalized axes, and angles covering both signs and half a turn.
constexpr float3_t kQuatConversionAxes[] = {float3_t::kUnitX,
    float3_t::kUnitY, float3_t::kUnitZ, float3_t{0.6f, 0, -0.8f},
    float3_t{0, 0.6f, 0.8f}, float3_t{0.48f, 0.6f, 0.64f}};
constexpr float_t kQuatConversionAngles[] = {
    -2.5f, -0.01f, 0.75f, 2, 3, kFloatPi};

// q and -q are the same rotation.
bool_t is_same_rotation(const quat_t a, const quat_t b)
{
    return approx_equal(a, b) || approx_equal(a, -b);
}

void unittests_math_quat_conversion_float4()
{
    // The components, in both directions, without normalizing.
    constexpr quat_t kQuat{1, -2, 3, 4};
    FND_TEST_TRUE(all(float4(kQuat) == float4_t{1, -2, 3, 4}));
    FND_TEST_TRUE(make_quat(float4(kQuat)) == kQuat);
    FND_TEST_TRUE(all(float4(quat_t::kIdentity) == float4_t::kUnitW));

    // Usable in constant expressions.
    static_assert(float4(kQuat).w == 4.0f);
}

void unittests_math_quat_conversion_make_float3x3()
{
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
    for (const float3_t axis : kQuatConversionAxes) {
        for (const float_t angle : kQuatConversionAngles) {
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
}

void unittests_math_quat_conversion_make_float3x4()
{
    // The float3x3_t rotation and no translation.
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
}

void unittests_math_quat_conversion_make_float4x4()
{
    // The float3x3_t rotation, no translation and the bottom row 0, 0, 0, 1.
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
}

void unittests_math_quat_conversion_make_quat()
{
    // From a float4_t: the components, without normalizing.
    FND_TEST_TRUE(make_quat(float4_t{1, -2, 3, 4}) == quat_t(1, -2, 3, 4));
    static_assert(make_quat(float4_t{1, -2, 3, 4}).w == 4.0f);

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
    for (const float3_t axis : kQuatConversionAxes) {
        for (const float_t angle : kQuatConversionAngles) {
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

void unittests_math_quat_conversion()
{
    unittests_math_quat_conversion_float4();
    unittests_math_quat_conversion_make_float3x3();
    unittests_math_quat_conversion_make_float3x4();
    unittests_math_quat_conversion_make_float4x4();
    unittests_math_quat_conversion_make_quat();
}

} // namespace fnd::unittests
