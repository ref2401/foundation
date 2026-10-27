module;
#include "foundation/unittests.h"


export module unittests.memory:allocator_heap;
import foundation.memory;

namespace fnd::unittests {

export void unittests_memory_allocator_heap();

constexpr ulong_t kHeapAlignments[]{
  1, 2, 4, 8, 16, 32, 64, 128, HeapAllocator::kMaxAlignment};
// Byte counts below, at and above the alignments.
constexpr ulong_t kHeapByteCounts[]{1, 3, 16, 100, 256, 4097};

void unittests_memory_allocator_heap_allocate()
{
  HeapAllocator heap{};

  // Every alignment and byte count: a block of exactly byte_count bytes whose
  // ptr is aligned as asked.
  for (const ulong_t alignment : kHeapAlignments) {
    for (const ulong_t byte_count : kHeapByteCounts) {
      const memory_block_t block{heap.allocate(byte_count, alignment)};
      FND_TEST_TRUE(block.ptr != nullptr);
      FND_TEST_TRUE(block.byte_count == byte_count);
      FND_TEST_TRUE(is_aligned(block.ptr, alignment));

      // Every byte is usable, and writing all of them leaves free working:
      // the allocator's bookkeeping lies outside the block.
      fill_bytes(block.ptr, byte_count, 0xAB);
      for (ulong_t i{0}; i < byte_count; ++i) {
        FND_TEST_TRUE(*block[i] == 0xAB);
      }

      heap.free(block);
    }
  }
}

void unittests_memory_allocator_heap_allocate_zero_bytes()
{
  HeapAllocator heap{};

  for (const ulong_t alignment : kHeapAlignments) {
    FND_TEST_TRUE(heap.allocate(0, alignment) == memory_block_t{});
  }
}

void unittests_memory_allocator_heap_allocate_distinct_blocks()
{
  HeapAllocator heap{};
  constexpr ulong_t kBlockCount{8};
  memory_block_t blocks[kBlockCount]{};

  for (ulong_t i{0}; i < kBlockCount; ++i) {
    blocks[i] = heap.allocate(32, 16);
  }

  // Blocks that are alive at the same time share no byte.
  for (ulong_t i{0}; i < kBlockCount; ++i) {
    for (ulong_t j{i + 1}; j < kBlockCount; ++j) {
      FND_TEST_FALSE(overlaps(blocks[i], blocks[j]));
    }
  }

  for (ulong_t i{0}; i < kBlockCount; ++i) {
    heap.free(blocks[i]);
  }
}

void unittests_memory_allocator_heap_allocate_failure()
{
  HeapAllocator heap{};

  // More bytes than the heap can give: the empty block.
  constexpr ulong_t kHugeByteCount{kULongMaxValue / 2};
  FND_TEST_TRUE(heap.allocate(kHugeByteCount, 16) == memory_block_t{});
}

void unittests_memory_allocator_heap_free_empty_block()
{
  HeapAllocator heap{};

  // The empty block is ignored, including the one allocate(0) returns.
  heap.free(memory_block_t{});
  heap.free(heap.allocate(0, 16));
}

void unittests_memory_allocator_heap_through_interface()
{
  HeapAllocator heap{};
  IAllocator& allocator{heap};

  // Calls through IAllocator reach HeapAllocator and keep the contract.
  const memory_block_t block{allocator.allocate(64, 32)};
  FND_TEST_TRUE(block.ptr != nullptr);
  FND_TEST_TRUE(block.byte_count == 64);
  FND_TEST_TRUE(is_aligned(block.ptr, 32));
  allocator.free(block);

  FND_TEST_TRUE(allocator.allocate(0, 32) == memory_block_t{});
}

void unittests_memory_allocator_heap()
{
  unittests_memory_allocator_heap_allocate();
  unittests_memory_allocator_heap_allocate_zero_bytes();
  unittests_memory_allocator_heap_allocate_distinct_blocks();
  unittests_memory_allocator_heap_allocate_failure();
  unittests_memory_allocator_heap_free_empty_block();
  unittests_memory_allocator_heap_through_interface();
}

} // namespace fnd::unittests
