module;
#include "foundation/core/macros.h"

export module foundation.memory:allocator;
import foundation.core;
import :block;

namespace fnd {

// Each implementation asserts the preconditions below; srcloc
// is the caller's location, for tracking and diagnostics.
export class IAllocator {
public:
  // Returns the memory at ptr to the allocator.
  // ptr is a live allocation of this allocator.
  // byte_count is the size it was last allocated or resized to.
  virtual void free(
    void* const ptr, const ulong_t byte_count,
    const source_location_t srcloc) = 0;

  // Memory of new_byte_count bytes aligned to alignment, a power of two;
  // new_byte_count is greater than 0.
  // If ptr is nullptr, old_byte_count is 0 then new memory is allocated.
  // Otherwise ptr is a live allocation of this allocator of old_byte_count
  // bytes; it is resized, possibly moved, keeping its bytes up to the smaller
  // of the two sizes.
  // On success only the returned pointer is valid.
  // Returns nullptr on failure; ptr then stays valid and unchanged.
  virtual void* realloc(
    void* const ptr, const ulong_t old_byte_count, const ulong_t new_byte_count,
    const ulong_t alignment, const source_location_t srcloc) = 0;

protected:
  IAllocator() = default;
  ~IAllocator() = default;
  IAllocator(const IAllocator&) = default;
  IAllocator(IAllocator&&) = default;
  IAllocator& operator=(const IAllocator&) = default;
  IAllocator& operator=(IAllocator&&) = default;
};

// Returns block's memory to allocator. An empty block is ignored.
export inline void free_block(
  IAllocator& allocator, const memory_block_t block,
  const source_location_t srcloc = make_source_location())
{
  if (!is_empty(block)) {
    allocator.free(block.ptr, block.byte_count, srcloc);
  }
}

// A block of new_byte_count bytes aligned to alignment. An empty block is
// allocated; otherwise block is resized, keeping its bytes up to the smaller
// of the two sizes. Returns an empty block on failure; block then stays valid.
export inline memory_block_t realloc_block(
  IAllocator& allocator, const memory_block_t block,
  const ulong_t new_byte_count, const ulong_t alignment,
  const source_location_t srcloc = make_source_location())
{
  FND_ASSERT((block.ptr == nullptr) == (block.byte_count == 0));
  FND_ASSERT(new_byte_count > 0);
  FND_ASSERT(is_pow2(alignment));

  void* const new_ptr{allocator.realloc(
    block.ptr, block.byte_count, new_byte_count, alignment, srcloc)};
  return memory_block_t{new_ptr, new_ptr ? new_byte_count : 0};
}

} // namespace fnd
