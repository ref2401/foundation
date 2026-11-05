module;
#include "foundation/unittests.h"


export module unittests.memory:utility;
import foundation.memory;

namespace fnd::unittests {

export void unittests_memory_utility();

void unittests_memory_utility_construct_at()
{
  constexpr ubyte_t kGarbage{0xAB};
  constexpr ulong_t kBufferByteCount{32};
  alignas(16) ubyte_t buffer[kBufferByteCount]{};

  // No arguments: value-initialized, so zero even over nonzero bytes.
  fill_bytes(buffer, kBufferByteCount, kGarbage);
  FND_TEST_TRUE(*construct_at<int_t>(buffer) == 0);

  struct construct_test_t final {
    int_t i;
    float_t f;
  };
  fill_bytes(buffer, kBufferByteCount, kGarbage);
  const construct_test_t* const zero{construct_at<construct_test_t>(buffer)};
  FND_TEST_TRUE(zero->i == 0);
  FND_TEST_TRUE(zero->f == 0);

  // An aggregate from several values: brace initialization, member by member.
  const construct_test_t* const object{
    construct_at<construct_test_t>(buffer, -7, 2.5f)};
  FND_TEST_TRUE(object->i == -7);
  FND_TEST_TRUE(object->f == 2.5f);

  // A scalar from a value, at ptr: only its bytes change, the bytes around it
  // stay as they are.
  fill_bytes(buffer, kBufferByteCount, kGarbage);
  constexpr ulong_t kOffset{8};
  const int_t* const p{construct_at<int_t>(buffer + kOffset, -7)};
  FND_TEST_TRUE(static_cast<const void*>(p) == buffer + kOffset);
  FND_TEST_TRUE(*p == -7);

  for (ulong_t i{0}; i < kBufferByteCount; ++i) {
    const bool_t is_constructed{kOffset <= i && i < kOffset + sizeof(int_t)};
    if (!is_constructed) {
      FND_TEST_TRUE(buffer[i] == kGarbage);
    }
  }

  // A constructor gets each argument as it was passed: an lvalue as an
  // lvalue, an rvalue as an rvalue.
  struct construct_arg_t final {
    int_t value;
  };
  struct construct_sink_t final {
    int_t value;
    bool_t is_moved;

    construct_sink_t(const construct_arg_t& source)
        : value{source.value}, is_moved{false}
    {
    }

    construct_sink_t(construct_arg_t&& source)
        : value{source.value}, is_moved{true}
    {
    }
  };
  construct_arg_t arg{5};

  const construct_sink_t* const from_lvalue{
    construct_at<construct_sink_t>(buffer, arg)};
  FND_TEST_TRUE(from_lvalue->value == 5);
  FND_TEST_FALSE(from_lvalue->is_moved);

  const construct_sink_t* const from_rvalue{
    construct_at<construct_sink_t>(buffer, move(arg))};
  FND_TEST_TRUE(from_rvalue->value == 5);
  FND_TEST_TRUE(from_rvalue->is_moved);
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

void unittests_memory_utility_equal_bytes()
{
  // Every byte value in both buffers.
  constexpr ulong_t kLength{256};
  ubyte_t a[kLength]{};
  ubyte_t b[kLength]{};
  for (ulong_t i{0}; i < kLength; ++i) {
    a[i] = static_cast<ubyte_t>(i);
    b[i] = static_cast<ubyte_t>(i);
  }
  FND_TEST_TRUE(equal_bytes(a, b, kLength));

  // One different byte anywhere makes them unequal: the first, the last, and
  // every one in between. Only the compared range counts.
  for (ulong_t i{1}; i < kLength; ++i) {
    b[i] = static_cast<ubyte_t>(b[i] + 1);
    FND_TEST_FALSE(equal_bytes(a, b, kLength));
    FND_TEST_TRUE(equal_bytes(a, b, i)); // the bytes before it
    b[i] = a[i];
  }

  // The bytes are compared as unsigned values: 0x7F and 0x80 differ, and so
  // do 0x00 and 0xFF.
  constexpr ubyte_t kBelow128{0x7F};
  constexpr ubyte_t kAbove127{0x80};
  FND_TEST_FALSE(equal_bytes(&kBelow128, &kAbove127, 1));
  FND_TEST_FALSE(equal_bytes(a, a + 255, 1));

  // A single equal byte; a range compared with itself.
  FND_TEST_TRUE(equal_bytes(a + 10, b + 10, 1));
  FND_TEST_TRUE(equal_bytes(a, a, kLength));

  // Overlapping ranges are allowed: a buffer of one repeated value equals
  // itself shifted by one byte, a buffer of distinct values does not.
  constexpr ulong_t kRepeatedLength{32};
  ubyte_t repeated[kRepeatedLength]{};
  for (ubyte_t& r : repeated) {
    r = 0xAA;
  }
  FND_TEST_TRUE(equal_bytes(repeated, repeated + 1, kRepeatedLength - 1));
  FND_TEST_FALSE(equal_bytes(a, a + 1, 31));

  // Objects with the same bytes are equal.
  struct equal_test_t final {
    int_t i;
    float_t f;
  };
  constexpr equal_test_t kObject0{-7, 2.5f};
  constexpr equal_test_t kObject1{-7, 2.5f};
  constexpr equal_test_t kObject2{-7, 3.5f};
  FND_TEST_TRUE(equal_bytes(&kObject0, &kObject1, sizeof(equal_test_t)));
  FND_TEST_FALSE(equal_bytes(&kObject0, &kObject2, sizeof(equal_test_t)));
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
  unittests_memory_utility_construct_at();
  unittests_memory_utility_copy_bytes();
  unittests_memory_utility_equal_bytes();
  unittests_memory_utility_fill_bytes();
  unittests_memory_utility_gibibytes();
  unittests_memory_utility_kibibytes();
  unittests_memory_utility_mebibytes();
}

} // namespace fnd::unittests
