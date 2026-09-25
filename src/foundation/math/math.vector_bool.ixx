module;
#include "foundation/core/macros.h"

export module foundation.math:vector_bool;
import foundation.core;

namespace fnd {

export struct bool2_t final {
    bool x{false};
    bool y{false};

    constexpr bool2_t() = default;
    constexpr explicit bool2_t(bool val) : x{val}, y{val} {}
    constexpr bool2_t(bool x, bool y) : x{x}, y{y} {}

    constexpr const bool& operator[](const uint_t idx) const
    {
        FND_ASSERT(idx == 0 || idx == 1);
        return idx == 0 ? x : y;
    }

    constexpr bool& operator[](const uint_t idx)
    {
        return const_cast<bool&>(static_cast<const bool2_t&>(*this)[idx]);
    }

    constexpr bool2_t operator!() const { return bool2_t{!x, !y}; }
};

export constexpr bool all(const bool2_t v)
{
    return v.x && v.y;
}

export constexpr bool any(const bool2_t v)
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

export constexpr bool2_t operator==(const bool2_t a, const bool val)
{
    return bool2_t{a.x == val, a.y == val};
}

export constexpr bool2_t operator!=(const bool2_t a, const bool val)
{
    return !(a == val);
}

export constexpr bool2_t operator==(const bool val, const bool2_t b)
{
    return bool2_t{val == b.x, val == b.y};
}

export constexpr bool2_t operator!=(const bool val, const bool2_t b)
{
    return !(val == b);
}

// NOTE:
// Overloaded && always evaluates both operands.
export constexpr bool2_t operator&&(const bool2_t a, const bool2_t b)
{
    return bool2_t{a.x && b.x, a.y && b.y};
}

export constexpr bool2_t operator&&(const bool2_t a, const bool val)
{
    return bool2_t{a.x && val, a.y && val};
}

export constexpr bool2_t operator&&(const bool val, const bool2_t b)
{
    return bool2_t{val && b.x, val && b.y};
}

// NOTE:
// Overloaded || always evaluates both operands.
export constexpr bool2_t operator||(const bool2_t a, const bool2_t b)
{
    return bool2_t{a.x || b.x, a.y || b.y};
}

export constexpr bool2_t operator||(const bool2_t a, const bool val)
{
    return bool2_t{a.x || val, a.y || val};
}

export constexpr bool2_t operator||(const bool val, const bool2_t b)
{
    return bool2_t{val || b.x, val || b.y};
}

} // namespace fnd
