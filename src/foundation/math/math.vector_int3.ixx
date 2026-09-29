module;
#include "foundation/core/macros.h"

export module foundation.math:vector_int3;
import foundation.core;
import :vector_bool;

namespace fnd {

export struct int3_t final {
    static const int3_t kZero;
    static const int3_t kUnitX;
    static const int3_t kUnitY;
    static const int3_t kUnitZ;

    int_t x{0};
    int_t y{0};
    int_t z{0};

    constexpr int3_t() = default;

    constexpr explicit int3_t(const int_t scalar)
        : x{scalar}, y{scalar}, z{scalar}
    {
    }

    constexpr int3_t(const int_t x, const int_t y, const int_t z)
        : x{x}, y{y}, z{z}
    {
    }

    constexpr const int_t& operator[](const uint_t idx) const
    {
        FND_ASSERT(idx < 3);
        return idx == 0 ? x : (idx == 1 ? y : z);
    }

    constexpr int_t& operator[](const uint_t idx)
    {
        return const_cast<int_t&>(static_cast<const int3_t&>(*this)[idx]);
    }
};

constexpr int3_t int3_t::kZero{0, 0, 0};
constexpr int3_t int3_t::kUnitX{1, 0, 0};
constexpr int3_t int3_t::kUnitY{0, 1, 0};
constexpr int3_t int3_t::kUnitZ{0, 0, 1};

export constexpr int3_t& operator++(int3_t& v)
{
    FND_ASSERT(v.x != kIntMaxValue);
    FND_ASSERT(v.y != kIntMaxValue);
    FND_ASSERT(v.z != kIntMaxValue);

    ++v.x;
    ++v.y;
    ++v.z;
    return v;
}

export constexpr int3_t operator++(int3_t& v, int)
{
    FND_ASSERT(v.x != kIntMaxValue);
    FND_ASSERT(v.y != kIntMaxValue);
    FND_ASSERT(v.z != kIntMaxValue);

    return int3_t{v.x++, v.y++, v.z++};
}

export constexpr int3_t& operator--(int3_t& v)
{
    FND_ASSERT(v.x != kIntMinValue);
    FND_ASSERT(v.y != kIntMinValue);
    FND_ASSERT(v.z != kIntMinValue);

    --v.x;
    --v.y;
    --v.z;
    return v;
}

export constexpr int3_t operator--(int3_t& v, int)
{
    FND_ASSERT(v.x != kIntMinValue);
    FND_ASSERT(v.y != kIntMinValue);
    FND_ASSERT(v.z != kIntMinValue);

    return int3_t{v.x--, v.y--, v.z--};
}

export constexpr int3_t operator-(const int3_t v)
{
    FND_ASSERT(v.x != kIntMinValue);
    FND_ASSERT(v.y != kIntMinValue);
    FND_ASSERT(v.z != kIntMinValue);

    return int3_t{-v.x, -v.y, -v.z};
}

export constexpr int3_t operator~(const int3_t v)
{
    return int3_t{~v.x, ~v.y, ~v.z};
}

export constexpr bool3_t operator==(const int3_t a, const int3_t b)
{
    return bool3_t{a.x == b.x, a.y == b.y, a.z == b.z};
}

export constexpr bool3_t operator==(const int3_t a, const int_t scalar)
{
    return bool3_t{a.x == scalar, a.y == scalar, a.z == scalar};
}

export constexpr bool3_t operator==(const int_t scalar, const int3_t b)
{
    return bool3_t{scalar == b.x, scalar == b.y, scalar == b.z};
}

export constexpr bool3_t operator!=(const int3_t a, const int3_t b)
{
    return !(a == b);
}

export constexpr bool3_t operator!=(const int3_t a, const int_t scalar)
{
    return !(a == scalar);
}

export constexpr bool3_t operator!=(const int_t scalar, const int3_t b)
{
    return !(scalar == b);
}

export constexpr bool3_t operator<(const int3_t a, const int3_t b)
{
    return bool3_t{a.x < b.x, a.y < b.y, a.z < b.z};
}

export constexpr bool3_t operator<(const int3_t a, const int_t scalar)
{
    return bool3_t{a.x < scalar, a.y < scalar, a.z < scalar};
}

export constexpr bool3_t operator<(const int_t scalar, const int3_t b)
{
    return bool3_t{scalar < b.x, scalar < b.y, scalar < b.z};
}

export constexpr bool3_t operator<=(const int3_t a, const int3_t b)
{
    return bool3_t{a.x <= b.x, a.y <= b.y, a.z <= b.z};
}

export constexpr bool3_t operator<=(const int3_t a, const int_t scalar)
{
    return bool3_t{a.x <= scalar, a.y <= scalar, a.z <= scalar};
}

export constexpr bool3_t operator<=(const int_t scalar, const int3_t b)
{
    return bool3_t{scalar <= b.x, scalar <= b.y, scalar <= b.z};
}

export constexpr bool3_t operator>(const int3_t a, const int3_t b)
{
    return bool3_t{a.x > b.x, a.y > b.y, a.z > b.z};
}

export constexpr bool3_t operator>(const int3_t a, const int_t scalar)
{
    return bool3_t{a.x > scalar, a.y > scalar, a.z > scalar};
}

export constexpr bool3_t operator>(const int_t scalar, const int3_t b)
{
    return bool3_t{scalar > b.x, scalar > b.y, scalar > b.z};
}

export constexpr bool3_t operator>=(const int3_t a, const int3_t b)
{
    return bool3_t{a.x >= b.x, a.y >= b.y, a.z >= b.z};
}

export constexpr bool3_t operator>=(const int3_t a, const int_t scalar)
{
    return bool3_t{a.x >= scalar, a.y >= scalar, a.z >= scalar};
}

export constexpr bool3_t operator>=(const int_t scalar, const int3_t b)
{
    return bool3_t{scalar >= b.x, scalar >= b.y, scalar >= b.z};
}

export constexpr int3_t operator&(const int3_t a, const int3_t b)
{
    return int3_t{a.x & b.x, a.y & b.y, a.z & b.z};
}

export constexpr int3_t operator&(const int3_t a, const int_t scalar)
{
    return int3_t{a.x & scalar, a.y & scalar, a.z & scalar};
}

export constexpr int3_t operator&(const int_t scalar, const int3_t b)
{
    return int3_t{scalar & b.x, scalar & b.y, scalar & b.z};
}

export constexpr int3_t operator*(const int3_t a, const int3_t b)
{
    FND_ASSERT(
        long_t{a.x} * b.x >= kIntMinValue && long_t{a.x} * b.x <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.y} * b.y >= kIntMinValue && long_t{a.y} * b.y <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.z} * b.z >= kIntMinValue && long_t{a.z} * b.z <= kIntMaxValue);

    return int3_t{a.x * b.x, a.y * b.y, a.z * b.z};
}

