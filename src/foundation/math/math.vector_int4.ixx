module;
#include "foundation/core/macros.h"

export module foundation.math:vector_int4;
import foundation.core;
import :vector_bool;
import :vector_int2;
import :vector_int3;

namespace fnd {

export struct int4_t final {
    int_t x{0};
    int_t y{0};
    int_t z{0};
    int_t w{0};

    constexpr int4_t() = default;

    constexpr explicit int4_t(
        const bool2_t v2, const int_t z = 0, const int_t w = 0)
        : x{v2.x}, y{v2.y}, z{z}, w{w}
    {
    }

    constexpr explicit int4_t(const bool4_t v4)
        : x{v4.x}, y{v4.y}, z{v4.z}, w{v4.w}
    {
    }

    constexpr explicit int4_t(const int_t val) : x{val}, y{val}, z{val}, w{val}
    {
    }

    constexpr explicit int4_t(
        const int2_t v2, const int_t z = 0, const int_t w = 0)
        : x{v2.x}, y{v2.y}, z{z}, w{w}
    {
    }

    constexpr explicit int4_t(const int3_t v3, const int_t w = 0)
        : x{v3.x}, y{v3.y}, z{v3.z}, w{w}
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

    constexpr int4_t& operator+=(const int_t val)
    {
        FND_ASSERT(
            long_t{x} + val >= kIntMinValue && long_t{x} + val <= kIntMaxValue);
        FND_ASSERT(
            long_t{y} + val >= kIntMinValue && long_t{y} + val <= kIntMaxValue);
        FND_ASSERT(
            long_t{z} + val >= kIntMinValue && long_t{z} + val <= kIntMaxValue);
        FND_ASSERT(
            long_t{w} + val >= kIntMinValue && long_t{w} + val <= kIntMaxValue);

        x += val;
        y += val;
        z += val;
        w += val;
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

    constexpr int4_t& operator-=(const int_t val)
    {
        FND_ASSERT(
            long_t{x} - val >= kIntMinValue && long_t{x} - val <= kIntMaxValue);
        FND_ASSERT(
            long_t{y} - val >= kIntMinValue && long_t{y} - val <= kIntMaxValue);
        FND_ASSERT(
            long_t{z} - val >= kIntMinValue && long_t{z} - val <= kIntMaxValue);
        FND_ASSERT(
            long_t{w} - val >= kIntMinValue && long_t{w} - val <= kIntMaxValue);

        x -= val;
        y -= val;
        z -= val;
        w -= val;
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

    constexpr int4_t& operator*=(const int_t val)
    {
        FND_ASSERT(
            long_t{x} * val >= kIntMinValue && long_t{x} * val <= kIntMaxValue);
        FND_ASSERT(
            long_t{y} * val >= kIntMinValue && long_t{y} * val <= kIntMaxValue);
        FND_ASSERT(
            long_t{z} * val >= kIntMinValue && long_t{z} * val <= kIntMaxValue);
        FND_ASSERT(
            long_t{w} * val >= kIntMinValue && long_t{w} * val <= kIntMaxValue);

        x *= val;
        y *= val;
        z *= val;
        w *= val;
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

    constexpr int4_t& operator/=(const int_t val)
    {
        FND_ASSERT(val != 0);
        FND_ASSERT(!(val == -1 && x == kIntMinValue));
        FND_ASSERT(!(val == -1 && y == kIntMinValue));
        FND_ASSERT(!(val == -1 && z == kIntMinValue));
        FND_ASSERT(!(val == -1 && w == kIntMinValue));

        x /= val;
        y /= val;
        z /= val;
        w /= val;
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

    constexpr int4_t& operator%=(const int_t val)
    {
        FND_ASSERT(val != 0);
        FND_ASSERT(!(val == -1 && x == kIntMinValue));
        FND_ASSERT(!(val == -1 && y == kIntMinValue));
        FND_ASSERT(!(val == -1 && z == kIntMinValue));
        FND_ASSERT(!(val == -1 && w == kIntMinValue));

        x %= val;
        y %= val;
        z %= val;
        w %= val;
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

    constexpr int4_t& operator&=(const int_t val)
    {
        x &= val;
        y &= val;
        z &= val;
        w &= val;
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

    constexpr int4_t& operator|=(const int_t val)
    {
        x |= val;
        y |= val;
        z |= val;
        w |= val;
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

    constexpr int4_t& operator^=(const int_t val)
    {
        x ^= val;
        y ^= val;
        z ^= val;
        w ^= val;
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

    constexpr int4_t& operator<<=(const int_t val)
    {
        FND_ASSERT(val >= 0 && val < 32);

        x <<= val;
        y <<= val;
        z <<= val;
        w <<= val;
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

    constexpr int4_t& operator>>=(const int_t val)
    {
        FND_ASSERT(val >= 0 && val < 32);

        x >>= val;
        y >>= val;
        z >>= val;
        w >>= val;
        return *this;
    }
};

export constexpr bool4_t operator==(const int4_t a, const int4_t b)
{
    return bool4_t{a.x == b.x, a.y == b.y, a.z == b.z, a.w == b.w};
}

export constexpr bool4_t operator!=(const int4_t a, const int4_t b)
{
    return !(a == b);
}

export constexpr bool4_t operator==(const int4_t a, const int_t val)
{
    return bool4_t{a.x == val, a.y == val, a.z == val, a.w == val};
}

export constexpr bool4_t operator!=(const int4_t a, const int_t val)
{
    return !(a == val);
}

export constexpr bool4_t operator==(const int_t val, const int4_t b)
{
    return bool4_t{val == b.x, val == b.y, val == b.z, val == b.w};
}

export constexpr bool4_t operator!=(const int_t val, const int4_t b)
{
    return !(val == b);
}

export constexpr bool4_t operator<(const int4_t a, const int4_t b)
{
    return bool4_t{a.x < b.x, a.y < b.y, a.z < b.z, a.w < b.w};
}

export constexpr bool4_t operator<(const int4_t a, const int_t val)
{
    return bool4_t{a.x < val, a.y < val, a.z < val, a.w < val};
}

export constexpr bool4_t operator<(const int_t val, const int4_t b)
{
    return bool4_t{val < b.x, val < b.y, val < b.z, val < b.w};
}

export constexpr bool4_t operator<=(const int4_t a, const int4_t b)
{
    return bool4_t{a.x <= b.x, a.y <= b.y, a.z <= b.z, a.w <= b.w};
}

export constexpr bool4_t operator<=(const int4_t a, const int_t val)
{
    return bool4_t{a.x <= val, a.y <= val, a.z <= val, a.w <= val};
}

export constexpr bool4_t operator<=(const int_t val, const int4_t b)
{
    return bool4_t{val <= b.x, val <= b.y, val <= b.z, val <= b.w};
}

export constexpr bool4_t operator>(const int4_t a, const int4_t b)
{
    return bool4_t{a.x > b.x, a.y > b.y, a.z > b.z, a.w > b.w};
}

export constexpr bool4_t operator>(const int4_t a, const int_t val)
{
    return bool4_t{a.x > val, a.y > val, a.z > val, a.w > val};
}

export constexpr bool4_t operator>(const int_t val, const int4_t b)
{
    return bool4_t{val > b.x, val > b.y, val > b.z, val > b.w};
}

export constexpr bool4_t operator>=(const int4_t a, const int4_t b)
{
    return bool4_t{a.x >= b.x, a.y >= b.y, a.z >= b.z, a.w >= b.w};
}

export constexpr bool4_t operator>=(const int4_t a, const int_t val)
{
    return bool4_t{a.x >= val, a.y >= val, a.z >= val, a.w >= val};
}

export constexpr bool4_t operator>=(const int_t val, const int4_t b)
{
    return bool4_t{val >= b.x, val >= b.y, val >= b.z, val >= b.w};
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

export constexpr int4_t operator+(const int4_t a, const int_t val)
{
    FND_ASSERT(
        long_t{a.x} + val >= kIntMinValue && long_t{a.x} + val <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.y} + val >= kIntMinValue && long_t{a.y} + val <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.z} + val >= kIntMinValue && long_t{a.z} + val <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.w} + val >= kIntMinValue && long_t{a.w} + val <= kIntMaxValue);

    return int4_t{a.x + val, a.y + val, a.z + val, a.w + val};
}

export constexpr int4_t operator+(const int_t val, const int4_t b)
{
    FND_ASSERT(
        long_t{val} + b.x >= kIntMinValue && long_t{val} + b.x <= kIntMaxValue);
    FND_ASSERT(
        long_t{val} + b.y >= kIntMinValue && long_t{val} + b.y <= kIntMaxValue);
    FND_ASSERT(
        long_t{val} + b.z >= kIntMinValue && long_t{val} + b.z <= kIntMaxValue);
    FND_ASSERT(
        long_t{val} + b.w >= kIntMinValue && long_t{val} + b.w <= kIntMaxValue);

    return int4_t{val + b.x, val + b.y, val + b.z, val + b.w};
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

export constexpr int4_t operator-(const int4_t a, const int_t val)
{
    FND_ASSERT(
        long_t{a.x} - val >= kIntMinValue && long_t{a.x} - val <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.y} - val >= kIntMinValue && long_t{a.y} - val <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.z} - val >= kIntMinValue && long_t{a.z} - val <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.w} - val >= kIntMinValue && long_t{a.w} - val <= kIntMaxValue);

    return int4_t{a.x - val, a.y - val, a.z - val, a.w - val};
}

export constexpr int4_t operator-(const int_t val, const int4_t b)
{
    FND_ASSERT(
        long_t{val} - b.x >= kIntMinValue && long_t{val} - b.x <= kIntMaxValue);
    FND_ASSERT(
        long_t{val} - b.y >= kIntMinValue && long_t{val} - b.y <= kIntMaxValue);
    FND_ASSERT(
        long_t{val} - b.z >= kIntMinValue && long_t{val} - b.z <= kIntMaxValue);
    FND_ASSERT(
        long_t{val} - b.w >= kIntMinValue && long_t{val} - b.w <= kIntMaxValue);

    return int4_t{val - b.x, val - b.y, val - b.z, val - b.w};
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

export constexpr int4_t operator*(const int4_t a, const int_t val)
{
    FND_ASSERT(
        long_t{a.x} * val >= kIntMinValue && long_t{a.x} * val <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.y} * val >= kIntMinValue && long_t{a.y} * val <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.z} * val >= kIntMinValue && long_t{a.z} * val <= kIntMaxValue);
    FND_ASSERT(
        long_t{a.w} * val >= kIntMinValue && long_t{a.w} * val <= kIntMaxValue);

    return int4_t{a.x * val, a.y * val, a.z * val, a.w * val};
}

export constexpr int4_t operator*(const int_t val, const int4_t b)
{
    FND_ASSERT(
        long_t{val} * b.x >= kIntMinValue && long_t{val} * b.x <= kIntMaxValue);
    FND_ASSERT(
        long_t{val} * b.y >= kIntMinValue && long_t{val} * b.y <= kIntMaxValue);
    FND_ASSERT(
        long_t{val} * b.z >= kIntMinValue && long_t{val} * b.z <= kIntMaxValue);
    FND_ASSERT(
        long_t{val} * b.w >= kIntMinValue && long_t{val} * b.w <= kIntMaxValue);

    return int4_t{val * b.x, val * b.y, val * b.z, val * b.w};
}

export constexpr int4_t operator/(const int4_t a, const int4_t b)
{
    FND_ASSERT(all(b != 0));
    FND_ASSERT(!any(a == kIntMinValue && b == -1));

    return int4_t{a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w};
}

export constexpr int4_t operator/(const int4_t a, const int_t val)
{
    FND_ASSERT(val != 0);
    FND_ASSERT(!(val == -1 && any(a == kIntMinValue)));

    return int4_t{a.x / val, a.y / val, a.z / val, a.w / val};
}

export constexpr int4_t operator/(const int_t val, const int4_t b)
{
    FND_ASSERT(all(b != 0));
    FND_ASSERT(!(val == kIntMinValue && any(b == -1)));

    return int4_t{val / b.x, val / b.y, val / b.z, val / b.w};
}

export constexpr int4_t operator%(const int4_t a, const int4_t b)
{
    FND_ASSERT(all(b != 0));
    FND_ASSERT(!any(a == kIntMinValue && b == -1));

    return int4_t{a.x % b.x, a.y % b.y, a.z % b.z, a.w % b.w};
}

export constexpr int4_t operator%(const int4_t a, const int_t val)
{
    FND_ASSERT(val != 0);
    FND_ASSERT(!(val == -1 && any(a == kIntMinValue)));

    return int4_t{a.x % val, a.y % val, a.z % val, a.w % val};
}

export constexpr int4_t operator%(const int_t val, const int4_t b)
{
    FND_ASSERT(all(b != 0));
    FND_ASSERT(!(val == kIntMinValue && any(b == -1)));

    return int4_t{val % b.x, val % b.y, val % b.z, val % b.w};
}

export constexpr int4_t operator&(const int4_t a, const int4_t b)
{
    return int4_t{a.x & b.x, a.y & b.y, a.z & b.z, a.w & b.w};
}

export constexpr int4_t operator&(const int4_t a, const int_t val)
{
    return int4_t{a.x & val, a.y & val, a.z & val, a.w & val};
}

export constexpr int4_t operator&(const int_t val, const int4_t b)
{
    return int4_t{val & b.x, val & b.y, val & b.z, val & b.w};
}

export constexpr int4_t operator|(const int4_t a, const int4_t b)
{
    return int4_t{a.x | b.x, a.y | b.y, a.z | b.z, a.w | b.w};
}

export constexpr int4_t operator|(const int4_t a, const int_t val)
{
    return int4_t{a.x | val, a.y | val, a.z | val, a.w | val};
}

export constexpr int4_t operator|(const int_t val, const int4_t b)
{
    return int4_t{val | b.x, val | b.y, val | b.z, val | b.w};
}

export constexpr int4_t operator^(const int4_t a, const int4_t b)
{
    return int4_t{a.x ^ b.x, a.y ^ b.y, a.z ^ b.z, a.w ^ b.w};
}

export constexpr int4_t operator^(const int4_t a, const int_t val)
{
    return int4_t{a.x ^ val, a.y ^ val, a.z ^ val, a.w ^ val};
}

export constexpr int4_t operator^(const int_t val, const int4_t b)
{
    return int4_t{val ^ b.x, val ^ b.y, val ^ b.z, val ^ b.w};
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

export constexpr int4_t operator<<(const int4_t a, const int_t val)
{
    FND_ASSERT(val >= 0 && val < 32);

    return int4_t{a.x << val, a.y << val, a.z << val, a.w << val};
}

export constexpr int4_t operator<<(const int_t val, const int4_t b)
{
    FND_ASSERT(all(b >= 0 && b < 32));

    return int4_t{val << b.x, val << b.y, val << b.z, val << b.w};
}

export constexpr int4_t operator>>(const int4_t a, const int4_t b)
{
    FND_ASSERT(all(b >= 0 && b < 32));

    return int4_t{a.x >> b.x, a.y >> b.y, a.z >> b.z, a.w >> b.w};
}

export constexpr int4_t operator>>(const int4_t a, const int_t val)
{
    FND_ASSERT(val >= 0 && val < 32);

    return int4_t{a.x >> val, a.y >> val, a.z >> val, a.w >> val};
}

export constexpr int4_t operator>>(const int_t val, const int4_t b)
{
    FND_ASSERT(all(b >= 0 && b < 32));

    return int4_t{val >> b.x, val >> b.y, val >> b.z, val >> b.w};
}

export constexpr int4_t abs(const int4_t v)
{
    return int4_t{abs(v.x), abs(v.y), abs(v.z), abs(v.w)};
}

export constexpr int4_t min(const int4_t a, const int4_t b)
{
    return int4_t{min(a.x, b.x), min(a.y, b.y), min(a.z, b.z), min(a.w, b.w)};
}

export constexpr int4_t min(const int4_t a, const int_t val)
{
    return int4_t{min(a.x, val), min(a.y, val), min(a.z, val), min(a.w, val)};
}

export constexpr int4_t min(const int_t val, const int4_t b)
{
    return int4_t{min(val, b.x), min(val, b.y), min(val, b.z), min(val, b.w)};
}

export constexpr int4_t max(const int4_t a, const int4_t b)
{
    return int4_t{max(a.x, b.x), max(a.y, b.y), max(a.z, b.z), max(a.w, b.w)};
}

export constexpr int4_t max(const int4_t a, const int_t val)
{
    return int4_t{max(a.x, val), max(a.y, val), max(a.z, val), max(a.w, val)};
}

export constexpr int4_t max(const int_t val, const int4_t b)
{
    return int4_t{max(val, b.x), max(val, b.y), max(val, b.z), max(val, b.w)};
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

export constexpr int4_t sign(const int4_t v)
{
    return int4_t{sign(v.x), sign(v.y), sign(v.z), sign(v.w)};
}

export constexpr int_t cmin(const int4_t v)
{
    return min(min(min(v.x, v.y), v.z), v.w);
}

export constexpr int_t cmax(const int4_t v)
{
    return max(max(max(v.x, v.y), v.z), v.w);
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

} // namespace fnd
