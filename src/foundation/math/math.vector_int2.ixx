module;
#include "foundation/core/macros.h"

export module foundation.math:vector_int2;
import foundation.core;
import :vector_bool;

namespace fnd {

export struct int2_t final {
    static const int2_t kZero;
    static const int2_t kUnitX;
    static const int2_t kUnitY;

    int_t x{0};
    int_t y{0};

    constexpr int2_t() = default;

    constexpr explicit int2_t(const int_t scalar) : x{scalar}, y{scalar} {}

    constexpr int2_t(const int_t x, const int_t y) : x{x}, y{y} {}

    constexpr const int_t& operator[](const uint_t idx) const
    {
        FND_ASSERT(idx < 2);
        return idx == 0 ? x : y;
    }

    constexpr int_t& operator[](const uint_t idx)
    {
        return const_cast<int_t&>(static_cast<const int2_t&>(*this)[idx]);
    }

    constexpr int2_t& operator++()
    {
        FND_ASSERT(x != kIntMaxValue);
        FND_ASSERT(y != kIntMaxValue);

        ++x;
        ++y;
        return *this;
    }

    constexpr int2_t operator++(int)
    {
        FND_ASSERT(x != kIntMaxValue);
        FND_ASSERT(y != kIntMaxValue);

        return int2_t{x++, y++};
    }

    constexpr int2_t& operator--()
    {
        FND_ASSERT(x != kIntMinValue);
        FND_ASSERT(y != kIntMinValue);

        --x;
        --y;
        return *this;
    }

    constexpr int2_t operator--(int)
    {
        FND_ASSERT(x != kIntMinValue);
        FND_ASSERT(y != kIntMinValue);

        return int2_t{x--, y--};
    }

    constexpr int2_t operator-() const
    {
        FND_ASSERT(x != kIntMinValue);
        FND_ASSERT(y != kIntMinValue);

        return int2_t{-x, -y};
    }

    constexpr int2_t operator~() const { return int2_t{~x, ~y}; }

    constexpr int2_t& operator+=(const int2_t b)
    {
        FND_ASSERT(
            long_t{x} + b.x >= kIntMinValue && long_t{x} + b.x <= kIntMaxValue);
        FND_ASSERT(
            long_t{y} + b.y >= kIntMinValue && long_t{y} + b.y <= kIntMaxValue);

        x += b.x;
        y += b.y;
        return *this;
    }

    constexpr int2_t& operator+=(const int_t scalar)
    {
        FND_ASSERT(long_t{x} + scalar >= kIntMinValue
            && long_t{x} + scalar <= kIntMaxValue);
        FND_ASSERT(long_t{y} + scalar >= kIntMinValue
            && long_t{y} + scalar <= kIntMaxValue);

        x += scalar;
        y += scalar;
        return *this;
    }

    constexpr int2_t& operator-=(const int2_t b)
    {
        FND_ASSERT(
            long_t{x} - b.x >= kIntMinValue && long_t{x} - b.x <= kIntMaxValue);
        FND_ASSERT(
            long_t{y} - b.y >= kIntMinValue && long_t{y} - b.y <= kIntMaxValue);

        x -= b.x;
        y -= b.y;
        return *this;
    }

    constexpr int2_t& operator-=(const int_t scalar)
    {
        FND_ASSERT(long_t{x} - scalar >= kIntMinValue
            && long_t{x} - scalar <= kIntMaxValue);
        FND_ASSERT(long_t{y} - scalar >= kIntMinValue
            && long_t{y} - scalar <= kIntMaxValue);

        x -= scalar;
        y -= scalar;
        return *this;
    }

    constexpr int2_t& operator*=(const int2_t b)
    {
        FND_ASSERT(
            long_t{x} * b.x >= kIntMinValue && long_t{x} * b.x <= kIntMaxValue);
        FND_ASSERT(
            long_t{y} * b.y >= kIntMinValue && long_t{y} * b.y <= kIntMaxValue);

        x *= b.x;
        y *= b.y;
        return *this;
    }

    constexpr int2_t& operator*=(const int_t scalar)
    {
        FND_ASSERT(long_t{x} * scalar >= kIntMinValue
            && long_t{x} * scalar <= kIntMaxValue);
        FND_ASSERT(long_t{y} * scalar >= kIntMinValue
            && long_t{y} * scalar <= kIntMaxValue);

        x *= scalar;
        y *= scalar;
        return *this;
    }

