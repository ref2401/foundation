module;
#include "foundation/unittests.h"


export module unittests.math:scalar;
import foundation.math;

namespace fnd::unittests {

export void unittests_math_scalar();

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
    FND_TEST_TRUE(approx_equal(asin(1.0f), kFloatPi / 2));
    FND_TEST_TRUE(approx_equal(asin(-1.0f), -kFloatPi / 2));
    FND_TEST_TRUE(isnan(asin(2.0f)));
}

void unittests_math_scalar_asin_double()
{
    FND_TEST_TRUE(approx_equal(asin(0.0), 0.0));
    FND_TEST_TRUE(approx_equal(asin(1.0), kDoublePi / 2));
    FND_TEST_TRUE(approx_equal(asin(-1.0), -kDoublePi / 2));
    FND_TEST_TRUE(isnan(asin(2.0)));
}

void unittests_math_scalar_atan_float()
{
    FND_TEST_TRUE(approx_equal(atan(0.0f), 0.0f));
    FND_TEST_TRUE(approx_equal(atan(1.0f), kFloatPi / 4));
    FND_TEST_TRUE(approx_equal(atan(kFloatInfinity), kFloatPi / 2));
    FND_TEST_TRUE(approx_equal(atan(-kFloatInfinity), -kFloatPi / 2));
}

void unittests_math_scalar_atan_double()
{
    FND_TEST_TRUE(approx_equal(atan(0.0), 0.0));
    FND_TEST_TRUE(approx_equal(atan(1.0), kDoublePi / 4));
    FND_TEST_TRUE(approx_equal(atan(kDoubleInfinity), kDoublePi / 2));
    FND_TEST_TRUE(approx_equal(atan(-kDoubleInfinity), -kDoublePi / 2));
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
    FND_TEST_TRUE(isnan(atan2(kFloatNaN, 1.0f)));
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
    FND_TEST_TRUE(isnan(atan2(kDoubleNaN, 1.0)));
}

void unittests_math_scalar_cos_float()
{
    FND_TEST_TRUE(approx_equal(cos(0.0f), 1.0f));
    FND_TEST_TRUE(approx_equal(cos(kFloatPi), -1.0f));
    FND_TEST_TRUE(isnan(cos(kFloatInfinity)));
}

void unittests_math_scalar_cos_double()
{
    FND_TEST_TRUE(approx_equal(cos(0.0), 1.0));
    FND_TEST_TRUE(approx_equal(cos(kDoublePi), -1.0));
    FND_TEST_TRUE(isnan(cos(kDoubleInfinity)));
}

void unittests_math_scalar_degrees_float()
{
    FND_TEST_TRUE(degrees(0.0f) == 0.0f);
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
    FND_TEST_TRUE(degrees(0.0) == 0.0);
    FND_TEST_TRUE(degrees(kDoublePi) == 180.0);
    FND_TEST_TRUE(degrees(-kDoublePi) == -180.0);
    FND_TEST_TRUE(degrees(kDoublePi / 2) == 90.0);
    FND_TEST_TRUE(degrees(kDoublePi * 2) == 360.0);
    FND_TEST_TRUE(approx_equal(degrees(1.0), 57.2957795130823209));
    FND_TEST_TRUE(degrees(kDoubleInfinity) == kDoubleInfinity);
    FND_TEST_TRUE(isnan(degrees(kDoubleNaN)));
}

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

void unittests_math_scalar_is_pow2_int()
{
    // Every single bit that keeps the value positive: 2^0 to 2^30.
    for (int_t k = 0; k < 31; ++k) {
        FND_TEST_TRUE(is_pow2(int_t{1} << k));
    }
    // Next to a power of two.
    for (int_t k = 2; k < 31; ++k) {
        FND_TEST_FALSE(is_pow2((int_t{1} << k) - 1));
        FND_TEST_FALSE(is_pow2((int_t{1} << k) + 1));
    }
    FND_TEST_FALSE(is_pow2(0));
    FND_TEST_FALSE(is_pow2(6));
    FND_TEST_FALSE(is_pow2(kIntMaxValue));
    // Negative numbers, also -2^31 with its single bit set.
    FND_TEST_FALSE(is_pow2(-1));
    FND_TEST_FALSE(is_pow2(-2));
    FND_TEST_FALSE(is_pow2(-1024));
    FND_TEST_FALSE(is_pow2(kIntMinValue));

    // Usable in constant expressions.
    static_assert(is_pow2(64));
}

