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
  // Largest alignment allocate accepts.
  static constexpr ulong_t kMaxAlignment{256};

  HeapAllocator() = default;
  ~HeapAllocator() = default;
  HeapAllocator(const HeapAllocator&) = delete;
  HeapAllocator(HeapAllocator&&) = delete;
  HeapAllocator& operator=(const HeapAllocator&) = delete;
  HeapAllocator& operator=(HeapAllocator&&) = delete;


  memory_block_t allocate(
    const ulong_t byte_count, const ulong_t alignment,
    const source_location_t srcloc = make_source_location()) override
  {
    FND_ASSERT(is_pow2(alignment));
    FND_ASSERT(alignment <= kMaxAlignment);
    FND_ASSERT(byte_count + alignment >= byte_count);

    if (byte_count == 0) return memory_block_t{};

    const ulong_t actual_byte_count{byte_count + alignment};
    ubyte_t* const ptr{static_cast<ubyte_t*>(::malloc(actual_byte_count))};
    if (!ptr) {
      return memory_block_t{};
    }

    ubyte_t* aligned_ptr{static_cast<ubyte_t*>(align_up(ptr, alignment))};
    if (aligned_ptr == ptr) {
      aligned_ptr = ptr + alignment;
    }

    const long_t offset{aligned_ptr - ptr};
    FND_ASSERT(1 <= offset && offset <= kMaxAlignment);
    aligned_ptr[-1] = static_cast<ubyte_t>(offset);

    return memory_block_t{aligned_ptr, byte_count};
  }

  void free(
    const memory_block_t& block,
    const source_location_t srcloc = make_source_location()) override
  {
    FND_ASSERT(is_well_formed(block));

    if (is_empty(block)) return;

    ubyte_t* const aligned_ptr{static_cast<ubyte_t*>(block.ptr)};
    ulong_t offset{aligned_ptr[-1]};
    if (offset == 0) offset = kMaxAlignment;

    void* const unaligned_ptr{aligned_ptr - offset};
    ::free(unaligned_ptr);
  }
};

} // namespace fnd
