module;
#include "foundation/core/macros.h"

#if !defined(FND_ARCH_X64)
  #error Atomics support only x64 architecture at the moment.
#endif // !defined(FND_ARCH_X64)

export module foundation.atomics:memory_order;
import foundation.core;

namespace fnd {

// Each order is kept against all three sources of reordering:
// - the compiler;
// - the CPU's execution;
// - visibility order (a core's writes becoming visible to other cores in a
// different order than it made them).
// A thread whose kReadAcquire read sees the value written by a kWriteRelease
// also sees everything that occurred before that release.
export enum class EMemoryOrder : ubyte_t {
  // No barrier. The operation is atomic (never seen half-written), and all
  // threads agree on the order of writes to that one location (coherency).
  // No ordering against any other read or write.
  kRelaxed,

  // No read or write that occurs after it can move before it. Reads and writes
  // that occur before it may move after it.
  kReadAcquire,

  // No read or write that occurs before it can move after it. Reads and writes
  // that occur after it may move before it. A release write followed by an
  // acquire read of another location may swap places.
  kWriteRelease,

  // No read or write that occurs before or after it can move past it, in
  // either direction.
  kFullFence
};

} // namespace fnd
