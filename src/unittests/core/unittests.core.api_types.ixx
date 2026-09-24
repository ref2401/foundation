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

void unittests_core_api_types_min_byte()
{
    static_assert(min(byte_t{1}, byte_t{2}) == 1);
    static_assert(min(byte_t{2}, byte_t{1}) == 1);
    static_assert(min(byte_t{-1}, byte_t{1}) == -1);
    static_assert(min(byte_t{5}, byte_t{5}) == 5);
    static_assert(min(kByteMinValue, kByteMaxValue) == kByteMinValue);
    static_assert(min(kByteMaxValue, kByteMinValue) == kByteMinValue);
}

void unittests_core_api_types_min_int()
{
    static_assert(min(int_t{1}, int_t{2}) == 1);
    static_assert(min(int_t{2}, int_t{1}) == 1);
    static_assert(min(int_t{-1}, int_t{1}) == -1);
    static_assert(min(int_t{5}, int_t{5}) == 5);
    static_assert(min(kIntMinValue, kIntMaxValue) == kIntMinValue);
    static_assert(min(kIntMaxValue, kIntMinValue) == kIntMinValue);
}

void unittests_core_api_types_min_long()
{
    static_assert(min(long_t{1}, long_t{2}) == 1);
    static_assert(min(long_t{2}, long_t{1}) == 1);
    static_assert(min(long_t{-1}, long_t{1}) == -1);
    static_assert(min(long_t{5}, long_t{5}) == 5);
    static_assert(min(kLongMinValue, kLongMaxValue) == kLongMinValue);
    static_assert(min(kLongMaxValue, kLongMinValue) == kLongMinValue);
}

void unittests_core_api_types_min_ubyte()
{
    static_assert(min(ubyte_t{1}, ubyte_t{2}) == 1);
    static_assert(min(ubyte_t{2}, ubyte_t{1}) == 1);
    static_assert(min(ubyte_t{5}, ubyte_t{5}) == 5);
    static_assert(min(kUByteMinValue, kUByteMaxValue) == kUByteMinValue);
    static_assert(min(kUByteMaxValue, kUByteMinValue) == kUByteMinValue);
}

void unittests_core_api_types_min_uint()
{
    static_assert(min(uint_t{1}, uint_t{2}) == 1);
    static_assert(min(uint_t{2}, uint_t{1}) == 1);
    static_assert(min(uint_t{5}, uint_t{5}) == 5);
    static_assert(min(kUIntMinValue, kUIntMaxValue) == kUIntMinValue);
    static_assert(min(kUIntMaxValue, kUIntMinValue) == kUIntMinValue);
}

void unittests_core_api_types_min_ulong()
{
    static_assert(min(ulong_t{1}, ulong_t{2}) == 1);
    static_assert(min(ulong_t{2}, ulong_t{1}) == 1);
    static_assert(min(ulong_t{5}, ulong_t{5}) == 5);
    static_assert(min(kULongMinValue, kULongMaxValue) == kULongMinValue);
    static_assert(min(kULongMaxValue, kULongMinValue) == kULongMinValue);
}

void unittests_core_api_types_min_float()
{
    FND_TEST_TRUE(min(1.0f, 2.0f) == 1.0f);
    FND_TEST_TRUE(min(2.0f, 1.0f) == 1.0f);
    FND_TEST_TRUE(min(-1.0f, 1.0f) == -1.0f);
    FND_TEST_TRUE(min(5.0f, 5.0f) == 5.0f);
    FND_TEST_TRUE(min(kFloatMinValue, kFloatMaxValue) == kFloatMinValue);
    FND_TEST_TRUE(min(-kFloatInfinity, 1.0f) == -kFloatInfinity);
    FND_TEST_TRUE(min(kFloatInfinity, 1.0f) == 1.0f);
    // Comparison based: if either argument is NaN, the second one is returned.
    FND_TEST_TRUE(min(kFloatNaN, 1.0f) == 1.0f);
    FND_TEST_TRUE(min(1.0f, kFloatNaN) == 1.0f);
    FND_TEST_TRUE(isnan(min(kFloatNaN, kFloatNaN)));
}

