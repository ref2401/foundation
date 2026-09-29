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


namespace fnd {

// ---------------------------------------------------------------------------
// bool2()
// ---------------------------------------------------------------------------

export constexpr bool2_t bool2(const bool_t scalar)
{
    return bool2_t{scalar, scalar};
}

export constexpr bool2_t bool2(const bool_t x, const bool_t y)
{
    return bool2_t{x, y};
}

export constexpr bool2_t bool2(const bool3_t v)
{
    return bool2_t{v.x, v.y};
}

export constexpr bool2_t bool2(const bool4_t v)
{
    return bool2_t{v.x, v.y};
}

export FND_INLINE bool2_t bool2(const float_t scalar)
{
    FND_ASSERT(!isnan(scalar));

    return bool2_t{scalar != 0.0f, scalar != 0.0f};
}

export FND_INLINE bool2_t bool2(const float_t x, const float_t y)
{
    FND_ASSERT(!isnan(x) && !isnan(y));

    return bool2_t{x != 0.0f, y != 0.0f};
}

export FND_INLINE bool2_t bool2(const float2_t v)
{
    FND_ASSERT(all(!isnan(v)));

    return bool2_t{v.x != 0.0f, v.y != 0.0f};
}

export FND_INLINE bool2_t bool2(const float3_t v)
{
    FND_ASSERT(!isnan(v.x) && !isnan(v.y));

    return bool2_t{v.x != 0.0f, v.y != 0.0f};
}

export FND_INLINE bool2_t bool2(const float4_t v)
{
    FND_ASSERT(!isnan(v.x) && !isnan(v.y));

    return bool2_t{v.x != 0.0f, v.y != 0.0f};
}

export constexpr bool2_t bool2(const int_t scalar)
{
    return bool2_t{scalar != 0, scalar != 0};
}

export constexpr bool2_t bool2(const int_t x, const int_t y)
{
    return bool2_t{x != 0, y != 0};
}

export constexpr bool2_t bool2(const int2_t v)
{
    return bool2_t{v.x != 0, v.y != 0};
}

export constexpr bool2_t bool2(const int3_t v)
{
    return bool2_t{v.x != 0, v.y != 0};
}

export constexpr bool2_t bool2(const int4_t v)
{
    return bool2_t{v.x != 0, v.y != 0};
}

export constexpr bool2_t bool2(const uint_t scalar)
{
    return bool2_t{scalar != 0u, scalar != 0u};
}

export constexpr bool2_t bool2(const uint_t x, const uint_t y)
{
    return bool2_t{x != 0u, y != 0u};
}

export constexpr bool2_t bool2(const uint2_t v)
{
    return bool2_t{v.x != 0u, v.y != 0u};
}

export constexpr bool2_t bool2(const uint3_t v)
{
    return bool2_t{v.x != 0u, v.y != 0u};
}

export constexpr bool2_t bool2(const uint4_t v)
{
    return bool2_t{v.x != 0u, v.y != 0u};
}

// ---------------------------------------------------------------------------
// bool3()
// ---------------------------------------------------------------------------

export constexpr bool3_t bool3(const bool_t scalar)
{
    return bool3_t{scalar, scalar, scalar};
}

export constexpr bool3_t bool3(const bool_t x, const bool_t y, const bool_t z)
{
    return bool3_t{x, y, z};
}

export constexpr bool3_t bool3(const bool2_t v, const bool_t z = false)
{
    return bool3_t{v.x, v.y, z};
}

export constexpr bool3_t bool3(const bool4_t v)
{
    return bool3_t{v.x, v.y, v.z};
}

export FND_INLINE bool3_t bool3(const float_t scalar)
{
    FND_ASSERT(!isnan(scalar));

    return bool3_t{scalar != 0.0f, scalar != 0.0f, scalar != 0.0f};
}

export FND_INLINE bool3_t bool3(
    const float_t x, const float_t y, const float_t z)
{
    FND_ASSERT(!isnan(x) && !isnan(y) && !isnan(z));

    return bool3_t{x != 0.0f, y != 0.0f, z != 0.0f};
}

export FND_INLINE bool3_t bool3(const float2_t v, const float_t z = 0)
{
    FND_ASSERT(all(!isnan(v)) && !isnan(z));

    return bool3_t{v.x != 0.0f, v.y != 0.0f, z != 0.0f};
}

export FND_INLINE bool3_t bool3(const float3_t v)
{
    FND_ASSERT(all(!isnan(v)));

    return bool3_t{v.x != 0.0f, v.y != 0.0f, v.z != 0.0f};
}

export FND_INLINE bool3_t bool3(const float4_t v)
{
    FND_ASSERT(!isnan(v.x) && !isnan(v.y) && !isnan(v.z));

    return bool3_t{v.x != 0.0f, v.y != 0.0f, v.z != 0.0f};
}

export constexpr bool3_t bool3(const int_t scalar)
{
    return bool3_t{scalar != 0, scalar != 0, scalar != 0};
}

export constexpr bool3_t bool3(const int_t x, const int_t y, const int_t z)
{
    return bool3_t{x != 0, y != 0, z != 0};
}

export constexpr bool3_t bool3(const int2_t v, const int_t z = 0)
{
    return bool3_t{v.x != 0, v.y != 0, z != 0};
}

export constexpr bool3_t bool3(const int3_t v)
{
    return bool3_t{v.x != 0, v.y != 0, v.z != 0};
}

export constexpr bool3_t bool3(const int4_t v)
{
    return bool3_t{v.x != 0, v.y != 0, v.z != 0};
}

export constexpr bool3_t bool3(const uint_t scalar)
{
    return bool3_t{scalar != 0u, scalar != 0u, scalar != 0u};
}

export constexpr bool3_t bool3(const uint_t x, const uint_t y, const uint_t z)
{
    return bool3_t{x != 0u, y != 0u, z != 0u};
}

export constexpr bool3_t bool3(const uint2_t v, const uint_t z = 0)
{
    return bool3_t{v.x != 0u, v.y != 0u, z != 0u};
}

export constexpr bool3_t bool3(const uint3_t v)
{
    return bool3_t{v.x != 0u, v.y != 0u, v.z != 0u};
}

export constexpr bool3_t bool3(const uint4_t v)
{
    return bool3_t{v.x != 0u, v.y != 0u, v.z != 0u};
}

// ---------------------------------------------------------------------------
// bool4()
// ---------------------------------------------------------------------------

export constexpr bool4_t bool4(const bool_t scalar)
{
    return bool4_t{scalar, scalar, scalar, scalar};
}

export constexpr bool4_t bool4(
    const bool_t x, const bool_t y, const bool_t z, const bool_t w)
{
    return bool4_t{x, y, z, w};
}

export constexpr bool4_t bool4(
    const bool2_t v, const bool_t z = false, const bool_t w = false)
{
    return bool4_t{v.x, v.y, z, w};
}

export constexpr bool4_t bool4(const bool3_t v, const bool_t w = false)
{
    return bool4_t{v.x, v.y, v.z, w};
}

export FND_INLINE bool4_t bool4(const float_t scalar)
{
    FND_ASSERT(!isnan(scalar));

    return bool4_t{
        scalar != 0.0f, scalar != 0.0f, scalar != 0.0f, scalar != 0.0f};
}

export FND_INLINE bool4_t bool4(
    const float_t x, const float_t y, const float_t z, const float_t w)
{
    FND_ASSERT(!isnan(x) && !isnan(y) && !isnan(z) && !isnan(w));

    return bool4_t{x != 0.0f, y != 0.0f, z != 0.0f, w != 0.0f};
}

export FND_INLINE bool4_t bool4(
    const float2_t v, const float_t z = 0, const float_t w = 0)
{
    FND_ASSERT(all(!isnan(v)) && !isnan(z) && !isnan(w));

    return bool4_t{v.x != 0.0f, v.y != 0.0f, z != 0.0f, w != 0.0f};
}

export FND_INLINE bool4_t bool4(const float3_t v, const float_t w = 0)
{
    FND_ASSERT(all(!isnan(v)) && !isnan(w));

    return bool4_t{v.x != 0.0f, v.y != 0.0f, v.z != 0.0f, w != 0.0f};
}

export FND_INLINE bool4_t bool4(const float4_t v)
{
    FND_ASSERT(all(!isnan(v)));

    return bool4_t{v.x != 0.0f, v.y != 0.0f, v.z != 0.0f, v.w != 0.0f};
}

export constexpr bool4_t bool4(const int_t scalar)
{
    return bool4_t{scalar != 0, scalar != 0, scalar != 0, scalar != 0};
}

export constexpr bool4_t bool4(
    const int_t x, const int_t y, const int_t z, const int_t w)
{
    return bool4_t{x != 0, y != 0, z != 0, w != 0};
}

export constexpr bool4_t bool4(
    const int2_t v, const int_t z = 0, const int_t w = 0)
{
    return bool4_t{v.x != 0, v.y != 0, z != 0, w != 0};
}

export constexpr bool4_t bool4(const int3_t v, const int_t w = 0)
{
    return bool4_t{v.x != 0, v.y != 0, v.z != 0, w != 0};
}

export constexpr bool4_t bool4(const int4_t v)
{
    return bool4_t{v.x != 0, v.y != 0, v.z != 0, v.w != 0};
}

export constexpr bool4_t bool4(const uint_t scalar)
{
    return bool4_t{scalar != 0u, scalar != 0u, scalar != 0u, scalar != 0u};
}

export constexpr bool4_t bool4(
    const uint_t x, const uint_t y, const uint_t z, const uint_t w)
{
    return bool4_t{x != 0u, y != 0u, z != 0u, w != 0u};
}

export constexpr bool4_t bool4(
    const uint2_t v, const uint_t z = 0, const uint_t w = 0)
{
    return bool4_t{v.x != 0u, v.y != 0u, z != 0u, w != 0u};
}

export constexpr bool4_t bool4(const uint3_t v, const uint_t w = 0)
{
    return bool4_t{v.x != 0u, v.y != 0u, v.z != 0u, w != 0u};
}

export constexpr bool4_t bool4(const uint4_t v)
{
    return bool4_t{v.x != 0u, v.y != 0u, v.z != 0u, v.w != 0u};
}

// ---------------------------------------------------------------------------
// can_trunc_to()
// ---------------------------------------------------------------------------

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
        can_trunc_to_int(v.x), can_trunc_to_int(v.y), can_trunc_to_int(v.z),
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
        can_trunc_to_uint(v.x), can_trunc_to_uint(v.y), can_trunc_to_uint(v.z),
        can_trunc_to_uint(v.w)};
}

