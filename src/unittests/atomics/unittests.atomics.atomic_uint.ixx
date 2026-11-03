module;
#include "foundation/unittests.h"


export module unittests.atomics:atomic_uint;
import foundation.atomics;
import foundation.core;

namespace fnd::unittests {

export void unittests_atomics_atomic_uint();

// Edge values and a pattern with every byte distinct: a value whose top bit is
// set is a negative long inside the atomic functions.
constexpr uint_t kAtomicUIntValues[]{
  0, 1, 0x01234567, 0x80000000, kUIntMaxValue};

void unittests_atomics_atomic_uint_type()
{
  static_assert(PodType<atomic_uint_t>);
  static_assert(sizeof(atomic_uint_t) == sizeof(uint_t));
  static_assert(alignof(atomic_uint_t) == alignof(uint_t));
}

void unittests_atomics_atomic_uint_constructors()
{
  const atomic_uint_t zero_atomic;
  FND_TEST_TRUE(zero_atomic.value == 0);

  const atomic_uint_t atomic{0x01234567};
  FND_TEST_TRUE(atomic.value == 0x01234567);
}

void unittests_atomics_atomic_uint_compare_exchange()
{
  // Every pair of current and expected values: the value before the call is
  // returned, and new_value replaces it exactly when it equals expected.
  // new_value differs from expected, so arguments passed to the intrinsic in
  // the wrong order would fail every matching pair.
  for (const uint_t current : kAtomicUIntValues) {
    for (const uint_t expected : kAtomicUIntValues) {
      atomic_uint_t atomic{current};
      const uint_t new_value{~expected};
      FND_TEST_TRUE(compare_exchange(atomic, expected, new_value) == current);
      if (current == expected) {
        FND_TEST_TRUE(atomic.value == new_value);
      }
      else {
        FND_TEST_TRUE(atomic.value == current);
      }
    }
  }

  // Swapping in the value already held succeeds and leaves it unchanged.
  constexpr uint_t kMagicValue{0x01234567};
  atomic_uint_t atomic{kMagicValue};
  FND_TEST_TRUE(
    compare_exchange(atomic, kMagicValue, kMagicValue) == kMagicValue);
  FND_TEST_TRUE(atomic.value == kMagicValue);

  // A retry loop: a stale expected fails, and the returned value is the next
  // expected, which succeeds.
  atomic_uint_t counter{41};
  uint_t expected{0};
  uint_t prev_value{compare_exchange(counter, expected, expected + 1)};
  FND_TEST_TRUE(prev_value == 41);
  FND_TEST_TRUE(counter.value == 41);
  expected = prev_value;
  prev_value = compare_exchange(counter, expected, expected + 1);
  FND_TEST_TRUE(prev_value == 41);
  FND_TEST_TRUE(counter.value == 42);
}

void unittests_atomics_atomic_uint_fetch_add()
{
  for (const uint_t current : kAtomicUIntValues) {
    for (const uint_t x : kAtomicUIntValues) {
      atomic_uint_t atomic{current};
      FND_TEST_TRUE(fetch_add(atomic, x) == current);
      FND_TEST_TRUE(atomic.value == current + x);
    }
  }

  // Overflow wraps.
  atomic_uint_t atomic{kUIntMaxValue};
  FND_TEST_TRUE(fetch_add(atomic, 1) == kUIntMaxValue);
  FND_TEST_TRUE(atomic.value == 0);
}

void unittests_atomics_atomic_uint_fetch_and()
{
  for (const uint_t current : kAtomicUIntValues) {
    for (const uint_t x : kAtomicUIntValues) {
      atomic_uint_t atomic{current};
      FND_TEST_TRUE(fetch_and(atomic, x) == current);
      FND_TEST_TRUE(atomic.value == (current & x));
    }
  }
}

void unittests_atomics_atomic_uint_fetch_or()
{
  for (const uint_t current : kAtomicUIntValues) {
    for (const uint_t x : kAtomicUIntValues) {
      atomic_uint_t atomic{current};
      FND_TEST_TRUE(fetch_or(atomic, x) == current);
      FND_TEST_TRUE(atomic.value == (current | x));
    }
  }
}

void unittests_atomics_atomic_uint_fetch_sub()
{
  for (const uint_t current : kAtomicUIntValues) {
    for (const uint_t x : kAtomicUIntValues) {
      atomic_uint_t atomic{current};
      FND_TEST_TRUE(fetch_sub(atomic, x) == current);
      FND_TEST_TRUE(atomic.value == current - x);
    }
  }

  // Going below zero wraps.
  atomic_uint_t atomic{0};
  FND_TEST_TRUE(fetch_sub(atomic, 1) == 0);
  FND_TEST_TRUE(atomic.value == kUIntMaxValue);

  // x = 2^31, whose negation as a long would overflow: subtracting it
  // flips the top bit.
  constexpr uint_t kTopBit{0x80000000};
  atomic_uint_t top_bit_atomic{0};
  FND_TEST_TRUE(fetch_sub(top_bit_atomic, kTopBit) == 0);
  FND_TEST_TRUE(top_bit_atomic.value == kTopBit);
  FND_TEST_TRUE(fetch_sub(top_bit_atomic, kTopBit) == kTopBit);
  FND_TEST_TRUE(top_bit_atomic.value == 0);
  store(top_bit_atomic, kUIntMaxValue);
  FND_TEST_TRUE(fetch_sub(top_bit_atomic, kTopBit) == kUIntMaxValue);
  FND_TEST_TRUE(top_bit_atomic.value == 0x7FFFFFFF);
}

void unittests_atomics_atomic_uint_fetch_xor()
{
  for (const uint_t current : kAtomicUIntValues) {
    for (const uint_t x : kAtomicUIntValues) {
      atomic_uint_t atomic{current};
      FND_TEST_TRUE(fetch_xor(atomic, x) == current);
      FND_TEST_TRUE(atomic.value == (current ^ x));
    }
  }
}

void unittests_atomics_atomic_uint_load()
{
  // Every order a load accepts returns the value, through a const atomic too.
  for (const uint_t value : kAtomicUIntValues) {
    const atomic_uint_t atomic{value};
    FND_TEST_TRUE(load<EMemoryOrder::kRelaxed>(atomic) == value);
    FND_TEST_TRUE(load<EMemoryOrder::kReadAcquire>(atomic) == value);
    FND_TEST_TRUE(load<EMemoryOrder::kFullFence>(atomic) == value);
    FND_TEST_TRUE(load(atomic) == value);
  }
}

void unittests_atomics_atomic_uint_store()
{
  // Every order a store accepts replaces the value, whatever it was before.
  atomic_uint_t atomic{};
  for (const uint_t value : kAtomicUIntValues) {
    store<EMemoryOrder::kRelaxed>(atomic, value);
    FND_TEST_TRUE(atomic.value == value);
    store<EMemoryOrder::kRelaxed>(atomic, ~value);
    FND_TEST_TRUE(atomic.value == ~value);

    store<EMemoryOrder::kWriteRelease>(atomic, value);
    FND_TEST_TRUE(atomic.value == value);
    store<EMemoryOrder::kWriteRelease>(atomic, ~value);
    FND_TEST_TRUE(atomic.value == ~value);

    store<EMemoryOrder::kFullFence>(atomic, value);
    FND_TEST_TRUE(atomic.value == value);
    store<EMemoryOrder::kFullFence>(atomic, ~value);
    FND_TEST_TRUE(atomic.value == ~value);

    store(atomic, value);
    FND_TEST_TRUE(atomic.value == value);
    store(atomic, ~value);
    FND_TEST_TRUE(atomic.value == ~value);
  }

  // A stored value reads back through load.
  store(atomic, 0x01234567);
  FND_TEST_TRUE(load(atomic) == 0x01234567);
}

void unittests_atomics_atomic_uint()
{
  unittests_atomics_atomic_uint_type();
  unittests_atomics_atomic_uint_constructors();
  unittests_atomics_atomic_uint_compare_exchange();
  unittests_atomics_atomic_uint_fetch_add();
  unittests_atomics_atomic_uint_fetch_and();
  unittests_atomics_atomic_uint_fetch_or();
  unittests_atomics_atomic_uint_fetch_sub();
  unittests_atomics_atomic_uint_fetch_xor();
  unittests_atomics_atomic_uint_load();
  unittests_atomics_atomic_uint_store();
}

} // namespace fnd::unittests
