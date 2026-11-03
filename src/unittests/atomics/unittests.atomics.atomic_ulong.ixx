module;
#include "foundation/unittests.h"


export module unittests.atomics:atomic_ulong;
import foundation.atomics;
import foundation.core;

namespace fnd::unittests {

export void unittests_atomics_atomic_ulong();

// Edge values and a pattern with every byte distinct: a value whose top bit is
// set is a negative __int64 inside the atomic functions.
constexpr ulong_t kAtomicULongValues[]{
  0, 1, 0x0123456789ABCDEF, 0x8000000000000000, kULongMaxValue};

void unittests_atomics_atomic_ulong_type()
{
  static_assert(PodType<atomic_ulong_t>);
  static_assert(sizeof(atomic_ulong_t) == sizeof(ulong_t));
  static_assert(alignof(atomic_ulong_t) == alignof(ulong_t));
}

void unittests_atomics_atomic_ulong_constructors()
{
  const atomic_ulong_t zero_atomic;
  FND_TEST_TRUE(zero_atomic.value == 0);

  const atomic_ulong_t atomic{0x0123456789ABCDEF};
  FND_TEST_TRUE(atomic.value == 0x0123456789ABCDEF);
}

void unittests_atomics_atomic_ulong_compare_exchange()
{
  // Every pair of current and expected values: the value before the call is
  // returned, and new_value replaces it exactly when it equals expected.
  // new_value differs from expected, so arguments passed to the intrinsic in
  // the wrong order would fail every matching pair.
  for (const ulong_t current : kAtomicULongValues) {
    for (const ulong_t expected : kAtomicULongValues) {
      atomic_ulong_t atomic{current};
      const ulong_t new_value{~expected};
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
  constexpr ulong_t kMagicValue{0x0123456789ABCDEF};
  atomic_ulong_t atomic{kMagicValue};
  FND_TEST_TRUE(
    compare_exchange(atomic, kMagicValue, kMagicValue) == kMagicValue);
  FND_TEST_TRUE(atomic.value == kMagicValue);

  // A retry loop: a stale expected fails, and the returned value is the next
  // expected, which succeeds.
  atomic_ulong_t counter{41};
  ulong_t expected{0};
  ulong_t prev_value{compare_exchange(counter, expected, expected + 1)};
  FND_TEST_TRUE(prev_value == 41);
  FND_TEST_TRUE(counter.value == 41);
  expected = prev_value;
  prev_value = compare_exchange(counter, expected, expected + 1);
  FND_TEST_TRUE(prev_value == 41);
  FND_TEST_TRUE(counter.value == 42);
}

void unittests_atomics_atomic_ulong_fetch_add()
{
  for (const ulong_t current : kAtomicULongValues) {
    for (const ulong_t x : kAtomicULongValues) {
      atomic_ulong_t atomic{current};
      FND_TEST_TRUE(fetch_add(atomic, x) == current);
      FND_TEST_TRUE(atomic.value == current + x);
    }
  }

  // Overflow wraps.
  atomic_ulong_t atomic{kULongMaxValue};
  FND_TEST_TRUE(fetch_add(atomic, 1) == kULongMaxValue);
  FND_TEST_TRUE(atomic.value == 0);
}

void unittests_atomics_atomic_ulong_fetch_and()
{
  for (const ulong_t current : kAtomicULongValues) {
    for (const ulong_t x : kAtomicULongValues) {
      atomic_ulong_t atomic{current};
      FND_TEST_TRUE(fetch_and(atomic, x) == current);
      FND_TEST_TRUE(atomic.value == (current & x));
    }
  }
}

void unittests_atomics_atomic_ulong_fetch_or()
{
  for (const ulong_t current : kAtomicULongValues) {
    for (const ulong_t x : kAtomicULongValues) {
      atomic_ulong_t atomic{current};
      FND_TEST_TRUE(fetch_or(atomic, x) == current);
      FND_TEST_TRUE(atomic.value == (current | x));
    }
  }
}

void unittests_atomics_atomic_ulong_fetch_sub()
{
  for (const ulong_t current : kAtomicULongValues) {
    for (const ulong_t x : kAtomicULongValues) {
      atomic_ulong_t atomic{current};
      FND_TEST_TRUE(fetch_sub(atomic, x) == current);
      FND_TEST_TRUE(atomic.value == current - x);
    }
  }

  // Going below zero wraps.
  atomic_ulong_t atomic{0};
  FND_TEST_TRUE(fetch_sub(atomic, 1) == 0);
  FND_TEST_TRUE(atomic.value == kULongMaxValue);

  // x = 2^63, whose negation as an __int64 would overflow: subtracting it
  // flips the top bit.
  constexpr ulong_t kTopBit{0x8000000000000000};
  atomic_ulong_t top_bit_atomic{0};
  FND_TEST_TRUE(fetch_sub(top_bit_atomic, kTopBit) == 0);
  FND_TEST_TRUE(top_bit_atomic.value == kTopBit);
  FND_TEST_TRUE(fetch_sub(top_bit_atomic, kTopBit) == kTopBit);
  FND_TEST_TRUE(top_bit_atomic.value == 0);
  store(top_bit_atomic, kULongMaxValue);
  FND_TEST_TRUE(fetch_sub(top_bit_atomic, kTopBit) == kULongMaxValue);
  FND_TEST_TRUE(top_bit_atomic.value == 0x7FFFFFFFFFFFFFFF);
}

void unittests_atomics_atomic_ulong_fetch_xor()
{
  for (const ulong_t current : kAtomicULongValues) {
    for (const ulong_t x : kAtomicULongValues) {
      atomic_ulong_t atomic{current};
      FND_TEST_TRUE(fetch_xor(atomic, x) == current);
      FND_TEST_TRUE(atomic.value == (current ^ x));
    }
  }
}

void unittests_atomics_atomic_ulong_load()
{
  // Every order a load accepts returns the value, through a const atomic too.
  for (const ulong_t value : kAtomicULongValues) {
    const atomic_ulong_t atomic{value};
    FND_TEST_TRUE(load<EMemoryOrder::kRelaxed>(atomic) == value);
    FND_TEST_TRUE(load<EMemoryOrder::kReadAcquire>(atomic) == value);
    FND_TEST_TRUE(load<EMemoryOrder::kFullFence>(atomic) == value);
    FND_TEST_TRUE(load(atomic) == value);
  }
}

void unittests_atomics_atomic_ulong_store()
{
  // Every order a store accepts replaces the value, whatever it was before.
  atomic_ulong_t atomic{};
  for (const ulong_t value : kAtomicULongValues) {
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
  store(atomic, 0x0123456789ABCDEF);
  FND_TEST_TRUE(load(atomic) == 0x0123456789ABCDEF);
}

void unittests_atomics_atomic_ulong()
{
  unittests_atomics_atomic_ulong_type();
  unittests_atomics_atomic_ulong_constructors();
  unittests_atomics_atomic_ulong_compare_exchange();
  unittests_atomics_atomic_ulong_fetch_add();
  unittests_atomics_atomic_ulong_fetch_and();
  unittests_atomics_atomic_ulong_fetch_or();
  unittests_atomics_atomic_ulong_fetch_sub();
  unittests_atomics_atomic_ulong_fetch_xor();
  unittests_atomics_atomic_ulong_load();
  unittests_atomics_atomic_ulong_store();
}

} // namespace fnd::unittests
