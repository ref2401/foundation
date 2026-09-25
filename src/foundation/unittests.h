#pragma once
import foundation.core;


#define FND_TEST_TRUE(...) \
    fnd::unittests::test_true((__VA_ARGS__), #__VA_ARGS__, fnd::make_source_location())

#define FND_TEST_FALSE(...) FND_TEST_TRUE(!(__VA_ARGS__))


namespace fnd::unittests {

void initialize();
bool_t have_all_passed();
void print_last_run_report();

void test_true(
    const bool_t condition, const char_t* const condition_text, 
    const source_location_t srcloc);

} // namespace fnd::unittests
