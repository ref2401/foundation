module;
#include "foundation/unittests.h"


export module unittests.math:quat;
import foundation.core;
import foundation.math;

// Some tests overflow to infinity on purpose. In Release, /GL lets the
// optimizer fold their constant inputs, and it reports C4756 at the
// library line it inlined rather than here.
#pragma warning(disable: 4756)

namespace fnd::unittests {

export void unittests_math_quat();

// Not unit quaternions: small values whose products are exact in binary, so
// == is reliable for the algebra. length_sqr(kQuatA) is 30.
constexpr quat_t kQuatA{1, 2, 3, 4};
constexpr quat_t kQuatB{-2, 0.5f, 1, 3};
constexpr quat_t kQuatC{0.5f, -1, 2, 1};

// The basis quaternions i, j and k.
constexpr quat_t kQuatI{1, 0, 0, 0};
constexpr quat_t kQuatJ{0, 1, 0, 0};
constexpr quat_t kQuatK{0, 0, 1, 0};

void unittests_math_quat_constants()
{
    FND_TEST_TRUE(quat_t::kZero == quat_t(0, 0, 0, 0));
    FND_TEST_TRUE(quat_t::kIdentity == quat_t(0, 0, 0, 1));
    FND_TEST_TRUE(quat_t::kZero == quat_t{});
    // The constants are usable in constant expressions.
    static_assert(quat_t::kIdentity.w == 1.0f);
}

void unittests_math_quat_constructors()
{
    // The default ctor gives the zero quaternion.
    const quat_t q_zero;
    FND_TEST_TRUE(q_zero.x == 0 && q_zero.y == 0 && q_zero.z == 0
        && q_zero.w == 0);

    // From four components.
    const quat_t q{1, -2, 3, -4};
    FND_TEST_TRUE(q.x == 1 && q.y == -2 && q.z == 3 && q.w == -4);
}

void unittests_math_quat_unary_minus_operator()
{
    FND_TEST_TRUE(-kQuatA == quat_t(-1, -2, -3, -4));
    FND_TEST_TRUE(-(-kQuatA) == kQuatA);
    static_assert((-quat_t::kIdentity).w == -1.0f);
}

void unittests_math_quat_equality_operators()
{
    FND_TEST_TRUE(kQuatA == kQuatA);
    FND_TEST_FALSE(kQuatA != kQuatA);
    FND_TEST_FALSE(kQuatA == kQuatB);
    FND_TEST_TRUE(kQuatA != kQuatB);

    // Each component counts.
    FND_TEST_TRUE(kQuatA != quat_t(0, 2, 3, 4));
    FND_TEST_TRUE(kQuatA != quat_t(1, 0, 3, 4));
    FND_TEST_TRUE(kQuatA != quat_t(1, 2, 0, 4));
    FND_TEST_TRUE(kQuatA != quat_t(1, 2, 3, 0));

    // q and -q are the same rotation, but not equal; a NaN is never equal.
    FND_TEST_TRUE(quat_t::kIdentity != -quat_t::kIdentity);
    const quat_t q_nan{kFloatNaN, 0, 0, 1};
    FND_TEST_FALSE(q_nan == q_nan);
    FND_TEST_TRUE(q_nan != q_nan);
}

void unittests_math_quat_multiplication_operator()
{
    // The Hamilton product: i * j = k, j * k = i, k * i = j, the reversed
    // orders negate, and i * i = j * j = k * k = -1.
    FND_TEST_TRUE(kQuatI * kQuatJ == kQuatK);
    FND_TEST_TRUE(kQuatJ * kQuatK == kQuatI);
    FND_TEST_TRUE(kQuatK * kQuatI == kQuatJ);
    FND_TEST_TRUE(kQuatJ * kQuatI == -kQuatK);
    FND_TEST_TRUE(kQuatK * kQuatJ == -kQuatI);
    FND_TEST_TRUE(kQuatI * kQuatK == -kQuatJ);
    FND_TEST_TRUE(kQuatI * kQuatI == -quat_t::kIdentity);
    FND_TEST_TRUE(kQuatJ * kQuatJ == -quat_t::kIdentity);
    FND_TEST_TRUE(kQuatK * kQuatK == -quat_t::kIdentity);

    // The identity is neutral, zero absorbs, and the product is associative
    // but not commutative.
    FND_TEST_TRUE(kQuatA * quat_t::kIdentity == kQuatA);
    FND_TEST_TRUE(quat_t::kIdentity * kQuatA == kQuatA);
    FND_TEST_TRUE(kQuatA * quat_t::kZero == quat_t::kZero);
    FND_TEST_TRUE((kQuatA * kQuatB) * kQuatC == kQuatA * (kQuatB * kQuatC));
    FND_TEST_TRUE(kQuatA * kQuatB != kQuatB * kQuatA);
    FND_TEST_TRUE(kQuatA * kQuatB == quat_t(-4.5f, 1, 17.5f, 10));

    // a * b applies b first, then a; rotations about one axis add up.
    constexpr float3_t kAxis{0.6f, 0, -0.8f};
    constexpr float3_t kVector{3, -4, 12};
    const quat_t q0 = make_quat_axis_angle(kAxis, 0.5f);
    const quat_t q1 = make_quat_axis_angle(float3_t::kUnitY, -1.25f);
    FND_TEST_TRUE(all(
        approx_equal(mul(q0 * q1, kVector), mul(q0, mul(q1, kVector)), 1e-4f)));
    FND_TEST_TRUE(approx_equal(make_quat_axis_angle(kAxis, 0.5f)
            * make_quat_axis_angle(kAxis, 0.75f),
        make_quat_axis_angle(kAxis, 1.25f)));

    // Usable in constant expressions.
    static_assert((kQuatI * kQuatJ).z == 1.0f);
}

void unittests_math_quat_scalar_multiplication_operator()
{
    // Each component is scaled, in either order.
    constexpr float_t kScale = 2;
    FND_TEST_TRUE(kQuatA * kScale == quat_t(2, 4, 6, 8));
    FND_TEST_TRUE(kScale * kQuatA == kQuatA * kScale);
    FND_TEST_TRUE(kQuatA * 1 == kQuatA);
    FND_TEST_TRUE(kQuatA * 0 == quat_t::kZero);
    FND_TEST_TRUE(kQuatA * -1 == -kQuatA);

    // The scale factors out of the Hamilton product, and length_sqr scales
    // by its square.
    FND_TEST_TRUE((kQuatA * kScale) * kQuatB == kScale * (kQuatA * kQuatB));
    FND_TEST_TRUE(kQuatA * (kQuatB * kScale) == kScale * (kQuatA * kQuatB));
    FND_TEST_TRUE(
        length_sqr(kQuatA * kScale) == kScale * kScale * length_sqr(kQuatA));

    // A scaled rotation is not a unit quaternion; normalizing it gives the
    // rotation back.
    const quat_t q = make_quat_axis_angle(float3_t{0, 0.6f, 0.8f}, 0.75f);
    FND_TEST_FALSE(is_normalized(q * 3));
    FND_TEST_TRUE(approx_equal(normalize(q * 3), q));

    // Usable in constant expressions.
    static_assert((kQuatA * 2.0f).w == 8.0f);
    static_assert((2.0f * kQuatA).w == 8.0f);
}

void unittests_math_quat_addition_operator()
{
    FND_TEST_TRUE(kQuatA + kQuatB == quat_t(-1, 2.5f, 4, 7));

    // Commutative and associative; zero is neutral and -q cancels q.
    FND_TEST_TRUE(kQuatA + kQuatB == kQuatB + kQuatA);
    FND_TEST_TRUE((kQuatA + kQuatB) + kQuatC == kQuatA + (kQuatB + kQuatC));
    FND_TEST_TRUE(kQuatA + quat_t::kZero == kQuatA);
    FND_TEST_TRUE(kQuatA + -kQuatA == quat_t::kZero);

    // The Hamilton product distributes over the sum, and a sum of scaled
    // quaternions scales: q * 2 == q + q.
    FND_TEST_TRUE(
        kQuatA * (kQuatB + kQuatC) == kQuatA * kQuatB + kQuatA * kQuatC);
    FND_TEST_TRUE(
        (kQuatB + kQuatC) * kQuatA == kQuatB * kQuatA + kQuatC * kQuatA);
    FND_TEST_TRUE(kQuatA + kQuatA == kQuatA * 2);

    // A sum of rotations is generally not a unit quaternion.
    FND_TEST_FALSE(is_normalized(quat_t::kIdentity + kQuatK));

    // Usable in constant expressions.
    static_assert((kQuatI + kQuatJ).y == 1.0f);
}

void unittests_math_quat_compound_assignment_operators()
{
    // Each compound operator gives the same as its binary operator.
    quat_t q = kQuatA;
    q *= kQuatB;
    FND_TEST_TRUE(q == kQuatA * kQuatB);
    q *= quat_t::kIdentity;
    FND_TEST_TRUE(q == kQuatA * kQuatB);

    q = kQuatA;
    q *= 2.0f;
    FND_TEST_TRUE(q == kQuatA * 2.0f);
    q *= 0.5f;
    FND_TEST_TRUE(q == kQuatA);

    q = kQuatA;
    q += kQuatB;
    FND_TEST_TRUE(q == kQuatA + kQuatB);
    q += quat_t::kZero;
    FND_TEST_TRUE(q == kQuatA + kQuatB);
}

void unittests_math_quat_approx_equal()
{
    FND_TEST_TRUE(approx_equal(kQuatA, kQuatA));
    FND_TEST_FALSE(approx_equal(kQuatA, kQuatB));

    // Within the default 1e-5 in every component, and with a custom
    // max_abs_diff.
    FND_TEST_TRUE(approx_equal(kQuatA, quat_t(1, 2, 3, 4.000001f)));
    FND_TEST_FALSE(approx_equal(kQuatA, quat_t(1, 2, 3, 4.001f)));
    FND_TEST_FALSE(approx_equal(kQuatA, quat_t(1.001f, 2, 3, 4)));
    FND_TEST_TRUE(approx_equal(kQuatA, quat_t(1.001f, 2, 3, 4), 0.01f));

    // q and -q are the same rotation, but not approximately equal; a NaN is
    // never approximately equal.
    FND_TEST_FALSE(approx_equal(quat_t::kIdentity, -quat_t::kIdentity));
    const quat_t q_nan{0, kFloatNaN, 0, 1};
    FND_TEST_FALSE(approx_equal(q_nan, q_nan));
}

void unittests_math_quat_conjugate()
{
    FND_TEST_TRUE(conjugate(kQuatA) == quat_t(-1, -2, -3, 4));
    FND_TEST_TRUE(conjugate(conjugate(kQuatA)) == kQuatA);
    FND_TEST_TRUE(conjugate(quat_t::kIdentity) == quat_t::kIdentity);

    // The conjugate of a product is the product of the conjugates,
    // reversed, and q * conjugate(q) is length_sqr(q) in w.
    FND_TEST_TRUE(conjugate(kQuatA * kQuatB)
        == conjugate(kQuatB) * conjugate(kQuatA));
    FND_TEST_TRUE(kQuatA * conjugate(kQuatA) == quat_t(0, 0, 0, 30));

    // For a rotation it is the opposite rotation.
    const quat_t q = make_quat_axis_angle(float3_t::kUnitZ, 0.75f);
    FND_TEST_TRUE(approx_equal(
        conjugate(q), make_quat_axis_angle(float3_t::kUnitZ, -0.75f)));
    static_assert(conjugate(kQuatA).x == -1.0f);
}

void unittests_math_quat_dot()
{
    FND_TEST_TRUE(dot(kQuatA, kQuatB) == 14.0f);
    FND_TEST_TRUE(dot(kQuatA, kQuatB) == dot(kQuatB, kQuatA));
    FND_TEST_TRUE(dot(kQuatA, -kQuatB) == -14.0f);
    FND_TEST_TRUE(dot(kQuatA, quat_t::kZero) == 0.0f);
    FND_TEST_TRUE(dot(kQuatA, kQuatA) == length_sqr(kQuatA));
    static_assert(dot(kQuatI, kQuatJ) == 0.0f);
}

// kQuatA with component idx (0, 1, 2, 3 for x, y, z, w) set to value.
quat_t quat_with_component(const uint_t idx, const float_t value)
{
    quat_t q = kQuatA;
    float_t* const components[] = {&q.x, &q.y, &q.z, &q.w};
    *components[idx] = value;
    return q;
}

void unittests_math_quat_isfinite()
{
    FND_TEST_TRUE(isfinite(quat_t::kZero));
    FND_TEST_TRUE(isfinite(quat_t::kIdentity));
    FND_TEST_TRUE(isfinite(kQuatA));
    FND_TEST_TRUE(isfinite(
        quat_t(kFloatMaxValue, kFloatMinValue, kFloatMinSubnormal, -0.0f)));

    // A single NaN or infinity in any component makes q not finite.
    for (uint_t idx = 0; idx < 4; ++idx) {
        FND_TEST_FALSE(isfinite(quat_with_component(idx, kFloatNaN)));
        FND_TEST_FALSE(isfinite(quat_with_component(idx, kFloatInfinity)));
        FND_TEST_FALSE(isfinite(quat_with_component(idx, -kFloatInfinity)));
    }

    // NaN and infinity together: isnan and isinf are both true.
    const quat_t q{kFloatNaN, 1, -kFloatInfinity, 0};
    FND_TEST_FALSE(isfinite(q));
    FND_TEST_TRUE(isinf(q));
    FND_TEST_TRUE(isnan(q));
}

void unittests_math_quat_isinf()
{
    FND_TEST_FALSE(isinf(quat_t::kZero));
    FND_TEST_FALSE(isinf(kQuatA));
    FND_TEST_FALSE(
        isinf(quat_t(kFloatMaxValue, kFloatMinValue, kFloatMaxValue, 1)));

    // Infinity of either sign in any component; NaN is not infinity.
    for (uint_t idx = 0; idx < 4; ++idx) {
        FND_TEST_TRUE(isinf(quat_with_component(idx, kFloatInfinity)));
        FND_TEST_TRUE(isinf(quat_with_component(idx, -kFloatInfinity)));
        FND_TEST_FALSE(isinf(quat_with_component(idx, kFloatNaN)));
    }

    // A product that overflows.
    FND_TEST_TRUE(isinf(quat_t(kFloatMaxValue, 0, 0, 1) * 2.0f));
}

void unittests_math_quat_isnan()
{
    FND_TEST_FALSE(isnan(quat_t::kZero));
    FND_TEST_FALSE(isnan(kQuatA));

    // NaN in any component; infinity is not NaN.
    for (uint_t idx = 0; idx < 4; ++idx) {
        FND_TEST_TRUE(isnan(quat_with_component(idx, kFloatNaN)));
        FND_TEST_FALSE(isnan(quat_with_component(idx, kFloatInfinity)));
        FND_TEST_FALSE(isnan(quat_with_component(idx, -kFloatInfinity)));
    }

    // inf - inf is NaN.
    const quat_t q_inf{kFloatInfinity, 0, 0, 1};
    FND_TEST_TRUE(isnan(q_inf + -q_inf));
}

void unittests_math_quat_length_sqr()
{
    FND_TEST_TRUE(length_sqr(kQuatA) == 30.0f);
    FND_TEST_TRUE(length_sqr(-kQuatA) == 30.0f);
    FND_TEST_TRUE(length_sqr(quat_t::kZero) == 0.0f);
    FND_TEST_TRUE(length_sqr(quat_t::kIdentity) == 1.0f);
    static_assert(length_sqr(kQuatA) == 30.0f);
}

void unittests_math_quat_inverse()
{
    FND_TEST_TRUE(inverse(quat_t::kIdentity) == quat_t::kIdentity);
    // A power-of-two length_sqr keeps it exact: {1, 1, 1, 1} / 4.
    FND_TEST_TRUE(
        inverse(quat_t(1, 1, 1, 1)) == quat_t(-0.25f, -0.25f, -0.25f, 0.25f));

    // Not only for a unit quaternion: q * inverse(q) and inverse(q) * q are
    // the identity, and inverting twice gives q back.
    FND_TEST_TRUE(approx_equal(kQuatA * inverse(kQuatA), quat_t::kIdentity));
    FND_TEST_TRUE(approx_equal(inverse(kQuatA) * kQuatA, quat_t::kIdentity));
    FND_TEST_TRUE(approx_equal(inverse(inverse(kQuatA)), kQuatA));
    FND_TEST_TRUE(approx_equal(
        inverse(kQuatA * kQuatB), inverse(kQuatB) * inverse(kQuatA)));

    // For a unit quaternion it is the conjugate.
    const quat_t q = make_quat_axis_angle(float3_t{0, 0.6f, 0.8f}, 2.0f);
    FND_TEST_TRUE(approx_equal(inverse(q), conjugate(q)));
}

void unittests_math_quat_is_normalized()
{
    FND_TEST_TRUE(is_normalized(quat_t::kIdentity));
    FND_TEST_TRUE(is_normalized(-quat_t::kIdentity));
    FND_TEST_TRUE(is_normalized(quat_t(0.5f, 0.5f, 0.5f, 0.5f)));
    FND_TEST_FALSE(is_normalized(quat_t::kZero));
    FND_TEST_FALSE(is_normalized(kQuatA));

    // Within the default 1e-4 of length_sqr 1, and with a custom
    // max_abs_diff.
    FND_TEST_TRUE(is_normalized(quat_t(0, 0, 0, 1.00001f)));
    FND_TEST_FALSE(is_normalized(quat_t(0, 0, 0, 1.001f)));
    FND_TEST_TRUE(is_normalized(quat_t(0, 0, 0, 1.001f), 0.01f));
}

void unittests_math_quat_length()
{
    FND_TEST_TRUE(length(quat_t(1, 1, 1, 1)) == 2.0f);
    FND_TEST_TRUE(length(quat_t::kZero) == 0.0f);
    FND_TEST_TRUE(length(quat_t::kIdentity) == 1.0f);
    FND_TEST_TRUE(approx_equal(length(kQuatA), sqrt(30.0f)));
}

void unittests_math_quat_make_quat_axis_angle()
{
    // A zero angle is the identity; a full turn is -identity, the same
    // rotation.
    FND_TEST_TRUE(make_quat_axis_angle(float3_t::kUnitX, 0) == quat_t::kIdentity);
    FND_TEST_TRUE(approx_equal(make_quat_axis_angle(float3_t::kUnitX, 2 * kFloatPi),
        -quat_t::kIdentity));

    // (axis * sin(angle / 2), cos(angle / 2)): half a turn about z is k.
    FND_TEST_TRUE(
        approx_equal(make_quat_axis_angle(float3_t::kUnitZ, kFloatPi), kQuatK));
    constexpr float3_t kAxis{0, 0.6f, 0.8f};
    constexpr float_t kAngle = 0.75f;
    const quat_t q = make_quat_axis_angle(kAxis, kAngle);
    FND_TEST_TRUE(approx_equal(q,
        quat_t(0, 0.6f * sin(0.5f * kAngle), 0.8f * sin(0.5f * kAngle),
            cos(0.5f * kAngle))));
    FND_TEST_TRUE(is_normalized(q));

    // A negative angle is the opposite rotation.
    FND_TEST_TRUE(
        approx_equal(make_quat_axis_angle(kAxis, -kAngle), conjugate(q)));
}

void unittests_math_quat_mul()
{
    constexpr float3_t kVector{3, -4, 12};
    FND_TEST_TRUE(all(mul(quat_t::kIdentity, kVector) == kVector));

    // Right-handed: a quarter turn about z takes x to y, about x takes y to
    // z, and about y takes z to x.
    FND_TEST_TRUE(all(approx_equal(
        mul(make_quat_axis_angle(float3_t::kUnitZ, 0.5f * kFloatPi),
            float3_t::kUnitX),
        float3_t::kUnitY)));
    FND_TEST_TRUE(all(approx_equal(
        mul(make_quat_axis_angle(float3_t::kUnitX, 0.5f * kFloatPi),
            float3_t::kUnitY),
        float3_t::kUnitZ)));
    FND_TEST_TRUE(all(approx_equal(
        mul(make_quat_axis_angle(float3_t::kUnitY, 0.5f * kFloatPi),
            float3_t::kUnitZ),
        float3_t::kUnitX)));

    // The same rotation as make_float3x3_axis_angle.
    constexpr float3_t kAxes[] = {
        float3_t::kUnitX, float3_t{0.6f, 0, -0.8f}, float3_t{0, 0.6f, 0.8f}};
    constexpr float_t kAngles[] = {-2.5f, 0.75f, 3};
    for (const float3_t axis : kAxes) {
        for (const float_t angle : kAngles) {
            FND_TEST_TRUE(all(approx_equal(
                mul(make_quat_axis_angle(axis, angle), kVector),
                mul(make_float3x3_axis_angle(axis, angle), kVector), 1e-4f)));
        }
    }

    // q and -q rotate alike; the length is kept, the axis stays fixed, and
    // the inverse undoes the rotation.
    const quat_t q = make_quat_axis_angle(float3_t{0.6f, 0, -0.8f}, 2.0f);
    FND_TEST_TRUE(all(approx_equal(mul(-q, kVector), mul(q, kVector), 1e-4f)));
    FND_TEST_TRUE(approx_equal(length(mul(q, kVector)), 13.0f, 1e-4f));
    FND_TEST_TRUE(all(approx_equal(
        mul(q, float3_t{0.6f, 0, -0.8f}), float3_t{0.6f, 0, -0.8f})));
    FND_TEST_TRUE(
        all(approx_equal(mul(inverse(q), mul(q, kVector)), kVector, 1e-4f)));
}

void unittests_math_quat_nlerp()
{
    constexpr float_t kAngle = 1.2f;
    const quat_t q0 = make_quat_axis_angle(float3_t::kUnitZ, kAngle);

    // The ends, and the halfway rotation at t = 0.5.
    FND_TEST_TRUE(approx_equal(nlerp(quat_t::kIdentity, q0, 0), quat_t::kIdentity));
    FND_TEST_TRUE(approx_equal(nlerp(quat_t::kIdentity, q0, 1), q0));
    FND_TEST_TRUE(approx_equal(nlerp(quat_t::kIdentity, q0, 0.5f),
        make_quat_axis_angle(float3_t::kUnitZ, 0.5f * kAngle)));

    // The angular speed is not constant, unlike slerp: at t = 0.25 the
    // rotation is not a quarter of the angle.
    const quat_t q1 = make_quat_axis_angle(float3_t::kUnitZ, 2.0f);
    FND_TEST_FALSE(approx_equal(nlerp(quat_t::kIdentity, q1, 0.25f),
        make_quat_axis_angle(float3_t::kUnitZ, 0.5f), 1e-3f));

    // The shorter way: -b gives the same result as b.
    const quat_t q2 = make_quat_axis_angle(float3_t{0.6f, 0, -0.8f}, -2.5f);
    FND_TEST_TRUE(approx_equal(nlerp(q0, -q2, 0.3f), nlerp(q0, q2, 0.3f)));

    // The result is normalized, extrapolated t included.
    constexpr float_t kTs[] = {-0.5f, 0, 0.1f, 0.3f, 0.5f, 0.7f, 0.9f, 1, 1.5f};
    for (const float_t t : kTs) {
        FND_TEST_TRUE(is_normalized(nlerp(q0, q2, t)));
    }
}

void unittests_math_quat_normalize()
{
    const quat_t q = normalize(kQuatA);
    FND_TEST_TRUE(is_normalized(q));
    const float_t inv_length = 1 / sqrt(30.0f);
    FND_TEST_TRUE(approx_equal(q,
        quat_t(inv_length, 2 * inv_length, 3 * inv_length, 4 * inv_length)));
    FND_TEST_TRUE(normalize(quat_t(0, 0, 0, 2)) == quat_t::kIdentity);
    FND_TEST_TRUE(approx_equal(normalize(-kQuatA), -q));
}

void unittests_math_quat_normalize_safe()
{
    // As normalize when q can be normalized.
    FND_TEST_TRUE(normalize_safe(kQuatA) == normalize(kQuatA));

    // Zero gives default_value: the identity unless given.
    FND_TEST_TRUE(normalize_safe(quat_t::kZero) == quat_t::kIdentity);
    FND_TEST_TRUE(normalize_safe(quat_t::kZero, kQuatK) == kQuatK);

    // Components whose squares overflow are still normalized.
    FND_TEST_TRUE(approx_equal(normalize_safe(quat_t(1e20f, 1e20f, 1e20f, 1e20f)),
        quat_t(0.5f, 0.5f, 0.5f, 0.5f)));
}

void unittests_math_quat_slerp()
{
    // Constant angular speed: t of the way is t of the angle, extrapolated
    // t included.
    constexpr float3_t kAxis{0, 0.6f, 0.8f};
    constexpr float_t kAngle = 2.0f;
    const quat_t q0 = make_quat_axis_angle(kAxis, kAngle);
    constexpr float_t kTs[] = {-0.5f, 0, 0.25f, 0.5f, 0.75f, 1, 1.5f};
    for (const float_t t : kTs) {
        FND_TEST_TRUE(approx_equal(slerp(quat_t::kIdentity, q0, t),
            make_quat_axis_angle(kAxis, t * kAngle)));
    }

    // The shorter way: -b gives the same result as b.
    const quat_t q1 = make_quat_axis_angle(float3_t{0.6f, 0, -0.8f}, -2.5f);
    FND_TEST_TRUE(approx_equal(slerp(q0, -q1, 0.3f), slerp(q0, q1, 0.3f)));
    FND_TEST_TRUE(approx_equal(slerp(q0, -q1, 1), q1));

    // The result is normalized up to rounding.
    for (const float_t t : kTs) {
        FND_TEST_TRUE(is_normalized(slerp(q0, q1, t), 1e-5f));
    }

    // Nearly parallel and equal rotations fall back to nlerp: no NaN.
    const quat_t q2 = make_quat_axis_angle(kAxis, kAngle + 0.01f);
    FND_TEST_TRUE(approx_equal(
        slerp(q0, q2, 0.5f), make_quat_axis_angle(kAxis, kAngle + 0.005f)));
    FND_TEST_TRUE(approx_equal(slerp(q0, q0, 0.3f), q0));
    FND_TEST_TRUE(approx_equal(slerp(q0, -q0, 0.3f), q0));
}

void unittests_math_quat()
{
    unittests_math_quat_constants();
    unittests_math_quat_constructors();
    unittests_math_quat_unary_minus_operator();
    unittests_math_quat_equality_operators();
    unittests_math_quat_multiplication_operator();
    unittests_math_quat_scalar_multiplication_operator();
    unittests_math_quat_addition_operator();
    unittests_math_quat_compound_assignment_operators();
    unittests_math_quat_approx_equal();
    unittests_math_quat_conjugate();
    unittests_math_quat_dot();
    unittests_math_quat_isfinite();
    unittests_math_quat_isinf();
    unittests_math_quat_isnan();
    unittests_math_quat_length_sqr();
    unittests_math_quat_inverse();
    unittests_math_quat_is_normalized();
    unittests_math_quat_length();
    unittests_math_quat_make_quat_axis_angle();
    unittests_math_quat_mul();
    unittests_math_quat_nlerp();
    unittests_math_quat_normalize();
    unittests_math_quat_normalize_safe();
    unittests_math_quat_slerp();
}

} // namespace fnd::unittests