void unittests_core_api_types_min_double()
{
    FND_TEST_TRUE(min(1.0, 2.0) == 1.0);
    FND_TEST_TRUE(min(2.0, 1.0) == 1.0);
    FND_TEST_TRUE(min(-1.0, 1.0) == -1.0);
    FND_TEST_TRUE(min(5.0, 5.0) == 5.0);
    FND_TEST_TRUE(min(kDoubleMinValue, kDoubleMaxValue) == kDoubleMinValue);
    FND_TEST_TRUE(min(-kDoubleInfinity, 1.0) == -kDoubleInfinity);
    FND_TEST_TRUE(min(kDoubleInfinity, 1.0) == 1.0);
    // Comparison based: if either argument is NaN, the second one is returned.
    FND_TEST_TRUE(min(kDoubleNaN, 1.0) == 1.0);
    FND_TEST_TRUE(min(1.0, kDoubleNaN) == 1.0);
    FND_TEST_TRUE(isnan(min(kDoubleNaN, kDoubleNaN)));
}

void unittests_core_api_types_max_byte()
{
    static_assert(max(byte_t{1}, byte_t{2}) == 2);
    static_assert(max(byte_t{2}, byte_t{1}) == 2);
    static_assert(max(byte_t{-1}, byte_t{1}) == 1);
    static_assert(max(byte_t{5}, byte_t{5}) == 5);
    static_assert(max(kByteMinValue, kByteMaxValue) == kByteMaxValue);
    static_assert(max(kByteMaxValue, kByteMinValue) == kByteMaxValue);
}

void unittests_core_api_types_max_int()
{
    static_assert(max(int_t{1}, int_t{2}) == 2);
    static_assert(max(int_t{2}, int_t{1}) == 2);
    static_assert(max(int_t{-1}, int_t{1}) == 1);
    static_assert(max(int_t{5}, int_t{5}) == 5);
    static_assert(max(kIntMinValue, kIntMaxValue) == kIntMaxValue);
    static_assert(max(kIntMaxValue, kIntMinValue) == kIntMaxValue);
}

void unittests_core_api_types_max_long()
{
    static_assert(max(long_t{1}, long_t{2}) == 2);
    static_assert(max(long_t{2}, long_t{1}) == 2);
    static_assert(max(long_t{-1}, long_t{1}) == 1);
    static_assert(max(long_t{5}, long_t{5}) == 5);
    static_assert(max(kLongMinValue, kLongMaxValue) == kLongMaxValue);
    static_assert(max(kLongMaxValue, kLongMinValue) == kLongMaxValue);
}

void unittests_core_api_types_max_ubyte()
{
    static_assert(max(ubyte_t{1}, ubyte_t{2}) == 2);
    static_assert(max(ubyte_t{2}, ubyte_t{1}) == 2);
    static_assert(max(ubyte_t{5}, ubyte_t{5}) == 5);
    static_assert(max(kUByteMinValue, kUByteMaxValue) == kUByteMaxValue);
    static_assert(max(kUByteMaxValue, kUByteMinValue) == kUByteMaxValue);
}

void unittests_core_api_types_max_uint()
{
    static_assert(max(uint_t{1}, uint_t{2}) == 2);
    static_assert(max(uint_t{2}, uint_t{1}) == 2);
    static_assert(max(uint_t{5}, uint_t{5}) == 5);
    static_assert(max(kUIntMinValue, kUIntMaxValue) == kUIntMaxValue);
    static_assert(max(kUIntMaxValue, kUIntMinValue) == kUIntMaxValue);
}

void unittests_core_api_types_max_ulong()
{
    static_assert(max(ulong_t{1}, ulong_t{2}) == 2);
    static_assert(max(ulong_t{2}, ulong_t{1}) == 2);
    static_assert(max(ulong_t{5}, ulong_t{5}) == 5);
    static_assert(max(kULongMinValue, kULongMaxValue) == kULongMaxValue);
    static_assert(max(kULongMaxValue, kULongMinValue) == kULongMaxValue);
}

void unittests_core_api_types_max_float()
{
    FND_TEST_TRUE(max(1.0f, 2.0f) == 2.0f);
    FND_TEST_TRUE(max(2.0f, 1.0f) == 2.0f);
    FND_TEST_TRUE(max(-1.0f, 1.0f) == 1.0f);
    FND_TEST_TRUE(max(5.0f, 5.0f) == 5.0f);
    FND_TEST_TRUE(max(kFloatMinValue, kFloatMaxValue) == kFloatMaxValue);
    FND_TEST_TRUE(max(kFloatInfinity, 1.0f) == kFloatInfinity);
    FND_TEST_TRUE(max(-kFloatInfinity, 1.0f) == 1.0f);
    // Comparison based: if either argument is NaN, the second one is returned.
    FND_TEST_TRUE(max(kFloatNaN, 1.0f) == 1.0f);
    FND_TEST_TRUE(max(1.0f, kFloatNaN) == 1.0f);
    FND_TEST_TRUE(isnan(max(kFloatNaN, kFloatNaN)));
}