// ---------------------------------------------------------------------------
// float2()
// ---------------------------------------------------------------------------

export constexpr float2_t float2(const bool_t scalar)
{
    return float2_t{scalar ? 1.0f : 0.0f, scalar ? 1.0f : 0.0f};
}

export constexpr float2_t float2(const bool_t x, const bool_t y)
{
    return float2_t{x ? 1.0f : 0.0f, y ? 1.0f : 0.0f};
}

export constexpr float2_t float2(const bool2_t v)
{
    return float2_t{v.x ? 1.0f : 0.0f, v.y ? 1.0f : 0.0f};
}

export constexpr float2_t float2(const bool3_t v)
{
    return float2_t{v.x ? 1.0f : 0.0f, v.y ? 1.0f : 0.0f};
}

export constexpr float2_t float2(const bool4_t v)
{
    return float2_t{v.x ? 1.0f : 0.0f, v.y ? 1.0f : 0.0f};
}

export constexpr float2_t float2(const float_t scalar)
{
    return float2_t{scalar, scalar};
}

export constexpr float2_t float2(const float_t x, const float_t y)
{
    return float2_t{x, y};
}

export constexpr float2_t float2(const float3_t v)
{
    return float2_t{v.x, v.y};
}

export constexpr float2_t float2(const float4_t v)
{
    return float2_t{v.x, v.y};
}

export constexpr float2_t float2(const int_t scalar)
{
    return float2_t{static_cast<float_t>(scalar), static_cast<float_t>(scalar)};
}

export constexpr float2_t float2(const int_t x, const int_t y)
{
    return float2_t{static_cast<float_t>(x), static_cast<float_t>(y)};
}

export constexpr float2_t float2(const int2_t v)
{
    return float2_t{static_cast<float_t>(v.x), static_cast<float_t>(v.y)};
}

