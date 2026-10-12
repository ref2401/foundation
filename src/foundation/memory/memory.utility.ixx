module;
#include "foundation/core/macros.h"

export module foundation.memory:utility;
import foundation.core;

namespace fnd {

// count gibibytes (2^30 bytes) in bytes.
export constexpr ulong_t gibibytes(const ulong_t count)
{
    constexpr ulong_t kBytesPerGib{1024 * 1024 * 1024};
    FND_ASSERT(count <= kULongMaxValue / kBytesPerGib); // overflow

    return count * kBytesPerGib;
}

// count kibibytes (2^10 bytes) in bytes.
export constexpr ulong_t kibibytes(const ulong_t count)
{
    constexpr ulong_t kBytesPerKib{1024};
    FND_ASSERT(count <= kULongMaxValue / kBytesPerKib); // overflow

    return count * kBytesPerKib;
}

// count mebibytes (2^20 bytes) in bytes.
export constexpr ulong_t mebibytes(const ulong_t count)
{
    constexpr ulong_t kBytesPerMib{1024 * 1024};
    FND_ASSERT(count <= kULongMaxValue / kBytesPerMib); // overflow

    return count * kBytesPerMib;
}

} // namespace fnd
