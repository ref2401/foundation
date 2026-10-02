module;
#include "foundation/core/macros.h"

export module foundation.math:matrix_conversion;
import foundation.core;
import :matrix_float3x3;
import :matrix_float3x4;
import :matrix_float4x4;
import :scalar;
import :vector_conversion;
import :vector_float3;
import :vector_float4;
import :vector_quat;

namespace fnd {

// The rotation matrix of the unit quaternion q as a float3x3_t, float3x4_t or
// float4x4_t: mul(rm, v) rotates v as mul(q, v) does.
// A float3x4_t has no translation.
// A float4x4_t also has the bottom row 0, 0, 0, 1.
template<typename TMatrix> TMatrix make_rotation_matrix(const quat_t q)
{
    static_assert(
        is_same<TMatrix, float3x3_t>() || is_same<TMatrix, float3x4_t>()
        || is_same<TMatrix, float4x4_t>());
    FND_ASSERT(is_normalized(q));

    // The components are doubled first, so each product below already holds
    // the factor 2 of the rotation matrix formula.
    const float_t x2 = q.x + q.x;
    const float_t y2 = q.y + q.y;
    const float_t z2 = q.z + q.z;
    const float_t xx2 = q.x * x2;
    const float_t xy2 = q.x * y2;
    const float_t xz2 = q.x * z2;
    const float_t yy2 = q.y * y2;
    const float_t yz2 = q.y * z2;
    const float_t zz2 = q.z * z2;
    const float_t wx2 = q.w * x2;
    const float_t wy2 = q.w * y2;
    const float_t wz2 = q.w * z2;

    // NOTE:
    // Performance (MSVC): the components are kept as scalars. Gathered into
    // float3_t columns first and assigned to rm, the float4x4_t is assembled
    // through the stack: 8 ns instead of 3 ns per call, inlined.
    //
    // mRC is the component in row R and column C.
    const float_t m00 = (1 - yy2) - zz2;
    const float_t m10 = xy2 + wz2;
    const float_t m20 = xz2 - wy2;
    const float_t m01 = xy2 - wz2;
    const float_t m11 = (1 - xx2) - zz2;
    const float_t m21 = yz2 + wx2;
    const float_t m02 = xz2 + wy2;
    const float_t m12 = yz2 - wx2;
    const float_t m22 = (1 - xx2) - yy2;

    TMatrix rm;
    if constexpr (is_same<TMatrix, float3x3_t>()) {
        rm = float3x3_t{m00, m10, m20, m01, m11, m21, m02, m12, m22};
    }
    else if constexpr (is_same<TMatrix, float3x4_t>()) {
        rm = float3x4_t{m00, m10, m20, m01, m11, m21, m02, m12, m22, 0, 0, 0};
    }
    else {
        rm = float4x4_t{
            m00, m10, m20, 0, m01, m11, m21, 0, m02, m12, m22, 0, 0, 0, 0, 1};
    }

    return rm;
}

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

export FND_INLINE float3x3_t make_float3x3(const quat_t q)
{
    return make_rotation_matrix<float3x3_t>(q);
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

export FND_INLINE float3x4_t make_float3x4(const quat_t q)
{
    return make_rotation_matrix<float3x4_t>(q);
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

export FND_INLINE float4x4_t make_float4x4(const quat_t q)
{
    return make_rotation_matrix<float4x4_t>(q);
}

// ---------------------------------------------------------------------------
// make_quat()
// ---------------------------------------------------------------------------

// The rotation of m as a unit quaternion. m may carry a positive scale per
// axis: its columns are normalized first. They must be orthogonal and form a
// right-handed basis (determinant > 0): a reflection is not a rotation, and
// no quaternion represents it.
export FND_INLINE quat_t make_quat(const float3x3_t& m)
{
    const float3_t c0 = normalize(m.col0);
    const float3_t c1 = normalize(m.col1);
    const float3_t c2 = normalize(m.col2);
    // Columns are orthogonal
    FND_ASSERT(approx_equal(dot(c0, c1), 0.0f, 1e-4f));
    FND_ASSERT(approx_equal(dot(c0, c2), 0.0f, 1e-4f));
    FND_ASSERT(approx_equal(dot(c1, c2), 0.0f, 1e-4f));
    // Columns form a right-handed basis, so the matrix is a rotation and not
    // a rotation combined with a mirror.
    FND_ASSERT(dot(c0, cross(c1, c2)) > 0);

    // NOTE: Shepperd's method
    const float_t m00 = c0.x;
    const float_t m11 = c1.y;
    const float_t m22 = c2.z;
    const float_t trace = m00 + m11 + m22;

    quat_t res_quat;
    if (trace >= m00 && trace >= m11 && trace >= m22) {
        const float_t w = 0.5f * sqrt(1 + trace);
        const float_t s = 0.25f / w;
        res_quat = quat_t{
            (c1.z - c2.y) * s, (c2.x - c0.z) * s, (c0.y - c1.x) * s, w};
    }
    else if (m00 >= m11 && m00 >= m22) {
        const float_t x = 0.5f * sqrt(1 + m00 - m11 - m22);
        const float_t s = 0.25f / x;
        res_quat = quat_t{
            x, (c1.x + c0.y) * s, (c2.x + c0.z) * s, (c1.z - c2.y) * s};
    }
    else if (m11 >= m22) {
        const float_t y = 0.5f * sqrt(1 - m00 + m11 - m22);
        const float_t s = 0.25f / y;
        res_quat = quat_t{
            (c1.x + c0.y) * s, y, (c2.y + c1.z) * s, (c2.x - c0.z) * s};
    }
    else {
        const float_t z = 0.5f * sqrt(1 - m00 - m11 + m22);
        const float_t s = 0.25f / z;
        res_quat = quat_t{
            (c2.x + c0.z) * s, (c2.y + c1.z) * s, z, (c0.y - c1.x) * s};
    }

    return res_quat;
}

export FND_INLINE quat_t make_quat(const float3x4_t& m)
{
    return make_quat(make_float3x3(m));
}

export FND_INLINE quat_t make_quat(const float4x4_t& m)
{
    return make_quat(make_float3x3(m));
}

} // namespace fnd
