module;
#include "foundation/core/macros.h"

export module foundation.math:vector_float3;
import foundation.core;
import :scalar;
import :vector_bool;

namespace fnd {

export struct float3_t final {
    static const float3_t kZero;
    static const float3_t kUnitX;
    static const float3_t kUnitY;
    static const float3_t kUnitZ;

    float_t x{0.0f};
    float_t y{0.0f};
    float_t z{0.0f};

    constexpr float3_t() = default;

    constexpr explicit float3_t(const float_t scalar)
        : x{scalar}, y{scalar}, z{scalar}
    {
    }

    constexpr float3_t(const float_t x, const float_t y, const float_t z)
        : x{x}, y{y}, z{z}
    {
    }

    constexpr const float_t& operator[](const uint_t idx) const
    {
        FND_ASSERT(idx < 3);
        return idx == 0 ? x : (idx == 1 ? y : z);
    }

    constexpr float_t& operator[](const uint_t idx)
    {
        return const_cast<float_t&>(static_cast<const float3_t&>(*this)[idx]);
    }

    constexpr float3_t& operator++()
    {
        ++x;
        ++y;
        ++z;
        return *this;
    }

    constexpr float3_t operator++(int) { return float3_t{x++, y++, z++}; }

    constexpr float3_t& operator--()
    {
        --x;
        --y;
        --z;
        return *this;
    }

    constexpr float3_t operator--(int) { return float3_t{x--, y--, z--}; }

    constexpr float3_t operator-() const { return float3_t{-x, -y, -z}; }

    constexpr float3_t& operator+=(const float3_t b)
    {
        x += b.x;
        y += b.y;
        z += b.z;
        return *this;
    }

    constexpr float3_t& operator+=(const float_t scalar)
    {
        x += scalar;
        y += scalar;
        z += scalar;
        return *this;
    }

    constexpr float3_t& operator-=(const float3_t b)
    {
        x -= b.x;
        y -= b.y;
        z -= b.z;
        return *this;
    }

    constexpr float3_t& operator-=(const float_t scalar)
    {
        x -= scalar;
        y -= scalar;
        z -= scalar;
        return *this;
    }

    constexpr float3_t& operator*=(const float3_t b)
    {
        x *= b.x;
        y *= b.y;
        z *= b.z;
        return *this;
    }