export constexpr float2_t float2(const int3_t v)
{
    return float2_t{static_cast<float_t>(v.x), static_cast<float_t>(v.y)};
}

export constexpr float2_t float2(const int4_t v)
{
    return float2_t{static_cast<float_t>(v.x), static_cast<float_t>(v.y)};
}

export constexpr float2_t float2(const uint_t scalar)
{
    return float2_t{static_cast<float_t>(scalar), static_cast<float_t>(scalar)};
}

export constexpr float2_t float2(const uint_t x, const uint_t y)
{
    return float2_t{static_cast<float_t>(x), static_cast<float_t>(y)};
}

export constexpr float2_t float2(const uint2_t v)
{
    return float2_t{static_cast<float_t>(v.x), static_cast<float_t>(v.y)};
}

export constexpr float2_t float2(const uint3_t v)
{
    return float2_t{static_cast<float_t>(v.x), static_cast<float_t>(v.y)};
}

export constexpr float2_t float2(const uint4_t v)
{
    return float2_t{static_cast<float_t>(v.x), static_cast<float_t>(v.y)};
}

// ---------------------------------------------------------------------------
// float3()
// ---------------------------------------------------------------------------

export constexpr float3_t float3(const bool_t scalar)
{
    return float3_t{
        scalar ? 1.0f : 0.0f, scalar ? 1.0f : 0.0f, scalar ? 1.0f : 0.0f};
}

export constexpr float3_t float3(const bool_t x, const bool_t y, const bool_t z)
{
    return float3_t{x ? 1.0f : 0.0f, y ? 1.0f : 0.0f, z ? 1.0f : 0.0f};
}

export constexpr float3_t float3(const bool2_t v, const bool_t z = false)
{
    return float3_t{v.x ? 1.0f : 0.0f, v.y ? 1.0f : 0.0f, z ? 1.0f : 0.0f};
}

export constexpr float3_t float3(const bool3_t v)
{
    return float3_t{v.x ? 1.0f : 0.0f, v.y ? 1.0f : 0.0f, v.z ? 1.0f : 0.0f};
}

export constexpr float3_t float3(const bool4_t v)
{
    return float3_t{v.x ? 1.0f : 0.0f, v.y ? 1.0f : 0.0f, v.z ? 1.0f : 0.0f};
}

export constexpr float3_t float3(const float_t scalar)
{
    return float3_t{scalar, scalar, scalar};
}

export constexpr float3_t float3(
    const float_t x, const float_t y, const float_t z)
{
    return float3_t{x, y, z};
}

export constexpr float3_t float3(const float2_t v, const float_t z = 0)
{
    return float3_t{v.x, v.y, z};
}

export constexpr float3_t float3(const float4_t v)
{
    return float3_t{v.x, v.y, v.z};
}

export constexpr float3_t float3(const int_t scalar)
{
    return float3_t{
        static_cast<float_t>(scalar), static_cast<float_t>(scalar),
        static_cast<float_t>(scalar)};
}

export constexpr float3_t float3(const int_t x, const int_t y, const int_t z)
{
    return float3_t{
        static_cast<float_t>(x), static_cast<float_t>(y),
        static_cast<float_t>(z)};
}

export constexpr float3_t float3(const int2_t v, const int_t z = 0)
{
    return float3_t{
        static_cast<float_t>(v.x), static_cast<float_t>(v.y),
        static_cast<float_t>(z)};
}

export constexpr float3_t float3(const int3_t v)
{
    return float3_t{
        static_cast<float_t>(v.x), static_cast<float_t>(v.y),
        static_cast<float_t>(v.z)};
}

export constexpr float3_t float3(const int4_t v)
{
    return float3_t{
        static_cast<float_t>(v.x), static_cast<float_t>(v.y),
        static_cast<float_t>(v.z)};
}

export constexpr float3_t float3(const uint_t scalar)
{
    return float3_t{
        static_cast<float_t>(scalar), static_cast<float_t>(scalar),
        static_cast<float_t>(scalar)};
}

export constexpr float3_t float3(const uint_t x, const uint_t y, const uint_t z)
{
    return float3_t{
        static_cast<float_t>(x), static_cast<float_t>(y),
        static_cast<float_t>(z)};
}

export constexpr float3_t float3(const uint2_t v, const uint_t z = 0)
{
    return float3_t{
        static_cast<float_t>(v.x), static_cast<float_t>(v.y),
        static_cast<float_t>(z)};
}

export constexpr float3_t float3(const uint3_t v)
{
    return float3_t{
        static_cast<float_t>(v.x), static_cast<float_t>(v.y),
        static_cast<float_t>(v.z)};
}

export constexpr float3_t float3(const uint4_t v)
{
    return float3_t{
        static_cast<float_t>(v.x), static_cast<float_t>(v.y),
        static_cast<float_t>(v.z)};
}

// ---------------------------------------------------------------------------
// float4()
// ---------------------------------------------------------------------------

export constexpr float4_t float4(const bool_t scalar)
{
    return float4_t{
        scalar ? 1.0f : 0.0f, scalar ? 1.0f : 0.0f, scalar ? 1.0f : 0.0f,
        scalar ? 1.0f : 0.0f};
}

export constexpr float4_t float4(
    const bool_t x, const bool_t y, const bool_t z, const bool_t w)
{
    return float4_t{
        x ? 1.0f : 0.0f, y ? 1.0f : 0.0f, z ? 1.0f : 0.0f, w ? 1.0f : 0.0f};
}

export constexpr float4_t float4(
    const bool2_t v, const bool_t z = false, const bool_t w = false)
{
    return float4_t{
        v.x ? 1.0f : 0.0f, v.y ? 1.0f : 0.0f, z ? 1.0f : 0.0f, w ? 1.0f : 0.0f};
}

export constexpr float4_t float4(const bool3_t v, const bool_t w = false)
{
    return float4_t{
        v.x ? 1.0f : 0.0f, v.y ? 1.0f : 0.0f, v.z ? 1.0f : 0.0f,
        w ? 1.0f : 0.0f};
}

export constexpr float4_t float4(const bool4_t v)
{
    return float4_t{
        v.x ? 1.0f : 0.0f, v.y ? 1.0f : 0.0f, v.z ? 1.0f : 0.0f,
        v.w ? 1.0f : 0.0f};
}

