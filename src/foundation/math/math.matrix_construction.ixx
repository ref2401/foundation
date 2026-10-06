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

// Orthographic projection from the right-handed view space (see
// make_float4x4_view_rh) to the Direct3D 12 clip space: left-handed, OX right
// and OY up in [-1, 1], depth OZ in [0, 1].
// The view volume is the width_vs x height_vs box centered on the -OZ axis,
// from near_dist_vs (ndc depth 0) to far_dist_vs (ndc depth 1) in front of the
// camera.
// near_dist_vs and far_dist_vs are distances along the viewing direction -OZ,
// not z coordinates: the near and far planes are z_vs = -near_dist_vs and
// z_vs = -far_dist_vs. A negative near_dist_vs puts the near plane behind the
// camera, at z_vs > 0.
// w stays 1, so clip space and NDC coincide.
// The OZ row mirrors the depth axis: that turns the right-handed view space
// into the left-handed clip space.
export constexpr float4x4_t make_float4x4_ortho_rh_to_dx12(
    const float_t width_vs, const float_t height_vs, const float_t near_dist_vs,
    const float_t far_dist_vs)
{
    FND_ASSERT(width_vs > 0);
    FND_ASSERT(height_vs > 0);
    // Negative or zero near_dist_vs is valid for orthographic projection:
    // geometry behind the camera plane still projects.
    FND_ASSERT(near_dist_vs < far_dist_vs);

    // z_vs = -near_dist_vs goes to depth 0 and z_vs = -far_dist_vs to depth 1.
    const float_t rcp_depth_vs = 1 / (near_dist_vs - far_dist_vs);
    return float4x4_t{
        2 / width_vs, 0, 0, 0, 0, 2 / height_vs, 0, 0, 0, 0, rcp_depth_vs, 0, 0,
        0, near_dist_vs * rcp_depth_vs, 1};
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

// The view matrix of a camera at position_ws looking at target_ws (gluLookAt):
// world space to a right-handed view space in which the camera is at the
// origin and looks along -z, +x is right and +y is up.
// up_ws gives the vertical direction:
//  It need not be normalized or perpendicular to target_ws - position_ws, only
//  not parallel to it.
export FND_INLINE float4x4_t make_float4x4_view_rh(
    const float3_t position_ws, const float3_t target_ws, const float3_t up_ws)
{
    // position_ws == target_ws
    FND_ASSERT(length_sqr(target_ws - position_ws) > kFloatMinNormal);

    const float3_t f_ws = normalize(target_ws - position_ws);
    // up_ws is not parallel to f_ws
    FND_ASSERT(length_sqr(cross(f_ws, up_ws)) > kFloatMinNormal);

    // The camera's basis in world space: right r_ws and up u_ws, forward f_ws.
    // The view matrix is the inverse of the camera's rotation
    // [r_ws | u_ws | -f_ws] and translation position_ws: the transposed
    // rotation, and -position_ws rotated by it.
    const float3_t r_ws = normalize(cross(f_ws, up_ws));
    const float3_t u_ws = cross(r_ws, f_ws);

    return float4x4_t{
        r_ws.x, u_ws.x, -f_ws.x, 0, r_ws.y, u_ws.y, -f_ws.y, 0, r_ws.z, u_ws.z,
        -f_ws.z, 0, -dot(r_ws, position_ws), -dot(u_ws, position_ws),
        dot(f_ws, position_ws), 1};
}

} // namespace fnd
