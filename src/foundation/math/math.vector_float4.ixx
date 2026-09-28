module;
#include "foundation/core/macros.h"

export module foundation.math:vector_float4;
import foundation.core;
import :scalar;
import :vector_bool;
import :vector_float2;
import :vector_float3;

namespace fnd {

// NOTE: w defaults to 1, so float4_t{} is {0, 0, 0, 1}.
export struct float4_t final {
    float_t x{0.0f};
    float_t y{0.0f};
    float_t z{0.0f};
    float_t w{1.0f};

    constexpr float4_t() = default;

    constexpr explicit float4_t(
        const bool2_t v2, const float_t z = 0.0f, const float_t w = 1.0f)
        : x{v2.x ? 1.0f : 0.0f}, y{v2.y ? 1.0f : 0.0f}, z{z}, w{w}
    {
    }

    constexpr explicit float4_t(const bool4_t v4)
        : x{v4.x ? 1.0f : 0.0f}, y{v4.y ? 1.0f : 0.0f}, z{v4.z ? 1.0f : 0.0f},
          w{v4.w ? 1.0f : 0.0f}
    {
    }

    constexpr explicit float4_t(const float_t scalar)
        : x{scalar}, y{scalar}, z{scalar}, w{scalar}
    {
    }

    constexpr explicit float4_t(
        const float2_t v2, const float_t z = 0.0f, const float_t w = 1.0f)
        : x{v2.x}, y{v2.y}, z{z}, w{w}
    {
    }

    constexpr explicit float4_t(const float3_t v3, const float_t w = 1.0f)
        : x{v3.x}, y{v3.y}, z{v3.z}, w{w}
    {
    }

    constexpr float4_t(
        const float_t x, const float_t y, const float_t z, const float_t w)
        : x{x}, y{y}, z{z}, w{w}
    {
    }

    constexpr const float_t& operator[](const uint_t idx) const
    {
        FND_ASSERT(idx < 4);
        return idx == 0 ? x : (idx == 1 ? y : (idx == 2 ? z : w));
    }

    constexpr float_t& operator[](const uint_t idx)
    {
        return const_cast<float_t&>(static_cast<const float4_t&>(*this)[idx]);
    }

    constexpr float4_t& operator++()
    {
        ++x;
        ++y;
        ++z;
        ++w;
        return *this;
    }

    constexpr float4_t operator++(int)
    {
        return float4_t{x++, y++, z++, w++};
    }

    constexpr float4_t& operator--()
    {
        --x;
        --y;
        --z;
        --w;
        return *this;
    }

    constexpr float4_t operator--(int)
    {
        return float4_t{x--, y--, z--, w--};
    }

    constexpr float4_t operator-() const { return float4_t{-x, -y, -z, -w}; }

    constexpr float4_t& operator+=(const float4_t b)
    {
        x += b.x;
        y += b.y;
        z += b.z;
        w += b.w;
        return *this;
    }

    constexpr float4_t& operator+=(const float_t scalar)
    {
        x += scalar;
        y += scalar;
        z += scalar;
        w += scalar;
        return *this;
    }

    constexpr float4_t& operator-=(const float4_t b)
    {
        x -= b.x;
        y -= b.y;
        z -= b.z;
        w -= b.w;
        return *this;
    }

    constexpr float4_t& operator-=(const float_t scalar)
    {
        x -= scalar;
        y -= scalar;
        z -= scalar;
        w -= scalar;
        return *this;
    }

    constexpr float4_t& operator*=(const float4_t b)
    {
        x *= b.x;
        y *= b.y;
        z *= b.z;
        w *= b.w;
        return *this;
    }

    constexpr float4_t& operator*=(const float_t scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
        return *this;
    }

    constexpr float4_t& operator/=(const float4_t b)
    {
        FND_ASSERT(b.x != 0.0f && b.y != 0.0f && b.z != 0.0f && b.w != 0.0f);

        x /= b.x;
        y /= b.y;
        z /= b.z;
        w /= b.w;
        return *this;
    }

    constexpr float4_t& operator/=(const float_t scalar)
    {
        FND_ASSERT(scalar != 0.0f);

        x /= scalar;
        y /= scalar;
        z /= scalar;
        w /= scalar;
        return *this;
    }

