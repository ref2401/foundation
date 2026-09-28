module;
#include "foundation/core/macros.h"

export module foundation.math:vector_uint2;
import foundation.core;
import :vector_bool;

namespace fnd {

export struct uint2_t final {
    uint_t x{0};
    uint_t y{0};

    constexpr uint2_t() = default;
    constexpr explicit uint2_t(const bool2_t v2) : x{v2.x}, y{v2.y} {}
    constexpr explicit uint2_t(const uint_t scalar) : x{scalar}, y{scalar} {}
    constexpr uint2_t(const uint_t x, const uint_t y) : x{x}, y{y} {}


    constexpr const uint_t& operator[](const uint_t idx) const
    {
        FND_ASSERT(idx < 2);
        return idx == 0 ? x : y;
    }

    constexpr uint_t& operator[](const uint_t idx)
    {
        return const_cast<uint_t&>(static_cast<const uint2_t&>(*this)[idx]);
    }

    constexpr uint2_t& operator++()
    {
        ++x;
        ++y;
        return *this;
    }

    constexpr uint2_t operator++(int) { return uint2_t{x++, y++}; }

    constexpr uint2_t& operator--()
    {
        --x;
        --y;
        return *this;
    }

    constexpr uint2_t operator--(int) { return uint2_t{x--, y--}; }

    constexpr uint2_t operator~() const { return uint2_t{~x, ~y}; }

    constexpr uint2_t& operator+=(const uint2_t b)
    {
        x += b.x;
        y += b.y;
        return *this;
    }

    constexpr uint2_t& operator+=(const uint_t scalar)
    {
        x += scalar;
        y += scalar;
        return *this;
    }

    constexpr uint2_t& operator+=(const int_t scalar)
    {
        FND_ASSERT(scalar >= 0);

        x += scalar;
        y += scalar;
        return *this;
    }

    constexpr uint2_t& operator-=(const uint2_t b)
    {
        x -= b.x;
        y -= b.y;
        return *this;
    }

    constexpr uint2_t& operator-=(const uint_t scalar)
    {
        x -= scalar;
        y -= scalar;
        return *this;
    }

    constexpr uint2_t& operator-=(const int_t scalar)
    {
        FND_ASSERT(scalar >= 0);

        x -= scalar;
        y -= scalar;
        return *this;
    }

    constexpr uint2_t& operator*=(const uint2_t b)
    {
        x *= b.x;
        y *= b.y;
        return *this;
    }

