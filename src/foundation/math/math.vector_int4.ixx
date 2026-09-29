module;
#include "foundation/core/macros.h"

export module foundation.math:vector_int4;
import foundation.core;
import :vector_bool;

namespace fnd {

export struct int4_t final {
    int_t x{0};
    int_t y{0};
    int_t z{0};
    int_t w{0};

    constexpr int4_t() = default;

    constexpr explicit int4_t(const int_t scalar)
        : x{scalar}, y{scalar}, z{scalar}, w{scalar}
    {
    }

    constexpr int4_t(const int_t x, const int_t y, const int_t z, const int_t w)
        : x{x}, y{y}, z{z}, w{w}
    {
    }

    constexpr const int_t& operator[](const uint_t idx) const
    {
        FND_ASSERT(idx < 4);
        return idx == 0 ? x : (idx == 1 ? y : (idx == 2 ? z : w));
    }

    constexpr int_t& operator[](const uint_t idx)
    {
        return const_cast<int_t&>(static_cast<const int4_t&>(*this)[idx]);
    }

    constexpr int4_t& operator++()
    {
        FND_ASSERT(x != kIntMaxValue);
        FND_ASSERT(y != kIntMaxValue);
        FND_ASSERT(z != kIntMaxValue);
        FND_ASSERT(w != kIntMaxValue);

        ++x;
        ++y;
        ++z;
        ++w;
        return *this;
    }

    constexpr int4_t operator++(int)
    {
        FND_ASSERT(x != kIntMaxValue);
        FND_ASSERT(y != kIntMaxValue);
        FND_ASSERT(z != kIntMaxValue);
        FND_ASSERT(w != kIntMaxValue);

        return int4_t{x++, y++, z++, w++};
    }

    constexpr int4_t& operator--()
    {
        FND_ASSERT(x != kIntMinValue);
        FND_ASSERT(y != kIntMinValue);
        FND_ASSERT(z != kIntMinValue);
        FND_ASSERT(w != kIntMinValue);

        --x;
        --y;
        --z;
        --w;
        return *this;
    }

    constexpr int4_t operator--(int)
    {
        FND_ASSERT(x != kIntMinValue);
        FND_ASSERT(y != kIntMinValue);
        FND_ASSERT(z != kIntMinValue);
        FND_ASSERT(w != kIntMinValue);

        return int4_t{x--, y--, z--, w--};
    }

    constexpr int4_t operator-() const
    {
        FND_ASSERT(x != kIntMinValue);
        FND_ASSERT(y != kIntMinValue);
        FND_ASSERT(z != kIntMinValue);
        FND_ASSERT(w != kIntMinValue);

        return int4_t{-x, -y, -z, -w};
    }

    constexpr int4_t operator~() const { return int4_t{~x, ~y, ~z, ~w}; }

    constexpr int4_t& operator+=(const int4_t b)
    {
        FND_ASSERT(
            long_t{x} + b.x >= kIntMinValue && long_t{x} + b.x <= kIntMaxValue);
        FND_ASSERT(
            long_t{y} + b.y >= kIntMinValue && long_t{y} + b.y <= kIntMaxValue);
        FND_ASSERT(
            long_t{z} + b.z >= kIntMinValue && long_t{z} + b.z <= kIntMaxValue);
        FND_ASSERT(
            long_t{w} + b.w >= kIntMinValue && long_t{w} + b.w <= kIntMaxValue);

        x += b.x;
        y += b.y;
        z += b.z;
        w += b.w;
        return *this;
    }

    constexpr int4_t& operator+=(const int_t scalar)
    {
        FND_ASSERT(long_t{x} + scalar >= kIntMinValue
            && long_t{x} + scalar <= kIntMaxValue);
        FND_ASSERT(long_t{y} + scalar >= kIntMinValue
            && long_t{y} + scalar <= kIntMaxValue);
        FND_ASSERT(long_t{z} + scalar >= kIntMinValue
            && long_t{z} + scalar <= kIntMaxValue);
        FND_ASSERT(long_t{w} + scalar >= kIntMinValue
            && long_t{w} + scalar <= kIntMaxValue);

        x += scalar;
        y += scalar;
        z += scalar;
        w += scalar;
        return *this;
    }

