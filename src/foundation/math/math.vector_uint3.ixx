module;
#include "foundation/core/macros.h"

export module foundation.math:vector_uint3;
import foundation.core;
import :vector_bool;
import :vector_uint2;

namespace fnd {

export struct uint3_t final {
    uint_t x{0};
    uint_t y{0};
    uint_t z{0};

    constexpr uint3_t() = default;

    constexpr explicit uint3_t(const bool2_t v2, const uint_t z = 0)
        : x{v2.x}, y{v2.y}, z{z}
    {
    }

    constexpr explicit uint3_t(const bool3_t v3) : x{v3.x}, y{v3.y}, z{v3.z} {}

    constexpr explicit uint3_t(const uint_t val) : x{val}, y{val}, z{val} {}

    constexpr explicit uint3_t(const uint2_t v2, const uint_t z = 0)
        : x{v2.x}, y{v2.y}, z{z}
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

    constexpr uint3_t& operator+=(const uint_t val)
    {
        x += val;
        y += val;
        z += val;
        return *this;
    }

    constexpr uint3_t& operator+=(const int_t val)
    {
        FND_ASSERT(val >= 0);

        x += val;
        y += val;
        z += val;
        return *this;
    }

    constexpr uint3_t& operator-=(const uint3_t b)
    {
        x -= b.x;
        y -= b.y;
        z -= b.z;
        return *this;
    }

    constexpr uint3_t& operator-=(const uint_t val)
    {
        x -= val;
        y -= val;
        z -= val;
        return *this;
    }

    constexpr uint3_t& operator-=(const int_t val)
    {
        FND_ASSERT(val >= 0);

        x -= val;
        y -= val;
        z -= val;
        return *this;
    }

    constexpr uint3_t& operator*=(const uint3_t b)
    {
        x *= b.x;
        y *= b.y;
        z *= b.z;
        return *this;
    }

    constexpr uint3_t& operator*=(const uint_t val)
    {
        x *= val;
        y *= val;
        z *= val;
        return *this;
    }

