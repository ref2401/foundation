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

void unittests_math_vector_conversion_bool2()
{
    // From a bool3_t or bool4_t: keeps x and y.
    const bool3_t v3{true, false, true};
    const bool4_t v4{true, false, true, false};
    FND_TEST_TRUE(all(bool2(v3) == bool2_t{true, false}));
    FND_TEST_TRUE(all(bool2(v4) == bool2_t{true, false}));

    // Any nonzero value is true: negative values, infinity and subnormals
    // included; -0.0f is false.
    FND_TEST_TRUE(all(bool2(-5, 0) == bool2_t{true, false}));
    FND_TEST_TRUE(all(bool2(-0.0f, -1.5f) == bool2_t{false, true}));
    FND_TEST_TRUE(all(bool2(-kFloatInfinity, kFloatMinSubnormal)
        == bool2_t{true, true}));
    FND_TEST_TRUE(all(bool2(kUIntMaxValue, 0u) == bool2_t{true, false}));

    // Every overload: splat, components and vectors of every element
    // type.
    FND_TEST_TRUE(all(bool2(true) == bool2_t{true, true}));
    FND_TEST_TRUE(all(bool2(true, false) == bool2_t{true, false}));
    FND_TEST_TRUE(
        all(bool2(bool3_t{true, false, true}) == bool2_t{true, false}));
    FND_TEST_TRUE(
        all(bool2(bool4_t{true, false, true, true}) == bool2_t{true, false}));
    FND_TEST_TRUE(all(bool2(3.75f) == bool2_t{true, true}));
    FND_TEST_TRUE(all(bool2(3.75f, 0.0f) == bool2_t{true, false}));
    FND_TEST_TRUE(all(bool2(float2_t{3.75f, 0.0f}) == bool2_t{true, false}));
    FND_TEST_TRUE(
        all(bool2(float3_t{3.75f, 0.0f, 7.25f}) == bool2_t{true, false}));
    FND_TEST_TRUE(
        all(bool2(float4_t{3.75f, 0.0f, 7.25f, 1.5f}) == bool2_t{true, false}));
    FND_TEST_TRUE(all(bool2(3) == bool2_t{true, true}));
    FND_TEST_TRUE(all(bool2(3, 0) == bool2_t{true, false}));
    FND_TEST_TRUE(all(bool2(int2_t{3, 0}) == bool2_t{true, false}));
    FND_TEST_TRUE(all(bool2(int3_t{3, 0, 7}) == bool2_t{true, false}));
    FND_TEST_TRUE(all(bool2(int4_t{3, 0, 7, 1}) == bool2_t{true, false}));
    FND_TEST_TRUE(all(bool2(3u) == bool2_t{true, true}));
    FND_TEST_TRUE(all(bool2(3u, 0u) == bool2_t{true, false}));
    FND_TEST_TRUE(all(bool2(uint2_t{3, 0}) == bool2_t{true, false}));
    FND_TEST_TRUE(all(bool2(uint3_t{3, 0, 7}) == bool2_t{true, false}));
    FND_TEST_TRUE(all(bool2(uint4_t{3, 0, 7, 1}) == bool2_t{true, false}));

}

void unittests_math_vector_conversion_bool3()
{
    // From a bool2_t: z defaults to false.
    const bool2_t v2{true, false};
    FND_TEST_TRUE(all(bool3(v2) == bool3_t{true, false, false}));
    FND_TEST_TRUE(all(bool3(v2, true) == bool3_t{true, false, true}));
    FND_TEST_TRUE(all(bool2(bool3(v2)) == v2));

    // From a bool4_t: keeps x, y and z.
    const bool4_t v4{true, false, true, false};
    FND_TEST_TRUE(all(bool3(v4) == bool3_t{true, false, true}));

    // Every overload: splat, components and vectors of every element
    // type.
    FND_TEST_TRUE(all(bool3(true) == bool3_t{true, true, true}));
    FND_TEST_TRUE(all(bool3(true, false, true) == bool3_t{true, false, true}));
    FND_TEST_TRUE(
        all(bool3(bool2_t{true, false}, true) == bool3_t{true, false, true}));
    FND_TEST_TRUE(
        all(bool3(bool2_t{true, false}) == bool3_t{true, false, false}));
    FND_TEST_TRUE(all(bool3(bool4_t{true, false, true, true})
        == bool3_t{true, false, true}));
    FND_TEST_TRUE(all(bool3(3.75f) == bool3_t{true, true, true}));
    FND_TEST_TRUE(all(bool3(3.75f, 0.0f, 7.25f) == bool3_t{true, false, true}));
    FND_TEST_TRUE(
        all(bool3(float2_t{3.75f, 0.0f}, 7.25f) == bool3_t{true, false, true}));
    FND_TEST_TRUE(
        all(bool3(float2_t{3.75f, 0.0f}) == bool3_t{true, false, false}));
    FND_TEST_TRUE(
        all(bool3(float3_t{3.75f, 0.0f, 7.25f}) == bool3_t{true, false, true}));
    FND_TEST_TRUE(all(bool3(float4_t{3.75f, 0.0f, 7.25f, 1.5f})
        == bool3_t{true, false, true}));
    FND_TEST_TRUE(all(bool3(3) == bool3_t{true, true, true}));
    FND_TEST_TRUE(all(bool3(3, 0, 7) == bool3_t{true, false, true}));
    FND_TEST_TRUE(all(bool3(int2_t{3, 0}, 7) == bool3_t{true, false, true}));
    FND_TEST_TRUE(all(bool3(int2_t{3, 0}) == bool3_t{true, false, false}));
    FND_TEST_TRUE(all(bool3(int3_t{3, 0, 7}) == bool3_t{true, false, true}));
    FND_TEST_TRUE(all(bool3(int4_t{3, 0, 7, 1}) == bool3_t{true, false, true}));
    FND_TEST_TRUE(all(bool3(3u) == bool3_t{true, true, true}));
    FND_TEST_TRUE(all(bool3(3u, 0u, 7u) == bool3_t{true, false, true}));
    FND_TEST_TRUE(
        all(bool3(uint2_t{3, 0}, 7u) == bool3_t{true, false, true}));
    FND_TEST_TRUE(all(bool3(uint2_t{3, 0}) == bool3_t{true, false, false}));
    FND_TEST_TRUE(
        all(bool3(uint3_t{3, 0, 7}) == bool3_t{true, false, true}));
    FND_TEST_TRUE(
        all(bool3(uint4_t{3, 0, 7, 1}) == bool3_t{true, false, true}));

}

