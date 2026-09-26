module;
#include "foundation/unittests.h"


export module unittests.core:arithmetic;
import foundation.core;

namespace fnd::unittests {

export void unittests_core_arithmetic();

// ---------------------------------------------------------------------------
// bit_cast
// ---------------------------------------------------------------------------

void unittests_core_arithmetic_bit_cast_int_to_float()
{
    FND_TEST_TRUE(bit_cast<float_t>(int_t{0}) == 0.0f);
    FND_TEST_TRUE(bit_cast<float_t>(int_t{0x3F800000}) == 1.0f);
    FND_TEST_TRUE(bit_cast<float_t>(static_cast<int_t>(0xBF800000u)) == -1.0f);
    FND_TEST_TRUE(bit_cast<float_t>(int_t{0x7F800000}) == kFloatInfinity);
    // Bits, not a value conversion: 1 is the smallest subnormal, not 1.0f.
    FND_TEST_TRUE(bit_cast<float_t>(int_t{1}) == kFloatMinSubnormal);
}

void unittests_core_arithmetic_bit_cast_uint_to_float()
{
    FND_TEST_TRUE(bit_cast<float_t>(0u) == 0.0f);
    FND_TEST_TRUE(bit_cast<float_t>(0x3F800000u) == 1.0f);
    FND_TEST_TRUE(bit_cast<float_t>(0xBF800000u) == -1.0f);
    FND_TEST_TRUE(bit_cast<float_t>(0x7F800000u) == kFloatInfinity);
    FND_TEST_TRUE(bit_cast<float_t>(0xFF800000u) == -kFloatInfinity);
    FND_TEST_TRUE(bit_cast<float_t>(0x7F7FFFFFu) == kFloatMaxValue);
    FND_TEST_TRUE(bit_cast<float_t>(0x00800000u) == kFloatMinNormal);
    FND_TEST_TRUE(bit_cast<float_t>(1u) == kFloatMinSubnormal);
}

void unittests_core_arithmetic_bit_cast_float_to_int()
{
    FND_TEST_TRUE(bit_cast<int_t>(0.0f) == 0);
    FND_TEST_TRUE(bit_cast<int_t>(-0.0f) == kIntMinValue);
    FND_TEST_TRUE(bit_cast<int_t>(1.0f) == 0x3F800000);
    FND_TEST_TRUE(bit_cast<int_t>(-1.0f) == static_cast<int_t>(0xBF800000u));
    FND_TEST_TRUE(bit_cast<int_t>(kFloatInfinity) == 0x7F800000);
}

void unittests_core_arithmetic_bit_cast_uint_to_int()
{
    FND_TEST_TRUE(bit_cast<int_t>(0u) == 0);
    FND_TEST_TRUE(bit_cast<int_t>(1u) == 1);
    FND_TEST_TRUE(bit_cast<int_t>(0x7FFFFFFFu) == kIntMaxValue);
    FND_TEST_TRUE(bit_cast<int_t>(0x80000000u) == kIntMinValue);
    FND_TEST_TRUE(bit_cast<int_t>(0xFFFFFFFFu) == -1);
}

void unittests_core_arithmetic_bit_cast_float_to_uint()
{
    FND_TEST_TRUE(bit_cast<uint_t>(0.0f) == 0u);
    FND_TEST_TRUE(bit_cast<uint_t>(-0.0f) == 0x80000000u);
    FND_TEST_TRUE(bit_cast<uint_t>(1.0f) == 0x3F800000u);
    FND_TEST_TRUE(bit_cast<uint_t>(-1.0f) == 0xBF800000u);
    FND_TEST_TRUE(bit_cast<uint_t>(kFloatInfinity) == 0x7F800000u);
    FND_TEST_TRUE(bit_cast<uint_t>(-kFloatInfinity) == 0xFF800000u);
    // NaN: all exponent bits set and a non-zero mantissa, whatever its sign.
    FND_TEST_TRUE((bit_cast<uint_t>(kFloatNaN) & 0x7FFFFFFFu) > 0x7F800000u);
    FND_TEST_TRUE(bit_cast<float_t>(bit_cast<uint_t>(1.5f)) == 1.5f);
}

void unittests_core_arithmetic_bit_cast_int_to_uint()
{
    FND_TEST_TRUE(bit_cast<uint_t>(int_t{0}) == 0u);
    FND_TEST_TRUE(bit_cast<uint_t>(int_t{1}) == 1u);
    FND_TEST_TRUE(bit_cast<uint_t>(int_t{-1}) == 0xFFFFFFFFu);
    FND_TEST_TRUE(bit_cast<uint_t>(kIntMaxValue) == 0x7FFFFFFFu);
    FND_TEST_TRUE(bit_cast<uint_t>(kIntMinValue) == 0x80000000u);
}

void unittests_core_arithmetic_bit_cast_long_to_double()
{
    FND_TEST_TRUE(bit_cast<double_t>(long_t{0}) == 0.0);
    FND_TEST_TRUE(bit_cast<double_t>(long_t{0x3FF0000000000000}) == 1.0);
    FND_TEST_TRUE(bit_cast<double_t>(static_cast<long_t>(0xBFF0000000000000ull)) == -1.0);
    FND_TEST_TRUE(bit_cast<double_t>(long_t{0x7FF0000000000000}) == kDoubleInfinity);
    // Bits, not a value conversion: 1 is the smallest subnormal, not 1.0.
    FND_TEST_TRUE(bit_cast<double_t>(long_t{1}) == kDoubleMinSubnormal);
}

void unittests_core_arithmetic_bit_cast_ulong_to_double()
{
    FND_TEST_TRUE(bit_cast<double_t>(0ull) == 0.0);
    FND_TEST_TRUE(bit_cast<double_t>(0x3FF0000000000000ull) == 1.0);
    FND_TEST_TRUE(bit_cast<double_t>(0xBFF0000000000000ull) == -1.0);
    FND_TEST_TRUE(bit_cast<double_t>(0x7FF0000000000000ull) == kDoubleInfinity);
    FND_TEST_TRUE(bit_cast<double_t>(0xFFF0000000000000ull) == -kDoubleInfinity);
    FND_TEST_TRUE(bit_cast<double_t>(0x7FEFFFFFFFFFFFFFull) == kDoubleMaxValue);
    FND_TEST_TRUE(bit_cast<double_t>(0x0010000000000000ull) == kDoubleMinNormal);
    FND_TEST_TRUE(bit_cast<double_t>(1ull) == kDoubleMinSubnormal);
}

void unittests_core_arithmetic_bit_cast_double_to_long()
{
    FND_TEST_TRUE(bit_cast<long_t>(0.0) == 0);
    FND_TEST_TRUE(bit_cast<long_t>(-0.0) == kLongMinValue);
    FND_TEST_TRUE(bit_cast<long_t>(1.0) == 0x3FF0000000000000);
    FND_TEST_TRUE(bit_cast<long_t>(-1.0) == static_cast<long_t>(0xBFF0000000000000ull));
    FND_TEST_TRUE(bit_cast<long_t>(kDoubleInfinity) == 0x7FF0000000000000);
}

void unittests_core_arithmetic_bit_cast_ulong_to_long()
{
    FND_TEST_TRUE(bit_cast<long_t>(0ull) == 0);
    FND_TEST_TRUE(bit_cast<long_t>(1ull) == 1);
    FND_TEST_TRUE(bit_cast<long_t>(0x7FFFFFFFFFFFFFFFull) == kLongMaxValue);
    FND_TEST_TRUE(bit_cast<long_t>(0x8000000000000000ull) == kLongMinValue);
    FND_TEST_TRUE(bit_cast<long_t>(0xFFFFFFFFFFFFFFFFull) == -1);
}

void unittests_core_arithmetic_bit_cast_double_to_ulong()
{
    FND_TEST_TRUE(bit_cast<ulong_t>(0.0) == 0ull);
    FND_TEST_TRUE(bit_cast<ulong_t>(-0.0) == 0x8000000000000000ull);
    FND_TEST_TRUE(bit_cast<ulong_t>(1.0) == 0x3FF0000000000000ull);
    FND_TEST_TRUE(bit_cast<ulong_t>(-1.0) == 0xBFF0000000000000ull);
    FND_TEST_TRUE(bit_cast<ulong_t>(kDoubleInfinity) == 0x7FF0000000000000ull);
    FND_TEST_TRUE(bit_cast<ulong_t>(-kDoubleInfinity) == 0xFFF0000000000000ull);
    // NaN: all exponent bits set and a non-zero mantissa, whatever its sign.
    FND_TEST_TRUE((bit_cast<ulong_t>(kDoubleNaN) & 0x7FFFFFFFFFFFFFFFull) > 0x7FF0000000000000ull);
    FND_TEST_TRUE(bit_cast<double_t>(bit_cast<ulong_t>(1.5)) == 1.5);
}

void unittests_core_arithmetic_bit_cast_long_to_ulong()
{
    FND_TEST_TRUE(bit_cast<ulong_t>(long_t{0}) == 0ull);
    FND_TEST_TRUE(bit_cast<ulong_t>(long_t{1}) == 1ull);
    FND_TEST_TRUE(bit_cast<ulong_t>(long_t{-1}) == 0xFFFFFFFFFFFFFFFFull);
    FND_TEST_TRUE(bit_cast<ulong_t>(kLongMaxValue) == 0x7FFFFFFFFFFFFFFFull);
    FND_TEST_TRUE(bit_cast<ulong_t>(kLongMinValue) == 0x8000000000000000ull);
}

void unittests_core_arithmetic_abs_integer_types()
{
    // byte_t
    FND_TEST_TRUE(abs(byte_t{0}) == 0);
    FND_TEST_TRUE(abs(byte_t{5}) == 5);
    FND_TEST_TRUE(abs(byte_t{-5}) == 5);
    FND_TEST_TRUE(abs(kByteMaxValue) == kByteMaxValue);
    FND_TEST_TRUE(abs(byte_t{-kByteMaxValue}) == kByteMaxValue);
    // int_t
    FND_TEST_TRUE(abs(int_t{0}) == 0);
    FND_TEST_TRUE(abs(int_t{5}) == 5);
    FND_TEST_TRUE(abs(int_t{-5}) == 5);
    FND_TEST_TRUE(abs(kIntMaxValue) == kIntMaxValue);
    FND_TEST_TRUE(abs(-kIntMaxValue) == kIntMaxValue);
    // long_t
    FND_TEST_TRUE(abs(long_t{0}) == 0);
    FND_TEST_TRUE(abs(long_t{5}) == 5);
    FND_TEST_TRUE(abs(long_t{-5}) == 5);
    FND_TEST_TRUE(abs(kLongMaxValue) == kLongMaxValue);
    FND_TEST_TRUE(abs(-kLongMaxValue) == kLongMaxValue);
}

void unittests_core_arithmetic_abs_float_types()
{
    // float_t
    FND_TEST_TRUE(abs(0.0f) == 0.0f);
    FND_TEST_TRUE(abs(2.5f) == 2.5f);
    FND_TEST_TRUE(abs(-2.5f) == 2.5f);
    FND_TEST_TRUE(sign(abs(-0.0f)) == 0);
    FND_TEST_TRUE(abs(-kFloatInfinity) == kFloatInfinity);
    FND_TEST_TRUE(isnan(abs(-kFloatNaN)));
    // double_t
    FND_TEST_TRUE(abs(0.0) == 0.0);
    FND_TEST_TRUE(abs(2.5) == 2.5);
    FND_TEST_TRUE(abs(-2.5) == 2.5);
    FND_TEST_TRUE(sign(abs(-0.0)) == 0);
    FND_TEST_TRUE(abs(-kDoubleInfinity) == kDoubleInfinity);
    FND_TEST_TRUE(isnan(abs(-kDoubleNaN)));
}

// NOTE:
// Smallest and largest NaN payloads: right above the infinity bit pattern, and
// all exponent and mantissa bits set.
constexpr float_t kFloatNaNLow = bit_cast<float_t>(0x7F800001u);
constexpr float_t kFloatNaNHigh = bit_cast<float_t>(0x7FFFFFFFu);
constexpr double_t kDoubleNaNLow = bit_cast<double_t>(0x7FF0000000000001ull);
constexpr double_t kDoubleNaNHigh = bit_cast<double_t>(0x7FFFFFFFFFFFFFFFull);

void unittests_core_arithmetic_isfinite_float()
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

void unittests_core_arithmetic_isfinite_double()
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

void unittests_core_arithmetic_isinf_float()
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

void unittests_core_arithmetic_isinf_double()
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

void unittests_core_arithmetic_isnan_float()
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

void unittests_core_arithmetic_isnan_double()
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

// ---------------------------------------------------------------------------
// approx_equal
// ---------------------------------------------------------------------------

void unittests_core_arithmetic_approx_equal_float()
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

