export module unittests.memory;
import :utility;
import :block;
import :allocator_heap;
import :unique_ptr;

namespace fnd::unittests {

export void run_unittests_memory()
{
  unittests_memory_utility();
  unittests_memory_block();
  unittests_memory_allocator_heap();
  unittests_memory_unique_ptr();
}

} // namespace fnd::unittests
