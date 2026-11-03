module;
#include "foundation/unittests.h"


export module unittests.atomics:atomic_int;
import foundation.atomics;
import foundation.core;

namespace fnd::unittests {

export void unittests_atomics_atomic_int();

// Edge values and a pattern with every byte distinct: kIntMinValue is the one
// value whose negation overflows.
constexpr int_t kAtomicIntValues[]{
  0, 1, -1, 0x01234567, kIntMinValue, kIntMaxValue};

void unittests_atomics_atomic_int_type()
{
  static_assert(PodType<atomic_int_t>);
  static_assert(sizeof(atomic_int_t) == sizeof(int_t));
  static_assert(alignof(atomic_int_t) == alignof(int_t));
}

void unittests_atomics_atomic_int_constructors()
{
  const atomic_int_t zero_atomic;
  FND_TEST_TRUE(zero_atomic.value == 0);

  const atomic_int_t atomic{-0x01234567};
  FND_TEST_TRUE(atomic.value == -0x01234567);
}

void unittests_atomics_atomic_int_compare_exchange()
{
  // Every pair of current and expected values: the value before the call is
  // returned, and new_value replaces it exactly when it equals expected.
  // new_value differs from expected, so arguments passed to the intrinsic in
  // the wrong order would fail every matching pair.
  for (const int_t current : kAtomicIntValues) {
    for (const int_t expected : kAtomicIntValues) {
      atomic_int_t atomic{current};
      const int_t new_value{~expected};
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
  constexpr int_t kMagicValue{-0x01234567};
  atomic_int_t atomic{kMagicValue};
  FND_TEST_TRUE(
    compare_exchange(atomic, kMagicValue, kMagicValue) == kMagicValue);
  FND_TEST_TRUE(atomic.value == kMagicValue);

  // A retry loop: a stale expected fails, and the returned value is the next
  // expected, which succeeds.
  atomic_int_t counter{-41};
  int_t expected{0};
  int_t prev_value{compare_exchange(counter, expected, expected - 1)};
  FND_TEST_TRUE(prev_value == -41);
  FND_TEST_TRUE(counter.value == -41);
  expected = prev_value;
  prev_value = compare_exchange(counter, expected, expected - 1);
  FND_TEST_TRUE(prev_value == -41);
  FND_TEST_TRUE(counter.value == -42);
}

void unittests_atomics_atomic_int_fetch_add()
{
  // a + b with wrapping: signed overflow is undefined, unsigned wraps.
  const auto wrapping_add = [](const int_t a, const int_t b) {
    return static_cast<int_t>(static_cast<uint_t>(a) + static_cast<uint_t>(b));
  };

  for (const int_t current : kAtomicIntValues) {
    for (const int_t x : kAtomicIntValues) {
      atomic_int_t atomic{current};
      FND_TEST_TRUE(fetch_add(atomic, x) == current);
      FND_TEST_TRUE(atomic.value == wrapping_add(current, x));
    }
  }

  // Overflow wraps, in both directions.
  atomic_int_t atomic{kIntMaxValue};
  FND_TEST_TRUE(fetch_add(atomic, 1) == kIntMaxValue);
  FND_TEST_TRUE(atomic.value == kIntMinValue);
  FND_TEST_TRUE(fetch_add(atomic, -1) == kIntMinValue);
  FND_TEST_TRUE(atomic.value == kIntMaxValue);
}

void unittests_atomics_atomic_int_fetch_and()
{
  for (const int_t current : kAtomicIntValues) {
    for (const int_t x : kAtomicIntValues) {
      atomic_int_t atomic{current};
      FND_TEST_TRUE(fetch_and(atomic, x) == current);
      FND_TEST_TRUE(atomic.value == (current & x));
    }
  }
}

void unittests_atomics_atomic_int_fetch_or()
{
  for (const int_t current : kAtomicIntValues) {
    for (const int_t x : kAtomicIntValues) {
      atomic_int_t atomic{current};
      FND_TEST_TRUE(fetch_or(atomic, x) == current);
      FND_TEST_TRUE(atomic.value == (current | x));
    }
  }
}

void unittests_atomics_atomic_int_fetch_sub()
{
  // a - b with wrapping: signed overflow is undefined, unsigned wraps.
  const auto wrapping_sub = [](const int_t a, const int_t b) {
    return static_cast<int_t>(static_cast<uint_t>(a) - static_cast<uint_t>(b));
  };

  for (const int_t current : kAtomicIntValues) {
    for (const int_t x : kAtomicIntValues) {
      atomic_int_t atomic{current};
      FND_TEST_TRUE(fetch_sub(atomic, x) == current);
      FND_TEST_TRUE(atomic.value == wrapping_sub(current, x));
    }
  }

  // Overflow wraps, in both directions.
  atomic_int_t atomic{kIntMinValue};
  FND_TEST_TRUE(fetch_sub(atomic, 1) == kIntMinValue);
  FND_TEST_TRUE(atomic.value == kIntMaxValue);
  FND_TEST_TRUE(fetch_sub(atomic, -1) == kIntMaxValue);
  FND_TEST_TRUE(atomic.value == kIntMinValue);

  // x = kIntMinValue, whose negation would overflow.
  atomic_int_t min_atomic{0};
  FND_TEST_TRUE(fetch_sub(min_atomic, kIntMinValue) == 0);
  FND_TEST_TRUE(min_atomic.value == kIntMinValue);
  FND_TEST_TRUE(fetch_sub(min_atomic, kIntMinValue) == kIntMinValue);
  FND_TEST_TRUE(min_atomic.value == 0);
  store(min_atomic, -1);
  FND_TEST_TRUE(fetch_sub(min_atomic, kIntMinValue) == -1);
  FND_TEST_TRUE(min_atomic.value == kIntMaxValue);
}

void unittests_atomics_atomic_int_fetch_xor()
{
  for (const int_t current : kAtomicIntValues) {
    for (const int_t x : kAtomicIntValues) {
      atomic_int_t atomic{current};
      FND_TEST_TRUE(fetch_xor(atomic, x) == current);
      FND_TEST_TRUE(atomic.value == (current ^ x));
    }
  }
}

void unittests_atomics_atomic_int_load()
{
  // Every order a load accepts returns the value, through a const atomic too.
  for (const int_t value : kAtomicIntValues) {
    const atomic_int_t atomic{value};
    FND_TEST_TRUE(load<EMemoryOrder::kRelaxed>(atomic) == value);
    FND_TEST_TRUE(load<EMemoryOrder::kReadAcquire>(atomic) == value);
    FND_TEST_TRUE(load<EMemoryOrder::kFullFence>(atomic) == value);
    FND_TEST_TRUE(load(atomic) == value);
  }
}

void unittests_atomics_atomic_int_store()
{
  // Every order a store accepts replaces the value, whatever it was before.
  atomic_int_t atomic{};
  for (const int_t value : kAtomicIntValues) {
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
  store(atomic, -0x01234567);
  FND_TEST_TRUE(load(atomic) == -0x01234567);
}

void unittests_atomics_atomic_int()
{
  unittests_atomics_atomic_int_type();
  unittests_atomics_atomic_int_constructors();
  unittests_atomics_atomic_int_compare_exchange();
  unittests_atomics_atomic_int_fetch_add();
  unittests_atomics_atomic_int_fetch_and();
  unittests_atomics_atomic_int_fetch_or();
  unittests_atomics_atomic_int_fetch_sub();
  unittests_atomics_atomic_int_fetch_xor();
  unittests_atomics_atomic_int_load();
  unittests_atomics_atomic_int_store();
}

} // namespace fnd::unittests
