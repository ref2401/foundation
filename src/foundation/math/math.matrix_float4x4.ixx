module;
#include "foundation/core/macros.h"

export module foundation.math:matrix_float4x4;
import foundation.core;
import :matrix_float3x3;
import :vector_conversion;
import :vector_float3;
import :vector_float4;

namespace fnd {

// NOTE:
// A general 4x4 matrix: it stores affine transforms (bottom row 0, 0, 0, 1)
// and projections alike. Column-major storage, column vectors: mul(m, v).
export struct float4x4_t final {
    static const float4x4_t kZero;
    static const float4x4_t kIdentity;

    float4_t col0;
    float4_t col1;
    float4_t col2;
    float4_t col3;

    constexpr float4x4_t() = default;

    constexpr float4x4_t(
        const float4_t c0, const float4_t c1, const float4_t c2,
        const float4_t c3)
        : col0{c0}, col1{c1}, col2{c2}, col3{c3}
    {
    }

    // The components are given in column-major order, column by column, as
    // they are stored: mRC is the component in row R and column C.
    constexpr float4x4_t(
        const float_t m00, const float_t m10, const float_t m20,
        const float_t m30, const float_t m01, const float_t m11,
        const float_t m21, const float_t m31, const float_t m02,
        const float_t m12, const float_t m22, const float_t m32,
        const float_t m03, const float_t m13, const float_t m23,
        const float_t m33)
        : col0{m00, m10, m20, m30},
          col1{m01, m11, m21, m31},
          col2{m02, m12, m22, m32},
          col3{m03, m13, m23, m33}
    {
    }
};

constexpr float4x4_t float4x4_t::kZero{
    float4_t{0, 0, 0, 0}, float4_t{0, 0, 0, 0}, float4_t{0, 0, 0, 0},
    float4_t{0, 0, 0, 0}};
constexpr float4x4_t float4x4_t::kIdentity{
    float4_t{1, 0, 0, 0}, float4_t{0, 1, 0, 0}, float4_t{0, 0, 1, 0},
    float4_t{0, 0, 0, 1}};

export constexpr float4x4_t operator-(const float4x4_t& m)
{
    return float4x4_t{-m.col0, -m.col1, -m.col2, -m.col3};
}

export constexpr bool_t operator==(const float4x4_t& a, const float4x4_t& b)
{
    return all(a.col0 == b.col0) && all(a.col1 == b.col1)
        && all(a.col2 == b.col2) && all(a.col3 == b.col3);
}

export constexpr bool_t operator!=(const float4x4_t& a, const float4x4_t& b)
{
    return !(a == b);
}

export constexpr float4x4_t operator*(const float4x4_t& m, const float_t scalar)
{
    return float4x4_t{
        m.col0 * scalar, m.col1 * scalar, m.col2 * scalar, m.col3 * scalar};
}

export constexpr float4x4_t operator*(const float_t scalar, const float4x4_t& m)
{
    return float4x4_t{
        scalar * m.col0, scalar * m.col1, scalar * m.col2, scalar * m.col3};
}

// Matrix product: column j of a * b is a times column j of b.
export constexpr float4x4_t operator*(const float4x4_t a, const float4x4_t b)
{
    // NOTE:
    // Performance (MSVC): the obvious a.col0 * b.col0.x + a.col1 * b.col0.y
    // + ... on float4_t temporaries compiles to ~250 instructions per matrix
    // product (15 ns), and reading b's columns through the reference while
    // the result is written costs reloads (~9 ns).
    // Passing each column of b by value to mul_column,
    // which writes the product out per component, gives ~90 vectorized
    // instructions (5.6 ns).
    //
    // a and b are taken by value rather than by const&. Inlined, the result
    // is written straight into the destination while a and b are still read;
    // through references the compiler must assume they may overlap (as in
    // m = m * m) and falls back to mostly scalar code (10 ns). As copies they
    // cannot overlap, and the product stays vectorized (4 ns). The cost is on
    // a non-inlined call: Win64 passes a large struct by value as a pointer to
    // a copy made by the caller, 7.5 ns instead of 5.6 ns (const ref).
    const auto mul_column = [&a](const float4_t c) {
        return float4_t{
            a.col0.x * c.x + a.col1.x * c.y + a.col2.x * c.z + a.col3.x * c.w,
            a.col0.y * c.x + a.col1.y * c.y + a.col2.y * c.z + a.col3.y * c.w,
            a.col0.z * c.x + a.col1.z * c.y + a.col2.z * c.z + a.col3.z * c.w,
            a.col0.w * c.x + a.col1.w * c.y + a.col2.w * c.z + a.col3.w * c.w};
    };

    return float4x4_t{
        mul_column(b.col0), mul_column(b.col1), mul_column(b.col2),
        mul_column(b.col3)};
}

export constexpr float4x4_t operator/(const float4x4_t& m, const float_t scalar)
{
    FND_ASSERT(scalar != 0.0f);

    return float4x4_t{
        m.col0 / scalar, m.col1 / scalar, m.col2 / scalar, m.col3 / scalar};
}

export constexpr float4x4_t& operator*=(float4x4_t& a, const float_t scalar)
{
    a = a * scalar;
    return a;
}

export constexpr float4x4_t& operator*=(float4x4_t& a, const float4x4_t& b)
{
    a = a * b;
    return a;
}

export constexpr float4x4_t& operator/=(float4x4_t& a, const float_t scalar)
{
    FND_ASSERT(scalar != 0.0f);

    a = a / scalar;
    return a;
}

export FND_INLINE bool_t approx_equal(
    const float4x4_t& a, const float4x4_t& b,
    const float_t max_abs_diff = 1e-5f)
{
    return all(approx_equal(a.col0, b.col0, max_abs_diff))
        && all(approx_equal(a.col1, b.col1, max_abs_diff))
        && all(approx_equal(a.col2, b.col2, max_abs_diff))
        && all(approx_equal(a.col3, b.col3, max_abs_diff));
}

// The largest of the sixteen components. A NaN component is ignored, as for
// the float_t max.
export FND_INLINE float_t cmax(const float4x4_t& m)
{
    return max(
        max(cmax(m.col0), cmax(m.col1)), max(cmax(m.col2), cmax(m.col3)));
}

// The smallest of the sixteen components. A NaN component is ignored, as for
// the float_t min.
export FND_INLINE float_t cmin(const float4x4_t& m)
{
    return min(
        min(cmin(m.col0), cmin(m.col1)), min(cmin(m.col2), cmin(m.col3)));
}

export constexpr float4_t column0(const float4x4_t& m)
{
    return m.col0;
}

export constexpr float4_t column1(const float4x4_t& m)
{
    return m.col1;
}

export constexpr float4_t column2(const float4x4_t& m)
{
    return m.col2;
}

export constexpr float4_t column3(const float4x4_t& m)
{
    return m.col3;
}

// Laplace expansion by complementary minors: each 2x2 minor of rows 0-1 is
// multiplied by the complementary 2x2 minor of rows 2-3 (rows 0, 1, 2, 3 are
// the x, y, z, w components of the columns).
export constexpr float_t determinant(const float4x4_t& m)
{
    // Minors of rows 0-1: aIJ uses columns I and J.
    const float_t a01 = m.col0.x * m.col1.y - m.col1.x * m.col0.y;
    const float_t a02 = m.col0.x * m.col2.y - m.col2.x * m.col0.y;
    const float_t a03 = m.col0.x * m.col3.y - m.col3.x * m.col0.y;
    const float_t a12 = m.col1.x * m.col2.y - m.col2.x * m.col1.y;
    const float_t a13 = m.col1.x * m.col3.y - m.col3.x * m.col1.y;
    const float_t a23 = m.col2.x * m.col3.y - m.col3.x * m.col2.y;
    // Minors of rows 2-3: bIJ uses columns I and J.
    const float_t b01 = m.col0.z * m.col1.w - m.col1.z * m.col0.w;
    const float_t b02 = m.col0.z * m.col2.w - m.col2.z * m.col0.w;
    const float_t b03 = m.col0.z * m.col3.w - m.col3.z * m.col0.w;
    const float_t b12 = m.col1.z * m.col2.w - m.col2.z * m.col1.w;
    const float_t b13 = m.col1.z * m.col3.w - m.col3.z * m.col1.w;
    const float_t b23 = m.col2.z * m.col3.w - m.col3.z * m.col2.w;

    return a01 * b23 - a02 * b13 + a03 * b12 + a12 * b03 - a13 * b02
        + a23 * b01;
}

// The adjugate (the transposed cofactors) divided by the determinant. Column C
// of the inverse holds the cofactors of row C of m. A cofactor of a row 0-1
// component expands along the other of rows 0-1 with the minors of rows 2-3,
// and a cofactor of a row 2-3 component along the other of rows 2-3 with the
// minors of rows 0-1; the same 2x2 minors give the determinant.
export constexpr float4x4_t inverse(const float4x4_t& m)
{
    // Minors of rows 0-1: aIJ uses columns I and J.
    const float_t a01 = m.col0.x * m.col1.y - m.col1.x * m.col0.y;
    const float_t a02 = m.col0.x * m.col2.y - m.col2.x * m.col0.y;
    const float_t a03 = m.col0.x * m.col3.y - m.col3.x * m.col0.y;
    const float_t a12 = m.col1.x * m.col2.y - m.col2.x * m.col1.y;
    const float_t a13 = m.col1.x * m.col3.y - m.col3.x * m.col1.y;
    const float_t a23 = m.col2.x * m.col3.y - m.col3.x * m.col2.y;
    // Minors of rows 2-3: bIJ uses columns I and J.
    const float_t b01 = m.col0.z * m.col1.w - m.col1.z * m.col0.w;
    const float_t b02 = m.col0.z * m.col2.w - m.col2.z * m.col0.w;
    const float_t b03 = m.col0.z * m.col3.w - m.col3.z * m.col0.w;
    const float_t b12 = m.col1.z * m.col2.w - m.col2.z * m.col1.w;
    const float_t b13 = m.col1.z * m.col3.w - m.col3.z * m.col1.w;
    const float_t b23 = m.col2.z * m.col3.w - m.col3.z * m.col2.w;

    const float_t det = a01 * b23 - a02 * b13 + a03 * b12 + a12 * b03
        - a13 * b02 + a23 * b01;
    FND_ASSERT(det != 0.0f); // m is singular

    const float_t inv_det = 1.0f / det;

    // rowR holds the cofactors of row R of m.
    const float4_t row0{
        m.col1.y * b23 - m.col2.y * b13 + m.col3.y * b12,
        -m.col0.y * b23 + m.col2.y * b03 - m.col3.y * b02,
        m.col0.y * b13 - m.col1.y * b03 + m.col3.y * b01,
        -m.col0.y * b12 + m.col1.y * b02 - m.col2.y * b01};
    const float4_t row1{
        -m.col1.x * b23 + m.col2.x * b13 - m.col3.x * b12,
        m.col0.x * b23 - m.col2.x * b03 + m.col3.x * b02,
        -m.col0.x * b13 + m.col1.x * b03 - m.col3.x * b01,
        m.col0.x * b12 - m.col1.x * b02 + m.col2.x * b01};
    const float4_t row2{
        m.col1.w * a23 - m.col2.w * a13 + m.col3.w * a12,
        -m.col0.w * a23 + m.col2.w * a03 - m.col3.w * a02,
        m.col0.w * a13 - m.col1.w * a03 + m.col3.w * a01,
        -m.col0.w * a12 + m.col1.w * a02 - m.col2.w * a01};
    const float4_t row3{
        -m.col1.z * a23 + m.col2.z * a13 - m.col3.z * a12,
        m.col0.z * a23 - m.col2.z * a03 + m.col3.z * a02,
        -m.col0.z * a13 + m.col1.z * a03 - m.col3.z * a01,
        m.col0.z * a12 - m.col1.z * a02 + m.col2.z * a01};

    return float4x4_t{
        row0 * inv_det, row1 * inv_det, row2 * inv_det, row3 * inv_det};
}

// Rotation about the normalized axis, with no translation; see
// make_float3x3_axis_angle for the direction of a positive angle.
export FND_INLINE float4x4_t make_float4x4_axis_angle(
    const float3_t axis, const float_t angle_radians)
{
    FND_ASSERT(is_normalized(axis));

    const float3x3_t rm = make_float3x3_axis_angle(axis, angle_radians);
    return float4x4_t{
        float4(rm.col0, 0), float4(rm.col1, 0), float4(rm.col2, 0),
        float4_t::kUnitW};
}

// Scale by s.x, s.y and s.z along the x, y and z axes, with no translation.
export constexpr float4x4_t make_float4x4_scale(const float3_t s)
{
    return float4x4_t{
        float4_t{s.x, 0, 0, 0}, float4_t{0, s.y, 0, 0}, float4_t{0, 0, s.z, 0},
        float4_t::kUnitW};
}

// Translation by t, with the identity as the linear part.
export constexpr float4x4_t make_float4x4_translation(const float3_t t)
{
    return float4x4_t{
        float4_t::kUnitX, float4_t::kUnitY, float4_t::kUnitZ, float4(t, 1)};
}

// Translation t combined with the linear part mrs (rotation and scale): mrs
// is applied first, then t. The same as make_float4x4_translation(t) * mrs.
export constexpr float4x4_t make_float4x4_trs(
    const float3_t t, const float3x3_t& mrs)
{
    return float4x4_t{
        float4(mrs.col0, 0), float4(mrs.col1, 0), float4(mrs.col2, 0),
        float4(t, 1)};
}

// m times the column vector v.
export constexpr float4_t mul(const float4x4_t& m, const float4_t v)
{
    // Written out per component; see operator*(float4x4_t, float4x4_t).
    return float4_t{
        m.col0.x * v.x + m.col1.x * v.y + m.col2.x * v.z + m.col3.x * v.w,
        m.col0.y * v.x + m.col1.y * v.y + m.col2.y * v.z + m.col3.y * v.w,
        m.col0.z * v.x + m.col1.z * v.y + m.col2.z * v.z + m.col3.z * v.w,
        m.col0.w * v.x + m.col1.w * v.y + m.col2.w * v.z + m.col3.w * v.w};
}

export constexpr float4_t row0(const float4x4_t& m)
{
    return float4_t{m.col0.x, m.col1.x, m.col2.x, m.col3.x};
}

export constexpr float4_t row1(const float4x4_t& m)
{
    return float4_t{m.col0.y, m.col1.y, m.col2.y, m.col3.y};
}

export constexpr float4_t row2(const float4x4_t& m)
{
    return float4_t{m.col0.z, m.col1.z, m.col2.z, m.col3.z};
}

export constexpr float4_t row3(const float4x4_t& m)
{
    return float4_t{m.col0.w, m.col1.w, m.col2.w, m.col3.w};
}

export constexpr void set_column0(float4x4_t& m, const float4_t c)
{
    m.col0 = c;
}

export constexpr void set_column1(float4x4_t& m, const float4_t c)
{
    m.col1 = c;
}

export constexpr void set_column2(float4x4_t& m, const float4_t c)
{
    m.col2 = c;
}

export constexpr void set_column3(float4x4_t& m, const float4_t c)
{
    m.col3 = c;
}

export constexpr void set_row0(float4x4_t& m, const float4_t r)
{
    m.col0.x = r.x;
    m.col1.x = r.y;
    m.col2.x = r.z;
    m.col3.x = r.w;
}

export constexpr void set_row1(float4x4_t& m, const float4_t r)
{
    m.col0.y = r.x;
    m.col1.y = r.y;
    m.col2.y = r.z;
    m.col3.y = r.w;
}

export constexpr void set_row2(float4x4_t& m, const float4_t r)
{
    m.col0.z = r.x;
    m.col1.z = r.y;
    m.col2.z = r.z;
    m.col3.z = r.w;
}

export constexpr void set_row3(float4x4_t& m, const float4_t r)
{
    m.col0.w = r.x;
    m.col1.w = r.y;
    m.col2.w = r.z;
    m.col3.w = r.w;
}

export constexpr float4x4_t transpose(const float4x4_t& m)
{
    return float4x4_t{row0(m), row1(m), row2(m), row3(m)};
}

} // namespace fnd
