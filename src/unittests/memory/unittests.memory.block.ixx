module;
#include "foundation/unittests.h"


export module unittests.memory:block;
import foundation.memory;

namespace fnd::unittests {

export void unittests_memory_block();

void unittests_memory_block_type()
{
  static_assert(PodType<memory_block_t>);
  static_assert(sizeof(memory_block_t) == 16);
}

void unittests_memory_block_constructors()
{
  const memory_block_t empty_block{};
  FND_TEST_TRUE(empty_block.ptr == nullptr);
  FND_TEST_TRUE(empty_block.byte_count == 0);

  constexpr ulong_t kBufferLength{16};
  ubyte_t buffer[kBufferLength]{};
  const memory_block_t block{buffer, kBufferLength};
  FND_TEST_TRUE(block.ptr == buffer);
  FND_TEST_TRUE(block.byte_count == kBufferLength);

  // Usable in constant expressions.
  static_assert(memory_block_t{}.byte_count == 0);
}

void unittests_memory_block_subscript_operator()
{
  constexpr ulong_t kByteCount{16};
  ubyte_t buffer[kByteCount]{};

  // Each index gives the address of that byte, writable through a non-const
  // block and read-only through a const one.
  memory_block_t block{buffer, kByteCount};
  const memory_block_t const_block{buffer, kByteCount};
  static_assert(is_same<decltype(block[0]), ubyte_t*>());
  static_assert(is_same<decltype(const_block[0]), const ubyte_t*>());

  for (ulong_t i{0}; i < kByteCount; ++i) {
    FND_TEST_TRUE(block[i] == buffer + i);
    FND_TEST_TRUE(const_block[i] == buffer + i);
  }

  *block[3] = 0xAB;
  FND_TEST_TRUE(buffer[3] == 0xAB);
}

void unittests_memory_block_equality_operators()
{
  constexpr ulong_t kBufferLength{16};
  ubyte_t buffer[kBufferLength]{};
  const memory_block_t block{buffer, kBufferLength};
  const memory_block_t block_copy{block};

  FND_TEST_TRUE(block == block_copy);
  FND_TEST_FALSE(block != block_copy);
  FND_TEST_TRUE(memory_block_t{} == memory_block_t{});

  // Both the pointer and the count take part.
  FND_TEST_TRUE(block != memory_block_t{buffer + 1, kBufferLength - 1});
  FND_TEST_TRUE(block != memory_block_t{buffer, kBufferLength - 1});
  FND_TEST_FALSE(block == memory_block_t{buffer, kBufferLength - 1});

  // Two empty blocks can differ: == compares fields, not emptiness.
  FND_TEST_TRUE(memory_block_t{buffer, 0} != memory_block_t{});
}

void unittests_memory_block_contains_pointer()
{
  constexpr ulong_t kBufferLength{32};
  constexpr ulong_t kOffset{8};
  constexpr ulong_t kByteCount{16};
  ubyte_t buffer[kBufferLength]{};
  const memory_block_t block{buffer + kOffset, kByteCount};

  // Exactly the pointers in [ptr, ptr + byte_count): the first byte is in,
  // one past the last is out.
  for (ulong_t i{0}; i < kBufferLength; ++i) {
    const bool_t is_inside{kOffset <= i && i < kOffset + kByteCount};
    FND_TEST_TRUE(contains(block, buffer + i) == is_inside);
  }
  FND_TEST_TRUE(contains(block, buffer + kOffset));
  FND_TEST_FALSE(contains(block, buffer + kOffset + kByteCount));
  FND_TEST_FALSE(contains(block, nullptr));

  // A pointer to const works the same.
  const ubyte_t* const const_ptr{buffer + kOffset};
  FND_TEST_TRUE(contains(block, const_ptr));

  // An empty block contains no pointer, nullptr included.
  FND_TEST_FALSE(contains(memory_block_t{}, buffer));
  FND_TEST_FALSE(contains(memory_block_t{}, nullptr));
  FND_TEST_FALSE(contains(memory_block_t{buffer, 0}, buffer));
  FND_TEST_FALSE(contains(memory_block_t{nullptr, 16}, nullptr));
}

void unittests_memory_block_contains_block()
{
  constexpr ulong_t kBufferLength{32};
  constexpr ulong_t kOffset{8};
  constexpr ulong_t kByteCount{16};
  ubyte_t buffer[kBufferLength]{};
  const memory_block_t block{buffer + kOffset, kByteCount};

  // Every non-empty sub-block of the buffer: contained exactly when it starts
  // and ends within the block.
  for (ulong_t offset{0}; offset < kBufferLength; ++offset) {
    for (ulong_t count{1}; offset + count <= kBufferLength; ++count) {
      const memory_block_t sub_block{buffer + offset, count};
      const bool_t is_inside{
        kOffset <= offset && offset + count <= kOffset + kByteCount};
      FND_TEST_TRUE(contains(block, sub_block) == is_inside);
    }
  }

  // A block contains itself, its first and its last byte; not a block that
  // sticks out on either side or is adjacent to it.
  FND_TEST_TRUE(contains(block, block));
  FND_TEST_TRUE(contains(block, memory_block_t{buffer + kOffset, 1}));
  FND_TEST_TRUE(
    contains(block, memory_block_t{buffer + kOffset + kByteCount - 1, 1}));
  FND_TEST_FALSE(contains(block, memory_block_t{buffer + kOffset - 1, 2}));
  FND_TEST_FALSE(
    contains(block, memory_block_t{buffer + kOffset + kByteCount - 1, 2}));
  FND_TEST_FALSE(contains(block, memory_block_t{buffer + kOffset - 4, 4}));
  FND_TEST_FALSE(
    contains(block, memory_block_t{buffer + kOffset + kByteCount, 4}));
  FND_TEST_FALSE(contains(block, memory_block_t{buffer, kBufferLength}));

  // An empty block contains no block, and an empty block is never contained,
  // not even where its pointer lies inside the block.
  FND_TEST_FALSE(contains(block, memory_block_t{}));
  FND_TEST_FALSE(contains(memory_block_t{}, block));
  FND_TEST_FALSE(contains(memory_block_t{}, memory_block_t{}));
  FND_TEST_FALSE(contains(block, memory_block_t{buffer + kOffset, 0}));
  FND_TEST_FALSE(contains(block, memory_block_t{nullptr, 16}));
  FND_TEST_FALSE(contains(memory_block_t{buffer + kOffset, 0}, block));
  FND_TEST_FALSE(contains(
    memory_block_t{buffer + kOffset, 0}, memory_block_t{buffer + kOffset, 0}));
  FND_TEST_FALSE(
    contains(memory_block_t{nullptr, 16}, memory_block_t{nullptr, 4}));
}

void unittests_memory_block_is_empty()
{
  constexpr ulong_t kBufferLength{16};
  ubyte_t buffer[kBufferLength]{};

  FND_TEST_TRUE(is_empty(memory_block_t{}));
  FND_TEST_TRUE(is_empty(memory_block_t{buffer, 0}));
  FND_TEST_TRUE(is_empty(memory_block_t{nullptr, kBufferLength}));
  FND_TEST_FALSE(is_empty(memory_block_t{buffer, kBufferLength}));
  FND_TEST_FALSE(is_empty(memory_block_t{buffer, 1}));

  // Usable in constant expressions.
  static_assert(is_empty(memory_block_t{}));
}

void unittests_memory_block_overlaps()
{
  constexpr ulong_t kBufferLength{32};
  constexpr ulong_t kOffset{8};
  constexpr ulong_t kByteCount{16};
  ubyte_t buffer[kBufferLength]{};
  const memory_block_t block{buffer + kOffset, kByteCount};

  // Every non-empty block of the buffer: overlaps exactly when it starts
  // before the block ends and ends after the block starts, in either order.
  for (ulong_t offset{0}; offset < kBufferLength; ++offset) {
    for (ulong_t count{1}; offset + count <= kBufferLength; ++count) {
      const memory_block_t other{buffer + offset, count};
      const bool_t is_shared{
        offset < kOffset + kByteCount && kOffset < offset + count};
      FND_TEST_TRUE(overlaps(block, other) == is_shared);
      FND_TEST_TRUE(overlaps(other, block) == is_shared);
    }
  }

  // A block overlaps itself, a block inside it, a block around it, and a
  // block sharing only its first or its last byte; not an adjacent block.
  FND_TEST_TRUE(overlaps(block, block));
  FND_TEST_TRUE(overlaps(block, memory_block_t{buffer + kOffset + 4, 4}));
  FND_TEST_TRUE(overlaps(block, memory_block_t{buffer, kBufferLength}));
  FND_TEST_TRUE(overlaps(block, memory_block_t{buffer + kOffset - 1, 2}));
  FND_TEST_TRUE(
    overlaps(block, memory_block_t{buffer + kOffset + kByteCount - 1, 2}));
  FND_TEST_FALSE(overlaps(block, memory_block_t{buffer + kOffset - 4, 4}));
  FND_TEST_FALSE(
    overlaps(block, memory_block_t{buffer + kOffset + kByteCount, 4}));

  // An empty block overlaps nothing, not even where its pointer lies inside
  // the other block.
  const memory_block_t empty_inside{buffer + kOffset + 4, 0};
  FND_TEST_FALSE(overlaps(block, memory_block_t{}));
  FND_TEST_FALSE(overlaps(memory_block_t{}, block));
  FND_TEST_FALSE(overlaps(memory_block_t{}, memory_block_t{}));
  FND_TEST_FALSE(overlaps(block, empty_inside));
  FND_TEST_FALSE(overlaps(empty_inside, block));
  FND_TEST_FALSE(overlaps(empty_inside, empty_inside));
  FND_TEST_FALSE(overlaps(block, memory_block_t{nullptr, 16}));
  FND_TEST_FALSE(
    overlaps(memory_block_t{nullptr, 16}, memory_block_t{nullptr, 4}));
}

void unittests_memory_block()
{
  unittests_memory_block_type();
  unittests_memory_block_constructors();
  unittests_memory_block_subscript_operator();
  unittests_memory_block_equality_operators();
  unittests_memory_block_contains_pointer();
  unittests_memory_block_contains_block();
  unittests_memory_block_is_empty();
  unittests_memory_block_overlaps();
}

} // namespace fnd::unittests