void unittests_math_vector_conversion_bool4()
{
    // From a bool2_t: z and w default to false.
    const bool2_t v2{true, false};
    FND_TEST_TRUE(all(bool4(v2) == bool4_t{true, false, false, false}));
    FND_TEST_TRUE(all(bool4(v2, true) == bool4_t{true, false, true, false}));
    FND_TEST_TRUE(
        all(bool4(v2, true, true) == bool4_t{true, false, true, true}));
    FND_TEST_TRUE(all(bool2(bool4(v2)) == v2));

    // From a bool3_t: w defaults to false.
    const bool3_t v3{true, false, true};
    FND_TEST_TRUE(all(bool4(v3) == bool4_t{true, false, true, false}));
    FND_TEST_TRUE(all(bool4(v3, true) == bool4_t{true, false, true, true}));
    FND_TEST_TRUE(all(bool3(bool4(v3)) == v3));

    // Every overload: splat, components and vectors of every element
    // type.
    FND_TEST_TRUE(all(bool4(true) == bool4_t{true, true, true, true}));
    FND_TEST_TRUE(all(bool4(true, false, true, true)
        == bool4_t{true, false, true, true}));
    FND_TEST_TRUE(all(bool4(bool2_t{true, false}, true, true)
        == bool4_t{true, false, true, true}));
    FND_TEST_TRUE(
        all(bool4(bool2_t{true, false}) == bool4_t{true, false, false, false}));
    FND_TEST_TRUE(all(bool4(bool3_t{true, false, true}, true)
        == bool4_t{true, false, true, true}));
    FND_TEST_TRUE(all(bool4(bool3_t{true, false, true})
        == bool4_t{true, false, true, false}));
    FND_TEST_TRUE(all(bool4(3.75f) == bool4_t{true, true, true, true}));
    FND_TEST_TRUE(all(bool4(3.75f, 0.0f, 7.25f, 1.5f)
        == bool4_t{true, false, true, true}));
    FND_TEST_TRUE(all(bool4(float2_t{3.75f, 0.0f}, 7.25f, 1.5f)
        == bool4_t{true, false, true, true}));
    FND_TEST_TRUE(all(bool4(float2_t{3.75f, 0.0f})
        == bool4_t{true, false, false, false}));
    FND_TEST_TRUE(all(bool4(float3_t{3.75f, 0.0f, 7.25f}, 1.5f)
        == bool4_t{true, false, true, true}));
    FND_TEST_TRUE(all(bool4(float3_t{3.75f, 0.0f, 7.25f})
        == bool4_t{true, false, true, false}));
    FND_TEST_TRUE(all(bool4(float4_t{3.75f, 0.0f, 7.25f, 1.5f})
        == bool4_t{true, false, true, true}));
    FND_TEST_TRUE(all(bool4(3) == bool4_t{true, true, true, true}));
    FND_TEST_TRUE(all(bool4(3, 0, 7, 1) == bool4_t{true, false, true, true}));
    FND_TEST_TRUE(
        all(bool4(int2_t{3, 0}, 7, 1) == bool4_t{true, false, true, true}));
    FND_TEST_TRUE(
        all(bool4(int2_t{3, 0}) == bool4_t{true, false, false, false}));
    FND_TEST_TRUE(
        all(bool4(int3_t{3, 0, 7}, 1) == bool4_t{true, false, true, true}));
    FND_TEST_TRUE(
        all(bool4(int3_t{3, 0, 7}) == bool4_t{true, false, true, false}));
    FND_TEST_TRUE(
        all(bool4(int4_t{3, 0, 7, 1}) == bool4_t{true, false, true, true}));
    FND_TEST_TRUE(all(bool4(3u) == bool4_t{true, true, true, true}));
    FND_TEST_TRUE(
        all(bool4(3u, 0u, 7u, 1u) == bool4_t{true, false, true, true}));
    FND_TEST_TRUE(all(bool4(uint2_t{3, 0}, 7u, 1u)
        == bool4_t{true, false, true, true}));
    FND_TEST_TRUE(
        all(bool4(uint2_t{3, 0}) == bool4_t{true, false, false, false}));
    FND_TEST_TRUE(all(bool4(uint3_t{3, 0, 7}, 1u)
        == bool4_t{true, false, true, true}));
    FND_TEST_TRUE(
        all(bool4(uint3_t{3, 0, 7}) == bool4_t{true, false, true, false}));
    FND_TEST_TRUE(all(bool4(uint4_t{3, 0, 7, 1})
        == bool4_t{true, false, true, true}));

}

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
    FND_TEST_TRUE(all(can_trunc_to_uint(float3_t{1, -1, 1})
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
    FND_TEST_TRUE(all(float2(int2_t{0, 1}) == float2_t{0, 1}));
    FND_TEST_TRUE(all(float2(int2_t{-7, 123}) == float2_t{-7, 123}));
    FND_TEST_TRUE(all(float2(int2_t{kIntMinValue, kIntMaxValue})
        == float2_t{-0x1p31f, 0x1p31f}));
    FND_TEST_TRUE(all(float2(int2_t{16777216, 16777217})
        == float2_t{16777216, 16777216}));
    FND_TEST_TRUE(all(float2(int2_t{-16777217, 16777219})
        == float2_t{-16777216.0f, 16777220.0f}));
    // Up to 2^24 the round trip gives back the same value.
    const int2_t iv{16777216, -12345};
    FND_TEST_TRUE(all(int2(float2(iv)) == iv));

    // From a uint2_t.
    FND_TEST_TRUE(all(float2(uint2_t{0, 7}) == float2_t{0, 7}));
    FND_TEST_TRUE(all(float2(uint2_t{kUIntMaxValue, 0x80000000u})
        == float2_t{0x1p32f, 0x1p31f}));
    FND_TEST_TRUE(all(float2(uint2_t{16777217, 16777219})
        == float2_t{16777216.0f, 16777220.0f}));
    const uint2_t uv{16777216, 12345};
    FND_TEST_TRUE(all(uint2(float2(uv)) == uv));

    // From a float3_t or float4_t: keeps x and y.
    const float3_t v3{1.5f, -2.5f, 3.25f};
    const float4_t v4{1.5f, -2.5f, 3.25f, -4.75f};
    FND_TEST_TRUE(all(float2(v3) == float2_t{1.5f, -2.5f}));
    FND_TEST_TRUE(all(float2(v4) == float2_t{1.5f, -2.5f}));

    // Every overload: splat, components and vectors of every element
    // type.
    FND_TEST_TRUE(all(float2(true) == float2_t{1, 1}));
    FND_TEST_TRUE(all(float2(true, false) == float2_t{1, 0}));
    FND_TEST_TRUE(all(float2(bool2_t{true, false}) == float2_t{1, 0}));
    FND_TEST_TRUE(
        all(float2(bool3_t{true, false, true}) == float2_t{1, 0}));
    FND_TEST_TRUE(
        all(float2(bool4_t{true, false, true, true}) == float2_t{1, 0}));
    FND_TEST_TRUE(all(float2(3.75f) == float2_t{3.75f, 3.75f}));
    FND_TEST_TRUE(all(float2(3.75f, 0.0f) == float2_t{3.75f, 0.0f}));
    FND_TEST_TRUE(
        all(float2(float3_t{3.75f, 0.0f, 7.25f}) == float2_t{3.75f, 0.0f}));
    FND_TEST_TRUE(all(float2(float4_t{3.75f, 0.0f, 7.25f, 1.5f})
        == float2_t{3.75f, 0.0f}));
    FND_TEST_TRUE(all(float2(3) == float2_t{3, 3}));
    FND_TEST_TRUE(all(float2(3, 0) == float2_t{3, 0}));
    FND_TEST_TRUE(all(float2(int2_t{3, 0}) == float2_t{3, 0}));
    FND_TEST_TRUE(all(float2(int3_t{3, 0, 7}) == float2_t{3, 0}));
    FND_TEST_TRUE(all(float2(int4_t{3, 0, 7, 1}) == float2_t{3, 0}));
    FND_TEST_TRUE(all(float2(3u) == float2_t{3, 3}));
    FND_TEST_TRUE(all(float2(3u, 0u) == float2_t{3, 0}));
    FND_TEST_TRUE(all(float2(uint2_t{3, 0}) == float2_t{3, 0}));
    FND_TEST_TRUE(all(float2(uint3_t{3, 0, 7}) == float2_t{3, 0}));
    FND_TEST_TRUE(all(float2(uint4_t{3, 0, 7, 1}) == float2_t{3, 0}));

}

void unittests_math_vector_conversion_float3()
{
    // From an int3_t.
    FND_TEST_TRUE(
        all(float3(int3_t{-1, 0, 1}) == float3_t{-1, 0, 1}));
    FND_TEST_TRUE(all(float3(int3_t{kIntMinValue, kIntMaxValue, 16777217})
        == float3_t{-0x1p31f, 0x1p31f, 16777216.0f}));
    const int3_t iv{16777216, -12345, 678};
    FND_TEST_TRUE(all(int3(float3(iv)) == iv));

    // From a uint3_t.
    FND_TEST_TRUE(
        all(float3(uint3_t{0, 7, 123}) == float3_t{0, 7, 123}));
    FND_TEST_TRUE(all(float3(uint3_t{kUIntMaxValue, 0x80000000u, 16777219u})
        == float3_t{0x1p32f, 0x1p31f, 16777220.0f}));
    const uint3_t uv{16777216, 12345, 678};
    FND_TEST_TRUE(all(uint3(float3(uv)) == uv));

    // From a float2_t: z defaults to 0.
    const float2_t v2{1.5f, -2.5f};
    FND_TEST_TRUE(all(float3(v2) == float3_t{1.5f, -2.5f, 0.0f}));
    FND_TEST_TRUE(all(float3(v2, 7.0f) == float3_t{1.5f, -2.5f, 7.0f}));
    FND_TEST_TRUE(all(float2(float3(v2)) == v2));

    // From a float4_t: keeps x, y and z.
    const float4_t v4{1.5f, -2.5f, 3.25f, -4.75f};
    FND_TEST_TRUE(all(float3(v4) == float3_t{1.5f, -2.5f, 3.25f}));

    // Every overload: splat, components and vectors of every element
    // type.
    FND_TEST_TRUE(all(float3(true) == float3_t{1, 1, 1}));
    FND_TEST_TRUE(all(float3(true, false, true) == float3_t{1, 0, 1}));
    FND_TEST_TRUE(
        all(float3(bool2_t{true, false}, true) == float3_t{1, 0, 1}));
    FND_TEST_TRUE(
        all(float3(bool2_t{true, false}) == float3_t{1, 0, 0}));
    FND_TEST_TRUE(
        all(float3(bool3_t{true, false, true}) == float3_t{1, 0, 1}));
    FND_TEST_TRUE(all(float3(bool4_t{true, false, true, true})
        == float3_t{1, 0, 1}));
    FND_TEST_TRUE(all(float3(3.75f) == float3_t{3.75f, 3.75f, 3.75f}));
    FND_TEST_TRUE(
        all(float3(3.75f, 0.0f, 7.25f) == float3_t{3.75f, 0.0f, 7.25f}));
    FND_TEST_TRUE(all(float3(float2_t{3.75f, 0.0f}, 7.25f)
        == float3_t{3.75f, 0.0f, 7.25f}));
    FND_TEST_TRUE(
        all(float3(float2_t{3.75f, 0.0f}) == float3_t{3.75f, 0.0f, 0.0f}));
    FND_TEST_TRUE(all(float3(float4_t{3.75f, 0.0f, 7.25f, 1.5f})
        == float3_t{3.75f, 0.0f, 7.25f}));
    FND_TEST_TRUE(all(float3(3) == float3_t{3, 3, 3}));
    FND_TEST_TRUE(all(float3(3, 0, 7) == float3_t{3, 0, 7}));
    FND_TEST_TRUE(all(float3(int2_t{3, 0}, 7) == float3_t{3, 0, 7}));
    FND_TEST_TRUE(all(float3(int2_t{3, 0}) == float3_t{3, 0, 0}));
    FND_TEST_TRUE(all(float3(int3_t{3, 0, 7}) == float3_t{3, 0, 7}));
    FND_TEST_TRUE(
        all(float3(int4_t{3, 0, 7, 1}) == float3_t{3, 0, 7}));
    FND_TEST_TRUE(all(float3(3u) == float3_t{3, 3, 3}));
    FND_TEST_TRUE(all(float3(3u, 0u, 7u) == float3_t{3, 0, 7}));
    FND_TEST_TRUE(
        all(float3(uint2_t{3, 0}, 7u) == float3_t{3, 0, 7}));
    FND_TEST_TRUE(all(float3(uint2_t{3, 0}) == float3_t{3, 0, 0}));
    FND_TEST_TRUE(
        all(float3(uint3_t{3, 0, 7}) == float3_t{3, 0, 7}));
    FND_TEST_TRUE(
        all(float3(uint4_t{3, 0, 7, 1}) == float3_t{3, 0, 7}));

}

void unittests_math_vector_conversion_float4()
{
    // From an int4_t.
    FND_TEST_TRUE(all(
        float4(int4_t{-1, 0, 1, 123}) == float4_t{-1, 0, 1, 123}));
    FND_TEST_TRUE(
        all(float4(int4_t{kIntMinValue, kIntMaxValue, 16777217, -16777219})
            == float4_t{-0x1p31f, 0x1p31f, 16777216.0f, -16777220.0f}));
    const int4_t iv{16777216, -12345, 678, -16777216};
    FND_TEST_TRUE(all(int4(float4(iv)) == iv));

    // From a uint4_t.
    FND_TEST_TRUE(all(float4(uint4_t{0, 7, 123, 16777216})
        == float4_t{0, 7, 123, 16777216}));
    FND_TEST_TRUE(
        all(float4(uint4_t{kUIntMaxValue, 0x80000000u, 16777217u, 16777219u})
            == float4_t{0x1p32f, 0x1p31f, 16777216.0f, 16777220.0f}));
    const uint4_t uv{16777216, 12345, 678, 0};
    FND_TEST_TRUE(all(uint4(float4(uv)) == uv));

    // From a float2_t: z and w default to 0.
    const float2_t v2{1.5f, -2.5f};
    FND_TEST_TRUE(all(float4(v2) == float4_t{1.5f, -2.5f, 0.0f, 0.0f}));
    FND_TEST_TRUE(all(float4(v2, 7.0f) == float4_t{1.5f, -2.5f, 7.0f, 0.0f}));
    FND_TEST_TRUE(
        all(float4(v2, 7.0f, -8.0f) == float4_t{1.5f, -2.5f, 7.0f, -8.0f}));
    FND_TEST_TRUE(all(float2(float4(v2)) == v2));

    // From a float3_t: w defaults to 0.
    const float3_t v3{1.5f, -2.5f, 3.25f};
    FND_TEST_TRUE(all(float4(v3) == float4_t{1.5f, -2.5f, 3.25f, 0.0f}));
    FND_TEST_TRUE(
        all(float4(v3, -8.0f) == float4_t{1.5f, -2.5f, 3.25f, -8.0f}));
    FND_TEST_TRUE(all(float3(float4(v3)) == v3));

    // Every overload: splat, components and vectors of every element
    // type.
    FND_TEST_TRUE(all(float4(true) == float4_t{1, 1, 1, 1}));
    FND_TEST_TRUE(all(float4(true, false, true, true)
        == float4_t{1, 0, 1, 1}));
    FND_TEST_TRUE(all(float4(bool2_t{true, false}, true, true)
        == float4_t{1, 0, 1, 1}));
    FND_TEST_TRUE(
        all(float4(bool2_t{true, false}) == float4_t{1, 0, 0, 0}));
    FND_TEST_TRUE(all(float4(bool3_t{true, false, true}, true)
        == float4_t{1, 0, 1, 1}));
    FND_TEST_TRUE(all(float4(bool3_t{true, false, true})
        == float4_t{1, 0, 1, 0}));
    FND_TEST_TRUE(all(float4(bool4_t{true, false, true, true})
        == float4_t{1, 0, 1, 1}));
    FND_TEST_TRUE(all(float4(3.75f) == float4_t{3.75f, 3.75f, 3.75f, 3.75f}));
    FND_TEST_TRUE(all(float4(3.75f, 0.0f, 7.25f, 1.5f)
        == float4_t{3.75f, 0.0f, 7.25f, 1.5f}));
    FND_TEST_TRUE(all(float4(float2_t{3.75f, 0.0f}, 7.25f, 1.5f)
        == float4_t{3.75f, 0.0f, 7.25f, 1.5f}));
    FND_TEST_TRUE(all(float4(float2_t{3.75f, 0.0f})
        == float4_t{3.75f, 0.0f, 0.0f, 0.0f}));
    FND_TEST_TRUE(all(float4(float3_t{3.75f, 0.0f, 7.25f}, 1.5f)
        == float4_t{3.75f, 0.0f, 7.25f, 1.5f}));
    FND_TEST_TRUE(all(float4(float3_t{3.75f, 0.0f, 7.25f})
        == float4_t{3.75f, 0.0f, 7.25f, 0.0f}));
    FND_TEST_TRUE(all(float4(3) == float4_t{3, 3, 3, 3}));
    FND_TEST_TRUE(all(float4(3, 0, 7, 1) == float4_t{3, 0, 7, 1}));
    FND_TEST_TRUE(
        all(float4(int2_t{3, 0}, 7, 1) == float4_t{3, 0, 7, 1}));
    FND_TEST_TRUE(
        all(float4(int2_t{3, 0}) == float4_t{3, 0, 0, 0}));
    FND_TEST_TRUE(
        all(float4(int3_t{3, 0, 7}, 1) == float4_t{3, 0, 7, 1}));
    FND_TEST_TRUE(
        all(float4(int3_t{3, 0, 7}) == float4_t{3, 0, 7, 0}));
    FND_TEST_TRUE(
        all(float4(int4_t{3, 0, 7, 1}) == float4_t{3, 0, 7, 1}));
    FND_TEST_TRUE(all(float4(3u) == float4_t{3, 3, 3, 3}));
    FND_TEST_TRUE(
        all(float4(3u, 0u, 7u, 1u) == float4_t{3, 0, 7, 1}));
    FND_TEST_TRUE(all(float4(uint2_t{3, 0}, 7u, 1u)
        == float4_t{3, 0, 7, 1}));
    FND_TEST_TRUE(
        all(float4(uint2_t{3, 0}) == float4_t{3, 0, 0, 0}));
    FND_TEST_TRUE(all(float4(uint3_t{3, 0, 7}, 1u)
        == float4_t{3, 0, 7, 1}));
    FND_TEST_TRUE(
        all(float4(uint3_t{3, 0, 7}) == float4_t{3, 0, 7, 0}));
    FND_TEST_TRUE(all(float4(uint4_t{3, 0, 7, 1})
        == float4_t{3, 0, 7, 1}));

    // From a quat_t: the components x, y, z and w.
    constexpr quat_t kQuat{1, -2, 3, 4};
    FND_TEST_TRUE(all(float4(kQuat) == float4_t{1, -2, 3, 4}));
    FND_TEST_TRUE(all(float4(quat_t::kIdentity) == float4_t::kUnitW));
    static_assert(float4(kQuat).w == 4.0f);
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
    FND_TEST_TRUE(all(int2(uint2_t{0, 7}) == int2_t{0, 7}));
    FND_TEST_TRUE(all(int2(uint2_t{static_cast<uint_t>(kIntMaxValue), 123u})
        == int2_t{kIntMaxValue, 123}));
    const int2_t iv{0, kIntMaxValue};
    FND_TEST_TRUE(all(int2(uint2(iv)) == iv));

    // From an int3_t or int4_t: keeps x and y.
    const int3_t v3{1, -2, 3};
    const int4_t v4{1, -2, 3, -4};
    FND_TEST_TRUE(all(int2(v3) == int2_t{1, -2}));
    FND_TEST_TRUE(all(int2(v4) == int2_t{1, -2}));

    // Every overload: splat, components and vectors of every element
    // type.
    FND_TEST_TRUE(all(int2(true) == int2_t{1, 1}));
    FND_TEST_TRUE(all(int2(true, false) == int2_t{1, 0}));
    FND_TEST_TRUE(all(int2(bool2_t{true, false}) == int2_t{1, 0}));
    FND_TEST_TRUE(all(int2(bool3_t{true, false, true}) == int2_t{1, 0}));
    FND_TEST_TRUE(all(int2(bool4_t{true, false, true, true}) == int2_t{1, 0}));
    FND_TEST_TRUE(all(int2(3.75f) == int2_t{3, 3}));
    FND_TEST_TRUE(all(int2(3.75f, 0.0f) == int2_t{3, 0}));
    FND_TEST_TRUE(all(int2(float2_t{3.75f, 0.0f}) == int2_t{3, 0}));
    FND_TEST_TRUE(all(int2(float3_t{3.75f, 0.0f, 7.25f}) == int2_t{3, 0}));
    FND_TEST_TRUE(
        all(int2(float4_t{3.75f, 0.0f, 7.25f, 1.5f}) == int2_t{3, 0}));
    FND_TEST_TRUE(all(int2(3) == int2_t{3, 3}));
    FND_TEST_TRUE(all(int2(3, 0) == int2_t{3, 0}));
    FND_TEST_TRUE(all(int2(int3_t{3, 0, 7}) == int2_t{3, 0}));
    FND_TEST_TRUE(all(int2(int4_t{3, 0, 7, 1}) == int2_t{3, 0}));
    FND_TEST_TRUE(all(int2(3u) == int2_t{3, 3}));
    FND_TEST_TRUE(all(int2(3u, 0u) == int2_t{3, 0}));
    FND_TEST_TRUE(all(int2(uint2_t{3, 0}) == int2_t{3, 0}));
    FND_TEST_TRUE(all(int2(uint3_t{3, 0, 7}) == int2_t{3, 0}));
    FND_TEST_TRUE(all(int2(uint4_t{3, 0, 7, 1}) == int2_t{3, 0}));

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
    FND_TEST_TRUE(all(int3(uint3_t{0, 7, 123}) == int3_t{0, 7, 123}));
    FND_TEST_TRUE(
        all(int3(uint3_t{static_cast<uint_t>(kIntMaxValue), 1u, 0u})
            == int3_t{kIntMaxValue, 1, 0}));
    const int3_t iv{0, kIntMaxValue, 678};
    FND_TEST_TRUE(all(int3(uint3(iv)) == iv));

    // From an int2_t: z defaults to 0.
    const int2_t v2{1, -2};
    FND_TEST_TRUE(all(int3(v2) == int3_t{1, -2, 0}));
    FND_TEST_TRUE(all(int3(v2, 7) == int3_t{1, -2, 7}));
    FND_TEST_TRUE(all(int2(int3(v2)) == v2));

    // From an int4_t: keeps x, y and z.
    const int4_t v4{1, -2, 3, -4};
    FND_TEST_TRUE(all(int3(v4) == int3_t{1, -2, 3}));

    // Every overload: splat, components and vectors of every element
    // type.
    FND_TEST_TRUE(all(int3(true) == int3_t{1, 1, 1}));
    FND_TEST_TRUE(all(int3(true, false, true) == int3_t{1, 0, 1}));
    FND_TEST_TRUE(all(int3(bool2_t{true, false}, true) == int3_t{1, 0, 1}));
    FND_TEST_TRUE(all(int3(bool2_t{true, false}) == int3_t{1, 0, 0}));
    FND_TEST_TRUE(all(int3(bool3_t{true, false, true}) == int3_t{1, 0, 1}));
    FND_TEST_TRUE(
        all(int3(bool4_t{true, false, true, true}) == int3_t{1, 0, 1}));
    FND_TEST_TRUE(all(int3(3.75f) == int3_t{3, 3, 3}));
    FND_TEST_TRUE(all(int3(3.75f, 0.0f, 7.25f) == int3_t{3, 0, 7}));
    FND_TEST_TRUE(all(int3(float2_t{3.75f, 0.0f}, 7.25f) == int3_t{3, 0, 7}));
    FND_TEST_TRUE(all(int3(float2_t{3.75f, 0.0f}) == int3_t{3, 0, 0}));
    FND_TEST_TRUE(all(int3(float3_t{3.75f, 0.0f, 7.25f}) == int3_t{3, 0, 7}));
    FND_TEST_TRUE(
        all(int3(float4_t{3.75f, 0.0f, 7.25f, 1.5f}) == int3_t{3, 0, 7}));
    FND_TEST_TRUE(all(int3(3) == int3_t{3, 3, 3}));
    FND_TEST_TRUE(all(int3(3, 0, 7) == int3_t{3, 0, 7}));
    FND_TEST_TRUE(all(int3(int2_t{3, 0}, 7) == int3_t{3, 0, 7}));
    FND_TEST_TRUE(all(int3(int2_t{3, 0}) == int3_t{3, 0, 0}));
    FND_TEST_TRUE(all(int3(int4_t{3, 0, 7, 1}) == int3_t{3, 0, 7}));
    FND_TEST_TRUE(all(int3(3u) == int3_t{3, 3, 3}));
    FND_TEST_TRUE(all(int3(3u, 0u, 7u) == int3_t{3, 0, 7}));
    FND_TEST_TRUE(all(int3(uint2_t{3, 0}, 7u) == int3_t{3, 0, 7}));
    FND_TEST_TRUE(all(int3(uint2_t{3, 0}) == int3_t{3, 0, 0}));
    FND_TEST_TRUE(all(int3(uint3_t{3, 0, 7}) == int3_t{3, 0, 7}));
    FND_TEST_TRUE(all(int3(uint4_t{3, 0, 7, 1}) == int3_t{3, 0, 7}));

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
        all(int4(uint4_t{0, 7, 123, 1}) == int4_t{0, 7, 123, 1}));
    FND_TEST_TRUE(
        all(int4(uint4_t{static_cast<uint_t>(kIntMaxValue), 1u, 0u, 2u})
            == int4_t{kIntMaxValue, 1, 0, 2}));
    const int4_t iv{0, kIntMaxValue, 678, 1};
    FND_TEST_TRUE(all(int4(uint4(iv)) == iv));

    // From an int2_t: z and w default to 0.
    const int2_t v2{1, -2};
    FND_TEST_TRUE(all(int4(v2) == int4_t{1, -2, 0, 0}));
    FND_TEST_TRUE(all(int4(v2, 7) == int4_t{1, -2, 7, 0}));
    FND_TEST_TRUE(
        all(int4(v2, 7, -8) == int4_t{1, -2, 7, -8}));
    FND_TEST_TRUE(all(int2(int4(v2)) == v2));

    // From an int3_t: w defaults to 0.
    const int3_t v3{1, -2, 3};
    FND_TEST_TRUE(all(int4(v3) == int4_t{1, -2, 3, 0}));
    FND_TEST_TRUE(all(int4(v3, -8) == int4_t{1, -2, 3, -8}));
    FND_TEST_TRUE(all(int3(int4(v3)) == v3));

    // Every overload: splat, components and vectors of every element
    // type.
    FND_TEST_TRUE(all(int4(true) == int4_t{1, 1, 1, 1}));
    FND_TEST_TRUE(all(int4(true, false, true, true) == int4_t{1, 0, 1, 1}));
    FND_TEST_TRUE(
        all(int4(bool2_t{true, false}, true, true) == int4_t{1, 0, 1, 1}));
    FND_TEST_TRUE(all(int4(bool2_t{true, false}) == int4_t{1, 0, 0, 0}));
    FND_TEST_TRUE(
        all(int4(bool3_t{true, false, true}, true) == int4_t{1, 0, 1, 1}));
    FND_TEST_TRUE(all(int4(bool3_t{true, false, true}) == int4_t{1, 0, 1, 0}));
    FND_TEST_TRUE(
        all(int4(bool4_t{true, false, true, true}) == int4_t{1, 0, 1, 1}));
    FND_TEST_TRUE(all(int4(3.75f) == int4_t{3, 3, 3, 3}));
    FND_TEST_TRUE(all(int4(3.75f, 0.0f, 7.25f, 1.5f) == int4_t{3, 0, 7, 1}));
    FND_TEST_TRUE(
        all(int4(float2_t{3.75f, 0.0f}, 7.25f, 1.5f) == int4_t{3, 0, 7, 1}));
    FND_TEST_TRUE(all(int4(float2_t{3.75f, 0.0f}) == int4_t{3, 0, 0, 0}));
    FND_TEST_TRUE(
        all(int4(float3_t{3.75f, 0.0f, 7.25f}, 1.5f) == int4_t{3, 0, 7, 1}));
    FND_TEST_TRUE(
        all(int4(float3_t{3.75f, 0.0f, 7.25f}) == int4_t{3, 0, 7, 0}));
    FND_TEST_TRUE(
        all(int4(float4_t{3.75f, 0.0f, 7.25f, 1.5f}) == int4_t{3, 0, 7, 1}));
    FND_TEST_TRUE(all(int4(3) == int4_t{3, 3, 3, 3}));
    FND_TEST_TRUE(all(int4(3, 0, 7, 1) == int4_t{3, 0, 7, 1}));
    FND_TEST_TRUE(all(int4(int2_t{3, 0}, 7, 1) == int4_t{3, 0, 7, 1}));
    FND_TEST_TRUE(all(int4(int2_t{3, 0}) == int4_t{3, 0, 0, 0}));
    FND_TEST_TRUE(all(int4(int3_t{3, 0, 7}, 1) == int4_t{3, 0, 7, 1}));
    FND_TEST_TRUE(all(int4(int3_t{3, 0, 7}) == int4_t{3, 0, 7, 0}));
    FND_TEST_TRUE(all(int4(3u) == int4_t{3, 3, 3, 3}));
    FND_TEST_TRUE(all(int4(3u, 0u, 7u, 1u) == int4_t{3, 0, 7, 1}));
    FND_TEST_TRUE(all(int4(uint2_t{3, 0}, 7u, 1u) == int4_t{3, 0, 7, 1}));
    FND_TEST_TRUE(all(int4(uint2_t{3, 0}) == int4_t{3, 0, 0, 0}));
    FND_TEST_TRUE(all(int4(uint3_t{3, 0, 7}, 1u) == int4_t{3, 0, 7, 1}));
    FND_TEST_TRUE(all(int4(uint3_t{3, 0, 7}) == int4_t{3, 0, 7, 0}));
    FND_TEST_TRUE(all(int4(uint4_t{3, 0, 7, 1}) == int4_t{3, 0, 7, 1}));

}