    constexpr int2_t& operator/=(const int2_t b)
    {
        FND_ASSERT(b.x != 0 && b.y != 0);
        FND_ASSERT(!(x == kIntMinValue && b.x == -1));
        FND_ASSERT(!(y == kIntMinValue && b.y == -1));

        x /= b.x;
        y /= b.y;
        return *this;
    }

    constexpr int2_t& operator/=(const int_t scalar)
    {
        FND_ASSERT(scalar != 0);
        FND_ASSERT(!(scalar == -1 && (x == kIntMinValue || y == kIntMinValue)));

        x /= scalar;
        y /= scalar;
        return *this;
    }

    constexpr int2_t& operator%=(const int2_t b)
    {
        FND_ASSERT(b.x != 0 && b.y != 0);
        FND_ASSERT(!(x == kIntMinValue && b.x == -1));
        FND_ASSERT(!(y == kIntMinValue && b.y == -1));

        x %= b.x;
        y %= b.y;
        return *this;
    }

    constexpr int2_t& operator%=(const int_t scalar)
    {
        FND_ASSERT(scalar != 0);
        FND_ASSERT(!(scalar == -1 && x == kIntMinValue));
        FND_ASSERT(!(scalar == -1 && y == kIntMinValue));

        x %= scalar;
        y %= scalar;
        return *this;
    }

    constexpr int2_t& operator&=(const int2_t b)
    {
        x &= b.x;
        y &= b.y;
        return *this;
    }

    constexpr int2_t& operator&=(const int_t scalar)
    {
        x &= scalar;
        y &= scalar;
        return *this;
    }

    constexpr int2_t& operator|=(const int2_t b)
    {
        x |= b.x;
        y |= b.y;
        return *this;
    }

    constexpr int2_t& operator|=(const int_t scalar)
    {
        x |= scalar;
        y |= scalar;
        return *this;
    }

    constexpr int2_t& operator^=(const int2_t b)
    {
        x ^= b.x;
        y ^= b.y;
        return *this;
    }

    constexpr int2_t& operator^=(const int_t scalar)
    {
        x ^= scalar;
        y ^= scalar;
        return *this;
    }

    constexpr int2_t& operator<<=(const int2_t b)
    {
        FND_ASSERT(b.x >= 0 && b.x < 32);
        FND_ASSERT(b.y >= 0 && b.y < 32);

        x <<= b.x;
        y <<= b.y;
        return *this;
    }

    constexpr int2_t& operator<<=(const int_t scalar)
    {
        FND_ASSERT(scalar >= 0 && scalar < 32);

        x <<= scalar;
        y <<= scalar;
        return *this;
    }

    constexpr int2_t& operator>>=(const int2_t b)
    {
        FND_ASSERT(b.x >= 0 && b.x < 32);
        FND_ASSERT(b.y >= 0 && b.y < 32);

        x >>= b.x;
        y >>= b.y;
        return *this;
    }

