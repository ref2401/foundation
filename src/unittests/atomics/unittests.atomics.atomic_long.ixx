module;
#include "foundation/unittests.h"


export module unittests.atomics:atomic_long;
import foundation.atomics;
import foundation.core;

namespace fnd::unittests {

export void unittests_atomics_atomic_long();

// Edge values and a pattern with every byte distinct: kLongMinValue is the one
// value whose negation overflows.
constexpr long_t kAtomicLongValues[]{
  0, 1, -1, 0x0123456789ABCDEF, kLongMinValue, kLongMaxValue};

void unittests_atomics_atomic_long_type()
{
  static_assert(PodType<atomic_long_t>);
  static_assert(sizeof(atomic_long_t) == sizeof(long_t));
  static_assert(alignof(atomic_long_t) == alignof(long_t));
}

void unittests_atomics_atomic_long_constructors()
{
  const atomic_long_t zero_atomic;
  FND_TEST_TRUE(zero_atomic.value == 0);

  const atomic_long_t atomic{-0x0123456789ABCDEF};
  FND_TEST_TRUE(atomic.value == -0x0123456789ABCDEF);
}

void unittests_atomics_atomic_long_compare_exchange()
{
  // Every pair of current and expected values: the value before the call is
  // returned, and new_value replaces it exactly when it equals expected.
  // new_value differs from expected, so arguments passed to the intrinsic in
  // the wrong order would fail every matching pair.
  for (const long_t current : kAtomicLongValues) {
    for (const long_t expected : kAtomicLongValues) {
      atomic_long_t atomic{current};
      const long_t new_value{~expected};
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
  constexpr long_t kMagicValue{-0x0123456789ABCDEF};
  atomic_long_t atomic{kMagicValue};
  FND_TEST_TRUE(
    compare_exchange(atomic, kMagicValue, kMagicValue) == kMagicValue);
  FND_TEST_TRUE(atomic.value == kMagicValue);

  // A retry loop: a stale expected fails, and the returned value is the next
  // expected, which succeeds.
  atomic_long_t counter{-41};
  long_t expected{0};
  long_t prev_value{compare_exchange(counter, expected, expected - 1)};
  FND_TEST_TRUE(prev_value == -41);
  FND_TEST_TRUE(counter.value == -41);
  expected = prev_value;
  prev_value = compare_exchange(counter, expected, expected - 1);
  FND_TEST_TRUE(prev_value == -41);
  FND_TEST_TRUE(counter.value == -42);
}

void unittests_atomics_atomic_long_fetch_add()
{
  // a + b with wrapping: signed overflow is undefined, unsigned wraps.
  const auto wrapping_add = [](const long_t a, const long_t b) {
    return static_cast<long_t>(
      static_cast<ulong_t>(a) + static_cast<ulong_t>(b));
  };

  for (const long_t current : kAtomicLongValues) {
    for (const long_t x : kAtomicLongValues) {
      atomic_long_t atomic{current};
      FND_TEST_TRUE(fetch_add(atomic, x) == current);
      FND_TEST_TRUE(atomic.value == wrapping_add(current, x));
    }
  }

  // Overflow wraps, in both directions.
  atomic_long_t atomic{kLongMaxValue};
  FND_TEST_TRUE(fetch_add(atomic, 1) == kLongMaxValue);
  FND_TEST_TRUE(atomic.value == kLongMinValue);
  FND_TEST_TRUE(fetch_add(atomic, -1) == kLongMinValue);
  FND_TEST_TRUE(atomic.value == kLongMaxValue);
}

void unittests_atomics_atomic_long_fetch_and()
{
  for (const long_t current : kAtomicLongValues) {
    for (const long_t x : kAtomicLongValues) {
      atomic_long_t atomic{current};
      FND_TEST_TRUE(fetch_and(atomic, x) == current);
      FND_TEST_TRUE(atomic.value == (current & x));
    }
  }
}

void unittests_atomics_atomic_long_fetch_or()
{
  for (const long_t current : kAtomicLongValues) {
    for (const long_t x : kAtomicLongValues) {
      atomic_long_t atomic{current};
      FND_TEST_TRUE(fetch_or(atomic, x) == current);
      FND_TEST_TRUE(atomic.value == (current | x));
    }
  }
}

void unittests_atomics_atomic_long_fetch_sub()
{
  // a - b with wrapping: signed overflow is undefined, unsigned wraps.
  const auto wrapping_sub = [](const long_t a, const long_t b) {
    return static_cast<long_t>(
      static_cast<ulong_t>(a) - static_cast<ulong_t>(b));
  };

  for (const long_t current : kAtomicLongValues) {
    for (const long_t x : kAtomicLongValues) {
      atomic_long_t atomic{current};
      FND_TEST_TRUE(fetch_sub(atomic, x) == current);
      FND_TEST_TRUE(atomic.value == wrapping_sub(current, x));
    }
  }

  // Overflow wraps, in both directions.
  atomic_long_t atomic{kLongMinValue};
  FND_TEST_TRUE(fetch_sub(atomic, 1) == kLongMinValue);
  FND_TEST_TRUE(atomic.value == kLongMaxValue);
  FND_TEST_TRUE(fetch_sub(atomic, -1) == kLongMaxValue);
  FND_TEST_TRUE(atomic.value == kLongMinValue);

  // x = kLongMinValue, whose negation would overflow.
  atomic_long_t min_atomic{0};
  FND_TEST_TRUE(fetch_sub(min_atomic, kLongMinValue) == 0);
  FND_TEST_TRUE(min_atomic.value == kLongMinValue);
  FND_TEST_TRUE(fetch_sub(min_atomic, kLongMinValue) == kLongMinValue);
  FND_TEST_TRUE(min_atomic.value == 0);
  store(min_atomic, -1);
  FND_TEST_TRUE(fetch_sub(min_atomic, kLongMinValue) == -1);
  FND_TEST_TRUE(min_atomic.value == kLongMaxValue);
}

void unittests_atomics_atomic_long_fetch_xor()
{
  for (const long_t current : kAtomicLongValues) {
    for (const long_t x : kAtomicLongValues) {
      atomic_long_t atomic{current};
      FND_TEST_TRUE(fetch_xor(atomic, x) == current);
      FND_TEST_TRUE(atomic.value == (current ^ x));
    }
  }
}

void unittests_atomics_atomic_long_load()
{
  // Every order a load accepts returns the value, through a const atomic too.
  for (const long_t value : kAtomicLongValues) {
    const atomic_long_t atomic{value};
    FND_TEST_TRUE(load<EMemoryOrder::kRelaxed>(atomic) == value);
    FND_TEST_TRUE(load<EMemoryOrder::kReadAcquire>(atomic) == value);
    FND_TEST_TRUE(load<EMemoryOrder::kFullFence>(atomic) == value);
    FND_TEST_TRUE(load(atomic) == value);
  }
}

void unittests_atomics_atomic_long_store()
{
  // Every order a store accepts replaces the value, whatever it was before.
  atomic_long_t atomic{};
  for (const long_t value : kAtomicLongValues) {
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
  store(atomic, -0x0123456789ABCDEF);
  FND_TEST_TRUE(load(atomic) == -0x0123456789ABCDEF);
}

void unittests_atomics_atomic_long()
{
  unittests_atomics_atomic_long_type();
  unittests_atomics_atomic_long_constructors();
  unittests_atomics_atomic_long_compare_exchange();
  unittests_atomics_atomic_long_fetch_add();
  unittests_atomics_atomic_long_fetch_and();
  unittests_atomics_atomic_long_fetch_or();
  unittests_atomics_atomic_long_fetch_sub();
  unittests_atomics_atomic_long_fetch_xor();
  unittests_atomics_atomic_long_load();
  unittests_atomics_atomic_long_store();
}

} // namespace fnd::unittests
