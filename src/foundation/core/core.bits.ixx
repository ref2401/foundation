export module foundation.core:bits;

namespace fnd {

export template<typename TDest, typename TSrc>
requires (sizeof(TDest) == sizeof(TSrc)
    && __is_trivially_copyable(TDest) 
    && __is_trivially_copyable(TSrc))
constexpr TDest bit_cast(const TSrc& val)
{
    return __builtin_bit_cast(TDest, val);
}

} // namespace fnd
