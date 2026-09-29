module;
#include "foundation/core/macros.h"

export module foundation.math:vector_int4;
import foundation.core;
import :vector_bool;

namespace fnd {

export struct int4_t final {
    static const int4_t kZero;
    static const int4_t kUnitX;
    static const int4_t kUnitY;
    static const int4_t kUnitZ;
    static const int4_t kUnitW;

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
};

constexpr int4_t int4_t::kZero{0, 0, 0, 0};
constexpr int4_t int4_t::kUnitX{1, 0, 0, 0};
constexpr int4_t int4_t::kUnitY{0, 1, 0, 0};
constexpr int4_t int4_t::kUnitZ{0, 0, 1, 0};
constexpr int4_t int4_t::kUnitW{0, 0, 0, 1};

export constexpr int4_t& operator++(int4_t& v)
{
    FND_ASSERT(v.x != kIntMaxValue);
    FND_ASSERT(v.y != kIntMaxValue);
    FND_ASSERT(v.z != kIntMaxValue);
    FND_ASSERT(v.w != kIntMaxValue);

    ++v.x;
    ++v.y;
    ++v.z;
    ++v.w;
    return v;
}

export constexpr int4_t operator++(int4_t& v, int)
{
    FND_ASSERT(v.x != kIntMaxValue);
    FND_ASSERT(v.y != kIntMaxValue);
    FND_ASSERT(v.z != kIntMaxValue);
    FND_ASSERT(v.w != kIntMaxValue);

    return int4_t{v.x++, v.y++, v.z++, v.w++};
}

export constexpr int4_t& operator--(int4_t& v)
{
    FND_ASSERT(v.x != kIntMinValue);
    FND_ASSERT(v.y != kIntMinValue);
    FND_ASSERT(v.z != kIntMinValue);
    FND_ASSERT(v.w != kIntMinValue);

    --v.x;
    --v.y;
    --v.z;
    --v.w;
    return v;
}

export constexpr int4_t operator--(int4_t& v, int)
{
    FND_ASSERT(v.x != kIntMinValue);
    FND_ASSERT(v.y != kIntMinValue);
    FND_ASSERT(v.z != kIntMinValue);
    FND_ASSERT(v.w != kIntMinValue);

    return int4_t{v.x--, v.y--, v.z--, v.w--};
}

export constexpr int4_t operator-(const int4_t v)
{
    FND_ASSERT(v.x != kIntMinValue);
    FND_ASSERT(v.y != kIntMinValue);
    FND_ASSERT(v.z != kIntMinValue);
    FND_ASSERT(v.w != kIntMinValue);

    return int4_t{-v.x, -v.y, -v.z, -v.w};
}

export constexpr int4_t operator~(const int4_t v)
{
    return int4_t{~v.x, ~v.y, ~v.z, ~v.w};
}

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

export constexpr int4_t& operator&=(int4_t& a, const int4_t b)
{
    a = a & b;
    return a;
}

export constexpr int4_t& operator&=(int4_t& a, const int_t scalar)
{
    a = a & scalar;
    return a;
}

export constexpr int4_t& operator*=(int4_t& a, const int4_t b)
{
    FND_ASSERT(
        long_t{a.x} * b.x >= kIntMinValue && long_t{a.x} * b.x <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.y} * b.y >= kIntMinValue && long_t{a.y} * b.y <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.z} * b.z >= kIntMinValue && long_t{a.z} * b.z <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.w} * b.w >= kIntMinValue && long_t{a.w} * b.w <= kIntMaxValue);

    a = a * b;
    return a;
}

export constexpr int4_t& operator*=(int4_t& a, const int_t scalar)
{
    FND_ASSERT(long_t{a.x} * scalar >= kIntMinValue
        && long_t{a.x} * scalar <= kIntMaxValue);
    FND_ASSERT(long_t{a.y} * scalar >= kIntMinValue
        && long_t{a.y} * scalar <= kIntMaxValue);
    FND_ASSERT(long_t{a.z} * scalar >= kIntMinValue
        && long_t{a.z} * scalar <= kIntMaxValue);
    FND_ASSERT(long_t{a.w} * scalar >= kIntMinValue
        && long_t{a.w} * scalar <= kIntMaxValue);

    a = a * scalar;
    return a;
}

