export module foundation.core:type_traits;

namespace fnd {

export template <typename T>
concept PodType = 
    __is_standard_layout(T) && __is_trivially_copyable(T);

export template<typename TSrc, typename TDest>
constexpr bool is_convertible() 
{
    return __is_convertible_to(TSrc, TDest);
}

export constexpr bool is_constant_evaluated()
{
    return __builtin_is_constant_evaluated();
}

} // namespace fnd
