#include "foundation/core/macros.h"
#include "foundation/unittests.h"
import unittests.core;


int main()
{
    fnd::unittests::initialize();
    fnd::unittests::run_unittests_core();
    fnd::unittests::print_last_run_report();

    return fnd::unittests::have_all_passed() ? 0 : 1;
}