void unittests_core_api_types_max_double()
{
    FND_TEST_TRUE(max(1.0, 2.0) == 2.0);
    FND_TEST_TRUE(max(2.0, 1.0) == 2.0);
    FND_TEST_TRUE(max(-1.0, 1.0) == 1.0);
    FND_TEST_TRUE(max(5.0, 5.0) == 5.0);
    FND_TEST_TRUE(max(kDoubleMinValue, kDoubleMaxValue) == kDoubleMaxValue);
    FND_TEST_TRUE(max(kDoubleInfinity, 1.0) == kDoubleInfinity);
    FND_TEST_TRUE(max(-kDoubleInfinity, 1.0) == 1.0);
    // Comparison based: if either argument is NaN, the second one is returned.
    FND_TEST_TRUE(max(kDoubleNaN, 1.0) == 1.0);
    FND_TEST_TRUE(max(1.0, kDoubleNaN) == 1.0);
    FND_TEST_TRUE(isnan(max(kDoubleNaN, kDoubleNaN)));
}

void unittests_core_api_types_clamp_byte()
{
    static_assert(clamp(byte_t{5}, byte_t{-10}, byte_t{10}) == 5);
    static_assert(clamp(byte_t{-20}, byte_t{-10}, byte_t{10}) == -10);
    static_assert(clamp(byte_t{20}, byte_t{-10}, byte_t{10}) == 10);
    static_assert(clamp(byte_t{-10}, byte_t{-10}, byte_t{10}) == -10);
    static_assert(clamp(byte_t{10}, byte_t{-10}, byte_t{10}) == 10);
    static_assert(clamp(byte_t{20}, byte_t{3}, byte_t{3}) == 3);
    static_assert(clamp(kByteMinValue, kByteMinValue, kByteMaxValue) == kByteMinValue);
    static_assert(clamp(kByteMaxValue, kByteMinValue, kByteMaxValue) == kByteMaxValue);
}

void unittests_core_api_types_clamp_int()
{
    static_assert(clamp(int_t{5}, int_t{-10}, int_t{10}) == 5);
    static_assert(clamp(int_t{-20}, int_t{-10}, int_t{10}) == -10);
    static_assert(clamp(int_t{20}, int_t{-10}, int_t{10}) == 10);
    static_assert(clamp(int_t{-10}, int_t{-10}, int_t{10}) == -10);
    static_assert(clamp(int_t{10}, int_t{-10}, int_t{10}) == 10);
    static_assert(clamp(int_t{20}, int_t{3}, int_t{3}) == 3);
    static_assert(clamp(kIntMinValue, kIntMinValue, kIntMaxValue) == kIntMinValue);
    static_assert(clamp(kIntMaxValue, kIntMinValue, kIntMaxValue) == kIntMaxValue);
}

void unittests_core_api_types_clamp_long()
{
    static_assert(clamp(long_t{5}, long_t{-10}, long_t{10}) == 5);
    static_assert(clamp(long_t{-20}, long_t{-10}, long_t{10}) == -10);
    static_assert(clamp(long_t{20}, long_t{-10}, long_t{10}) == 10);
    static_assert(clamp(long_t{-10}, long_t{-10}, long_t{10}) == -10);
    static_assert(clamp(long_t{10}, long_t{-10}, long_t{10}) == 10);
    static_assert(clamp(long_t{20}, long_t{3}, long_t{3}) == 3);
    static_assert(clamp(kLongMinValue, kLongMinValue, kLongMaxValue) == kLongMinValue);
    static_assert(clamp(kLongMaxValue, kLongMinValue, kLongMaxValue) == kLongMaxValue);
}

