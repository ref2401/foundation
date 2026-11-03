module;
#include <intrin.h>
#include "foundation/core/macros.h"

export module foundation.atomics:atomic_ulong;
import foundation.core;
import :memory_order;

namespace fnd {

// Copying atomic_ulong_t or accessing value directly is neither atomic nor
// ordered (value += x is a separate load and store). Copy only while no other
// thread uses it; otherwise use load and store.
export struct atomic_ulong_t final {
  volatile ulong_t value{};
};

static_assert(sizeof(atomic_ulong_t) == sizeof(ulong_t));
static_assert(alignof(atomic_ulong_t) == 8);
static_assert(is_same<ulong_t, unsigned __int64>()); // ulong_t <-> __int64


// Replaces atomic's value with new_value if it equals expected, as one full
// fence. Returns the value before the call. Never fails spuriously.
export inline ulong_t compare_exchange(
  atomic_ulong_t& atomic, const ulong_t expected, const ulong_t new_value)
{
  FND_ASSERT(is_aligned(&atomic.value, alignof(atomic_ulong_t)));

  const __int64 prev{_InterlockedCompareExchange64(
    reinterpret_cast<volatile __int64*>(&atomic.value),
    static_cast<__int64>(new_value), static_cast<__int64>(expected))};
  return static_cast<ulong_t>(prev);
}

// Adds x to atomic's value, wrapping on overflow, as one full fence. Returns
// the value before the call.
export inline ulong_t fetch_add(atomic_ulong_t& atomic, const ulong_t x)
{
  FND_ASSERT(is_aligned(&atomic.value, alignof(atomic_ulong_t)));

  const __int64 prev{_InterlockedExchangeAdd64(
    reinterpret_cast<volatile __int64*>(&atomic.value),
    static_cast<__int64>(x))};
  return static_cast<ulong_t>(prev);
}

// Sets atomic's value to its bitwise AND with x, as one full fence. Returns the
// value before the call; using it costs a lock cmpxchg loop, ignoring it costs
// one lock and.
export inline ulong_t fetch_and(atomic_ulong_t& atomic, const ulong_t x)
{
  FND_ASSERT(is_aligned(&atomic.value, alignof(atomic_ulong_t)));

  const __int64 prev{_InterlockedAnd64(
    reinterpret_cast<volatile __int64*>(&atomic.value),
    static_cast<__int64>(x))};
  return static_cast<ulong_t>(prev);
}

// Sets atomic's value to its bitwise OR with x, as one full fence. Returns the
// value before the call; using it costs a lock cmpxchg loop, ignoring it costs
// one lock or.
export inline ulong_t fetch_or(atomic_ulong_t& atomic, const ulong_t x)
{
  FND_ASSERT(is_aligned(&atomic.value, alignof(atomic_ulong_t)));

  const __int64 prev{_InterlockedOr64(
    reinterpret_cast<volatile __int64*>(&atomic.value),
    static_cast<__int64>(x))};
  return static_cast<ulong_t>(prev);
}

// Subtracts x from atomic's value, wrapping below zero, as one full fence.
// Returns the value before the call.
export inline ulong_t fetch_sub(atomic_ulong_t& atomic, const ulong_t x)
{
  FND_ASSERT(is_aligned(&atomic.value, alignof(atomic_ulong_t)));

  const __int64 prev{_InterlockedExchangeAdd64(
    reinterpret_cast<volatile __int64*>(&atomic.value),
    static_cast<__int64>(0 - x))};
  return static_cast<ulong_t>(prev);
}

// Sets atomic's value to its bitwise XOR with x, as one full fence. Returns the
// value before the call; using it costs a lock cmpxchg loop, ignoring it costs
// one lock xor.
export inline ulong_t fetch_xor(atomic_ulong_t& atomic, const ulong_t x)
{
  FND_ASSERT(is_aligned(&atomic.value, alignof(atomic_ulong_t)));

  const __int64 prev{_InterlockedXor64(
    reinterpret_cast<volatile __int64*>(&atomic.value),
    static_cast<__int64>(x))};
  return static_cast<ulong_t>(prev);
}

// atomic's value, read in one untorn access with memory order Order (a full
// fence by default). kWriteRelease is rejected: a load can't release.
export template<EMemoryOrder Order = EMemoryOrder::kFullFence>
ulong_t load(const atomic_ulong_t& atomic)
{
  static_assert(
    Order != EMemoryOrder::kWriteRelease,
    "EMemoryOrder::kWriteRelease is meaningless for a load");
  FND_ASSERT(is_aligned(&atomic.value, alignof(atomic_ulong_t)));

  if constexpr (Order == EMemoryOrder::kFullFence) {
    _ReadWriteBarrier();
    __faststorefence();
    _ReadWriteBarrier();
  }

  const ulong_t v{static_cast<ulong_t>(__iso_volatile_load64(
    reinterpret_cast<const volatile __int64*>(&atomic.value)))};

  if constexpr (Order != EMemoryOrder::kRelaxed) {
    _ReadWriteBarrier();
  }

  return v;
}

// Writes new_value to atomic in one untorn access with memory order Order (a
// full fence by default). kReadAcquire is rejected: a store can't acquire.
export template<EMemoryOrder Order = EMemoryOrder::kFullFence>
void store(atomic_ulong_t& atomic, const ulong_t new_value)
{
  static_assert(
    Order != EMemoryOrder::kReadAcquire,
    "EMemoryOrder::kReadAcquire is meaningless for a store");
  FND_ASSERT(is_aligned(&atomic.value, alignof(atomic_ulong_t)));

  if constexpr (Order == EMemoryOrder::kFullFence) {
    _InterlockedExchange64(
      reinterpret_cast<volatile __int64*>(&atomic.value),
      static_cast<__int64>(new_value));
  }
  else {
    if constexpr (Order == EMemoryOrder::kWriteRelease) {
      _ReadWriteBarrier();
    }

    __iso_volatile_store64(
      reinterpret_cast<volatile __int64*>(&atomic.value),
      static_cast<__int64>(new_value));
  }
}

} // namespace fnd
