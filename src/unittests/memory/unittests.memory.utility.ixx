module;
#include "foundation/unittests.h"


export module unittests.memory:utility;
import foundation.memory;

namespace fnd::unittests {

export void unittests_memory_utility();

// Alignment of the test buffers: the largest alignment that the tests on real
// memory can check.
constexpr ulong_t kMaxBufferAlignment{256};
// Every power-of-two alignment up to that of the test buffers.
constexpr ulong_t kAlignments[]{
  1, 2, 4, 8, 16, 32, 64, 128, kMaxBufferAlignment};

void unittests_memory_utility_align_up()
{
  alignas(kMaxBufferAlignment) ubyte_t buffer[2 * kMaxBufferAlignment]{};

  // An aligned pointer stays where it is.
  FND_TEST_TRUE(align_up(buffer, kMaxBufferAlignment) == buffer);
  FND_TEST_TRUE(align_up(buffer + 16, 16) == buffer + 16);

  // Otherwise it moves forward to the next multiple of alignment.
  FND_TEST_TRUE(align_up(buffer + 1, 16) == buffer + 16);
  FND_TEST_TRUE(align_up(buffer + 15, 16) == buffer + 16);
  FND_TEST_TRUE(align_up(buffer + 17, 16) == buffer + 32);
  FND_TEST_TRUE(align_up(buffer + 33, 64) == buffer + 64);
  FND_TEST_TRUE(
    align_up(buffer + 1, kMaxBufferAlignment) == buffer + kMaxBufferAlignment);

  // Every offset and alignment: the result is aligned, not before the
  // pointer, less than alignment after it, and the closest such address.
  // A pointer to const gives the same address.
  for (ulong_t offset{0}; offset < 128; ++offset) {
    for (const ulong_t alignment : kAlignments) {
      ubyte_t* const ptr{buffer + offset};
      const ulong_t expected_offset{
        (offset + alignment - 1) / alignment * alignment};

      ubyte_t* const res_ptr{static_cast<ubyte_t*>(align_up(ptr, alignment))};
      FND_TEST_TRUE(res_ptr == buffer + expected_offset);
      FND_TEST_TRUE(is_aligned(res_ptr, alignment));
      FND_TEST_TRUE(res_ptr >= ptr);
      FND_TEST_TRUE(res_ptr < ptr + alignment);

      const ubyte_t* const const_ptr{ptr};
      FND_TEST_TRUE(align_up(const_ptr, alignment) == res_ptr);
    }
  }

  // Alignment 1 never moves a pointer; nullptr stays nullptr.
  FND_TEST_TRUE(align_up(buffer + 7, 1) == buffer + 7);
  FND_TEST_TRUE(align_up(static_cast<void*>(nullptr), 64) == nullptr);
  FND_TEST_TRUE(align_up(static_cast<const void*>(nullptr), 64) == nullptr);

  // A pointer to const keeps its constness; an aligned one stays where it
  // is.
  const ubyte_t* const const_ptr{buffer + 3};
  static_assert(is_same<decltype(align_up(const_ptr, 16)), const void*>());
  static_assert(is_same<decltype(align_up(buffer, 16)), void*>());
  FND_TEST_TRUE(align_up(const_ptr, 16) == buffer + 16);
  FND_TEST_TRUE(align_up(const_ptr + 13, 16) == const_ptr + 13);

  // Addresses built from integers reach what the buffer can't: page and
  // larger alignments, and the upper half of a 64-bit address. The pointer
  // is never dereferenced.
  const auto align_up_test_address =
    [](const uptr_t address, const ulong_t alignment) {
      return reinterpret_cast<uptr_t>(
        align_up(reinterpret_cast<void*>(address), alignment));
    };
  FND_TEST_TRUE(align_up_test_address(0x1000, 4096) == 0x1000);
  FND_TEST_TRUE(align_up_test_address(0x1001, 4096) == 0x2000);
  FND_TEST_TRUE(
    align_up_test_address(0x100000001, ulong_t{1} << 32) == uptr_t{2} << 32);
  FND_TEST_TRUE(align_up_test_address(1, ulong_t{1} << 63) == uptr_t{1} << 63);
  // A mask computed in 32 bits would clear the upper half.
  FND_TEST_TRUE(
    align_up_test_address(0x123456789ABCDEF1, 16) == 0x123456789ABCDF00);

  // The largest address that does not overflow with alignment 16. With
  // alignment 1 nothing overflows, not even the last address.
  constexpr uptr_t kMaxAddress{~uptr_t{0} - 15};
  FND_TEST_TRUE(align_up_test_address(kMaxAddress, 16) == kMaxAddress);
  FND_TEST_TRUE(align_up_test_address(~uptr_t{0}, 1) == ~uptr_t{0});
}

void unittests_memory_utility_copy_bytes()
{
  // Every byte value as the source: 0 and values above 127 are copied too.
  ubyte_t from[256]{};
  for (ulong_t i{0}; i < 256; ++i) {
    from[i] = static_cast<ubyte_t>(i);
  }

  // The whole range.
  ubyte_t to[256]{};
  copy_bytes(from, to, 256);
  for (ulong_t i{0}; i < 256; ++i) {
    FND_TEST_TRUE(to[i] == from[i]);
  }

  // A part into the middle of a buffer: the bytes around it stay as they
  // are.
  constexpr ubyte_t kUntouchedValue{0xAB};
  constexpr ulong_t kFromOffset{200};
  constexpr ulong_t kToOffset{4};
  constexpr ulong_t kByteCount{8};
  constexpr ulong_t kPartLength{16};
  ubyte_t part[kPartLength]{};
  for (ubyte_t& b : part) {
    b = kUntouchedValue;
  }
  copy_bytes(from + kFromOffset, part + kToOffset, kByteCount);
  for (ulong_t i{0}; i < kPartLength; ++i) {
    const bool_t is_copied{kToOffset <= i && i < kToOffset + kByteCount};
    const ubyte_t expected_value{
      is_copied ? from[kFromOffset + i - kToOffset] : kUntouchedValue};
    FND_TEST_TRUE(part[i] == expected_value);
  }

  // Adjacent ranges do not overlap: the destination is right after the source
  constexpr ulong_t kBufferLength{24};
  ubyte_t buffer[kBufferLength]{};
  for (ulong_t i{0}; i < kBufferLength; ++i) {
    buffer[i] = static_cast<ubyte_t>(i);
  }
  copy_bytes(buffer, buffer + 8, 8);
  for (ulong_t i{0}; i < 8; ++i) {
    FND_TEST_TRUE(buffer[i] == i);     // the source is unchanged
    FND_TEST_TRUE(buffer[8 + i] == i); // the copy
    FND_TEST_TRUE(buffer[16 + i] == 16 + i);
  }

  // Adjacent ranges do not overlap: the destination is right before the source
  copy_bytes(buffer + 16, buffer + 8, 8);
  for (ulong_t i{0}; i < 8; ++i) {
    FND_TEST_TRUE(buffer[i] == i);
    FND_TEST_TRUE(buffer[8 + i] == 16 + i);
    FND_TEST_TRUE(buffer[16 + i] == 16 + i);
  }

  // A single byte, and an object: its bytes are its value.
  ubyte_t single_byte_dest{0};
  copy_bytes(from + 255, &single_byte_dest, 1);
  FND_TEST_TRUE(single_byte_dest == 255);

  struct copy_test_t final {
    int_t i;
    float_t f;
  };
  constexpr copy_test_t kObject{-7, 2.5f};
  copy_test_t object{};
  copy_bytes(&kObject, &object, sizeof(copy_test_t));
  FND_TEST_TRUE(object.i == kObject.i);
  FND_TEST_TRUE(object.f == kObject.f);
}

void unittests_memory_utility_fill_bytes()
{
  // The whole buffer, with 0, a value above 127 and the largest value.
  constexpr ubyte_t kValues[]{0, 0xAB, 0xFF};
  constexpr ulong_t kBufferLength{64};
  ubyte_t buffer[kBufferLength]{};

  for (const ubyte_t value : kValues) {
    fill_bytes(buffer, kBufferLength, value);

    for (const ubyte_t b : buffer) {
      FND_TEST_TRUE(b == value);
    }
  }

  // A part in the middle: the bytes around it stay as they are.
  constexpr ubyte_t kUntouched{0x11};
  constexpr ubyte_t kValue{0xCD};
  constexpr ulong_t kOffset{5};
  constexpr ulong_t kCount{7};
  fill_bytes(buffer, kBufferLength, kUntouched);
  fill_bytes(buffer + kOffset, kCount, kValue);

  for (ulong_t i{0}; i < kBufferLength; ++i) {
    const bool_t is_filled{kOffset <= i && i < kOffset + kCount};
    const ubyte_t expected_value{is_filled ? kValue : kUntouched};
    FND_TEST_TRUE(buffer[i] == expected_value);
  }

  // A single byte.
  ubyte_t single_byte{0};
  fill_bytes(&single_byte, 1, kValue);
  FND_TEST_TRUE(single_byte == kValue);

  // An object: every byte of it gets the value.
  struct fill_test_t final {
    uint_t u;
    ubyte_t b;
  };

  fill_test_t object{1, 2};
  fill_bytes(&object, sizeof(fill_test_t), 0xFF);
  FND_TEST_TRUE(object.u == kUIntMaxValue);
  FND_TEST_TRUE(object.b == 0xFF);
}

void unittests_memory_utility_gibibytes()
{
  FND_TEST_TRUE(gibibytes(0) == 0);
  FND_TEST_TRUE(gibibytes(1) == ulong_t{1} << 30);
  FND_TEST_TRUE(gibibytes(1) == mebibytes(1024));
  // Beyond what a uint_t holds.
  FND_TEST_TRUE(gibibytes(4) == ulong_t{1} << 32);
  FND_TEST_TRUE(gibibytes(3) == 3 * gibibytes(1));

  // The largest count that does not overflow.
  constexpr ulong_t kMaxCount{kULongMaxValue >> 30};
  FND_TEST_TRUE(gibibytes(kMaxCount) == kMaxCount << 30);
  FND_TEST_TRUE(gibibytes(kMaxCount) > kULongMaxValue - gibibytes(1));

  // Usable in constant expressions.
  static_assert(gibibytes(2) == 2147483648);
}

void unittests_memory_utility_is_aligned()
{
  alignas(kMaxBufferAlignment) ubyte_t buffer[128]{};

  // buffer + offset is aligned exactly when offset is a multiple of
  // alignment.
  for (ulong_t offset{0}; offset < 128; ++offset) {
    for (const ulong_t alignment : kAlignments) {
      FND_TEST_TRUE(
        is_aligned(buffer + offset, alignment) == (offset % alignment == 0));
    }
  }
  FND_TEST_TRUE(is_aligned(buffer + 48, 16));
  FND_TEST_FALSE(is_aligned(buffer + 48, 32));
  FND_TEST_FALSE(is_aligned(buffer + 1, 2));

  // Alignment 1 holds for every address; nullptr is aligned to anything.
  FND_TEST_TRUE(is_aligned(buffer + 7, 1));
  FND_TEST_TRUE(is_aligned(nullptr, 64));
  FND_TEST_TRUE(is_aligned(nullptr, ulong_t{1} << 63));

  // A pointer to const works the same.
  const ubyte_t* const const_ptr{buffer + 16};
  FND_TEST_TRUE(is_aligned(const_ptr, 16));
  FND_TEST_FALSE(is_aligned(const_ptr, 32));

  // Addresses built from integers reach alignments the buffer can't; the
  // upper bits of an address don't affect the result. The pointer is never
  // dereferenced.
  const auto is_aligned_test_address =
    [](const uptr_t address, const ulong_t alignment) {
      return is_aligned(reinterpret_cast<const void*>(address), alignment);
    };
  FND_TEST_TRUE(is_aligned_test_address(0x1000, 4096));
  FND_TEST_FALSE(is_aligned_test_address(0x1000, 8192));
  FND_TEST_TRUE(is_aligned_test_address(0x123456789ABCDE00, 512));
  FND_TEST_FALSE(is_aligned_test_address(0x123456789ABCDE00, 1024));
  FND_TEST_TRUE(is_aligned_test_address(uptr_t{1} << 63, ulong_t{1} << 63));
  FND_TEST_FALSE(is_aligned_test_address(uptr_t{1} << 62, ulong_t{1} << 63));
}

void unittests_memory_utility_kibibytes()
{
  FND_TEST_TRUE(kibibytes(0) == 0);
  FND_TEST_TRUE(kibibytes(1) == 1024);
  FND_TEST_TRUE(kibibytes(4) == 4096);
  FND_TEST_TRUE(kibibytes(3) == 3 * kibibytes(1));

  // The largest count that does not overflow.
  constexpr ulong_t kMaxCount{kULongMaxValue >> 10};
  FND_TEST_TRUE(kibibytes(kMaxCount) == kMaxCount << 10);
  FND_TEST_TRUE(kibibytes(kMaxCount) > kULongMaxValue - kibibytes(1));

  // Usable in constant expressions.
  static_assert(kibibytes(2) == 2048);
}

void unittests_memory_utility_mebibytes()
{
  FND_TEST_TRUE(mebibytes(0) == 0);
  FND_TEST_TRUE(mebibytes(1) == ulong_t{1} << 20);
  FND_TEST_TRUE(mebibytes(1) == kibibytes(1024));
  FND_TEST_TRUE(mebibytes(3) == 3 * mebibytes(1));
  // Beyond what a uint_t holds.
  FND_TEST_TRUE(mebibytes(4096) == gibibytes(4));

  // The largest count that does not overflow.
  constexpr ulong_t kMaxCount{kULongMaxValue >> 20};
  FND_TEST_TRUE(mebibytes(kMaxCount) == kMaxCount << 20);
  FND_TEST_TRUE(mebibytes(kMaxCount) > kULongMaxValue - mebibytes(1));

  // Usable in constant expressions.
  static_assert(mebibytes(2) == 2097152);
}

void unittests_memory_utility()
{
  unittests_memory_utility_align_up();
  unittests_memory_utility_copy_bytes();
  unittests_memory_utility_fill_bytes();
  unittests_memory_utility_gibibytes();
  unittests_memory_utility_is_aligned();
  unittests_memory_utility_kibibytes();
  unittests_memory_utility_mebibytes();
}

} // namespace fnd::unittests
