module;
#include "foundation/core/macros.h"

export module foundation.math:vector_float2;
import foundation.core;
import :scalar;
import :vector_bool;

namespace fnd {

export struct float2_t final {
    float_t x{0.0f};
    float_t y{0.0f};

    constexpr float2_t() = default;

    constexpr explicit float2_t(const bool2_t v2)
        : x{v2.x ? 1.0f : 0.0f}, y{v2.y ? 1.0f : 0.0f}
    {
    }

    constexpr explicit float2_t(const float_t val) : x{val}, y{val} {}

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

    constexpr float2_t& operator++()
    {
        ++x;
        ++y;
        return *this;
    }

    constexpr float2_t operator++(int) { return float2_t{x++, y++}; }

    constexpr float2_t& operator--()
    {
        --x;
        --y;
        return *this;
    }

    constexpr float2_t operator--(int) { return float2_t{x--, y--}; }

    constexpr float2_t operator-() const { return float2_t{-x, -y}; }

    constexpr float2_t& operator+=(const float2_t b)
    {
        x += b.x;
        y += b.y;
        return *this;
    }

    constexpr float2_t& operator+=(const float_t val)
    {
        x += val;
        y += val;
        return *this;
    }

    constexpr float2_t& operator-=(const float2_t b)
    {
        x -= b.x;
        y -= b.y;
        return *this;
    }

    constexpr float2_t& operator-=(const float_t val)
    {
        x -= val;
        y -= val;
        return *this;
    }

    constexpr float2_t& operator*=(const float2_t b)
    {
        x *= b.x;
        y *= b.y;
        return *this;
    }

    constexpr float2_t& operator*=(const float_t val)
    {
        x *= val;
        y *= val;
        return *this;
    }

    constexpr float2_t& operator/=(const float2_t b)
    {
        FND_ASSERT(b.x != 0.0f && b.y != 0.0f);

        x /= b.x;
        y /= b.y;
        return *this;
    }

    constexpr float2_t& operator/=(const float_t val)
    {
        FND_ASSERT(val != 0.0f);

        x /= val;
        y /= val;
        return *this;
    }

    // The result has the sign of the left operand, as fmod does.
    FND_INLINE float2_t& operator%=(const float2_t b)
    {
        FND_ASSERT(b.x != 0.0f && b.y != 0.0f);

        x = fmod(x, b.x);
        y = fmod(y, b.y);
        return *this;
    }

