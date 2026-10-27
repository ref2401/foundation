module;
#include <stdlib.h>
#include "foundation/core/macros.h"

export module foundation.memory:allocator_heap;
import foundation.core;
import :allocator;
import :utility;

namespace fnd {

export class HeapAllocator final : public IAllocator {
public:
  static constexpr ulong_t kMaxAlignment{256};

  HeapAllocator() = default;
  ~HeapAllocator() = default;
  HeapAllocator(const HeapAllocator&) = delete;
  HeapAllocator(HeapAllocator&&) = delete;
  HeapAllocator& operator=(const HeapAllocator&) = delete;
  HeapAllocator& operator=(HeapAllocator&&) = delete;


  void* allocate(
    const ulong_t byte_count, const ulong_t alignment,
    const source_location_t srcloc = make_source_location()) override
  {
    FND_ASSERT(is_pow2(alignment));
    FND_ASSERT(alignment <= kMaxAlignment);
    FND_ASSERT(byte_count + alignment >= byte_count);

    if (byte_count == 0) return nullptr;

    const ulong_t actual_byte_count{byte_count + alignment};
    ubyte_t* const ptr{static_cast<ubyte_t*>(::malloc(actual_byte_count))};
    if (!ptr) {
      return nullptr;
    }

    ubyte_t* aligned_ptr{static_cast<ubyte_t*>(align_up(ptr, alignment))};
    if (aligned_ptr == ptr) {
      aligned_ptr = ptr + alignment;
    }

    const long_t offset{aligned_ptr - ptr};
    FND_ASSERT(1 <= offset && offset <= kMaxAlignment);
    aligned_ptr[-1] = static_cast<ubyte_t>(offset);

    return aligned_ptr;
  }

  void free(
    void* const ptr, const ulong_t byte_count,
    const source_location_t srcloc = make_source_location()) override
  {
    if (!ptr) return;

    ubyte_t* const aligned_ptr{static_cast<ubyte_t*>(ptr)};
    ulong_t offset{aligned_ptr[-1]};
    if (offset == 0) offset = kMaxAlignment;

    void* const unaligned_ptr{aligned_ptr - offset};
    ::free(unaligned_ptr);
  }
};

} // namespace fnd
