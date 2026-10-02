module;
#include "foundation/core/macros.h"

export module foundation.math:matrix_construction;
import foundation.core;
import :matrix_conversion;
import :matrix_float3x3;
import :matrix_float3x4;
import :matrix_float4x4;
import :scalar;
import :vector_conversion;
import :vector_float3;
import :vector_float4;
import :vector_quat;

namespace fnd {

// ---------------------------------------------------------------------------
// make_float3x3_*()
// ---------------------------------------------------------------------------

// Rotation by angle_radians (in radians) about axis, which must be normalized
// (Rodrigues' rotation formula).
// Right-handed: a positive angle_radians rotates
// counter-clockwise when looking from the tip of axis toward the origin.
export FND_INLINE float3x3_t make_float3x3_axis_angle(
    const float3_t axis, const float_t angle_radians)
{
    FND_ASSERT(is_normalized(axis));

    const float_t c = cos(angle_radians);
    const float_t s = sin(angle_radians);
    const float_t omc = 1.0f - c;
    const float_t xx = axis.x * axis.x;
    const float_t xy = axis.x * axis.y;
    const float_t xz = axis.x * axis.z;
    const float_t yy = axis.y * axis.y;
    const float_t yz = axis.y * axis.z;
    const float_t zz = axis.z * axis.z;

    return float3x3_t{
        float3_t{c + omc * xx, omc * xy + axis.z * s, omc * xz - axis.y * s},
        float3_t{omc * xy - axis.z * s, c + omc * yy, omc * yz + axis.x * s},
        float3_t{omc * xz + axis.y * s, omc * yz - axis.x * s, c + omc * zz}};
}

export constexpr float3x3_t make_float3x3_scale(const float3_t s)
{
    return float3x3_t{
        float3_t{s.x, 0, 0}, float3_t{0, s.y, 0}, float3_t{0, 0, s.z}};
}

// ---------------------------------------------------------------------------
// make_float3x4_*()
// ---------------------------------------------------------------------------

// Rotation about the normalized axis, with no translation; see
// make_float3x3_axis_angle for the direction of a positive angle.
export FND_INLINE float3x4_t make_float3x4_axis_angle(
    const float3_t axis, const float_t angle_radians)
{
    FND_ASSERT(is_normalized(axis));

    const float3x3_t rm = make_float3x3_axis_angle(axis, angle_radians);
    return float3x4_t{rm.col0, rm.col1, rm.col2, float3_t::kZero};
}

export constexpr float3x4_t make_float3x4_scale(const float3_t s)
{
    return float3x4_t{
        float3_t{s.x, 0, 0}, float3_t{0, s.y, 0}, float3_t{0, 0, s.z},
        float3_t::kZero};
}

export constexpr float3x4_t make_float3x4_translation(const float3_t t)
{
    return float3x4_t{float3_t::kUnitX, float3_t::kUnitY, float3_t::kUnitZ, t};
}

export constexpr float3x4_t make_float3x4_trs(
    const float3_t t, const float3x3_t& mrs)
{
    return float3x4_t{mrs.col0, mrs.col1, mrs.col2, t};
}

export FND_INLINE float3x4_t make_float3x4_trs(
    const float3_t t, const quat_t r, const float3_t s)
{
    FND_ASSERT(is_normalized(r));

    // the scale is diagonal, so the columns of the rotation are scaled instead.
    const float3x3_t rm = make_float3x3(r);
    return float3x4_t{rm.col0 * s.x, rm.col1 * s.y, rm.col2 * s.z, t};
}

// ---------------------------------------------------------------------------
// make_float4x4_*()
// ---------------------------------------------------------------------------

export FND_INLINE float4x4_t make_float4x4_axis_angle(
    const float3_t axis, const float_t angle_radians)
{
    FND_ASSERT(is_normalized(axis));

    const float3x3_t rm = make_float3x3_axis_angle(axis, angle_radians);
    return float4x4_t{
        float4(rm.col0, 0), float4(rm.col1, 0), float4(rm.col2, 0),
        float4_t::kUnitW};
}

export constexpr float4x4_t make_float4x4_scale(const float3_t s)
{
    return float4x4_t{
        float4_t{s.x, 0, 0, 0}, float4_t{0, s.y, 0, 0}, float4_t{0, 0, s.z, 0},
        float4_t::kUnitW};
}

export constexpr float4x4_t make_float4x4_translation(const float3_t t)
{
    return float4x4_t{
        float4_t::kUnitX, float4_t::kUnitY, float4_t::kUnitZ, float4(t, 1)};
}

export constexpr float4x4_t make_float4x4_trs(
    const float3_t t, const float3x3_t& mrs)
{
    return float4x4_t{
        float4(mrs.col0, 0), float4(mrs.col1, 0), float4(mrs.col2, 0),
        float4(t, 1)};
}

export FND_INLINE float4x4_t make_float4x4_trs(
    const float3_t t, const quat_t r, const float3_t s)
{
    FND_ASSERT(is_normalized(r));

    // the scale is diagonal, so the columns of the rotation are scaled instead.
    const float3x3_t rm = make_float3x3(r);
    return float4x4_t{
        float4(rm.col0 * s.x, 0), float4(rm.col1 * s.y, 0),
        float4(rm.col2 * s.z, 0), float4(t, 1)};
}

} // namespace fnd
