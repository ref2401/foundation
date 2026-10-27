module;
#include "foundation/core/macros.h"

export module foundation.memory:allocator;
import foundation.core;
import :block;

namespace fnd {

// Hands out and takes back raw memory. Each implementation asserts the
// preconditions below, plus any limits of its own (such as a maximum
// alignment); thread safety is up to each implementation.
export class IAllocator {
public:
  // A block of exactly byte_count bytes whose ptr is a multiple of
  // alignment, a power of two. byte_count 0 gives the empty block.
  // On failure, returns the empty block.
  virtual memory_block_t allocate(
    const ulong_t byte_count, const ulong_t alignment,
    const source_location_t srcloc = make_source_location()) = 0;

  // Takes back a block that allocate of this allocator returned, unchanged
  // (same ptr and byte_count). The empty block is ignored.
  virtual void free(
    const memory_block_t& block,
    const source_location_t srcloc = make_source_location()) = 0;

protected:
  IAllocator() = default;
  ~IAllocator() = default;
  IAllocator(const IAllocator&) = default;
  IAllocator(IAllocator&&) = default;
  IAllocator& operator=(const IAllocator&) = default;
  IAllocator& operator=(IAllocator&&) = default;
};

} // namespace fnd
