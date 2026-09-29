module;
#include "foundation/core/macros.h"

export module foundation.math:vector_uint3;
import foundation.core;
import :vector_bool;

namespace fnd {

export struct uint3_t final {
    static const uint3_t kZero;
    static const uint3_t kUnitX;
    static const uint3_t kUnitY;
    static const uint3_t kUnitZ;

    uint_t x{0};
    uint_t y{0};
    uint_t z{0};

    constexpr uint3_t() = default;

    constexpr explicit uint3_t(const uint_t scalar)
        : x{scalar}, y{scalar}, z{scalar}
    {
    }

    constexpr uint3_t(const uint_t x, const uint_t y, const uint_t z)
        : x{x}, y{y}, z{z}
    {
    }

    constexpr const uint_t& operator[](const uint_t idx) const
    {
        FND_ASSERT(idx < 3);
        return idx == 0 ? x : (idx == 1 ? y : z);
    }

    constexpr uint_t& operator[](const uint_t idx)
    {
        return const_cast<uint_t&>(static_cast<const uint3_t&>(*this)[idx]);
    }

    constexpr uint3_t& operator++()
    {
        ++x;
        ++y;
        ++z;
        return *this;
    }

    constexpr uint3_t operator++(int) { return uint3_t{x++, y++, z++}; }

    constexpr uint3_t& operator--()
    {
        --x;
        --y;
        --z;
        return *this;
    }

    constexpr uint3_t operator--(int) { return uint3_t{x--, y--, z--}; }

    constexpr uint3_t operator~() const { return uint3_t{~x, ~y, ~z}; }

    constexpr uint3_t& operator+=(const uint3_t b)
    {
        x += b.x;
        y += b.y;
        z += b.z;
        return *this;
    }

    constexpr uint3_t& operator+=(const uint_t scalar)
    {
        x += scalar;
        y += scalar;
        z += scalar;
        return *this;
    }

    constexpr uint3_t& operator+=(const int_t scalar)
    {
        FND_ASSERT(scalar >= 0);

        x += scalar;
        y += scalar;
        z += scalar;
        return *this;
    }

    constexpr uint3_t& operator-=(const uint3_t b)
    {
        x -= b.x;
        y -= b.y;
        z -= b.z;
        return *this;
    }

    constexpr uint3_t& operator-=(const uint_t scalar)
    {
        x -= scalar;
        y -= scalar;
        z -= scalar;
        return *this;
    }

    constexpr uint3_t& operator-=(const int_t scalar)
    {
        FND_ASSERT(scalar >= 0);

        x -= scalar;
        y -= scalar;
        z -= scalar;
        return *this;
    }

    constexpr uint3_t& operator*=(const uint3_t b)
    {
        x *= b.x;
        y *= b.y;
        z *= b.z;
        return *this;
    }