export constexpr float4_t float4(const float_t scalar)
{
    return float4_t{scalar, scalar, scalar, scalar};
}

export constexpr float4_t float4(
    const float_t x, const float_t y, const float_t z, const float_t w)
{
    return float4_t{x, y, z, w};
}

export constexpr float4_t float4(
    const float2_t v, const float_t z = 0, const float_t w = 0)
{
    return float4_t{v.x, v.y, z, w};
}

export constexpr float4_t float4(const float3_t v, const float_t w = 0)
{
    return float4_t{v.x, v.y, v.z, w};
}

export constexpr float4_t float4(const int_t scalar)
{
    return float4_t{
        static_cast<float_t>(scalar), static_cast<float_t>(scalar),
        static_cast<float_t>(scalar), static_cast<float_t>(scalar)};
}

export constexpr float4_t float4(
    const int_t x, const int_t y, const int_t z, const int_t w)
{
    return float4_t{
        static_cast<float_t>(x), static_cast<float_t>(y),
        static_cast<float_t>(z), static_cast<float_t>(w)};
}

export constexpr float4_t float4(
    const int2_t v, const int_t z = 0, const int_t w = 0)
{
    return float4_t{
        static_cast<float_t>(v.x), static_cast<float_t>(v.y),
        static_cast<float_t>(z), static_cast<float_t>(w)};
}

export constexpr float4_t float4(const int3_t v, const int_t w = 0)
{
    return float4_t{
        static_cast<float_t>(v.x), static_cast<float_t>(v.y),
        static_cast<float_t>(v.z), static_cast<float_t>(w)};
}

export constexpr float4_t float4(const int4_t v)
{
    return float4_t{
        static_cast<float_t>(v.x), static_cast<float_t>(v.y),
        static_cast<float_t>(v.z), static_cast<float_t>(v.w)};
}

export constexpr float4_t float4(const uint_t scalar)
{
    return float4_t{
        static_cast<float_t>(scalar), static_cast<float_t>(scalar),
        static_cast<float_t>(scalar), static_cast<float_t>(scalar)};
}

export constexpr float4_t float4(
    const uint_t x, const uint_t y, const uint_t z, const uint_t w)
{
    return float4_t{
        static_cast<float_t>(x), static_cast<float_t>(y),
        static_cast<float_t>(z), static_cast<float_t>(w)};
}

export constexpr float4_t float4(
    const uint2_t v, const uint_t z = 0, const uint_t w = 0)
{
    return float4_t{
        static_cast<float_t>(v.x), static_cast<float_t>(v.y),
        static_cast<float_t>(z), static_cast<float_t>(w)};
}

export constexpr float4_t float4(const uint3_t v, const uint_t w = 0)
{
    return float4_t{
        static_cast<float_t>(v.x), static_cast<float_t>(v.y),
        static_cast<float_t>(v.z), static_cast<float_t>(w)};
}

export constexpr float4_t float4(const uint4_t v)
{
    return float4_t{
        static_cast<float_t>(v.x), static_cast<float_t>(v.y),
        static_cast<float_t>(v.z), static_cast<float_t>(v.w)};
}

// ---------------------------------------------------------------------------
// int2()
// ---------------------------------------------------------------------------

export constexpr int2_t int2(const bool_t scalar)
{
    return int2_t{scalar ? 1 : 0, scalar ? 1 : 0};
}

export constexpr int2_t int2(const bool_t x, const bool_t y)
{
    return int2_t{x ? 1 : 0, y ? 1 : 0};
}

export constexpr int2_t int2(const bool2_t v)
{
    return int2_t{v.x ? 1 : 0, v.y ? 1 : 0};
}

export constexpr int2_t int2(const bool3_t v)
{
    return int2_t{v.x ? 1 : 0, v.y ? 1 : 0};
}

export constexpr int2_t int2(const bool4_t v)
{
    return int2_t{v.x ? 1 : 0, v.y ? 1 : 0};
}

export FND_INLINE int2_t int2(const float_t scalar)
{
    FND_ASSERT(can_trunc_to_int(scalar));

    return int2_t{static_cast<int_t>(scalar), static_cast<int_t>(scalar)};
}

export FND_INLINE int2_t int2(const float_t x, const float_t y)
{
    FND_ASSERT(can_trunc_to_int(x) && can_trunc_to_int(y));

    return int2_t{static_cast<int_t>(x), static_cast<int_t>(y)};
}

export FND_INLINE int2_t int2(const float2_t v)
{
    FND_ASSERT(all(can_trunc_to_int(v)));

    return int2_t{static_cast<int_t>(v.x), static_cast<int_t>(v.y)};
}

export FND_INLINE int2_t int2(const float3_t v)
{
    FND_ASSERT(can_trunc_to_int(v.x) && can_trunc_to_int(v.y));

    return int2_t{static_cast<int_t>(v.x), static_cast<int_t>(v.y)};
}

export FND_INLINE int2_t int2(const float4_t v)
{
    FND_ASSERT(can_trunc_to_int(v.x) && can_trunc_to_int(v.y));

    return int2_t{static_cast<int_t>(v.x), static_cast<int_t>(v.y)};
}

export constexpr int2_t int2(const int_t scalar)
{
    return int2_t{scalar, scalar};
}

export constexpr int2_t int2(const int_t x, const int_t y)
{
    return int2_t{x, y};
}

export constexpr int2_t int2(const int3_t v)
{
    return int2_t{v.x, v.y};
}

export constexpr int2_t int2(const int4_t v)
{
    return int2_t{v.x, v.y};
}

export constexpr int2_t int2(const uint_t scalar)
{
    FND_ASSERT(scalar <= static_cast<uint_t>(kIntMaxValue));

    return int2_t{static_cast<int_t>(scalar), static_cast<int_t>(scalar)};
}

export constexpr int2_t int2(const uint_t x, const uint_t y)
{
    FND_ASSERT(x <= static_cast<uint_t>(kIntMaxValue)
        && y <= static_cast<uint_t>(kIntMaxValue));

    return int2_t{static_cast<int_t>(x), static_cast<int_t>(y)};
}

export constexpr int2_t int2(const uint2_t v)
{
    FND_ASSERT(all(v <= static_cast<uint_t>(kIntMaxValue)));

    return int2_t{static_cast<int_t>(v.x), static_cast<int_t>(v.y)};
}

