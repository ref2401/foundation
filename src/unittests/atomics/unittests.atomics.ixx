export module unittests.atomics;
import :atomic_long;
import :atomic_uint;
import :atomic_ulong;

namespace fnd::unittests {

export void run_unittests_atomics()
{
  unittests_atomics_atomic_long();
  unittests_atomics_atomic_uint();
  unittests_atomics_atomic_ulong();
}

} // namespace fnd::unittests