    constexpr int4_t& operator-=(const int4_t b)
    {
        FND_ASSERT(
            long_t{x} - b.x >= kIntMinValue && long_t{x} - b.x <= kIntMaxValue);
        FND_ASSERT(
            long_t{y} - b.y >= kIntMinValue && long_t{y} - b.y <= kIntMaxValue);
        FND_ASSERT(
            long_t{z} - b.z >= kIntMinValue && long_t{z} - b.z <= kIntMaxValue);
        FND_ASSERT(
            long_t{w} - b.w >= kIntMinValue && long_t{w} - b.w <= kIntMaxValue);

        x -= b.x;
        y -= b.y;
        z -= b.z;
        w -= b.w;
        return *this;
    }

    constexpr int4_t& operator-=(const int_t scalar)
    {
        FND_ASSERT(long_t{x} - scalar >= kIntMinValue
            && long_t{x} - scalar <= kIntMaxValue);
        FND_ASSERT(long_t{y} - scalar >= kIntMinValue
            && long_t{y} - scalar <= kIntMaxValue);
        FND_ASSERT(long_t{z} - scalar >= kIntMinValue
            && long_t{z} - scalar <= kIntMaxValue);
        FND_ASSERT(long_t{w} - scalar >= kIntMinValue
            && long_t{w} - scalar <= kIntMaxValue);

        x -= scalar;
        y -= scalar;
        z -= scalar;
        w -= scalar;
        return *this;
    }

    constexpr int4_t& operator*=(const int4_t b)
    {
        FND_ASSERT(
            long_t{x} * b.x >= kIntMinValue && long_t{x} * b.x <= kIntMaxValue);
        FND_ASSERT(
            long_t{y} * b.y >= kIntMinValue && long_t{y} * b.y <= kIntMaxValue);
        FND_ASSERT(
            long_t{z} * b.z >= kIntMinValue && long_t{z} * b.z <= kIntMaxValue);
        FND_ASSERT(
            long_t{w} * b.w >= kIntMinValue && long_t{w} * b.w <= kIntMaxValue);

        x *= b.x;
        y *= b.y;
        z *= b.z;
        w *= b.w;
        return *this;
    }

    constexpr int4_t& operator*=(const int_t scalar)
    {
        FND_ASSERT(long_t{x} * scalar >= kIntMinValue
            && long_t{x} * scalar <= kIntMaxValue);
        FND_ASSERT(long_t{y} * scalar >= kIntMinValue
            && long_t{y} * scalar <= kIntMaxValue);
        FND_ASSERT(long_t{z} * scalar >= kIntMinValue
            && long_t{z} * scalar <= kIntMaxValue);
        FND_ASSERT(long_t{w} * scalar >= kIntMinValue
            && long_t{w} * scalar <= kIntMaxValue);

        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
        return *this;
    }

    constexpr int4_t& operator/=(const int4_t b)
    {
        FND_ASSERT(b.x != 0 && b.y != 0 && b.z != 0 && b.w != 0);
        FND_ASSERT(!(x == kIntMinValue && b.x == -1));
        FND_ASSERT(!(y == kIntMinValue && b.y == -1));
        FND_ASSERT(!(z == kIntMinValue && b.z == -1));
        FND_ASSERT(!(w == kIntMinValue && b.w == -1));

        x /= b.x;
        y /= b.y;
        z /= b.z;
        w /= b.w;
        return *this;
    }

    constexpr int4_t& operator/=(const int_t scalar)
    {
        FND_ASSERT(scalar != 0);
        FND_ASSERT(!(scalar == -1 && x == kIntMinValue));
        FND_ASSERT(!(scalar == -1 && y == kIntMinValue));
        FND_ASSERT(!(scalar == -1 && z == kIntMinValue));
        FND_ASSERT(!(scalar == -1 && w == kIntMinValue));

        x /= scalar;
        y /= scalar;
        z /= scalar;
        w /= scalar;
        return *this;
    }

    constexpr int4_t& operator%=(const int4_t b)
    {
        FND_ASSERT(b.x != 0 && b.y != 0 && b.z != 0 && b.w != 0);
        FND_ASSERT(!(x == kIntMinValue && b.x == -1));
        FND_ASSERT(!(y == kIntMinValue && b.y == -1));
        FND_ASSERT(!(z == kIntMinValue && b.z == -1));
        FND_ASSERT(!(w == kIntMinValue && b.w == -1));

        x %= b.x;
        y %= b.y;
        z %= b.z;
        w %= b.w;
        return *this;
    }