export constexpr int2_t int2(const uint3_t v)
{
    FND_ASSERT(v.x <= static_cast<uint_t>(kIntMaxValue)
        && v.y <= static_cast<uint_t>(kIntMaxValue));

    return int2_t{static_cast<int_t>(v.x), static_cast<int_t>(v.y)};
}

export constexpr int2_t int2(const uint4_t v)
{
    FND_ASSERT(v.x <= static_cast<uint_t>(kIntMaxValue)
        && v.y <= static_cast<uint_t>(kIntMaxValue));

    return int2_t{static_cast<int_t>(v.x), static_cast<int_t>(v.y)};
}

// ---------------------------------------------------------------------------
// int3()
// ---------------------------------------------------------------------------

export constexpr int3_t int3(const bool_t scalar)
{
    return int3_t{scalar ? 1 : 0, scalar ? 1 : 0, scalar ? 1 : 0};
}

export constexpr int3_t int3(const bool_t x, const bool_t y, const bool_t z)
{
    return int3_t{x ? 1 : 0, y ? 1 : 0, z ? 1 : 0};
}

export constexpr int3_t int3(const bool2_t v, const bool_t z = false)
{
    return int3_t{v.x ? 1 : 0, v.y ? 1 : 0, z ? 1 : 0};
}

export constexpr int3_t int3(const bool3_t v)
{
    return int3_t{v.x ? 1 : 0, v.y ? 1 : 0, v.z ? 1 : 0};
}

export constexpr int3_t int3(const bool4_t v)
{
    return int3_t{v.x ? 1 : 0, v.y ? 1 : 0, v.z ? 1 : 0};
}

export FND_INLINE int3_t int3(const float_t scalar)
{
    FND_ASSERT(can_trunc_to_int(scalar));

    return int3_t{
        static_cast<int_t>(scalar), static_cast<int_t>(scalar),
        static_cast<int_t>(scalar)};
}

export FND_INLINE int3_t int3(const float_t x, const float_t y, const float_t z)
{
    FND_ASSERT(can_trunc_to_int(x) && can_trunc_to_int(y)
        && can_trunc_to_int(z));

    return int3_t{
        static_cast<int_t>(x), static_cast<int_t>(y), static_cast<int_t>(z)};
}

export FND_INLINE int3_t int3(const float2_t v, const float_t z = 0)
{
    FND_ASSERT(all(can_trunc_to_int(v)) && can_trunc_to_int(z));

    return int3_t{
        static_cast<int_t>(v.x), static_cast<int_t>(v.y),
        static_cast<int_t>(z)};
}

export FND_INLINE int3_t int3(const float3_t v)
{
    FND_ASSERT(all(can_trunc_to_int(v)));

    return int3_t{
        static_cast<int_t>(v.x), static_cast<int_t>(v.y),
        static_cast<int_t>(v.z)};
}

export FND_INLINE int3_t int3(const float4_t v)
{
    FND_ASSERT(can_trunc_to_int(v.x) && can_trunc_to_int(v.y)
        && can_trunc_to_int(v.z));

    return int3_t{
        static_cast<int_t>(v.x), static_cast<int_t>(v.y),
        static_cast<int_t>(v.z)};
}

export constexpr int3_t int3(const int_t scalar)
{
    return int3_t{scalar, scalar, scalar};
}

export constexpr int3_t int3(const int_t x, const int_t y, const int_t z)
{
    return int3_t{x, y, z};
}

export constexpr int3_t int3(const int2_t v, const int_t z = 0)
{
    return int3_t{v.x, v.y, z};
}

export constexpr int3_t int3(const int4_t v)
{
    return int3_t{v.x, v.y, v.z};
}

export constexpr int3_t int3(const uint_t scalar)
{
    FND_ASSERT(scalar <= static_cast<uint_t>(kIntMaxValue));

    return int3_t{
        static_cast<int_t>(scalar), static_cast<int_t>(scalar),
        static_cast<int_t>(scalar)};
}

export constexpr int3_t int3(const uint_t x, const uint_t y, const uint_t z)
{
    FND_ASSERT(x <= static_cast<uint_t>(kIntMaxValue)
        && y <= static_cast<uint_t>(kIntMaxValue)
        && z <= static_cast<uint_t>(kIntMaxValue));

    return int3_t{
        static_cast<int_t>(x), static_cast<int_t>(y), static_cast<int_t>(z)};
}

export constexpr int3_t int3(const uint2_t v, const uint_t z = 0)
{
    FND_ASSERT(all(v <= static_cast<uint_t>(kIntMaxValue))
        && z <= static_cast<uint_t>(kIntMaxValue));

    return int3_t{
        static_cast<int_t>(v.x), static_cast<int_t>(v.y),
        static_cast<int_t>(z)};
}

export constexpr int3_t int3(const uint3_t v)
{
    FND_ASSERT(all(v <= static_cast<uint_t>(kIntMaxValue)));

    return int3_t{
        static_cast<int_t>(v.x), static_cast<int_t>(v.y),
        static_cast<int_t>(v.z)};
}

export constexpr int3_t int3(const uint4_t v)
{
    FND_ASSERT(v.x <= static_cast<uint_t>(kIntMaxValue)
        && v.y <= static_cast<uint_t>(kIntMaxValue)
        && v.z <= static_cast<uint_t>(kIntMaxValue));

    return int3_t{
        static_cast<int_t>(v.x), static_cast<int_t>(v.y),
        static_cast<int_t>(v.z)};
}

// ---------------------------------------------------------------------------
// int4()
// ---------------------------------------------------------------------------

export constexpr int4_t int4(const bool_t scalar)
{
    return int4_t{
        scalar ? 1 : 0, scalar ? 1 : 0, scalar ? 1 : 0, scalar ? 1 : 0};
}

export constexpr int4_t int4(
    const bool_t x, const bool_t y, const bool_t z, const bool_t w)
{
    return int4_t{x ? 1 : 0, y ? 1 : 0, z ? 1 : 0, w ? 1 : 0};
}

export constexpr int4_t int4(
    const bool2_t v, const bool_t z = false, const bool_t w = false)
{
    return int4_t{v.x ? 1 : 0, v.y ? 1 : 0, z ? 1 : 0, w ? 1 : 0};
}

