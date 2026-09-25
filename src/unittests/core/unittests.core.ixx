module;
#include <string.h>
#include "foundation/unittests.h"


export module unittests.core;
import :arithmetic_types;
import :arithmetic;
import :span;


namespace fnd::unittests {

void unittests_source_location_t();

export void run_unittests_core()
{
    unittests_core_arithmetic_types();
    unittests_core_arithmetic();
    unittests_source_location_t();
    unittests_span_t();
}



// ---------------------------------------------------------------------------
// source_location_t
// ---------------------------------------------------------------------------

void unittests_source_location_t_is_pod_type()
{
    static_assert(PodType<source_location_t>);
}

void unittests_source_location_t_make_source_location()
{
    const source_location_t s0 = make_source_location();
    const source_location_t s1 = make_source_location();
    FND_TEST_TRUE(s0.line + 1 == s1.line);
    FND_TEST_TRUE(s0.filename != nullptr);
    FND_TEST_TRUE(s0.function_name != nullptr);
    FND_TEST_TRUE(strcmp(s0.filename, s1.filename) == 0);
    FND_TEST_TRUE(strcmp(s0.function_name, s1.function_name) == 0);
}

void unittests_source_location_t()
{
    unittests_source_location_t_is_pod_type();
    unittests_source_location_t_make_source_location();
}

} // namespace fnd::unittests
