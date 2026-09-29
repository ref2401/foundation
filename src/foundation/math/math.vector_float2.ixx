module;
#include "foundation/core/macros.h"

export module foundation.math:vector_float2;
import foundation.core;
import :scalar;
import :vector_bool;

namespace fnd {

export struct float2_t final {
    static const float2_t kZero;
    static const float2_t kUnitX;
    static const float2_t kUnitY;

    float_t x{0};
    float_t y{0};

    constexpr float2_t() = default;

    constexpr explicit float2_t(const float_t scalar) : x{scalar}, y{scalar} {}

    constexpr float2_t(const float_t x, const float_t y) : x{x}, y{y} {}

    constexpr const float_t& operator[](const uint_t idx) const
    {
        FND_ASSERT(idx < 2);
        return idx == 0 ? x : y;
    }

    constexpr float_t& operator[](const uint_t idx)
    {
        return const_cast<float_t&>(static_cast<const float2_t&>(*this)[idx]);
    }
};

constexpr float2_t float2_t::kZero{0, 0};
constexpr float2_t float2_t::kUnitX{1, 0};
constexpr float2_t float2_t::kUnitY{0, 1};

export constexpr float2_t& operator++(float2_t& v)
{
    ++v.x;
    ++v.y;
    return v;
}

export constexpr float2_t operator++(float2_t& v, int)
{
    return float2_t{v.x++, v.y++};
}

export constexpr float2_t& operator--(float2_t& v)
{
    --v.x;
    --v.y;
    return v;
}

export constexpr float2_t operator--(float2_t& v, int)
{
    return float2_t{v.x--, v.y--};
}

export constexpr float2_t operator-(const float2_t v)
{
    return float2_t{-v.x, -v.y};
}

export constexpr bool2_t operator==(const float2_t a, const float2_t b)
{
    return bool2_t{a.x == b.x, a.y == b.y};
}

export constexpr bool2_t operator==(const float2_t a, const float_t scalar)
{
    return bool2_t{a.x == scalar, a.y == scalar};
}

export constexpr bool2_t operator==(const float_t scalar, const float2_t b)
{
    return bool2_t{scalar == b.x, scalar == b.y};
}

export constexpr bool2_t operator!=(const float2_t a, const float2_t b)
{
    return !(a == b);
}

export constexpr bool2_t operator!=(const float2_t a, const float_t scalar)
{
    return !(a == scalar);
}

export constexpr bool2_t operator!=(const float_t scalar, const float2_t b)
{
    return !(scalar == b);
}

export FND_INLINE bool2_t operator<(const float2_t a, const float2_t b)
{
    return bool2_t{a.x < b.x, a.y < b.y};
}

export FND_INLINE bool2_t operator<(const float2_t a, const float_t scalar)
{
    return bool2_t{a.x < scalar, a.y < scalar};
}

export FND_INLINE bool2_t operator<(const float_t scalar, const float2_t b)
{
    return bool2_t{scalar < b.x, scalar < b.y};
}

export FND_INLINE bool2_t operator<=(const float2_t a, const float2_t b)
{
    return bool2_t{a.x <= b.x, a.y <= b.y};
}

export FND_INLINE bool2_t operator<=(const float2_t a, const float_t scalar)
{
    return bool2_t{a.x <= scalar, a.y <= scalar};
}

export FND_INLINE bool2_t operator<=(const float_t scalar, const float2_t b)
{
    return bool2_t{scalar <= b.x, scalar <= b.y};
}

export FND_INLINE bool2_t operator>(const float2_t a, const float2_t b)
{
    return bool2_t{a.x > b.x, a.y > b.y};
}

export FND_INLINE bool2_t operator>(const float2_t a, const float_t scalar)
{
    return bool2_t{a.x > scalar, a.y > scalar};
}

export FND_INLINE bool2_t operator>(const float_t scalar, const float2_t b)
{
    return bool2_t{scalar > b.x, scalar > b.y};
}

export FND_INLINE bool2_t operator>=(const float2_t a, const float2_t b)
{
    return bool2_t{a.x >= b.x, a.y >= b.y};
}

export FND_INLINE bool2_t operator>=(const float2_t a, const float_t scalar)
{
    return bool2_t{a.x >= scalar, a.y >= scalar};
}

export FND_INLINE bool2_t operator>=(const float_t scalar, const float2_t b)
{
    return bool2_t{scalar >= b.x, scalar >= b.y};
}

export constexpr float2_t operator*(const float2_t a, const float2_t b)
{
    return float2_t{a.x * b.x, a.y * b.y};
}

export constexpr float2_t operator*(const float2_t a, const float_t scalar)
{
    return float2_t{a.x * scalar, a.y * scalar};
}

export constexpr float2_t operator*(const float_t scalar, const float2_t b)
{
    return float2_t{scalar * b.x, scalar * b.y};
}

export constexpr float2_t operator+(const float2_t a, const float2_t b)
{
    return float2_t{a.x + b.x, a.y + b.y};
}

export constexpr float2_t operator+(const float2_t a, const float_t scalar)
{
    return float2_t{a.x + scalar, a.y + scalar};
}

export constexpr float2_t operator+(const float_t scalar, const float2_t b)
{
    return float2_t{scalar + b.x, scalar + b.y};
}

export constexpr float2_t operator-(const float2_t a, const float2_t b)
{
    return float2_t{a.x - b.x, a.y - b.y};
}

export constexpr float2_t operator-(const float2_t a, const float_t scalar)
{
    return float2_t{a.x - scalar, a.y - scalar};
}

export constexpr float2_t operator-(const float_t scalar, const float2_t b)
{
    return float2_t{scalar - b.x, scalar - b.y};
}

// The result has the sign of the left operand, as fmod does.
export FND_INLINE float2_t operator%(const float2_t a, const float2_t b)
{
    FND_ASSERT(b.x != 0.0f && b.y != 0.0f);

    return float2_t{fmod(a.x, b.x), fmod(a.y, b.y)};
}

export FND_INLINE float2_t operator%(const float2_t a, const float_t scalar)
{
    FND_ASSERT(scalar != 0.0f);

    return float2_t{fmod(a.x, scalar), fmod(a.y, scalar)};
}

export FND_INLINE float2_t operator%(const float_t scalar, const float2_t b)
{
    FND_ASSERT(b.x != 0.0f && b.y != 0.0f);

    return float2_t{fmod(scalar, b.x), fmod(scalar, b.y)};
}

export constexpr float2_t operator/(const float2_t a, const float2_t b)
{
    FND_ASSERT(b.x != 0.0f && b.y != 0.0f);

    return float2_t{a.x / b.x, a.y / b.y};
}

export constexpr float2_t operator/(const float2_t a, const float_t scalar)
{
    FND_ASSERT(scalar != 0.0f);

    return float2_t{a.x / scalar, a.y / scalar};
}

export constexpr float2_t operator/(const float_t scalar, const float2_t b)
{
    FND_ASSERT(b.x != 0.0f && b.y != 0.0f);

    return float2_t{scalar / b.x, scalar / b.y};
}

export constexpr float2_t& operator*=(float2_t& a, const float2_t b)
{
    a = a * b;
    return a;
}

export constexpr float2_t& operator*=(float2_t& a, const float_t scalar)
{
    a = a * scalar;
    return a;
}

export constexpr float2_t& operator+=(float2_t& a, const float2_t b)
{
    a = a + b;
    return a;
}

export constexpr float2_t& operator+=(float2_t& a, const float_t scalar)
{
    a = a + scalar;
    return a;
}

export constexpr float2_t& operator-=(float2_t& a, const float2_t b)
{
    a = a - b;
    return a;
}

export constexpr float2_t& operator-=(float2_t& a, const float_t scalar)
{
    a = a - scalar;
    return a;
}

export FND_INLINE float2_t& operator%=(float2_t& a, const float2_t b)
{
    FND_ASSERT(b.x != 0.0f && b.y != 0.0f);

    a = a % b;
    return a;
}

export FND_INLINE float2_t& operator%=(float2_t& a, const float_t scalar)
{
    FND_ASSERT(scalar != 0.0f);

    a = a % scalar;
    return a;
}

export constexpr float2_t& operator/=(float2_t& a, const float2_t b)
{
    FND_ASSERT(b.x != 0.0f && b.y != 0.0f);

    a = a / b;
    return a;
}

export constexpr float2_t& operator/=(float2_t& a, const float_t scalar)
{
    FND_ASSERT(scalar != 0.0f);

    a = a / scalar;
    return a;
}

export FND_INLINE float2_t abs(const float2_t v)
{
    return float2_t{abs(v.x), abs(v.y)};
}

export FND_INLINE float2_t acos(const float2_t v)
{
    return float2_t{acos(v.x), acos(v.y)};
}

export FND_INLINE bool2_t approx_equal(
    const float2_t a, const float2_t b, const float_t max_abs_diff = 1e-5f)
{
    FND_ASSERT(max_abs_diff >= 0);
    return bool2_t{
        approx_equal(a.x, b.x, max_abs_diff),
        approx_equal(a.y, b.y, max_abs_diff)};
}

export FND_INLINE bool2_t approx_equal(
    const float2_t a, const float_t scalar, const float_t max_abs_diff = 1e-5f)
{
    FND_ASSERT(max_abs_diff >= 0);
    return bool2_t{
        approx_equal(a.x, scalar, max_abs_diff),
        approx_equal(a.y, scalar, max_abs_diff)};
}

export FND_INLINE bool2_t approx_equal(
    const float_t scalar, const float2_t b, const float_t max_abs_diff = 1e-5f)
{
    FND_ASSERT(max_abs_diff >= 0);
    return bool2_t{
        approx_equal(scalar, b.x, max_abs_diff),
        approx_equal(scalar, b.y, max_abs_diff)};
}

export FND_INLINE float2_t asin(const float2_t v)
{
    return float2_t{asin(v.x), asin(v.y)};
}

export FND_INLINE float2_t atan(const float2_t v)
{
    return float2_t{atan(v.x), atan(v.y)};
}

export FND_INLINE float2_t atan2(const float2_t y, const float2_t x)
{
    return float2_t{atan2(y.x, x.x), atan2(y.y, x.y)};
}

export FND_INLINE float2_t ceil(const float2_t v)
{
    return float2_t{ceil(v.x), ceil(v.y)};
}

export FND_INLINE float2_t clamp(
    const float2_t v, const float2_t lower, const float2_t upper)
{
    FND_ASSERT(all(lower <= upper));

    return float2_t{clamp(v.x, lower.x, upper.x), clamp(v.y, lower.y, upper.y)};
}

export FND_INLINE float2_t clamp(
    const float2_t v, const float2_t lower, const float_t upper)
{
    FND_ASSERT(all(lower <= upper));

    return float2_t{clamp(v.x, lower.x, upper), clamp(v.y, lower.y, upper)};
}

export FND_INLINE float2_t clamp(
    const float2_t v, const float_t lower, const float2_t upper)
{
    FND_ASSERT(all(lower <= upper));

    return float2_t{clamp(v.x, lower, upper.x), clamp(v.y, lower, upper.y)};
}

export FND_INLINE float2_t clamp(
    const float2_t v, const float_t lower, const float_t upper)
{
    FND_ASSERT(lower <= upper);

    return float2_t{clamp(v.x, lower, upper), clamp(v.y, lower, upper)};
}

export FND_INLINE float_t cmax(const float2_t v)
{
    return max(v.x, v.y);
}

export FND_INLINE float_t cmin(const float2_t v)
{
    return min(v.x, v.y);
}

export constexpr float_t cmul(const float2_t v)
{
    return v.x * v.y;
}

export FND_INLINE float2_t cos(const float2_t v)
{
    return float2_t{cos(v.x), cos(v.y)};
}

export constexpr float_t csum(const float2_t v)
{
    return v.x + v.y;
}

export constexpr float2_t degrees(const float2_t v)
{
    return float2_t{degrees(v.x), degrees(v.y)};
}

export constexpr float_t distance_sqr(const float2_t a, const float2_t b)
{
    const float2_t d = a - b;
    return d.x * d.x + d.y * d.y;
}

export FND_INLINE float_t distance(const float2_t a, const float2_t b)
{
    const float_t d2 = distance_sqr(a, b);
    return sqrt(d2);
}

export constexpr float_t dot(const float2_t a, const float2_t b)
{
    return a.x * b.x + a.y * b.y;
}

export FND_INLINE float2_t exp(const float2_t v)
{
    return float2_t{exp(v.x), exp(v.y)};
}

export FND_INLINE float2_t exp2(const float2_t v)
{
    return float2_t{exp2(v.x), exp2(v.y)};
}

export FND_INLINE float2_t floor(const float2_t v)
{
    return float2_t{floor(v.x), floor(v.y)};
}

export FND_INLINE float2_t fmod(const float2_t a, const float2_t b)
{
    return float2_t{fmod(a.x, b.x), fmod(a.y, b.y)};
}

export FND_INLINE float2_t fmod(const float2_t a, const float_t scalar)
{
    return float2_t{fmod(a.x, scalar), fmod(a.y, scalar)};
}

export FND_INLINE float2_t fmod(const float_t scalar, const float2_t b)
{
    return float2_t{fmod(scalar, b.x), fmod(scalar, b.y)};
}

export FND_INLINE float2_t fractional(const float2_t v)
{
    return float2_t{fractional(v.x), fractional(v.y)};
}

export FND_INLINE bool2_t isfinite(const float2_t v)
{
    return bool2_t{isfinite(v.x), isfinite(v.y)};
}

export FND_INLINE bool2_t isinf(const float2_t v)
{
    return bool2_t{isinf(v.x), isinf(v.y)};
}

export FND_INLINE bool2_t isnan(const float2_t v)
{
    return bool2_t{isnan(v.x), isnan(v.y)};
}

export constexpr float_t length_sqr(const float2_t v)
{
    return v.x * v.x + v.y * v.y;
}

export FND_INLINE float_t length(const float2_t v)
{
    return sqrt(length_sqr(v));
}

export FND_INLINE float2_t lerp(
    const float2_t a, const float2_t b, const float_t t)
{
    return float2_t{lerp(a.x, b.x, t), lerp(a.y, b.y, t)};
}

export FND_INLINE float2_t lerp(
    const float2_t a, const float2_t b, const float2_t t)
{
    return float2_t{lerp(a.x, b.x, t.x), lerp(a.y, b.y, t.y)};
}

export FND_INLINE float2_t log(const float2_t v)
{
    return float2_t{log(v.x), log(v.y)};
}

export FND_INLINE float2_t log10(const float2_t v)
{
    return float2_t{log10(v.x), log10(v.y)};
}

export FND_INLINE float2_t log2(const float2_t v)
{
    return float2_t{log2(v.x), log2(v.y)};
}

export FND_INLINE float2_t max(const float2_t a, const float2_t b)
{
    return float2_t{max(a.x, b.x), max(a.y, b.y)};
}

export FND_INLINE float2_t max(const float2_t a, const float_t scalar)
{
    return float2_t{max(a.x, scalar), max(a.y, scalar)};
}

export FND_INLINE float2_t max(const float_t scalar, const float2_t b)
{
    return float2_t{max(scalar, b.x), max(scalar, b.y)};
}

export FND_INLINE float2_t min(const float2_t a, const float2_t b)
{
    return float2_t{min(a.x, b.x), min(a.y, b.y)};
}

export FND_INLINE float2_t min(const float2_t a, const float_t scalar)
{
    return float2_t{min(a.x, scalar), min(a.y, scalar)};
}

export FND_INLINE float2_t min(const float_t scalar, const float2_t b)
{
    return float2_t{min(scalar, b.x), min(scalar, b.y)};
}

// Splits each component into its fractional part (returned) and its integer
// part (stored in vi). Both parts have the sign of the component.
export FND_INLINE float2_t modf(const float2_t v, float2_t& vi)
{
    return float2_t{modf(v.x, vi.x), modf(v.y, vi.y)};
}

export FND_INLINE float2_t normalize(const float2_t v)
{
    const float_t l2 = length_sqr(v);
    FND_ASSERT(l2 > kFloatMinNormal);

    return v * rsqrt(l2);
}

export FND_INLINE float2_t normalize_safe(
    const float2_t v, const float2_t default_value = float2_t{})
{
    FND_ASSERT(all(!isnan(v)));
    FND_ASSERT(all(!isnan(default_value)));

    float2_t res_vec = default_value;
    const float_t l2 = length_sqr(v);

    if (isinf(l2)) {
        // NOTE:
        // l2 is infinity (e.g. v = {1e20f, 1}).
        // v should be rescaled so there is no overflow.
        // Rescaling is ok because normalize(v) == normalize(v * s), s > 0
        //
        // Scaling by cmax(abs(v)) needs no constant, but costs abs,
        // max and division instead of multiplication.
        //
        // 0x1p-66f is 2^-66. A power of two is exact: multiplying by it
        // lowers the exponent of each component by 66 and does not round.
        // Any 2^-k with 65 <= k <= 126 works
        // - k >= 65: the scaled squares of two kFloatMaxValue components
        //      do not overflow;
        // - k <= 126: the scaled l2 stays a normal float.

        const float2_t scaled_vec = v * 0x1p-66f;
        res_vec = scaled_vec * rsqrt(length_sqr(scaled_vec));
    }
    else if (l2 > kFloatMinNormal) {
        res_vec = v * rsqrt(l2);
    }

    FND_ASSERT(all(!isnan(res_vec))); // post condition
    return res_vec;
}

export FND_INLINE float2_t pow(const float2_t base, const float2_t exponent)
{
    return float2_t{pow(base.x, exponent.x), pow(base.y, exponent.y)};
}

export FND_INLINE float2_t pow(const float2_t base, const float_t exponent)
{
    return float2_t{pow(base.x, exponent), pow(base.y, exponent)};
}

export constexpr float2_t radians(const float2_t v)
{
    return float2_t{radians(v.x), radians(v.y)};
}

export FND_INLINE float2_t rcp(const float2_t v)
{
    return float2_t{rcp(v.x), rcp(v.y)};
}

export FND_INLINE float2_t rsqrt(const float2_t v)
{
    return float2_t{rsqrt(v.x), rsqrt(v.y)};
}

export FND_INLINE float2_t saturate(const float2_t v)
{
    return float2_t{saturate(v.x), saturate(v.y)};
}

export FND_INLINE float2_t sign(const float2_t v)
{
    return float2_t{sign(v.x), sign(v.y)};
}

export FND_INLINE float2_t sin(const float2_t v)
{
    return float2_t{sin(v.x), sin(v.y)};
}

export FND_INLINE float2_t smoothstep(
    const float2_t x, const float2_t edge0, const float2_t edge1)
{
    return float2_t{
        smoothstep(x.x, edge0.x, edge1.x), smoothstep(x.y, edge0.y, edge1.y)};
}

export FND_INLINE float2_t smoothstep(
    const float2_t x, const float_t edge0, const float_t edge1)
{
    return float2_t{
        smoothstep(x.x, edge0, edge1), smoothstep(x.y, edge0, edge1)};
}

export FND_INLINE float2_t sqrt(const float2_t v)
{
    return float2_t{sqrt(v.x), sqrt(v.y)};
}

export FND_INLINE float2_t tan(const float2_t v)
{
    return float2_t{tan(v.x), tan(v.y)};
}

export FND_INLINE float2_t trunc(const float2_t v)
{
    return float2_t{trunc(v.x), trunc(v.y)};
}

} // namespace fnd