export constexpr int4_t int4(const bool3_t v, const bool_t w = false)
{
    return int4_t{v.x ? 1 : 0, v.y ? 1 : 0, v.z ? 1 : 0, w ? 1 : 0};
}

export constexpr int4_t int4(const bool4_t v)
{
    return int4_t{v.x ? 1 : 0, v.y ? 1 : 0, v.z ? 1 : 0, v.w ? 1 : 0};
}

export FND_INLINE int4_t int4(const float_t scalar)
{
    FND_ASSERT(can_trunc_to_int(scalar));

    return int4_t{
        static_cast<int_t>(scalar), static_cast<int_t>(scalar),
        static_cast<int_t>(scalar), static_cast<int_t>(scalar)};
}

export FND_INLINE int4_t int4(
    const float_t x, const float_t y, const float_t z, const float_t w)
{
    FND_ASSERT(can_trunc_to_int(x) && can_trunc_to_int(y) && can_trunc_to_int(z)
        && can_trunc_to_int(w));

    return int4_t{
        static_cast<int_t>(x), static_cast<int_t>(y), static_cast<int_t>(z),
        static_cast<int_t>(w)};
}

export FND_INLINE int4_t int4(
    const float2_t v, const float_t z = 0, const float_t w = 0)
{
    FND_ASSERT(all(can_trunc_to_int(v)) && can_trunc_to_int(z)
        && can_trunc_to_int(w));

    return int4_t{
        static_cast<int_t>(v.x), static_cast<int_t>(v.y), static_cast<int_t>(z),
        static_cast<int_t>(w)};
}

export FND_INLINE int4_t int4(const float3_t v, const float_t w = 0)
{
    FND_ASSERT(all(can_trunc_to_int(v)) && can_trunc_to_int(w));

    return int4_t{
        static_cast<int_t>(v.x), static_cast<int_t>(v.y),
        static_cast<int_t>(v.z), static_cast<int_t>(w)};
}

export FND_INLINE int4_t int4(const float4_t v)
{
    FND_ASSERT(all(can_trunc_to_int(v)));

    return int4_t{
        static_cast<int_t>(v.x), static_cast<int_t>(v.y),
        static_cast<int_t>(v.z), static_cast<int_t>(v.w)};
}

export constexpr int4_t int4(const int_t scalar)
{
    return int4_t{scalar, scalar, scalar, scalar};
}

export constexpr int4_t int4(
    const int_t x, const int_t y, const int_t z, const int_t w)
{
    return int4_t{x, y, z, w};
}

export constexpr int4_t int4(
    const int2_t v, const int_t z = 0, const int_t w = 0)
{
    return int4_t{v.x, v.y, z, w};
}

export constexpr int4_t int4(const int3_t v, const int_t w = 0)
{
    return int4_t{v.x, v.y, v.z, w};
}

export constexpr int4_t int4(const uint_t scalar)
{
    FND_ASSERT(scalar <= static_cast<uint_t>(kIntMaxValue));

    return int4_t{
        static_cast<int_t>(scalar), static_cast<int_t>(scalar),
        static_cast<int_t>(scalar), static_cast<int_t>(scalar)};
}

export constexpr int4_t int4(
    const uint_t x, const uint_t y, const uint_t z, const uint_t w)
{
    FND_ASSERT(x <= static_cast<uint_t>(kIntMaxValue)
        && y <= static_cast<uint_t>(kIntMaxValue)
        && z <= static_cast<uint_t>(kIntMaxValue)
        && w <= static_cast<uint_t>(kIntMaxValue));

    return int4_t{
        static_cast<int_t>(x), static_cast<int_t>(y), static_cast<int_t>(z),
        static_cast<int_t>(w)};
}

export constexpr int4_t int4(
    const uint2_t v, const uint_t z = 0, const uint_t w = 0)
{
    FND_ASSERT(all(v <= static_cast<uint_t>(kIntMaxValue))
        && z <= static_cast<uint_t>(kIntMaxValue)
        && w <= static_cast<uint_t>(kIntMaxValue));

    return int4_t{
        static_cast<int_t>(v.x), static_cast<int_t>(v.y), static_cast<int_t>(z),
        static_cast<int_t>(w)};
}

export constexpr int4_t int4(const uint3_t v, const uint_t w = 0)
{
    FND_ASSERT(all(v <= static_cast<uint_t>(kIntMaxValue))
        && w <= static_cast<uint_t>(kIntMaxValue));

    return int4_t{
        static_cast<int_t>(v.x), static_cast<int_t>(v.y),
        static_cast<int_t>(v.z), static_cast<int_t>(w)};
}

export constexpr int4_t int4(const uint4_t v)
{
    FND_ASSERT(all(v <= static_cast<uint_t>(kIntMaxValue)));

    return int4_t{
        static_cast<int_t>(v.x), static_cast<int_t>(v.y),
        static_cast<int_t>(v.z), static_cast<int_t>(v.w)};
}

// ---------------------------------------------------------------------------
// uint2()
// ---------------------------------------------------------------------------

export constexpr uint2_t uint2(const bool_t scalar)
{
    return uint2_t{scalar ? 1u : 0u, scalar ? 1u : 0u};
}

export constexpr uint2_t uint2(const bool_t x, const bool_t y)
{
    return uint2_t{x ? 1u : 0u, y ? 1u : 0u};
}

export constexpr uint2_t uint2(const bool2_t v)
{
    return uint2_t{v.x ? 1u : 0u, v.y ? 1u : 0u};
}

export constexpr uint2_t uint2(const bool3_t v)
{
    return uint2_t{v.x ? 1u : 0u, v.y ? 1u : 0u};
}

export constexpr uint2_t uint2(const bool4_t v)
{
    return uint2_t{v.x ? 1u : 0u, v.y ? 1u : 0u};
}

export FND_INLINE uint2_t uint2(const float_t scalar)
{
    FND_ASSERT(can_trunc_to_uint(scalar));

    return uint2_t{static_cast<uint_t>(scalar), static_cast<uint_t>(scalar)};
}