export constexpr int3_t operator*(const int3_t a, const int_t scalar)
{
    FND_ASSERT(long_t{a.x} * scalar >= kIntMinValue
        && long_t{a.x} * scalar <= kIntMaxValue);
    FND_ASSERT(long_t{a.y} * scalar >= kIntMinValue
        && long_t{a.y} * scalar <= kIntMaxValue);
    FND_ASSERT(long_t{a.z} * scalar >= kIntMinValue
        && long_t{a.z} * scalar <= kIntMaxValue);

    return int3_t{a.x * scalar, a.y * scalar, a.z * scalar};
}

export constexpr int3_t operator*(const int_t scalar, const int3_t b)
{
    FND_ASSERT(long_t{scalar} * b.x >= kIntMinValue
        && long_t{scalar} * b.x <= kIntMaxValue);
    FND_ASSERT(long_t{scalar} * b.y >= kIntMinValue
        && long_t{scalar} * b.y <= kIntMaxValue);
    FND_ASSERT(long_t{scalar} * b.z >= kIntMinValue
        && long_t{scalar} * b.z <= kIntMaxValue);

    return int3_t{scalar * b.x, scalar * b.y, scalar * b.z};
}

export constexpr int3_t operator+(const int3_t a, const int3_t b)
{
    FND_ASSERT(
        long_t{a.x} + b.x >= kIntMinValue && long_t{a.x} + b.x <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.y} + b.y >= kIntMinValue && long_t{a.y} + b.y <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.z} + b.z >= kIntMinValue && long_t{a.z} + b.z <= kIntMaxValue);

    return int3_t{a.x + b.x, a.y + b.y, a.z + b.z};
}

