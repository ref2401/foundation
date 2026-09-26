module;
#include "foundation/core/macros.h"

export module foundation.math:vector_int;
import foundation.core;
import :scalar;
import :vector_bool;

namespace fnd {

export struct int2_t final {
    int_t x{0};
    int_t y{0};

    constexpr int2_t() = default;
    constexpr explicit int2_t(const bool2_t v2) : x{v2.x}, y{v2.y} {}
    constexpr explicit int2_t(const int_t val) : x{val}, y{val} {}
    constexpr int2_t(int_t x, int_t y) : x{x}, y{y} {}

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
};

export constexpr bool2_t operator==(const int2_t a, const int2_t b)
{
    return bool2_t{a.x == b.x, a.y == b.y};
}

export constexpr bool2_t operator!=(const int2_t a, const int2_t b)
{
    return !(a == b);
}

export constexpr bool2_t operator==(const int2_t a, const int_t val)
{
    return bool2_t{a.x == val, a.y == val};
}

export constexpr bool2_t operator!=(const int2_t a, const int_t val)
{
    return !(a == val);
}

export constexpr bool2_t operator==(const int_t val, const int2_t b)
{
    return bool2_t{val == b.x, val == b.y};
}

export constexpr bool2_t operator!=(const int_t val, const int2_t b)
{
    return !(val == b);
}

export constexpr bool2_t operator<(const int2_t a, const int2_t b)
{
    return bool2_t{a.x < b.x, a.y < b.y};
}

export constexpr bool2_t operator<(const int2_t a, const int_t val)
{
    return bool2_t{a.x < val, a.y < val};
}

export constexpr bool2_t operator<(const int_t val, const int2_t b)
{
    return bool2_t{val < b.x, val < b.y};
}

export constexpr bool2_t operator<=(const int2_t a, const int2_t b)
{
    return bool2_t{a.x <= b.x, a.y <= b.y};
}

export constexpr bool2_t operator<=(const int2_t a, const int_t val)
{
    return bool2_t{a.x <= val, a.y <= val};
}

export constexpr bool2_t operator<=(const int_t val, const int2_t b)
{
    return bool2_t{val <= b.x, val <= b.y};
}

export constexpr bool2_t operator>(const int2_t a, const int2_t b)
{
    return bool2_t{a.x > b.x, a.y > b.y};
}

export constexpr bool2_t operator>(const int2_t a, const int_t val)
{
    return bool2_t{a.x > val, a.y > val};
}

export constexpr bool2_t operator>(const int_t val, const int2_t b)
{
    return bool2_t{val > b.x, val > b.y};
}

export constexpr bool2_t operator>=(const int2_t a, const int2_t b)
{
    return bool2_t{a.x >= b.x, a.y >= b.y};
}

export constexpr bool2_t operator>=(const int2_t a, const int_t val)
{
    return bool2_t{a.x >= val, a.y >= val};
}

export constexpr bool2_t operator>=(const int_t val, const int2_t b)
{
    return bool2_t{val >= b.x, val >= b.y};
}

export constexpr int2_t operator+(const int2_t a, const int2_t b)
{
    FND_ASSERT(long_t{a.x} + b.x >= kIntMinValue && long_t{a.x} + b.x <= kIntMaxValue);
    FND_ASSERT(long_t{a.y} + b.y >= kIntMinValue && long_t{a.y} + b.y <= kIntMaxValue);

    return int2_t{a.x + b.x, a.y + b.y};
}

export constexpr int2_t operator+(const int2_t a, const int_t val)
{
    FND_ASSERT(long_t{a.x} + val >= kIntMinValue && long_t{a.x} + val <= kIntMaxValue);
    FND_ASSERT(long_t{a.y} + val >= kIntMinValue && long_t{a.y} + val <= kIntMaxValue);

    return int2_t{a.x + val, a.y + val};
}

export constexpr int2_t operator+(const int_t val, const int2_t b)
{
    FND_ASSERT(long_t{val} + b.x >= kIntMinValue && long_t{val} + b.x <= kIntMaxValue);
    FND_ASSERT(long_t{val} + b.y >= kIntMinValue && long_t{val} + b.y <= kIntMaxValue);

    return int2_t{val + b.x, val + b.y};
}

export constexpr int2_t operator-(const int2_t a, const int2_t b)
{
    FND_ASSERT(long_t{a.x} - b.x >= kIntMinValue && long_t{a.x} - b.x <= kIntMaxValue);
    FND_ASSERT(long_t{a.y} - b.y >= kIntMinValue && long_t{a.y} - b.y <= kIntMaxValue);

    return int2_t{a.x - b.x, a.y - b.y};
}

export constexpr int2_t operator-(const int2_t a, const int_t val)
{
    FND_ASSERT(long_t{a.x} - val >= kIntMinValue && long_t{a.x} - val <= kIntMaxValue);
    FND_ASSERT(long_t{a.y} - val >= kIntMinValue && long_t{a.y} - val <= kIntMaxValue);

    return int2_t{a.x - val, a.y - val};
}

export constexpr int2_t operator-(const int_t val, const int2_t b)
{
    FND_ASSERT(long_t{val} - b.x >= kIntMinValue && long_t{val} - b.x <= kIntMaxValue);
    FND_ASSERT(long_t{val} - b.y >= kIntMinValue && long_t{val} - b.y <= kIntMaxValue);

    return int2_t{val - b.x, val - b.y};
}

export constexpr int2_t operator*(const int2_t a, const int2_t b)
{
    FND_ASSERT(long_t{a.x} * b.x >= kIntMinValue && long_t{a.x} * b.x <= kIntMaxValue);
    FND_ASSERT(long_t{a.y} * b.y >= kIntMinValue && long_t{a.y} * b.y <= kIntMaxValue);

    return int2_t{a.x * b.x, a.y * b.y};
}

export constexpr int2_t operator*(const int2_t a, const int_t val)
{
    FND_ASSERT(long_t{a.x} * val >= kIntMinValue && long_t{a.x} * val <= kIntMaxValue);
    FND_ASSERT(long_t{a.y} * val >= kIntMinValue && long_t{a.y} * val <= kIntMaxValue);

    return int2_t{a.x * val, a.y * val};
}

export constexpr int2_t operator*(const int_t val, const int2_t b)
{
    FND_ASSERT(long_t{val} * b.x >= kIntMinValue && long_t{val} * b.x <= kIntMaxValue);
    FND_ASSERT(long_t{val} * b.y >= kIntMinValue && long_t{val} * b.y <= kIntMaxValue);

    return int2_t{val * b.x, val * b.y};
}

export constexpr int2_t operator/(const int2_t a, const int2_t b)
{
    FND_ASSERT(all(b != 0));
    FND_ASSERT(!any(a == kIntMinValue && b == -1));

    return int2_t{a.x / b.x, a.y / b.y};
}

export constexpr int2_t operator/(const int2_t a, const int_t val)
{
    FND_ASSERT(val != 0);
    FND_ASSERT(!(val == -1 && any(a == kIntMinValue)));

    return int2_t{a.x / val, a.y / val};
}

export constexpr int2_t operator/(const int_t val, const int2_t b)
{
    FND_ASSERT(all(b != 0));
    FND_ASSERT(!(val == kIntMinValue && any(b == -1)));

    return int2_t{val / b.x, val / b.y};
}

export constexpr int2_t operator%(const int2_t a, const int2_t b)
{
    FND_ASSERT(all(b != 0));
    FND_ASSERT(!any(a == kIntMinValue && b == -1));

    return int2_t{a.x % b.x, a.y % b.y};
}

export constexpr int2_t operator%(const int2_t a, const int_t val)
{
    FND_ASSERT(val != 0);
    FND_ASSERT(!(val == -1 && any(a == kIntMinValue)));

    return int2_t{a.x % val, a.y % val};
}

export constexpr int2_t operator%(const int_t val, const int2_t b)
{
    FND_ASSERT(all(b != 0));
    FND_ASSERT(!(val == kIntMinValue && any(b == -1)));

    return int2_t{val % b.x, val % b.y};
}

export constexpr int2_t operator&(const int2_t a, const int2_t b)
{
    return int2_t{a.x & b.x, a.y & b.y};
}

export constexpr int2_t operator&(const int2_t a, const int_t val)
{
    return int2_t{a.x & val, a.y & val};
}

export constexpr int2_t operator&(const int_t val, const int2_t b)
{
    return int2_t{val & b.x, val & b.y};
}

export constexpr int2_t operator|(const int2_t a, const int2_t b)
{
    return int2_t{a.x | b.x, a.y | b.y};
}

export constexpr int2_t operator|(const int2_t a, const int_t val)
{
    return int2_t{a.x | val, a.y | val};
}

export constexpr int2_t operator|(const int_t val, const int2_t b)
{
    return int2_t{val | b.x, val | b.y};
}

export constexpr int2_t operator^(const int2_t a, const int2_t b)
{
    return int2_t{a.x ^ b.x, a.y ^ b.y};
}

export constexpr int2_t operator^(const int2_t a, const int_t val)
{
    return int2_t{a.x ^ val, a.y ^ val};
}

export constexpr int2_t operator^(const int_t val, const int2_t b)
{
    return int2_t{val ^ b.x, val ^ b.y};
}

export constexpr int2_t operator<<(const int2_t a, const int2_t b)
{
    FND_ASSERT(all(b >= 0 && b < 32));

    return int2_t{a.x << b.x, a.y << b.y};
}

export constexpr int2_t operator<<(const int2_t a, const int_t val)
{
    FND_ASSERT(val >= 0 && val < 32);

    return int2_t{a.x << val, a.y << val};
}

export constexpr int2_t operator<<(const int_t val, const int2_t b)
{
    FND_ASSERT(all(b >= 0 && b < 32));

    return int2_t{val << b.x, val << b.y};
}

export constexpr int2_t operator>>(const int2_t a, const int2_t b)
{
    FND_ASSERT(all(b >= 0 && b < 32));

    return int2_t{a.x >> b.x, a.y >> b.y};
}

export constexpr int2_t operator>>(const int2_t a, const int_t val)
{
    FND_ASSERT(val >= 0 && val < 32);

    return int2_t{a.x >> val, a.y >> val};
}

export constexpr int2_t operator>>(const int_t val, const int2_t b)
{
    FND_ASSERT(all(b >= 0 && b < 32));

    return int2_t{val >> b.x, val >> b.y};
}

export constexpr int2_t& operator+=(int2_t& a, const int2_t b)
{
    a = a + b;
    return a;
}

export constexpr int2_t& operator+=(int2_t& a, const int_t val)
{
    a = a + val;
    return a;
}

export constexpr int2_t& operator-=(int2_t& a, const int2_t b)
{
    a = a - b;
    return a;
}

export constexpr int2_t& operator-=(int2_t& a, const int_t val)
{
    a = a - val;
    return a;
}

export constexpr int2_t& operator*=(int2_t& a, const int2_t b)
{
    a = a * b;
    return a;
}

export constexpr int2_t& operator*=(int2_t& a, const int_t val)
{
    a = a * val;
    return a;
}

export constexpr int2_t& operator/=(int2_t& a, const int2_t b)
{
    a = a / b;
    return a;
}

export constexpr int2_t& operator/=(int2_t& a, const int_t val)
{
    a = a / val;
    return a;
}

export constexpr int2_t& operator%=(int2_t& a, const int2_t b)
{
    a = a % b;
    return a;
}

export constexpr int2_t& operator%=(int2_t& a, const int_t val)
{
    a = a % val;
    return a;
}

export constexpr int2_t& operator&=(int2_t& a, const int2_t b)
{
    a = a & b;
    return a;
}

export constexpr int2_t& operator&=(int2_t& a, const int_t val)
{
    a = a & val;
    return a;
}

export constexpr int2_t& operator|=(int2_t& a, const int2_t b)
{
    a = a | b;
    return a;
}

export constexpr int2_t& operator|=(int2_t& a, const int_t val)
{
    a = a | val;
    return a;
}

export constexpr int2_t& operator^=(int2_t& a, const int2_t b)
{
    a = a ^ b;
    return a;
}

export constexpr int2_t& operator^=(int2_t& a, const int_t val)
{
    a = a ^ val;
    return a;
}

export constexpr int2_t& operator<<=(int2_t& a, const int2_t b)
{
    a = a << b;
    return a;
}

export constexpr int2_t& operator<<=(int2_t& a, const int_t val)
{
    a = a << val;
    return a;
}

export constexpr int2_t& operator>>=(int2_t& a, const int2_t b)
{
    a = a >> b;
    return a;
}

export constexpr int2_t& operator>>=(int2_t& a, const int_t val)
{
    a = a >> val;
    return a;
}

} // namespace fnd