void unittests_math_scalar_is_pow2_uint()
{
    // Every single bit: 2^0 to 2^31.
    for (uint_t k = 0; k < 32; ++k) {
        FND_TEST_TRUE(is_pow2(uint_t{1} << k));
    }
    for (uint_t k = 2; k < 32; ++k) {
        FND_TEST_FALSE(is_pow2((uint_t{1} << k) - 1));
        FND_TEST_FALSE(is_pow2((uint_t{1} << k) + 1));
    }
    FND_TEST_FALSE(is_pow2(0u));
    FND_TEST_FALSE(is_pow2(6u));
    FND_TEST_FALSE(is_pow2(kUIntMaxValue));

    static_assert(is_pow2(64u));
}

void unittests_math_scalar_is_pow2_long()
{
    // Every single bit that keeps the value positive: 2^0 to 2^62.
    for (long_t k = 0; k < 63; ++k) {
        FND_TEST_TRUE(is_pow2(long_t{1} << k));
    }
    for (long_t k = 2; k < 63; ++k) {
        FND_TEST_FALSE(is_pow2((long_t{1} << k) - 1));
        FND_TEST_FALSE(is_pow2((long_t{1} << k) + 1));
    }
    FND_TEST_FALSE(is_pow2(long_t{0}));
    FND_TEST_FALSE(is_pow2(long_t{6}));
    FND_TEST_FALSE(is_pow2(kLongMaxValue));
    // Negative numbers, also -2^63 with its single bit set.
    FND_TEST_FALSE(is_pow2(long_t{-1}));
    FND_TEST_FALSE(is_pow2(long_t{-1024}));
    FND_TEST_FALSE(is_pow2(kLongMinValue));

    static_assert(is_pow2(long_t{1} << 40));
}

void unittests_math_scalar_is_pow2_ulong()
{
    // Every single bit: 2^0 to 2^63.
    for (ulong_t k = 0; k < 64; ++k) {
        FND_TEST_TRUE(is_pow2(ulong_t{1} << k));
    }
    for (ulong_t k = 2; k < 64; ++k) {
        FND_TEST_FALSE(is_pow2((ulong_t{1} << k) - 1));
        FND_TEST_FALSE(is_pow2((ulong_t{1} << k) + 1));
    }
    FND_TEST_FALSE(is_pow2(ulong_t{0}));
    FND_TEST_FALSE(is_pow2(ulong_t{6}));
    FND_TEST_FALSE(is_pow2(kULongMaxValue));

    static_assert(is_pow2(ulong_t{1} << 63));
}

void unittests_math_scalar_is_pow2_float()
{
    // Every power of two, by exact doubling and halving: 1 up to 2^127, and
    // down through the normals into the subnormals, to 2^-149.
    float_t up = 1;
    for (int_t k = 0; k <= 127; ++k, up *= 2) {
        FND_TEST_TRUE(is_pow2(up));
    }
    float_t down = 1;
    for (int_t k = 0; k <= 149; ++k, down *= 0.5f) {
        FND_TEST_TRUE(is_pow2(down));
    }
    FND_TEST_TRUE(is_pow2(kFloatMinNormal));
    FND_TEST_TRUE(is_pow2(kFloatMinSubnormal));
    FND_TEST_TRUE(is_pow2(kFloatEpsilon));

    // 1.5 times a power of two is exact for the normals and is not one.
    float_t x = kFloatMinNormal;
    for (int_t k = -126; k < 127; ++k, x *= 2) {
        FND_TEST_FALSE(is_pow2(1.5f * x));
    }
    FND_TEST_FALSE(is_pow2(3.0f));
    FND_TEST_FALSE(is_pow2(0.75f));
    FND_TEST_FALSE(is_pow2(1.0f + kFloatEpsilon));
    FND_TEST_FALSE(is_pow2(kFloatMaxValue));
    FND_TEST_FALSE(is_pow2(3 * kFloatMinSubnormal));

    // Zero, negative numbers, infinity and NaN.
    FND_TEST_FALSE(is_pow2(0.0f));
    FND_TEST_FALSE(is_pow2(-0.0f));
    FND_TEST_FALSE(is_pow2(-1.0f));
    FND_TEST_FALSE(is_pow2(-0.5f));
    FND_TEST_FALSE(is_pow2(kFloatInfinity));
    FND_TEST_FALSE(is_pow2(-kFloatInfinity));
    FND_TEST_FALSE(is_pow2(kFloatNaN));
}

