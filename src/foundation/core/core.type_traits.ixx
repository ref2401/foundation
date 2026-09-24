export module foundation.core:type_traits;

namespace fnd {

export template <typename T>
concept PodType = 
    __is_standard_layout(T) && __is_trivially_copyable(T);

export constexpr bool is_constant_evaluated()
{
    return __builtin_is_constant_evaluated();
}

} // namespace fnd