    constexpr int4_t& operator%=(const int_t scalar)
    {
        FND_ASSERT(scalar != 0);
        FND_ASSERT(!(scalar == -1 && x == kIntMinValue));
        FND_ASSERT(!(scalar == -1 && y == kIntMinValue));
        FND_ASSERT(!(scalar == -1 && z == kIntMinValue));
        FND_ASSERT(!(scalar == -1 && w == kIntMinValue));

        x %= scalar;
        y %= scalar;
        z %= scalar;
        w %= scalar;
        return *this;
    }

    constexpr int4_t& operator&=(const int4_t b)
    {
        x &= b.x;
        y &= b.y;
        z &= b.z;
        w &= b.w;
        return *this;
    }

    constexpr int4_t& operator&=(const int_t scalar)
    {
        x &= scalar;
        y &= scalar;
        z &= scalar;
        w &= scalar;
        return *this;
    }

    constexpr int4_t& operator|=(const int4_t b)
    {
        x |= b.x;
        y |= b.y;
        z |= b.z;
        w |= b.w;
        return *this;
    }

    constexpr int4_t& operator|=(const int_t scalar)
    {
        x |= scalar;
        y |= scalar;
        z |= scalar;
        w |= scalar;
        return *this;
    }

    constexpr int4_t& operator^=(const int4_t b)
    {
        x ^= b.x;
        y ^= b.y;
        z ^= b.z;
        w ^= b.w;
        return *this;
    }

    constexpr int4_t& operator^=(const int_t scalar)
    {
        x ^= scalar;
        y ^= scalar;
        z ^= scalar;
        w ^= scalar;
        return *this;
    }

    constexpr int4_t& operator<<=(const int4_t b)
    {
        FND_ASSERT(b.x >= 0 && b.x < 32);
        FND_ASSERT(b.y >= 0 && b.y < 32);
        FND_ASSERT(b.z >= 0 && b.z < 32);
        FND_ASSERT(b.w >= 0 && b.w < 32);

        x <<= b.x;
        y <<= b.y;
        z <<= b.z;
        w <<= b.w;
        return *this;
    }

    constexpr int4_t& operator<<=(const int_t scalar)
    {
        FND_ASSERT(scalar >= 0 && scalar < 32);

        x <<= scalar;
        y <<= scalar;
        z <<= scalar;
        w <<= scalar;
        return *this;
    }

    constexpr int4_t& operator>>=(const int4_t b)
    {
        FND_ASSERT(b.x >= 0 && b.x < 32);
        FND_ASSERT(b.y >= 0 && b.y < 32);
        FND_ASSERT(b.z >= 0 && b.z < 32);
        FND_ASSERT(b.w >= 0 && b.w < 32);

        x >>= b.x;
        y >>= b.y;
        z >>= b.z;
        w >>= b.w;
        return *this;
    }

