#include <math.h>
#include "foundation/core/macros.h"
#include "foundation/unittests.h"
import foundation.core;
import unittests.core;
import unittests.math;

int main()
{
    using namespace fnd;
    using namespace fnd::unittests;


    initialize();
    run_unittests_core();
    run_unittests_math();
    print_last_run_report();

    return have_all_passed() ? 0 : 1;
}
