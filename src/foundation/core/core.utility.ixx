module;
#include "foundation/core/macros.h"

export module foundation.core:utility;
import :type_traits;

namespace fnd {

// Passes on a forwarding reference parameter (T&& value) as it was received:
// forward<T>(value) is an lvalue for an lvalue argument and an rvalue for an
// rvalue argument, with const and volatile kept.
export template<typename T>
[[nodiscard]] FND_CAST_FUNCTION constexpr T&& forward(Unref<T>& value)
{
    return static_cast<T&&>(value);
}

export template<typename T>
[[nodiscard]] FND_CAST_FUNCTION constexpr T&& forward(Unref<T>&& value)
{
    // An rvalue must not be forwarded as an lvalue: with T = int_t& the result
    // would be a reference to a temporary.
    static_assert(!is_same<T, Unref<T>&>());
    return static_cast<T&&>(value);
}

// value as an rvalue, so that a move constructor or move assignment is chosen.
export template<typename T>
[[nodiscard]] FND_CAST_FUNCTION constexpr Unref<T>&& move(T&& value)
{
    // A const object cannot be moved: its rvalue would be const too, which a
    // move constructor cannot take, and the copy constructor would silently be
    // used instead.
    static_assert(!is_const<Unref<T>>());
    return static_cast<Unref<T>&&>(value);
}

// Assigns new_value to object and returns object's previous value.
export template<typename T, typename U = T>
[[nodiscard]] constexpr T exchange(T& object, U&& new_value)
{
    T old_value = move(object);
    object = forward<U>(new_value);
    return old_value;
}

} // namespace fnd