void unittests_math_vector_conversion_quat()
{
    // The components x, y, z and w, without normalizing; float4 gives them
    // back.
    constexpr float4_t kVector{1, -2, 3, 4};
    FND_TEST_TRUE(quat(kVector) == quat_t(1, -2, 3, 4));
    FND_TEST_TRUE(all(float4(quat(kVector)) == kVector));
    FND_TEST_TRUE(quat(float4_t::kUnitW) == quat_t::kIdentity);
    FND_TEST_TRUE(quat(float4(quat_t::kIdentity)) == quat_t::kIdentity);

    // Usable in constant expressions.
    static_assert(quat(kVector).w == 4.0f);
}

void unittests_math_vector_conversion_uint2()
{
    // From a float2_t: truncates toward zero.
    FND_TEST_TRUE(all(uint2(float2_t{2.75f, 0.5f}) == uint2_t{2, 0}));
    FND_TEST_TRUE(all(uint2(float2_t{0.999f, -0.0f}) == uint2_t{0, 0}));
    // The upper edge of the valid range: the largest float below 2^32.
    FND_TEST_TRUE(all(uint2(float2_t{0x1.fffffep31f, 1e9f})
        == uint2_t{4294967040u, 1000000000u}));

    // From an int2_t.
    FND_TEST_TRUE(all(uint2(int2_t{0, 7}) == uint2_t{0, 7}));
    FND_TEST_TRUE(
        all(uint2(int2_t{kIntMaxValue, 123}) == uint2_t{2147483647, 123}));
    const uint2_t uv{0, 2147483647};
    FND_TEST_TRUE(all(uint2(int2(uv)) == uv));

    // From a uint3_t or uint4_t: keeps x and y.
    const uint3_t v3{1, 2, 3};
    const uint4_t v4{1, 2, 3, 4};
    FND_TEST_TRUE(all(uint2(v3) == uint2_t{1, 2}));
    FND_TEST_TRUE(all(uint2(v4) == uint2_t{1, 2}));

    // Every overload: splat, components and vectors of every element
    // type.
    FND_TEST_TRUE(all(uint2(true) == uint2_t{1, 1}));
    FND_TEST_TRUE(all(uint2(true, false) == uint2_t{1, 0}));
    FND_TEST_TRUE(all(uint2(bool2_t{true, false}) == uint2_t{1, 0}));
    FND_TEST_TRUE(all(uint2(bool3_t{true, false, true}) == uint2_t{1, 0}));
    FND_TEST_TRUE(
        all(uint2(bool4_t{true, false, true, true}) == uint2_t{1, 0}));
    FND_TEST_TRUE(all(uint2(3.75f) == uint2_t{3, 3}));
    FND_TEST_TRUE(all(uint2(3.75f, 0.0f) == uint2_t{3, 0}));
    FND_TEST_TRUE(all(uint2(float2_t{3.75f, 0.0f}) == uint2_t{3, 0}));
    FND_TEST_TRUE(all(uint2(float3_t{3.75f, 0.0f, 7.25f}) == uint2_t{3, 0}));
    FND_TEST_TRUE(
        all(uint2(float4_t{3.75f, 0.0f, 7.25f, 1.5f}) == uint2_t{3, 0}));
    FND_TEST_TRUE(all(uint2(3) == uint2_t{3, 3}));
    FND_TEST_TRUE(all(uint2(3, 0) == uint2_t{3, 0}));
    FND_TEST_TRUE(all(uint2(int2_t{3, 0}) == uint2_t{3, 0}));
    FND_TEST_TRUE(all(uint2(int3_t{3, 0, 7}) == uint2_t{3, 0}));
    FND_TEST_TRUE(all(uint2(int4_t{3, 0, 7, 1}) == uint2_t{3, 0}));
    FND_TEST_TRUE(all(uint2(3u) == uint2_t{3, 3}));
    FND_TEST_TRUE(all(uint2(3u, 0u) == uint2_t{3, 0}));
    FND_TEST_TRUE(all(uint2(uint3_t{3, 0, 7}) == uint2_t{3, 0}));
    FND_TEST_TRUE(all(uint2(uint4_t{3, 0, 7, 1}) == uint2_t{3, 0}));

}

