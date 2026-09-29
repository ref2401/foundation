module;
#include "foundation/core/macros.h"

export module foundation.math:vector_uint4;
import foundation.core;
import :vector_bool;

namespace fnd {

export struct uint4_t final {
    static const uint4_t kZero;
    static const uint4_t kUnitX;
    static const uint4_t kUnitY;
    static const uint4_t kUnitZ;
    static const uint4_t kUnitW;

    uint_t x{0};
    uint_t y{0};
    uint_t z{0};
    uint_t w{0};

    constexpr uint4_t() = default;

    constexpr explicit uint4_t(const uint_t scalar)
        : x{scalar}, y{scalar}, z{scalar}, w{scalar}
    {
    }

    constexpr uint4_t(
        const uint_t x, const uint_t y, const uint_t z, const uint_t w)
        : x{x}, y{y}, z{z}, w{w}
    {
    }

    constexpr const uint_t& operator[](const uint_t idx) const
    {
        FND_ASSERT(idx < 4);
        return idx == 0 ? x : (idx == 1 ? y : (idx == 2 ? z : w));
    }

    constexpr uint_t& operator[](const uint_t idx)
    {
        return const_cast<uint_t&>(static_cast<const uint4_t&>(*this)[idx]);
    }

    constexpr uint4_t& operator++()
    {
        ++x;
        ++y;
        ++z;
        ++w;
        return *this;
    }

    constexpr uint4_t operator++(int) { return uint4_t{x++, y++, z++, w++}; }

    constexpr uint4_t& operator--()
    {
        --x;
        --y;
        --z;
        --w;
        return *this;
    }

    constexpr uint4_t operator--(int) { return uint4_t{x--, y--, z--, w--}; }

    constexpr uint4_t operator~() const { return uint4_t{~x, ~y, ~z, ~w}; }

    constexpr uint4_t& operator+=(const uint4_t b)
    {
        x += b.x;
        y += b.y;
        z += b.z;
        w += b.w;
        return *this;
    }

    constexpr uint4_t& operator+=(const uint_t scalar)
    {
        x += scalar;
        y += scalar;
        z += scalar;
        w += scalar;
        return *this;
    }

    constexpr uint4_t& operator+=(const int_t scalar)
    {
        FND_ASSERT(scalar >= 0);

        x += scalar;
        y += scalar;
        z += scalar;
        w += scalar;
        return *this;
    }

    constexpr uint4_t& operator-=(const uint4_t b)
    {
        x -= b.x;
        y -= b.y;
        z -= b.z;
        w -= b.w;
        return *this;
    }

    constexpr uint4_t& operator-=(const uint_t scalar)
    {
        x -= scalar;
        y -= scalar;
        z -= scalar;
        w -= scalar;
        return *this;
    }

    constexpr uint4_t& operator-=(const int_t scalar)
    {
        FND_ASSERT(scalar >= 0);

        x -= scalar;
        y -= scalar;
        z -= scalar;
        w -= scalar;
        return *this;
    }

    constexpr uint4_t& operator*=(const uint4_t b)
    {
        x *= b.x;
        y *= b.y;
        z *= b.z;
        w *= b.w;
        return *this;
    }

    constexpr uint4_t& operator*=(const uint_t scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
        return *this;
    }

    constexpr uint4_t& operator*=(const int_t scalar)
    {
        FND_ASSERT(scalar >= 0);

        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
        return *this;
    }

    constexpr uint4_t& operator/=(const uint4_t b)
    {
        FND_ASSERT(b.x != 0 && b.y != 0 && b.z != 0 && b.w != 0);

        x /= b.x;
        y /= b.y;
        z /= b.z;
        w /= b.w;
        return *this;
    }

    constexpr uint4_t& operator/=(const uint_t scalar)
    {
        FND_ASSERT(scalar != 0);

        x /= scalar;
        y /= scalar;
        z /= scalar;
        w /= scalar;
        return *this;
    }

    constexpr uint4_t& operator/=(const int_t scalar)
    {
        FND_ASSERT(scalar > 0);

        x /= scalar;
        y /= scalar;
        z /= scalar;
        w /= scalar;
        return *this;
    }

