module;
#include "foundation/core/macros.h"

export module foundation.math:matrix_float3x4;
import foundation.core;
import :matrix_float3x3;
import :vector_float3;
import :vector_float4;

namespace fnd {

// NOTE:
// An affine transform: 3 rows and 4 columns. col0-col2 are the linear part
// (rotation, scale, ...) and col3 is the translation.
// The math treats it as a 4x4 matrix whose implicit bottom row is {0, 0, 0, 1},
// so the product of two float3x4_t is their composition,
// and the inverse is the inverse transform.
export struct float3x4_t final {
    static const float3x4_t kZero;
    static const float3x4_t kIdentity;

    float3_t col0;
    float3_t col1;
    float3_t col2;
    float3_t col3;

    constexpr float3x4_t() = default;

    constexpr float3x4_t(
        const float3_t c0, const float3_t c1, const float3_t c2,
        const float3_t c3)
        : col0{c0}, col1{c1}, col2{c2}, col3{c3}
    {
    }

    // The components are given in column-major order, column by column, as
    // they are stored: mRC is the component in row R and column C.
    constexpr float3x4_t(
        const float_t m00, const float_t m10, const float_t m20,
        const float_t m01, const float_t m11, const float_t m21,
        const float_t m02, const float_t m12, const float_t m22,
        const float_t m03, const float_t m13, const float_t m23)
        : col0{m00, m10, m20},
          col1{m01, m11, m21},
          col2{m02, m12, m22},
          col3{m03, m13, m23}
    {
    }
};

constexpr float3x4_t float3x4_t::kZero{
    float3_t{0, 0, 0}, float3_t{0, 0, 0}, float3_t{0, 0, 0}, float3_t{0, 0, 0}};
constexpr float3x4_t float3x4_t::kIdentity{
    float3_t{1, 0, 0}, float3_t{0, 1, 0}, float3_t{0, 0, 1}, float3_t{0, 0, 0}};

export constexpr float3x4_t operator-(const float3x4_t& m)
{
    return float3x4_t{-m.col0, -m.col1, -m.col2, -m.col3};
}

export constexpr bool_t operator==(const float3x4_t& a, const float3x4_t& b)
{
    return all(a.col0 == b.col0) && all(a.col1 == b.col1)
        && all(a.col2 == b.col2) && all(a.col3 == b.col3);
}

export constexpr bool_t operator!=(const float3x4_t& a, const float3x4_t& b)
{
    return !(a == b);
}

export constexpr float3x4_t operator*(const float3x4_t& m, const float_t scalar)
{
    return float3x4_t{
        m.col0 * scalar, m.col1 * scalar, m.col2 * scalar, m.col3 * scalar};
}

export constexpr float3x4_t operator*(const float_t scalar, const float3x4_t& m)
{
    return float3x4_t{
        scalar * m.col0, scalar * m.col1, scalar * m.col2, scalar * m.col3};
}

// Composition: a * b applies b first, then a. Both are 4x4 matrices with the
// implicit bottom row 0, 0, 0, 1, so the linear part is a.linear * b.linear
// and the translation is a.linear * b.col3 + a.col3.
export constexpr float3x4_t operator*(const float3x4_t& a, const float3x4_t& b)
{
    // NOTE:
    // Performance (MSVC): float3_t columns are 12 bytes, so no form of this
    // product gets 4-wide SSE; the best MSVC does is x and y two at a time
    // plus a scalar z. The obvious a.col0 * b.col0.x + ... on float3_t
    // temporaries does reach that shape in a non-inlined call (10 ns), but
    // inlined into a loop it falls back to fully scalar code (8 ns). Writing
    // the sums out per component keeps the vectorized shape inlined as well
    // (~6 ns) at no cost to the non-inlined call.
    //
    // a and b stay const&: by value helps inlined (~6 ns), but a non-inlined
    // call then costs 17 ns instead of 10 ns.
    return float3x4_t{
        float3_t{
            a.col0.x * b.col0.x + a.col1.x * b.col0.y + a.col2.x * b.col0.z,
            a.col0.y * b.col0.x + a.col1.y * b.col0.y + a.col2.y * b.col0.z,
            a.col0.z * b.col0.x + a.col1.z * b.col0.y + a.col2.z * b.col0.z},
        float3_t{
            a.col0.x * b.col1.x + a.col1.x * b.col1.y + a.col2.x * b.col1.z,
            a.col0.y * b.col1.x + a.col1.y * b.col1.y + a.col2.y * b.col1.z,
            a.col0.z * b.col1.x + a.col1.z * b.col1.y + a.col2.z * b.col1.z},
        float3_t{
            a.col0.x * b.col2.x + a.col1.x * b.col2.y + a.col2.x * b.col2.z,
            a.col0.y * b.col2.x + a.col1.y * b.col2.y + a.col2.y * b.col2.z,
            a.col0.z * b.col2.x + a.col1.z * b.col2.y + a.col2.z * b.col2.z},
        float3_t{
            a.col0.x * b.col3.x + a.col1.x * b.col3.y + a.col2.x * b.col3.z + a.col3.x,
            a.col0.y * b.col3.x + a.col1.y * b.col3.y + a.col2.y * b.col3.z + a.col3.y,
            a.col0.z * b.col3.x + a.col1.z * b.col3.y + a.col2.z * b.col3.z + a.col3.z}};
}

export constexpr float3x4_t operator/(const float3x4_t& m, const float_t scalar)
{
    FND_ASSERT(scalar != 0.0f);

    return float3x4_t{
        m.col0 / scalar, m.col1 / scalar, m.col2 / scalar, m.col3 / scalar};
}

export constexpr float3x4_t& operator*=(float3x4_t& a, const float_t scalar)
{
    a = a * scalar;
    return a;
}

export constexpr float3x4_t& operator*=(float3x4_t& a, const float3x4_t& b)
{
    a = a * b;
    return a;
}

export constexpr float3x4_t& operator/=(float3x4_t& a, const float_t scalar)
{
    FND_ASSERT(scalar != 0.0f);

    a = a / scalar;
    return a;
}

export FND_INLINE bool_t approx_equal(
    const float3x4_t& a, const float3x4_t& b,
    const float_t max_abs_diff = 1e-5f)
{
    return all(approx_equal(a.col0, b.col0, max_abs_diff))
        && all(approx_equal(a.col1, b.col1, max_abs_diff))
        && all(approx_equal(a.col2, b.col2, max_abs_diff))
        && all(approx_equal(a.col3, b.col3, max_abs_diff));
}

// The largest of the twelve components. A NaN component is ignored, as for
// the float_t max.
export FND_INLINE float_t cmax(const float3x4_t& m)
{
    return max(
        max(cmax(m.col0), cmax(m.col1)), max(cmax(m.col2), cmax(m.col3)));
}

// The smallest of the twelve components. A NaN component is ignored, as for
// the float_t min.
export FND_INLINE float_t cmin(const float3x4_t& m)
{
    return min(
        min(cmin(m.col0), cmin(m.col1)), min(cmin(m.col2), cmin(m.col3)));
}

export constexpr float3_t column0(const float3x4_t& m)
{
    return m.col0;
}

export constexpr float3_t column1(const float3x4_t& m)
{
    return m.col1;
}

export constexpr float3_t column2(const float3x4_t& m)
{
    return m.col2;
}

export constexpr float3_t column3(const float3x4_t& m)
{
    return m.col3;
}

// The determinant of the 4x4 matrix.
// Expanding it along the implicit bottom
// row 0, 0, 0, 1 leaves only the determinant of the linear part (col0-col2),
// so the translation does not change it.
export constexpr float_t determinant(const float3x4_t& m)
{
    return dot(m.col0, cross(m.col1, m.col2));
}

export constexpr float3x4_t inverse(const float3x4_t& m)
{
    // The inverse of the 4x4 matrix. With the bottom row 0, 0, 0, 1, the
    // inverse has that bottom row too:
    //   | L  t |^-1   | inverse(L)  -inverse(L) * t |
    //   | 0  1 |    = | 0            1              |
    // so it is again a float3x4_t. The float3x3_t inverse asserts that the
    // linear part is not singular.
    const float3x3_t m_inv_linear = inverse(float3x3_t{m.col0, m.col1, m.col2});
    return float3x4_t{
        m_inv_linear.col0, m_inv_linear.col1, m_inv_linear.col2,
        -mul(m_inv_linear, m.col3)};
}

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

// Translation t combined with the linear part mrs (rotation and scale): mrs
// is applied first, then t. The same as make_float3x4_translation(t) * mrs.
export constexpr float3x4_t make_float3x4_trs(
    const float3_t t, const float3x3_t& mrs)
{
    return float3x4_t{mrs.col0, mrs.col1, mrs.col2, t};
}

// m times the column vector v; v.w scales the translation (1 for a point, 0
// for a direction).
export constexpr float3_t mul(const float3x4_t& m, const float4_t v)
{
    return m.col0 * v.x + m.col1 * v.y + m.col2 * v.z + m.col3 * v.w;
}

// Transforms the direction v: the linear part only, no translation.
export constexpr float3_t mul_direction(const float3x4_t& m, const float3_t v)
{
    return m.col0 * v.x + m.col1 * v.y + m.col2 * v.z;
}

// Transforms the point p: the linear part and then the translation.
export constexpr float3_t mul_point(const float3x4_t& m, const float3_t p)
{
    return m.col0 * p.x + m.col1 * p.y + m.col2 * p.z + m.col3;
}

export constexpr float4_t row0(const float3x4_t& m)
{
    return float4_t{m.col0.x, m.col1.x, m.col2.x, m.col3.x};
}

export constexpr float4_t row1(const float3x4_t& m)
{
    return float4_t{m.col0.y, m.col1.y, m.col2.y, m.col3.y};
}

export constexpr float4_t row2(const float3x4_t& m)
{
    return float4_t{m.col0.z, m.col1.z, m.col2.z, m.col3.z};
}

export constexpr void set_column0(float3x4_t& m, const float3_t c)
{
    m.col0 = c;
}

export constexpr void set_column1(float3x4_t& m, const float3_t c)
{
    m.col1 = c;
}

export constexpr void set_column2(float3x4_t& m, const float3_t c)
{
    m.col2 = c;
}

export constexpr void set_column3(float3x4_t& m, const float3_t c)
{
    m.col3 = c;
}

export constexpr void set_row0(float3x4_t& m, const float4_t r)
{
    m.col0.x = r.x;
    m.col1.x = r.y;
    m.col2.x = r.z;
    m.col3.x = r.w;
}

export constexpr void set_row1(float3x4_t& m, const float4_t r)
{
    m.col0.y = r.x;
    m.col1.y = r.y;
    m.col2.y = r.z;
    m.col3.y = r.w;
}

export constexpr void set_row2(float3x4_t& m, const float4_t r)
{
    m.col0.z = r.x;
    m.col1.z = r.y;
    m.col2.z = r.z;
    m.col3.z = r.w;
}

} // namespace fnd