export constexpr int3_t operator+(const int3_t a, const int_t scalar)
{
    FND_ASSERT(long_t{a.x} + scalar >= kIntMinValue
        && long_t{a.x} + scalar <= kIntMaxValue);
    FND_ASSERT(long_t{a.y} + scalar >= kIntMinValue
        && long_t{a.y} + scalar <= kIntMaxValue);
    FND_ASSERT(long_t{a.z} + scalar >= kIntMinValue
        && long_t{a.z} + scalar <= kIntMaxValue);

    return int3_t{a.x + scalar, a.y + scalar, a.z + scalar};
}

export constexpr int3_t operator+(const int_t scalar, const int3_t b)
{
    FND_ASSERT(long_t{scalar} + b.x >= kIntMinValue
        && long_t{scalar} + b.x <= kIntMaxValue);
    FND_ASSERT(long_t{scalar} + b.y >= kIntMinValue
        && long_t{scalar} + b.y <= kIntMaxValue);
    FND_ASSERT(long_t{scalar} + b.z >= kIntMinValue
        && long_t{scalar} + b.z <= kIntMaxValue);

    return int3_t{scalar + b.x, scalar + b.y, scalar + b.z};
}

export constexpr int3_t operator-(const int3_t a, const int3_t b)
{
    FND_ASSERT(
        long_t{a.x} - b.x >= kIntMinValue && long_t{a.x} - b.x <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.y} - b.y >= kIntMinValue && long_t{a.y} - b.y <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.z} - b.z >= kIntMinValue && long_t{a.z} - b.z <= kIntMaxValue);

    return int3_t{a.x - b.x, a.y - b.y, a.z - b.z};
}

export constexpr int3_t operator-(const int3_t a, const int_t scalar)
{
    FND_ASSERT(long_t{a.x} - scalar >= kIntMinValue
        && long_t{a.x} - scalar <= kIntMaxValue);
    FND_ASSERT(long_t{a.y} - scalar >= kIntMinValue
        && long_t{a.y} - scalar <= kIntMaxValue);
    FND_ASSERT(long_t{a.z} - scalar >= kIntMinValue
        && long_t{a.z} - scalar <= kIntMaxValue);

    return int3_t{a.x - scalar, a.y - scalar, a.z - scalar};
}

export constexpr int3_t operator-(const int_t scalar, const int3_t b)
{
    FND_ASSERT(long_t{scalar} - b.x >= kIntMinValue
        && long_t{scalar} - b.x <= kIntMaxValue);
    FND_ASSERT(long_t{scalar} - b.y >= kIntMinValue
        && long_t{scalar} - b.y <= kIntMaxValue);
    FND_ASSERT(long_t{scalar} - b.z >= kIntMinValue
        && long_t{scalar} - b.z <= kIntMaxValue);

    return int3_t{scalar - b.x, scalar - b.y, scalar - b.z};
}

export constexpr int3_t operator%(const int3_t a, const int3_t b)
{
    FND_ASSERT(all(b != 0));
    FND_ASSERT(!any(a == kIntMinValue && b == -1));

    return int3_t{a.x % b.x, a.y % b.y, a.z % b.z};
}

export constexpr int3_t operator%(const int3_t a, const int_t scalar)
{
    FND_ASSERT(scalar != 0);
    FND_ASSERT(!(scalar == -1 && any(a == kIntMinValue)));

    return int3_t{a.x % scalar, a.y % scalar, a.z % scalar};
}

export constexpr int3_t operator%(const int_t scalar, const int3_t b)
{
    FND_ASSERT(all(b != 0));
    FND_ASSERT(!(scalar == kIntMinValue && any(b == -1)));

    return int3_t{scalar % b.x, scalar % b.y, scalar % b.z};
}