    constexpr int4_t& operator>>=(const int_t scalar)
    {
        FND_ASSERT(scalar >= 0 && scalar < 32);

        x >>= scalar;
        y >>= scalar;
        z >>= scalar;
        w >>= scalar;
        return *this;
    }
};

export constexpr bool4_t operator==(const int4_t a, const int4_t b)
{
    return bool4_t{a.x == b.x, a.y == b.y, a.z == b.z, a.w == b.w};
}

export constexpr bool4_t operator==(const int4_t a, const int_t scalar)
{
    return bool4_t{a.x == scalar, a.y == scalar, a.z == scalar, a.w == scalar};
}

export constexpr bool4_t operator==(const int_t scalar, const int4_t b)
{
    return bool4_t{scalar == b.x, scalar == b.y, scalar == b.z, scalar == b.w};
}

export constexpr bool4_t operator!=(const int4_t a, const int4_t b)
{
    return !(a == b);
}

export constexpr bool4_t operator!=(const int4_t a, const int_t scalar)
{
    return !(a == scalar);
}

export constexpr bool4_t operator!=(const int_t scalar, const int4_t b)
{
    return !(scalar == b);
}

export constexpr bool4_t operator<(const int4_t a, const int4_t b)
{
    return bool4_t{a.x < b.x, a.y < b.y, a.z < b.z, a.w < b.w};
}

export constexpr bool4_t operator<(const int4_t a, const int_t scalar)
{
    return bool4_t{a.x < scalar, a.y < scalar, a.z < scalar, a.w < scalar};
}

export constexpr bool4_t operator<(const int_t scalar, const int4_t b)
{
    return bool4_t{scalar < b.x, scalar < b.y, scalar < b.z, scalar < b.w};
}

export constexpr bool4_t operator<=(const int4_t a, const int4_t b)
{
    return bool4_t{a.x <= b.x, a.y <= b.y, a.z <= b.z, a.w <= b.w};
}

export constexpr bool4_t operator<=(const int4_t a, const int_t scalar)
{
    return bool4_t{a.x <= scalar, a.y <= scalar, a.z <= scalar, a.w <= scalar};
}

export constexpr bool4_t operator<=(const int_t scalar, const int4_t b)
{
    return bool4_t{scalar <= b.x, scalar <= b.y, scalar <= b.z, scalar <= b.w};
}

export constexpr bool4_t operator>(const int4_t a, const int4_t b)
{
    return bool4_t{a.x > b.x, a.y > b.y, a.z > b.z, a.w > b.w};
}

export constexpr bool4_t operator>(const int4_t a, const int_t scalar)
{
    return bool4_t{a.x > scalar, a.y > scalar, a.z > scalar, a.w > scalar};
}

export constexpr bool4_t operator>(const int_t scalar, const int4_t b)
{
    return bool4_t{scalar > b.x, scalar > b.y, scalar > b.z, scalar > b.w};
}

export constexpr bool4_t operator>=(const int4_t a, const int4_t b)
{
    return bool4_t{a.x >= b.x, a.y >= b.y, a.z >= b.z, a.w >= b.w};
}

export constexpr bool4_t operator>=(const int4_t a, const int_t scalar)
{
    return bool4_t{a.x >= scalar, a.y >= scalar, a.z >= scalar, a.w >= scalar};
}

export constexpr bool4_t operator>=(const int_t scalar, const int4_t b)
{
    return bool4_t{scalar >= b.x, scalar >= b.y, scalar >= b.z, scalar >= b.w};
}

export constexpr int4_t operator&(const int4_t a, const int4_t b)
{
    return int4_t{a.x & b.x, a.y & b.y, a.z & b.z, a.w & b.w};
}

export constexpr int4_t operator&(const int4_t a, const int_t scalar)
{
    return int4_t{a.x & scalar, a.y & scalar, a.z & scalar, a.w & scalar};
}

export constexpr int4_t operator&(const int_t scalar, const int4_t b)
{
    return int4_t{scalar & b.x, scalar & b.y, scalar & b.z, scalar & b.w};
}

export constexpr int4_t operator*(const int4_t a, const int4_t b)
{
    FND_ASSERT(
        long_t{a.x} * b.x >= kIntMinValue && long_t{a.x} * b.x <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.y} * b.y >= kIntMinValue && long_t{a.y} * b.y <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.z} * b.z >= kIntMinValue && long_t{a.z} * b.z <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.w} * b.w >= kIntMinValue && long_t{a.w} * b.w <= kIntMaxValue);

    return int4_t{a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w};
}

export constexpr int4_t operator*(const int4_t a, const int_t scalar)
{
    FND_ASSERT(long_t{a.x} * scalar >= kIntMinValue
        && long_t{a.x} * scalar <= kIntMaxValue);
    FND_ASSERT(long_t{a.y} * scalar >= kIntMinValue
        && long_t{a.y} * scalar <= kIntMaxValue);
    FND_ASSERT(long_t{a.z} * scalar >= kIntMinValue
        && long_t{a.z} * scalar <= kIntMaxValue);
    FND_ASSERT(long_t{a.w} * scalar >= kIntMinValue
        && long_t{a.w} * scalar <= kIntMaxValue);

    return int4_t{a.x * scalar, a.y * scalar, a.z * scalar, a.w * scalar};
}

export constexpr int4_t operator*(const int_t scalar, const int4_t b)
{
    FND_ASSERT(long_t{scalar} * b.x >= kIntMinValue
        && long_t{scalar} * b.x <= kIntMaxValue);
    FND_ASSERT(long_t{scalar} * b.y >= kIntMinValue
        && long_t{scalar} * b.y <= kIntMaxValue);
    FND_ASSERT(long_t{scalar} * b.z >= kIntMinValue
        && long_t{scalar} * b.z <= kIntMaxValue);
    FND_ASSERT(long_t{scalar} * b.w >= kIntMinValue
        && long_t{scalar} * b.w <= kIntMaxValue);

    return int4_t{scalar * b.x, scalar * b.y, scalar * b.z, scalar * b.w};
}

