module;
#include "foundation/core/macros.h"

export module foundation.math:vector_conversion;
import foundation.core;
import :vector_bool;
import :vector_float2;
import :vector_float3;
import :vector_float4;
import :vector_int2;
import :vector_int3;
import :vector_int4;
import :vector_uint2;
import :vector_uint3;
import :vector_uint4;

// NOTE:
// Conversions between vectors of the same size and a different element type.
// They live in their own partition, because vector partitions cannot import
// each other both ways, so the types cannot convert through constructors.
//
// - int/uint -> float: rounds to the nearest float when |x| > 2^24.
// - float -> int/uint: truncates toward zero, as static_cast does. Every
//   component must be in the range checked by can_trunc_to_int/uint (see
//   core.arithmetic), otherwise the conversion is UB, so it is asserted.
// - int <-> uint: the value must fit in the destination.

namespace fnd {

export FND_INLINE bool2_t can_trunc_to_int(const float2_t v)
{
    return bool2_t{can_trunc_to_int(v.x), can_trunc_to_int(v.y)};
}

export FND_INLINE bool3_t can_trunc_to_int(const float3_t v)
{
    return bool3_t{
        can_trunc_to_int(v.x), can_trunc_to_int(v.y), can_trunc_to_int(v.z)};
}

export FND_INLINE bool4_t can_trunc_to_int(const float4_t v)
{
    return bool4_t{
        can_trunc_to_int(v.x),
        can_trunc_to_int(v.y),
        can_trunc_to_int(v.z),
        can_trunc_to_int(v.w)};
}

export FND_INLINE bool2_t can_trunc_to_uint(const float2_t v)
{
    return bool2_t{can_trunc_to_uint(v.x), can_trunc_to_uint(v.y)};
}

export FND_INLINE bool3_t can_trunc_to_uint(const float3_t v)
{
    return bool3_t{
        can_trunc_to_uint(v.x), can_trunc_to_uint(v.y), can_trunc_to_uint(v.z)};
}

export FND_INLINE bool4_t can_trunc_to_uint(const float4_t v)
{
    return bool4_t{
        can_trunc_to_uint(v.x),
        can_trunc_to_uint(v.y),
        can_trunc_to_uint(v.z),
        can_trunc_to_uint(v.w)};
}

export constexpr float2_t float2(const int2_t v)
{
    return float2_t{static_cast<float_t>(v.x), static_cast<float_t>(v.y)};
}

export constexpr float2_t float2(const uint2_t v)
{
    return float2_t{static_cast<float_t>(v.x), static_cast<float_t>(v.y)};
}

export constexpr float3_t float3(const int3_t v)
{
    return float3_t{
        static_cast<float_t>(v.x),
        static_cast<float_t>(v.y),
        static_cast<float_t>(v.z)};
}

export constexpr float3_t float3(const uint3_t v)
{
    return float3_t{
        static_cast<float_t>(v.x),
        static_cast<float_t>(v.y),
        static_cast<float_t>(v.z)};
}

export constexpr float4_t float4(const int4_t v)
{
    return float4_t{
        static_cast<float_t>(v.x),
        static_cast<float_t>(v.y),
        static_cast<float_t>(v.z),
        static_cast<float_t>(v.w)};
}

export constexpr float4_t float4(const uint4_t v)
{
    return float4_t{
        static_cast<float_t>(v.x),
        static_cast<float_t>(v.y),
        static_cast<float_t>(v.z),
        static_cast<float_t>(v.w)};
}

export FND_INLINE int2_t int2(const float2_t v)
{
    FND_ASSERT(all(can_trunc_to_int(v)));

    return int2_t{static_cast<int_t>(v.x), static_cast<int_t>(v.y)};
}

export constexpr int2_t int2(const uint2_t v)
{
    FND_ASSERT(all(v <= static_cast<uint_t>(kIntMaxValue)));

    return int2_t{static_cast<int_t>(v.x), static_cast<int_t>(v.y)};
}

export FND_INLINE int3_t int3(const float3_t v)
{
    FND_ASSERT(all(can_trunc_to_int(v)));

    return int3_t{
        static_cast<int_t>(v.x),
        static_cast<int_t>(v.y),
        static_cast<int_t>(v.z)};
}

export constexpr int3_t int3(const uint3_t v)
{
    FND_ASSERT(all(v <= static_cast<uint_t>(kIntMaxValue)));

    return int3_t{
        static_cast<int_t>(v.x),
        static_cast<int_t>(v.y),
        static_cast<int_t>(v.z)};
}

export FND_INLINE int4_t int4(const float4_t v)
{
    FND_ASSERT(all(can_trunc_to_int(v)));

    return int4_t{
        static_cast<int_t>(v.x),
        static_cast<int_t>(v.y),
        static_cast<int_t>(v.z),
        static_cast<int_t>(v.w)};
}

export constexpr int4_t int4(const uint4_t v)
{
    FND_ASSERT(all(v <= static_cast<uint_t>(kIntMaxValue)));

    return int4_t{
        static_cast<int_t>(v.x),
        static_cast<int_t>(v.y),
        static_cast<int_t>(v.z),
        static_cast<int_t>(v.w)};
}

export FND_INLINE uint2_t uint2(const float2_t v)
{
    FND_ASSERT(all(can_trunc_to_uint(v)));

    return uint2_t{static_cast<uint_t>(v.x), static_cast<uint_t>(v.y)};
}

export constexpr uint2_t uint2(const int2_t v)
{
    FND_ASSERT(all(v >= 0));

    return uint2_t{static_cast<uint_t>(v.x), static_cast<uint_t>(v.y)};
}

export FND_INLINE uint3_t uint3(const float3_t v)
{
    FND_ASSERT(all(can_trunc_to_uint(v)));

    return uint3_t{
        static_cast<uint_t>(v.x),
        static_cast<uint_t>(v.y),
        static_cast<uint_t>(v.z)};
}

export constexpr uint3_t uint3(const int3_t v)
{
    FND_ASSERT(all(v >= 0));

    return uint3_t{
        static_cast<uint_t>(v.x),
        static_cast<uint_t>(v.y),
        static_cast<uint_t>(v.z)};
}

export FND_INLINE uint4_t uint4(const float4_t v)
{
    FND_ASSERT(all(can_trunc_to_uint(v)));

    return uint4_t{
        static_cast<uint_t>(v.x),
        static_cast<uint_t>(v.y),
        static_cast<uint_t>(v.z),
        static_cast<uint_t>(v.w)};
}

export constexpr uint4_t uint4(const int4_t v)
{
    FND_ASSERT(all(v >= 0));

    return uint4_t{
        static_cast<uint_t>(v.x),
        static_cast<uint_t>(v.y),
        static_cast<uint_t>(v.z),
        static_cast<uint_t>(v.w)};
}

} // namespace fnd