export constexpr int3_t operator/(const int3_t a, const int3_t b)
{
    FND_ASSERT(all(b != 0));
    FND_ASSERT(!any(a == kIntMinValue && b == -1));

    return int3_t{a.x / b.x, a.y / b.y, a.z / b.z};
}

export constexpr int3_t operator/(const int3_t a, const int_t scalar)
{
    FND_ASSERT(scalar != 0);
    FND_ASSERT(!(scalar == -1 && any(a == kIntMinValue)));

    return int3_t{a.x / scalar, a.y / scalar, a.z / scalar};
}

export constexpr int3_t operator/(const int_t scalar, const int3_t b)
{
    FND_ASSERT(all(b != 0));
    FND_ASSERT(!(scalar == kIntMinValue && any(b == -1)));

    return int3_t{scalar / b.x, scalar / b.y, scalar / b.z};
}

// NOTE:
// operator<< does not check the result for overflow, unlike operator*. Since
// C++20 a left shift is defined for every value: the bits shifted out are
// discarded, so the result wraps modulo 2^32 (kIntMaxValue << 1 is -2).
export constexpr int3_t operator<<(const int3_t a, const int3_t b)
{
    FND_ASSERT(all(b >= 0 && b < 32));

    return int3_t{a.x << b.x, a.y << b.y, a.z << b.z};
}

export constexpr int3_t operator<<(const int3_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0 && scalar < 32);

    return int3_t{a.x << scalar, a.y << scalar, a.z << scalar};
}

export constexpr int3_t operator<<(const int_t scalar, const int3_t b)
{
    FND_ASSERT(all(b >= 0 && b < 32));

    return int3_t{scalar << b.x, scalar << b.y, scalar << b.z};
}

export constexpr int3_t operator>>(const int3_t a, const int3_t b)
{
    FND_ASSERT(all(b >= 0 && b < 32));

    return int3_t{a.x >> b.x, a.y >> b.y, a.z >> b.z};
}

export constexpr int3_t operator>>(const int3_t a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0 && scalar < 32);

    return int3_t{a.x >> scalar, a.y >> scalar, a.z >> scalar};
}

export constexpr int3_t operator>>(const int_t scalar, const int3_t b)
{
    FND_ASSERT(all(b >= 0 && b < 32));

    return int3_t{scalar >> b.x, scalar >> b.y, scalar >> b.z};
}

export constexpr int3_t operator^(const int3_t a, const int3_t b)
{
    return int3_t{a.x ^ b.x, a.y ^ b.y, a.z ^ b.z};
}

export constexpr int3_t operator^(const int3_t a, const int_t scalar)
{
    return int3_t{a.x ^ scalar, a.y ^ scalar, a.z ^ scalar};
}

export constexpr int3_t operator^(const int_t scalar, const int3_t b)
{
    return int3_t{scalar ^ b.x, scalar ^ b.y, scalar ^ b.z};
}

export constexpr int3_t operator|(const int3_t a, const int3_t b)
{
    return int3_t{a.x | b.x, a.y | b.y, a.z | b.z};
}

export constexpr int3_t operator|(const int3_t a, const int_t scalar)
{
    return int3_t{a.x | scalar, a.y | scalar, a.z | scalar};
}

export constexpr int3_t operator|(const int_t scalar, const int3_t b)
{
    return int3_t{scalar | b.x, scalar | b.y, scalar | b.z};
}

export constexpr int3_t& operator&=(int3_t& a, const int3_t b)
{
    a = a & b;
    return a;
}

export constexpr int3_t& operator&=(int3_t& a, const int_t scalar)
{
    a = a & scalar;
    return a;
}

export constexpr int3_t& operator*=(int3_t& a, const int3_t b)
{
    FND_ASSERT(
        long_t{a.x} * b.x >= kIntMinValue && long_t{a.x} * b.x <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.y} * b.y >= kIntMinValue && long_t{a.y} * b.y <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.z} * b.z >= kIntMinValue && long_t{a.z} * b.z <= kIntMaxValue);

    a = a * b;
    return a;
}