    constexpr uint3_t& operator*=(const int_t val)
    {
        FND_ASSERT(val >= 0);

        x *= val;
        y *= val;
        z *= val;
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

    constexpr uint3_t& operator/=(const uint_t val)
    {
        FND_ASSERT(val != 0);

        x /= val;
        y /= val;
        z /= val;
        return *this;
    }

    constexpr uint3_t& operator/=(const int_t val)
    {
        FND_ASSERT(val > 0);

        x /= val;
        y /= val;
        z /= val;
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

    constexpr uint3_t& operator%=(const uint_t val)
    {
        FND_ASSERT(val != 0);

        x %= val;
        y %= val;
        z %= val;
        return *this;
    }

    constexpr uint3_t& operator%=(const int_t val)
    {
        FND_ASSERT(val > 0);

        x %= val;
        y %= val;
        z %= val;
        return *this;
    }

    constexpr uint3_t& operator&=(const uint3_t b)
    {
        x &= b.x;
        y &= b.y;
        z &= b.z;
        return *this;
    }

    constexpr uint3_t& operator&=(const uint_t val)
    {
        x &= val;
        y &= val;
        z &= val;
        return *this;
    }

    constexpr uint3_t& operator&=(const int_t val)
    {
        FND_ASSERT(val >= 0);

        x &= val;
        y &= val;
        z &= val;
        return *this;
    }

    constexpr uint3_t& operator|=(const uint3_t b)
    {
        x |= b.x;
        y |= b.y;
        z |= b.z;
        return *this;
    }

    constexpr uint3_t& operator|=(const uint_t val)
    {
        x |= val;
        y |= val;
        z |= val;
        return *this;
    }

    constexpr uint3_t& operator|=(const int_t val)
    {
        FND_ASSERT(val >= 0);

        x |= val;
        y |= val;
        z |= val;
        return *this;
    }

    constexpr uint3_t& operator^=(const uint3_t b)
    {
        x ^= b.x;
        y ^= b.y;
        z ^= b.z;
        return *this;
    }

    constexpr uint3_t& operator^=(const uint_t val)
    {
        x ^= val;
        y ^= val;
        z ^= val;
        return *this;
    }

    constexpr uint3_t& operator^=(const int_t val)
    {
        FND_ASSERT(val >= 0);

        x ^= val;
        y ^= val;
        z ^= val;
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

    constexpr uint3_t& operator<<=(const uint_t val)
    {
        FND_ASSERT(val < 32);

        x <<= val;
        y <<= val;
        z <<= val;
        return *this;
    }

    constexpr uint3_t& operator<<=(const int_t val)
    {
        FND_ASSERT(val >= 0 && val < 32);

        x <<= val;
        y <<= val;
        z <<= val;
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

    constexpr uint3_t& operator>>=(const uint_t val)
    {
        FND_ASSERT(val < 32);

        x >>= val;
        y >>= val;
        z >>= val;
        return *this;
    }

    constexpr uint3_t& operator>>=(const int_t val)
    {
        FND_ASSERT(val >= 0 && val < 32);

        x >>= val;
        y >>= val;
        z >>= val;
        return *this;
    }
};

export constexpr bool3_t operator==(const uint3_t a, const uint3_t b)
{
    return bool3_t{a.x == b.x, a.y == b.y, a.z == b.z};
}

export constexpr bool3_t operator==(const uint3_t a, const uint_t val)
{
    return bool3_t{a.x == val, a.y == val, a.z == val};
}

export constexpr bool3_t operator==(const uint_t val, const uint3_t b)
{
    return bool3_t{val == b.x, val == b.y, val == b.z};
}

export constexpr bool3_t operator==(const uint3_t a, const int_t val)
{
    FND_ASSERT(val >= 0);

    const uint_t uval = static_cast<uint_t>(val);
    return bool3_t{a.x == uval, a.y == uval, a.z == uval};
}

export constexpr bool3_t operator==(const int_t val, const uint3_t b)
{
    FND_ASSERT(val >= 0);

    const uint_t uval = static_cast<uint_t>(val);
    return bool3_t{uval == b.x, uval == b.y, uval == b.z};
}

export constexpr bool3_t operator!=(const uint3_t a, const uint3_t b)
{
    return !(a == b);
}

export constexpr bool3_t operator!=(const uint3_t a, const uint_t val)
{
    return !(a == val);
}

export constexpr bool3_t operator!=(const uint_t val, const uint3_t b)
{
    return !(val == b);
}

export constexpr bool3_t operator!=(const uint3_t a, const int_t val)
{
    return !(a == val);
}

export constexpr bool3_t operator!=(const int_t val, const uint3_t b)
{
    return !(val == b);
}

export constexpr bool3_t operator<(const uint3_t a, const uint3_t b)
{
    return bool3_t{a.x < b.x, a.y < b.y, a.z < b.z};
}

export constexpr bool3_t operator<(const uint3_t a, const uint_t val)
{
    return bool3_t{a.x < val, a.y < val, a.z < val};
}

export constexpr bool3_t operator<(const uint_t val, const uint3_t b)
{
    return bool3_t{val < b.x, val < b.y, val < b.z};
}

export constexpr bool3_t operator<(const uint3_t a, const int_t val)
{
    FND_ASSERT(val >= 0);

    const uint_t uval = static_cast<uint_t>(val);
    return bool3_t{a.x < uval, a.y < uval, a.z < uval};
}

export constexpr bool3_t operator<(const int_t val, const uint3_t b)
{
    FND_ASSERT(val >= 0);

    const uint_t uval = static_cast<uint_t>(val);
    return bool3_t{uval < b.x, uval < b.y, uval < b.z};
}

export constexpr bool3_t operator<=(const uint3_t a, const uint3_t b)
{
    return bool3_t{a.x <= b.x, a.y <= b.y, a.z <= b.z};
}

export constexpr bool3_t operator<=(const uint3_t a, const uint_t val)
{
    return bool3_t{a.x <= val, a.y <= val, a.z <= val};
}

export constexpr bool3_t operator<=(const uint_t val, const uint3_t b)
{
    return bool3_t{val <= b.x, val <= b.y, val <= b.z};
}

export constexpr bool3_t operator<=(const uint3_t a, const int_t val)
{
    FND_ASSERT(val >= 0);

    const uint_t uval = static_cast<uint_t>(val);
    return bool3_t{a.x <= uval, a.y <= uval, a.z <= uval};
}

export constexpr bool3_t operator<=(const int_t val, const uint3_t b)
{
    FND_ASSERT(val >= 0);

    const uint_t uval = static_cast<uint_t>(val);
    return bool3_t{uval <= b.x, uval <= b.y, uval <= b.z};
}

export constexpr bool3_t operator>(const uint3_t a, const uint3_t b)
{
    return bool3_t{a.x > b.x, a.y > b.y, a.z > b.z};
}

export constexpr bool3_t operator>(const uint3_t a, const uint_t val)
{
    return bool3_t{a.x > val, a.y > val, a.z > val};
}

export constexpr bool3_t operator>(const uint_t val, const uint3_t b)
{
    return bool3_t{val > b.x, val > b.y, val > b.z};
}

export constexpr bool3_t operator>(const uint3_t a, const int_t val)
{
    FND_ASSERT(val >= 0);

    const uint_t uval = static_cast<uint_t>(val);
    return bool3_t{a.x > uval, a.y > uval, a.z > uval};
}

export constexpr bool3_t operator>(const int_t val, const uint3_t b)
{
    FND_ASSERT(val >= 0);

    const uint_t uval = static_cast<uint_t>(val);
    return bool3_t{uval > b.x, uval > b.y, uval > b.z};
}

export constexpr bool3_t operator>=(const uint3_t a, const uint3_t b)
{
    return bool3_t{a.x >= b.x, a.y >= b.y, a.z >= b.z};
}

export constexpr bool3_t operator>=(const uint3_t a, const uint_t val)
{
    return bool3_t{a.x >= val, a.y >= val, a.z >= val};
}

export constexpr bool3_t operator>=(const uint_t val, const uint3_t b)
{
    return bool3_t{val >= b.x, val >= b.y, val >= b.z};
}

export constexpr bool3_t operator>=(const uint3_t a, const int_t val)
{
    FND_ASSERT(val >= 0);

    const uint_t uval = static_cast<uint_t>(val);
    return bool3_t{a.x >= uval, a.y >= uval, a.z >= uval};
}

export constexpr bool3_t operator>=(const int_t val, const uint3_t b)
{
    FND_ASSERT(val >= 0);

    const uint_t uval = static_cast<uint_t>(val);
    return bool3_t{uval >= b.x, uval >= b.y, uval >= b.z};
}

export constexpr uint3_t operator&(const uint3_t a, const uint3_t b)
{
    return uint3_t{a.x & b.x, a.y & b.y, a.z & b.z};
}

export constexpr uint3_t operator&(const uint3_t a, const uint_t val)
{
    return uint3_t{a.x & val, a.y & val, a.z & val};
}

export constexpr uint3_t operator&(const uint_t val, const uint3_t b)
{
    return uint3_t{val & b.x, val & b.y, val & b.z};
}

export constexpr uint3_t operator&(const uint3_t a, const int_t val)
{
    FND_ASSERT(val >= 0);

    return uint3_t{a.x & val, a.y & val, a.z & val};
}

export constexpr uint3_t operator&(const int_t val, const uint3_t b)
{
    FND_ASSERT(val >= 0);

    return uint3_t{val & b.x, val & b.y, val & b.z};
}

export constexpr uint3_t operator*(const uint3_t a, const uint3_t b)
{
    return uint3_t{a.x * b.x, a.y * b.y, a.z * b.z};
}

export constexpr uint3_t operator*(const uint3_t a, const uint_t val)
{
    return uint3_t{a.x * val, a.y * val, a.z * val};
}

export constexpr uint3_t operator*(const uint_t val, const uint3_t b)
{
    return uint3_t{val * b.x, val * b.y, val * b.z};
}

export constexpr uint3_t operator*(const uint3_t a, const int_t val)
{
    FND_ASSERT(val >= 0);

    return uint3_t{a.x * val, a.y * val, a.z * val};
}

export constexpr uint3_t operator*(const int_t val, const uint3_t b)
{
    FND_ASSERT(val >= 0);

    return uint3_t{val * b.x, val * b.y, val * b.z};
}

export constexpr uint3_t operator+(const uint3_t a, const uint3_t b)
{
    return uint3_t{a.x + b.x, a.y + b.y, a.z + b.z};
}

export constexpr uint3_t operator+(const uint3_t a, const uint_t val)
{
    return uint3_t{a.x + val, a.y + val, a.z + val};
}

export constexpr uint3_t operator+(const uint_t val, const uint3_t b)
{
    return uint3_t{val + b.x, val + b.y, val + b.z};
}

export constexpr uint3_t operator+(const uint3_t a, const int_t val)
{
    FND_ASSERT(val >= 0);

    return uint3_t{a.x + val, a.y + val, a.z + val};
}

export constexpr uint3_t operator+(const int_t val, const uint3_t b)
{
    FND_ASSERT(val >= 0);

    return uint3_t{val + b.x, val + b.y, val + b.z};
}

export constexpr uint3_t operator-(const uint3_t a, const uint3_t b)
{
    return uint3_t{a.x - b.x, a.y - b.y, a.z - b.z};
}

export constexpr uint3_t operator-(const uint3_t a, const uint_t val)
{
    return uint3_t{a.x - val, a.y - val, a.z - val};
}

export constexpr uint3_t operator-(const uint_t val, const uint3_t b)
{
    return uint3_t{val - b.x, val - b.y, val - b.z};
}

export constexpr uint3_t operator-(const uint3_t a, const int_t val)
{
    FND_ASSERT(val >= 0);

    return uint3_t{a.x - val, a.y - val, a.z - val};
}

export constexpr uint3_t operator-(const int_t val, const uint3_t b)
{
    FND_ASSERT(val >= 0);

    return uint3_t{val - b.x, val - b.y, val - b.z};
}

export constexpr uint3_t operator%(const uint3_t a, const uint3_t b)
{
    FND_ASSERT(all(b != 0u));

    return uint3_t{a.x % b.x, a.y % b.y, a.z % b.z};
}

export constexpr uint3_t operator%(const uint3_t a, const uint_t val)
{
    FND_ASSERT(val != 0);

    return uint3_t{a.x % val, a.y % val, a.z % val};
}

export constexpr uint3_t operator%(const uint_t val, const uint3_t b)
{
    FND_ASSERT(all(b != 0u));

    return uint3_t{val % b.x, val % b.y, val % b.z};
}

export constexpr uint3_t operator%(const uint3_t a, const int_t val)
{
    FND_ASSERT(val > 0);

    return uint3_t{a.x % val, a.y % val, a.z % val};
}

export constexpr uint3_t operator%(const int_t val, const uint3_t b)
{
    FND_ASSERT(val >= 0);
    FND_ASSERT(all(b != 0u));

    return uint3_t{val % b.x, val % b.y, val % b.z};
}

export constexpr uint3_t operator/(const uint3_t a, const uint3_t b)
{
    FND_ASSERT(all(b != 0u));

    return uint3_t{a.x / b.x, a.y / b.y, a.z / b.z};
}

export constexpr uint3_t operator/(const uint3_t a, const uint_t val)
{
    FND_ASSERT(val != 0);

    return uint3_t{a.x / val, a.y / val, a.z / val};
}

export constexpr uint3_t operator/(const uint_t val, const uint3_t b)
{
    FND_ASSERT(all(b != 0u));

    return uint3_t{val / b.x, val / b.y, val / b.z};
}

export constexpr uint3_t operator/(const uint3_t a, const int_t val)
{
    FND_ASSERT(val > 0);

    return uint3_t{a.x / val, a.y / val, a.z / val};
}

export constexpr uint3_t operator/(const int_t val, const uint3_t b)
{
    FND_ASSERT(val >= 0);
    FND_ASSERT(all(b != 0u));

    return uint3_t{val / b.x, val / b.y, val / b.z};
}

export constexpr uint3_t operator<<(const uint3_t a, const uint3_t b)
{
    FND_ASSERT(all(b < 32u));

    return uint3_t{a.x << b.x, a.y << b.y, a.z << b.z};
}

export constexpr uint3_t operator<<(const uint3_t a, const uint_t val)
{
    FND_ASSERT(val < 32);

    return uint3_t{a.x << val, a.y << val, a.z << val};
}

export constexpr uint3_t operator<<(const uint_t val, const uint3_t b)
{
    FND_ASSERT(all(b < 32u));

    return uint3_t{val << b.x, val << b.y, val << b.z};
}

export constexpr uint3_t operator<<(const uint3_t a, const int_t val)
{
    FND_ASSERT(val >= 0 && val < 32);

    return uint3_t{a.x << val, a.y << val, a.z << val};
}

export constexpr uint3_t operator<<(const int_t val, const uint3_t b)
{
    FND_ASSERT(val >= 0);
    FND_ASSERT(all(b < 32u));

    const uint_t uval = static_cast<uint_t>(val);
    return uint3_t{uval << b.x, uval << b.y, uval << b.z};
}

export constexpr uint3_t operator>>(const uint3_t a, const uint3_t b)
{
    FND_ASSERT(all(b < 32u));

    return uint3_t{a.x >> b.x, a.y >> b.y, a.z >> b.z};
}

export constexpr uint3_t operator>>(const uint3_t a, const uint_t val)
{
    FND_ASSERT(val < 32);

    return uint3_t{a.x >> val, a.y >> val, a.z >> val};
}

export constexpr uint3_t operator>>(const uint_t val, const uint3_t b)
{
    FND_ASSERT(all(b < 32u));

    return uint3_t{val >> b.x, val >> b.y, val >> b.z};
}

export constexpr uint3_t operator>>(const uint3_t a, const int_t val)
{
    FND_ASSERT(val >= 0 && val < 32);

    return uint3_t{a.x >> val, a.y >> val, a.z >> val};
}

export constexpr uint3_t operator>>(const int_t val, const uint3_t b)
{
    FND_ASSERT(val >= 0);
    FND_ASSERT(all(b < 32u));

    const uint_t uval = static_cast<uint_t>(val);
    return uint3_t{uval >> b.x, uval >> b.y, uval >> b.z};
}

export constexpr uint3_t operator^(const uint3_t a, const uint3_t b)
{
    return uint3_t{a.x ^ b.x, a.y ^ b.y, a.z ^ b.z};
}

export constexpr uint3_t operator^(const uint3_t a, const uint_t val)
{
    return uint3_t{a.x ^ val, a.y ^ val, a.z ^ val};
}

export constexpr uint3_t operator^(const uint_t val, const uint3_t b)
{
    return uint3_t{val ^ b.x, val ^ b.y, val ^ b.z};
}

export constexpr uint3_t operator^(const uint3_t a, const int_t val)
{
    FND_ASSERT(val >= 0);

    return uint3_t{a.x ^ val, a.y ^ val, a.z ^ val};
}

export constexpr uint3_t operator^(const int_t val, const uint3_t b)
{
    FND_ASSERT(val >= 0);

    return uint3_t{val ^ b.x, val ^ b.y, val ^ b.z};
}

export constexpr uint3_t operator|(const uint3_t a, const uint3_t b)
{
    return uint3_t{a.x | b.x, a.y | b.y, a.z | b.z};
}

export constexpr uint3_t operator|(const uint3_t a, const uint_t val)
{
    return uint3_t{a.x | val, a.y | val, a.z | val};
}

export constexpr uint3_t operator|(const uint_t val, const uint3_t b)
{
    return uint3_t{val | b.x, val | b.y, val | b.z};
}

export constexpr uint3_t operator|(const uint3_t a, const int_t val)
{
    FND_ASSERT(val >= 0);

    return uint3_t{a.x | val, a.y | val, a.z | val};
}

export constexpr uint3_t operator|(const int_t val, const uint3_t b)
{
    FND_ASSERT(val >= 0);

    return uint3_t{val | b.x, val | b.y, val | b.z};
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

export constexpr uint3_t max(const uint3_t a, const uint_t val)
{
    return uint3_t{max(a.x, val), max(a.y, val), max(a.z, val)};
}

export constexpr uint3_t max(const uint_t val, const uint3_t b)
{
    return uint3_t{max(val, b.x), max(val, b.y), max(val, b.z)};
}

export constexpr uint3_t min(const uint3_t a, const uint3_t b)
{
    return uint3_t{min(a.x, b.x), min(a.y, b.y), min(a.z, b.z)};
}

export constexpr uint3_t min(const uint3_t a, const uint_t val)
{
    return uint3_t{min(a.x, val), min(a.y, val), min(a.z, val)};
}

export constexpr uint3_t min(const uint_t val, const uint3_t b)
{
    return uint3_t{min(val, b.x), min(val, b.y), min(val, b.z)};
}

} // namespace fnd