void unittests_math_vector_conversion_uint3()
{
    // From a float3_t: truncates toward zero.
    FND_TEST_TRUE(
        all(uint3(float3_t{2.75f, 0.5f, 0.999f}) == uint3_t{2, 0, 0}));
    FND_TEST_TRUE(all(uint3(float3_t{0x1.fffffep31f, 1e9f, -0.0f})
        == uint3_t{4294967040u, 1000000000u, 0u}));

    // From an int3_t.
    FND_TEST_TRUE(all(uint3(int3_t{0, 7, 123}) == uint3_t{0, 7, 123}));
    FND_TEST_TRUE(all(uint3(int3_t{kIntMaxValue, 1, 0})
        == uint3_t{2147483647, 1, 0}));
    const uint3_t uv{0, 2147483647, 678};
    FND_TEST_TRUE(all(uint3(int3(uv)) == uv));

    // From a uint2_t: z defaults to 0.
    const uint2_t v2{1, 2};
    FND_TEST_TRUE(all(uint3(v2) == uint3_t{1, 2, 0}));
    FND_TEST_TRUE(all(uint3(v2, 7u) == uint3_t{1, 2, 7}));
    FND_TEST_TRUE(all(uint2(uint3(v2)) == v2));

    // From a uint4_t: keeps x, y and z.
    const uint4_t v4{1, 2, 3, 4};
    FND_TEST_TRUE(all(uint3(v4) == uint3_t{1, 2, 3}));

    // Every overload: splat, components and vectors of every element
    // type.
    FND_TEST_TRUE(all(uint3(true) == uint3_t{1, 1, 1}));
    FND_TEST_TRUE(all(uint3(true, false, true) == uint3_t{1, 0, 1}));
    FND_TEST_TRUE(
        all(uint3(bool2_t{true, false}, true) == uint3_t{1, 0, 1}));
    FND_TEST_TRUE(all(uint3(bool2_t{true, false}) == uint3_t{1, 0, 0}));
    FND_TEST_TRUE(
        all(uint3(bool3_t{true, false, true}) == uint3_t{1, 0, 1}));
    FND_TEST_TRUE(
        all(uint3(bool4_t{true, false, true, true}) == uint3_t{1, 0, 1}));
    FND_TEST_TRUE(all(uint3(3.75f) == uint3_t{3, 3, 3}));
    FND_TEST_TRUE(all(uint3(3.75f, 0.0f, 7.25f) == uint3_t{3, 0, 7}));
    FND_TEST_TRUE(
        all(uint3(float2_t{3.75f, 0.0f}, 7.25f) == uint3_t{3, 0, 7}));
    FND_TEST_TRUE(all(uint3(float2_t{3.75f, 0.0f}) == uint3_t{3, 0, 0}));
    FND_TEST_TRUE(
        all(uint3(float3_t{3.75f, 0.0f, 7.25f}) == uint3_t{3, 0, 7}));
    FND_TEST_TRUE(
        all(uint3(float4_t{3.75f, 0.0f, 7.25f, 1.5f}) == uint3_t{3, 0, 7}));
    FND_TEST_TRUE(all(uint3(3) == uint3_t{3, 3, 3}));
    FND_TEST_TRUE(all(uint3(3, 0, 7) == uint3_t{3, 0, 7}));
    FND_TEST_TRUE(all(uint3(int2_t{3, 0}, 7) == uint3_t{3, 0, 7}));
    FND_TEST_TRUE(all(uint3(int2_t{3, 0}) == uint3_t{3, 0, 0}));
    FND_TEST_TRUE(all(uint3(int3_t{3, 0, 7}) == uint3_t{3, 0, 7}));
    FND_TEST_TRUE(all(uint3(int4_t{3, 0, 7, 1}) == uint3_t{3, 0, 7}));
    FND_TEST_TRUE(all(uint3(3u) == uint3_t{3, 3, 3}));
    FND_TEST_TRUE(all(uint3(3u, 0u, 7u) == uint3_t{3, 0, 7}));
    FND_TEST_TRUE(all(uint3(uint2_t{3, 0}, 7u) == uint3_t{3, 0, 7}));
    FND_TEST_TRUE(all(uint3(uint2_t{3, 0}) == uint3_t{3, 0, 0}));
    FND_TEST_TRUE(all(uint3(uint4_t{3, 0, 7, 1}) == uint3_t{3, 0, 7}));

}