export constexpr int3_t& operator*=(int3_t& a, const int_t scalar)
{
    FND_ASSERT(long_t{a.x} * scalar >= kIntMinValue
        && long_t{a.x} * scalar <= kIntMaxValue);
    FND_ASSERT(long_t{a.y} * scalar >= kIntMinValue
        && long_t{a.y} * scalar <= kIntMaxValue);
    FND_ASSERT(long_t{a.z} * scalar >= kIntMinValue
        && long_t{a.z} * scalar <= kIntMaxValue);

    a = a * scalar;
    return a;
}

export constexpr int3_t& operator+=(int3_t& a, const int3_t b)
{
    FND_ASSERT(
        long_t{a.x} + b.x >= kIntMinValue && long_t{a.x} + b.x <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.y} + b.y >= kIntMinValue && long_t{a.y} + b.y <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.z} + b.z >= kIntMinValue && long_t{a.z} + b.z <= kIntMaxValue);

    a = a + b;
    return a;
}

export constexpr int3_t& operator+=(int3_t& a, const int_t scalar)
{
    FND_ASSERT(long_t{a.x} + scalar >= kIntMinValue
        && long_t{a.x} + scalar <= kIntMaxValue);
    FND_ASSERT(long_t{a.y} + scalar >= kIntMinValue
        && long_t{a.y} + scalar <= kIntMaxValue);
    FND_ASSERT(long_t{a.z} + scalar >= kIntMinValue
        && long_t{a.z} + scalar <= kIntMaxValue);

    a = a + scalar;
    return a;
}

export constexpr int3_t& operator-=(int3_t& a, const int3_t b)
{
    FND_ASSERT(
        long_t{a.x} - b.x >= kIntMinValue && long_t{a.x} - b.x <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.y} - b.y >= kIntMinValue && long_t{a.y} - b.y <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.z} - b.z >= kIntMinValue && long_t{a.z} - b.z <= kIntMaxValue);

    a = a - b;
    return a;
}

export constexpr int3_t& operator-=(int3_t& a, const int_t scalar)
{
    FND_ASSERT(long_t{a.x} - scalar >= kIntMinValue
        && long_t{a.x} - scalar <= kIntMaxValue);
    FND_ASSERT(long_t{a.y} - scalar >= kIntMinValue
        && long_t{a.y} - scalar <= kIntMaxValue);
    FND_ASSERT(long_t{a.z} - scalar >= kIntMinValue
        && long_t{a.z} - scalar <= kIntMaxValue);

    a = a - scalar;
    return a;
}

export constexpr int3_t& operator%=(int3_t& a, const int3_t b)
{
    FND_ASSERT(all(b != 0));
    FND_ASSERT(!any(a == kIntMinValue && b == -1));

    a = a % b;
    return a;
}

export constexpr int3_t& operator%=(int3_t& a, const int_t scalar)
{
    FND_ASSERT(scalar != 0);
    FND_ASSERT(!(scalar == -1 && any(a == kIntMinValue)));

    a = a % scalar;
    return a;
}

export constexpr int3_t& operator/=(int3_t& a, const int3_t b)
{
    FND_ASSERT(all(b != 0));
    FND_ASSERT(!any(a == kIntMinValue && b == -1));

    a = a / b;
    return a;
}

export constexpr int3_t& operator/=(int3_t& a, const int_t scalar)
{
    FND_ASSERT(scalar != 0);
    FND_ASSERT(!(scalar == -1 && any(a == kIntMinValue)));

    a = a / scalar;
    return a;
}

export constexpr int3_t& operator<<=(int3_t& a, const int3_t b)
{
    FND_ASSERT(all(b >= 0 && b < 32));

    a = a << b;
    return a;
}

export constexpr int3_t& operator<<=(int3_t& a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0 && scalar < 32);

    a = a << scalar;
    return a;
}

export constexpr int3_t& operator>>=(int3_t& a, const int3_t b)
{
    FND_ASSERT(all(b >= 0 && b < 32));

    a = a >> b;
    return a;
}

export constexpr int3_t& operator>>=(int3_t& a, const int_t scalar)
{
    FND_ASSERT(scalar >= 0 && scalar < 32);

    a = a >> scalar;
    return a;
}