void unittests_math_scalar_is_pow2_double()
{
    // Every power of two, by exact doubling and halving: 1 up to 2^1023, and
    // down through the normals into the subnormals, to 2^-1074.
    double_t up = 1;
    for (int_t k = 0; k <= 1023; ++k, up *= 2) {
        FND_TEST_TRUE(is_pow2(up));
    }
    double_t down = 1;
    for (int_t k = 0; k <= 1074; ++k, down *= 0.5) {
        FND_TEST_TRUE(is_pow2(down));
    }
    FND_TEST_TRUE(is_pow2(kDoubleMinNormal));
    FND_TEST_TRUE(is_pow2(kDoubleMinSubnormal));
    FND_TEST_TRUE(is_pow2(kDoubleEpsilon));

    // 1.5 times a power of two is exact for the normals and is not one.
    double_t x = kDoubleMinNormal;
    for (int_t k = -1022; k < 1023; ++k, x *= 2) {
        FND_TEST_FALSE(is_pow2(1.5 * x));
    }
    FND_TEST_FALSE(is_pow2(3.0));
    FND_TEST_FALSE(is_pow2(0.75));
    FND_TEST_FALSE(is_pow2(1.0 + kDoubleEpsilon));
    FND_TEST_FALSE(is_pow2(kDoubleMaxValue));
    FND_TEST_FALSE(is_pow2(3 * kDoubleMinSubnormal));

    // Zero, negative numbers, infinity and NaN.
    FND_TEST_FALSE(is_pow2(0.0));
    FND_TEST_FALSE(is_pow2(-0.0));
    FND_TEST_FALSE(is_pow2(-1.0));
    FND_TEST_FALSE(is_pow2(-0.5));
    FND_TEST_FALSE(is_pow2(kDoubleInfinity));
    FND_TEST_FALSE(is_pow2(-kDoubleInfinity));
    FND_TEST_FALSE(is_pow2(kDoubleNaN));
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

void unittests_math_scalar_pow_float()
{
    FND_TEST_TRUE(approx_equal(pow(2.0f, 10.0f), 1024.0f));
    FND_TEST_TRUE(approx_equal(pow(2.0f, -1.0f), 0.5f));
    FND_TEST_TRUE(approx_equal(pow(9.0f, 0.5f), 3.0f));
    FND_TEST_TRUE(approx_equal(pow(-2.0f, 3.0f), -8.0f));
    FND_TEST_TRUE(pow(0.0f, 2.0f) == 0.0f);
    FND_TEST_TRUE(pow(0.0f, -1.0f) == kFloatInfinity);
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
    FND_TEST_TRUE(pow(kDoubleNaN, 0.0) == 1.0);
    FND_TEST_TRUE(pow(1.0, kDoubleNaN) == 1.0);
}

void unittests_math_scalar_radians_float()
{
    FND_TEST_TRUE(radians(0.0f) == 0.0f);
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
    FND_TEST_TRUE(radians(0.0) == 0.0);
    FND_TEST_TRUE(radians(180.0) == kDoublePi);
    FND_TEST_TRUE(radians(-180.0) == -kDoublePi);
    FND_TEST_TRUE(radians(90.0) == kDoublePi / 2);
    FND_TEST_TRUE(radians(360.0) == kDoublePi * 2);
    FND_TEST_TRUE(approx_equal(radians(1.0), 0.0174532925199432958));
    FND_TEST_TRUE(approx_equal(radians(degrees(1.0)), 1.0));
    FND_TEST_TRUE(radians(kDoubleInfinity) == kDoubleInfinity);
    FND_TEST_TRUE(isnan(radians(kDoubleNaN)));
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

void unittests_math_scalar_sin_float()
{
    FND_TEST_TRUE(approx_equal(sin(0.0f), 0.0f));
    FND_TEST_TRUE(approx_equal(sin(kFloatPi / 2), 1.0f));
    FND_TEST_TRUE(approx_equal(sin(-kFloatPi / 2), -1.0f));
    FND_TEST_TRUE(isnan(sin(kFloatInfinity)));
}

void unittests_math_scalar_sin_double()
{
    FND_TEST_TRUE(approx_equal(sin(0.0), 0.0));
    FND_TEST_TRUE(approx_equal(sin(kDoublePi / 2), 1.0));
    FND_TEST_TRUE(approx_equal(sin(-kDoublePi / 2), -1.0));
    FND_TEST_TRUE(isnan(sin(kDoubleInfinity)));
}

void unittests_math_scalar_smoothstep_float()
{
    FND_TEST_TRUE(smoothstep(-1.0f, 0.0f, 1.0f) == 0.0f);
    FND_TEST_TRUE(smoothstep(0.0f, 0.0f, 1.0f) == 0.0f);
    FND_TEST_TRUE(smoothstep(0.25f, 0.0f, 1.0f) == 0.15625f);
    FND_TEST_TRUE(smoothstep(0.5f, 0.0f, 1.0f) == 0.5f);
    FND_TEST_TRUE(smoothstep(0.75f, 0.0f, 1.0f) == 0.84375f);
    FND_TEST_TRUE(smoothstep(1.0f, 0.0f, 1.0f) == 1.0f);
    FND_TEST_TRUE(smoothstep(2.0f, 0.0f, 1.0f) == 1.0f);
    FND_TEST_TRUE(smoothstep(3.0f, 2.0f, 4.0f) == 0.5f);
    // edge0 > edge1 reverses the curve.
    FND_TEST_TRUE(smoothstep(0.25f, 1.0f, 0.0f) == 0.84375f);
    FND_TEST_TRUE(smoothstep(2.0f, 1.0f, 0.0f) == 0.0f);
}

void unittests_math_scalar_smoothstep_double()
{
    FND_TEST_TRUE(smoothstep(-1.0, 0.0, 1.0) == 0.0);
    FND_TEST_TRUE(smoothstep(0.0, 0.0, 1.0) == 0.0);
    FND_TEST_TRUE(smoothstep(0.25, 0.0, 1.0) == 0.15625);
    FND_TEST_TRUE(smoothstep(0.5, 0.0, 1.0) == 0.5);
    FND_TEST_TRUE(smoothstep(0.75, 0.0, 1.0) == 0.84375);
    FND_TEST_TRUE(smoothstep(1.0, 0.0, 1.0) == 1.0);
    FND_TEST_TRUE(smoothstep(2.0, 0.0, 1.0) == 1.0);
    FND_TEST_TRUE(smoothstep(3.0, 2.0, 4.0) == 0.5);
    // edge0 > edge1 reverses the curve.
    FND_TEST_TRUE(smoothstep(0.25, 1.0, 0.0) == 0.84375);
    FND_TEST_TRUE(smoothstep(2.0, 1.0, 0.0) == 0.0);
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

void unittests_math_scalar_tan_float()
{
    FND_TEST_TRUE(approx_equal(tan(0.0f), 0.0f));
    FND_TEST_TRUE(approx_equal(tan(kFloatPi / 4), 1.0f));
    FND_TEST_TRUE(isnan(tan(kFloatInfinity)));
}

void unittests_math_scalar_tan_double()
{
    FND_TEST_TRUE(approx_equal(tan(0.0), 0.0));
    FND_TEST_TRUE(approx_equal(tan(kDoublePi / 4), 1.0));
    FND_TEST_TRUE(isnan(tan(kDoubleInfinity)));
}

void unittests_math_scalar()
{
    unittests_math_scalar_acos_float();
    unittests_math_scalar_acos_double();
    unittests_math_scalar_asin_float();
    unittests_math_scalar_asin_double();
    unittests_math_scalar_atan_float();
    unittests_math_scalar_atan_double();
    unittests_math_scalar_atan2_float();
    unittests_math_scalar_atan2_double();
    unittests_math_scalar_cos_float();
    unittests_math_scalar_cos_double();
    unittests_math_scalar_degrees_float();
    unittests_math_scalar_degrees_double();
    unittests_math_scalar_exp_float();
    unittests_math_scalar_exp_double();
    unittests_math_scalar_exp2_float();
    unittests_math_scalar_exp2_double();
    unittests_math_scalar_is_pow2_int();
    unittests_math_scalar_is_pow2_uint();
    unittests_math_scalar_is_pow2_long();
    unittests_math_scalar_is_pow2_ulong();
    unittests_math_scalar_is_pow2_float();
    unittests_math_scalar_is_pow2_double();
    unittests_math_scalar_lerp_float();
    unittests_math_scalar_lerp_double();
    unittests_math_scalar_log_float();
    unittests_math_scalar_log_double();
    unittests_math_scalar_log10_float();
    unittests_math_scalar_log10_double();
    unittests_math_scalar_log2_float();
    unittests_math_scalar_log2_double();
    unittests_math_scalar_pow_float();
    unittests_math_scalar_pow_double();
    unittests_math_scalar_radians_float();
    unittests_math_scalar_radians_double();
    unittests_math_scalar_rcp_float();
    unittests_math_scalar_rcp_double();
    unittests_math_scalar_rsqrt_float();
    unittests_math_scalar_rsqrt_double();
    unittests_math_scalar_sin_float();
    unittests_math_scalar_sin_double();
    unittests_math_scalar_smoothstep_float();
    unittests_math_scalar_smoothstep_double();
    unittests_math_scalar_sqrt_float();
    unittests_math_scalar_sqrt_double();
    unittests_math_scalar_tan_float();
    unittests_math_scalar_tan_double();
}

} // namespace fnd::unittests
