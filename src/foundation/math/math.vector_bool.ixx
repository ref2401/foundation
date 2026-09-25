module;
#include "foundation/core/macros.h"

export module foundation.math:vector_bool;
import foundation.core;

namespace fnd {

export struct bool2_t final {
    bool_t x{false};
    bool_t y{false};

    constexpr bool2_t() = default;
    constexpr explicit bool2_t(bool_t val) : x{val}, y{val} {}
    constexpr bool2_t(bool_t x, bool_t y) : x{x}, y{y} {}

    constexpr const bool_t& operator[](const uint_t idx) const
    {
        FND_ASSERT(idx < 2);
        return idx == 0 ? x : y;
    }

    constexpr bool_t& operator[](const uint_t idx)
    {
        return const_cast<bool_t&>(static_cast<const bool2_t&>(*this)[idx]);
    }

    constexpr bool2_t operator!() const { return bool2_t{!x, !y}; }
};

export constexpr bool_t all(const bool2_t v)
{
    return v.x && v.y;
}

export constexpr bool_t any(const bool2_t v)
{
    return v.x || v.y;
}

export constexpr bool2_t operator==(const bool2_t a, const bool2_t b)
{
    return bool2_t{a.x == b.x, a.y == b.y};
}

export constexpr bool2_t operator!=(const bool2_t a, const bool2_t b)
{
    return !(a == b);
}

export constexpr bool2_t operator==(const bool2_t a, const bool_t val)
{
    return bool2_t{a.x == val, a.y == val};
}

export constexpr bool2_t operator!=(const bool2_t a, const bool_t val)
{
    return !(a == val);
}

export constexpr bool2_t operator==(const bool_t val, const bool2_t b)
{
    return bool2_t{val == b.x, val == b.y};
}

export constexpr bool2_t operator!=(const bool_t val, const bool2_t b)
{
    return !(val == b);
}

// NOTE:
// Overloaded && always evaluates both operands.
export constexpr bool2_t operator&&(const bool2_t a, const bool2_t b)
{
    return bool2_t{a.x && b.x, a.y && b.y};
}

export constexpr bool2_t operator&&(const bool2_t a, const bool_t val)
{
    return bool2_t{a.x && val, a.y && val};
}

export constexpr bool2_t operator&&(const bool_t val, const bool2_t b)
{
    return bool2_t{val && b.x, val && b.y};
}

// NOTE:
// Overloaded || always evaluates both operands.
export constexpr bool2_t operator||(const bool2_t a, const bool2_t b)
{
    return bool2_t{a.x || b.x, a.y || b.y};
}

export constexpr bool2_t operator||(const bool2_t a, const bool_t val)
{
    return bool2_t{a.x || val, a.y || val};
}

export constexpr bool2_t operator||(const bool_t val, const bool2_t b)
{
    return bool2_t{val || b.x, val || b.y};
}

export struct bool3_t final {
    bool_t x{false};
    bool_t y{false};
    bool_t z{false};

    constexpr bool3_t() = default;
    constexpr explicit bool3_t(bool_t val) : x{val}, y{val}, z{val} {}
    constexpr bool3_t(bool_t x, bool_t y, bool_t z) : x{x}, y{y}, z{z} {}

    constexpr const bool_t& operator[](const uint_t idx) const
    {
        FND_ASSERT(idx < 3);
        return idx == 0 ? x : (idx == 1 ? y : z);
    }

    constexpr bool_t& operator[](const uint_t idx)
    {
        return const_cast<bool_t&>(static_cast<const bool3_t&>(*this)[idx]);
    }

    constexpr bool3_t operator!() const { return bool3_t{!x, !y, !z}; }
};

export constexpr bool_t all(const bool3_t v)
{
    return v.x && v.y && v.z;
}

export constexpr bool_t any(const bool3_t v)
{
    return v.x || v.y || v.z;
}

export constexpr bool3_t operator==(const bool3_t a, const bool3_t b)
{
    return bool3_t{a.x == b.x, a.y == b.y, a.z == b.z};
}

export constexpr bool3_t operator!=(const bool3_t a, const bool3_t b)
{
    return !(a == b);
}

export constexpr bool3_t operator==(const bool3_t a, const bool_t val)
{
    return bool3_t{a.x == val, a.y == val, a.z == val};
}

export constexpr bool3_t operator!=(const bool3_t a, const bool_t val)
{
    return !(a == val);
}

export constexpr bool3_t operator==(const bool_t val, const bool3_t b)
{
    return bool3_t{val == b.x, val == b.y, val == b.z};
}

export constexpr bool3_t operator!=(const bool_t val, const bool3_t b)
{
    return !(val == b);
}

// NOTE:
// Overloaded && always evaluates both operands.
export constexpr bool3_t operator&&(const bool3_t a, const bool3_t b)
{
    return bool3_t{a.x && b.x, a.y && b.y, a.z && b.z};
}

export constexpr bool3_t operator&&(const bool3_t a, const bool_t val)
{
    return bool3_t{a.x && val, a.y && val, a.z && val};
}

export constexpr bool3_t operator&&(const bool_t val, const bool3_t b)
{
    return bool3_t{val && b.x, val && b.y, val && b.z};
}

// NOTE:
// Overloaded || always evaluates both operands.
export constexpr bool3_t operator||(const bool3_t a, const bool3_t b)
{
    return bool3_t{a.x || b.x, a.y || b.y, a.z || b.z};
}

export constexpr bool3_t operator||(const bool3_t a, const bool_t val)
{
    return bool3_t{a.x || val, a.y || val, a.z || val};
}

export constexpr bool3_t operator||(const bool_t val, const bool3_t b)
{
    return bool3_t{val || b.x, val || b.y, val || b.z};
}

} // namespace fnd