    constexpr int2_t& operator>>=(const int_t scalar)
    {
        FND_ASSERT(scalar >= 0 && scalar < 32);

        x >>= scalar;
        y >>= scalar;
        return *this;
    }
};

constexpr int2_t int2_t::kZero{0, 0};
constexpr int2_t int2_t::kUnitX{1, 0};
constexpr int2_t int2_t::kUnitY{0, 1};

export constexpr bool2_t operator==(const int2_t a, const int2_t b)
{
    return bool2_t{a.x == b.x, a.y == b.y};
}

export constexpr bool2_t operator==(const int2_t a, const int_t scalar)
{
    return bool2_t{a.x == scalar, a.y == scalar};
}

export constexpr bool2_t operator==(const int_t scalar, const int2_t b)
{
    return bool2_t{scalar == b.x, scalar == b.y};
}

export constexpr bool2_t operator!=(const int2_t a, const int2_t b)
{
    return !(a == b);
}

export constexpr bool2_t operator!=(const int2_t a, const int_t scalar)
{
    return !(a == scalar);
}

export constexpr bool2_t operator!=(const int_t scalar, const int2_t b)
{
    return !(scalar == b);
}

export constexpr bool2_t operator<(const int2_t a, const int2_t b)
{
    return bool2_t{a.x < b.x, a.y < b.y};
}

export constexpr bool2_t operator<(const int2_t a, const int_t scalar)
{
    return bool2_t{a.x < scalar, a.y < scalar};
}

export constexpr bool2_t operator<(const int_t scalar, const int2_t b)
{
    return bool2_t{scalar < b.x, scalar < b.y};
}

export constexpr bool2_t operator<=(const int2_t a, const int2_t b)
{
    return bool2_t{a.x <= b.x, a.y <= b.y};
}

export constexpr bool2_t operator<=(const int2_t a, const int_t scalar)
{
    return bool2_t{a.x <= scalar, a.y <= scalar};
}

export constexpr bool2_t operator<=(const int_t scalar, const int2_t b)
{
    return bool2_t{scalar <= b.x, scalar <= b.y};
}

export constexpr bool2_t operator>(const int2_t a, const int2_t b)
{
    return bool2_t{a.x > b.x, a.y > b.y};
}

export constexpr bool2_t operator>(const int2_t a, const int_t scalar)
{
    return bool2_t{a.x > scalar, a.y > scalar};
}

export constexpr bool2_t operator>(const int_t scalar, const int2_t b)
{
    return bool2_t{scalar > b.x, scalar > b.y};
}

export constexpr bool2_t operator>=(const int2_t a, const int2_t b)
{
    return bool2_t{a.x >= b.x, a.y >= b.y};
}

export constexpr bool2_t operator>=(const int2_t a, const int_t scalar)
{
    return bool2_t{a.x >= scalar, a.y >= scalar};
}

export constexpr bool2_t operator>=(const int_t scalar, const int2_t b)
{
    return bool2_t{scalar >= b.x, scalar >= b.y};
}

export constexpr int2_t operator&(const int2_t a, const int2_t b)
{
    return int2_t{a.x & b.x, a.y & b.y};
}

export constexpr int2_t operator&(const int2_t a, const int_t scalar)
{
    return int2_t{a.x & scalar, a.y & scalar};
}

export constexpr int2_t operator&(const int_t scalar, const int2_t b)
{
    return int2_t{scalar & b.x, scalar & b.y};
}

export constexpr int2_t operator*(const int2_t a, const int2_t b)
{
    FND_ASSERT(
        long_t{a.x} * b.x >= kIntMinValue && long_t{a.x} * b.x <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.y} * b.y >= kIntMinValue && long_t{a.y} * b.y <= kIntMaxValue);

    return int2_t{a.x * b.x, a.y * b.y};
}

export constexpr int2_t operator*(const int2_t a, const int_t scalar)
{
    FND_ASSERT(long_t{a.x} * scalar >= kIntMinValue
        && long_t{a.x} * scalar <= kIntMaxValue);
    FND_ASSERT(long_t{a.y} * scalar >= kIntMinValue
        && long_t{a.y} * scalar <= kIntMaxValue);

    return int2_t{a.x * scalar, a.y * scalar};
}

export constexpr int2_t operator*(const int_t scalar, const int2_t b)
{
    FND_ASSERT(long_t{scalar} * b.x >= kIntMinValue
        && long_t{scalar} * b.x <= kIntMaxValue);
    FND_ASSERT(long_t{scalar} * b.y >= kIntMinValue
        && long_t{scalar} * b.y <= kIntMaxValue);

    return int2_t{scalar * b.x, scalar * b.y};
}

export constexpr int2_t operator+(const int2_t a, const int2_t b)
{
    FND_ASSERT(
        long_t{a.x} + b.x >= kIntMinValue && long_t{a.x} + b.x <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.y} + b.y >= kIntMinValue && long_t{a.y} + b.y <= kIntMaxValue);

    return int2_t{a.x + b.x, a.y + b.y};
}

export constexpr int2_t operator+(const int2_t a, const int_t scalar)
{
    FND_ASSERT(long_t{a.x} + scalar >= kIntMinValue
        && long_t{a.x} + scalar <= kIntMaxValue);
    FND_ASSERT(long_t{a.y} + scalar >= kIntMinValue
        && long_t{a.y} + scalar <= kIntMaxValue);

    return int2_t{a.x + scalar, a.y + scalar};
}