    constexpr float3_t& operator*=(const float_t scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    constexpr float3_t& operator/=(const float3_t b)
    {
        FND_ASSERT(b.x != 0.0f && b.y != 0.0f && b.z != 0.0f);

        x /= b.x;
        y /= b.y;
        z /= b.z;
        return *this;
    }

    constexpr float3_t& operator/=(const float_t scalar)
    {
        FND_ASSERT(scalar != 0.0f);

        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    // The result has the sign of the left operand, as fmod does.
    FND_INLINE float3_t& operator%=(const float3_t b)
    {
        FND_ASSERT(b.x != 0.0f && b.y != 0.0f && b.z != 0.0f);

        x = fmod(x, b.x);
        y = fmod(y, b.y);
        z = fmod(z, b.z);
        return *this;
    }

    FND_INLINE float3_t& operator%=(const float_t scalar)
    {
        FND_ASSERT(scalar != 0.0f);

        x = fmod(x, scalar);
        y = fmod(y, scalar);
        z = fmod(z, scalar);
        return *this;
    }
};

constexpr float3_t float3_t::kZero{0.0f, 0.0f, 0.0f};
constexpr float3_t float3_t::kUnitX{1.0f, 0.0f, 0.0f};
constexpr float3_t float3_t::kUnitY{0.0f, 1.0f, 0.0f};
constexpr float3_t float3_t::kUnitZ{0.0f, 0.0f, 1.0f};

export constexpr bool3_t operator==(const float3_t a, const float3_t b)
{
    return bool3_t{a.x == b.x, a.y == b.y, a.z == b.z};
}

export constexpr bool3_t operator==(const float3_t a, const float_t scalar)
{
    return bool3_t{a.x == scalar, a.y == scalar, a.z == scalar};
}

export constexpr bool3_t operator==(const float_t scalar, const float3_t b)
{
    return bool3_t{scalar == b.x, scalar == b.y, scalar == b.z};
}

export constexpr bool3_t operator!=(const float3_t a, const float3_t b)
{
    return !(a == b);
}

export constexpr bool3_t operator!=(const float3_t a, const float_t scalar)
{
    return !(a == scalar);
}

export constexpr bool3_t operator!=(const float_t scalar, const float3_t b)
{
    return !(scalar == b);
}

export FND_INLINE bool3_t operator<(const float3_t a, const float3_t b)
{
    return bool3_t{a.x < b.x, a.y < b.y, a.z < b.z};
}

export FND_INLINE bool3_t operator<(const float3_t a, const float_t scalar)
{
    return bool3_t{a.x < scalar, a.y < scalar, a.z < scalar};
}

export FND_INLINE bool3_t operator<(const float_t scalar, const float3_t b)
{
    return bool3_t{scalar < b.x, scalar < b.y, scalar < b.z};
}

export FND_INLINE bool3_t operator<=(const float3_t a, const float3_t b)
{
    return bool3_t{a.x <= b.x, a.y <= b.y, a.z <= b.z};
}

export FND_INLINE bool3_t operator<=(const float3_t a, const float_t scalar)
{
    return bool3_t{a.x <= scalar, a.y <= scalar, a.z <= scalar};
}

export FND_INLINE bool3_t operator<=(const float_t scalar, const float3_t b)
{
    return bool3_t{scalar <= b.x, scalar <= b.y, scalar <= b.z};
}

export FND_INLINE bool3_t operator>(const float3_t a, const float3_t b)
{
    return bool3_t{a.x > b.x, a.y > b.y, a.z > b.z};
}

export FND_INLINE bool3_t operator>(const float3_t a, const float_t scalar)
{
    return bool3_t{a.x > scalar, a.y > scalar, a.z > scalar};
}

export FND_INLINE bool3_t operator>(const float_t scalar, const float3_t b)
{
    return bool3_t{scalar > b.x, scalar > b.y, scalar > b.z};
}

export FND_INLINE bool3_t operator>=(const float3_t a, const float3_t b)
{
    return bool3_t{a.x >= b.x, a.y >= b.y, a.z >= b.z};
}

export FND_INLINE bool3_t operator>=(const float3_t a, const float_t scalar)
{
    return bool3_t{a.x >= scalar, a.y >= scalar, a.z >= scalar};
}

export FND_INLINE bool3_t operator>=(const float_t scalar, const float3_t b)
{
    return bool3_t{scalar >= b.x, scalar >= b.y, scalar >= b.z};
}

export constexpr float3_t operator*(const float3_t a, const float3_t b)
{
    return float3_t{a.x * b.x, a.y * b.y, a.z * b.z};
}

export constexpr float3_t operator*(const float3_t a, const float_t scalar)
{
    return float3_t{a.x * scalar, a.y * scalar, a.z * scalar};
}

export constexpr float3_t operator*(const float_t scalar, const float3_t b)
{
    return float3_t{scalar * b.x, scalar * b.y, scalar * b.z};
}

export constexpr float3_t operator+(const float3_t a, const float3_t b)
{
    return float3_t{a.x + b.x, a.y + b.y, a.z + b.z};
}

export constexpr float3_t operator+(const float3_t a, const float_t scalar)
{
    return float3_t{a.x + scalar, a.y + scalar, a.z + scalar};
}

export constexpr float3_t operator+(const float_t scalar, const float3_t b)
{
    return float3_t{scalar + b.x, scalar + b.y, scalar + b.z};
}

export constexpr float3_t operator-(const float3_t a, const float3_t b)
{
    return float3_t{a.x - b.x, a.y - b.y, a.z - b.z};
}

export constexpr float3_t operator-(const float3_t a, const float_t scalar)
{
    return float3_t{a.x - scalar, a.y - scalar, a.z - scalar};
}

export constexpr float3_t operator-(const float_t scalar, const float3_t b)
{
    return float3_t{scalar - b.x, scalar - b.y, scalar - b.z};
}

// The result has the sign of the left operand, as fmod does.
export FND_INLINE float3_t operator%(const float3_t a, const float3_t b)
{
    FND_ASSERT(b.x != 0.0f && b.y != 0.0f && b.z != 0.0f);

    return float3_t{fmod(a.x, b.x), fmod(a.y, b.y), fmod(a.z, b.z)};
}

export FND_INLINE float3_t operator%(const float3_t a, const float_t scalar)
{
    FND_ASSERT(scalar != 0.0f);

    return float3_t{fmod(a.x, scalar), fmod(a.y, scalar), fmod(a.z, scalar)};
}

export FND_INLINE float3_t operator%(const float_t scalar, const float3_t b)
{
    FND_ASSERT(b.x != 0.0f && b.y != 0.0f && b.z != 0.0f);

    return float3_t{fmod(scalar, b.x), fmod(scalar, b.y), fmod(scalar, b.z)};
}

export constexpr float3_t operator/(const float3_t a, const float3_t b)
{
    FND_ASSERT(b.x != 0.0f && b.y != 0.0f && b.z != 0.0f);

    return float3_t{a.x / b.x, a.y / b.y, a.z / b.z};
}

export constexpr float3_t operator/(const float3_t a, const float_t scalar)
{
    FND_ASSERT(scalar != 0.0f);

    return float3_t{a.x / scalar, a.y / scalar, a.z / scalar};
}

export constexpr float3_t operator/(const float_t scalar, const float3_t b)
{
    FND_ASSERT(b.x != 0.0f && b.y != 0.0f && b.z != 0.0f);

    return float3_t{scalar / b.x, scalar / b.y, scalar / b.z};
}

export FND_INLINE float3_t abs(const float3_t v)
{
    return float3_t{abs(v.x), abs(v.y), abs(v.z)};
}

export FND_INLINE float3_t acos(const float3_t v)
{
    return float3_t{acos(v.x), acos(v.y), acos(v.z)};
}

export FND_INLINE bool3_t approx_equal(
    const float3_t a, const float3_t b, const float_t max_abs_diff = 1e-5f)
{
    FND_ASSERT(max_abs_diff >= 0);
    return bool3_t{
        approx_equal(a.x, b.x, max_abs_diff),
        approx_equal(a.y, b.y, max_abs_diff),
        approx_equal(a.z, b.z, max_abs_diff)};
}

export FND_INLINE bool3_t approx_equal(
    const float3_t a, const float_t scalar, const float_t max_abs_diff = 1e-5f)
{
    FND_ASSERT(max_abs_diff >= 0);
    return bool3_t{
        approx_equal(a.x, scalar, max_abs_diff),
        approx_equal(a.y, scalar, max_abs_diff),
        approx_equal(a.z, scalar, max_abs_diff)};
}

export FND_INLINE bool3_t approx_equal(
    const float_t scalar, const float3_t b, const float_t max_abs_diff = 1e-5f)
{
    FND_ASSERT(max_abs_diff >= 0);
    return bool3_t{
        approx_equal(scalar, b.x, max_abs_diff),
        approx_equal(scalar, b.y, max_abs_diff),
        approx_equal(scalar, b.z, max_abs_diff)};
}

export FND_INLINE float3_t asin(const float3_t v)
{
    return float3_t{asin(v.x), asin(v.y), asin(v.z)};
}

export FND_INLINE float3_t atan(const float3_t v)
{
    return float3_t{atan(v.x), atan(v.y), atan(v.z)};
}

export FND_INLINE float3_t atan2(const float3_t y, const float3_t x)
{
    return float3_t{atan2(y.x, x.x), atan2(y.y, x.y), atan2(y.z, x.z)};
}

export FND_INLINE float3_t ceil(const float3_t v)
{
    return float3_t{ceil(v.x), ceil(v.y), ceil(v.z)};
}

export FND_INLINE float3_t clamp(
    const float3_t v, const float3_t lower, const float3_t upper)
{
    FND_ASSERT(all(lower <= upper));

    return float3_t{
        clamp(v.x, lower.x, upper.x),
        clamp(v.y, lower.y, upper.y),
        clamp(v.z, lower.z, upper.z)};
}

export FND_INLINE float3_t clamp(
    const float3_t v, const float3_t lower, const float_t upper)
{
    FND_ASSERT(all(lower <= upper));

    return float3_t{
        clamp(v.x, lower.x, upper),
        clamp(v.y, lower.y, upper),
        clamp(v.z, lower.z, upper)};
}

export FND_INLINE float3_t clamp(
    const float3_t v, const float_t lower, const float3_t upper)
{
    FND_ASSERT(all(lower <= upper));

    return float3_t{
        clamp(v.x, lower, upper.x),
        clamp(v.y, lower, upper.y),
        clamp(v.z, lower, upper.z)};
}

export FND_INLINE float3_t clamp(
    const float3_t v, const float_t lower, const float_t upper)
{
    FND_ASSERT(lower <= upper);

    return float3_t{
        clamp(v.x, lower, upper),
        clamp(v.y, lower, upper),
        clamp(v.z, lower, upper)};
}

export FND_INLINE float_t cmax(const float3_t v)
{
    return max(max(v.x, v.y), v.z);
}

export FND_INLINE float_t cmin(const float3_t v)
{
    return min(min(v.x, v.y), v.z);
}

export constexpr float_t cmul(const float3_t v)
{
    return v.x * v.y * v.z;
}

export FND_INLINE float3_t cos(const float3_t v)
{
    return float3_t{cos(v.x), cos(v.y), cos(v.z)};
}

// Right-handed: cross({1, 0, 0}, {0, 1, 0}) == {0, 0, 1}.
export constexpr float3_t cross(const float3_t a, const float3_t b)
{
    return float3_t{
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x};
}

export constexpr float_t csum(const float3_t v)
{
    return v.x + v.y + v.z;
}

export constexpr float3_t degrees(const float3_t v)
{
    return float3_t{degrees(v.x), degrees(v.y), degrees(v.z)};
}

export constexpr float_t distance_sqr(const float3_t a, const float3_t b)
{
    const float3_t d = a - b;
    return d.x * d.x + d.y * d.y + d.z * d.z;
}

export FND_INLINE float_t distance(const float3_t a, const float3_t b)
{
    const float_t d2 = distance_sqr(a, b);
    return sqrt(d2);
}

export constexpr float_t dot(const float3_t a, const float3_t b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

export FND_INLINE float3_t exp(const float3_t v)
{
    return float3_t{exp(v.x), exp(v.y), exp(v.z)};
}

export FND_INLINE float3_t exp2(const float3_t v)
{
    return float3_t{exp2(v.x), exp2(v.y), exp2(v.z)};
}

export FND_INLINE float3_t floor(const float3_t v)
{
    return float3_t{floor(v.x), floor(v.y), floor(v.z)};
}

export FND_INLINE float3_t fmod(const float3_t a, const float3_t b)
{
    return float3_t{fmod(a.x, b.x), fmod(a.y, b.y), fmod(a.z, b.z)};
}

export FND_INLINE float3_t fmod(const float3_t a, const float_t scalar)
{
    return float3_t{fmod(a.x, scalar), fmod(a.y, scalar), fmod(a.z, scalar)};
}

export FND_INLINE float3_t fmod(const float_t scalar, const float3_t b)
{
    return float3_t{fmod(scalar, b.x), fmod(scalar, b.y), fmod(scalar, b.z)};
}

export FND_INLINE float3_t fractional(const float3_t v)
{
    return float3_t{fractional(v.x), fractional(v.y), fractional(v.z)};
}

export FND_INLINE bool3_t isfinite(const float3_t v)
{
    return bool3_t{isfinite(v.x), isfinite(v.y), isfinite(v.z)};
}

export FND_INLINE bool3_t isinf(const float3_t v)
{
    return bool3_t{isinf(v.x), isinf(v.y), isinf(v.z)};
}

export FND_INLINE bool3_t isnan(const float3_t v)
{
    return bool3_t{isnan(v.x), isnan(v.y), isnan(v.z)};
}

export constexpr float_t length_sqr(const float3_t v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

export FND_INLINE float_t length(const float3_t v)
{
    return sqrt(length_sqr(v));
}

export FND_INLINE float3_t lerp(
    const float3_t a, const float3_t b, const float_t t)
{
    return float3_t{lerp(a.x, b.x, t), lerp(a.y, b.y, t), lerp(a.z, b.z, t)};
}

export FND_INLINE float3_t lerp(
    const float3_t a, const float3_t b, const float3_t t)
{
    return float3_t{
        lerp(a.x, b.x, t.x), lerp(a.y, b.y, t.y), lerp(a.z, b.z, t.z)};
}

export FND_INLINE float3_t log(const float3_t v)
{
    return float3_t{log(v.x), log(v.y), log(v.z)};
}

export FND_INLINE float3_t log10(const float3_t v)
{
    return float3_t{log10(v.x), log10(v.y), log10(v.z)};
}

export FND_INLINE float3_t log2(const float3_t v)
{
    return float3_t{log2(v.x), log2(v.y), log2(v.z)};
}

export FND_INLINE float3_t max(const float3_t a, const float3_t b)
{
    return float3_t{max(a.x, b.x), max(a.y, b.y), max(a.z, b.z)};
}

export FND_INLINE float3_t max(const float3_t a, const float_t scalar)
{
    return float3_t{max(a.x, scalar), max(a.y, scalar), max(a.z, scalar)};
}

export FND_INLINE float3_t max(const float_t scalar, const float3_t b)
{
    return float3_t{max(scalar, b.x), max(scalar, b.y), max(scalar, b.z)};
}

export FND_INLINE float3_t min(const float3_t a, const float3_t b)
{
    return float3_t{min(a.x, b.x), min(a.y, b.y), min(a.z, b.z)};
}

export FND_INLINE float3_t min(const float3_t a, const float_t scalar)
{
    return float3_t{min(a.x, scalar), min(a.y, scalar), min(a.z, scalar)};
}

export FND_INLINE float3_t min(const float_t scalar, const float3_t b)
{
    return float3_t{min(scalar, b.x), min(scalar, b.y), min(scalar, b.z)};
}

// Splits each component into its fractional part (returned) and its integer
// part (stored in vi). Both parts have the sign of the component.
export FND_INLINE float3_t modf(const float3_t v, float3_t& vi)
{
    return float3_t{modf(v.x, vi.x), modf(v.y, vi.y), modf(v.z, vi.z)};
}

export FND_INLINE float3_t normalize(const float3_t v)
{
    const float_t l2 = length_sqr(v);
    FND_ASSERT(l2 > kFloatMinNormal);

    return v * rsqrt(l2);
}

export FND_INLINE float3_t normalize_safe(
    const float3_t v, const float3_t default_value = float3_t{})
{
    FND_ASSERT(all(!isnan(v)));

    float3_t res_vec = default_value;
    const float_t l2 = length_sqr(v);

    if (isinf(l2)) {
        // NOTE:
        // l2 is infinity (e.g. v = {1e20f, 1, 1}).
        // v should be rescaled so there is no overflow.
        // Rescaling is ok because normalize(v) == normalize(v * s), s > 0
        //
        // Scaling by cmax(abs(v)) needs no constant, but costs abs,
        // max and division instead of multiplication.
        //
        // 0x1p-66f is 2^-66. A power of two is exact: multiplying by it
        // lowers the exponent of each component by 66 and does not round.
        // Any 2^-k with 65 <= k <= 126 works:
        // - k >= 65: the scaled squares of three kFloatMaxValue components
        //      do not overflow;
        // - k <= 126: the scaled l2 stays a normal float.

        const float3_t scaled_vec = v * 0x1p-66f;
        res_vec = scaled_vec * rsqrt(length_sqr(scaled_vec));
    }
    else if (l2 > kFloatMinNormal) {
        res_vec = v * rsqrt(l2);
    }

    FND_ASSERT(all(!isnan(res_vec))); // post condition
    return res_vec;
}

export FND_INLINE float3_t pow(const float3_t base, const float3_t exponent)
{
    return float3_t{
        pow(base.x, exponent.x),
        pow(base.y, exponent.y),
        pow(base.z, exponent.z)};
}

export FND_INLINE float3_t pow(const float3_t base, const float_t exponent)
{
    return float3_t{
        pow(base.x, exponent), pow(base.y, exponent), pow(base.z, exponent)};
}

export constexpr float3_t radians(const float3_t v)
{
    return float3_t{radians(v.x), radians(v.y), radians(v.z)};
}

export FND_INLINE float3_t rcp(const float3_t v)
{
    return float3_t{rcp(v.x), rcp(v.y), rcp(v.z)};
}

export FND_INLINE float3_t rsqrt(const float3_t v)
{
    return float3_t{rsqrt(v.x), rsqrt(v.y), rsqrt(v.z)};
}

export FND_INLINE float3_t saturate(const float3_t v)
{
    return float3_t{saturate(v.x), saturate(v.y), saturate(v.z)};
}

export FND_INLINE float3_t sign(const float3_t v)
{
    return float3_t{sign(v.x), sign(v.y), sign(v.z)};
}

export FND_INLINE float3_t sin(const float3_t v)
{
    return float3_t{sin(v.x), sin(v.y), sin(v.z)};
}

export FND_INLINE float3_t smoothstep(
    const float3_t x, const float3_t edge0, const float3_t edge1)
{
    return float3_t{
        smoothstep(x.x, edge0.x, edge1.x),
        smoothstep(x.y, edge0.y, edge1.y),
        smoothstep(x.z, edge0.z, edge1.z)};
}

export FND_INLINE float3_t smoothstep(
    const float3_t x, const float_t edge0, const float_t edge1)
{
    return float3_t{
        smoothstep(x.x, edge0, edge1),
        smoothstep(x.y, edge0, edge1),
        smoothstep(x.z, edge0, edge1)};
}

export FND_INLINE float3_t sqrt(const float3_t v)
{
    return float3_t{sqrt(v.x), sqrt(v.y), sqrt(v.z)};
}

export FND_INLINE float3_t tan(const float3_t v)
{
    return float3_t{tan(v.x), tan(v.y), tan(v.z)};
}

export FND_INLINE float3_t trunc(const float3_t v)
{
    return float3_t{trunc(v.x), trunc(v.y), trunc(v.z)};
}

} // namespace fnd
