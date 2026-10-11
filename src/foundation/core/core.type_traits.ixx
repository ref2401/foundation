module;
#include <type_traits>

export module foundation.core:type_traits;
import :arithmetic_types;

namespace fnd {

export template<typename T>
concept PodType = __is_standard_layout(T) && __is_trivially_copyable(T);

// ---------------------------------------------------------------------------
// Unref
// ---------------------------------------------------------------------------

// T without its reference: T& and T&& become T, any other type stays as it is.
// const and volatile are kept: Unref<const int_t&> is const int_t.
template<typename T> struct UnrefImpl { using type = T; };
template<typename T> struct UnrefImpl<T&> { using type = T; };
template<typename T> struct UnrefImpl<T&&> { using type = T; };
export template<typename T> using Unref = typename UnrefImpl<T>::type;


export template<typename TSrc, typename TDest> constexpr bool_t is_convertible()
{
    return __is_convertible_to(TSrc, TDest);
}

export constexpr bool_t is_constant_evaluated()
{
    return __builtin_is_constant_evaluated();
}

// ---------------------------------------------------------------------------
// is_same
// ---------------------------------------------------------------------------

// True if T and U are the same type; const, volatile and references count.
template<typename T, typename U> constexpr bool_t kIsSame = false;
template<typename T> constexpr bool_t kIsSame<T, T> = true;
export template<typename T, typename U> constexpr bool_t is_same()
{
    return kIsSame<T, U>;
}

} // namespace fnd
