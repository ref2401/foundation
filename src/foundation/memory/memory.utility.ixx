module;
#include <string.h>
#include "foundation/core/macros.h"

export module foundation.memory:utility;
import foundation.core;

namespace fnd {

// ptr rounded up to the next multiple of alignment, a power of two;
// ptr itself if it is aligned already.
export inline const void* align_up(
  const void* const ptr, const ulong_t alignment)
{
  FND_ASSERT(is_pow2(alignment));

  const uptr_t address{reinterpret_cast<uptr_t>(ptr)};
  const uptr_t offset{alignment - 1};
  FND_ASSERT(address + offset >= address); // overflow

  const uptr_t mask{~offset};
  return reinterpret_cast<const void*>((address + offset) & mask);
}

export inline void* align_up(void* const ptr, const ulong_t alignment)
{
  FND_ASSERT(is_pow2(alignment));

  const uptr_t address{reinterpret_cast<uptr_t>(ptr)};
  const uptr_t offset{alignment - 1};
  FND_ASSERT(address + offset >= address); // overflow

  // ptr is non-const, so casting the result back is safe. The static_cast
  // selects the const overload; without it this would call itself.
  return const_cast<void*>(align_up(static_cast<const void*>(ptr), alignment));
}

// Copies byte_count bytes from `from` to `to`; the ranges must not overlap.
export inline void copy_bytes(
  const void* const from, void* const to, const ulong_t byte_count)
{
  FND_ASSERT(from != nullptr);
  FND_ASSERT(to != nullptr);
  FND_ASSERT(byte_count > 0);

  const uptr_t p0{reinterpret_cast<uptr_t>(from)};
  const uptr_t p1{reinterpret_cast<uptr_t>(to)};
  FND_ASSERT(p0 - p1 >= byte_count && p1 - p0 >= byte_count); // overlap

  ::memcpy(to, from, byte_count);
}

// True if the byte_count bytes at ptr0 and ptr1 are equal.
// The ranges may overlap.
export inline bool_t equal_bytes(
  const void* const ptr0, const void* const ptr1, const ulong_t byte_count)
{
  FND_ASSERT(ptr0 != nullptr);
  FND_ASSERT(ptr1 != nullptr);
  FND_ASSERT(byte_count > 0);

  return ::memcmp(ptr0, ptr1, byte_count) == 0;
}

// Sets byte_count bytes at ptr to value.
export inline void fill_bytes(
  void* const ptr, const ulong_t byte_count, const ubyte_t value)
{
  FND_ASSERT(ptr != nullptr);
  FND_ASSERT(byte_count > 0);

  ::memset(ptr, value, byte_count);
}

// count gibibytes (2^30 bytes) in bytes.
export constexpr ulong_t gibibytes(const ulong_t count)
{
  constexpr ulong_t kBytesPerGib{1024 * 1024 * 1024};
  FND_ASSERT(count <= kULongMaxValue / kBytesPerGib); // overflow

  return count * kBytesPerGib;
}

// True if ptr is a multiple of alignment, a power of two.
// nullptr is aligned to anything.
export inline bool_t is_aligned(const void* const ptr, const ulong_t alignment)
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