export constexpr int2_t operator+(const int_t scalar, const int2_t b)
{
    FND_ASSERT(long_t{scalar} + b.x >= kIntMinValue
        && long_t{scalar} + b.x <= kIntMaxValue);
    FND_ASSERT(long_t{scalar} + b.y >= kIntMinValue
        && long_t{scalar} + b.y <= kIntMaxValue);

    return int2_t{scalar + b.x, scalar + b.y};
}

export constexpr int2_t operator-(const int2_t a, const int2_t b)
{
    FND_ASSERT(
        long_t{a.x} - b.x >= kIntMinValue && long_t{a.x} - b.x <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.y} - b.y >= kIntMinValue && long_t{a.y} - b.y <= kIntMaxValue);

    return int2_t{a.x - b.x, a.y - b.y};
}

export constexpr int2_t operator-(const int2_t a, const int_t scalar)
{
    FND_ASSERT(long_t{a.x} - scalar >= kIntMinValue
        && long_t{a.x} - scalar <= kIntMaxValue);
    FND_ASSERT(long_t{a.y} - scalar >= kIntMinValue
        && long_t{a.y} - scalar <= kIntMaxValue);

    return int2_t{a.x - scalar, a.y - scalar};
}

export constexpr int2_t operator-(const int_t scalar, const int2_t b)
{
    FND_ASSERT(long_t{scalar} - b.x >= kIntMinValue
        && long_t{scalar} - b.x <= kIntMaxValue);
    FND_ASSERT(long_t{scalar} - b.y >= kIntMinValue
        && long_t{scalar} - b.y <= kIntMaxValue);

    return int2_t{scalar - b.x, scalar - b.y};
}

export constexpr int2_t operator%(const int2_t a, const int2_t b)
{
    FND_ASSERT(all(b != 0));
    FND_ASSERT(!any(a == kIntMinValue && b == -1));

    return int2_t{a.x % b.x, a.y % b.y};
}

export constexpr int2_t operator%(const int2_t a, const int_t scalar)
{
    FND_ASSERT(scalar != 0);
    FND_ASSERT(!(scalar == -1 && any(a == kIntMinValue)));

    return int2_t{a.x % scalar, a.y % scalar};
}

export constexpr int2_t operator%(const int_t scalar, const int2_t b)
{
    FND_ASSERT(all(b != 0));
    FND_ASSERT(!(scalar == kIntMinValue && any(b == -1)));

    return int2_t{scalar % b.x, scalar % b.y};
}

export constexpr int2_t operator/(const int2_t a, const int2_t b)
{
    FND_ASSERT(all(b != 0));
    FND_ASSERT(!any(a == kIntMinValue && b == -1));

    return int2_t{a.x / b.x, a.y / b.y};
}

export constexpr int2_t operator/(const int2_t a, const int_t scalar)
{
    FND_ASSERT(scalar != 0);
    FND_ASSERT(!(scalar == -1 && any(a == kIntMinValue)));

    return int2_t{a.x / scalar, a.y / scalar};
}

export constexpr int2_t operator/(const int_t scalar, const int2_t b)
{
    FND_ASSERT(all(b != 0));
    FND_ASSERT(!(scalar == kIntMinValue && any(b == -1)));

    return int2_t{scalar / b.x, scalar / b.y};
}

// NOTE:
// operator<< does not check the result for overflow, unlike operator*. Since
// C++20 a left shift is defined for every value: the bits shifted out are
// discarded, so the result wraps modulo 2^32 (kIntMaxValue << 1 is -2).
export constexpr int2_t operator<<(const int2_t a, const int2_t b)
{
    FND_ASSERT(all(b >= 0 && b < 32));

    return int2_t{a.x << b.x, a.y << b.y};
}

export constexpr int2_t operator<<(const int2_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0 && scalar < 32);

    return int2_t{a.x << scalar, a.y << scalar};
}

export constexpr int2_t operator<<(const int_t scalar, const int2_t b)
{
    FND_ASSERT(all(b >= 0 && b < 32));

    return int2_t{scalar << b.x, scalar << b.y};
}