    constexpr uint3_t& operator*=(const uint_t scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    constexpr uint3_t& operator*=(const int_t scalar)
    {
        FND_ASSERT(scalar >= 0);

        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    constexpr uint3_t& operator/=(const uint3_t b)
    {
        FND_ASSERT(b.x != 0 && b.y != 0 && b.z != 0);

        x /= b.x;
        y /= b.y;
        z /= b.z;
        return *this;
    }

    constexpr uint3_t& operator/=(const uint_t scalar)
    {
        FND_ASSERT(scalar != 0);

        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    constexpr uint3_t& operator/=(const int_t scalar)
    {
        FND_ASSERT(scalar > 0);

        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    constexpr uint3_t& operator%=(const uint3_t b)
    {
        FND_ASSERT(b.x != 0 && b.y != 0 && b.z != 0);

        x %= b.x;
        y %= b.y;
        z %= b.z;
        return *this;
    }

    constexpr uint3_t& operator%=(const uint_t scalar)
    {
        FND_ASSERT(scalar != 0);

        x %= scalar;
        y %= scalar;
        z %= scalar;
        return *this;
    }

    constexpr uint3_t& operator%=(const int_t scalar)
    {
        FND_ASSERT(scalar > 0);

        x %= scalar;
        y %= scalar;
        z %= scalar;
        return *this;
    }

    constexpr uint3_t& operator&=(const uint3_t b)
    {
        x &= b.x;
        y &= b.y;
        z &= b.z;
        return *this;
    }

    constexpr uint3_t& operator&=(const uint_t scalar)
    {
        x &= scalar;
        y &= scalar;
        z &= scalar;
        return *this;
    }

    constexpr uint3_t& operator&=(const int_t scalar)
    {
        FND_ASSERT(scalar >= 0);

        x &= scalar;
        y &= scalar;
        z &= scalar;
        return *this;
    }

    constexpr uint3_t& operator|=(const uint3_t b)
    {
        x |= b.x;
        y |= b.y;
        z |= b.z;
        return *this;
    }

    constexpr uint3_t& operator|=(const uint_t scalar)
    {
        x |= scalar;
        y |= scalar;
        z |= scalar;
        return *this;
    }

    constexpr uint3_t& operator|=(const int_t scalar)
    {
        FND_ASSERT(scalar >= 0);

        x |= scalar;
        y |= scalar;
        z |= scalar;
        return *this;
    }

    constexpr uint3_t& operator^=(const uint3_t b)
    {
        x ^= b.x;
        y ^= b.y;
        z ^= b.z;
        return *this;
    }

    constexpr uint3_t& operator^=(const uint_t scalar)
    {
        x ^= scalar;
        y ^= scalar;
        z ^= scalar;
        return *this;
    }

    constexpr uint3_t& operator^=(const int_t scalar)
    {
        FND_ASSERT(scalar >= 0);

        x ^= scalar;
        y ^= scalar;
        z ^= scalar;
        return *this;
    }

    constexpr uint3_t& operator<<=(const uint3_t b)
    {
        FND_ASSERT(b.x < 32);
        FND_ASSERT(b.y < 32);
        FND_ASSERT(b.z < 32);

        x <<= b.x;
        y <<= b.y;
        z <<= b.z;
        return *this;
    }

    constexpr uint3_t& operator<<=(const uint_t scalar)
    {
        FND_ASSERT(scalar < 32);

        x <<= scalar;
        y <<= scalar;
        z <<= scalar;
        return *this;
    }

    constexpr uint3_t& operator<<=(const int_t scalar)
    {
        FND_ASSERT(scalar >= 0 && scalar < 32);

        x <<= scalar;
        y <<= scalar;
        z <<= scalar;
        return *this;
    }

    constexpr uint3_t& operator>>=(const uint3_t b)
    {
        FND_ASSERT(b.x < 32);
        FND_ASSERT(b.y < 32);
        FND_ASSERT(b.z < 32);

        x >>= b.x;
        y >>= b.y;
        z >>= b.z;
        return *this;
    }

    constexpr uint3_t& operator>>=(const uint_t scalar)
    {
        FND_ASSERT(scalar < 32);

        x >>= scalar;
        y >>= scalar;
        z >>= scalar;
        return *this;
    }

    constexpr uint3_t& operator>>=(const int_t scalar)
    {
        FND_ASSERT(scalar >= 0 && scalar < 32);

        x >>= scalar;
        y >>= scalar;
        z >>= scalar;
        return *this;
    }
};

constexpr uint3_t uint3_t::kZero{0, 0, 0};
constexpr uint3_t uint3_t::kUnitX{1, 0, 0};
constexpr uint3_t uint3_t::kUnitY{0, 1, 0};
constexpr uint3_t uint3_t::kUnitZ{0, 0, 1};

export constexpr bool3_t operator==(const uint3_t a, const uint3_t b)
{
    return bool3_t{a.x == b.x, a.y == b.y, a.z == b.z};
}

export constexpr bool3_t operator==(const uint3_t a, const uint_t scalar)
{
    return bool3_t{a.x == scalar, a.y == scalar, a.z == scalar};
}

export constexpr bool3_t operator==(const uint_t scalar, const uint3_t b)
{
    return bool3_t{scalar == b.x, scalar == b.y, scalar == b.z};
}

export constexpr bool3_t operator==(const uint3_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    const uint_t uval = static_cast<uint_t>(scalar);
    return bool3_t{a.x == uval, a.y == uval, a.z == uval};
}

export constexpr bool3_t operator==(const int_t scalar, const uint3_t b)
{
    FND_ASSERT(scalar >= 0);

    const uint_t uval = static_cast<uint_t>(scalar);
    return bool3_t{uval == b.x, uval == b.y, uval == b.z};
}

export constexpr bool3_t operator!=(const uint3_t a, const uint3_t b)
{
    return !(a == b);
}

export constexpr bool3_t operator!=(const uint3_t a, const uint_t scalar)
{
    return !(a == scalar);
}

export constexpr bool3_t operator!=(const uint_t scalar, const uint3_t b)
{
    return !(scalar == b);
}

export constexpr bool3_t operator!=(const uint3_t a, const int_t scalar)
{
    return !(a == scalar);
}

export constexpr bool3_t operator!=(const int_t scalar, const uint3_t b)
{
    return !(scalar == b);
}

export constexpr bool3_t operator<(const uint3_t a, const uint3_t b)
{
    return bool3_t{a.x < b.x, a.y < b.y, a.z < b.z};
}

export constexpr bool3_t operator<(const uint3_t a, const uint_t scalar)
{
    return bool3_t{a.x < scalar, a.y < scalar, a.z < scalar};
}

export constexpr bool3_t operator<(const uint_t scalar, const uint3_t b)
{
    return bool3_t{scalar < b.x, scalar < b.y, scalar < b.z};
}

export constexpr bool3_t operator<(const uint3_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    const uint_t uval = static_cast<uint_t>(scalar);
    return bool3_t{a.x < uval, a.y < uval, a.z < uval};
}

export constexpr bool3_t operator<(const int_t scalar, const uint3_t b)
{
    FND_ASSERT(scalar >= 0);

    const uint_t uval = static_cast<uint_t>(scalar);
    return bool3_t{uval < b.x, uval < b.y, uval < b.z};
}

export constexpr bool3_t operator<=(const uint3_t a, const uint3_t b)
{
    return bool3_t{a.x <= b.x, a.y <= b.y, a.z <= b.z};
}

export constexpr bool3_t operator<=(const uint3_t a, const uint_t scalar)
{
    return bool3_t{a.x <= scalar, a.y <= scalar, a.z <= scalar};
}

export constexpr bool3_t operator<=(const uint_t scalar, const uint3_t b)
{
    return bool3_t{scalar <= b.x, scalar <= b.y, scalar <= b.z};
}

export constexpr bool3_t operator<=(const uint3_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    const uint_t uval = static_cast<uint_t>(scalar);
    return bool3_t{a.x <= uval, a.y <= uval, a.z <= uval};
}

export constexpr bool3_t operator<=(const int_t scalar, const uint3_t b)
{
    FND_ASSERT(scalar >= 0);

    const uint_t uval = static_cast<uint_t>(scalar);
    return bool3_t{uval <= b.x, uval <= b.y, uval <= b.z};
}

export constexpr bool3_t operator>(const uint3_t a, const uint3_t b)
{
    return bool3_t{a.x > b.x, a.y > b.y, a.z > b.z};
}

export constexpr bool3_t operator>(const uint3_t a, const uint_t scalar)
{
    return bool3_t{a.x > scalar, a.y > scalar, a.z > scalar};
}

export constexpr bool3_t operator>(const uint_t scalar, const uint3_t b)
{
    return bool3_t{scalar > b.x, scalar > b.y, scalar > b.z};
}

export constexpr bool3_t operator>(const uint3_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    const uint_t uval = static_cast<uint_t>(scalar);
    return bool3_t{a.x > uval, a.y > uval, a.z > uval};
}

export constexpr bool3_t operator>(const int_t scalar, const uint3_t b)
{
    FND_ASSERT(scalar >= 0);

    const uint_t uval = static_cast<uint_t>(scalar);
    return bool3_t{uval > b.x, uval > b.y, uval > b.z};
}

export constexpr bool3_t operator>=(const uint3_t a, const uint3_t b)
{
    return bool3_t{a.x >= b.x, a.y >= b.y, a.z >= b.z};
}

export constexpr bool3_t operator>=(const uint3_t a, const uint_t scalar)
{
    return bool3_t{a.x >= scalar, a.y >= scalar, a.z >= scalar};
}

export constexpr bool3_t operator>=(const uint_t scalar, const uint3_t b)
{
    return bool3_t{scalar >= b.x, scalar >= b.y, scalar >= b.z};
}

export constexpr bool3_t operator>=(const uint3_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    const uint_t uval = static_cast<uint_t>(scalar);
    return bool3_t{a.x >= uval, a.y >= uval, a.z >= uval};
}

export constexpr bool3_t operator>=(const int_t scalar, const uint3_t b)
{
    FND_ASSERT(scalar >= 0);

    const uint_t uval = static_cast<uint_t>(scalar);
    return bool3_t{uval >= b.x, uval >= b.y, uval >= b.z};
}

export constexpr uint3_t operator&(const uint3_t a, const uint3_t b)
{
    return uint3_t{a.x & b.x, a.y & b.y, a.z & b.z};
}

export constexpr uint3_t operator&(const uint3_t a, const uint_t scalar)
{
    return uint3_t{a.x & scalar, a.y & scalar, a.z & scalar};
}

export constexpr uint3_t operator&(const uint_t scalar, const uint3_t b)
{
    return uint3_t{scalar & b.x, scalar & b.y, scalar & b.z};
}

export constexpr uint3_t operator&(const uint3_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    return uint3_t{a.x & scalar, a.y & scalar, a.z & scalar};
}

export constexpr uint3_t operator&(const int_t scalar, const uint3_t b)
{
    FND_ASSERT(scalar >= 0);

    return uint3_t{scalar & b.x, scalar & b.y, scalar & b.z};
}

export constexpr uint3_t operator*(const uint3_t a, const uint3_t b)
{
    return uint3_t{a.x * b.x, a.y * b.y, a.z * b.z};
}

export constexpr uint3_t operator*(const uint3_t a, const uint_t scalar)
{
    return uint3_t{a.x * scalar, a.y * scalar, a.z * scalar};
}

export constexpr uint3_t operator*(const uint_t scalar, const uint3_t b)
{
    return uint3_t{scalar * b.x, scalar * b.y, scalar * b.z};
}

export constexpr uint3_t operator*(const uint3_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    return uint3_t{a.x * scalar, a.y * scalar, a.z * scalar};
}

export constexpr uint3_t operator*(const int_t scalar, const uint3_t b)
{
    FND_ASSERT(scalar >= 0);

    return uint3_t{scalar * b.x, scalar * b.y, scalar * b.z};
}

export constexpr uint3_t operator+(const uint3_t a, const uint3_t b)
{
    return uint3_t{a.x + b.x, a.y + b.y, a.z + b.z};
}

export constexpr uint3_t operator+(const uint3_t a, const uint_t scalar)
{
    return uint3_t{a.x + scalar, a.y + scalar, a.z + scalar};
}

export constexpr uint3_t operator+(const uint_t scalar, const uint3_t b)
{
    return uint3_t{scalar + b.x, scalar + b.y, scalar + b.z};
}

export constexpr uint3_t operator+(const uint3_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    return uint3_t{a.x + scalar, a.y + scalar, a.z + scalar};
}

export constexpr uint3_t operator+(const int_t scalar, const uint3_t b)
{
    FND_ASSERT(scalar >= 0);

    return uint3_t{scalar + b.x, scalar + b.y, scalar + b.z};
}

export constexpr uint3_t operator-(const uint3_t a, const uint3_t b)
{
    return uint3_t{a.x - b.x, a.y - b.y, a.z - b.z};
}

export constexpr uint3_t operator-(const uint3_t a, const uint_t scalar)
{
    return uint3_t{a.x - scalar, a.y - scalar, a.z - scalar};
}

export constexpr uint3_t operator-(const uint_t scalar, const uint3_t b)
{
    return uint3_t{scalar - b.x, scalar - b.y, scalar - b.z};
}

export constexpr uint3_t operator-(const uint3_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    return uint3_t{a.x - scalar, a.y - scalar, a.z - scalar};
}

export constexpr uint3_t operator-(const int_t scalar, const uint3_t b)
{
    FND_ASSERT(scalar >= 0);

    return uint3_t{scalar - b.x, scalar - b.y, scalar - b.z};
}

export constexpr uint3_t operator%(const uint3_t a, const uint3_t b)
{
    FND_ASSERT(all(b != 0u));

    return uint3_t{a.x % b.x, a.y % b.y, a.z % b.z};
}

export constexpr uint3_t operator%(const uint3_t a, const uint_t scalar)
{
    FND_ASSERT(scalar != 0);

    return uint3_t{a.x % scalar, a.y % scalar, a.z % scalar};
}

export constexpr uint3_t operator%(const uint_t scalar, const uint3_t b)
{
    FND_ASSERT(all(b != 0u));

    return uint3_t{scalar % b.x, scalar % b.y, scalar % b.z};
}

export constexpr uint3_t operator%(const uint3_t a, const int_t scalar)
{
    FND_ASSERT(scalar > 0);

    return uint3_t{a.x % scalar, a.y % scalar, a.z % scalar};
}

export constexpr uint3_t operator%(const int_t scalar, const uint3_t b)
{
    FND_ASSERT(scalar >= 0);
    FND_ASSERT(all(b != 0u));

    return uint3_t{scalar % b.x, scalar % b.y, scalar % b.z};
}

export constexpr uint3_t operator/(const uint3_t a, const uint3_t b)
{
    FND_ASSERT(all(b != 0u));

    return uint3_t{a.x / b.x, a.y / b.y, a.z / b.z};
}

export constexpr uint3_t operator/(const uint3_t a, const uint_t scalar)
{
    FND_ASSERT(scalar != 0);

    return uint3_t{a.x / scalar, a.y / scalar, a.z / scalar};
}

export constexpr uint3_t operator/(const uint_t scalar, const uint3_t b)
{
    FND_ASSERT(all(b != 0u));

    return uint3_t{scalar / b.x, scalar / b.y, scalar / b.z};
}

export constexpr uint3_t operator/(const uint3_t a, const int_t scalar)
{
    FND_ASSERT(scalar > 0);

    return uint3_t{a.x / scalar, a.y / scalar, a.z / scalar};
}

export constexpr uint3_t operator/(const int_t scalar, const uint3_t b)
{
    FND_ASSERT(scalar >= 0);
    FND_ASSERT(all(b != 0u));

    return uint3_t{scalar / b.x, scalar / b.y, scalar / b.z};
}

export constexpr uint3_t operator<<(const uint3_t a, const uint3_t b)
{
    FND_ASSERT(all(b < 32u));

    return uint3_t{a.x << b.x, a.y << b.y, a.z << b.z};
}

export constexpr uint3_t operator<<(const uint3_t a, const uint_t scalar)
{
    FND_ASSERT(scalar < 32);

    return uint3_t{a.x << scalar, a.y << scalar, a.z << scalar};
}

export constexpr uint3_t operator<<(const uint_t scalar, const uint3_t b)
{
    FND_ASSERT(all(b < 32u));

    return uint3_t{scalar << b.x, scalar << b.y, scalar << b.z};
}

export constexpr uint3_t operator<<(const uint3_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0 && scalar < 32);

    return uint3_t{a.x << scalar, a.y << scalar, a.z << scalar};
}

export constexpr uint3_t operator<<(const int_t scalar, const uint3_t b)
{
    FND_ASSERT(scalar >= 0);
    FND_ASSERT(all(b < 32u));

    const uint_t uval = static_cast<uint_t>(scalar);
    return uint3_t{uval << b.x, uval << b.y, uval << b.z};
}

export constexpr uint3_t operator>>(const uint3_t a, const uint3_t b)
{
    FND_ASSERT(all(b < 32u));

    return uint3_t{a.x >> b.x, a.y >> b.y, a.z >> b.z};
}

export constexpr uint3_t operator>>(const uint3_t a, const uint_t scalar)
{
    FND_ASSERT(scalar < 32);

    return uint3_t{a.x >> scalar, a.y >> scalar, a.z >> scalar};
}

export constexpr uint3_t operator>>(const uint_t scalar, const uint3_t b)
{
    FND_ASSERT(all(b < 32u));

    return uint3_t{scalar >> b.x, scalar >> b.y, scalar >> b.z};
}

export constexpr uint3_t operator>>(const uint3_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0 && scalar < 32);

    return uint3_t{a.x >> scalar, a.y >> scalar, a.z >> scalar};
}

export constexpr uint3_t operator>>(const int_t scalar, const uint3_t b)
{
    FND_ASSERT(scalar >= 0);
    FND_ASSERT(all(b < 32u));

    const uint_t uval = static_cast<uint_t>(scalar);
    return uint3_t{uval >> b.x, uval >> b.y, uval >> b.z};
}

export constexpr uint3_t operator^(const uint3_t a, const uint3_t b)
{
    return uint3_t{a.x ^ b.x, a.y ^ b.y, a.z ^ b.z};
}

export constexpr uint3_t operator^(const uint3_t a, const uint_t scalar)
{
    return uint3_t{a.x ^ scalar, a.y ^ scalar, a.z ^ scalar};
}

export constexpr uint3_t operator^(const uint_t scalar, const uint3_t b)
{
    return uint3_t{scalar ^ b.x, scalar ^ b.y, scalar ^ b.z};
}

export constexpr uint3_t operator^(const uint3_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    return uint3_t{a.x ^ scalar, a.y ^ scalar, a.z ^ scalar};
}

export constexpr uint3_t operator^(const int_t scalar, const uint3_t b)
{
    FND_ASSERT(scalar >= 0);

    return uint3_t{scalar ^ b.x, scalar ^ b.y, scalar ^ b.z};
}

export constexpr uint3_t operator|(const uint3_t a, const uint3_t b)
{
    return uint3_t{a.x | b.x, a.y | b.y, a.z | b.z};
}

export constexpr uint3_t operator|(const uint3_t a, const uint_t scalar)
{
    return uint3_t{a.x | scalar, a.y | scalar, a.z | scalar};
}

export constexpr uint3_t operator|(const uint_t scalar, const uint3_t b)
{
    return uint3_t{scalar | b.x, scalar | b.y, scalar | b.z};
}

export constexpr uint3_t operator|(const uint3_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    return uint3_t{a.x | scalar, a.y | scalar, a.z | scalar};
}

export constexpr uint3_t operator|(const int_t scalar, const uint3_t b)
{
    FND_ASSERT(scalar >= 0);

    return uint3_t{scalar | b.x, scalar | b.y, scalar | b.z};
}

export constexpr uint3_t clamp(
    const uint3_t v, const uint3_t lower, const uint3_t upper)
{
    FND_ASSERT(all(lower <= upper));

    return uint3_t{clamp(v.x, lower.x, upper.x), clamp(v.y, lower.y, upper.y),
        clamp(v.z, lower.z, upper.z)};
}

export constexpr uint3_t clamp(
    const uint3_t v, const uint3_t lower, const uint_t upper)
{
    FND_ASSERT(all(lower <= upper));

    return uint3_t{clamp(v.x, lower.x, upper), clamp(v.y, lower.y, upper),
        clamp(v.z, lower.z, upper)};
}

export constexpr uint3_t clamp(
    const uint3_t v, const uint_t lower, const uint3_t upper)
{
    FND_ASSERT(all(lower <= upper));

    return uint3_t{clamp(v.x, lower, upper.x), clamp(v.y, lower, upper.y),
        clamp(v.z, lower, upper.z)};
}

export constexpr uint3_t clamp(
    const uint3_t v, const uint_t lower, const uint_t upper)
{
    FND_ASSERT(lower <= upper);

    return uint3_t{clamp(v.x, lower, upper), clamp(v.y, lower, upper),
        clamp(v.z, lower, upper)};
}

export constexpr uint_t cmax(const uint3_t v)
{
    return max(max(v.x, v.y), v.z);
}

export constexpr uint_t cmin(const uint3_t v)
{
    return min(min(v.x, v.y), v.z);
}

export constexpr uint_t cmul(const uint3_t v)
{
    return v.x * v.y * v.z;
}

export constexpr uint_t csum(const uint3_t v)
{
    return v.x + v.y + v.z;
}

export constexpr uint3_t max(const uint3_t a, const uint3_t b)
{
    return uint3_t{max(a.x, b.x), max(a.y, b.y), max(a.z, b.z)};
}

export constexpr uint3_t max(const uint3_t a, const uint_t scalar)
{
    return uint3_t{max(a.x, scalar), max(a.y, scalar), max(a.z, scalar)};
}

export constexpr uint3_t max(const uint_t scalar, const uint3_t b)
{
    return uint3_t{max(scalar, b.x), max(scalar, b.y), max(scalar, b.z)};
}

export constexpr uint3_t min(const uint3_t a, const uint3_t b)
{
    return uint3_t{min(a.x, b.x), min(a.y, b.y), min(a.z, b.z)};
}

export constexpr uint3_t min(const uint3_t a, const uint_t scalar)
{
    return uint3_t{min(a.x, scalar), min(a.y, scalar), min(a.z, scalar)};
}

export constexpr uint3_t min(const uint_t scalar, const uint3_t b)
{
    return uint3_t{min(scalar, b.x), min(scalar, b.y), min(scalar, b.z)};
}

} // namespace fnd