void unittests_core_api_types_clamp_ubyte()
{
    static_assert(clamp(ubyte_t{5}, ubyte_t{2}, ubyte_t{10}) == 5);
    static_assert(clamp(ubyte_t{0}, ubyte_t{2}, ubyte_t{10}) == 2);
    static_assert(clamp(ubyte_t{20}, ubyte_t{2}, ubyte_t{10}) == 10);
    static_assert(clamp(ubyte_t{2}, ubyte_t{2}, ubyte_t{10}) == 2);
    static_assert(clamp(ubyte_t{10}, ubyte_t{2}, ubyte_t{10}) == 10);
    static_assert(clamp(ubyte_t{20}, ubyte_t{3}, ubyte_t{3}) == 3);
    static_assert(clamp(kUByteMinValue, kUByteMinValue, kUByteMaxValue) == kUByteMinValue);
    static_assert(clamp(kUByteMaxValue, kUByteMinValue, kUByteMaxValue) == kUByteMaxValue);
}

void unittests_core_api_types_clamp_uint()
{
    static_assert(clamp(uint_t{5}, uint_t{2}, uint_t{10}) == 5);
    static_assert(clamp(uint_t{0}, uint_t{2}, uint_t{10}) == 2);
    static_assert(clamp(uint_t{20}, uint_t{2}, uint_t{10}) == 10);
    static_assert(clamp(uint_t{2}, uint_t{2}, uint_t{10}) == 2);
    static_assert(clamp(uint_t{10}, uint_t{2}, uint_t{10}) == 10);
    static_assert(clamp(uint_t{20}, uint_t{3}, uint_t{3}) == 3);
    static_assert(clamp(kUIntMinValue, kUIntMinValue, kUIntMaxValue) == kUIntMinValue);
    static_assert(clamp(kUIntMaxValue, kUIntMinValue, kUIntMaxValue) == kUIntMaxValue);
}

void unittests_core_api_types_clamp_ulong()
{
    static_assert(clamp(ulong_t{5}, ulong_t{2}, ulong_t{10}) == 5);
    static_assert(clamp(ulong_t{0}, ulong_t{2}, ulong_t{10}) == 2);
    static_assert(clamp(ulong_t{20}, ulong_t{2}, ulong_t{10}) == 10);
    static_assert(clamp(ulong_t{2}, ulong_t{2}, ulong_t{10}) == 2);
    static_assert(clamp(ulong_t{10}, ulong_t{2}, ulong_t{10}) == 10);
    static_assert(clamp(ulong_t{20}, ulong_t{3}, ulong_t{3}) == 3);
    static_assert(clamp(kULongMinValue, kULongMinValue, kULongMaxValue) == kULongMinValue);
    static_assert(clamp(kULongMaxValue, kULongMinValue, kULongMaxValue) == kULongMaxValue);
}

void unittests_core_api_types_clamp_float()
{
    FND_TEST_TRUE(clamp(0.5f, -1.0f, 1.0f) == 0.5f);
    FND_TEST_TRUE(clamp(-2.0f, -1.0f, 1.0f) == -1.0f);
    FND_TEST_TRUE(clamp(2.0f, -1.0f, 1.0f) == 1.0f);
    FND_TEST_TRUE(clamp(-1.0f, -1.0f, 1.0f) == -1.0f);
    FND_TEST_TRUE(clamp(1.0f, -1.0f, 1.0f) == 1.0f);
    FND_TEST_TRUE(clamp(2.0f, 0.5f, 0.5f) == 0.5f);
    FND_TEST_TRUE(clamp(kFloatInfinity, -1.0f, 1.0f) == 1.0f);
    FND_TEST_TRUE(clamp(-kFloatInfinity, -1.0f, 1.0f) == -1.0f);
}

void unittests_core_api_types_clamp_double()
{
    FND_TEST_TRUE(clamp(0.5, -1.0, 1.0) == 0.5);
    FND_TEST_TRUE(clamp(-2.0, -1.0, 1.0) == -1.0);
    FND_TEST_TRUE(clamp(2.0, -1.0, 1.0) == 1.0);
    FND_TEST_TRUE(clamp(-1.0, -1.0, 1.0) == -1.0);
    FND_TEST_TRUE(clamp(1.0, -1.0, 1.0) == 1.0);
    FND_TEST_TRUE(clamp(2.0, 0.5, 0.5) == 0.5);
    FND_TEST_TRUE(clamp(kDoubleInfinity, -1.0, 1.0) == 1.0);
    FND_TEST_TRUE(clamp(-kDoubleInfinity, -1.0, 1.0) == -1.0);
}

void unittests_core_api_types_sign_byte()
{
    static_assert(sign(byte_t{0}) == 0);
    static_assert(sign(byte_t{5}) == 1);
    static_assert(sign(byte_t{-5}) == -1);
    static_assert(sign(kByteMaxValue) == 1);
    static_assert(sign(kByteMinValue) == -1);
}