    constexpr uint4_t& operator%=(const uint4_t b)
    {
        FND_ASSERT(b.x != 0 && b.y != 0 && b.z != 0 && b.w != 0);

        x %= b.x;
        y %= b.y;
        z %= b.z;
        w %= b.w;
        return *this;
    }

    constexpr uint4_t& operator%=(const uint_t scalar)
    {
        FND_ASSERT(scalar != 0);

        x %= scalar;
        y %= scalar;
        z %= scalar;
        w %= scalar;
        return *this;
    }

    constexpr uint4_t& operator%=(const int_t scalar)
    {
        FND_ASSERT(scalar > 0);

        x %= scalar;
        y %= scalar;
        z %= scalar;
        w %= scalar;
        return *this;
    }

    constexpr uint4_t& operator&=(const uint4_t b)
    {
        x &= b.x;
        y &= b.y;
        z &= b.z;
        w &= b.w;
        return *this;
    }

    constexpr uint4_t& operator&=(const uint_t scalar)
    {
        x &= scalar;
        y &= scalar;
        z &= scalar;
        w &= scalar;
        return *this;
    }

    constexpr uint4_t& operator&=(const int_t scalar)
    {
        FND_ASSERT(scalar >= 0);

        x &= scalar;
        y &= scalar;
        z &= scalar;
        w &= scalar;
        return *this;
    }

    constexpr uint4_t& operator|=(const uint4_t b)
    {
        x |= b.x;
        y |= b.y;
        z |= b.z;
        w |= b.w;
        return *this;
    }

    constexpr uint4_t& operator|=(const uint_t scalar)
    {
        x |= scalar;
        y |= scalar;
        z |= scalar;
        w |= scalar;
        return *this;
    }

    constexpr uint4_t& operator|=(const int_t scalar)
    {
        FND_ASSERT(scalar >= 0);

        x |= scalar;
        y |= scalar;
        z |= scalar;
        w |= scalar;
        return *this;
    }

    constexpr uint4_t& operator^=(const uint4_t b)
    {
        x ^= b.x;
        y ^= b.y;
        z ^= b.z;
        w ^= b.w;
        return *this;
    }

    constexpr uint4_t& operator^=(const uint_t scalar)
    {
        x ^= scalar;
        y ^= scalar;
        z ^= scalar;
        w ^= scalar;
        return *this;
    }

    constexpr uint4_t& operator^=(const int_t scalar)
    {
        FND_ASSERT(scalar >= 0);

        x ^= scalar;
        y ^= scalar;
        z ^= scalar;
        w ^= scalar;
        return *this;
    }

    constexpr uint4_t& operator<<=(const uint4_t b)
    {
        FND_ASSERT(b.x < 32);
        FND_ASSERT(b.y < 32);
        FND_ASSERT(b.z < 32);
        FND_ASSERT(b.w < 32);

        x <<= b.x;
        y <<= b.y;
        z <<= b.z;
        w <<= b.w;
        return *this;
    }

    constexpr uint4_t& operator<<=(const uint_t scalar)
    {
        FND_ASSERT(scalar < 32);

        x <<= scalar;
        y <<= scalar;
        z <<= scalar;
        w <<= scalar;
        return *this;
    }

    constexpr uint4_t& operator<<=(const int_t scalar)
    {
        FND_ASSERT(scalar >= 0 && scalar < 32);

        x <<= scalar;
        y <<= scalar;
        z <<= scalar;
        w <<= scalar;
        return *this;
    }

    constexpr uint4_t& operator>>=(const uint4_t b)
    {
        FND_ASSERT(b.x < 32);
        FND_ASSERT(b.y < 32);
        FND_ASSERT(b.z < 32);
        FND_ASSERT(b.w < 32);

        x >>= b.x;
        y >>= b.y;
        z >>= b.z;
        w >>= b.w;
        return *this;
    }

    constexpr uint4_t& operator>>=(const uint_t scalar)
    {
        FND_ASSERT(scalar < 32);

        x >>= scalar;
        y >>= scalar;
        z >>= scalar;
        w >>= scalar;
        return *this;
    }