    constexpr uint2_t& operator*=(const uint_t scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    constexpr uint2_t& operator*=(const int_t scalar)
    {
        FND_ASSERT(scalar >= 0);

        x *= scalar;
        y *= scalar;
        return *this;
    }

    constexpr uint2_t& operator/=(const uint2_t b)
    {
        FND_ASSERT(b.x != 0 && b.y != 0);

        x /= b.x;
        y /= b.y;
        return *this;
    }

    constexpr uint2_t& operator/=(const uint_t scalar)
    {
        FND_ASSERT(scalar != 0);

        x /= scalar;
        y /= scalar;
        return *this;
    }

    constexpr uint2_t& operator/=(const int_t scalar)
    {
        FND_ASSERT(scalar > 0);

        x /= scalar;
        y /= scalar;
        return *this;
    }

    constexpr uint2_t& operator%=(const uint2_t b)
    {
        FND_ASSERT(b.x != 0 && b.y != 0);

        x %= b.x;
        y %= b.y;
        return *this;
    }

    constexpr uint2_t& operator%=(const uint_t scalar)
    {
        FND_ASSERT(scalar != 0);

        x %= scalar;
        y %= scalar;
        return *this;
    }

    constexpr uint2_t& operator%=(const int_t scalar)
    {
        FND_ASSERT(scalar > 0);

        x %= scalar;
        y %= scalar;
        return *this;
    }

    constexpr uint2_t& operator&=(const uint2_t b)
    {
        x &= b.x;
        y &= b.y;
        return *this;
    }

    constexpr uint2_t& operator&=(const uint_t scalar)
    {
        x &= scalar;
        y &= scalar;
        return *this;
    }

    constexpr uint2_t& operator&=(const int_t scalar)
    {
        FND_ASSERT(scalar >= 0);

        x &= scalar;
        y &= scalar;
        return *this;
    }

    constexpr uint2_t& operator|=(const uint2_t b)
    {
        x |= b.x;
        y |= b.y;
        return *this;
    }

    constexpr uint2_t& operator|=(const uint_t scalar)
    {
        x |= scalar;
        y |= scalar;
        return *this;
    }

    constexpr uint2_t& operator|=(const int_t scalar)
    {
        FND_ASSERT(scalar >= 0);

        x |= scalar;
        y |= scalar;
        return *this;
    }

    constexpr uint2_t& operator^=(const uint2_t b)
    {
        x ^= b.x;
        y ^= b.y;
        return *this;
    }

    constexpr uint2_t& operator^=(const uint_t scalar)
    {
        x ^= scalar;
        y ^= scalar;
        return *this;
    }

    constexpr uint2_t& operator^=(const int_t scalar)
    {
        FND_ASSERT(scalar >= 0);

        x ^= scalar;
        y ^= scalar;
        return *this;
    }

    constexpr uint2_t& operator<<=(const uint2_t b)
    {
        FND_ASSERT(b.x < 32);
        FND_ASSERT(b.y < 32);

        x <<= b.x;
        y <<= b.y;
        return *this;
    }

    constexpr uint2_t& operator<<=(const uint_t scalar)
    {
        FND_ASSERT(scalar < 32);

        x <<= scalar;
        y <<= scalar;
        return *this;
    }

    constexpr uint2_t& operator<<=(const int_t scalar)
    {
        FND_ASSERT(scalar >= 0 && scalar < 32);

        x <<= scalar;
        y <<= scalar;
        return *this;
    }

    constexpr uint2_t& operator>>=(const uint2_t b)
    {
        FND_ASSERT(b.x < 32);
        FND_ASSERT(b.y < 32);

        x >>= b.x;
        y >>= b.y;
        return *this;
    }

    constexpr uint2_t& operator>>=(const uint_t scalar)
    {
        FND_ASSERT(scalar < 32);

        x >>= scalar;
        y >>= scalar;
        return *this;
    }

    constexpr uint2_t& operator>>=(const int_t scalar)
    {
        FND_ASSERT(scalar >= 0 && scalar < 32);

        x >>= scalar;
        y >>= scalar;
        return *this;
    }
};

export constexpr bool2_t operator==(const uint2_t a, const uint2_t b)
{
    return bool2_t{a.x == b.x, a.y == b.y};
}

export constexpr bool2_t operator==(const uint2_t a, const uint_t scalar)
{
    return bool2_t{a.x == scalar, a.y == scalar};
}

export constexpr bool2_t operator==(const uint_t scalar, const uint2_t b)
{
    return bool2_t{scalar == b.x, scalar == b.y};
}

export constexpr bool2_t operator==(const uint2_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    const uint_t uval = static_cast<uint_t>(scalar);
    return bool2_t{a.x == uval, a.y == uval};
}

export constexpr bool2_t operator==(const int_t scalar, const uint2_t b)
{
    FND_ASSERT(scalar >= 0);

    const uint_t uval = static_cast<uint_t>(scalar);
    return bool2_t{uval == b.x, uval == b.y};
}

export constexpr bool2_t operator!=(const uint2_t a, const uint2_t b)
{
    return !(a == b);
}

export constexpr bool2_t operator!=(const uint2_t a, const uint_t scalar)
{
    return !(a == scalar);
}

export constexpr bool2_t operator!=(const uint_t scalar, const uint2_t b)
{
    return !(scalar == b);
}

export constexpr bool2_t operator!=(const uint2_t a, const int_t scalar)
{
    return !(a == scalar);
}

export constexpr bool2_t operator!=(const int_t scalar, const uint2_t b)
{
    return !(scalar == b);
}

export constexpr bool2_t operator<(const uint2_t a, const uint2_t b)
{
    return bool2_t{a.x < b.x, a.y < b.y};
}

export constexpr bool2_t operator<(const uint2_t a, const uint_t scalar)
{
    return bool2_t{a.x < scalar, a.y < scalar};
}

export constexpr bool2_t operator<(const uint_t scalar, const uint2_t b)
{
    return bool2_t{scalar < b.x, scalar < b.y};
}

export constexpr bool2_t operator<(const uint2_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    const uint_t uval = static_cast<uint_t>(scalar);
    return bool2_t{a.x < uval, a.y < uval};
}

export constexpr bool2_t operator<(const int_t scalar, const uint2_t b)
{
    FND_ASSERT(scalar >= 0);

    const uint_t uval = static_cast<uint_t>(scalar);
    return bool2_t{uval < b.x, uval < b.y};
}

export constexpr bool2_t operator<=(const uint2_t a, const uint2_t b)
{
    return bool2_t{a.x <= b.x, a.y <= b.y};
}

export constexpr bool2_t operator<=(const uint2_t a, const uint_t scalar)
{
    return bool2_t{a.x <= scalar, a.y <= scalar};
}

export constexpr bool2_t operator<=(const uint_t scalar, const uint2_t b)
{
    return bool2_t{scalar <= b.x, scalar <= b.y};
}

export constexpr bool2_t operator<=(const uint2_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    const uint_t uval = static_cast<uint_t>(scalar);
    return bool2_t{a.x <= uval, a.y <= uval};
}

export constexpr bool2_t operator<=(const int_t scalar, const uint2_t b)
{
    FND_ASSERT(scalar >= 0);

    const uint_t uval = static_cast<uint_t>(scalar);
    return bool2_t{uval <= b.x, uval <= b.y};
}

export constexpr bool2_t operator>(const uint2_t a, const uint2_t b)
{
    return bool2_t{a.x > b.x, a.y > b.y};
}

export constexpr bool2_t operator>(const uint2_t a, const uint_t scalar)
{
    return bool2_t{a.x > scalar, a.y > scalar};
}

export constexpr bool2_t operator>(const uint_t scalar, const uint2_t b)
{
    return bool2_t{scalar > b.x, scalar > b.y};
}

export constexpr bool2_t operator>(const uint2_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    const uint_t uval = static_cast<uint_t>(scalar);
    return bool2_t{a.x > uval, a.y > uval};
}

export constexpr bool2_t operator>(const int_t scalar, const uint2_t b)
{
    FND_ASSERT(scalar >= 0);

    const uint_t uval = static_cast<uint_t>(scalar);
    return bool2_t{uval > b.x, uval > b.y};
}

export constexpr bool2_t operator>=(const uint2_t a, const uint2_t b)
{
    return bool2_t{a.x >= b.x, a.y >= b.y};
}

export constexpr bool2_t operator>=(const uint2_t a, const uint_t scalar)
{
    return bool2_t{a.x >= scalar, a.y >= scalar};
}

export constexpr bool2_t operator>=(const uint_t scalar, const uint2_t b)
{
    return bool2_t{scalar >= b.x, scalar >= b.y};
}

export constexpr bool2_t operator>=(const uint2_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    const uint_t uval = static_cast<uint_t>(scalar);
    return bool2_t{a.x >= uval, a.y >= uval};
}

export constexpr bool2_t operator>=(const int_t scalar, const uint2_t b)
{
    FND_ASSERT(scalar >= 0);

    const uint_t uval = static_cast<uint_t>(scalar);
    return bool2_t{uval >= b.x, uval >= b.y};
}

export constexpr uint2_t operator&(const uint2_t a, const uint2_t b)
{
    return uint2_t{a.x & b.x, a.y & b.y};
}

export constexpr uint2_t operator&(const uint2_t a, const uint_t scalar)
{
    return uint2_t{a.x & scalar, a.y & scalar};
}

export constexpr uint2_t operator&(const uint_t scalar, const uint2_t b)
{
    return uint2_t{scalar & b.x, scalar & b.y};
}

export constexpr uint2_t operator&(const uint2_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    return uint2_t{a.x & scalar, a.y & scalar};
}

export constexpr uint2_t operator&(const int_t scalar, const uint2_t b)
{
    FND_ASSERT(scalar >= 0);

    return uint2_t{scalar & b.x, scalar & b.y};
}

export constexpr uint2_t operator*(const uint2_t a, const uint2_t b)
{
    return uint2_t{a.x * b.x, a.y * b.y};
}

export constexpr uint2_t operator*(const uint2_t a, const uint_t scalar)
{
    return uint2_t{a.x * scalar, a.y * scalar};
}

export constexpr uint2_t operator*(const uint_t scalar, const uint2_t b)
{
    return uint2_t{scalar * b.x, scalar * b.y};
}

export constexpr uint2_t operator*(const uint2_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    return uint2_t{a.x * scalar, a.y * scalar};
}

export constexpr uint2_t operator*(const int_t scalar, const uint2_t b)
{
    FND_ASSERT(scalar >= 0);

    return uint2_t{scalar * b.x, scalar * b.y};
}

export constexpr uint2_t operator+(const uint2_t a, const uint2_t b)
{
    return uint2_t{a.x + b.x, a.y + b.y};
}

export constexpr uint2_t operator+(const uint2_t a, const uint_t scalar)
{
    return uint2_t{a.x + scalar, a.y + scalar};
}

export constexpr uint2_t operator+(const uint_t scalar, const uint2_t b)
{
    return uint2_t{scalar + b.x, scalar + b.y};
}

export constexpr uint2_t operator+(const uint2_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    return uint2_t{a.x + scalar, a.y + scalar};
}

export constexpr uint2_t operator+(const int_t scalar, const uint2_t b)
{
    FND_ASSERT(scalar >= 0);

    return uint2_t{scalar + b.x, scalar + b.y};
}

export constexpr uint2_t operator-(const uint2_t a, const uint2_t b)
{
    return uint2_t{a.x - b.x, a.y - b.y};
}

export constexpr uint2_t operator-(const uint2_t a, const uint_t scalar)
{
    return uint2_t{a.x - scalar, a.y - scalar};
}

export constexpr uint2_t operator-(const uint_t scalar, const uint2_t b)
{
    return uint2_t{scalar - b.x, scalar - b.y};
}

export constexpr uint2_t operator-(const uint2_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    return uint2_t{a.x - scalar, a.y - scalar};
}

export constexpr uint2_t operator-(const int_t scalar, const uint2_t b)
{
    FND_ASSERT(scalar >= 0);

    return uint2_t{scalar - b.x, scalar - b.y};
}

export constexpr uint2_t operator%(const uint2_t a, const uint2_t b)
{
    FND_ASSERT(all(b != 0u));

    return uint2_t{a.x % b.x, a.y % b.y};
}

export constexpr uint2_t operator%(const uint2_t a, const uint_t scalar)
{
    FND_ASSERT(scalar != 0);

    return uint2_t{a.x % scalar, a.y % scalar};
}

export constexpr uint2_t operator%(const uint_t scalar, const uint2_t b)
{
    FND_ASSERT(all(b != 0u));

    return uint2_t{scalar % b.x, scalar % b.y};
}

export constexpr uint2_t operator%(const uint2_t a, const int_t scalar)
{
    FND_ASSERT(scalar > 0);

    return uint2_t{a.x % scalar, a.y % scalar};
}

export constexpr uint2_t operator%(const int_t scalar, const uint2_t b)
{
    FND_ASSERT(scalar >= 0);
    FND_ASSERT(all(b != 0u));

    return uint2_t{scalar % b.x, scalar % b.y};
}

export constexpr uint2_t operator/(const uint2_t a, const uint2_t b)
{
    FND_ASSERT(all(b != 0u));

    return uint2_t{a.x / b.x, a.y / b.y};
}

export constexpr uint2_t operator/(const uint2_t a, const uint_t scalar)
{
    FND_ASSERT(scalar != 0);

    return uint2_t{a.x / scalar, a.y / scalar};
}

export constexpr uint2_t operator/(const uint_t scalar, const uint2_t b)
{
    FND_ASSERT(all(b != 0u));

    return uint2_t{scalar / b.x, scalar / b.y};
}

export constexpr uint2_t operator/(const uint2_t a, const int_t scalar)
{
    FND_ASSERT(scalar > 0);

    return uint2_t{a.x / scalar, a.y / scalar};
}

export constexpr uint2_t operator/(const int_t scalar, const uint2_t b)
{
    FND_ASSERT(scalar >= 0);
    FND_ASSERT(all(b != 0u));

    return uint2_t{scalar / b.x, scalar / b.y};
}

export constexpr uint2_t operator<<(const uint2_t a, const uint2_t b)
{
    FND_ASSERT(all(b < 32u));

    return uint2_t{a.x << b.x, a.y << b.y};
}

export constexpr uint2_t operator<<(const uint2_t a, const uint_t scalar)
{
    FND_ASSERT(scalar < 32);

    return uint2_t{a.x << scalar, a.y << scalar};
}

export constexpr uint2_t operator<<(const uint_t scalar, const uint2_t b)
{
    FND_ASSERT(all(b < 32u));

    return uint2_t{scalar << b.x, scalar << b.y};
}

export constexpr uint2_t operator<<(const uint2_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0 && scalar < 32);

