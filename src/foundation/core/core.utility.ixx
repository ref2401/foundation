module;

// For a function whose body is a single cast of its parameter, such as move and
// forward: MSVC replaces each call with the cast itself, in Debug builds too.
// A macro cannot be exported from a module: this one is only for the cast
// functions of this file.
#if __has_cpp_attribute(msvc::intrinsic)
  #define FND_CAST_FUNCTION [[msvc::intrinsic]]
#else
  #define FND_CAST_FUNCTION
#endif

export module foundation.core:utility;
import :type_traits;

namespace fnd {

// The bytes of x reinterpreted as a TDest of the same size, not a value
// conversion: bit_cast<uint_t>(1.0f) is 0x3F800000, not 1.
export template<typename TDest, typename TSrc>
requires(
  sizeof(TDest) == sizeof(TSrc) && __is_trivially_copyable(TDest)
  && __is_trivially_copyable(TSrc))
constexpr TDest bit_cast(const TSrc& x)
{
  return __builtin_bit_cast(TDest, x);
}

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

// Swaps the values of a and b.
// swap(a, a) move-assigns the moved-from a to itself, which must be safe;
export template<typename T> constexpr void swap(T& a, T& b)
{
  T temp = move(a);
  a = move(b);
  b = move(temp);
}

} // namespace fnd
