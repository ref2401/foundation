export module unittests.memory;
import :utility;
import :block;

namespace fnd::unittests {

export void run_unittests_memory()
{
  unittests_memory_utility();
  unittests_memory_block();
}

} // namespace fnd::unittests
