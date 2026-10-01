module;
#include "foundation/core/macros.h"

export module foundation.math:matrix_conversion;
import foundation.core;
import :matrix_float3x3;
import :matrix_float3x4;
import :matrix_float4x4;
import :vector_conversion;
import :vector_float3;
import :vector_float4;

namespace fnd {

// ---------------------------------------------------------------------------
// make_float3x3()
// ---------------------------------------------------------------------------

// The linear part; the translation is dropped.
export constexpr float3x3_t make_float3x3(const float3x4_t& m)
{
    return float3x3_t{m.col0, m.col1, m.col2};
}

// The upper-left 3x3; the translation and the bottom row are dropped.
export constexpr float3x3_t make_float3x3(const float4x4_t& m)
{
    return float3x3_t{float3(m.col0), float3(m.col1), float3(m.col2)};
}

// ---------------------------------------------------------------------------
// make_float3x4()
// ---------------------------------------------------------------------------

// m as the linear part, with no translation.
export constexpr float3x4_t make_float3x4(const float3x3_t& m)
{
    return float3x4_t{m.col0, m.col1, m.col2, float3_t::kZero};
}

// The top three rows; the bottom row is dropped.
export constexpr float3x4_t make_float3x4(const float4x4_t& m)
{
    return float3x4_t{
        float3(m.col0), float3(m.col1), float3(m.col2), float3(m.col3)};
}

// ---------------------------------------------------------------------------
// make_float4x4()
// ---------------------------------------------------------------------------

// m as the upper-left 3x3, with no translation and the bottom row 0, 0, 0, 1.
export constexpr float4x4_t make_float4x4(const float3x3_t& m)
{
    return float4x4_t{
        float4(m.col0, 0), float4(m.col1, 0), float4(m.col2, 0),
        float4_t::kUnitW};
}

// m with its implicit bottom row 0, 0, 0, 1.
export constexpr float4x4_t make_float4x4(const float3x4_t& m)
{
    return float4x4_t{
        float4(m.col0, 0), float4(m.col1, 0), float4(m.col2, 0),
        float4(m.col3, 1)};
}

} // namespace fnd