void unittests_math_vector_conversion_uint4()
{
    // From a float4_t: truncates toward zero.
    FND_TEST_TRUE(all(uint4(float4_t{2.75f, 0.5f, 0.999f, -0.0f})
        == uint4_t{2, 0, 0, 0}));
    FND_TEST_TRUE(all(uint4(float4_t{0x1.fffffep31f, 1e9f, 1.5f, 0.999f})
        == uint4_t{4294967040u, 1000000000u, 1u, 0u}));

    // From an int4_t.
    FND_TEST_TRUE(
        all(uint4(int4_t{0, 7, 123, 1}) == uint4_t{0, 7, 123, 1}));
    FND_TEST_TRUE(all(uint4(int4_t{kIntMaxValue, 1, 0, 2})
        == uint4_t{2147483647, 1, 0, 2}));
    const uint4_t uv{0, 2147483647, 678, 1};
    FND_TEST_TRUE(all(uint4(int4(uv)) == uv));

    // From a uint2_t: z and w default to 0.
    const uint2_t v2{1, 2};
    FND_TEST_TRUE(all(uint4(v2) == uint4_t{1, 2, 0, 0}));
    FND_TEST_TRUE(all(uint4(v2, 7u) == uint4_t{1, 2, 7, 0}));
    FND_TEST_TRUE(
        all(uint4(v2, 7u, 8u) == uint4_t{1, 2, 7, 8}));
    FND_TEST_TRUE(all(uint2(uint4(v2)) == v2));

    // From a uint3_t: w defaults to 0.
    const uint3_t v3{1, 2, 3};
    FND_TEST_TRUE(all(uint4(v3) == uint4_t{1, 2, 3, 0}));
    FND_TEST_TRUE(all(uint4(v3, 8u) == uint4_t{1, 2, 3, 8}));
    FND_TEST_TRUE(all(uint3(uint4(v3)) == v3));

    // Every overload: splat, components and vectors of every element
    // type.
    FND_TEST_TRUE(all(uint4(true) == uint4_t{1, 1, 1, 1}));
    FND_TEST_TRUE(
        all(uint4(true, false, true, true) == uint4_t{1, 0, 1, 1}));
    FND_TEST_TRUE(all(uint4(bool2_t{true, false}, true, true)
        == uint4_t{1, 0, 1, 1}));
    FND_TEST_TRUE(all(uint4(bool2_t{true, false}) == uint4_t{1, 0, 0, 0}));
    FND_TEST_TRUE(all(uint4(bool3_t{true, false, true}, true)
        == uint4_t{1, 0, 1, 1}));
    FND_TEST_TRUE(
        all(uint4(bool3_t{true, false, true}) == uint4_t{1, 0, 1, 0}));
    FND_TEST_TRUE(all(uint4(bool4_t{true, false, true, true})
        == uint4_t{1, 0, 1, 1}));
    FND_TEST_TRUE(all(uint4(3.75f) == uint4_t{3, 3, 3, 3}));
    FND_TEST_TRUE(
        all(uint4(3.75f, 0.0f, 7.25f, 1.5f) == uint4_t{3, 0, 7, 1}));
    FND_TEST_TRUE(all(uint4(float2_t{3.75f, 0.0f}, 7.25f, 1.5f)
        == uint4_t{3, 0, 7, 1}));
    FND_TEST_TRUE(all(uint4(float2_t{3.75f, 0.0f}) == uint4_t{3, 0, 0, 0}));
    FND_TEST_TRUE(all(uint4(float3_t{3.75f, 0.0f, 7.25f}, 1.5f)
        == uint4_t{3, 0, 7, 1}));
    FND_TEST_TRUE(
        all(uint4(float3_t{3.75f, 0.0f, 7.25f}) == uint4_t{3, 0, 7, 0}));
    FND_TEST_TRUE(all(uint4(float4_t{3.75f, 0.0f, 7.25f, 1.5f})
        == uint4_t{3, 0, 7, 1}));
    FND_TEST_TRUE(all(uint4(3) == uint4_t{3, 3, 3, 3}));
    FND_TEST_TRUE(all(uint4(3, 0, 7, 1) == uint4_t{3, 0, 7, 1}));
    FND_TEST_TRUE(all(uint4(int2_t{3, 0}, 7, 1) == uint4_t{3, 0, 7, 1}));
    FND_TEST_TRUE(all(uint4(int2_t{3, 0}) == uint4_t{3, 0, 0, 0}));
    FND_TEST_TRUE(all(uint4(int3_t{3, 0, 7}, 1) == uint4_t{3, 0, 7, 1}));
    FND_TEST_TRUE(all(uint4(int3_t{3, 0, 7}) == uint4_t{3, 0, 7, 0}));
    FND_TEST_TRUE(all(uint4(int4_t{3, 0, 7, 1}) == uint4_t{3, 0, 7, 1}));
    FND_TEST_TRUE(all(uint4(3u) == uint4_t{3, 3, 3, 3}));
    FND_TEST_TRUE(all(uint4(3u, 0u, 7u, 1u) == uint4_t{3, 0, 7, 1}));
    FND_TEST_TRUE(
        all(uint4(uint2_t{3, 0}, 7u, 1u) == uint4_t{3, 0, 7, 1}));
    FND_TEST_TRUE(all(uint4(uint2_t{3, 0}) == uint4_t{3, 0, 0, 0}));
    FND_TEST_TRUE(
        all(uint4(uint3_t{3, 0, 7}, 1u) == uint4_t{3, 0, 7, 1}));
    FND_TEST_TRUE(all(uint4(uint3_t{3, 0, 7}) == uint4_t{3, 0, 7, 0}));

}

void unittests_math_vector_conversion()
{
    unittests_math_vector_conversion_bool2();
    unittests_math_vector_conversion_bool3();
    unittests_math_vector_conversion_bool4();
    unittests_math_vector_conversion_can_trunc_to_int();
    unittests_math_vector_conversion_can_trunc_to_uint();
    unittests_math_vector_conversion_float2();
    unittests_math_vector_conversion_float3();
    unittests_math_vector_conversion_float4();
    unittests_math_vector_conversion_int2();
    unittests_math_vector_conversion_int3();
    unittests_math_vector_conversion_int4();
    unittests_math_vector_conversion_quat();
    unittests_math_vector_conversion_uint2();
    unittests_math_vector_conversion_uint3();
    unittests_math_vector_conversion_uint4();
}
} // namespace fnd::unittests
