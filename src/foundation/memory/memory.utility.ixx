module;
#include "foundation/core/macros.h"

export module foundation.memory:utility;
import foundation.core;

namespace fnd {

// ptr rounded up to the next multiple of alignment, a power of two;
// ptr itself if it is aligned already.
export FND_INLINE const void* align_up(
  const void* const ptr, const ulong_t alignment)
{
  FND_ASSERT(is_pow2(alignment));

  const uptr_t address{reinterpret_cast<uptr_t>(ptr)};
  const uptr_t mask{alignment - 1};
  FND_ASSERT(address + mask >= address); // overflow

  return reinterpret_cast<const void*>((address + mask) & ~mask);
}

export FND_INLINE void* align_up(void* const ptr, const ulong_t alignment)
{
  FND_ASSERT(is_pow2(alignment));

  const uptr_t address{reinterpret_cast<uptr_t>(ptr)};
  const uptr_t mask{alignment - 1};
  FND_ASSERT(address + mask >= address); // overflow

  // ptr is non-const, so casting the result back is safe. The static_cast
  // selects the const overload; without it this would call itself.
  return const_cast<void*>(align_up(static_cast<const void*>(ptr), alignment));
}

// count gibibytes (2^30 bytes) in bytes.
export constexpr ulong_t gibibytes(const ulong_t count)
{
  constexpr ulong_t kBytesPerGib{1024 * 1024 * 1024};
  FND_ASSERT(count <= kULongMaxValue / kBytesPerGib); // overflow

  return count * kBytesPerGib;
}

// True if ptr is a multiple of alignment, a power of two. nullptr is aligned to
// anything.
export FND_INLINE bool_t is_aligned(
  const void* const ptr, const ulong_t alignment)
{
  FND_ASSERT(is_pow2(alignment));

  return (reinterpret_cast<uptr_t>(ptr) & (alignment - 1)) == 0;
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