    // across 0
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

void unittests_core_arithmetic_approx_equal_double()
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

void unittests_core_arithmetic_min_byte()
{
    FND_TEST_TRUE(min(byte_t{1}, byte_t{2}) == 1);
    FND_TEST_TRUE(min(byte_t{2}, byte_t{1}) == 1);
    FND_TEST_TRUE(min(byte_t{-1}, byte_t{1}) == -1);
    FND_TEST_TRUE(min(byte_t{5}, byte_t{5}) == 5);
    FND_TEST_TRUE(min(kByteMinValue, kByteMaxValue) == kByteMinValue);
    FND_TEST_TRUE(min(kByteMaxValue, kByteMinValue) == kByteMinValue);
}

void unittests_core_arithmetic_min_int()
{
    FND_TEST_TRUE(min(int_t{1}, int_t{2}) == 1);
    FND_TEST_TRUE(min(int_t{2}, int_t{1}) == 1);
    FND_TEST_TRUE(min(int_t{-1}, int_t{1}) == -1);
    FND_TEST_TRUE(min(int_t{5}, int_t{5}) == 5);
    FND_TEST_TRUE(min(kIntMinValue, kIntMaxValue) == kIntMinValue);
    FND_TEST_TRUE(min(kIntMaxValue, kIntMinValue) == kIntMinValue);
}

void unittests_core_arithmetic_min_long()
{
    FND_TEST_TRUE(min(long_t{1}, long_t{2}) == 1);
    FND_TEST_TRUE(min(long_t{2}, long_t{1}) == 1);
    FND_TEST_TRUE(min(long_t{-1}, long_t{1}) == -1);
    FND_TEST_TRUE(min(long_t{5}, long_t{5}) == 5);
    FND_TEST_TRUE(min(kLongMinValue, kLongMaxValue) == kLongMinValue);
    FND_TEST_TRUE(min(kLongMaxValue, kLongMinValue) == kLongMinValue);
}

void unittests_core_arithmetic_min_ubyte()
{
    FND_TEST_TRUE(min(ubyte_t{1}, ubyte_t{2}) == 1);
    FND_TEST_TRUE(min(ubyte_t{2}, ubyte_t{1}) == 1);
    FND_TEST_TRUE(min(ubyte_t{5}, ubyte_t{5}) == 5);
    FND_TEST_TRUE(min(kUByteMinValue, kUByteMaxValue) == kUByteMinValue);
    FND_TEST_TRUE(min(kUByteMaxValue, kUByteMinValue) == kUByteMinValue);
}

void unittests_core_arithmetic_min_uint()
{
    FND_TEST_TRUE(min(uint_t{1}, uint_t{2}) == 1);
    FND_TEST_TRUE(min(uint_t{2}, uint_t{1}) == 1);
    FND_TEST_TRUE(min(uint_t{5}, uint_t{5}) == 5);
    FND_TEST_TRUE(min(kUIntMinValue, kUIntMaxValue) == kUIntMinValue);
    FND_TEST_TRUE(min(kUIntMaxValue, kUIntMinValue) == kUIntMinValue);
}

void unittests_core_arithmetic_min_ulong()
{
    FND_TEST_TRUE(min(ulong_t{1}, ulong_t{2}) == 1);
    FND_TEST_TRUE(min(ulong_t{2}, ulong_t{1}) == 1);
    FND_TEST_TRUE(min(ulong_t{5}, ulong_t{5}) == 5);
    FND_TEST_TRUE(min(kULongMinValue, kULongMaxValue) == kULongMinValue);
    FND_TEST_TRUE(min(kULongMaxValue, kULongMinValue) == kULongMinValue);
}

void unittests_core_arithmetic_min_float()
{
    FND_TEST_TRUE(min(1.0f, 2.0f) == 1.0f);
    FND_TEST_TRUE(min(2.0f, 1.0f) == 1.0f);
    FND_TEST_TRUE(min(-1.0f, 1.0f) == -1.0f);
    FND_TEST_TRUE(min(5.0f, 5.0f) == 5.0f);
    FND_TEST_TRUE(min(kFloatMinValue, kFloatMaxValue) == kFloatMinValue);
    FND_TEST_TRUE(min(-kFloatInfinity, 1.0f) == -kFloatInfinity);
    FND_TEST_TRUE(min(kFloatInfinity, 1.0f) == 1.0f);
    FND_TEST_TRUE(min(kFloatNaN, 1.0f) == 1.0f);
    FND_TEST_TRUE(min(1.0f, kFloatNaN) == 1.0f);
    FND_TEST_TRUE(isnan(min(kFloatNaN, kFloatNaN)));
}

void unittests_core_arithmetic_min_double()
{
    FND_TEST_TRUE(min(1.0, 2.0) == 1.0);
    FND_TEST_TRUE(min(2.0, 1.0) == 1.0);
    FND_TEST_TRUE(min(-1.0, 1.0) == -1.0);
    FND_TEST_TRUE(min(5.0, 5.0) == 5.0);
    FND_TEST_TRUE(min(kDoubleMinValue, kDoubleMaxValue) == kDoubleMinValue);
    FND_TEST_TRUE(min(-kDoubleInfinity, 1.0) == -kDoubleInfinity);
    FND_TEST_TRUE(min(kDoubleInfinity, 1.0) == 1.0);
    FND_TEST_TRUE(min(kDoubleNaN, 1.0) == 1.0);
    FND_TEST_TRUE(min(1.0, kDoubleNaN) == 1.0);
    FND_TEST_TRUE(isnan(min(kDoubleNaN, kDoubleNaN)));
}

void unittests_core_arithmetic_max_byte()
{
    FND_TEST_TRUE(max(byte_t{1}, byte_t{2}) == 2);
    FND_TEST_TRUE(max(byte_t{2}, byte_t{1}) == 2);
    FND_TEST_TRUE(max(byte_t{-1}, byte_t{1}) == 1);
    FND_TEST_TRUE(max(byte_t{5}, byte_t{5}) == 5);
    FND_TEST_TRUE(max(kByteMinValue, kByteMaxValue) == kByteMaxValue);
    FND_TEST_TRUE(max(kByteMaxValue, kByteMinValue) == kByteMaxValue);
}

void unittests_core_arithmetic_max_int()
{
    FND_TEST_TRUE(max(int_t{1}, int_t{2}) == 2);
    FND_TEST_TRUE(max(int_t{2}, int_t{1}) == 2);
    FND_TEST_TRUE(max(int_t{-1}, int_t{1}) == 1);
    FND_TEST_TRUE(max(int_t{5}, int_t{5}) == 5);
    FND_TEST_TRUE(max(kIntMinValue, kIntMaxValue) == kIntMaxValue);
    FND_TEST_TRUE(max(kIntMaxValue, kIntMinValue) == kIntMaxValue);
}

void unittests_core_arithmetic_max_long()
{
    FND_TEST_TRUE(max(long_t{1}, long_t{2}) == 2);
    FND_TEST_TRUE(max(long_t{2}, long_t{1}) == 2);
    FND_TEST_TRUE(max(long_t{-1}, long_t{1}) == 1);
    FND_TEST_TRUE(max(long_t{5}, long_t{5}) == 5);
    FND_TEST_TRUE(max(kLongMinValue, kLongMaxValue) == kLongMaxValue);
    FND_TEST_TRUE(max(kLongMaxValue, kLongMinValue) == kLongMaxValue);
}

void unittests_core_arithmetic_max_ubyte()
{
    FND_TEST_TRUE(max(ubyte_t{1}, ubyte_t{2}) == 2);
    FND_TEST_TRUE(max(ubyte_t{2}, ubyte_t{1}) == 2);
    FND_TEST_TRUE(max(ubyte_t{5}, ubyte_t{5}) == 5);
    FND_TEST_TRUE(max(kUByteMinValue, kUByteMaxValue) == kUByteMaxValue);
    FND_TEST_TRUE(max(kUByteMaxValue, kUByteMinValue) == kUByteMaxValue);
}

void unittests_core_arithmetic_max_uint()
{
    FND_TEST_TRUE(max(uint_t{1}, uint_t{2}) == 2);
    FND_TEST_TRUE(max(uint_t{2}, uint_t{1}) == 2);
    FND_TEST_TRUE(max(uint_t{5}, uint_t{5}) == 5);
    FND_TEST_TRUE(max(kUIntMinValue, kUIntMaxValue) == kUIntMaxValue);
    FND_TEST_TRUE(max(kUIntMaxValue, kUIntMinValue) == kUIntMaxValue);
}

void unittests_core_arithmetic_max_ulong()
{
    FND_TEST_TRUE(max(ulong_t{1}, ulong_t{2}) == 2);
    FND_TEST_TRUE(max(ulong_t{2}, ulong_t{1}) == 2);
    FND_TEST_TRUE(max(ulong_t{5}, ulong_t{5}) == 5);
    FND_TEST_TRUE(max(kULongMinValue, kULongMaxValue) == kULongMaxValue);
    FND_TEST_TRUE(max(kULongMaxValue, kULongMinValue) == kULongMaxValue);
}

void unittests_core_arithmetic_max_float()
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

void unittests_core_arithmetic_max_double()
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

void unittests_core_arithmetic_clamp_byte()
{
    FND_TEST_TRUE(clamp(byte_t{5}, byte_t{-10}, byte_t{10}) == 5);
    FND_TEST_TRUE(clamp(byte_t{-20}, byte_t{-10}, byte_t{10}) == -10);
    FND_TEST_TRUE(clamp(byte_t{20}, byte_t{-10}, byte_t{10}) == 10);
    FND_TEST_TRUE(clamp(byte_t{-10}, byte_t{-10}, byte_t{10}) == -10);
    FND_TEST_TRUE(clamp(byte_t{10}, byte_t{-10}, byte_t{10}) == 10);
    FND_TEST_TRUE(clamp(byte_t{20}, byte_t{3}, byte_t{3}) == 3);
    FND_TEST_TRUE(clamp(kByteMinValue, kByteMinValue, kByteMaxValue) == kByteMinValue);
    FND_TEST_TRUE(clamp(kByteMaxValue, kByteMinValue, kByteMaxValue) == kByteMaxValue);
}

void unittests_core_arithmetic_clamp_int()
{
    FND_TEST_TRUE(clamp(int_t{5}, int_t{-10}, int_t{10}) == 5);
    FND_TEST_TRUE(clamp(int_t{-20}, int_t{-10}, int_t{10}) == -10);
    FND_TEST_TRUE(clamp(int_t{20}, int_t{-10}, int_t{10}) == 10);
    FND_TEST_TRUE(clamp(int_t{-10}, int_t{-10}, int_t{10}) == -10);
    FND_TEST_TRUE(clamp(int_t{10}, int_t{-10}, int_t{10}) == 10);
    FND_TEST_TRUE(clamp(int_t{20}, int_t{3}, int_t{3}) == 3);
    FND_TEST_TRUE(clamp(kIntMinValue, kIntMinValue, kIntMaxValue) == kIntMinValue);
    FND_TEST_TRUE(clamp(kIntMaxValue, kIntMinValue, kIntMaxValue) == kIntMaxValue);
}

void unittests_core_arithmetic_clamp_long()
{
    FND_TEST_TRUE(clamp(long_t{5}, long_t{-10}, long_t{10}) == 5);
    FND_TEST_TRUE(clamp(long_t{-20}, long_t{-10}, long_t{10}) == -10);
    FND_TEST_TRUE(clamp(long_t{20}, long_t{-10}, long_t{10}) == 10);
    FND_TEST_TRUE(clamp(long_t{-10}, long_t{-10}, long_t{10}) == -10);
    FND_TEST_TRUE(clamp(long_t{10}, long_t{-10}, long_t{10}) == 10);
    FND_TEST_TRUE(clamp(long_t{20}, long_t{3}, long_t{3}) == 3);
    FND_TEST_TRUE(clamp(kLongMinValue, kLongMinValue, kLongMaxValue) == kLongMinValue);
    FND_TEST_TRUE(clamp(kLongMaxValue, kLongMinValue, kLongMaxValue) == kLongMaxValue);
}

void unittests_core_arithmetic_clamp_ubyte()
{
    FND_TEST_TRUE(clamp(ubyte_t{5}, ubyte_t{2}, ubyte_t{10}) == 5);
    FND_TEST_TRUE(clamp(ubyte_t{0}, ubyte_t{2}, ubyte_t{10}) == 2);
    FND_TEST_TRUE(clamp(ubyte_t{20}, ubyte_t{2}, ubyte_t{10}) == 10);
    FND_TEST_TRUE(clamp(ubyte_t{2}, ubyte_t{2}, ubyte_t{10}) == 2);
    FND_TEST_TRUE(clamp(ubyte_t{10}, ubyte_t{2}, ubyte_t{10}) == 10);
    FND_TEST_TRUE(clamp(ubyte_t{20}, ubyte_t{3}, ubyte_t{3}) == 3);
    FND_TEST_TRUE(clamp(kUByteMinValue, kUByteMinValue, kUByteMaxValue) == kUByteMinValue);
    FND_TEST_TRUE(clamp(kUByteMaxValue, kUByteMinValue, kUByteMaxValue) == kUByteMaxValue);
}

void unittests_core_arithmetic_clamp_uint()
{
    FND_TEST_TRUE(clamp(uint_t{5}, uint_t{2}, uint_t{10}) == 5);
    FND_TEST_TRUE(clamp(uint_t{0}, uint_t{2}, uint_t{10}) == 2);
    FND_TEST_TRUE(clamp(uint_t{20}, uint_t{2}, uint_t{10}) == 10);
    FND_TEST_TRUE(clamp(uint_t{2}, uint_t{2}, uint_t{10}) == 2);
    FND_TEST_TRUE(clamp(uint_t{10}, uint_t{2}, uint_t{10}) == 10);
    FND_TEST_TRUE(clamp(uint_t{20}, uint_t{3}, uint_t{3}) == 3);
    FND_TEST_TRUE(clamp(kUIntMinValue, kUIntMinValue, kUIntMaxValue) == kUIntMinValue);
    FND_TEST_TRUE(clamp(kUIntMaxValue, kUIntMinValue, kUIntMaxValue) == kUIntMaxValue);
}

void unittests_core_arithmetic_clamp_ulong()
{
    FND_TEST_TRUE(clamp(ulong_t{5}, ulong_t{2}, ulong_t{10}) == 5);
    FND_TEST_TRUE(clamp(ulong_t{0}, ulong_t{2}, ulong_t{10}) == 2);
    FND_TEST_TRUE(clamp(ulong_t{20}, ulong_t{2}, ulong_t{10}) == 10);
    FND_TEST_TRUE(clamp(ulong_t{2}, ulong_t{2}, ulong_t{10}) == 2);
    FND_TEST_TRUE(clamp(ulong_t{10}, ulong_t{2}, ulong_t{10}) == 10);
    FND_TEST_TRUE(clamp(ulong_t{20}, ulong_t{3}, ulong_t{3}) == 3);
    FND_TEST_TRUE(clamp(kULongMinValue, kULongMinValue, kULongMaxValue) == kULongMinValue);
    FND_TEST_TRUE(clamp(kULongMaxValue, kULongMinValue, kULongMaxValue) == kULongMaxValue);
}

void unittests_core_arithmetic_clamp_float()
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

void unittests_core_arithmetic_clamp_double()
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

void unittests_core_arithmetic_saturate_float()
{
    FND_TEST_TRUE(saturate(-1.0f) == 0.0f);
    FND_TEST_TRUE(saturate(0.0f) == 0.0f);
    FND_TEST_TRUE(saturate(0.25f) == 0.25f);
    FND_TEST_TRUE(saturate(1.0f) == 1.0f);
    FND_TEST_TRUE(saturate(2.0f) == 1.0f);
    FND_TEST_TRUE(saturate(kFloatInfinity) == 1.0f);
    FND_TEST_TRUE(saturate(-kFloatInfinity) == 0.0f);
}

void unittests_core_arithmetic_saturate_double()
{
    FND_TEST_TRUE(saturate(-1.0) == 0.0);
    FND_TEST_TRUE(saturate(0.0) == 0.0);
    FND_TEST_TRUE(saturate(0.25) == 0.25);
    FND_TEST_TRUE(saturate(1.0) == 1.0);
    FND_TEST_TRUE(saturate(2.0) == 1.0);
    FND_TEST_TRUE(saturate(kDoubleInfinity) == 1.0);
    FND_TEST_TRUE(saturate(-kDoubleInfinity) == 0.0);
}

void unittests_core_arithmetic_sign_byte()
{
    FND_TEST_TRUE(sign(byte_t{0}) == 0);
    FND_TEST_TRUE(sign(byte_t{5}) == 1);
    FND_TEST_TRUE(sign(byte_t{-5}) == -1);
    FND_TEST_TRUE(sign(kByteMaxValue) == 1);
    FND_TEST_TRUE(sign(kByteMinValue) == -1);
}

void unittests_core_arithmetic_sign_int()
{
    FND_TEST_TRUE(sign(int_t{0}) == 0);
    FND_TEST_TRUE(sign(int_t{5}) == 1);
    FND_TEST_TRUE(sign(int_t{-5}) == -1);
    FND_TEST_TRUE(sign(kIntMaxValue) == 1);
    FND_TEST_TRUE(sign(kIntMinValue) == -1);
}

void unittests_core_arithmetic_sign_long()
{
    FND_TEST_TRUE(sign(long_t{0}) == 0);
    FND_TEST_TRUE(sign(long_t{5}) == 1);
    FND_TEST_TRUE(sign(long_t{-5}) == -1);
    FND_TEST_TRUE(sign(kLongMaxValue) == 1);
    FND_TEST_TRUE(sign(kLongMinValue) == -1);
}

void unittests_core_arithmetic_sign_float()
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

void unittests_core_arithmetic_sign_double()
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

void unittests_core_arithmetic_ceil_float()
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

void unittests_core_arithmetic_ceil_double()
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

void unittests_core_arithmetic_floor_float()
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

void unittests_core_arithmetic_floor_double()
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

void unittests_core_arithmetic_trunc_float()
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

void unittests_core_arithmetic_trunc_double()
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

void unittests_core_arithmetic_fmod_float()
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

void unittests_core_arithmetic_fmod_double()
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

void unittests_core_arithmetic_modf_float()
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

void unittests_core_arithmetic_modf_double()
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

void unittests_core_arithmetic_fractional_float()
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

void unittests_core_arithmetic_fractional_double()
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

void unittests_core_arithmetic()
{
    unittests_core_arithmetic_bit_cast_int_to_float();
    unittests_core_arithmetic_bit_cast_uint_to_float();
    unittests_core_arithmetic_bit_cast_float_to_int();
    unittests_core_arithmetic_bit_cast_uint_to_int();
    unittests_core_arithmetic_bit_cast_float_to_uint();
    unittests_core_arithmetic_bit_cast_int_to_uint();
    unittests_core_arithmetic_bit_cast_long_to_double();
    unittests_core_arithmetic_bit_cast_ulong_to_double();
    unittests_core_arithmetic_bit_cast_double_to_long();
    unittests_core_arithmetic_bit_cast_ulong_to_long();
    unittests_core_arithmetic_bit_cast_double_to_ulong();
    unittests_core_arithmetic_bit_cast_long_to_ulong();
    unittests_core_arithmetic_abs_integer_types();
    unittests_core_arithmetic_abs_float_types();
    unittests_core_arithmetic_isfinite_float();
    unittests_core_arithmetic_isfinite_double();
    unittests_core_arithmetic_isinf_float();
    unittests_core_arithmetic_isinf_double();
    unittests_core_arithmetic_isnan_float();
    unittests_core_arithmetic_isnan_double();
    unittests_core_arithmetic_approx_equal_float();
    unittests_core_arithmetic_approx_equal_double();
    unittests_core_arithmetic_min_byte();
    unittests_core_arithmetic_min_int();
    unittests_core_arithmetic_min_long();
    unittests_core_arithmetic_min_ubyte();
    unittests_core_arithmetic_min_uint();
    unittests_core_arithmetic_min_ulong();
    unittests_core_arithmetic_min_float();
    unittests_core_arithmetic_min_double();
    unittests_core_arithmetic_max_byte();
    unittests_core_arithmetic_max_int();
    unittests_core_arithmetic_max_long();
    unittests_core_arithmetic_max_ubyte();
    unittests_core_arithmetic_max_uint();
    unittests_core_arithmetic_max_ulong();
    unittests_core_arithmetic_max_float();
    unittests_core_arithmetic_max_double();
    unittests_core_arithmetic_clamp_byte();
    unittests_core_arithmetic_clamp_int();
    unittests_core_arithmetic_clamp_long();
    unittests_core_arithmetic_clamp_ubyte();
    unittests_core_arithmetic_clamp_uint();
    unittests_core_arithmetic_clamp_ulong();
    unittests_core_arithmetic_clamp_float();
    unittests_core_arithmetic_clamp_double();
    unittests_core_arithmetic_saturate_float();
    unittests_core_arithmetic_saturate_double();
    unittests_core_arithmetic_sign_byte();
    unittests_core_arithmetic_sign_int();
    unittests_core_arithmetic_sign_long();
    unittests_core_arithmetic_sign_float();
    unittests_core_arithmetic_sign_double();
    unittests_core_arithmetic_ceil_float();
    unittests_core_arithmetic_ceil_double();
    unittests_core_arithmetic_floor_float();
    unittests_core_arithmetic_floor_double();
    unittests_core_arithmetic_trunc_float();
    unittests_core_arithmetic_trunc_double();
    unittests_core_arithmetic_fmod_float();
    unittests_core_arithmetic_fmod_double();
    unittests_core_arithmetic_modf_float();
    unittests_core_arithmetic_modf_double();
    unittests_core_arithmetic_fractional_float();
    unittests_core_arithmetic_fractional_double();
}

} // namespace fnd::unittests