    FND_INLINE float2_t& operator%=(const float_t val)
    {
        FND_ASSERT(val != 0.0f);

        x = fmod(x, val);
        y = fmod(y, val);
        return *this;
    }
};

export constexpr bool2_t operator==(const float2_t a, const float2_t b)
{
    return bool2_t{a.x == b.x, a.y == b.y};
}

export constexpr bool2_t operator==(const float2_t a, const float_t val)
{
    return bool2_t{a.x == val, a.y == val};
}

export constexpr bool2_t operator==(const float_t val, const float2_t b)
{
    return bool2_t{val == b.x, val == b.y};
}

export constexpr bool2_t operator!=(const float2_t a, const float2_t b)
{
    return !(a == b);
}

export constexpr bool2_t operator!=(const float2_t a, const float_t val)
{
    return !(a == val);
}

export constexpr bool2_t operator!=(const float_t val, const float2_t b)
{
    return !(val == b);
}

export FND_INLINE bool2_t operator<(const float2_t a, const float2_t b)
{
    return bool2_t{a.x < b.x, a.y < b.y};
}

export FND_INLINE bool2_t operator<(const float2_t a, const float_t val)
{
    return bool2_t{a.x < val, a.y < val};
}

export FND_INLINE bool2_t operator<(const float_t val, const float2_t b)
{
    return bool2_t{val < b.x, val < b.y};
}

export FND_INLINE bool2_t operator<=(const float2_t a, const float2_t b)
{
    return bool2_t{a.x <= b.x, a.y <= b.y};
}

export FND_INLINE bool2_t operator<=(const float2_t a, const float_t val)
{
    return bool2_t{a.x <= val, a.y <= val};
}

export FND_INLINE bool2_t operator<=(const float_t val, const float2_t b)
{
    return bool2_t{val <= b.x, val <= b.y};
}

export FND_INLINE bool2_t operator>(const float2_t a, const float2_t b)
{
    return bool2_t{a.x > b.x, a.y > b.y};
}

export FND_INLINE bool2_t operator>(const float2_t a, const float_t val)
{
    return bool2_t{a.x > val, a.y > val};
}

export FND_INLINE bool2_t operator>(const float_t val, const float2_t b)
{
    return bool2_t{val > b.x, val > b.y};
}

export FND_INLINE bool2_t operator>=(const float2_t a, const float2_t b)
{
    return bool2_t{a.x >= b.x, a.y >= b.y};
}

export FND_INLINE bool2_t operator>=(const float2_t a, const float_t val)
{
    return bool2_t{a.x >= val, a.y >= val};
}

export FND_INLINE bool2_t operator>=(const float_t val, const float2_t b)
{
    return bool2_t{val >= b.x, val >= b.y};
}

export constexpr float2_t operator*(const float2_t a, const float2_t b)
{
    return float2_t{a.x * b.x, a.y * b.y};
}

export constexpr float2_t operator*(const float2_t a, const float_t val)
{
    return float2_t{a.x * val, a.y * val};
}

export constexpr float2_t operator*(const float_t val, const float2_t b)
{
    return float2_t{val * b.x, val * b.y};
}

export constexpr float2_t operator+(const float2_t a, const float2_t b)
{
    return float2_t{a.x + b.x, a.y + b.y};
}

export constexpr float2_t operator+(const float2_t a, const float_t val)
{
    return float2_t{a.x + val, a.y + val};
}

export constexpr float2_t operator+(const float_t val, const float2_t b)
{
    return float2_t{val + b.x, val + b.y};
}

export constexpr float2_t operator-(const float2_t a, const float2_t b)
{
    return float2_t{a.x - b.x, a.y - b.y};
}

export constexpr float2_t operator-(const float2_t a, const float_t val)
{
    return float2_t{a.x - val, a.y - val};
}

export constexpr float2_t operator-(const float_t val, const float2_t b)
{
    return float2_t{val - b.x, val - b.y};
}

// The result has the sign of the left operand, as fmod does.
export FND_INLINE float2_t operator%(const float2_t a, const float2_t b)
{
    FND_ASSERT(b.x != 0.0f && b.y != 0.0f);

    return float2_t{fmod(a.x, b.x), fmod(a.y, b.y)};
}

export FND_INLINE float2_t operator%(const float2_t a, const float_t val)
{
    FND_ASSERT(val != 0.0f);

    return float2_t{fmod(a.x, val), fmod(a.y, val)};
}

export FND_INLINE float2_t operator%(const float_t val, const float2_t b)
{
    FND_ASSERT(b.x != 0.0f && b.y != 0.0f);

    return float2_t{fmod(val, b.x), fmod(val, b.y)};
}

export constexpr float2_t operator/(const float2_t a, const float2_t b)
{
    FND_ASSERT(b.x != 0.0f && b.y != 0.0f);

    return float2_t{a.x / b.x, a.y / b.y};
}

export constexpr float2_t operator/(const float2_t a, const float_t val)
{
    FND_ASSERT(val != 0.0f);

    return float2_t{a.x / val, a.y / val};
}

export constexpr float2_t operator/(const float_t val, const float2_t b)
{
    FND_ASSERT(b.x != 0.0f && b.y != 0.0f);

    return float2_t{val / b.x, val / b.y};
}

export FND_INLINE float2_t abs(const float2_t v)
{
    return float2_t{abs(v.x), abs(v.y)};
}

export FND_INLINE float2_t acos(const float2_t v)
{
    return float2_t{acos(v.x), acos(v.y)};
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

export FND_INLINE float2_t fmod(const float2_t a, const float_t val)
{
    return float2_t{fmod(a.x, val), fmod(a.y, val)};
}

export FND_INLINE float2_t fmod(const float_t val, const float2_t b)
{
    return float2_t{fmod(val, b.x), fmod(val, b.y)};
}

export FND_INLINE float2_t fractional(const float2_t v)
{
    return float2_t{fractional(v.x), fractional(v.y)};
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

export FND_INLINE float2_t max(const float2_t a, const float_t val)
{
    return float2_t{max(a.x, val), max(a.y, val)};
}

export FND_INLINE float2_t max(const float_t val, const float2_t b)
{
    return float2_t{max(val, b.x), max(val, b.y)};
}

export FND_INLINE float2_t min(const float2_t a, const float2_t b)
{
    return float2_t{min(a.x, b.x), min(a.y, b.y)};
}

export FND_INLINE float2_t min(const float2_t a, const float_t val)
{
    return float2_t{min(a.x, val), min(a.y, val)};
}

export FND_INLINE float2_t min(const float_t val, const float2_t b)
{
    return float2_t{min(val, b.x), min(val, b.y)};
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
    const float2_t edge0, const float2_t edge1, const float2_t x)
{
    return float2_t{
        smoothstep(edge0.x, edge1.x, x.x), smoothstep(edge0.y, edge1.y, x.y)};
}

export FND_INLINE float2_t smoothstep(
    const float_t edge0, const float_t edge1, const float2_t x)
{
    return float2_t{
        smoothstep(edge0, edge1, x.x), smoothstep(edge0, edge1, x.y)};
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