export constexpr int3_t& operator^=(int3_t& a, const int3_t b)
{
    a = a ^ b;
    return a;
}

export constexpr int3_t& operator^=(int3_t& a, const int_t scalar)
{
    a = a ^ scalar;
    return a;
}

export constexpr int3_t& operator|=(int3_t& a, const int3_t b)
{
    a = a | b;
    return a;
}

export constexpr int3_t& operator|=(int3_t& a, const int_t scalar)
{
    a = a | scalar;
    return a;
}

export constexpr int3_t abs(const int3_t v)
{
    return int3_t{abs(v.x), abs(v.y), abs(v.z)};
}

export constexpr int3_t clamp(
    const int3_t v, const int3_t lower, const int3_t upper)
{
    FND_ASSERT(all(lower <= upper));

    return int3_t{clamp(v.x, lower.x, upper.x), clamp(v.y, lower.y, upper.y),
        clamp(v.z, lower.z, upper.z)};
}

export constexpr int3_t clamp(
    const int3_t v, const int3_t lower, const int_t upper)
{
    FND_ASSERT(all(lower <= upper));

    return int3_t{clamp(v.x, lower.x, upper), clamp(v.y, lower.y, upper),
        clamp(v.z, lower.z, upper)};
}

export constexpr int3_t clamp(
    const int3_t v, const int_t lower, const int3_t upper)
{
    FND_ASSERT(all(lower <= upper));

    return int3_t{clamp(v.x, lower, upper.x), clamp(v.y, lower, upper.y),
        clamp(v.z, lower, upper.z)};
}

export constexpr int3_t clamp(
    const int3_t v, const int_t lower, const int_t upper)
{
    FND_ASSERT(lower <= upper);

    return int3_t{clamp(v.x, lower, upper), clamp(v.y, lower, upper),
        clamp(v.z, lower, upper)};
}

export constexpr int_t cmax(const int3_t v)
{
    return max(max(v.x, v.y), v.z);
}

export constexpr int_t cmin(const int3_t v)
{
    return min(min(v.x, v.y), v.z);
}

export constexpr int_t cmul(const int3_t v)
{
    FND_ASSERT(
        long_t{v.x} * v.y >= kIntMinValue && long_t{v.x} * v.y <= kIntMaxValue);

    const int_t partial1 = v.x * v.y;
    FND_ASSERT(long_t{partial1} * v.z >= kIntMinValue
        && long_t{partial1} * v.z <= kIntMaxValue);

    return partial1 * v.z;
}

export constexpr int_t csum(const int3_t v)
{
    FND_ASSERT(
        long_t{v.x} + v.y >= kIntMinValue && long_t{v.x} + v.y <= kIntMaxValue);

    const int_t partial1 = v.x + v.y;
    FND_ASSERT(long_t{partial1} + v.z >= kIntMinValue
        && long_t{partial1} + v.z <= kIntMaxValue);

    return partial1 + v.z;
}

export constexpr int3_t max(const int3_t a, const int3_t b)
{
    return int3_t{max(a.x, b.x), max(a.y, b.y), max(a.z, b.z)};
}

export constexpr int3_t max(const int3_t a, const int_t scalar)
{
    return int3_t{max(a.x, scalar), max(a.y, scalar), max(a.z, scalar)};
}

export constexpr int3_t max(const int_t scalar, const int3_t b)
{
    return int3_t{max(scalar, b.x), max(scalar, b.y), max(scalar, b.z)};
}

export constexpr int3_t min(const int3_t a, const int3_t b)
{
    return int3_t{min(a.x, b.x), min(a.y, b.y), min(a.z, b.z)};
}

export constexpr int3_t min(const int3_t a, const int_t scalar)
{
    return int3_t{min(a.x, scalar), min(a.y, scalar), min(a.z, scalar)};
}

export constexpr int3_t min(const int_t scalar, const int3_t b)
{
    return int3_t{min(scalar, b.x), min(scalar, b.y), min(scalar, b.z)};
}

export constexpr int3_t sign(const int3_t v)
{
    return int3_t{sign(v.x), sign(v.y), sign(v.z)};
}

} // namespace fnd
