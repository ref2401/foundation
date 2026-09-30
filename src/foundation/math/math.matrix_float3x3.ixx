module;
#include "foundation/core/macros.h"

export module foundation.math:matrix_float3x3;
import foundation.core;
import :scalar;
import :vector_float3;
import :vector_float4;

namespace fnd {

export struct float3x3_t final {
    static const float3x3_t kZero;
    static const float3x3_t kIdentity;

    float3_t col0;
    float3_t col1;
    float3_t col2;

    constexpr float3x3_t() = default;

    constexpr float3x3_t(
        const float3_t c0, const float3_t c1, const float3_t c2)
        : col0{c0}, col1{c1}, col2{c2}
    {
    }

    // The components are given in column-major order, column by column, as
    // they are stored: mRC is the component in row R and column C.
    constexpr float3x3_t(
        const float_t m00, const float_t m10, const float_t m20,
        const float_t m01, const float_t m11, const float_t m21,
        const float_t m02, const float_t m12, const float_t m22)
        : col0{m00, m10, m20}, col1{m01, m11, m21}, col2{m02, m12, m22}
    {
    }
};

constexpr float3x3_t float3x3_t::kZero{
    float3_t{0, 0, 0}, float3_t{0, 0, 0}, float3_t{0, 0, 0}};
constexpr float3x3_t float3x3_t::kIdentity{
    float3_t{1, 0, 0}, float3_t{0, 1, 0}, float3_t{0, 0, 1}};

export constexpr float3x3_t operator-(const float3x3_t& v)
{
    return float3x3_t{-v.col0, -v.col1, -v.col2};
}

export constexpr bool_t operator==(const float3x3_t& a, const float3x3_t& b)
{
    return all(a.col0 == b.col0) && all(a.col1 == b.col1)
        && all(a.col2 == b.col2);
}

export constexpr bool_t operator!=(const float3x3_t& a, const float3x3_t& b)
{
    return !(a == b);
}

export constexpr float3x3_t operator*(const float3x3_t& m, const float_t scalar)
{
    return float3x3_t{m.col0 * scalar, m.col1 * scalar, m.col2 * scalar};
}

export constexpr float3x3_t operator*(const float_t scalar, const float3x3_t& m)
{
    return float3x3_t{scalar * m.col0, scalar * m.col1, scalar * m.col2};
}

// Matrix product
export constexpr float3x3_t operator*(const float3x3_t& a, const float3x3_t& b)
{
    return float3x3_t{
        a.col0 * b.col0.x + a.col1 * b.col0.y + a.col2 * b.col0.z,
        a.col0 * b.col1.x + a.col1 * b.col1.y + a.col2 * b.col1.z,
        a.col0 * b.col2.x + a.col1 * b.col2.y + a.col2 * b.col2.z};
}

export constexpr float3x3_t operator/(const float3x3_t& m, const float_t scalar)
{
    FND_ASSERT(scalar != 0.0f);

    return float3x3_t{m.col0 / scalar, m.col1 / scalar, m.col2 / scalar};
}

export constexpr float3x3_t& operator*=(float3x3_t& a, const float_t scalar)
{
    a = a * scalar;
    return a;
}

export constexpr float3x3_t& operator*=(float3x3_t& a, const float3x3_t& b)
{
    a = a * b;
    return a;
}

export constexpr float3x3_t& operator/=(float3x3_t& a, const float_t scalar)
{
    FND_ASSERT(scalar != 0.0f);

    a = a / scalar;
    return a;
}

export FND_INLINE bool_t approx_equal(
    const float3x3_t& a, const float3x3_t& b,
    const float_t max_abs_diff = 1e-5f)
{
    return all(approx_equal(a.col0, b.col0, max_abs_diff))
        && all(approx_equal(a.col1, b.col1, max_abs_diff))
        && all(approx_equal(a.col2, b.col2, max_abs_diff));
}

export FND_INLINE float_t cmax(const float3x3_t& m)
{
    return max(max(cmax(m.col0), cmax(m.col1)), cmax(m.col2));
}

export FND_INLINE float_t cmin(const float3x3_t& m)
{
    return min(min(cmin(m.col0), cmin(m.col1)), cmin(m.col2));
}

export constexpr float3_t column0(const float3x3_t& m)
{
    return m.col0;
}

export constexpr float3_t column1(const float3x3_t& m)
{
    return m.col1;
}

export constexpr float3_t column2(const float3x3_t& m)
{
    return m.col2;
}

export constexpr float_t determinant(const float3x3_t& m)
{
    return dot(m.col0, cross(m.col1, m.col2));
}

export constexpr float3x3_t inverse(const float3x3_t& m)
{
    const float3_t r0 = cross(m.col1, m.col2);
    const float3_t r1 = cross(m.col2, m.col0);
    const float3_t r2 = cross(m.col0, m.col1);
    const float_t det = dot(m.col0, r0);
    FND_ASSERT(det != 0.0f); // m is singular

    return float3x3_t{r0.x, r1.x, r2.x, r0.y, r1.y, r2.y, r0.z, r1.z, r2.z}
    / det;
}

export constexpr float3_t mul(const float3x3_t& m, const float3_t v)
{
    return m.col0 * v.x + m.col1 * v.y + m.col2 * v.z;
}

export constexpr float3_t row0(const float3x3_t& m)
{
    return float3_t{m.col0.x, m.col1.x, m.col2.x};
}

export constexpr float3_t row1(const float3x3_t& m)
{
    return float3_t{m.col0.y, m.col1.y, m.col2.y};
}

export constexpr float3_t row2(const float3x3_t& m)
{
    return float3_t{m.col0.z, m.col1.z, m.col2.z};
}

export constexpr void set_column0(float3x3_t& m, const float3_t c)
{
    m.col0 = c;
}

export constexpr void set_column1(float3x3_t& m, const float3_t c)
{
    m.col1 = c;
}

export constexpr void set_column2(float3x3_t& m, const float3_t c)
{
    m.col2 = c;
}

export constexpr void set_row0(float3x3_t& m, const float3_t r)
{
    m.col0.x = r.x;
    m.col1.x = r.y;
    m.col2.x = r.z;
}

export constexpr void set_row1(float3x3_t& m, const float3_t r)
{
    m.col0.y = r.x;
    m.col1.y = r.y;
    m.col2.y = r.z;
}

export constexpr void set_row2(float3x3_t& m, const float3_t r)
{
    m.col0.z = r.x;
    m.col1.z = r.y;
    m.col2.z = r.z;
}

export constexpr float3x3_t transpose(const float3x3_t& m)
{
    return float3x3_t{
        float3_t{m.col0.x, m.col1.x, m.col2.x},
        float3_t{m.col0.y, m.col1.y, m.col2.y},
        float3_t{m.col0.z, m.col1.z, m.col2.z}};
}

} // namespace fnd
