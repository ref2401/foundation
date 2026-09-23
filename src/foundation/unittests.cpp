#include "foundation/unittests.h"

#include <stdio.h>

namespace fnd::unittests {

namespace {

ulong_t g_total_unittest_count{0};
ulong_t g_failed_unittest_count{0};


} // namespace

void initialize()
{
    g_total_unittest_count = 0;
    g_failed_unittest_count = 0;
}

bool have_all_passed()
{
    return g_total_unittest_count > 0 && g_failed_unittest_count == 0;
}

void print_last_run_report()
{
    if (g_total_unittest_count == 0) {
        fputs("No unittests were run\n", stdout);
        return;
    }

    const char* const message = have_all_passed()
        ? "All unittests have passed" 
        : "Not all unittests have passed";
    
    const ulong_t num = g_total_unittest_count - g_failed_unittest_count;
    fprintf_s(
        stdout, "%s: %llu/%llu\n", message, num, g_total_unittest_count);
}

void test_true(
    const bool condition, const char_t* const condition_text, 
    const source_location_t srcloc)
{
    ++g_total_unittest_count;

    if (condition) return;

    ++g_failed_unittest_count;
    fprintf_s(
        stdout,
        "%s(%u): unittest failed in '%s'. \"%s\"\n", srcloc.filename, 
        srcloc.line, srcloc.function_name, condition_text);
}

} // namespace fnd::unittests
