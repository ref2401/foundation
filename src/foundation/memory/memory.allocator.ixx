module;
#include "foundation/core/macros.h"

export module foundation.memory:allocator;
import foundation.core;
import :block;

namespace fnd {

export class IAllocator {
public:
  virtual void* allocate(
    const ulong_t byte_count, const ulong_t alignment,
    const source_location_t srcloc) = 0;

  virtual void free(
    void* const ptr, const ulong_t byte_count,
    const source_location_t srcloc) = 0;

protected:
  IAllocator() = default;
  ~IAllocator() = default;
  IAllocator(const IAllocator&) = default;
  IAllocator(IAllocator&&) = default;
  IAllocator& operator=(const IAllocator&) = default;
  IAllocator& operator=(IAllocator&&) = default;
};


export inline memory_block_t allocate_block(
  IAllocator& allocator, const ulong_t byte_count, const ulong_t alignment,
  const source_location_t srcloc = make_source_location())
{
  FND_ASSERT(byte_count > 0);
  FND_ASSERT(is_pow2(alignment));

  void* const ptr{allocator.allocate(byte_count, alignment, srcloc)};
  return memory_block_t{ptr, ptr ? byte_count : 0};
}

export inline void free_block(
  IAllocator& allocator, const memory_block_t block,
  const source_location_t srcloc = make_source_location())
{
  FND_ASSERT(is_well_formed(block));

  if (!is_empty(block)) {
    allocator.free(block.ptr, block.byte_count, srcloc);
  }
}

} // namespace fnd
