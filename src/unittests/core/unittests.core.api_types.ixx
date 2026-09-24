module;
#include "foundation/unittests.h"


export module unittests.core:api_types;
import foundation.core;

namespace fnd::unittests {

export void unittests_core_api_types();

// ---------------------------------------------------------------------------
// Built in types
// ---------------------------------------------------------------------------

void unittests_core_api_type_definitions()
{
    // byte_t
    static_assert(sizeof(byte_t) == 1, "byte_t must be 1 byte");
    static_assert(byte_t{-1} < byte_t{0}, "byte_t must be signed");
    // int_t
    static_assert(sizeof(int_t) == 4, "int_t must be 4 bytes");
    static_assert(int_t{-1} < int_t{0}, "int_t must be signed");
    // long_t
    static_assert(sizeof(long_t) == 8, "long_t must be 8 bytes");
    static_assert(long_t{-1} < long_t{0}, "long_t must be signed");
    // float
    static_assert(sizeof(float_t) == 4, "float_t must be 4 bytes");
    static_assert(sizeof(double_t) == 8, "float_t must be 8 bytes");

    // ubyte_t
    static_assert(sizeof(ubyte_t) == 1, "ubyte_t must be 1 byte");
    static_assert(ubyte_t(-1) > ubyte_t{0}, "ubyte_t must be unsigned");
    // uint_t
    static_assert(sizeof(uint_t) == 4, "uint_t must be 4 bytes");
    static_assert(uint_t(-1) > uint_t{0}, "uint_t must be unsigned");
    // ulong_t
    static_assert(sizeof(ulong_t) == 8, "ulong_t must be 8 bytes");
    static_assert(ulong_t(-1) > ulong_t{0}, "ulong_t must be unsigned");

    static_assert(sizeof(void*) == 8, "foundation targets 64-bit only");
}

// NOTE:
// Smallest and largest NaN payloads: right above the infinity bit pattern, and
// all exponent and mantissa bits set.
constexpr float_t kFloatNaNLow = bit_cast<float_t>(0x7F800001u);
constexpr float_t kFloatNaNHigh = bit_cast<float_t>(0x7FFFFFFFu);
constexpr double_t kDoubleNaNLow = bit_cast<double_t>(0x7FF0000000000001ull);
constexpr double_t kDoubleNaNHigh = bit_cast<double_t>(0x7FFFFFFFFFFFFFFFull);

void unittests_core_api_types_isfinite_float()
{
    FND_TEST_TRUE(isfinite(0.0f));
    FND_TEST_TRUE(isfinite(-0.0f));
    FND_TEST_TRUE(isfinite(1.0f));
    FND_TEST_TRUE(isfinite(-1.0f));
    FND_TEST_TRUE(isfinite(kFloatMaxValue));
    FND_TEST_TRUE(isfinite(kFloatMinValue));
    FND_TEST_TRUE(isfinite(kFloatMinNormal));
    FND_TEST_TRUE(isfinite(kFloatMinSubnormal));
    FND_TEST_TRUE(isfinite(-kFloatMinSubnormal));
    FND_TEST_FALSE(isfinite(kFloatInfinity));
    FND_TEST_FALSE(isfinite(-kFloatInfinity));
    FND_TEST_FALSE(isfinite(kFloatNaN));
    FND_TEST_FALSE(isfinite(-kFloatNaN));
    FND_TEST_FALSE(isfinite(kFloatNaNLow));
    FND_TEST_FALSE(isfinite(kFloatNaNHigh));
}

void unittests_core_api_types_isfinite_double()
{
    FND_TEST_TRUE(isfinite(0.0));
    FND_TEST_TRUE(isfinite(-0.0));
    FND_TEST_TRUE(isfinite(1.0));
    FND_TEST_TRUE(isfinite(-1.0));
    FND_TEST_TRUE(isfinite(kDoubleMaxValue));
    FND_TEST_TRUE(isfinite(kDoubleMinValue));
    FND_TEST_TRUE(isfinite(kDoubleMinNormal));
    FND_TEST_TRUE(isfinite(kDoubleMinSubnormal));
    FND_TEST_TRUE(isfinite(-kDoubleMinSubnormal));
    FND_TEST_FALSE(isfinite(kDoubleInfinity));
    FND_TEST_FALSE(isfinite(-kDoubleInfinity));
    FND_TEST_FALSE(isfinite(kDoubleNaN));
    FND_TEST_FALSE(isfinite(-kDoubleNaN));
    FND_TEST_FALSE(isfinite(kDoubleNaNLow));
    FND_TEST_FALSE(isfinite(kDoubleNaNHigh));
}

void unittests_core_api_types_isinf_float()
{
    FND_TEST_TRUE(isinf(kFloatInfinity));
    FND_TEST_TRUE(isinf(-kFloatInfinity));
    FND_TEST_FALSE(isinf(0.0f));
    FND_TEST_FALSE(isinf(-0.0f));
    FND_TEST_FALSE(isinf(1.0f));
    FND_TEST_FALSE(isinf(-1.0f));
    FND_TEST_FALSE(isinf(kFloatMaxValue));
    FND_TEST_FALSE(isinf(kFloatMinValue));
    FND_TEST_FALSE(isinf(kFloatMinNormal));
    FND_TEST_FALSE(isinf(kFloatMinSubnormal));
    FND_TEST_FALSE(isinf(kFloatNaN));
    FND_TEST_FALSE(isinf(-kFloatNaN));
    FND_TEST_FALSE(isinf(kFloatNaNLow));
    FND_TEST_FALSE(isinf(kFloatNaNHigh));
}

void unittests_core_api_types_isinf_double()
{
    FND_TEST_TRUE(isinf(kDoubleInfinity));
    FND_TEST_TRUE(isinf(-kDoubleInfinity));
    FND_TEST_FALSE(isinf(0.0));
    FND_TEST_FALSE(isinf(-0.0));
    FND_TEST_FALSE(isinf(1.0));
    FND_TEST_FALSE(isinf(-1.0));
    FND_TEST_FALSE(isinf(kDoubleMaxValue));
    FND_TEST_FALSE(isinf(kDoubleMinValue));
    FND_TEST_FALSE(isinf(kDoubleMinNormal));
    FND_TEST_FALSE(isinf(kDoubleMinSubnormal));
    FND_TEST_FALSE(isinf(kDoubleNaN));
    FND_TEST_FALSE(isinf(-kDoubleNaN));
    FND_TEST_FALSE(isinf(kDoubleNaNLow));
    FND_TEST_FALSE(isinf(kDoubleNaNHigh));
}

void unittests_core_api_types_isnan_float()
{
    FND_TEST_TRUE(isnan(kFloatNaN));
    FND_TEST_TRUE(isnan(-kFloatNaN));
    FND_TEST_TRUE(isnan(kFloatNaNLow));
    FND_TEST_TRUE(isnan(kFloatNaNHigh));
    FND_TEST_FALSE(isnan(0.0f));
    FND_TEST_FALSE(isnan(-0.0f));
    FND_TEST_FALSE(isnan(1.0f));
    FND_TEST_FALSE(isnan(-1.0f));
    FND_TEST_FALSE(isnan(kFloatMaxValue));
    FND_TEST_FALSE(isnan(kFloatMinValue));
    FND_TEST_FALSE(isnan(kFloatMinNormal));
    FND_TEST_FALSE(isnan(kFloatMinSubnormal));
    FND_TEST_FALSE(isnan(kFloatInfinity));
    FND_TEST_FALSE(isnan(-kFloatInfinity));
}

void unittests_core_api_types_isnan_double()
{
    FND_TEST_TRUE(isnan(kDoubleNaN));
    FND_TEST_TRUE(isnan(-kDoubleNaN));
    FND_TEST_TRUE(isnan(kDoubleNaNLow));
    FND_TEST_TRUE(isnan(kDoubleNaNHigh));
    FND_TEST_FALSE(isnan(0.0));
    FND_TEST_FALSE(isnan(-0.0));
    FND_TEST_FALSE(isnan(1.0));
    FND_TEST_FALSE(isnan(-1.0));
    FND_TEST_FALSE(isnan(kDoubleMaxValue));
    FND_TEST_FALSE(isnan(kDoubleMinValue));
    FND_TEST_FALSE(isnan(kDoubleMinNormal));
    FND_TEST_FALSE(isnan(kDoubleMinSubnormal));
    FND_TEST_FALSE(isnan(kDoubleInfinity));
    FND_TEST_FALSE(isnan(-kDoubleInfinity));
}

void unittests_core_api_types()
{
    unittests_core_api_type_definitions();
    unittests_core_api_types_isfinite_float();
    unittests_core_api_types_isfinite_double();
    unittests_core_api_types_isinf_float();
    unittests_core_api_types_isinf_double();
    unittests_core_api_types_isnan_float();
    unittests_core_api_types_isnan_double();
}

} // namespace fnd::unittests