export constexpr int4_t operator+(const int4_t a, const int4_t b)
{
    FND_ASSERT(
        long_t{a.x} + b.x >= kIntMinValue && long_t{a.x} + b.x <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.y} + b.y >= kIntMinValue && long_t{a.y} + b.y <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.z} + b.z >= kIntMinValue && long_t{a.z} + b.z <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.w} + b.w >= kIntMinValue && long_t{a.w} + b.w <= kIntMaxValue);

    return int4_t{a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

export constexpr int4_t operator+(const int4_t a, const int_t scalar)
{
    FND_ASSERT(long_t{a.x} + scalar >= kIntMinValue
        && long_t{a.x} + scalar <= kIntMaxValue);
    FND_ASSERT(long_t{a.y} + scalar >= kIntMinValue
        && long_t{a.y} + scalar <= kIntMaxValue);
    FND_ASSERT(long_t{a.z} + scalar >= kIntMinValue
        && long_t{a.z} + scalar <= kIntMaxValue);
    FND_ASSERT(long_t{a.w} + scalar >= kIntMinValue
        && long_t{a.w} + scalar <= kIntMaxValue);

    return int4_t{a.x + scalar, a.y + scalar, a.z + scalar, a.w + scalar};
}

export constexpr int4_t operator+(const int_t scalar, const int4_t b)
{
    FND_ASSERT(long_t{scalar} + b.x >= kIntMinValue
        && long_t{scalar} + b.x <= kIntMaxValue);
    FND_ASSERT(long_t{scalar} + b.y >= kIntMinValue
        && long_t{scalar} + b.y <= kIntMaxValue);
    FND_ASSERT(long_t{scalar} + b.z >= kIntMinValue
        && long_t{scalar} + b.z <= kIntMaxValue);
    FND_ASSERT(long_t{scalar} + b.w >= kIntMinValue
        && long_t{scalar} + b.w <= kIntMaxValue);

    return int4_t{scalar + b.x, scalar + b.y, scalar + b.z, scalar + b.w};
}

export constexpr int4_t operator-(const int4_t a, const int4_t b)
{
    FND_ASSERT(
        long_t{a.x} - b.x >= kIntMinValue && long_t{a.x} - b.x <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.y} - b.y >= kIntMinValue && long_t{a.y} - b.y <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.z} - b.z >= kIntMinValue && long_t{a.z} - b.z <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.w} - b.w >= kIntMinValue && long_t{a.w} - b.w <= kIntMaxValue);

    return int4_t{a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}

export constexpr int4_t operator-(const int4_t a, const int_t scalar)
{
    FND_ASSERT(long_t{a.x} - scalar >= kIntMinValue
        && long_t{a.x} - scalar <= kIntMaxValue);
    FND_ASSERT(long_t{a.y} - scalar >= kIntMinValue
        && long_t{a.y} - scalar <= kIntMaxValue);
    FND_ASSERT(long_t{a.z} - scalar >= kIntMinValue
        && long_t{a.z} - scalar <= kIntMaxValue);
    FND_ASSERT(long_t{a.w} - scalar >= kIntMinValue
        && long_t{a.w} - scalar <= kIntMaxValue);

    return int4_t{a.x - scalar, a.y - scalar, a.z - scalar, a.w - scalar};
}

export constexpr int4_t operator-(const int_t scalar, const int4_t b)
{
    FND_ASSERT(long_t{scalar} - b.x >= kIntMinValue
        && long_t{scalar} - b.x <= kIntMaxValue);
    FND_ASSERT(long_t{scalar} - b.y >= kIntMinValue
        && long_t{scalar} - b.y <= kIntMaxValue);
    FND_ASSERT(long_t{scalar} - b.z >= kIntMinValue
        && long_t{scalar} - b.z <= kIntMaxValue);
    FND_ASSERT(long_t{scalar} - b.w >= kIntMinValue
        && long_t{scalar} - b.w <= kIntMaxValue);

    return int4_t{scalar - b.x, scalar - b.y, scalar - b.z, scalar - b.w};
}

export constexpr int4_t operator%(const int4_t a, const int4_t b)
{
    FND_ASSERT(all(b != 0));
    FND_ASSERT(!any(a == kIntMinValue && b == -1));

    return int4_t{a.x % b.x, a.y % b.y, a.z % b.z, a.w % b.w};
}

