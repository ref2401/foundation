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
    // max_abs_param
    FND_TEST_TRUE(approx_equal(1.0f, 1.0f, 0.0f));
    FND_TEST_FALSE(approx_equal(1.0f, 1.00001f, 0.0f));
    FND_TEST_TRUE(approx_equal(1.0f, 1.001f, 1.0f));
    FND_TEST_TRUE(approx_equal(1.0f, 1.001f, 0.1f));
    FND_TEST_TRUE(approx_equal(1.0f, 1.001f, 0.01f));
    FND_TEST_FALSE(approx_equal(1.0f, 1.001f, 0.001f));
    FND_TEST_FALSE(approx_equal(1.0f, 1.001f, 0.0009f));
    FND_TEST_FALSE(approx_equal(1.0f, 1.001f, 0.0001f));
}

// ---------------------------------------------------------------------------
// Trigonometry
// ---------------------------------------------------------------------------

// The float_t/double_t nearest to pi. The tests compare with == only at points
// where the correctly rounded result is exactly 0, ±1 or kPi times a power of 2.
constexpr float_t kFloatPi{3.14159265358979323846f};
constexpr double_t kDoublePi{3.14159265358979323846};

void unittests_math_scalar_sin_cos_tan()
{
    // float_t
    FND_TEST_TRUE(sin(0.0f) == 0.0f);
    FND_TEST_TRUE(signbit(sin(-0.0f)));
    FND_TEST_TRUE(sin(kFloatPi / 2) == 1.0f);
    FND_TEST_TRUE(sin(-kFloatPi / 2) == -1.0f);
    FND_TEST_TRUE(cos(0.0f) == 1.0f);
    FND_TEST_TRUE(cos(kFloatPi) == -1.0f);
    FND_TEST_TRUE(tan(0.0f) == 0.0f);
    FND_TEST_TRUE(signbit(tan(-0.0f)));
    FND_TEST_TRUE(tan(kFloatPi / 4) == 1.0f);
    FND_TEST_TRUE(isnan(sin(INFINITY)));
    FND_TEST_TRUE(isnan(cos(INFINITY)));
    FND_TEST_TRUE(isnan(tan(INFINITY)));
    // double_t
    FND_TEST_TRUE(sin(0.0) == 0.0);
    FND_TEST_TRUE(signbit(sin(-0.0)));
    FND_TEST_TRUE(sin(kDoublePi / 2) == 1.0);
    FND_TEST_TRUE(sin(-kDoublePi / 2) == -1.0);
    FND_TEST_TRUE(cos(0.0) == 1.0);
    FND_TEST_TRUE(cos(kDoublePi) == -1.0);
    FND_TEST_TRUE(tan(0.0) == 0.0);
    FND_TEST_TRUE(signbit(tan(-0.0)));
    FND_TEST_TRUE(isnan(sin(double_t(INFINITY))));
    FND_TEST_TRUE(isnan(cos(double_t(INFINITY))));
    FND_TEST_TRUE(isnan(tan(double_t(INFINITY))));
}

void unittests_math_scalar_asin_acos_atan()
{
    // float_t
    FND_TEST_TRUE(asin(0.0f) == 0.0f);
    FND_TEST_TRUE(signbit(asin(-0.0f)));
    FND_TEST_TRUE(asin(1.0f) == kFloatPi / 2);
    FND_TEST_TRUE(asin(-1.0f) == -kFloatPi / 2);
    FND_TEST_TRUE(acos(1.0f) == 0.0f);
    FND_TEST_TRUE(acos(0.0f) == kFloatPi / 2);
    FND_TEST_TRUE(acos(-1.0f) == kFloatPi);
    FND_TEST_TRUE(atan(0.0f) == 0.0f);
    FND_TEST_TRUE(signbit(atan(-0.0f)));
    FND_TEST_TRUE(atan(1.0f) == kFloatPi / 4);
    FND_TEST_TRUE(atan(INFINITY) == kFloatPi / 2);
    FND_TEST_TRUE(atan(-INFINITY) == -kFloatPi / 2);
    FND_TEST_TRUE(isnan(asin(2.0f)));
    FND_TEST_TRUE(isnan(acos(-2.0f)));
    // double_t
    FND_TEST_TRUE(asin(0.0) == 0.0);
    FND_TEST_TRUE(signbit(asin(-0.0)));
    FND_TEST_TRUE(asin(1.0) == kDoublePi / 2);
    FND_TEST_TRUE(asin(-1.0) == -kDoublePi / 2);
    FND_TEST_TRUE(acos(1.0) == 0.0);
    FND_TEST_TRUE(acos(0.0) == kDoublePi / 2);
    FND_TEST_TRUE(acos(-1.0) == kDoublePi);
    FND_TEST_TRUE(atan(0.0) == 0.0);
    FND_TEST_TRUE(signbit(atan(-0.0)));
    FND_TEST_TRUE(atan(1.0) == kDoublePi / 4);
    FND_TEST_TRUE(atan(double_t(INFINITY)) == kDoublePi / 2);
    FND_TEST_TRUE(atan(-double_t(INFINITY)) == -kDoublePi / 2);
    FND_TEST_TRUE(isnan(asin(2.0)));
    FND_TEST_TRUE(isnan(acos(-2.0)));
}

void unittests_math_scalar_atan2()
{
    // float_t: one point per axis direction, and the sign of zero picks the
    // side of the branch cut along the negative x axis.
    FND_TEST_TRUE(atan2(0.0f, 1.0f) == 0.0f);
    FND_TEST_TRUE(atan2(1.0f, 0.0f) == kFloatPi / 2);
    FND_TEST_TRUE(atan2(-1.0f, 0.0f) == -kFloatPi / 2);
    FND_TEST_TRUE(atan2(0.0f, -1.0f) == kFloatPi);
    FND_TEST_TRUE(atan2(-0.0f, -1.0f) == -kFloatPi);
    FND_TEST_TRUE(atan2(1.0f, 1.0f) == kFloatPi / 4);
    FND_TEST_TRUE(isnan(atan2(NAN, 1.0f)));
    // double_t
    FND_TEST_TRUE(atan2(0.0, 1.0) == 0.0);
    FND_TEST_TRUE(atan2(1.0, 0.0) == kDoublePi / 2);
    FND_TEST_TRUE(atan2(-1.0, 0.0) == -kDoublePi / 2);
    FND_TEST_TRUE(atan2(0.0, -1.0) == kDoublePi);
    FND_TEST_TRUE(atan2(-0.0, -1.0) == -kDoublePi);
    FND_TEST_TRUE(atan2(1.0, 1.0) == kDoublePi / 4);
    FND_TEST_TRUE(isnan(atan2(double_t(NAN), 1.0)));
}


void unittests_math_scalar()
{
    unittests_math_scalar_abs_integer_types();
    unittests_math_scalar_abs_float_types();

    unittests_math_scalar_approx_equal_float();

    unittests_math_scalar_sin_cos_tan();
    unittests_math_scalar_asin_acos_atan();
    unittests_math_scalar_atan2();
}

} // namespace fnd::unittests