void unittests_core_api_types_sign_int()
{
    static_assert(sign(int_t{0}) == 0);
    static_assert(sign(int_t{5}) == 1);
    static_assert(sign(int_t{-5}) == -1);
    static_assert(sign(kIntMaxValue) == 1);
    static_assert(sign(kIntMinValue) == -1);
}

void unittests_core_api_types_sign_long()
{
    static_assert(sign(long_t{0}) == 0);
    static_assert(sign(long_t{5}) == 1);
    static_assert(sign(long_t{-5}) == -1);
    static_assert(sign(kLongMaxValue) == 1);
    static_assert(sign(kLongMinValue) == -1);
}

void unittests_core_api_types_sign_float()
{
    FND_TEST_TRUE(sign(0.0f) == 0.0f);
    FND_TEST_TRUE(sign(-0.0f) == 0.0f);
    FND_TEST_TRUE(sign(2.5f) == 1.0f);
    FND_TEST_TRUE(sign(-2.5f) == -1.0f);
    FND_TEST_TRUE(sign(kFloatMinSubnormal) == 1.0f);
    FND_TEST_TRUE(sign(-kFloatMinSubnormal) == -1.0f);
    FND_TEST_TRUE(sign(kFloatMaxValue) == 1.0f);
    FND_TEST_TRUE(sign(kFloatMinValue) == -1.0f);
    FND_TEST_TRUE(sign(kFloatInfinity) == 1.0f);
    FND_TEST_TRUE(sign(-kFloatInfinity) == -1.0f);
    FND_TEST_TRUE(sign(kFloatNaN) == 0.0f);
}

void unittests_core_api_types_sign_double()
{
    FND_TEST_TRUE(sign(0.0) == 0.0);
    FND_TEST_TRUE(sign(-0.0) == 0.0);
    FND_TEST_TRUE(sign(2.5) == 1.0);
    FND_TEST_TRUE(sign(-2.5) == -1.0);
    FND_TEST_TRUE(sign(kDoubleMinSubnormal) == 1.0);
    FND_TEST_TRUE(sign(-kDoubleMinSubnormal) == -1.0);
    FND_TEST_TRUE(sign(kDoubleMaxValue) == 1.0);
    FND_TEST_TRUE(sign(kDoubleMinValue) == -1.0);
    FND_TEST_TRUE(sign(kDoubleInfinity) == 1.0);
    FND_TEST_TRUE(sign(-kDoubleInfinity) == -1.0);
    FND_TEST_TRUE(sign(kDoubleNaN) == 0.0);
}

void unittests_core_api_types_ceil_float()
{
    FND_TEST_TRUE(ceil(0.0f) == 0.0f);
    FND_TEST_TRUE(ceil(1.5f) == 2.0f);
    FND_TEST_TRUE(ceil(-1.5f) == -1.0f);
    FND_TEST_TRUE(ceil(2.0f) == 2.0f);
    FND_TEST_TRUE(ceil(-2.0f) == -2.0f);
    FND_TEST_TRUE(ceil(0.5f) == 1.0f);
    FND_TEST_TRUE(ceil(-0.5f) == 0.0f);
    FND_TEST_TRUE(ceil(kFloatMinSubnormal) == 1.0f);
    FND_TEST_TRUE(ceil(-kFloatMinSubnormal) == 0.0f);
    FND_TEST_TRUE(ceil(kFloatMaxValue) == kFloatMaxValue);
    FND_TEST_TRUE(ceil(kFloatInfinity) == kFloatInfinity);
    FND_TEST_TRUE(ceil(-kFloatInfinity) == -kFloatInfinity);
    FND_TEST_TRUE(isnan(ceil(kFloatNaN)));
}

void unittests_core_api_types_ceil_double()
{
    FND_TEST_TRUE(ceil(0.0) == 0.0);
    FND_TEST_TRUE(ceil(1.5) == 2.0);
    FND_TEST_TRUE(ceil(-1.5) == -1.0);
    FND_TEST_TRUE(ceil(2.0) == 2.0);
    FND_TEST_TRUE(ceil(-2.0) == -2.0);
    FND_TEST_TRUE(ceil(0.5) == 1.0);
    FND_TEST_TRUE(ceil(-0.5) == 0.0);
    FND_TEST_TRUE(ceil(kDoubleMinSubnormal) == 1.0);
    FND_TEST_TRUE(ceil(-kDoubleMinSubnormal) == 0.0);
    FND_TEST_TRUE(ceil(kDoubleMaxValue) == kDoubleMaxValue);
    FND_TEST_TRUE(ceil(kDoubleInfinity) == kDoubleInfinity);
    FND_TEST_TRUE(ceil(-kDoubleInfinity) == -kDoubleInfinity);
    FND_TEST_TRUE(isnan(ceil(kDoubleNaN)));
}

