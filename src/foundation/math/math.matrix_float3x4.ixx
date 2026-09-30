module;
#include "foundation/core/macros.h"

export module foundation.math:matrix_float3x4;
import foundation.core;
import :matrix_float3x3;
import :scalar;
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
    return float3x4_t{
        a.col0 * b.col0.x + a.col1 * b.col0.y + a.col2 * b.col0.z,
        a.col0 * b.col1.x + a.col1 * b.col1.y + a.col2 * b.col1.z,
        a.col0 * b.col2.x + a.col1 * b.col2.y + a.col2 * b.col2.z,
        a.col0 * b.col3.x + a.col1 * b.col3.y + a.col2 * b.col3.z + a.col3};
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
    // so it is again a float3x4_t.
    // The rows of the inverse linear part are the cross products of pairs of
    // columns, divided by the determinant (dot(col0, cross(col1, col2))).
    const float3_t r0 = cross(m.col1, m.col2);
    const float3_t r1 = cross(m.col2, m.col0);
    const float3_t r2 = cross(m.col0, m.col1);
    const float_t det = dot(m.col0, r0);
    FND_ASSERT(det != 0.0f); // the linear part is singular

    return float3x4_t{
        float3_t{r0.x, r1.x, r2.x} / det, float3_t{r0.y, r1.y, r2.y} / det,
        float3_t{r0.z, r1.z, r2.z} / det,
        -float3_t{dot(r0, m.col3), dot(r1, m.col3), dot(r2, m.col3)} / det};
}

export FND_INLINE float3x4_t make_float3x4_rotation(
    const float3_t axis, const float_t angle_angle)
{
    const float3x3_t rm = make_float3x3_rotation(axis, angle_angle);
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

// m times the column vector v; v.w scales the translation (1 for a point, 0
// for a direction).
export constexpr float3_t mul(const float3x4_t& m, const float4_t v)
{
    return m.col0 * v.x + m.col1 * v.y + m.col2 * v.z + m.col3 * v.w;
}

// Transforms the point p: the linear part and then the translation.
export constexpr float3_t mul_point(const float3x4_t& m, const float3_t p)
{
    return m.col0 * p.x + m.col1 * p.y + m.col2 * p.z + m.col3;
}

// Transforms the direction v: the linear part only, no translation.
export constexpr float3_t mul_direction(const float3x4_t& m, const float3_t v)
{
    return m.col0 * v.x + m.col1 * v.y + m.col2 * v.z;
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