export constexpr int4_t& operator+=(int4_t& a, const int4_t b)
{
    FND_ASSERT(
        long_t{a.x} + b.x >= kIntMinValue && long_t{a.x} + b.x <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.y} + b.y >= kIntMinValue && long_t{a.y} + b.y <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.z} + b.z >= kIntMinValue && long_t{a.z} + b.z <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.w} + b.w >= kIntMinValue && long_t{a.w} + b.w <= kIntMaxValue);

    a = a + b;
    return a;
}

export constexpr int4_t& operator+=(int4_t& a, const int_t scalar)
{
    FND_ASSERT(long_t{a.x} + scalar >= kIntMinValue
        && long_t{a.x} + scalar <= kIntMaxValue);
    FND_ASSERT(long_t{a.y} + scalar >= kIntMinValue
        && long_t{a.y} + scalar <= kIntMaxValue);
    FND_ASSERT(long_t{a.z} + scalar >= kIntMinValue
        && long_t{a.z} + scalar <= kIntMaxValue);
    FND_ASSERT(long_t{a.w} + scalar >= kIntMinValue
        && long_t{a.w} + scalar <= kIntMaxValue);

    a = a + scalar;
    return a;
}

export constexpr int4_t& operator-=(int4_t& a, const int4_t b)
{
    FND_ASSERT(
        long_t{a.x} - b.x >= kIntMinValue && long_t{a.x} - b.x <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.y} - b.y >= kIntMinValue && long_t{a.y} - b.y <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.z} - b.z >= kIntMinValue && long_t{a.z} - b.z <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.w} - b.w >= kIntMinValue && long_t{a.w} - b.w <= kIntMaxValue);

    a = a - b;
    return a;
}

export constexpr int4_t& operator-=(int4_t& a, const int_t scalar)
{
    FND_ASSERT(long_t{a.x} - scalar >= kIntMinValue
        && long_t{a.x} - scalar <= kIntMaxValue);
    FND_ASSERT(long_t{a.y} - scalar >= kIntMinValue
        && long_t{a.y} - scalar <= kIntMaxValue);
    FND_ASSERT(long_t{a.z} - scalar >= kIntMinValue
        && long_t{a.z} - scalar <= kIntMaxValue);
    FND_ASSERT(long_t{a.w} - scalar >= kIntMinValue
        && long_t{a.w} - scalar <= kIntMaxValue);

    a = a - scalar;
    return a;
}

export constexpr int4_t& operator%=(int4_t& a, const int4_t b)
{
    FND_ASSERT(all(b != 0));
    FND_ASSERT(!any(a == kIntMinValue && b == -1));

    a = a % b;
    return a;
}

export constexpr int4_t& operator%=(int4_t& a, const int_t scalar)
{
    FND_ASSERT(scalar != 0);
    FND_ASSERT(!(scalar == -1 && any(a == kIntMinValue)));

    a = a % scalar;
    return a;
}

export constexpr int4_t& operator/=(int4_t& a, const int4_t b)
{
    FND_ASSERT(all(b != 0));
    FND_ASSERT(!any(a == kIntMinValue && b == -1));

    a = a / b;
    return a;
}

export constexpr int4_t& operator/=(int4_t& a, const int_t scalar)
{
    FND_ASSERT(scalar != 0);
    FND_ASSERT(!(scalar == -1 && any(a == kIntMinValue)));

    a = a / scalar;
    return a;
}

export constexpr int4_t& operator<<=(int4_t& a, const int4_t b)
{
    FND_ASSERT(all(b >= 0 && b < 32));

    a = a << b;
    return a;
}

export constexpr int4_t& operator<<=(int4_t& a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0 && scalar < 32);

    a = a << scalar;
    return a;
}

export constexpr int4_t& operator>>=(int4_t& a, const int4_t b)
{
    FND_ASSERT(all(b >= 0 && b < 32));

    a = a >> b;
    return a;
}

export constexpr int4_t& operator>>=(int4_t& a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0 && scalar < 32);

    a = a >> scalar;
    return a;
}

export constexpr int4_t& operator^=(int4_t& a, const int4_t b)
{
    a = a ^ b;
    return a;
}

export constexpr int4_t& operator^=(int4_t& a, const int_t scalar)
{
    a = a ^ scalar;
    return a;
}

export constexpr int4_t& operator|=(int4_t& a, const int4_t b)
{
    a = a | b;
    return a;
}

export constexpr int4_t& operator|=(int4_t& a, const int_t scalar)
{
    a = a | scalar;
    return a;
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