void unittests_core_api_types_floor_float()
{
    FND_TEST_TRUE(floor(0.0f) == 0.0f);
    FND_TEST_TRUE(floor(1.5f) == 1.0f);
    FND_TEST_TRUE(floor(-1.5f) == -2.0f);
    FND_TEST_TRUE(floor(2.0f) == 2.0f);
    FND_TEST_TRUE(floor(-2.0f) == -2.0f);
    FND_TEST_TRUE(floor(0.5f) == 0.0f);
    FND_TEST_TRUE(floor(-0.5f) == -1.0f);
    FND_TEST_TRUE(floor(kFloatMinSubnormal) == 0.0f);
    FND_TEST_TRUE(floor(-kFloatMinSubnormal) == -1.0f);
    FND_TEST_TRUE(floor(kFloatMinValue) == kFloatMinValue);
    FND_TEST_TRUE(floor(kFloatInfinity) == kFloatInfinity);
    FND_TEST_TRUE(floor(-kFloatInfinity) == -kFloatInfinity);
    FND_TEST_TRUE(isnan(floor(kFloatNaN)));
}

void unittests_core_api_types_floor_double()
{
    FND_TEST_TRUE(floor(0.0) == 0.0);
    FND_TEST_TRUE(floor(1.5) == 1.0);
    FND_TEST_TRUE(floor(-1.5) == -2.0);
    FND_TEST_TRUE(floor(2.0) == 2.0);
    FND_TEST_TRUE(floor(-2.0) == -2.0);
    FND_TEST_TRUE(floor(0.5) == 0.0);
    FND_TEST_TRUE(floor(-0.5) == -1.0);
    FND_TEST_TRUE(floor(kDoubleMinSubnormal) == 0.0);
    FND_TEST_TRUE(floor(-kDoubleMinSubnormal) == -1.0);
    FND_TEST_TRUE(floor(kDoubleMinValue) == kDoubleMinValue);
    FND_TEST_TRUE(floor(kDoubleInfinity) == kDoubleInfinity);
    FND_TEST_TRUE(floor(-kDoubleInfinity) == -kDoubleInfinity);
    FND_TEST_TRUE(isnan(floor(kDoubleNaN)));
}

void unittests_core_api_types_trunc_float()
{
    FND_TEST_TRUE(trunc(0.0f) == 0.0f);
    FND_TEST_TRUE(trunc(1.5f) == 1.0f);
    FND_TEST_TRUE(trunc(-1.5f) == -1.0f);
    FND_TEST_TRUE(trunc(2.0f) == 2.0f);
    FND_TEST_TRUE(trunc(-2.0f) == -2.0f);
    FND_TEST_TRUE(trunc(0.5f) == 0.0f);
    FND_TEST_TRUE(trunc(-0.5f) == 0.0f);
    FND_TEST_TRUE(trunc(kFloatMinSubnormal) == 0.0f);
    FND_TEST_TRUE(trunc(-kFloatMinSubnormal) == 0.0f);
    FND_TEST_TRUE(trunc(kFloatMaxValue) == kFloatMaxValue);
    FND_TEST_TRUE(trunc(kFloatInfinity) == kFloatInfinity);
    FND_TEST_TRUE(trunc(-kFloatInfinity) == -kFloatInfinity);
    FND_TEST_TRUE(isnan(trunc(kFloatNaN)));
}

