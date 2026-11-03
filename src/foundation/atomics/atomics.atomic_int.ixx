module;
#include <intrin.h>
#include "foundation/core/macros.h"

export module foundation.atomics:atomic_int;
import foundation.core;
import :memory_order;

namespace fnd {

// Copying atomic_int_t or accessing value directly is neither atomic nor
// ordered (value += x is a separate load and store). Copy only while no other
// thread uses it; otherwise use load and store.
export struct atomic_int_t final {
  volatile int_t value{};
};

static_assert(sizeof(atomic_int_t) == sizeof(int_t));
static_assert(alignof(atomic_int_t) == 4);
static_assert(is_same<int_t, __int32>()); // __iso_volatile_* take int_t as is
// MSVC shenanigan: int_t <-> long
static_assert(sizeof(long) == sizeof(int_t));

// Replaces atomic's value with new_value if it equals expected, as one full
// fence. Returns the value before the call. Never fails spuriously.
export inline int_t compare_exchange(
  atomic_int_t& atomic, const int_t expected, const int_t new_value)
{
  FND_ASSERT(is_aligned(&atomic.value, alignof(atomic_int_t)));

  const long prev{_InterlockedCompareExchange(
    reinterpret_cast<volatile long*>(&atomic.value),
    static_cast<long>(new_value), static_cast<long>(expected))};
  return static_cast<int_t>(prev);
}

// Adds x to atomic's value, wrapping on overflow, as one full fence. Returns
// the value before the call.
export inline int_t fetch_add(atomic_int_t& atomic, const int_t x)
{
  FND_ASSERT(is_aligned(&atomic.value, alignof(atomic_int_t)));

  const long prev{_InterlockedExchangeAdd(
    reinterpret_cast<volatile long*>(&atomic.value), static_cast<long>(x))};
  return static_cast<int_t>(prev);
}

// Sets atomic's value to its bitwise AND with x, as one full fence. Returns the
// value before the call; using it costs a lock cmpxchg loop, ignoring it costs
// one lock and.
export inline int_t fetch_and(atomic_int_t& atomic, const int_t x)
{
  FND_ASSERT(is_aligned(&atomic.value, alignof(atomic_int_t)));

  const long prev{_InterlockedAnd(
    reinterpret_cast<volatile long*>(&atomic.value), static_cast<long>(x))};
  return static_cast<int_t>(prev);
}

// Sets atomic's value to its bitwise OR with x, as one full fence. Returns the
// value before the call; using it costs a lock cmpxchg loop, ignoring it costs
// one lock or.
export inline int_t fetch_or(atomic_int_t& atomic, const int_t x)
{
  FND_ASSERT(is_aligned(&atomic.value, alignof(atomic_int_t)));

  const long prev{_InterlockedOr(
    reinterpret_cast<volatile long*>(&atomic.value), static_cast<long>(x))};
  return static_cast<int_t>(prev);
}

// Subtracts x from atomic's value, wrapping on overflow, as one full fence.
// Returns the value before the call.
export inline int_t fetch_sub(atomic_int_t& atomic, const int_t x)
{
  FND_ASSERT(is_aligned(&atomic.value, alignof(atomic_int_t)));

  // Negated as unsigned, where wrapping is defined: -x overflows for
  // x = kIntMinValue.
  const long negated_x{static_cast<long>(0 - static_cast<uint_t>(x))};
  const long prev{_InterlockedExchangeAdd(
    reinterpret_cast<volatile long*>(&atomic.value), negated_x)};
  return static_cast<int_t>(prev);
}

// Sets atomic's value to its bitwise XOR with x, as one full fence. Returns the
// value before the call; using it costs a lock cmpxchg loop, ignoring it costs
// one lock xor.
export inline int_t fetch_xor(atomic_int_t& atomic, const int_t x)
{
  FND_ASSERT(is_aligned(&atomic.value, alignof(atomic_int_t)));

  const long prev{_InterlockedXor(
    reinterpret_cast<volatile long*>(&atomic.value), static_cast<long>(x))};
  return static_cast<int_t>(prev);
}

// atomic's value, read in one untorn access with memory order Order (a full
// fence by default). kWriteRelease is rejected: a load can't release.
export template<EMemoryOrder Order = EMemoryOrder::kFullFence>
int_t load(const atomic_int_t& atomic)
{
  static_assert(
    Order != EMemoryOrder::kWriteRelease,
    "EMemoryOrder::kWriteRelease is meaningless for a load");
  FND_ASSERT(is_aligned(&atomic.value, alignof(atomic_int_t)));

  if constexpr (Order == EMemoryOrder::kFullFence) {
    _ReadWriteBarrier();
    __faststorefence();
    _ReadWriteBarrier();
  }

  const int_t v{__iso_volatile_load32(&atomic.value)};

  if constexpr (Order != EMemoryOrder::kRelaxed) {
    _ReadWriteBarrier();
  }

  return v;
}

// Writes new_value to atomic in one untorn access with memory order Order (a
// full fence by default). kReadAcquire is rejected: a store can't acquire.
export template<EMemoryOrder Order = EMemoryOrder::kFullFence>
void store(atomic_int_t& atomic, const int_t new_value)
{
  static_assert(
    Order != EMemoryOrder::kReadAcquire,
    "EMemoryOrder::kReadAcquire is meaningless for a store");
  FND_ASSERT(is_aligned(&atomic.value, alignof(atomic_int_t)));

  if constexpr (Order == EMemoryOrder::kFullFence) {
    _InterlockedExchange(
      reinterpret_cast<volatile long*>(&atomic.value),
      static_cast<long>(new_value));
  }
  else {
    if constexpr (Order == EMemoryOrder::kWriteRelease) {
      _ReadWriteBarrier();
    }

    __iso_volatile_store32(&atomic.value, new_value);
  }
}

} // namespace fnd
