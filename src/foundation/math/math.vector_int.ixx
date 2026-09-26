module;
#include "foundation/core/macros.h"

export module foundation.math:vector_int;
import foundation.core;
import :vector_bool;

namespace fnd {

export struct int2_t final {
    int_t x{0};
    int_t y{0};

    constexpr int2_t() = default;
    constexpr explicit int2_t(const bool2_t v2) : x{v2.x}, y{v2.y} {}
    constexpr explicit int2_t(const int_t val) : x{val}, y{val} {}
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

// NOTE:
// operator<< does not check the result for overflow, unlike operator*. Since
// C++20 a left shift is defined for every value: the bits shifted out are
// discarded, so the result wraps modulo 2^32 (kIntMaxValue << 1 is -2).
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

export constexpr int2_t abs(const int2_t v)
{
    return int2_t{abs(v.x), abs(v.y)};
}

export constexpr int2_t min(const int2_t a, const int2_t b)
{
    return int2_t{min(a.x, b.x), min(a.y, b.y)};
}

export constexpr int2_t min(const int2_t a, const int_t val)
{
    return int2_t{min(a.x, val), min(a.y, val)};
}

export constexpr int2_t min(const int_t val, const int2_t b)
{
    return int2_t{min(val, b.x), min(val, b.y)};
}

export constexpr int2_t max(const int2_t a, const int2_t b)
{
    return int2_t{max(a.x, b.x), max(a.y, b.y)};
}

export constexpr int2_t max(const int2_t a, const int_t val)
{
    return int2_t{max(a.x, val), max(a.y, val)};
}

export constexpr int2_t max(const int_t val, const int2_t b)
{
    return int2_t{max(val, b.x), max(val, b.y)};
}

export constexpr int2_t clamp(const int2_t v, const int2_t lower, const int2_t upper)
{
    FND_ASSERT(all(lower <= upper));

    return int2_t{clamp(v.x, lower.x, upper.x), clamp(v.y, lower.y, upper.y)};
}

export constexpr int2_t clamp(const int2_t v, const int2_t lower, const int_t upper)
{
    FND_ASSERT(all(lower <= upper));

    return int2_t{clamp(v.x, lower.x, upper), clamp(v.y, lower.y, upper)};
}

export constexpr int2_t clamp(const int2_t v, const int_t lower, const int2_t upper)
{
    FND_ASSERT(all(lower <= upper));

    return int2_t{clamp(v.x, lower, upper.x), clamp(v.y, lower, upper.y)};
}

export constexpr int2_t clamp(const int2_t v, const int_t lower, const int_t upper)
{
    FND_ASSERT(lower <= upper);

    return int2_t{clamp(v.x, lower, upper), clamp(v.y, lower, upper)};
}

export constexpr int2_t sign(const int2_t v)
{
    return int2_t{sign(v.x), sign(v.y)};
}

export constexpr int_t cmin(const int2_t v)
{
    return min(v.x, v.y);
}

export constexpr int_t cmax(const int2_t v)
{
    return max(v.x, v.y);
}

export constexpr int_t csum(const int2_t v)
{
    FND_ASSERT(long_t{v.x} + v.y >= kIntMinValue && long_t{v.x} + v.y <= kIntMaxValue);

    return v.x + v.y;
}

export constexpr int_t cmul(const int2_t v)
{
    FND_ASSERT(long_t{v.x} * v.y >= kIntMinValue && long_t{v.x} * v.y <= kIntMaxValue);

    return v.x * v.y;
}

} // namespace fnd