export constexpr int4_t operator%(const int4_t a, const int_t scalar)
{
    FND_ASSERT(scalar != 0);
    FND_ASSERT(!(scalar == -1 && any(a == kIntMinValue)));

    return int4_t{a.x % scalar, a.y % scalar, a.z % scalar, a.w % scalar};
}

export constexpr int4_t operator%(const int_t scalar, const int4_t b)
{
    FND_ASSERT(all(b != 0));
    FND_ASSERT(!(scalar == kIntMinValue && any(b == -1)));

    return int4_t{scalar % b.x, scalar % b.y, scalar % b.z, scalar % b.w};
}

export constexpr int4_t operator/(const int4_t a, const int4_t b)
{
    FND_ASSERT(all(b != 0));
    FND_ASSERT(!any(a == kIntMinValue && b == -1));

    return int4_t{a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w};
}

export constexpr int4_t operator/(const int4_t a, const int_t scalar)
{
    FND_ASSERT(scalar != 0);
    FND_ASSERT(!(scalar == -1 && any(a == kIntMinValue)));

    return int4_t{a.x / scalar, a.y / scalar, a.z / scalar, a.w / scalar};
}

export constexpr int4_t operator/(const int_t scalar, const int4_t b)
{
    FND_ASSERT(all(b != 0));
    FND_ASSERT(!(scalar == kIntMinValue && any(b == -1)));

    return int4_t{scalar / b.x, scalar / b.y, scalar / b.z, scalar / b.w};
}

// NOTE:
// operator<< does not check the result for overflow, unlike operator*. Since
// C++20 a left shift is defined for every value: the bits shifted out are
// discarded, so the result wraps modulo 2^32 (kIntMaxValue << 1 is -2).
export constexpr int4_t operator<<(const int4_t a, const int4_t b)
{
    FND_ASSERT(all(b >= 0 && b < 32));

    return int4_t{a.x << b.x, a.y << b.y, a.z << b.z, a.w << b.w};
}

export constexpr int4_t operator<<(const int4_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0 && scalar < 32);

    return int4_t{a.x << scalar, a.y << scalar, a.z << scalar, a.w << scalar};
}

export constexpr int4_t operator<<(const int_t scalar, const int4_t b)
{
    FND_ASSERT(all(b >= 0 && b < 32));

    return int4_t{scalar << b.x, scalar << b.y, scalar << b.z, scalar << b.w};
}

export constexpr int4_t operator>>(const int4_t a, const int4_t b)
{
    FND_ASSERT(all(b >= 0 && b < 32));

    return int4_t{a.x >> b.x, a.y >> b.y, a.z >> b.z, a.w >> b.w};
}

export constexpr int4_t operator>>(const int4_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0 && scalar < 32);

    return int4_t{a.x >> scalar, a.y >> scalar, a.z >> scalar, a.w >> scalar};
}

export constexpr int4_t operator>>(const int_t scalar, const int4_t b)
{
    FND_ASSERT(all(b >= 0 && b < 32));

    return int4_t{scalar >> b.x, scalar >> b.y, scalar >> b.z, scalar >> b.w};
}

export constexpr int4_t operator^(const int4_t a, const int4_t b)
{
    return int4_t{a.x ^ b.x, a.y ^ b.y, a.z ^ b.z, a.w ^ b.w};
}

export constexpr int4_t operator^(const int4_t a, const int_t scalar)
{
    return int4_t{a.x ^ scalar, a.y ^ scalar, a.z ^ scalar, a.w ^ scalar};
}

export constexpr int4_t operator^(const int_t scalar, const int4_t b)
{
    return int4_t{scalar ^ b.x, scalar ^ b.y, scalar ^ b.z, scalar ^ b.w};
}

export constexpr int4_t operator|(const int4_t a, const int4_t b)
{
    return int4_t{a.x | b.x, a.y | b.y, a.z | b.z, a.w | b.w};
}

export constexpr int4_t operator|(const int4_t a, const int_t scalar)
{
    return int4_t{a.x | scalar, a.y | scalar, a.z | scalar, a.w | scalar};
}

export constexpr int4_t operator|(const int_t scalar, const int4_t b)
{
    return int4_t{scalar | b.x, scalar | b.y, scalar | b.z, scalar | b.w};
}

