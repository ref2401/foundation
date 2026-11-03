module;
#include <intrin.h>
#include "foundation/core/macros.h"

export module foundation.atomics:atomic_uint;
import foundation.core;
import :memory_order;

namespace fnd {

// Copying atomic_uint_t or accessing value directly is neither atomic nor
// ordered (value += x is a separate load and store). Copy only while no other
// thread uses it; otherwise use load and store.
export struct atomic_uint_t final {
  volatile uint_t value{};
};

static_assert(sizeof(atomic_uint_t) == sizeof(uint_t));
static_assert(alignof(atomic_uint_t) == 4);
// MSVC shenanigan: uint_t <-> long
static_assert(sizeof(long) == sizeof(uint_t));

// Replaces atomic's value with new_value if it equals expected, as one full
// fence. Returns the value before the call. Never fails spuriously.
export inline uint_t compare_exchange(
  atomic_uint_t& atomic, const uint_t expected, const uint_t new_value)
{
  FND_ASSERT(is_aligned(&atomic.value, alignof(atomic_uint_t)));

  const long prev{_InterlockedCompareExchange(
    reinterpret_cast<volatile long*>(&atomic.value),
    static_cast<long>(new_value), static_cast<long>(expected))};
  return static_cast<uint_t>(prev);
}

// Adds x to atomic's value, wrapping on overflow, as one full fence. Returns
// the value before the call.
export inline uint_t fetch_add(atomic_uint_t& atomic, const uint_t x)
{
  FND_ASSERT(is_aligned(&atomic.value, alignof(atomic_uint_t)));

  const long prev{_InterlockedExchangeAdd(
    reinterpret_cast<volatile long*>(&atomic.value), static_cast<long>(x))};
  return static_cast<uint_t>(prev);
}

// Sets atomic's value to its bitwise AND with x, as one full fence. Returns the
// value before the call; using it costs a lock cmpxchg loop, ignoring it costs
// one lock and.
export inline uint_t fetch_and(atomic_uint_t& atomic, const uint_t x)
{
  FND_ASSERT(is_aligned(&atomic.value, alignof(atomic_uint_t)));

  const long prev{_InterlockedAnd(
    reinterpret_cast<volatile long*>(&atomic.value), static_cast<long>(x))};
  return static_cast<uint_t>(prev);
}

// Sets atomic's value to its bitwise OR with x, as one full fence. Returns the
// value before the call; using it costs a lock cmpxchg loop, ignoring it costs
// one lock or.
export inline uint_t fetch_or(atomic_uint_t& atomic, const uint_t x)
{
  FND_ASSERT(is_aligned(&atomic.value, alignof(atomic_uint_t)));

  const long prev{_InterlockedOr(
    reinterpret_cast<volatile long*>(&atomic.value), static_cast<long>(x))};
  return static_cast<uint_t>(prev);
}

// Subtracts x from atomic's value, wrapping below zero, as one full fence.
// Returns the value before the call.
export inline uint_t fetch_sub(atomic_uint_t& atomic, const uint_t x)
{
  FND_ASSERT(is_aligned(&atomic.value, alignof(atomic_uint_t)));

  const long prev{_InterlockedExchangeAdd(
    reinterpret_cast<volatile long*>(&atomic.value), static_cast<long>(0 - x))};
  return static_cast<uint_t>(prev);
}

// Sets atomic's value to its bitwise XOR with x, as one full fence. Returns the
// value before the call; using it costs a lock cmpxchg loop, ignoring it costs
// one lock xor.
export inline uint_t fetch_xor(atomic_uint_t& atomic, const uint_t x)
{
  FND_ASSERT(is_aligned(&atomic.value, alignof(atomic_uint_t)));

  const long prev{_InterlockedXor(
    reinterpret_cast<volatile long*>(&atomic.value), static_cast<long>(x))};
  return static_cast<uint_t>(prev);
}

// atomic's value, read in one untorn access with memory order Order (a full
// fence by default). kWriteRelease is rejected: a load can't release.
export template<EMemoryOrder Order = EMemoryOrder::kFullFence>
uint_t load(const atomic_uint_t& atomic)
{
  static_assert(
    Order != EMemoryOrder::kWriteRelease,
    "EMemoryOrder::kWriteRelease is meaningless for a load");
  FND_ASSERT(is_aligned(&atomic.value, alignof(atomic_uint_t)));

  if constexpr (Order == EMemoryOrder::kFullFence) {
    _ReadWriteBarrier();
    __faststorefence();
    _ReadWriteBarrier();
  }

  const uint_t v{static_cast<uint_t>(__iso_volatile_load32(
    reinterpret_cast<const volatile __int32*>(&atomic.value)))};

  if constexpr (Order != EMemoryOrder::kRelaxed) {
    _ReadWriteBarrier();
  }

  return v;
}

// Writes new_value to atomic in one untorn access with memory order Order (a
// full fence by default). kReadAcquire is rejected: a store can't acquire.
export template<EMemoryOrder Order = EMemoryOrder::kFullFence>
void store(atomic_uint_t& atomic, const uint_t new_value)
{
  static_assert(
    Order != EMemoryOrder::kReadAcquire,
    "EMemoryOrder::kReadAcquire is meaningless for a store");
  FND_ASSERT(is_aligned(&atomic.value, alignof(atomic_uint_t)));

  if constexpr (Order == EMemoryOrder::kFullFence) {
    _InterlockedExchange(
      reinterpret_cast<volatile long*>(&atomic.value),
      static_cast<long>(new_value));
  }
  else {
    if constexpr (Order == EMemoryOrder::kWriteRelease) {
      _ReadWriteBarrier();
    }

    __iso_volatile_store32(
      reinterpret_cast<volatile __int32*>(&atomic.value),
      static_cast<__int32>(new_value));
  }
}

} // namespace fnd