void unittests_core_api_types_trunc_double()
{
    FND_TEST_TRUE(trunc(0.0) == 0.0);
    FND_TEST_TRUE(trunc(1.5) == 1.0);
    FND_TEST_TRUE(trunc(-1.5) == -1.0);
    FND_TEST_TRUE(trunc(2.0) == 2.0);
    FND_TEST_TRUE(trunc(-2.0) == -2.0);
    FND_TEST_TRUE(trunc(0.5) == 0.0);
    FND_TEST_TRUE(trunc(-0.5) == 0.0);
    FND_TEST_TRUE(trunc(kDoubleMinSubnormal) == 0.0);
    FND_TEST_TRUE(trunc(-kDoubleMinSubnormal) == 0.0);
    FND_TEST_TRUE(trunc(kDoubleMaxValue) == kDoubleMaxValue);
    FND_TEST_TRUE(trunc(kDoubleInfinity) == kDoubleInfinity);
    FND_TEST_TRUE(trunc(-kDoubleInfinity) == -kDoubleInfinity);
    FND_TEST_TRUE(isnan(trunc(kDoubleNaN)));
}

// ---------------------------------------------------------------------------
// fmod
// ---------------------------------------------------------------------------

void unittests_core_api_types_fmod_float()
{
    // The result has the sign of x.
    FND_TEST_TRUE(fmod(7.0f, 3.0f) == 1.0f);
    FND_TEST_TRUE(fmod(-7.0f, 3.0f) == -1.0f);
    FND_TEST_TRUE(fmod(7.0f, -3.0f) == 1.0f);
    FND_TEST_TRUE(fmod(-7.0f, -3.0f) == -1.0f);
    FND_TEST_TRUE(fmod(5.5f, 2.0f) == 1.5f);
    FND_TEST_TRUE(fmod(-5.5f, 2.0f) == -1.5f);
    FND_TEST_TRUE(fmod(6.0f, 3.0f) == 0.0f);
    FND_TEST_TRUE(fmod(0.0f, 3.0f) == 0.0f);
    FND_TEST_TRUE(fmod(1.0f, 3.0f) == 1.0f);
    FND_TEST_TRUE(fmod(1.0f, kFloatInfinity) == 1.0f);
    FND_TEST_TRUE(isnan(fmod(1.0f, 0.0f)));
    FND_TEST_TRUE(isnan(fmod(kFloatInfinity, 1.0f)));
    FND_TEST_TRUE(isnan(fmod(kFloatNaN, 1.0f)));
    FND_TEST_TRUE(isnan(fmod(1.0f, kFloatNaN)));
}

void unittests_core_api_types_fmod_double()
{
    // The result has the sign of x.
    FND_TEST_TRUE(fmod(7.0, 3.0) == 1.0);
    FND_TEST_TRUE(fmod(-7.0, 3.0) == -1.0);
    FND_TEST_TRUE(fmod(7.0, -3.0) == 1.0);
    FND_TEST_TRUE(fmod(-7.0, -3.0) == -1.0);
    FND_TEST_TRUE(fmod(5.5, 2.0) == 1.5);
    FND_TEST_TRUE(fmod(-5.5, 2.0) == -1.5);
    FND_TEST_TRUE(fmod(6.0, 3.0) == 0.0);
    FND_TEST_TRUE(fmod(0.0, 3.0) == 0.0);
    FND_TEST_TRUE(fmod(1.0, 3.0) == 1.0);
    FND_TEST_TRUE(fmod(1.0, kDoubleInfinity) == 1.0);
    FND_TEST_TRUE(isnan(fmod(1.0, 0.0)));
    FND_TEST_TRUE(isnan(fmod(kDoubleInfinity, 1.0)));
    FND_TEST_TRUE(isnan(fmod(kDoubleNaN, 1.0)));
    FND_TEST_TRUE(isnan(fmod(1.0, kDoubleNaN)));
}

void unittests_core_api_types_modf_float()
{
    float_t integer;

    // Both parts have the sign of x.
    FND_TEST_TRUE(modf(3.75f, integer) == 0.75f);
    FND_TEST_TRUE(integer == 3.0f);
    FND_TEST_TRUE(modf(-3.75f, integer) == -0.75f);
    FND_TEST_TRUE(integer == -3.0f);
    FND_TEST_TRUE(modf(2.0f, integer) == 0.0f);
    FND_TEST_TRUE(integer == 2.0f);
    FND_TEST_TRUE(modf(-2.0f, integer) == 0.0f);
    FND_TEST_TRUE(integer == -2.0f);
    FND_TEST_TRUE(modf(0.5f, integer) == 0.5f);
    FND_TEST_TRUE(integer == 0.0f);
    FND_TEST_TRUE(modf(-0.5f, integer) == -0.5f);
    FND_TEST_TRUE(integer == 0.0f);
    FND_TEST_TRUE(modf(0.0f, integer) == 0.0f);
    FND_TEST_TRUE(integer == 0.0f);
    FND_TEST_TRUE(modf(kFloatMinSubnormal, integer) == kFloatMinSubnormal);
    FND_TEST_TRUE(integer == 0.0f);
    FND_TEST_TRUE(modf(kFloatMaxValue, integer) == 0.0f);
    FND_TEST_TRUE(integer == kFloatMaxValue);
    FND_TEST_TRUE(modf(kFloatInfinity, integer) == 0.0f);
    FND_TEST_TRUE(integer == kFloatInfinity);
    FND_TEST_TRUE(modf(-kFloatInfinity, integer) == 0.0f);
    FND_TEST_TRUE(integer == -kFloatInfinity);
    FND_TEST_TRUE(isnan(modf(kFloatNaN, integer)));
    FND_TEST_TRUE(isnan(integer));
}

