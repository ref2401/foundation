module;
#include "foundation/unittests.h"


export module unittests.math:vector_conversion;
import foundation.core;
import foundation.math;

namespace fnd::unittests {

export void unittests_math_vector_conversion();

// NOTE:
// Floats hold every integer up to 2^24 exactly. Above that they are 2 apart
// (up to 2^25), and an odd integer rounds to the neighbour with an even
// significand: 16777217 -> 16777216 and 16777219 -> 16777220.

void unittests_math_vector_conversion_can_trunc_to_int()
{
    // Each component is checked on its own, as for the float_t overload:
    // -2^31 <= x < 2^31.
    FND_TEST_TRUE(all(can_trunc_to_int(float2_t{-0x1p31f, 0x1.fffffep30f})));
    FND_TEST_TRUE(all(can_trunc_to_int(float2_t{0x1p31f, -2.75f})
        == bool2_t{false, true}));
    FND_TEST_TRUE(all(can_trunc_to_int(float2_t{0.0f, kFloatNaN})
        == bool2_t{true, false}));

    FND_TEST_TRUE(
        all(can_trunc_to_int(float3_t{-0x1p31f, 0x1.fffffep30f, -0.0f})));
    FND_TEST_TRUE(all(can_trunc_to_int(float3_t{kFloatInfinity, 1.0f, 1.0f})
        == bool3_t{false, true, true}));
    FND_TEST_TRUE(all(can_trunc_to_int(float3_t{1.0f, -0x1.000002p31f, 1.0f})
        == bool3_t{true, false, true}));
    FND_TEST_TRUE(all(can_trunc_to_int(float3_t{1.0f, 1.0f, kFloatNaN})
        == bool3_t{true, true, false}));

    FND_TEST_TRUE(all(
        can_trunc_to_int(float4_t{-0x1p31f, 0x1.fffffep30f, -0.0f, 1e9f})));
    FND_TEST_TRUE(
        all(can_trunc_to_int(float4_t{kFloatNaN, 1.0f, 1.0f, 1.0f})
            == bool4_t{false, true, true, true}));
    FND_TEST_TRUE(
        all(can_trunc_to_int(float4_t{1.0f, -kFloatInfinity, 1.0f, 1.0f})
            == bool4_t{true, false, true, true}));
    FND_TEST_TRUE(
        all(can_trunc_to_int(float4_t{1.0f, 1.0f, kFloatMaxValue, 1.0f})
            == bool4_t{true, true, false, true}));
    FND_TEST_TRUE(all(can_trunc_to_int(float4_t{1.0f, 1.0f, 1.0f, 0x1p31f})
        == bool4_t{true, true, true, false}));
}

void unittests_math_vector_conversion_can_trunc_to_uint()
{
    // Each component is checked on its own, as for the float_t overload:
    // 0 <= x < 2^32.
    FND_TEST_TRUE(all(can_trunc_to_uint(float2_t{0.0f, 0x1.fffffep31f})));
    FND_TEST_TRUE(all(can_trunc_to_uint(float2_t{-0.5f, 2.75f})
        == bool2_t{false, true}));
    FND_TEST_TRUE(all(can_trunc_to_uint(float2_t{-0.0f, 0x1p32f})
        == bool2_t{true, false}));

    FND_TEST_TRUE(
        all(can_trunc_to_uint(float3_t{0.0f, 0x1.fffffep31f, -0.0f})));
    FND_TEST_TRUE(all(can_trunc_to_uint(float3_t{kFloatNaN, 1.0f, 1.0f})
        == bool3_t{false, true, true}));
    FND_TEST_TRUE(all(can_trunc_to_uint(float3_t{1.0f, -1.0f, 1.0f})
        == bool3_t{true, false, true}));
    FND_TEST_TRUE(all(can_trunc_to_uint(float3_t{1.0f, 1.0f, kFloatInfinity})
        == bool3_t{true, true, false}));

    FND_TEST_TRUE(all(
        can_trunc_to_uint(float4_t{0.0f, 0x1.fffffep31f, -0.0f, 1e9f})));
    FND_TEST_TRUE(
        all(can_trunc_to_uint(float4_t{-kFloatMinSubnormal, 1.0f, 1.0f, 1.0f})
            == bool4_t{false, true, true, true}));
    FND_TEST_TRUE(all(can_trunc_to_uint(float4_t{1.0f, kFloatNaN, 1.0f, 1.0f})
        == bool4_t{true, false, true, true}));
    FND_TEST_TRUE(
        all(can_trunc_to_uint(float4_t{1.0f, 1.0f, kFloatMaxValue, 1.0f})
            == bool4_t{true, true, false, true}));
    FND_TEST_TRUE(all(can_trunc_to_uint(float4_t{1.0f, 1.0f, 1.0f, 0x1p32f})
        == bool4_t{true, true, true, false}));
}

void unittests_math_vector_conversion_float2()
{
    // From an int2_t.
    FND_TEST_TRUE(all(float2(int2_t{0, 1}) == float2_t{0.0f, 1.0f}));
    FND_TEST_TRUE(all(float2(int2_t{-7, 123}) == float2_t{-7.0f, 123.0f}));
    FND_TEST_TRUE(all(float2(int2_t{kIntMinValue, kIntMaxValue})
        == float2_t{-0x1p31f, 0x1p31f}));
    FND_TEST_TRUE(all(float2(int2_t{16777216, 16777217})
        == float2_t{16777216.0f, 16777216.0f}));
    FND_TEST_TRUE(all(float2(int2_t{-16777217, 16777219})
        == float2_t{-16777216.0f, 16777220.0f}));
    // Up to 2^24 the round trip gives back the same value.
    const int2_t iv{16777216, -12345};
    FND_TEST_TRUE(all(int2(float2(iv)) == iv));

    // From a uint2_t.
    FND_TEST_TRUE(all(float2(uint2_t{0u, 7u}) == float2_t{0.0f, 7.0f}));
    FND_TEST_TRUE(all(float2(uint2_t{kUIntMaxValue, 0x80000000u})
        == float2_t{0x1p32f, 0x1p31f}));
    FND_TEST_TRUE(all(float2(uint2_t{16777217u, 16777219u})
        == float2_t{16777216.0f, 16777220.0f}));
    const uint2_t uv{16777216u, 12345u};
    FND_TEST_TRUE(all(uint2(float2(uv)) == uv));
}

void unittests_math_vector_conversion_float3()
{
    // From an int3_t.
    FND_TEST_TRUE(
        all(float3(int3_t{-1, 0, 1}) == float3_t{-1.0f, 0.0f, 1.0f}));
    FND_TEST_TRUE(all(float3(int3_t{kIntMinValue, kIntMaxValue, 16777217})
        == float3_t{-0x1p31f, 0x1p31f, 16777216.0f}));
    const int3_t iv{16777216, -12345, 678};
    FND_TEST_TRUE(all(int3(float3(iv)) == iv));

    // From a uint3_t.
    FND_TEST_TRUE(
        all(float3(uint3_t{0u, 7u, 123u}) == float3_t{0.0f, 7.0f, 123.0f}));
    FND_TEST_TRUE(all(float3(uint3_t{kUIntMaxValue, 0x80000000u, 16777219u})
        == float3_t{0x1p32f, 0x1p31f, 16777220.0f}));
    const uint3_t uv{16777216u, 12345u, 678u};
    FND_TEST_TRUE(all(uint3(float3(uv)) == uv));
}

void unittests_math_vector_conversion_float4()
{
    // From an int4_t.
    FND_TEST_TRUE(all(
        float4(int4_t{-1, 0, 1, 123}) == float4_t{-1.0f, 0.0f, 1.0f, 123.0f}));
    FND_TEST_TRUE(
        all(float4(int4_t{kIntMinValue, kIntMaxValue, 16777217, -16777219})
            == float4_t{-0x1p31f, 0x1p31f, 16777216.0f, -16777220.0f}));
    const int4_t iv{16777216, -12345, 678, -16777216};
    FND_TEST_TRUE(all(int4(float4(iv)) == iv));

    // From a uint4_t.
    FND_TEST_TRUE(all(float4(uint4_t{0u, 7u, 123u, 16777216u})
        == float4_t{0.0f, 7.0f, 123.0f, 16777216.0f}));
    FND_TEST_TRUE(
        all(float4(uint4_t{kUIntMaxValue, 0x80000000u, 16777217u, 16777219u})
            == float4_t{0x1p32f, 0x1p31f, 16777216.0f, 16777220.0f}));
    const uint4_t uv{16777216u, 12345u, 678u, 0u};
    FND_TEST_TRUE(all(uint4(float4(uv)) == uv));
}

void unittests_math_vector_conversion_int2()
{
    // From a float2_t: truncates toward zero.
    FND_TEST_TRUE(all(int2(float2_t{2.75f, -2.75f}) == int2_t{2, -2}));
    FND_TEST_TRUE(all(int2(float2_t{0.5f, -0.5f}) == int2_t{0, 0}));
    FND_TEST_TRUE(all(int2(float2_t{-0.0f, 0.999f}) == int2_t{0, 0}));
    FND_TEST_TRUE(
        all(int2(float2_t{1e9f, -1e9f}) == int2_t{1000000000, -1000000000}));
    // The edges of the valid range: -2^31 and the largest float below 2^31.
    FND_TEST_TRUE(all(int2(float2_t{-0x1p31f, 0x1.fffffep30f})
        == int2_t{kIntMinValue, 2147483520}));

    // From a uint2_t.
    FND_TEST_TRUE(all(int2(uint2_t{0u, 7u}) == int2_t{0, 7}));
    FND_TEST_TRUE(all(int2(uint2_t{static_cast<uint_t>(kIntMaxValue), 123u})
        == int2_t{kIntMaxValue, 123}));
    const int2_t iv{0, kIntMaxValue};
    FND_TEST_TRUE(all(int2(uint2(iv)) == iv));
}

void unittests_math_vector_conversion_int3()
{
    // From a float3_t: truncates toward zero.
    FND_TEST_TRUE(
        all(int3(float3_t{2.75f, -2.75f, 0.5f}) == int3_t{2, -2, 0}));
    FND_TEST_TRUE(all(int3(float3_t{-0.5f, -0.0f, 1e9f})
        == int3_t{0, 0, 1000000000}));
    FND_TEST_TRUE(all(int3(float3_t{-0x1p31f, 0x1.fffffep30f, -1.5f})
        == int3_t{kIntMinValue, 2147483520, -1}));

    // From a uint3_t.
    FND_TEST_TRUE(all(int3(uint3_t{0u, 7u, 123u}) == int3_t{0, 7, 123}));
    FND_TEST_TRUE(
        all(int3(uint3_t{static_cast<uint_t>(kIntMaxValue), 1u, 0u})
            == int3_t{kIntMaxValue, 1, 0}));
    const int3_t iv{0, kIntMaxValue, 678};
    FND_TEST_TRUE(all(int3(uint3(iv)) == iv));
}

void unittests_math_vector_conversion_int4()
{
    // From a float4_t: truncates toward zero.
    FND_TEST_TRUE(all(int4(float4_t{2.75f, -2.75f, 0.5f, -0.5f})
        == int4_t{2, -2, 0, 0}));
    FND_TEST_TRUE(all(int4(float4_t{-0.0f, 0.999f, 1e9f, -1e9f})
        == int4_t{0, 0, 1000000000, -1000000000}));
    FND_TEST_TRUE(all(int4(float4_t{-0x1p31f, 0x1.fffffep30f, -1.5f, 1.5f})
        == int4_t{kIntMinValue, 2147483520, -1, 1}));

    // From a uint4_t.
    FND_TEST_TRUE(
        all(int4(uint4_t{0u, 7u, 123u, 1u}) == int4_t{0, 7, 123, 1}));
    FND_TEST_TRUE(
        all(int4(uint4_t{static_cast<uint_t>(kIntMaxValue), 1u, 0u, 2u})
            == int4_t{kIntMaxValue, 1, 0, 2}));
    const int4_t iv{0, kIntMaxValue, 678, 1};
    FND_TEST_TRUE(all(int4(uint4(iv)) == iv));
}

void unittests_math_vector_conversion_uint2()
{
    // From a float2_t: truncates toward zero.
    FND_TEST_TRUE(all(uint2(float2_t{2.75f, 0.5f}) == uint2_t{2u, 0u}));
    FND_TEST_TRUE(all(uint2(float2_t{0.999f, -0.0f}) == uint2_t{0u, 0u}));
    // The upper edge of the valid range: the largest float below 2^32.
    FND_TEST_TRUE(all(uint2(float2_t{0x1.fffffep31f, 1e9f})
        == uint2_t{4294967040u, 1000000000u}));

    // From an int2_t.
    FND_TEST_TRUE(all(uint2(int2_t{0, 7}) == uint2_t{0u, 7u}));
    FND_TEST_TRUE(
        all(uint2(int2_t{kIntMaxValue, 123}) == uint2_t{2147483647u, 123u}));
    const uint2_t uv{0u, 2147483647u};
    FND_TEST_TRUE(all(uint2(int2(uv)) == uv));
}

void unittests_math_vector_conversion_uint3()
{
    // From a float3_t: truncates toward zero.
    FND_TEST_TRUE(
        all(uint3(float3_t{2.75f, 0.5f, 0.999f}) == uint3_t{2u, 0u, 0u}));
    FND_TEST_TRUE(all(uint3(float3_t{0x1.fffffep31f, 1e9f, -0.0f})
        == uint3_t{4294967040u, 1000000000u, 0u}));

    // From an int3_t.
    FND_TEST_TRUE(all(uint3(int3_t{0, 7, 123}) == uint3_t{0u, 7u, 123u}));
    FND_TEST_TRUE(all(uint3(int3_t{kIntMaxValue, 1, 0})
        == uint3_t{2147483647u, 1u, 0u}));
    const uint3_t uv{0u, 2147483647u, 678u};
    FND_TEST_TRUE(all(uint3(int3(uv)) == uv));
}

void unittests_math_vector_conversion_uint4()
{
    // From a float4_t: truncates toward zero.
    FND_TEST_TRUE(all(uint4(float4_t{2.75f, 0.5f, 0.999f, -0.0f})
        == uint4_t{2u, 0u, 0u, 0u}));
    FND_TEST_TRUE(all(uint4(float4_t{0x1.fffffep31f, 1e9f, 1.5f, 0.999f})
        == uint4_t{4294967040u, 1000000000u, 1u, 0u}));

    // From an int4_t.
    FND_TEST_TRUE(
        all(uint4(int4_t{0, 7, 123, 1}) == uint4_t{0u, 7u, 123u, 1u}));
    FND_TEST_TRUE(all(uint4(int4_t{kIntMaxValue, 1, 0, 2})
        == uint4_t{2147483647u, 1u, 0u, 2u}));
    const uint4_t uv{0u, 2147483647u, 678u, 1u};
    FND_TEST_TRUE(all(uint4(int4(uv)) == uv));
}

void unittests_math_vector_conversion()
{
    unittests_math_vector_conversion_can_trunc_to_int();
    unittests_math_vector_conversion_can_trunc_to_uint();
    unittests_math_vector_conversion_float2();
    unittests_math_vector_conversion_float3();
    unittests_math_vector_conversion_float4();
    unittests_math_vector_conversion_int2();
    unittests_math_vector_conversion_int3();
    unittests_math_vector_conversion_int4();
    unittests_math_vector_conversion_uint2();
    unittests_math_vector_conversion_uint3();
    unittests_math_vector_conversion_uint4();
}

} // namespace fnd::unittests