    // The result has the sign of the left operand, as fmod does.
    FND_INLINE float4_t& operator%=(const float4_t b)
    {
        FND_ASSERT(b.x != 0.0f && b.y != 0.0f && b.z != 0.0f && b.w != 0.0f);

        x = fmod(x, b.x);
        y = fmod(y, b.y);
        z = fmod(z, b.z);
        w = fmod(w, b.w);
        return *this;
    }

    FND_INLINE float4_t& operator%=(const float_t scalar)
    {
        FND_ASSERT(scalar != 0.0f);

        x = fmod(x, scalar);
        y = fmod(y, scalar);
        z = fmod(z, scalar);
        w = fmod(w, scalar);
        return *this;
    }
};

export constexpr bool4_t operator==(const float4_t a, const float4_t b)
{
    return bool4_t{a.x == b.x, a.y == b.y, a.z == b.z, a.w == b.w};
}

export constexpr bool4_t operator==(const float4_t a, const float_t scalar)
{
    return bool4_t{a.x == scalar, a.y == scalar, a.z == scalar, a.w == scalar};
}

export constexpr bool4_t operator==(const float_t scalar, const float4_t b)
{
    return bool4_t{scalar == b.x, scalar == b.y, scalar == b.z, scalar == b.w};
}

export constexpr bool4_t operator!=(const float4_t a, const float4_t b)
{
    return !(a == b);
}

export constexpr bool4_t operator!=(const float4_t a, const float_t scalar)
{
    return !(a == scalar);
}

export constexpr bool4_t operator!=(const float_t scalar, const float4_t b)
{
    return !(scalar == b);
}

export FND_INLINE bool4_t operator<(const float4_t a, const float4_t b)
{
    return bool4_t{a.x < b.x, a.y < b.y, a.z < b.z, a.w < b.w};
}

export FND_INLINE bool4_t operator<(const float4_t a, const float_t scalar)
{
    return bool4_t{a.x < scalar, a.y < scalar, a.z < scalar, a.w < scalar};
}

export FND_INLINE bool4_t operator<(const float_t scalar, const float4_t b)
{
    return bool4_t{scalar < b.x, scalar < b.y, scalar < b.z, scalar < b.w};
}

export FND_INLINE bool4_t operator<=(const float4_t a, const float4_t b)
{
    return bool4_t{a.x <= b.x, a.y <= b.y, a.z <= b.z, a.w <= b.w};
}

export FND_INLINE bool4_t operator<=(const float4_t a, const float_t scalar)
{
    return bool4_t{a.x <= scalar, a.y <= scalar, a.z <= scalar, a.w <= scalar};
}

export FND_INLINE bool4_t operator<=(const float_t scalar, const float4_t b)
{
    return bool4_t{scalar <= b.x, scalar <= b.y, scalar <= b.z, scalar <= b.w};
}

export FND_INLINE bool4_t operator>(const float4_t a, const float4_t b)
{
    return bool4_t{a.x > b.x, a.y > b.y, a.z > b.z, a.w > b.w};
}

export FND_INLINE bool4_t operator>(const float4_t a, const float_t scalar)
{
    return bool4_t{a.x > scalar, a.y > scalar, a.z > scalar, a.w > scalar};
}

export FND_INLINE bool4_t operator>(const float_t scalar, const float4_t b)
{
    return bool4_t{scalar > b.x, scalar > b.y, scalar > b.z, scalar > b.w};
}

export FND_INLINE bool4_t operator>=(const float4_t a, const float4_t b)
{
    return bool4_t{a.x >= b.x, a.y >= b.y, a.z >= b.z, a.w >= b.w};
}

export FND_INLINE bool4_t operator>=(const float4_t a, const float_t scalar)
{
    return bool4_t{a.x >= scalar, a.y >= scalar, a.z >= scalar, a.w >= scalar};
}

export FND_INLINE bool4_t operator>=(const float_t scalar, const float4_t b)
{
    return bool4_t{scalar >= b.x, scalar >= b.y, scalar >= b.z, scalar >= b.w};
}

export constexpr float4_t operator*(const float4_t a, const float4_t b)
{
    return float4_t{a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w};
}

export constexpr float4_t operator*(const float4_t a, const float_t scalar)
{
    return float4_t{a.x * scalar, a.y * scalar, a.z * scalar, a.w * scalar};
}

export constexpr float4_t operator*(const float_t scalar, const float4_t b)
{
    return float4_t{scalar * b.x, scalar * b.y, scalar * b.z, scalar * b.w};
}

export constexpr float4_t operator+(const float4_t a, const float4_t b)
{
    return float4_t{a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

export constexpr float4_t operator+(const float4_t a, const float_t scalar)
{
    return float4_t{a.x + scalar, a.y + scalar, a.z + scalar, a.w + scalar};
}

export constexpr float4_t operator+(const float_t scalar, const float4_t b)
{
    return float4_t{scalar + b.x, scalar + b.y, scalar + b.z, scalar + b.w};
}

export constexpr float4_t operator-(const float4_t a, const float4_t b)
{
    return float4_t{a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}

export constexpr float4_t operator-(const float4_t a, const float_t scalar)
{
    return float4_t{a.x - scalar, a.y - scalar, a.z - scalar, a.w - scalar};
}

export constexpr float4_t operator-(const float_t scalar, const float4_t b)
{
    return float4_t{scalar - b.x, scalar - b.y, scalar - b.z, scalar - b.w};
}

// The result has the sign of the left operand, as fmod does.
export FND_INLINE float4_t operator%(const float4_t a, const float4_t b)
{
    FND_ASSERT(b.x != 0.0f && b.y != 0.0f && b.z != 0.0f && b.w != 0.0f);

    return float4_t{
        fmod(a.x, b.x), fmod(a.y, b.y), fmod(a.z, b.z), fmod(a.w, b.w)};
}

export FND_INLINE float4_t operator%(const float4_t a, const float_t scalar)
{
    FND_ASSERT(scalar != 0.0f);

    return float4_t{
        fmod(a.x, scalar),
        fmod(a.y, scalar),
        fmod(a.z, scalar),
        fmod(a.w, scalar)};
}

export FND_INLINE float4_t operator%(const float_t scalar, const float4_t b)
{
    FND_ASSERT(b.x != 0.0f && b.y != 0.0f && b.z != 0.0f && b.w != 0.0f);

    return float4_t{
        fmod(scalar, b.x),
        fmod(scalar, b.y),
        fmod(scalar, b.z),
        fmod(scalar, b.w)};
}

export constexpr float4_t operator/(const float4_t a, const float4_t b)
{
    FND_ASSERT(b.x != 0.0f && b.y != 0.0f && b.z != 0.0f && b.w != 0.0f);

    return float4_t{a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w};
}

export constexpr float4_t operator/(const float4_t a, const float_t scalar)
{
    FND_ASSERT(scalar != 0.0f);

    return float4_t{a.x / scalar, a.y / scalar, a.z / scalar, a.w / scalar};
}

export constexpr float4_t operator/(const float_t scalar, const float4_t b)
{
    FND_ASSERT(b.x != 0.0f && b.y != 0.0f && b.z != 0.0f && b.w != 0.0f);

    return float4_t{scalar / b.x, scalar / b.y, scalar / b.z, scalar / b.w};
}

export FND_INLINE float4_t abs(const float4_t v)
{
    return float4_t{abs(v.x), abs(v.y), abs(v.z), abs(v.w)};
}

export FND_INLINE float4_t acos(const float4_t v)
{
    return float4_t{acos(v.x), acos(v.y), acos(v.z), acos(v.w)};
}

export FND_INLINE bool4_t approx_equal(
    const float4_t a, const float4_t b, const float_t max_abs_diff = 1e-5f)
{
    FND_ASSERT(max_abs_diff >= 0);
    return bool4_t{
        approx_equal(a.x, b.x, max_abs_diff),
        approx_equal(a.y, b.y, max_abs_diff),
        approx_equal(a.z, b.z, max_abs_diff),
        approx_equal(a.w, b.w, max_abs_diff)};
}

export FND_INLINE bool4_t approx_equal(
    const float4_t a, const float_t scalar, const float_t max_abs_diff = 1e-5f)
{
    FND_ASSERT(max_abs_diff >= 0);
    return bool4_t{
        approx_equal(a.x, scalar, max_abs_diff),
        approx_equal(a.y, scalar, max_abs_diff),
        approx_equal(a.z, scalar, max_abs_diff),
        approx_equal(a.w, scalar, max_abs_diff)};
}

export FND_INLINE bool4_t approx_equal(
    const float_t scalar, const float4_t b, const float_t max_abs_diff = 1e-5f)
{
    FND_ASSERT(max_abs_diff >= 0);
    return bool4_t{
        approx_equal(scalar, b.x, max_abs_diff),
        approx_equal(scalar, b.y, max_abs_diff),
        approx_equal(scalar, b.z, max_abs_diff),
        approx_equal(scalar, b.w, max_abs_diff)};
}

export FND_INLINE float4_t asin(const float4_t v)
{
    return float4_t{asin(v.x), asin(v.y), asin(v.z), asin(v.w)};
}

export FND_INLINE float4_t atan(const float4_t v)
{
    return float4_t{atan(v.x), atan(v.y), atan(v.z), atan(v.w)};
}

export FND_INLINE float4_t atan2(const float4_t y, const float4_t x)
{
    return float4_t{
        atan2(y.x, x.x), atan2(y.y, x.y), atan2(y.z, x.z), atan2(y.w, x.w)};
}

export FND_INLINE float4_t ceil(const float4_t v)
{
    return float4_t{ceil(v.x), ceil(v.y), ceil(v.z), ceil(v.w)};
}

export FND_INLINE float4_t clamp(
    const float4_t v, const float4_t lower, const float4_t upper)
{
    FND_ASSERT(all(lower <= upper));

    return float4_t{
        clamp(v.x, lower.x, upper.x),
        clamp(v.y, lower.y, upper.y),
        clamp(v.z, lower.z, upper.z),
        clamp(v.w, lower.w, upper.w)};
}

export FND_INLINE float4_t clamp(
    const float4_t v, const float4_t lower, const float_t upper)
{
    FND_ASSERT(all(lower <= upper));

    return float4_t{
        clamp(v.x, lower.x, upper),
        clamp(v.y, lower.y, upper),
        clamp(v.z, lower.z, upper),
        clamp(v.w, lower.w, upper)};
}

export FND_INLINE float4_t clamp(
    const float4_t v, const float_t lower, const float4_t upper)
{
    FND_ASSERT(all(lower <= upper));

    return float4_t{
        clamp(v.x, lower, upper.x),
        clamp(v.y, lower, upper.y),
        clamp(v.z, lower, upper.z),
        clamp(v.w, lower, upper.w)};
}

export FND_INLINE float4_t clamp(
    const float4_t v, const float_t lower, const float_t upper)
{
    FND_ASSERT(lower <= upper);

    return float4_t{
        clamp(v.x, lower, upper),
        clamp(v.y, lower, upper),
        clamp(v.z, lower, upper),
        clamp(v.w, lower, upper)};
}

export FND_INLINE float_t cmax(const float4_t v)
{
    return max(max(max(v.x, v.y), v.z), v.w);
}

export FND_INLINE float_t cmin(const float4_t v)
{
    return min(min(min(v.x, v.y), v.z), v.w);
}

export constexpr float_t cmul(const float4_t v)
{
    return v.x * v.y * v.z * v.w;
}

export FND_INLINE float4_t cos(const float4_t v)
{
    return float4_t{cos(v.x), cos(v.y), cos(v.z), cos(v.w)};
}

export constexpr float_t csum(const float4_t v)
{
    return v.x + v.y + v.z + v.w;
}

export constexpr float4_t degrees(const float4_t v)
{
    return float4_t{degrees(v.x), degrees(v.y), degrees(v.z), degrees(v.w)};
}

export constexpr float_t distance_sqr(const float4_t a, const float4_t b)
{
    const float4_t d = a - b;
    return d.x * d.x + d.y * d.y + d.z * d.z + d.w * d.w;
}

export FND_INLINE float_t distance(const float4_t a, const float4_t b)
{
    const float_t d2 = distance_sqr(a, b);
    return sqrt(d2);
}

export constexpr float_t dot(const float4_t a, const float4_t b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

export FND_INLINE float4_t exp(const float4_t v)
{
    return float4_t{exp(v.x), exp(v.y), exp(v.z), exp(v.w)};
}

export FND_INLINE float4_t exp2(const float4_t v)
{
    return float4_t{exp2(v.x), exp2(v.y), exp2(v.z), exp2(v.w)};
}

export FND_INLINE float4_t floor(const float4_t v)
{
    return float4_t{floor(v.x), floor(v.y), floor(v.z), floor(v.w)};
}

export FND_INLINE float4_t fmod(const float4_t a, const float4_t b)
{
    return float4_t{
        fmod(a.x, b.x), fmod(a.y, b.y), fmod(a.z, b.z), fmod(a.w, b.w)};
}

export FND_INLINE float4_t fmod(const float4_t a, const float_t scalar)
{
    return float4_t{
        fmod(a.x, scalar),
        fmod(a.y, scalar),
        fmod(a.z, scalar),
        fmod(a.w, scalar)};
}

export FND_INLINE float4_t fmod(const float_t scalar, const float4_t b)
{
    return float4_t{
        fmod(scalar, b.x),
        fmod(scalar, b.y),
        fmod(scalar, b.z),
        fmod(scalar, b.w)};
}

export FND_INLINE float4_t fractional(const float4_t v)
{
    return float4_t{
        fractional(v.x), fractional(v.y), fractional(v.z), fractional(v.w)};
}

export FND_INLINE bool4_t isfinite(const float4_t v)
{
    return bool4_t{isfinite(v.x), isfinite(v.y), isfinite(v.z), isfinite(v.w)};
}

export FND_INLINE bool4_t isinf(const float4_t v)
{
    return bool4_t{isinf(v.x), isinf(v.y), isinf(v.z), isinf(v.w)};
}

export FND_INLINE bool4_t isnan(const float4_t v)
{
    return bool4_t{isnan(v.x), isnan(v.y), isnan(v.z), isnan(v.w)};
}

export constexpr float_t length_sqr(const float4_t v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
}

export FND_INLINE float_t length(const float4_t v)
{
    return sqrt(length_sqr(v));
}

export FND_INLINE float4_t lerp(
    const float4_t a, const float4_t b, const float_t t)
{
    return float4_t{
        lerp(a.x, b.x, t), lerp(a.y, b.y, t), lerp(a.z, b.z, t),
        lerp(a.w, b.w, t)};
}

export FND_INLINE float4_t lerp(
    const float4_t a, const float4_t b, const float4_t t)
{
    return float4_t{
        lerp(a.x, b.x, t.x),
        lerp(a.y, b.y, t.y),
        lerp(a.z, b.z, t.z),
        lerp(a.w, b.w, t.w)};
}

export FND_INLINE float4_t log(const float4_t v)
{
    return float4_t{log(v.x), log(v.y), log(v.z), log(v.w)};
}

export FND_INLINE float4_t log10(const float4_t v)
{
    return float4_t{log10(v.x), log10(v.y), log10(v.z), log10(v.w)};
}

export FND_INLINE float4_t log2(const float4_t v)
{
    return float4_t{log2(v.x), log2(v.y), log2(v.z), log2(v.w)};
}

export FND_INLINE float4_t max(const float4_t a, const float4_t b)
{
    return float4_t{max(a.x, b.x), max(a.y, b.y), max(a.z, b.z), max(a.w, b.w)};
}

export FND_INLINE float4_t max(const float4_t a, const float_t scalar)
{
    return float4_t{
        max(a.x, scalar), max(a.y, scalar), max(a.z, scalar), max(a.w, scalar)};
}

export FND_INLINE float4_t max(const float_t scalar, const float4_t b)
{
    return float4_t{
        max(scalar, b.x), max(scalar, b.y), max(scalar, b.z), max(scalar, b.w)};
}

export FND_INLINE float4_t min(const float4_t a, const float4_t b)
{
    return float4_t{min(a.x, b.x), min(a.y, b.y), min(a.z, b.z), min(a.w, b.w)};
}

export FND_INLINE float4_t min(const float4_t a, const float_t scalar)
{
    return float4_t{
        min(a.x, scalar), min(a.y, scalar), min(a.z, scalar), min(a.w, scalar)};
}

export FND_INLINE float4_t min(const float_t scalar, const float4_t b)
{
    return float4_t{
        min(scalar, b.x), min(scalar, b.y), min(scalar, b.z), min(scalar, b.w)};
}

// Splits each component into its fractional part (returned) and its integer
// part (stored in vi). Both parts have the sign of the component.
export FND_INLINE float4_t modf(const float4_t v, float4_t& vi)
{
    return float4_t{
        modf(v.x, vi.x), modf(v.y, vi.y), modf(v.z, vi.z), modf(v.w, vi.w)};
}

export FND_INLINE float4_t normalize(const float4_t v)
{
    const float_t l2 = length_sqr(v);
    FND_ASSERT(l2 > kFloatMinNormal);

    return v * rsqrt(l2);
}

// NOTE: default_value is a zero vector, not float4_t{} (which has w = 1).
export FND_INLINE float4_t normalize_safe(
    const float4_t v, const float4_t default_value = float4_t{0.0f})
{
    FND_ASSERT(all(!isnan(v)));

    float4_t res_vec = default_value;
    const float_t l2 = length_sqr(v);

    if (isinf(l2)) {
        // NOTE:
        // l2 is infinity (e.g. v = {1e20f, 1, 1, 1}).
        // v should be rescaled so there is no overflow.
        // Rescaling is ok because normalize(v) == normalize(v * s), s > 0
        //
        // Scaling by cmax(abs(v)) needs no constant, but costs abs,
        // max and division instead of multiplication.
        //
        // 0x1p-66f is 2^-66. A power of two is exact: multiplying by it
        // lowers the exponent of each component by 66 and does not round.
        // Any 2^-k with 65 <= k <= 126 works:
        // - k >= 65: the scaled squares of four kFloatMaxValue components
        //      do not overflow;
        // - k <= 126: the scaled l2 stays a normal float.

        const float4_t scaled_vec = v * 0x1p-66f;
        res_vec = scaled_vec * rsqrt(length_sqr(scaled_vec));
    }
    else if (l2 > kFloatMinNormal) {
        res_vec = v * rsqrt(l2);
    }

    FND_ASSERT(all(!isnan(res_vec))); // post condition
    return res_vec;
}

export FND_INLINE float4_t pow(const float4_t base, const float4_t exponent)
{
    return float4_t{
        pow(base.x, exponent.x),
        pow(base.y, exponent.y),
        pow(base.z, exponent.z),
        pow(base.w, exponent.w)};
}

export FND_INLINE float4_t pow(const float4_t base, const float_t exponent)
{
    return float4_t{
        pow(base.x, exponent),
        pow(base.y, exponent),
        pow(base.z, exponent),
        pow(base.w, exponent)};
}

export constexpr float4_t radians(const float4_t v)
{
    return float4_t{radians(v.x), radians(v.y), radians(v.z), radians(v.w)};
}

export FND_INLINE float4_t rcp(const float4_t v)
{
    return float4_t{rcp(v.x), rcp(v.y), rcp(v.z), rcp(v.w)};
}

export FND_INLINE float4_t rsqrt(const float4_t v)
{
    return float4_t{rsqrt(v.x), rsqrt(v.y), rsqrt(v.z), rsqrt(v.w)};
}

export FND_INLINE float4_t saturate(const float4_t v)
{
    return float4_t{saturate(v.x), saturate(v.y), saturate(v.z), saturate(v.w)};
}

export FND_INLINE float4_t sign(const float4_t v)
{
    return float4_t{sign(v.x), sign(v.y), sign(v.z), sign(v.w)};
}

export FND_INLINE float4_t sin(const float4_t v)
{
    return float4_t{sin(v.x), sin(v.y), sin(v.z), sin(v.w)};
}

export FND_INLINE float4_t smoothstep(
    const float4_t x, const float4_t edge0, const float4_t edge1)
{
    return float4_t{
        smoothstep(x.x, edge0.x, edge1.x),
        smoothstep(x.y, edge0.y, edge1.y),
        smoothstep(x.z, edge0.z, edge1.z),
        smoothstep(x.w, edge0.w, edge1.w)};
}

export FND_INLINE float4_t smoothstep(
    const float4_t x, const float_t edge0, const float_t edge1)
{
    return float4_t{
        smoothstep(x.x, edge0, edge1),
        smoothstep(x.y, edge0, edge1),
        smoothstep(x.z, edge0, edge1),
        smoothstep(x.w, edge0, edge1)};
}

export FND_INLINE float4_t sqrt(const float4_t v)
{
    return float4_t{sqrt(v.x), sqrt(v.y), sqrt(v.z), sqrt(v.w)};
}

export FND_INLINE float4_t tan(const float4_t v)
{
    return float4_t{tan(v.x), tan(v.y), tan(v.z), tan(v.w)};
}

export FND_INLINE float4_t trunc(const float4_t v)
{
    return float4_t{trunc(v.x), trunc(v.y), trunc(v.z), trunc(v.w)};
}

} // namespace fnd