    return uint2_t{a.x << scalar, a.y << scalar};
}

export constexpr uint2_t operator<<(const int_t scalar, const uint2_t b)
{
    FND_ASSERT(scalar >= 0);
    FND_ASSERT(all(b < 32u));

    const uint_t uval = static_cast<uint_t>(scalar);
    return uint2_t{uval << b.x, uval << b.y};
}

export constexpr uint2_t operator>>(const uint2_t a, const uint2_t b)
{
    FND_ASSERT(all(b < 32u));

    return uint2_t{a.x >> b.x, a.y >> b.y};
}

export constexpr uint2_t operator>>(const uint2_t a, const uint_t scalar)
{
    FND_ASSERT(scalar < 32);

    return uint2_t{a.x >> scalar, a.y >> scalar};
}

export constexpr uint2_t operator>>(const uint_t scalar, const uint2_t b)
{
    FND_ASSERT(all(b < 32u));

    return uint2_t{scalar >> b.x, scalar >> b.y};
}

export constexpr uint2_t operator>>(const uint2_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0 && scalar < 32);

    return uint2_t{a.x >> scalar, a.y >> scalar};
}

export constexpr uint2_t operator>>(const int_t scalar, const uint2_t b)
{
    FND_ASSERT(scalar >= 0);
    FND_ASSERT(all(b < 32u));

    const uint_t uval = static_cast<uint_t>(scalar);
    return uint2_t{uval >> b.x, uval >> b.y};
}

