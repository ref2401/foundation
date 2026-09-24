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
    unittests_math_scalar_cos_float();
    unittests_math_scalar_cos_double();
    unittests_math_scalar_sin_float();
    unittests_math_scalar_sin_double();
    unittests_math_scalar_tan_float();
    unittests_math_scalar_tan_double();
}

} // namespace fnd::unittests
