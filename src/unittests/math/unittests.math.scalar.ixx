module;
#include <math.h>
#include "foundation/unittests.h"


export module unittests.math:scalar;
import foundation.math;

namespace fnd::unittests {

export void unittests_math_scalar();

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

void unittests_math_scalar()
{
    unittests_math_scalar_abs_integer_types();
    unittests_math_scalar_abs_float_types();
}

} // namespace fnd::unittests