export constexpr uint2_t operator^(const uint2_t a, const uint2_t b)
{
    return uint2_t{a.x ^ b.x, a.y ^ b.y};
}

export constexpr uint2_t operator^(const uint2_t a, const uint_t scalar)
{
    return uint2_t{a.x ^ scalar, a.y ^ scalar};
}

export constexpr uint2_t operator^(const uint_t scalar, const uint2_t b)
{
    return uint2_t{scalar ^ b.x, scalar ^ b.y};
}

export constexpr uint2_t operator^(const uint2_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    return uint2_t{a.x ^ scalar, a.y ^ scalar};
}

export constexpr uint2_t operator^(const int_t scalar, const uint2_t b)
{
    FND_ASSERT(scalar >= 0);

    return uint2_t{scalar ^ b.x, scalar ^ b.y};
}

export constexpr uint2_t operator|(const uint2_t a, const uint2_t b)
{
    return uint2_t{a.x | b.x, a.y | b.y};
}

export constexpr uint2_t operator|(const uint2_t a, const uint_t scalar)
{
    return uint2_t{a.x | scalar, a.y | scalar};
}

export constexpr uint2_t operator|(const uint_t scalar, const uint2_t b)
{
    return uint2_t{scalar | b.x, scalar | b.y};
}

export constexpr uint2_t operator|(const uint2_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    return uint2_t{a.x | scalar, a.y | scalar};
}

