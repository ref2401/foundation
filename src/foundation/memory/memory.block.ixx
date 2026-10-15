module;
#include "foundation/core/macros.h"

export module foundation.memory:block;
import foundation.core;

namespace fnd {

export struct memory_block_t final {
  void* ptr{nullptr};
  ulong_t byte_count{0};

  constexpr memory_block_t() = default;
  constexpr memory_block_t(void* const ptr, const ulong_t byte_count)
      : ptr{ptr}, byte_count{byte_count}
  {
  }

  inline const ubyte_t* operator[](const ulong_t byte_idx) const
  {
    FND_ASSERT(byte_idx < byte_count);
    return static_cast<const ubyte_t*>(ptr) + byte_idx;
  }

  inline ubyte_t* operator[](const ulong_t byte_idx)
  {
    FND_ASSERT(byte_idx < byte_count);
    return const_cast<ubyte_t*>(
      static_cast<const memory_block_t&>(*this)[byte_idx]);
  }
};

export constexpr bool_t operator==(
  const memory_block_t a, const memory_block_t b)
{
  return a.ptr == b.ptr && a.byte_count == b.byte_count;
}

export constexpr bool_t operator!=(
  const memory_block_t a, const memory_block_t b)
{
  return !(a == b);
}

// Writes the addresses [out_start, out_end) that block covers. A block
// without a pointer covers no addresses, whatever its byte_count.
inline void compute_address_range(
  const memory_block_t block, uptr_t& out_start, uptr_t& out_end)
{
  out_start = reinterpret_cast<uptr_t>(block.ptr);
  out_end = out_start + (block.ptr == nullptr ? 0 : block.byte_count);
  FND_ASSERT(out_end >= out_start); // overflow
}

// True if ptr points into [block.ptr, block.ptr + block.byte_count).
// An empty block contains no pointer.
export inline bool_t contains(const memory_block_t block, const void* const ptr)
{
  // Addresses are compared as integers: ptr may point outside the block,
  // and comparing unrelated pointers with < gives an unspecified result.
  uptr_t start;
  uptr_t end;
  compute_address_range(block, /* out: */ start, end);
  const uptr_t p{reinterpret_cast<uptr_t>(ptr)};

  return start <= p && p < end;
}

// True if every byte of sub_block lies within block.
// False if either block is empty.
export inline bool_t contains(
  const memory_block_t block, const memory_block_t sub_block)
{
  // Addresses are compared as integers: sub_block may lie outside the block,
  // and comparing unrelated pointers with < gives an unspecified result.
  uptr_t start;
  uptr_t end;
  compute_address_range(block, /* out: */ start, end);
  uptr_t p0;
  uptr_t p1;
  compute_address_range(sub_block, /* out: */ p0, p1);

  return start <= p0 && p0 < p1 && p1 <= end;
}

// True if block has no memory: ptr is nullptr or byte_count is 0.
export constexpr bool_t is_empty(const memory_block_t block)
{
  return block.ptr == nullptr || block.byte_count == 0;
}

// True if block0 and block1 share at least one byte.
// False if either block is empty.
export bool_t overlaps(const memory_block_t block0, const memory_block_t block1)
{
  uptr_t start0;
  uptr_t end0;
  compute_address_range(block0, /* out: */ start0, end0);
  uptr_t start1;
  uptr_t end1;
  compute_address_range(block1, /* out: */ start1, end1);

  return max(start0, start1) < min(end0, end1);
}

// The byte_count bytes of block that start at byte_offset. They must lie
// within block and be at least one byte.
export inline memory_block_t slice(
  const memory_block_t block, const ulong_t byte_offset,
  const ulong_t byte_count)
{
  FND_ASSERT(!is_empty(block));
  // Also keeps block.byte_count - byte_offset below from wrapping.
  FND_ASSERT(byte_offset < block.byte_count);
  FND_ASSERT(byte_count > 0);
  FND_ASSERT(byte_count <= block.byte_count - byte_offset);

  ubyte_t* const new_ptr{static_cast<ubyte_t*>(block.ptr) + byte_offset};

  return memory_block_t{new_ptr, byte_count};
}

// The bytes of block from byte_offset to its end. At least one byte must
// remain.
export inline memory_block_t slice(
  const memory_block_t block, const ulong_t byte_offset)
{
  FND_ASSERT(!is_empty(block));
  FND_ASSERT(byte_offset < block.byte_count);

  const ulong_t byte_count{block.byte_count - byte_offset};
  return slice(block, byte_offset, byte_count);
}

} // namespace fnd
