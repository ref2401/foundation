#include "foundation/core/macros.h"
#include "foundation/unittests.h"
import foundation.core;
import foundation.math;
import unittests.core;
import unittests.math;
import unittests.memory;

int main()
{
    using namespace fnd;
    using namespace fnd::unittests;

    initialize();
    run_unittests_core();
    run_unittests_math();
    run_unittests_memory();
    print_last_run_report();

    return have_all_passed() ? 0 : 1;
}
