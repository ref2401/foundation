module;
#include <math.h>
#include "foundation/unittests.h"


export module unittests.math:scalar;
import foundation.math;

namespace fnd::unittests {

export void unittests_math_scalar();

// ---------------------------------------------------------------------------
// Abs
// ---------------------------------------------------------------------------

void unittests_math_scalar_abs_integer_types()
{
    // byte_t
    static_assert(abs(byte_t{0}) == 0);
    static_assert(abs(byte_t{5}) == 5);
    static_assert(abs(byte_t{-5}) == 5);
    static_assert(abs(kByteMaxValue) == kByteMaxValue);
    static_assert(abs(byte_t{-kByteMaxValue}) == kByteMaxValue);
    // int_t
    static_assert(abs(int_t{0}) == 0);
    static_assert(abs(int_t{5}) == 5);
    static_assert(abs(int_t{-5}) == 5);
    static_assert(abs(kIntMaxValue) == kIntMaxValue);
    static_assert(abs(-kIntMaxValue) == kIntMaxValue);
    // long_t
    static_assert(abs(long_t{0}) == 0);
    static_assert(abs(long_t{5}) == 5);
    static_assert(abs(long_t{-5}) == 5);
    static_assert(abs(kLongMaxValue) == kLongMaxValue);
    static_assert(abs(-kLongMaxValue) == kLongMaxValue);
}

void unittests_math_scalar_abs_float_types()
{
    // float_t
    FND_TEST_TRUE(abs(0.0f) == 0.0f);
    FND_TEST_TRUE(abs(2.5f) == 2.5f);
    FND_TEST_TRUE(abs(-2.5f) == 2.5f);
    FND_TEST_FALSE(signbit(abs(-0.0f)));
    FND_TEST_TRUE(abs(-INFINITY) == INFINITY);
    FND_TEST_TRUE(isnan(abs(-NAN)));
    // double_t
    FND_TEST_TRUE(abs(0.0) == 0.0);
    FND_TEST_TRUE(abs(2.5) == 2.5);
    FND_TEST_TRUE(abs(-2.5) == 2.5);
    FND_TEST_FALSE(signbit(abs(-0.0)));
    FND_TEST_TRUE(abs(-double_t(INFINITY)) == double_t(INFINITY));
    FND_TEST_TRUE(isnan(abs(-double_t(NAN))));
}

// ---------------------------------------------------------------------------
// Comparison
// ---------------------------------------------------------------------------

void unittests_math_scalar_approx_equal_float()
{
    FND_TEST_TRUE(approx_equal(1.0f, 1.0f));
    FND_TEST_TRUE(approx_equal(2.0f, 2.0f));

    // max_abs_diff
    FND_TEST_TRUE(approx_equal(1.0f, 1.0f, 0.0f));
    FND_TEST_FALSE(approx_equal(1.0f, 1.00001f, 0.0f));
    FND_TEST_FALSE(approx_equal(1.00001f, 1.0f, 0.0f));
    FND_TEST_TRUE(approx_equal(1.0f, 1.001f, 1.0f));
    FND_TEST_TRUE(approx_equal(1.001f, 1.0f, 1.0f));
    FND_TEST_TRUE(approx_equal(1.0f, 1.001f, 0.1f));
    FND_TEST_TRUE(approx_equal(1.001f, 1.0f, 0.1f));

    // inclusive boundary
    FND_TEST_TRUE(approx_equal(1.0f, 1.5f, 0.5f)); 
    FND_TEST_FALSE(approx_equal(1.0f, 1.5f, 0.4999f));

    // accross 0
    FND_TEST_TRUE(approx_equal(-0.0f, 0.0f, 0.0f));
    FND_TEST_TRUE(approx_equal(0.0f, -0.0f, 0.0f));
    FND_TEST_TRUE(approx_equal(-0.5f, 0.5f, 1.0f));
    FND_TEST_TRUE(approx_equal(0.5f, -0.5f, 1.0f));

    // special value cases
    FND_TEST_TRUE(approx_equal(kFloatInfinity, kFloatInfinity));
    FND_TEST_TRUE(approx_equal(-kFloatInfinity, -kFloatInfinity));
    FND_TEST_FALSE(approx_equal(kFloatInfinity, -kFloatInfinity));
    FND_TEST_FALSE(approx_equal(0.0f, kFloatNaN));
    FND_TEST_FALSE(approx_equal(kFloatNaN, 0.0f));
    FND_TEST_FALSE(approx_equal(kFloatNaN, kFloatNaN));
}

void unittests_math_scalar_approx_equal_double()
{
    FND_TEST_TRUE(approx_equal(1.0, 1.0));
    FND_TEST_TRUE(approx_equal(2.0, 2.0));

    // max_abs_diff
    FND_TEST_TRUE(approx_equal(1.0, 1.0, 0.0));
    FND_TEST_FALSE(approx_equal(1.0, 1.00001, 0.0));
    FND_TEST_FALSE(approx_equal(1.00001, 1.0, 0.0));
    FND_TEST_TRUE(approx_equal(1.0, 1.001, 1.0));
    FND_TEST_TRUE(approx_equal(1.001, 1.0, 1.0));
    FND_TEST_TRUE(approx_equal(1.0, 1.001, 0.1));
    FND_TEST_TRUE(approx_equal(1.001, 1.0, 0.1));

    // inclusive boundary
    FND_TEST_TRUE(approx_equal(1.0, 1.5, 0.5));
    FND_TEST_FALSE(approx_equal(1.0, 1.5, 0.4999));

    // across 0
    FND_TEST_TRUE(approx_equal(-0.0, 0.0, 0.0));
    FND_TEST_TRUE(approx_equal(0.0, -0.0, 0.0));
    FND_TEST_TRUE(approx_equal(-0.5, 0.5, 1.0));
    FND_TEST_TRUE(approx_equal(0.5, -0.5, 1.0));

    // special value cases
    FND_TEST_TRUE(approx_equal(kDoubleInfinity, kDoubleInfinity));
    FND_TEST_TRUE(approx_equal(-kDoubleInfinity, -kDoubleInfinity));
    FND_TEST_FALSE(approx_equal(kDoubleInfinity, -kDoubleInfinity));
    FND_TEST_FALSE(approx_equal(0.0, kDoubleNaN));
    FND_TEST_FALSE(approx_equal(kDoubleNaN, 0.0));
    FND_TEST_FALSE(approx_equal(kDoubleNaN, kDoubleNaN));
}

// ---------------------------------------------------------------------------
// Trigonometry
// ---------------------------------------------------------------------------

void unittests_math_scalar_acos_float()
{
    FND_TEST_TRUE(approx_equal(acos(1.0f), 0.0f));
    FND_TEST_TRUE(approx_equal(acos(0.0f), kFloatPi / 2));
    FND_TEST_TRUE(approx_equal(acos(-1.0f), kFloatPi));
    FND_TEST_TRUE(isnan(acos(-2.0f)));
}

void unittests_math_scalar_acos_double()
{
    FND_TEST_TRUE(approx_equal(acos(1.0), 0.0));
    FND_TEST_TRUE(approx_equal(acos(0.0), kDoublePi / 2));
    FND_TEST_TRUE(approx_equal(acos(-1.0), kDoublePi));
    FND_TEST_TRUE(isnan(acos(-2.0)));
}

void unittests_math_scalar_asin_float()
{
    FND_TEST_TRUE(approx_equal(asin(0.0f), 0.0f));
    FND_TEST_TRUE(signbit(asin(-0.0f)));
    FND_TEST_TRUE(approx_equal(asin(1.0f), kFloatPi / 2));
    FND_TEST_TRUE(approx_equal(asin(-1.0f), -kFloatPi / 2));
    FND_TEST_TRUE(isnan(asin(2.0f)));
}

void unittests_math_scalar_asin_double()
{
    FND_TEST_TRUE(approx_equal(asin(0.0), 0.0));
    FND_TEST_TRUE(signbit(asin(-0.0)));
    FND_TEST_TRUE(approx_equal(asin(1.0), kDoublePi / 2));
    FND_TEST_TRUE(approx_equal(asin(-1.0), -kDoublePi / 2));
    FND_TEST_TRUE(isnan(asin(2.0)));
}

void unittests_math_scalar_atan_float()
{
    FND_TEST_TRUE(approx_equal(atan(0.0f), 0.0f));
    FND_TEST_TRUE(signbit(atan(-0.0f)));
    FND_TEST_TRUE(approx_equal(atan(1.0f), kFloatPi / 4));
    FND_TEST_TRUE(approx_equal(atan(INFINITY), kFloatPi / 2));
    FND_TEST_TRUE(approx_equal(atan(-INFINITY), -kFloatPi / 2));
}

void unittests_math_scalar_atan_double()
{
    FND_TEST_TRUE(approx_equal(atan(0.0), 0.0));
    FND_TEST_TRUE(signbit(atan(-0.0)));
    FND_TEST_TRUE(approx_equal(atan(1.0), kDoublePi / 4));
    FND_TEST_TRUE(approx_equal(atan(double_t(INFINITY)), kDoublePi / 2));
    FND_TEST_TRUE(approx_equal(atan(-double_t(INFINITY)), -kDoublePi / 2));
}

void unittests_math_scalar_atan2_float()
{
    // One point per axis direction, and the sign of zero picks the side of
    // the branch cut along the negative x axis.
    FND_TEST_TRUE(approx_equal(atan2(0.0f, 1.0f), 0.0f));
    FND_TEST_TRUE(approx_equal(atan2(1.0f, 0.0f), kFloatPi / 2));
    FND_TEST_TRUE(approx_equal(atan2(-1.0f, 0.0f), -kFloatPi / 2));
    FND_TEST_TRUE(approx_equal(atan2(0.0f, -1.0f), kFloatPi));
    FND_TEST_TRUE(approx_equal(atan2(-0.0f, -1.0f), -kFloatPi));
    FND_TEST_TRUE(approx_equal(atan2(1.0f, 1.0f), kFloatPi / 4));
    FND_TEST_TRUE(isnan(atan2(NAN, 1.0f)));
}

void unittests_math_scalar_atan2_double()
{
    // One point per axis direction, and the sign of zero picks the side of
    // the branch cut along the negative x axis.
    FND_TEST_TRUE(approx_equal(atan2(0.0, 1.0), 0.0));
    FND_TEST_TRUE(approx_equal(atan2(1.0, 0.0), kDoublePi / 2));
    FND_TEST_TRUE(approx_equal(atan2(-1.0, 0.0), -kDoublePi / 2));
    FND_TEST_TRUE(approx_equal(atan2(0.0, -1.0), kDoublePi));
    FND_TEST_TRUE(approx_equal(atan2(-0.0, -1.0), -kDoublePi));
    FND_TEST_TRUE(approx_equal(atan2(1.0, 1.0), kDoublePi / 4));
    FND_TEST_TRUE(isnan(atan2(double_t(NAN), 1.0)));
}

void unittests_math_scalar_degrees_float()
{
    static_assert(degrees(0.0f) == 0.0f);
    FND_TEST_TRUE(degrees(kFloatPi) == 180.0f);
    FND_TEST_TRUE(degrees(-kFloatPi) == -180.0f);
    FND_TEST_TRUE(degrees(kFloatPi / 2) == 90.0f);
    FND_TEST_TRUE(degrees(kFloatPi * 2) == 360.0f);
    FND_TEST_TRUE(approx_equal(degrees(1.0f), 57.2957795130823209f));
    FND_TEST_TRUE(degrees(kFloatInfinity) == kFloatInfinity);
    FND_TEST_TRUE(isnan(degrees(kFloatNaN)));
}

void unittests_math_scalar_degrees_double()
{
    static_assert(degrees(0.0) == 0.0);
    FND_TEST_TRUE(degrees(kDoublePi) == 180.0);
    FND_TEST_TRUE(degrees(-kDoublePi) == -180.0);
    FND_TEST_TRUE(degrees(kDoublePi / 2) == 90.0);
    FND_TEST_TRUE(degrees(kDoublePi * 2) == 360.0);
    FND_TEST_TRUE(approx_equal(degrees(1.0), 57.2957795130823209));
    FND_TEST_TRUE(degrees(kDoubleInfinity) == kDoubleInfinity);
    FND_TEST_TRUE(isnan(degrees(kDoubleNaN)));
}

void unittests_math_scalar_radians_float()
{
    static_assert(radians(0.0f) == 0.0f);
    FND_TEST_TRUE(radians(180.0f) == kFloatPi);
    FND_TEST_TRUE(radians(-180.0f) == -kFloatPi);
    FND_TEST_TRUE(radians(90.0f) == kFloatPi / 2);
    FND_TEST_TRUE(radians(360.0f) == kFloatPi * 2);
    FND_TEST_TRUE(approx_equal(radians(1.0f), 0.0174532925199432958f));
    FND_TEST_TRUE(approx_equal(radians(degrees(1.0f)), 1.0f));
    FND_TEST_TRUE(radians(kFloatInfinity) == kFloatInfinity);
    FND_TEST_TRUE(isnan(radians(kFloatNaN)));
}

void unittests_math_scalar_radians_double()
{
    static_assert(radians(0.0) == 0.0);
    FND_TEST_TRUE(radians(180.0) == kDoublePi);
    FND_TEST_TRUE(radians(-180.0) == -kDoublePi);
    FND_TEST_TRUE(radians(90.0) == kDoublePi / 2);
    FND_TEST_TRUE(radians(360.0) == kDoublePi * 2);
    FND_TEST_TRUE(approx_equal(radians(1.0), 0.0174532925199432958));
    FND_TEST_TRUE(approx_equal(radians(degrees(1.0)), 1.0));
    FND_TEST_TRUE(radians(kDoubleInfinity) == kDoubleInfinity);
    FND_TEST_TRUE(isnan(radians(kDoubleNaN)));
}

void unittests_math_scalar_cos_float()
{
    FND_TEST_TRUE(approx_equal(cos(0.0f), 1.0f));
    FND_TEST_TRUE(approx_equal(cos(kFloatPi), -1.0f));
    FND_TEST_TRUE(isnan(cos(INFINITY)));
}

void unittests_math_scalar_cos_double()
{
    FND_TEST_TRUE(approx_equal(cos(0.0), 1.0));
    FND_TEST_TRUE(approx_equal(cos(kDoublePi), -1.0));
    FND_TEST_TRUE(isnan(cos(double_t(INFINITY))));
}

void unittests_math_scalar_sin_float()
{
    FND_TEST_TRUE(approx_equal(sin(0.0f), 0.0f));
    FND_TEST_TRUE(signbit(sin(-0.0f)));
    FND_TEST_TRUE(approx_equal(sin(kFloatPi / 2), 1.0f));
    FND_TEST_TRUE(approx_equal(sin(-kFloatPi / 2), -1.0f));
    FND_TEST_TRUE(isnan(sin(INFINITY)));
}

void unittests_math_scalar_sin_double()
{
    FND_TEST_TRUE(approx_equal(sin(0.0), 0.0));
    FND_TEST_TRUE(signbit(sin(-0.0)));
    FND_TEST_TRUE(approx_equal(sin(kDoublePi / 2), 1.0));
    FND_TEST_TRUE(approx_equal(sin(-kDoublePi / 2), -1.0));
    FND_TEST_TRUE(isnan(sin(double_t(INFINITY))));
}

void unittests_math_scalar_tan_float()
{
    FND_TEST_TRUE(approx_equal(tan(0.0f), 0.0f));
    FND_TEST_TRUE(signbit(tan(-0.0f)));
    FND_TEST_TRUE(approx_equal(tan(kFloatPi / 4), 1.0f));
    FND_TEST_TRUE(isnan(tan(INFINITY)));
}

void unittests_math_scalar_tan_double()
{
    FND_TEST_TRUE(approx_equal(tan(0.0), 0.0));
    FND_TEST_TRUE(signbit(tan(-0.0)));
    FND_TEST_TRUE(approx_equal(tan(kDoublePi / 4), 1.0));
    FND_TEST_TRUE(isnan(tan(double_t(INFINITY))));
}

// ---------------------------------------------------------------------------
// Interpolation
// ---------------------------------------------------------------------------

void unittests_math_scalar_saturate_float()
{
    FND_TEST_TRUE(saturate(-1.0f) == 0.0f);
    FND_TEST_TRUE(saturate(0.0f) == 0.0f);
    FND_TEST_TRUE(saturate(0.25f) == 0.25f);
    FND_TEST_TRUE(saturate(1.0f) == 1.0f);
    FND_TEST_TRUE(saturate(2.0f) == 1.0f);
    FND_TEST_TRUE(saturate(kFloatInfinity) == 1.0f);
    FND_TEST_TRUE(saturate(-kFloatInfinity) == 0.0f);
}

void unittests_math_scalar_saturate_double()
{
    FND_TEST_TRUE(saturate(-1.0) == 0.0);
    FND_TEST_TRUE(saturate(0.0) == 0.0);
    FND_TEST_TRUE(saturate(0.25) == 0.25);
    FND_TEST_TRUE(saturate(1.0) == 1.0);
    FND_TEST_TRUE(saturate(2.0) == 1.0);
    FND_TEST_TRUE(saturate(kDoubleInfinity) == 1.0);
    FND_TEST_TRUE(saturate(-kDoubleInfinity) == 0.0);
}

void unittests_math_scalar_lerp_float()
{
    FND_TEST_TRUE(lerp(0.0f, 10.0f, 0.0f) == 0.0f);
    FND_TEST_TRUE(lerp(0.0f, 10.0f, 1.0f) == 10.0f);
    FND_TEST_TRUE(lerp(0.0f, 10.0f, 0.5f) == 5.0f);
    FND_TEST_TRUE(lerp(2.0f, 4.0f, 0.25f) == 2.5f);
    FND_TEST_TRUE(lerp(10.0f, 0.0f, 0.25f) == 7.5f);
    FND_TEST_TRUE(lerp(3.0f, 3.0f, 0.75f) == 3.0f);
    // t outside [0, 1] extrapolates.
    FND_TEST_TRUE(lerp(0.0f, 10.0f, 2.0f) == 20.0f);
    FND_TEST_TRUE(lerp(0.0f, 10.0f, -1.0f) == -10.0f);
}

void unittests_math_scalar_lerp_double()
{
    FND_TEST_TRUE(lerp(0.0, 10.0, 0.0) == 0.0);
    FND_TEST_TRUE(lerp(0.0, 10.0, 1.0) == 10.0);
    FND_TEST_TRUE(lerp(0.0, 10.0, 0.5) == 5.0);
    FND_TEST_TRUE(lerp(2.0, 4.0, 0.25) == 2.5);
    FND_TEST_TRUE(lerp(10.0, 0.0, 0.25) == 7.5);
    FND_TEST_TRUE(lerp(3.0, 3.0, 0.75) == 3.0);
    // t outside [0, 1] extrapolates.
    FND_TEST_TRUE(lerp(0.0, 10.0, 2.0) == 20.0);
    FND_TEST_TRUE(lerp(0.0, 10.0, -1.0) == -10.0);
}

void unittests_math_scalar_smoothstep_float()
{
    FND_TEST_TRUE(smoothstep(0.0f, 1.0f, -1.0f) == 0.0f);
    FND_TEST_TRUE(smoothstep(0.0f, 1.0f, 0.0f) == 0.0f);
    FND_TEST_TRUE(smoothstep(0.0f, 1.0f, 0.25f) == 0.15625f);
    FND_TEST_TRUE(smoothstep(0.0f, 1.0f, 0.5f) == 0.5f);
    FND_TEST_TRUE(smoothstep(0.0f, 1.0f, 0.75f) == 0.84375f);
    FND_TEST_TRUE(smoothstep(0.0f, 1.0f, 1.0f) == 1.0f);
    FND_TEST_TRUE(smoothstep(0.0f, 1.0f, 2.0f) == 1.0f);
    FND_TEST_TRUE(smoothstep(2.0f, 4.0f, 3.0f) == 0.5f);
    // edge0 > edge1 reverses the curve.
    FND_TEST_TRUE(smoothstep(1.0f, 0.0f, 0.25f) == 0.84375f);
    FND_TEST_TRUE(smoothstep(1.0f, 0.0f, 2.0f) == 0.0f);
}

void unittests_math_scalar_smoothstep_double()
{
    FND_TEST_TRUE(smoothstep(0.0, 1.0, -1.0) == 0.0);
    FND_TEST_TRUE(smoothstep(0.0, 1.0, 0.0) == 0.0);
    FND_TEST_TRUE(smoothstep(0.0, 1.0, 0.25) == 0.15625);
    FND_TEST_TRUE(smoothstep(0.0, 1.0, 0.5) == 0.5);
    FND_TEST_TRUE(smoothstep(0.0, 1.0, 0.75) == 0.84375);
    FND_TEST_TRUE(smoothstep(0.0, 1.0, 1.0) == 1.0);
    FND_TEST_TRUE(smoothstep(0.0, 1.0, 2.0) == 1.0);
    FND_TEST_TRUE(smoothstep(2.0, 4.0, 3.0) == 0.5);
    // edge0 > edge1 reverses the curve.
    FND_TEST_TRUE(smoothstep(1.0, 0.0, 0.25) == 0.84375);
    FND_TEST_TRUE(smoothstep(1.0, 0.0, 2.0) == 0.0);
}

// ---------------------------------------------------------------------------
// Power and roots
// ---------------------------------------------------------------------------

void unittests_math_scalar_pow_float()
{
    FND_TEST_TRUE(approx_equal(pow(2.0f, 10.0f), 1024.0f));
    FND_TEST_TRUE(approx_equal(pow(2.0f, -1.0f), 0.5f));
    FND_TEST_TRUE(approx_equal(pow(9.0f, 0.5f), 3.0f));
    FND_TEST_TRUE(approx_equal(pow(-2.0f, 3.0f), -8.0f));
    FND_TEST_TRUE(pow(0.0f, 2.0f) == 0.0f);
    FND_TEST_TRUE(pow(0.0f, -1.0f) == kFloatInfinity);
    // Anything to the power 0 is 1, and 1 to any power is 1, even with NaN.
    FND_TEST_TRUE(pow(kFloatNaN, 0.0f) == 1.0f);
    FND_TEST_TRUE(pow(1.0f, kFloatNaN) == 1.0f);
}

void unittests_math_scalar_pow_double()
{
    FND_TEST_TRUE(approx_equal(pow(2.0, 10.0), 1024.0));
    FND_TEST_TRUE(approx_equal(pow(2.0, -1.0), 0.5));
    FND_TEST_TRUE(approx_equal(pow(9.0, 0.5), 3.0));
    FND_TEST_TRUE(approx_equal(pow(-2.0, 3.0), -8.0));
    FND_TEST_TRUE(pow(0.0, 2.0) == 0.0);
    FND_TEST_TRUE(pow(0.0, -1.0) == kDoubleInfinity);
    // Anything to the power 0 is 1, and 1 to any power is 1, even with NaN.
    FND_TEST_TRUE(pow(kDoubleNaN, 0.0) == 1.0);
    FND_TEST_TRUE(pow(1.0, kDoubleNaN) == 1.0);
}

void unittests_math_scalar_rcp_float()
{
    FND_TEST_TRUE(rcp(1.0f) == 1.0f);
    FND_TEST_TRUE(rcp(2.0f) == 0.5f);
    FND_TEST_TRUE(rcp(-4.0f) == -0.25f);
    FND_TEST_TRUE(rcp(kFloatInfinity) == 0.0f);
}

void unittests_math_scalar_rcp_double()
{
    FND_TEST_TRUE(rcp(1.0) == 1.0);
    FND_TEST_TRUE(rcp(2.0) == 0.5);
    FND_TEST_TRUE(rcp(-4.0) == -0.25);
    FND_TEST_TRUE(rcp(kDoubleInfinity) == 0.0);
}

void unittests_math_scalar_sqrt_float()
{
    FND_TEST_TRUE(sqrt(0.0f) == 0.0f);
    FND_TEST_TRUE(sqrt(1.0f) == 1.0f);
    FND_TEST_TRUE(sqrt(4.0f) == 2.0f);
    FND_TEST_TRUE(sqrt(0.25f) == 0.5f);
    FND_TEST_TRUE(approx_equal(sqrt(2.0f), 1.41421356237309505f));
    FND_TEST_TRUE(sqrt(kFloatInfinity) == kFloatInfinity);
}

void unittests_math_scalar_sqrt_double()
{
    FND_TEST_TRUE(sqrt(0.0) == 0.0);
    FND_TEST_TRUE(sqrt(1.0) == 1.0);
    FND_TEST_TRUE(sqrt(4.0) == 2.0);
    FND_TEST_TRUE(sqrt(0.25) == 0.5);
    FND_TEST_TRUE(approx_equal(sqrt(2.0), 1.41421356237309505));
    FND_TEST_TRUE(sqrt(kDoubleInfinity) == kDoubleInfinity);
}

void unittests_math_scalar_rsqrt_float()
{
    FND_TEST_TRUE(rsqrt(1.0f) == 1.0f);
    FND_TEST_TRUE(rsqrt(4.0f) == 0.5f);
    FND_TEST_TRUE(rsqrt(0.25f) == 2.0f);
    FND_TEST_TRUE(approx_equal(rsqrt(2.0f), 0.70710678118654752f));
    FND_TEST_TRUE(rsqrt(kFloatInfinity) == 0.0f);
}

void unittests_math_scalar_rsqrt_double()
{
    FND_TEST_TRUE(rsqrt(1.0) == 1.0);
    FND_TEST_TRUE(rsqrt(4.0) == 0.5);
    FND_TEST_TRUE(rsqrt(0.25) == 2.0);
    FND_TEST_TRUE(approx_equal(rsqrt(2.0), 0.70710678118654752));
    FND_TEST_TRUE(rsqrt(kDoubleInfinity) == 0.0);
}

// ---------------------------------------------------------------------------
// Exponential and logarithm
// ---------------------------------------------------------------------------

void unittests_math_scalar_exp_float()
{
    FND_TEST_TRUE(exp(0.0f) == 1.0f);
    FND_TEST_TRUE(approx_equal(exp(1.0f), 2.71828182845904524f));
    FND_TEST_TRUE(approx_equal(exp(-1.0f), 0.36787944117144233f));
    FND_TEST_TRUE(exp(kFloatInfinity) == kFloatInfinity);
    FND_TEST_TRUE(exp(-kFloatInfinity) == 0.0f);
    FND_TEST_TRUE(isnan(exp(kFloatNaN)));
}

void unittests_math_scalar_exp_double()
{
    FND_TEST_TRUE(exp(0.0) == 1.0);
    FND_TEST_TRUE(approx_equal(exp(1.0), 2.71828182845904524));
    FND_TEST_TRUE(approx_equal(exp(-1.0), 0.36787944117144233));
    FND_TEST_TRUE(exp(kDoubleInfinity) == kDoubleInfinity);
    FND_TEST_TRUE(exp(-kDoubleInfinity) == 0.0);
    FND_TEST_TRUE(isnan(exp(kDoubleNaN)));
}

void unittests_math_scalar_exp2_float()
{
    FND_TEST_TRUE(exp2(0.0f) == 1.0f);
    FND_TEST_TRUE(approx_equal(exp2(1.0f), 2.0f));
    FND_TEST_TRUE(approx_equal(exp2(10.0f), 1024.0f));
    FND_TEST_TRUE(approx_equal(exp2(-1.0f), 0.5f));
    FND_TEST_TRUE(approx_equal(exp2(0.5f), 1.41421356237309505f));
    FND_TEST_TRUE(exp2(kFloatInfinity) == kFloatInfinity);
    FND_TEST_TRUE(exp2(-kFloatInfinity) == 0.0f);
    FND_TEST_TRUE(isnan(exp2(kFloatNaN)));
}

void unittests_math_scalar_exp2_double()
{
    FND_TEST_TRUE(exp2(0.0) == 1.0);
    FND_TEST_TRUE(approx_equal(exp2(1.0), 2.0));
    FND_TEST_TRUE(approx_equal(exp2(10.0), 1024.0));
    FND_TEST_TRUE(approx_equal(exp2(-1.0), 0.5));
    FND_TEST_TRUE(approx_equal(exp2(0.5), 1.41421356237309505));
    FND_TEST_TRUE(exp2(kDoubleInfinity) == kDoubleInfinity);
    FND_TEST_TRUE(exp2(-kDoubleInfinity) == 0.0);
    FND_TEST_TRUE(isnan(exp2(kDoubleNaN)));
}

void unittests_math_scalar_log_float()
{
    FND_TEST_TRUE(log(1.0f) == 0.0f);
    FND_TEST_TRUE(approx_equal(log(2.71828182845904524f), 1.0f));
    FND_TEST_TRUE(approx_equal(log(2.0f), 0.69314718055994531f));
    FND_TEST_TRUE(log(kFloatInfinity) == kFloatInfinity);
}

void unittests_math_scalar_log_double()
{
    FND_TEST_TRUE(log(1.0) == 0.0);
    FND_TEST_TRUE(approx_equal(log(2.71828182845904524), 1.0));
    FND_TEST_TRUE(approx_equal(log(2.0), 0.69314718055994531));
    FND_TEST_TRUE(log(kDoubleInfinity) == kDoubleInfinity);
}

void unittests_math_scalar_log2_float()
{
    FND_TEST_TRUE(log2(1.0f) == 0.0f);
    FND_TEST_TRUE(approx_equal(log2(2.0f), 1.0f));
    FND_TEST_TRUE(approx_equal(log2(1024.0f), 10.0f));
    FND_TEST_TRUE(approx_equal(log2(0.5f), -1.0f));
    FND_TEST_TRUE(log2(kFloatInfinity) == kFloatInfinity);
}

void unittests_math_scalar_log2_double()
{
    FND_TEST_TRUE(log2(1.0) == 0.0);
    FND_TEST_TRUE(approx_equal(log2(2.0), 1.0));
    FND_TEST_TRUE(approx_equal(log2(1024.0), 10.0));
    FND_TEST_TRUE(approx_equal(log2(0.5), -1.0));
    FND_TEST_TRUE(log2(kDoubleInfinity) == kDoubleInfinity);
}

void unittests_math_scalar_log10_float()
{
    FND_TEST_TRUE(log10(1.0f) == 0.0f);
    FND_TEST_TRUE(approx_equal(log10(10.0f), 1.0f));
    FND_TEST_TRUE(approx_equal(log10(1000.0f), 3.0f));
    FND_TEST_TRUE(approx_equal(log10(0.01f), -2.0f));
    FND_TEST_TRUE(log10(kFloatInfinity) == kFloatInfinity);
}

void unittests_math_scalar_log10_double()
{
    FND_TEST_TRUE(log10(1.0) == 0.0);
    FND_TEST_TRUE(approx_equal(log10(10.0), 1.0));
    FND_TEST_TRUE(approx_equal(log10(1000.0), 3.0));
    FND_TEST_TRUE(approx_equal(log10(0.01), -2.0));
    FND_TEST_TRUE(log10(kDoubleInfinity) == kDoubleInfinity);
}

// ---------------------------------------------------------------------------
// frac
// ---------------------------------------------------------------------------

void unittests_math_scalar_fractional_float()
{
    FND_TEST_TRUE(fractional(0.0f) == 0.0f);
    FND_TEST_TRUE(fractional(1.25f) == 0.25f);
    FND_TEST_TRUE(fractional(2.0f) == 0.0f);
    FND_TEST_TRUE(fractional(0.5f) == 0.5f);
    // Negative x gives the fractional part of |x|.
    FND_TEST_TRUE(fractional(-1.25f) == 0.25f);
    FND_TEST_TRUE(fractional(-0.5f) == 0.5f);
    FND_TEST_TRUE(fractional(-2.0f) == 0.0f);
    // Exact even for tiny values.
    FND_TEST_TRUE(fractional(kFloatMinSubnormal) == kFloatMinSubnormal);
    FND_TEST_TRUE(fractional(-kFloatMinSubnormal) == kFloatMinSubnormal);
    FND_TEST_TRUE(fractional(-1e-10f) == 1e-10f);
    FND_TEST_TRUE(fractional(kFloatMaxValue) == 0.0f);
    FND_TEST_TRUE(fractional(kFloatInfinity) == 0.0f);
    FND_TEST_TRUE(fractional(-kFloatInfinity) == 0.0f);
    FND_TEST_TRUE(isnan(fractional(kFloatNaN)));
}

void unittests_math_scalar_fractional_double()
{
    FND_TEST_TRUE(fractional(0.0) == 0.0);
    FND_TEST_TRUE(fractional(1.25) == 0.25);
    FND_TEST_TRUE(fractional(2.0) == 0.0);
    FND_TEST_TRUE(fractional(0.5) == 0.5);
    // Negative x gives the fractional part of |x|.
    FND_TEST_TRUE(fractional(-1.25) == 0.25);
    FND_TEST_TRUE(fractional(-0.5) == 0.5);
    FND_TEST_TRUE(fractional(-2.0) == 0.0);
    // Exact even for tiny values.
    FND_TEST_TRUE(fractional(kDoubleMinSubnormal) == kDoubleMinSubnormal);
    FND_TEST_TRUE(fractional(-kDoubleMinSubnormal) == kDoubleMinSubnormal);
    FND_TEST_TRUE(fractional(-1e-10) == 1e-10);
    FND_TEST_TRUE(fractional(kDoubleMaxValue) == 0.0);
    FND_TEST_TRUE(fractional(kDoubleInfinity) == 0.0);
    FND_TEST_TRUE(fractional(-kDoubleInfinity) == 0.0);
    FND_TEST_TRUE(isnan(fractional(kDoubleNaN)));
}

void unittests_math_scalar()
{
    unittests_math_scalar_abs_integer_types();
    unittests_math_scalar_abs_float_types();

    unittests_math_scalar_approx_equal_float();
    unittests_math_scalar_approx_equal_double();

    unittests_math_scalar_acos_float();
    unittests_math_scalar_acos_double();
    unittests_math_scalar_asin_float();
    unittests_math_scalar_asin_double();
    unittests_math_scalar_atan_float();
    unittests_math_scalar_atan_double();
    unittests_math_scalar_atan2_float();
    unittests_math_scalar_atan2_double();
    unittests_math_scalar_degrees_float();
    unittests_math_scalar_degrees_double();
    unittests_math_scalar_radians_float();
    unittests_math_scalar_radians_double();
    unittests_math_scalar_cos_float();
    unittests_math_scalar_cos_double();
    unittests_math_scalar_sin_float();
    unittests_math_scalar_sin_double();
    unittests_math_scalar_tan_float();
    unittests_math_scalar_tan_double();

    unittests_math_scalar_saturate_float();
    unittests_math_scalar_saturate_double();
    unittests_math_scalar_lerp_float();
    unittests_math_scalar_lerp_double();
    unittests_math_scalar_smoothstep_float();
    unittests_math_scalar_smoothstep_double();
    unittests_math_scalar_pow_float();
    unittests_math_scalar_pow_double();
    unittests_math_scalar_rcp_float();
    unittests_math_scalar_rcp_double();
    unittests_math_scalar_sqrt_float();
    unittests_math_scalar_sqrt_double();
    unittests_math_scalar_rsqrt_float();
    unittests_math_scalar_rsqrt_double();
    unittests_math_scalar_exp_float();
    unittests_math_scalar_exp_double();
    unittests_math_scalar_exp2_float();
    unittests_math_scalar_exp2_double();
    unittests_math_scalar_log_float();
    unittests_math_scalar_log_double();
    unittests_math_scalar_log2_float();
    unittests_math_scalar_log2_double();
    unittests_math_scalar_log10_float();
    unittests_math_scalar_log10_double();
    unittests_math_scalar_fractional_float();
    unittests_math_scalar_fractional_double();
}

} // namespace fnd::unittests
