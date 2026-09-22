module;
#include "foundation/core/macros.h"

export module foundation.core:span;
import :api_types;

namespace fnd {

export template<typename T>
struct span_t final {
    T* ptr;
    ulong_t count;

    constexpr T& operator[](const ulong_t index)
    {
        FND_ASSERT(index < count);
        return ptr[index];
    }

    constexpr const T& operator[](const ulong_t index) const
    {
        FND_ASSERT(index < count);
        return ptr[index];
    }
};

export template<typename T>
constexpr bool operator==(const span_t<T> lhs, const span_t<T> rhs)
{
    return lhs.ptr == rhs.ptr && lhs.count == rhs.count;
}

export template<typename T>
constexpr bool operator!=(const span_t<T> lhs, const span_t<T> rhs)
{
    return !(lhs == rhs);
}

export template<typename T>
constexpr bool is_empty(const span_t<T> span)
{
    return !span.ptr || (span.count == 0);
}

} // namespace fnd