export FND_INLINE uint2_t uint2(const float_t x, const float_t y)
{
    FND_ASSERT(can_trunc_to_uint(x) && can_trunc_to_uint(y));

    return uint2_t{static_cast<uint_t>(x), static_cast<uint_t>(y)};
}

export FND_INLINE uint2_t uint2(const float2_t v)
{
    FND_ASSERT(all(can_trunc_to_uint(v)));

    return uint2_t{static_cast<uint_t>(v.x), static_cast<uint_t>(v.y)};
}

export FND_INLINE uint2_t uint2(const float3_t v)
{
    FND_ASSERT(can_trunc_to_uint(v.x) && can_trunc_to_uint(v.y));

    return uint2_t{static_cast<uint_t>(v.x), static_cast<uint_t>(v.y)};
}

export FND_INLINE uint2_t uint2(const float4_t v)
{
    FND_ASSERT(can_trunc_to_uint(v.x) && can_trunc_to_uint(v.y));

    return uint2_t{static_cast<uint_t>(v.x), static_cast<uint_t>(v.y)};
}

export constexpr uint2_t uint2(const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    return uint2_t{static_cast<uint_t>(scalar), static_cast<uint_t>(scalar)};
}

export constexpr uint2_t uint2(const int_t x, const int_t y)
{
    FND_ASSERT(x >= 0 && y >= 0);

    return uint2_t{static_cast<uint_t>(x), static_cast<uint_t>(y)};
}

export constexpr uint2_t uint2(const int2_t v)
{
    FND_ASSERT(all(v >= 0));

    return uint2_t{static_cast<uint_t>(v.x), static_cast<uint_t>(v.y)};
}

export constexpr uint2_t uint2(const int3_t v)
{
    FND_ASSERT(v.x >= 0 && v.y >= 0);

    return uint2_t{static_cast<uint_t>(v.x), static_cast<uint_t>(v.y)};
}

export constexpr uint2_t uint2(const int4_t v)
{
    FND_ASSERT(v.x >= 0 && v.y >= 0);

    return uint2_t{static_cast<uint_t>(v.x), static_cast<uint_t>(v.y)};
}

export constexpr uint2_t uint2(const uint_t scalar)
{
    return uint2_t{scalar, scalar};
}

export constexpr uint2_t uint2(const uint_t x, const uint_t y)
{
    return uint2_t{x, y};
}

export constexpr uint2_t uint2(const uint3_t v)
{
    return uint2_t{v.x, v.y};
}

export constexpr uint2_t uint2(const uint4_t v)
{
    return uint2_t{v.x, v.y};
}

// ---------------------------------------------------------------------------
// uint3()
// ---------------------------------------------------------------------------

export constexpr uint3_t uint3(const bool_t scalar)
{
    return uint3_t{scalar ? 1u : 0u, scalar ? 1u : 0u, scalar ? 1u : 0u};
}

export constexpr uint3_t uint3(const bool_t x, const bool_t y, const bool_t z)
{
    return uint3_t{x ? 1u : 0u, y ? 1u : 0u, z ? 1u : 0u};
}

export constexpr uint3_t uint3(const bool2_t v, const bool_t z = false)
{
    return uint3_t{v.x ? 1u : 0u, v.y ? 1u : 0u, z ? 1u : 0u};
}

export constexpr uint3_t uint3(const bool3_t v)
{
    return uint3_t{v.x ? 1u : 0u, v.y ? 1u : 0u, v.z ? 1u : 0u};
}

export constexpr uint3_t uint3(const bool4_t v)
{
    return uint3_t{v.x ? 1u : 0u, v.y ? 1u : 0u, v.z ? 1u : 0u};
}

export FND_INLINE uint3_t uint3(const float_t scalar)
{
    FND_ASSERT(can_trunc_to_uint(scalar));

    return uint3_t{
        static_cast<uint_t>(scalar), static_cast<uint_t>(scalar),
        static_cast<uint_t>(scalar)};
}

export FND_INLINE uint3_t uint3(
    const float_t x, const float_t y, const float_t z)
{
    FND_ASSERT(can_trunc_to_uint(x) && can_trunc_to_uint(y)
        && can_trunc_to_uint(z));

    return uint3_t{
        static_cast<uint_t>(x), static_cast<uint_t>(y), static_cast<uint_t>(z)};
}

export FND_INLINE uint3_t uint3(const float2_t v, const float_t z = 0)
{
    FND_ASSERT(all(can_trunc_to_uint(v)) && can_trunc_to_uint(z));

    return uint3_t{
        static_cast<uint_t>(v.x), static_cast<uint_t>(v.y),
        static_cast<uint_t>(z)};
}

export FND_INLINE uint3_t uint3(const float3_t v)
{
    FND_ASSERT(all(can_trunc_to_uint(v)));

    return uint3_t{
        static_cast<uint_t>(v.x), static_cast<uint_t>(v.y),
        static_cast<uint_t>(v.z)};
}

export FND_INLINE uint3_t uint3(const float4_t v)
{
    FND_ASSERT(can_trunc_to_uint(v.x) && can_trunc_to_uint(v.y)
        && can_trunc_to_uint(v.z));

    return uint3_t{
        static_cast<uint_t>(v.x), static_cast<uint_t>(v.y),
        static_cast<uint_t>(v.z)};
}

export constexpr uint3_t uint3(const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    return uint3_t{
        static_cast<uint_t>(scalar), static_cast<uint_t>(scalar),
        static_cast<uint_t>(scalar)};
}

export constexpr uint3_t uint3(const int_t x, const int_t y, const int_t z)
{
    FND_ASSERT(x >= 0 && y >= 0 && z >= 0);

    return uint3_t{
        static_cast<uint_t>(x), static_cast<uint_t>(y), static_cast<uint_t>(z)};
}

export constexpr uint3_t uint3(const int2_t v, const int_t z = 0)
{
    FND_ASSERT(all(v >= 0) && z >= 0);

    return uint3_t{
        static_cast<uint_t>(v.x), static_cast<uint_t>(v.y),
        static_cast<uint_t>(z)};
}

export constexpr uint3_t uint3(const int3_t v)
{
    FND_ASSERT(all(v >= 0));

    return uint3_t{
        static_cast<uint_t>(v.x), static_cast<uint_t>(v.y),
        static_cast<uint_t>(v.z)};
}