export constexpr uint2_t operator|(const int_t scalar, const uint2_t b)
{
    FND_ASSERT(scalar >= 0);

    return uint2_t{scalar | b.x, scalar | b.y};
}

export constexpr uint2_t clamp(
    const uint2_t v, const uint2_t lower, const uint2_t upper)
{
    FND_ASSERT(all(lower <= upper));

    return uint2_t{clamp(v.x, lower.x, upper.x), clamp(v.y, lower.y, upper.y)};
}

export constexpr uint2_t clamp(
    const uint2_t v, const uint2_t lower, const uint_t upper)
{
    FND_ASSERT(all(lower <= upper));

    return uint2_t{clamp(v.x, lower.x, upper), clamp(v.y, lower.y, upper)};
}

export constexpr uint2_t clamp(
    const uint2_t v, const uint_t lower, const uint2_t upper)
{
    FND_ASSERT(all(lower <= upper));

    return uint2_t{clamp(v.x, lower, upper.x), clamp(v.y, lower, upper.y)};
}

export constexpr uint2_t clamp(
    const uint2_t v, const uint_t lower, const uint_t upper)
{
    FND_ASSERT(lower <= upper);

    return uint2_t{clamp(v.x, lower, upper), clamp(v.y, lower, upper)};
}

export constexpr uint_t cmax(const uint2_t v)
{
    return max(v.x, v.y);
}

export constexpr uint_t cmin(const uint2_t v)
{
    return min(v.x, v.y);
}

export constexpr uint_t cmul(const uint2_t v)
{
    return v.x * v.y;
}

export constexpr uint_t csum(const uint2_t v)
{
    return v.x + v.y;
}

export constexpr uint2_t max(const uint2_t a, const uint2_t b)
{
    return uint2_t{max(a.x, b.x), max(a.y, b.y)};
}

export constexpr uint2_t max(const uint2_t a, const uint_t scalar)
{
    return uint2_t{max(a.x, scalar), max(a.y, scalar)};
}

export constexpr uint2_t max(const uint_t scalar, const uint2_t b)
{
    return uint2_t{max(scalar, b.x), max(scalar, b.y)};
}

export constexpr uint2_t min(const uint2_t a, const uint2_t b)
{
    return uint2_t{min(a.x, b.x), min(a.y, b.y)};
}

export constexpr uint2_t min(const uint2_t a, const uint_t scalar)
{
    return uint2_t{min(a.x, scalar), min(a.y, scalar)};
}

export constexpr uint2_t min(const uint_t scalar, const uint2_t b)
{
    return uint2_t{min(scalar, b.x), min(scalar, b.y)};
}

} // namespace fnd