    constexpr uint4_t& operator>>=(const int_t scalar)
    {
        FND_ASSERT(scalar >= 0 && scalar < 32);

        x >>= scalar;
        y >>= scalar;
        z >>= scalar;
        w >>= scalar;
        return *this;
    }
};

constexpr uint4_t uint4_t::kZero{0, 0, 0, 0};
constexpr uint4_t uint4_t::kUnitX{1, 0, 0, 0};
constexpr uint4_t uint4_t::kUnitY{0, 1, 0, 0};
constexpr uint4_t uint4_t::kUnitZ{0, 0, 1, 0};
constexpr uint4_t uint4_t::kUnitW{0, 0, 0, 1};

export constexpr bool4_t operator==(const uint4_t a, const uint4_t b)
{
    return bool4_t{a.x == b.x, a.y == b.y, a.z == b.z, a.w == b.w};
}

export constexpr bool4_t operator==(const uint4_t a, const uint_t scalar)
{
    return bool4_t{a.x == scalar, a.y == scalar, a.z == scalar, a.w == scalar};
}

export constexpr bool4_t operator==(const uint_t scalar, const uint4_t b)
{
    return bool4_t{scalar == b.x, scalar == b.y, scalar == b.z, scalar == b.w};
}

export constexpr bool4_t operator==(const uint4_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    const uint_t uval = static_cast<uint_t>(scalar);
    return bool4_t{a.x == uval, a.y == uval, a.z == uval, a.w == uval};
}

export constexpr bool4_t operator==(const int_t scalar, const uint4_t b)
{
    FND_ASSERT(scalar >= 0);

    const uint_t uval = static_cast<uint_t>(scalar);
    return bool4_t{uval == b.x, uval == b.y, uval == b.z, uval == b.w};
}

export constexpr bool4_t operator!=(const uint4_t a, const uint4_t b)
{
    return !(a == b);
}

export constexpr bool4_t operator!=(const uint4_t a, const uint_t scalar)
{
    return !(a == scalar);
}

export constexpr bool4_t operator!=(const uint_t scalar, const uint4_t b)
{
    return !(scalar == b);
}

export constexpr bool4_t operator!=(const uint4_t a, const int_t scalar)
{
    return !(a == scalar);
}

export constexpr bool4_t operator!=(const int_t scalar, const uint4_t b)
{
    return !(scalar == b);
}

export constexpr bool4_t operator<(const uint4_t a, const uint4_t b)
{
    return bool4_t{a.x < b.x, a.y < b.y, a.z < b.z, a.w < b.w};
}

export constexpr bool4_t operator<(const uint4_t a, const uint_t scalar)
{
    return bool4_t{a.x < scalar, a.y < scalar, a.z < scalar, a.w < scalar};
}

export constexpr bool4_t operator<(const uint_t scalar, const uint4_t b)
{
    return bool4_t{scalar < b.x, scalar < b.y, scalar < b.z, scalar < b.w};
}

export constexpr bool4_t operator<(const uint4_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    const uint_t uval = static_cast<uint_t>(scalar);
    return bool4_t{a.x < uval, a.y < uval, a.z < uval, a.w < uval};
}

export constexpr bool4_t operator<(const int_t scalar, const uint4_t b)
{
    FND_ASSERT(scalar >= 0);

    const uint_t uval = static_cast<uint_t>(scalar);
    return bool4_t{uval < b.x, uval < b.y, uval < b.z, uval < b.w};
}

export constexpr bool4_t operator<=(const uint4_t a, const uint4_t b)
{
    return bool4_t{a.x <= b.x, a.y <= b.y, a.z <= b.z, a.w <= b.w};
}

export constexpr bool4_t operator<=(const uint4_t a, const uint_t scalar)
{
    return bool4_t{a.x <= scalar, a.y <= scalar, a.z <= scalar, a.w <= scalar};
}

export constexpr bool4_t operator<=(const uint_t scalar, const uint4_t b)
{
    return bool4_t{scalar <= b.x, scalar <= b.y, scalar <= b.z, scalar <= b.w};
}

export constexpr bool4_t operator<=(const uint4_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    const uint_t uval = static_cast<uint_t>(scalar);
    return bool4_t{a.x <= uval, a.y <= uval, a.z <= uval, a.w <= uval};
}

export constexpr bool4_t operator<=(const int_t scalar, const uint4_t b)
{
    FND_ASSERT(scalar >= 0);

    const uint_t uval = static_cast<uint_t>(scalar);
    return bool4_t{uval <= b.x, uval <= b.y, uval <= b.z, uval <= b.w};
}

export constexpr bool4_t operator>(const uint4_t a, const uint4_t b)
{
    return bool4_t{a.x > b.x, a.y > b.y, a.z > b.z, a.w > b.w};
}

export constexpr bool4_t operator>(const uint4_t a, const uint_t scalar)
{
    return bool4_t{a.x > scalar, a.y > scalar, a.z > scalar, a.w > scalar};
}

export constexpr bool4_t operator>(const uint_t scalar, const uint4_t b)
{
    return bool4_t{scalar > b.x, scalar > b.y, scalar > b.z, scalar > b.w};
}

export constexpr bool4_t operator>(const uint4_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    const uint_t uval = static_cast<uint_t>(scalar);
    return bool4_t{a.x > uval, a.y > uval, a.z > uval, a.w > uval};
}

export constexpr bool4_t operator>(const int_t scalar, const uint4_t b)
{
    FND_ASSERT(scalar >= 0);

    const uint_t uval = static_cast<uint_t>(scalar);
    return bool4_t{uval > b.x, uval > b.y, uval > b.z, uval > b.w};
}

export constexpr bool4_t operator>=(const uint4_t a, const uint4_t b)
{
    return bool4_t{a.x >= b.x, a.y >= b.y, a.z >= b.z, a.w >= b.w};
}

export constexpr bool4_t operator>=(const uint4_t a, const uint_t scalar)
{
    return bool4_t{a.x >= scalar, a.y >= scalar, a.z >= scalar, a.w >= scalar};
}

export constexpr bool4_t operator>=(const uint_t scalar, const uint4_t b)
{
    return bool4_t{scalar >= b.x, scalar >= b.y, scalar >= b.z, scalar >= b.w};
}

export constexpr bool4_t operator>=(const uint4_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    const uint_t uval = static_cast<uint_t>(scalar);
    return bool4_t{a.x >= uval, a.y >= uval, a.z >= uval, a.w >= uval};
}

export constexpr bool4_t operator>=(const int_t scalar, const uint4_t b)
{
    FND_ASSERT(scalar >= 0);

    const uint_t uval = static_cast<uint_t>(scalar);
    return bool4_t{uval >= b.x, uval >= b.y, uval >= b.z, uval >= b.w};
}

export constexpr uint4_t operator&(const uint4_t a, const uint4_t b)
{
    return uint4_t{a.x & b.x, a.y & b.y, a.z & b.z, a.w & b.w};
}

export constexpr uint4_t operator&(const uint4_t a, const uint_t scalar)
{
    return uint4_t{a.x & scalar, a.y & scalar, a.z & scalar, a.w & scalar};
}

export constexpr uint4_t operator&(const uint_t scalar, const uint4_t b)
{
    return uint4_t{scalar & b.x, scalar & b.y, scalar & b.z, scalar & b.w};
}

export constexpr uint4_t operator&(const uint4_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    return uint4_t{a.x & scalar, a.y & scalar, a.z & scalar, a.w & scalar};
}

export constexpr uint4_t operator&(const int_t scalar, const uint4_t b)
{
    FND_ASSERT(scalar >= 0);

    return uint4_t{scalar & b.x, scalar & b.y, scalar & b.z, scalar & b.w};
}

export constexpr uint4_t operator*(const uint4_t a, const uint4_t b)
{
    return uint4_t{a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w};
}

export constexpr uint4_t operator*(const uint4_t a, const uint_t scalar)
{
    return uint4_t{a.x * scalar, a.y * scalar, a.z * scalar, a.w * scalar};
}

export constexpr uint4_t operator*(const uint_t scalar, const uint4_t b)
{
    return uint4_t{scalar * b.x, scalar * b.y, scalar * b.z, scalar * b.w};
}

export constexpr uint4_t operator*(const uint4_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    return uint4_t{a.x * scalar, a.y * scalar, a.z * scalar, a.w * scalar};
}

export constexpr uint4_t operator*(const int_t scalar, const uint4_t b)
{
    FND_ASSERT(scalar >= 0);

    return uint4_t{scalar * b.x, scalar * b.y, scalar * b.z, scalar * b.w};
}

export constexpr uint4_t operator+(const uint4_t a, const uint4_t b)
{
    return uint4_t{a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

export constexpr uint4_t operator+(const uint4_t a, const uint_t scalar)
{
    return uint4_t{a.x + scalar, a.y + scalar, a.z + scalar, a.w + scalar};
}

export constexpr uint4_t operator+(const uint_t scalar, const uint4_t b)
{
    return uint4_t{scalar + b.x, scalar + b.y, scalar + b.z, scalar + b.w};
}

export constexpr uint4_t operator+(const uint4_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    return uint4_t{a.x + scalar, a.y + scalar, a.z + scalar, a.w + scalar};
}

export constexpr uint4_t operator+(const int_t scalar, const uint4_t b)
{
    FND_ASSERT(scalar >= 0);

    return uint4_t{scalar + b.x, scalar + b.y, scalar + b.z, scalar + b.w};
}

export constexpr uint4_t operator-(const uint4_t a, const uint4_t b)
{
    return uint4_t{a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}

export constexpr uint4_t operator-(const uint4_t a, const uint_t scalar)
{
    return uint4_t{a.x - scalar, a.y - scalar, a.z - scalar, a.w - scalar};
}

export constexpr uint4_t operator-(const uint_t scalar, const uint4_t b)
{
    return uint4_t{scalar - b.x, scalar - b.y, scalar - b.z, scalar - b.w};
}

export constexpr uint4_t operator-(const uint4_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    return uint4_t{a.x - scalar, a.y - scalar, a.z - scalar, a.w - scalar};
}

export constexpr uint4_t operator-(const int_t scalar, const uint4_t b)
{
    FND_ASSERT(scalar >= 0);

    return uint4_t{scalar - b.x, scalar - b.y, scalar - b.z, scalar - b.w};
}

export constexpr uint4_t operator%(const uint4_t a, const uint4_t b)
{
    FND_ASSERT(all(b != 0u));

    return uint4_t{a.x % b.x, a.y % b.y, a.z % b.z, a.w % b.w};
}

export constexpr uint4_t operator%(const uint4_t a, const uint_t scalar)
{
    FND_ASSERT(scalar != 0);

    return uint4_t{a.x % scalar, a.y % scalar, a.z % scalar, a.w % scalar};
}

export constexpr uint4_t operator%(const uint_t scalar, const uint4_t b)
{
    FND_ASSERT(all(b != 0u));

    return uint4_t{scalar % b.x, scalar % b.y, scalar % b.z, scalar % b.w};
}

export constexpr uint4_t operator%(const uint4_t a, const int_t scalar)
{
    FND_ASSERT(scalar > 0);

    return uint4_t{a.x % scalar, a.y % scalar, a.z % scalar, a.w % scalar};
}

export constexpr uint4_t operator%(const int_t scalar, const uint4_t b)
{
    FND_ASSERT(scalar >= 0);
    FND_ASSERT(all(b != 0u));

    return uint4_t{scalar % b.x, scalar % b.y, scalar % b.z, scalar % b.w};
}

export constexpr uint4_t operator/(const uint4_t a, const uint4_t b)
{
    FND_ASSERT(all(b != 0u));

    return uint4_t{a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w};
}

export constexpr uint4_t operator/(const uint4_t a, const uint_t scalar)
{
    FND_ASSERT(scalar != 0);

    return uint4_t{a.x / scalar, a.y / scalar, a.z / scalar, a.w / scalar};
}

export constexpr uint4_t operator/(const uint_t scalar, const uint4_t b)
{
    FND_ASSERT(all(b != 0u));

    return uint4_t{scalar / b.x, scalar / b.y, scalar / b.z, scalar / b.w};
}

export constexpr uint4_t operator/(const uint4_t a, const int_t scalar)
{
    FND_ASSERT(scalar > 0);

    return uint4_t{a.x / scalar, a.y / scalar, a.z / scalar, a.w / scalar};
}

export constexpr uint4_t operator/(const int_t scalar, const uint4_t b)
{
    FND_ASSERT(scalar >= 0);
    FND_ASSERT(all(b != 0u));

    return uint4_t{scalar / b.x, scalar / b.y, scalar / b.z, scalar / b.w};
}

export constexpr uint4_t operator<<(const uint4_t a, const uint4_t b)
{
    FND_ASSERT(all(b < 32u));

    return uint4_t{a.x << b.x, a.y << b.y, a.z << b.z, a.w << b.w};
}

export constexpr uint4_t operator<<(const uint4_t a, const uint_t scalar)
{
    FND_ASSERT(scalar < 32);

    return uint4_t{a.x << scalar, a.y << scalar, a.z << scalar, a.w << scalar};
}

export constexpr uint4_t operator<<(const uint_t scalar, const uint4_t b)
{
    FND_ASSERT(all(b < 32u));

    return uint4_t{scalar << b.x, scalar << b.y, scalar << b.z, scalar << b.w};
}

export constexpr uint4_t operator<<(const uint4_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0 && scalar < 32);

    return uint4_t{a.x << scalar, a.y << scalar, a.z << scalar, a.w << scalar};
}

export constexpr uint4_t operator<<(const int_t scalar, const uint4_t b)
{
    FND_ASSERT(scalar >= 0);
    FND_ASSERT(all(b < 32u));

    const uint_t uval = static_cast<uint_t>(scalar);
    return uint4_t{uval << b.x, uval << b.y, uval << b.z, uval << b.w};
}

export constexpr uint4_t operator>>(const uint4_t a, const uint4_t b)
{
    FND_ASSERT(all(b < 32u));

    return uint4_t{a.x >> b.x, a.y >> b.y, a.z >> b.z, a.w >> b.w};
}

export constexpr uint4_t operator>>(const uint4_t a, const uint_t scalar)
{
    FND_ASSERT(scalar < 32);

    return uint4_t{a.x >> scalar, a.y >> scalar, a.z >> scalar, a.w >> scalar};
}

export constexpr uint4_t operator>>(const uint_t scalar, const uint4_t b)
{
    FND_ASSERT(all(b < 32u));

    return uint4_t{scalar >> b.x, scalar >> b.y, scalar >> b.z, scalar >> b.w};
}

export constexpr uint4_t operator>>(const uint4_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0 && scalar < 32);

    return uint4_t{a.x >> scalar, a.y >> scalar, a.z >> scalar, a.w >> scalar};
}

export constexpr uint4_t operator>>(const int_t scalar, const uint4_t b)
{
    FND_ASSERT(scalar >= 0);
    FND_ASSERT(all(b < 32u));

    const uint_t uval = static_cast<uint_t>(scalar);
    return uint4_t{uval >> b.x, uval >> b.y, uval >> b.z, uval >> b.w};
}

export constexpr uint4_t operator^(const uint4_t a, const uint4_t b)
{
    return uint4_t{a.x ^ b.x, a.y ^ b.y, a.z ^ b.z, a.w ^ b.w};
}

export constexpr uint4_t operator^(const uint4_t a, const uint_t scalar)
{
    return uint4_t{a.x ^ scalar, a.y ^ scalar, a.z ^ scalar, a.w ^ scalar};
}

export constexpr uint4_t operator^(const uint_t scalar, const uint4_t b)
{
    return uint4_t{scalar ^ b.x, scalar ^ b.y, scalar ^ b.z, scalar ^ b.w};
}

export constexpr uint4_t operator^(const uint4_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    return uint4_t{a.x ^ scalar, a.y ^ scalar, a.z ^ scalar, a.w ^ scalar};
}

export constexpr uint4_t operator^(const int_t scalar, const uint4_t b)
{
    FND_ASSERT(scalar >= 0);

    return uint4_t{scalar ^ b.x, scalar ^ b.y, scalar ^ b.z, scalar ^ b.w};
}

export constexpr uint4_t operator|(const uint4_t a, const uint4_t b)
{
    return uint4_t{a.x | b.x, a.y | b.y, a.z | b.z, a.w | b.w};
}

export constexpr uint4_t operator|(const uint4_t a, const uint_t scalar)
{
    return uint4_t{a.x | scalar, a.y | scalar, a.z | scalar, a.w | scalar};
}

export constexpr uint4_t operator|(const uint_t scalar, const uint4_t b)
{
    return uint4_t{scalar | b.x, scalar | b.y, scalar | b.z, scalar | b.w};
}

export constexpr uint4_t operator|(const uint4_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0);

    return uint4_t{a.x | scalar, a.y | scalar, a.z | scalar, a.w | scalar};
}

export constexpr uint4_t operator|(const int_t scalar, const uint4_t b)
{
    FND_ASSERT(scalar >= 0);

    return uint4_t{scalar | b.x, scalar | b.y, scalar | b.z, scalar | b.w};
}

export constexpr uint4_t clamp(
    const uint4_t v, const uint4_t lower, const uint4_t upper)
{
    FND_ASSERT(all(lower <= upper));

    return uint4_t{clamp(v.x, lower.x, upper.x), clamp(v.y, lower.y, upper.y),
        clamp(v.z, lower.z, upper.z), clamp(v.w, lower.w, upper.w)};
}

export constexpr uint4_t clamp(
    const uint4_t v, const uint4_t lower, const uint_t upper)
{
    FND_ASSERT(all(lower <= upper));

    return uint4_t{clamp(v.x, lower.x, upper), clamp(v.y, lower.y, upper),
        clamp(v.z, lower.z, upper), clamp(v.w, lower.w, upper)};
}

export constexpr uint4_t clamp(
    const uint4_t v, const uint_t lower, const uint4_t upper)
{
    FND_ASSERT(all(lower <= upper));

    return uint4_t{clamp(v.x, lower, upper.x), clamp(v.y, lower, upper.y),
        clamp(v.z, lower, upper.z), clamp(v.w, lower, upper.w)};
}

export constexpr uint4_t clamp(
    const uint4_t v, const uint_t lower, const uint_t upper)
{
    FND_ASSERT(lower <= upper);

    return uint4_t{clamp(v.x, lower, upper), clamp(v.y, lower, upper),
        clamp(v.z, lower, upper), clamp(v.w, lower, upper)};
}

export constexpr uint_t cmax(const uint4_t v)
{
    return max(max(max(v.x, v.y), v.z), v.w);
}

export constexpr uint_t cmin(const uint4_t v)
{
    return min(min(min(v.x, v.y), v.z), v.w);
}

export constexpr uint_t cmul(const uint4_t v)
{
    return v.x * v.y * v.z * v.w;
}

export constexpr uint_t csum(const uint4_t v)
{
    return v.x + v.y + v.z + v.w;
}

export constexpr uint4_t max(const uint4_t a, const uint4_t b)
{
    return uint4_t{max(a.x, b.x), max(a.y, b.y), max(a.z, b.z), max(a.w, b.w)};
}

export constexpr uint4_t max(const uint4_t a, const uint_t scalar)
{
    return uint4_t{
        max(a.x, scalar), max(a.y, scalar), max(a.z, scalar), max(a.w, scalar)};
}

export constexpr uint4_t max(const uint_t scalar, const uint4_t b)
{
    return uint4_t{
        max(scalar, b.x), max(scalar, b.y), max(scalar, b.z), max(scalar, b.w)};
}

export constexpr uint4_t min(const uint4_t a, const uint4_t b)
{
    return uint4_t{min(a.x, b.x), min(a.y, b.y), min(a.z, b.z), min(a.w, b.w)};
}

export constexpr uint4_t min(const uint4_t a, const uint_t scalar)
{
    return uint4_t{
        min(a.x, scalar), min(a.y, scalar), min(a.z, scalar), min(a.w, scalar)};
}

export constexpr uint4_t min(const uint_t scalar, const uint4_t b)
{
    return uint4_t{
        min(scalar, b.x), min(scalar, b.y), min(scalar, b.z), min(scalar, b.w)};
}

} // namespace fnd