export constexpr uint3_t uint3(const int4_t v)
{
    FND_ASSERT(v.x >= 0 && v.y >= 0 && v.z >= 0);

    return uint3_t{
        static_cast<uint_t>(v.x), static_cast<uint_t>(v.y),
        static_cast<uint_t>(v.z)};
}

export constexpr uint3_t uint3(const uint_t scalar)
{
    return uint3_t{scalar, scalar, scalar};
}

export constexpr uint3_t uint3(const uint_t x, const uint_t y, const uint_t z)
{
    return uint3_t{x, y, z};
}

export constexpr uint3_t uint3(const uint2_t v, const uint_t z = 0)
{
    return uint3_t{v.x, v.y, z};
}

export constexpr uint3_t uint3(const uint4_t v)
{
    return uint3_t{v.x, v.y, v.z};
}

// ---------------------------------------------------------------------------
// uint4()
// ---------------------------------------------------------------------------

export constexpr uint4_t uint4(const bool_t scalar)
{
    return uint4_t{
        scalar ? 1u : 0u, scalar ? 1u : 0u, scalar ? 1u : 0u, scalar ? 1u : 0u};
}

export constexpr uint4_t uint4(
    const bool_t x, const bool_t y, const bool_t z, const bool_t w)
{
    return uint4_t{x ? 1u : 0u, y ? 1u : 0u, z ? 1u : 0u, w ? 1u : 0u};
}

export constexpr uint4_t uint4(
    const bool2_t v, const bool_t z = false, const bool_t w = false)
{
    return uint4_t{v.x ? 1u : 0u, v.y ? 1u : 0u, z ? 1u : 0u, w ? 1u : 0u};
}

export constexpr uint4_t uint4(const bool3_t v, const bool_t w = false)
{
    return uint4_t{v.x ? 1u : 0u, v.y ? 1u : 0u, v.z ? 1u : 0u, w ? 1u : 0u};
}

export constexpr uint4_t uint4(const bool4_t v)
{
    return uint4_t{v.x ? 1u : 0u, v.y ? 1u : 0u, v.z ? 1u : 0u, v.w ? 1u : 0u};
}

export FND_INLINE uint4_t uint4(const float_t scalar)
{
    FND_ASSERT(can_trunc_to_uint(scalar));

    return uint4_t{
        static_cast<uint_t>(scalar), static_cast<uint_t>(scalar),
        static_cast<uint_t>(scalar), static_cast<uint_t>(scalar)};
}

export FND_INLINE uint4_t uint4(
    const float_t x, const float_t y, const float_t z, const float_t w)
{
    FND_ASSERT(can_trunc_to_uint(x) && can_trunc_to_uint(y)
        && can_trunc_to_uint(z) && can_trunc_to_uint(w));

    return uint4_t{
        static_cast<uint_t>(x), static_cast<uint_t>(y), static_cast<uint_t>(z),
        static_cast<uint_t>(w)};
}

export FND_INLINE uint4_t uint4(
    const float2_t v, const float_t z = 0, const float_t w = 0)
{
    FND_ASSERT(all(can_trunc_to_uint(v)) && can_trunc_to_uint(z)
        && can_trunc_to_uint(w));

    return uint4_t{
        static_cast<uint_t>(v.x), static_cast<uint_t>(v.y),
        static_cast<uint_t>(z), static_cast<uint_t>(w)};
}

export FND_INLINE uint4_t uint4(const float3_t v, const float_t w = 0)
{
    FND_ASSERT(all(can_trunc_to_uint(v)) && can_trunc_to_uint(w));

    return uint4_t{
        static_cast<uint_t>(v.x), static_cast<uint_t>(v.y),
        static_cast<uint_t>(v.z), static_cast<uint_t>(w)};
}

export FND_INLINE uint4_t uint4(const float4_t v)
{
    FND_ASSERT(all(can_trunc_to_uint(v)));

    return uint4_t{
        static_cast<uint_t>(v.x), static_cast<uint_t>(v.y),
        static_cast<uint_t>(v.z), static_cast<uint_t>(v.w)};
}

export constexpr uint4_t uint4(const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    return uint4_t{
        static_cast<uint_t>(scalar), static_cast<uint_t>(scalar),
        static_cast<uint_t>(scalar), static_cast<uint_t>(scalar)};
}

export constexpr uint4_t uint4(
    const int_t x, const int_t y, const int_t z, const int_t w)
{
    FND_ASSERT(x >= 0 && y >= 0 && z >= 0 && w >= 0);

    return uint4_t{
        static_cast<uint_t>(x), static_cast<uint_t>(y), static_cast<uint_t>(z),
        static_cast<uint_t>(w)};
}

export constexpr uint4_t uint4(
    const int2_t v, const int_t z = 0, const int_t w = 0)
{
    FND_ASSERT(all(v >= 0) && z >= 0 && w >= 0);

    return uint4_t{
        static_cast<uint_t>(v.x), static_cast<uint_t>(v.y),
        static_cast<uint_t>(z), static_cast<uint_t>(w)};
}

export constexpr uint4_t uint4(const int3_t v, const int_t w = 0)
{
    FND_ASSERT(all(v >= 0) && w >= 0);

    return uint4_t{
        static_cast<uint_t>(v.x), static_cast<uint_t>(v.y),
        static_cast<uint_t>(v.z), static_cast<uint_t>(w)};
}

export constexpr uint4_t uint4(const int4_t v)
{
    FND_ASSERT(all(v >= 0));

    return uint4_t{
        static_cast<uint_t>(v.x), static_cast<uint_t>(v.y),
        static_cast<uint_t>(v.z), static_cast<uint_t>(v.w)};
}

export constexpr uint4_t uint4(const uint_t scalar)
{
    return uint4_t{scalar, scalar, scalar, scalar};
}

export constexpr uint4_t uint4(
    const uint_t x, const uint_t y, const uint_t z, const uint_t w)
{
    return uint4_t{x, y, z, w};
}

export constexpr uint4_t uint4(
    const uint2_t v, const uint_t z = 0, const uint_t w = 0)
{
    return uint4_t{v.x, v.y, z, w};
}

export constexpr uint4_t uint4(const uint3_t v, const uint_t w = 0)
{
    return uint4_t{v.x, v.y, v.z, w};
}

} // namespace fnd
