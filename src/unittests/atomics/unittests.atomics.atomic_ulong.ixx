module;
#include "foundation/unittests.h"


export module unittests.atomics:atomic_ulong;
import foundation.atomics;
import foundation.core;

namespace fnd::unittests {

export void unittests_atomics_atomic_ulong();

// Edge values and a pattern with every byte distinct: a value whose top bit is
// set is a negative __int64 inside load and store.
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

  const atomic_ulong_t atomic{};
  static_assert(is_same<decltype(load(atomic)), ulong_t>());
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
  unittests_atomics_atomic_ulong_load();
  unittests_atomics_atomic_ulong_store();
}

} // namespace fnd::unittests
