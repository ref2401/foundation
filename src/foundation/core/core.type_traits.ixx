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
template<typename T> struct UnrefImpl final { using type = T; };
template<typename T> struct UnrefImpl<T&> final { using type = T; };
template<typename T> struct UnrefImpl<T&&> final { using type = T; };
export template<typename T> using Unref = typename UnrefImpl<T>::type;


// ---------------------------------------------------------------------------
// is_const
// ---------------------------------------------------------------------------

// True if T itself is const-qualified (const or const volatile). Only the top
// level counts:
// - is_const<const int_t&>() is false: a reference is never const itself, the
//   int_t it refers to is. is_const<Unref<T>>() asks about that type.
// - is_const<const int_t*>() is false: it is a non-const pointer to a const
//   int_t. is_const<int_t* const>() is true: the pointer itself is const.
template<typename T> constexpr bool_t kIsConst = false;
template<typename T> constexpr bool_t kIsConst<const T> = true;
export template<typename T> constexpr bool_t is_const()
{
    return kIsConst<T>;
}

export constexpr bool_t is_constant_evaluated()
{
    return __builtin_is_constant_evaluated();
}

export template<typename TSrc, typename TDest> constexpr bool_t is_convertible()
{
    return __is_convertible_to(TSrc, TDest);
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