export constexpr int2_t operator>>(const int2_t a, const int2_t b)
{
    FND_ASSERT(all(b >= 0 && b < 32));

    return int2_t{a.x >> b.x, a.y >> b.y};
}

export constexpr int2_t operator>>(const int2_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0 && scalar < 32);

    return int2_t{a.x >> scalar, a.y >> scalar};
}

export constexpr int2_t operator>>(const int_t scalar, const int2_t b)
{
    FND_ASSERT(all(b >= 0 && b < 32));

    return int2_t{scalar >> b.x, scalar >> b.y};
}

export constexpr int2_t operator^(const int2_t a, const int2_t b)
{
    return int2_t{a.x ^ b.x, a.y ^ b.y};
}

export constexpr int2_t operator^(const int2_t a, const int_t scalar)
{
    return int2_t{a.x ^ scalar, a.y ^ scalar};
}

export constexpr int2_t operator^(const int_t scalar, const int2_t b)
{
    return int2_t{scalar ^ b.x, scalar ^ b.y};
}

export constexpr int2_t operator|(const int2_t a, const int2_t b)
{
    return int2_t{a.x | b.x, a.y | b.y};
}

export constexpr int2_t operator|(const int2_t a, const int_t scalar)
{
    return int2_t{a.x | scalar, a.y | scalar};
}

export constexpr int2_t operator|(const int_t scalar, const int2_t b)
{
    return int2_t{scalar | b.x, scalar | b.y};
}

export constexpr int2_t abs(const int2_t v)
{
    return int2_t{abs(v.x), abs(v.y)};
}

export constexpr int2_t clamp(
    const int2_t v, const int2_t lower, const int2_t upper)
{
    FND_ASSERT(all(lower <= upper));

    return int2_t{clamp(v.x, lower.x, upper.x), clamp(v.y, lower.y, upper.y)};
}

export constexpr int2_t clamp(
    const int2_t v, const int2_t lower, const int_t upper)
{
    FND_ASSERT(all(lower <= upper));

    return int2_t{clamp(v.x, lower.x, upper), clamp(v.y, lower.y, upper)};
}

export constexpr int2_t clamp(
    const int2_t v, const int_t lower, const int2_t upper)
{
    FND_ASSERT(all(lower <= upper));

    return int2_t{clamp(v.x, lower, upper.x), clamp(v.y, lower, upper.y)};
}

export constexpr int2_t clamp(
    const int2_t v, const int_t lower, const int_t upper)
{
    FND_ASSERT(lower <= upper);

    return int2_t{clamp(v.x, lower, upper), clamp(v.y, lower, upper)};
}

export constexpr int_t cmax(const int2_t v)
{
    return max(v.x, v.y);
}

export constexpr int_t cmin(const int2_t v)
{
    return min(v.x, v.y);
}

export constexpr int_t cmul(const int2_t v)
{
    FND_ASSERT(
        long_t{v.x} * v.y >= kIntMinValue && long_t{v.x} * v.y <= kIntMaxValue);

    return v.x * v.y;
}

export constexpr int_t csum(const int2_t v)
{
    FND_ASSERT(
        long_t{v.x} + v.y >= kIntMinValue && long_t{v.x} + v.y <= kIntMaxValue);

    return v.x + v.y;
}

export constexpr int2_t max(const int2_t a, const int2_t b)
{
    return int2_t{max(a.x, b.x), max(a.y, b.y)};
}

export constexpr int2_t max(const int2_t a, const int_t scalar)
{
    return int2_t{max(a.x, scalar), max(a.y, scalar)};
}

export constexpr int2_t max(const int_t scalar, const int2_t b)
{
    return int2_t{max(scalar, b.x), max(scalar, b.y)};
}

export constexpr int2_t min(const int2_t a, const int2_t b)
{
    return int2_t{min(a.x, b.x), min(a.y, b.y)};
}

export constexpr int2_t min(const int2_t a, const int_t scalar)
{
    return int2_t{min(a.x, scalar), min(a.y, scalar)};
}

export constexpr int2_t min(const int_t scalar, const int2_t b)
{
    return int2_t{min(scalar, b.x), min(scalar, b.y)};
}

export constexpr int2_t sign(const int2_t v)
{
    return int2_t{sign(v.x), sign(v.y)};
}

} // namespace fnd
