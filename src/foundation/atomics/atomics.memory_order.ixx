export module foundation.atomics:memory_order;
import foundation.core;

namespace fnd {

export enum class EMemoryOrder : ubyte_t {
  kRelaxed,
  kReadAcquire,
  kWriteRelease,
  kFullFence
};

} // namespace fnd