void unittests_core_api_types_modf_double()
{
    double_t integer;

    // Both parts have the sign of x.
    FND_TEST_TRUE(modf(3.75, integer) == 0.75);
    FND_TEST_TRUE(integer == 3.0);
    FND_TEST_TRUE(modf(-3.75, integer) == -0.75);
    FND_TEST_TRUE(integer == -3.0);
    FND_TEST_TRUE(modf(2.0, integer) == 0.0);
    FND_TEST_TRUE(integer == 2.0);
    FND_TEST_TRUE(modf(-2.0, integer) == 0.0);
    FND_TEST_TRUE(integer == -2.0);
    FND_TEST_TRUE(modf(0.5, integer) == 0.5);
    FND_TEST_TRUE(integer == 0.0);
    FND_TEST_TRUE(modf(-0.5, integer) == -0.5);
    FND_TEST_TRUE(integer == 0.0);
    FND_TEST_TRUE(modf(0.0, integer) == 0.0);
    FND_TEST_TRUE(integer == 0.0);
    FND_TEST_TRUE(modf(kDoubleMinSubnormal, integer) == kDoubleMinSubnormal);
    FND_TEST_TRUE(integer == 0.0);
    FND_TEST_TRUE(modf(kDoubleMaxValue, integer) == 0.0);
    FND_TEST_TRUE(integer == kDoubleMaxValue);
    FND_TEST_TRUE(modf(kDoubleInfinity, integer) == 0.0);
    FND_TEST_TRUE(integer == kDoubleInfinity);
    FND_TEST_TRUE(modf(-kDoubleInfinity, integer) == 0.0);
    FND_TEST_TRUE(integer == -kDoubleInfinity);
    FND_TEST_TRUE(isnan(modf(kDoubleNaN, integer)));
    FND_TEST_TRUE(isnan(integer));
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
    unittests_core_api_types_min_byte();
    unittests_core_api_types_min_int();
    unittests_core_api_types_min_long();
    unittests_core_api_types_min_ubyte();
    unittests_core_api_types_min_uint();
    unittests_core_api_types_min_ulong();
    unittests_core_api_types_min_float();
    unittests_core_api_types_min_double();
    unittests_core_api_types_max_byte();
    unittests_core_api_types_max_int();
    unittests_core_api_types_max_long();
    unittests_core_api_types_max_ubyte();
    unittests_core_api_types_max_uint();
    unittests_core_api_types_max_ulong();
    unittests_core_api_types_max_float();
    unittests_core_api_types_max_double();
    unittests_core_api_types_clamp_byte();
    unittests_core_api_types_clamp_int();
    unittests_core_api_types_clamp_long();
    unittests_core_api_types_clamp_ubyte();
    unittests_core_api_types_clamp_uint();
    unittests_core_api_types_clamp_ulong();
    unittests_core_api_types_clamp_float();
    unittests_core_api_types_clamp_double();
    unittests_core_api_types_sign_byte();
    unittests_core_api_types_sign_int();
    unittests_core_api_types_sign_long();
    unittests_core_api_types_sign_float();
    unittests_core_api_types_sign_double();
    unittests_core_api_types_ceil_float();
    unittests_core_api_types_ceil_double();
    unittests_core_api_types_floor_float();
    unittests_core_api_types_floor_double();
    unittests_core_api_types_trunc_float();
    unittests_core_api_types_trunc_double();
    unittests_core_api_types_fmod_float();
    unittests_core_api_types_fmod_double();
    unittests_core_api_types_modf_float();
    unittests_core_api_types_modf_double();
}

} // namespace fnd::unittests