export constexpr int4_t abs(const int4_t v)
{
    return int4_t{abs(v.x), abs(v.y), abs(v.z), abs(v.w)};
}

export constexpr int4_t clamp(
    const int4_t v, const int4_t lower, const int4_t upper)
{
    FND_ASSERT(all(lower <= upper));

    return int4_t{clamp(v.x, lower.x, upper.x), clamp(v.y, lower.y, upper.y),
        clamp(v.z, lower.z, upper.z), clamp(v.w, lower.w, upper.w)};
}

export constexpr int4_t clamp(
    const int4_t v, const int4_t lower, const int_t upper)
{
    FND_ASSERT(all(lower <= upper));

    return int4_t{clamp(v.x, lower.x, upper), clamp(v.y, lower.y, upper),
        clamp(v.z, lower.z, upper), clamp(v.w, lower.w, upper)};
}

export constexpr int4_t clamp(
    const int4_t v, const int_t lower, const int4_t upper)
{
    FND_ASSERT(all(lower <= upper));

    return int4_t{clamp(v.x, lower, upper.x), clamp(v.y, lower, upper.y),
        clamp(v.z, lower, upper.z), clamp(v.w, lower, upper.w)};
}

export constexpr int4_t clamp(
    const int4_t v, const int_t lower, const int_t upper)
{
    FND_ASSERT(lower <= upper);

    return int4_t{clamp(v.x, lower, upper), clamp(v.y, lower, upper),
        clamp(v.z, lower, upper), clamp(v.w, lower, upper)};
}

export constexpr int_t cmax(const int4_t v)
{
    return max(max(max(v.x, v.y), v.z), v.w);
}

export constexpr int_t cmin(const int4_t v)
{
    return min(min(min(v.x, v.y), v.z), v.w);
}

export constexpr int_t cmul(const int4_t v)
{
    FND_ASSERT(
        long_t{v.x} * v.y >= kIntMinValue && long_t{v.x} * v.y <= kIntMaxValue);

    const int_t partial1 = v.x * v.y;
    FND_ASSERT(long_t{partial1} * v.z >= kIntMinValue
        && long_t{partial1} * v.z <= kIntMaxValue);

    const int_t partial2 = partial1 * v.z;
    FND_ASSERT(long_t{partial2} * v.w >= kIntMinValue
        && long_t{partial2} * v.w <= kIntMaxValue);

    return partial2 * v.w;
}

export constexpr int_t csum(const int4_t v)
{
    FND_ASSERT(
        long_t{v.x} + v.y >= kIntMinValue && long_t{v.x} + v.y <= kIntMaxValue);

    const int_t partial1 = v.x + v.y;
    FND_ASSERT(long_t{partial1} + v.z >= kIntMinValue
        && long_t{partial1} + v.z <= kIntMaxValue);

    const int_t partial2 = partial1 + v.z;
    FND_ASSERT(long_t{partial2} + v.w >= kIntMinValue
        && long_t{partial2} + v.w <= kIntMaxValue);

    return partial2 + v.w;
}

export constexpr int4_t max(const int4_t a, const int4_t b)
{
    return int4_t{max(a.x, b.x), max(a.y, b.y), max(a.z, b.z), max(a.w, b.w)};
}

export constexpr int4_t max(const int4_t a, const int_t scalar)
{
    return int4_t{
        max(a.x, scalar), max(a.y, scalar), max(a.z, scalar), max(a.w, scalar)};
}

export constexpr int4_t max(const int_t scalar, const int4_t b)
{
    return int4_t{
        max(scalar, b.x), max(scalar, b.y), max(scalar, b.z), max(scalar, b.w)};
}

export constexpr int4_t min(const int4_t a, const int4_t b)
{
    return int4_t{min(a.x, b.x), min(a.y, b.y), min(a.z, b.z), min(a.w, b.w)};
}

export constexpr int4_t min(const int4_t a, const int_t scalar)
{
    return int4_t{
        min(a.x, scalar), min(a.y, scalar), min(a.z, scalar), min(a.w, scalar)};
}

export constexpr int4_t min(const int_t scalar, const int4_t b)
{
    return int4_t{
        min(scalar, b.x), min(scalar, b.y), min(scalar, b.z), min(scalar, b.w)};
}

export constexpr int4_t sign(const int4_t v)
{
    return int4_t{sign(v.x), sign(v.y), sign(v.z), sign(v.w)};
}

} // namespace fnd
