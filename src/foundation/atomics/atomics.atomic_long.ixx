module;
#include <intrin.h>
#include "foundation/core/macros.h"

export module foundation.atomics:atomic_long;
import foundation.core;
import :memory_order;

namespace fnd {

// Copying atomic_long_t or accessing value directly is neither atomic nor
// ordered (value += x is a separate load and store). Copy only while no other
// thread uses it; otherwise use load and store.
export struct atomic_long_t final {
  volatile long_t value{};
};

static_assert(sizeof(atomic_long_t) == sizeof(long_t));
static_assert(alignof(atomic_long_t) == 8);
static_assert(is_same<long_t, __int64>()); // the intrinsics take long_t as is

// Replaces atomic's value with new_value if it equals expected, as one full
// fence. Returns the value before the call. Never fails spuriously.
export inline long_t compare_exchange(
  atomic_long_t& atomic, const long_t expected, const long_t new_value)
{
  FND_ASSERT(is_aligned(&atomic.value, alignof(atomic_long_t)));

  return _InterlockedCompareExchange64(&atomic.value, new_value, expected);
}

// Adds x to atomic's value, wrapping on overflow, as one full fence. Returns
// the value before the call.
export inline long_t fetch_add(atomic_long_t& atomic, const long_t x)
{
  FND_ASSERT(is_aligned(&atomic.value, alignof(atomic_long_t)));

  return _InterlockedExchangeAdd64(&atomic.value, x);
}

// Sets atomic's value to its bitwise AND with x, as one full fence. Returns the
// value before the call; using it costs a lock cmpxchg loop, ignoring it costs
// one lock and.
export inline long_t fetch_and(atomic_long_t& atomic, const long_t x)
{
  FND_ASSERT(is_aligned(&atomic.value, alignof(atomic_long_t)));

  return _InterlockedAnd64(&atomic.value, x);
}

// Sets atomic's value to its bitwise OR with x, as one full fence. Returns the
// value before the call; using it costs a lock cmpxchg loop, ignoring it costs
// one lock or.
export inline long_t fetch_or(atomic_long_t& atomic, const long_t x)
{
  FND_ASSERT(is_aligned(&atomic.value, alignof(atomic_long_t)));

  return _InterlockedOr64(&atomic.value, x);
}

// Subtracts x from atomic's value, wrapping on overflow, as one full fence.
// Returns the value before the call.
export inline long_t fetch_sub(atomic_long_t& atomic, const long_t x)
{
  FND_ASSERT(is_aligned(&atomic.value, alignof(atomic_long_t)));

  // Negated as unsigned, where wrapping is defined: -x overflows for
  // x = kLongMinValue.
  const long_t negated_x{static_cast<long_t>(0 - static_cast<ulong_t>(x))};
  return _InterlockedExchangeAdd64(&atomic.value, negated_x);
}

// Sets atomic's value to its bitwise XOR with x, as one full fence. Returns the
// value before the call; using it costs a lock cmpxchg loop, ignoring it costs
// one lock xor.
export inline long_t fetch_xor(atomic_long_t& atomic, const long_t x)
{
  FND_ASSERT(is_aligned(&atomic.value, alignof(atomic_long_t)));

  return _InterlockedXor64(&atomic.value, x);
}

// atomic's value, read in one untorn access with memory order Order (a full
// fence by default). kWriteRelease is rejected: a load can't release.
export template<EMemoryOrder Order = EMemoryOrder::kFullFence>
long_t load(const atomic_long_t& atomic)
{
  static_assert(
    Order != EMemoryOrder::kWriteRelease,
    "EMemoryOrder::kWriteRelease is meaningless for a load");
  FND_ASSERT(is_aligned(&atomic.value, alignof(atomic_long_t)));

  if constexpr (Order == EMemoryOrder::kFullFence) {
    _ReadWriteBarrier();
    __faststorefence();
    _ReadWriteBarrier();
  }

  const long_t v{__iso_volatile_load64(&atomic.value)};

  if constexpr (Order != EMemoryOrder::kRelaxed) {
    _ReadWriteBarrier();
  }

  return v;
}

// Writes new_value to atomic in one untorn access with memory order Order (a
// full fence by default). kReadAcquire is rejected: a store can't acquire.
export template<EMemoryOrder Order = EMemoryOrder::kFullFence>
void store(atomic_long_t& atomic, const long_t new_value)
{
  static_assert(
    Order != EMemoryOrder::kReadAcquire,
    "EMemoryOrder::kReadAcquire is meaningless for a store");
  FND_ASSERT(is_aligned(&atomic.value, alignof(atomic_long_t)));

  if constexpr (Order == EMemoryOrder::kFullFence) {
    _InterlockedExchange64(&atomic.value, new_value);
  }
  else {
    if constexpr (Order == EMemoryOrder::kWriteRelease) {
      _ReadWriteBarrier();
    }

    __iso_volatile_store64(&atomic.value, new_value);
  }
}

} // namespace fnd
