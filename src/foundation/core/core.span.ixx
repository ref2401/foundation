module;
#include "foundation/core/macros.h"

export module foundation.core:span;
import :arithmetic_types;

namespace fnd {

export template<typename T>
struct span_t final {
    T* ptr{nullptr};
    ulong_t count{0};

    constexpr span_t() = default;
    constexpr span_t(T* ptr, ulong_t count) : ptr{ptr}, count{count} {}

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
constexpr bool operator==(const span_t<T> a, const span_t<T> b)
{
    return a.ptr == b.ptr && a.count == b.count;
}

export template<typename T>
constexpr bool operator!=(const span_t<T> a, const span_t<T> b)
{
    return !(a == b);
}

export template<typename T>
constexpr bool is_empty(const span_t<T> span)
{
    return !span.ptr || (span.count == 0);
}

} // namespace fnd
