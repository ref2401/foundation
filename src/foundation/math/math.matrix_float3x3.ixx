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

    // All components are 0.
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

    constexpr float3x3_t operator-() const
    {
        return float3x3_t{-col0, -col1, -col2};
    }

    constexpr float3x3_t& operator*=(const float_t scalar)
    {
        col0 *= scalar;
        col1 *= scalar;
        col2 *= scalar;
        return *this;
    }

    // Matrix product: *this = *this * b.
    constexpr float3x3_t& operator*=(const float3x3_t& b)
    {
        // Column j of the product is *this times column j of b. All three are
        // computed before any is assigned, so m *= m works.
        const float3_t c0 = col0 * b.col0.x + col1 * b.col0.y + col2 * b.col0.z;
        const float3_t c1 = col0 * b.col1.x + col1 * b.col1.y + col2 * b.col1.z;
        const float3_t c2 = col0 * b.col2.x + col1 * b.col2.y + col2 * b.col2.z;
        col0 = c0;
        col1 = c1;
        col2 = c2;
        return *this;
    }

    constexpr float3x3_t& operator/=(const float_t scalar)
    {
        FND_ASSERT(scalar != 0.0f);

        col0 /= scalar;
        col1 /= scalar;
        col2 /= scalar;
        return *this;
    }
};

constexpr float3x3_t float3x3_t::kZero{
    float3_t{0, 0, 0},
    float3_t{0, 0, 0},
    float3_t{0, 0, 0}};
constexpr float3x3_t float3x3_t::kIdentity{
    float3_t{1, 0, 0},
    float3_t{0, 1, 0},
    float3_t{0, 0, 1}};

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

// Matrix product: column j of a * b is a times column j of b.
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

export FND_INLINE bool_t approx_equal(
    const float3x3_t& a, const float3x3_t& b,
    const float_t max_abs_diff = 1e-5f)
{
    return all(approx_equal(a.col0, b.col0, max_abs_diff))
        && all(approx_equal(a.col1, b.col1, max_abs_diff))
        && all(approx_equal(a.col2, b.col2, max_abs_diff));
}

export constexpr float3x3_t transpose(const float3x3_t& m)
{
    return float3x3_t{
        float3_t{m.col0.x, m.col1.x, m.col2.x},
        float3_t{m.col0.y, m.col1.y, m.col2.y},
        float3_t{m.col0.z, m.col1.z, m.col2.z}};
}

} // namespace fnd
