#pragma once
import foundation.core;


#define FND_TEST_TRUE(condition) \
    fnd::unittests::test_true((condition), #condition, fnd::make_source_location())

#define FND_TEST_FALSE(condition) FND_TEST_TRUE(!(condition))


namespace fnd::unittests {

void initialize();
bool have_all_passed();
void print_last_run_report();

void test_true(
    const bool condition, const char_t* const condition_text, 
    const source_location_t srcloc);

} // namespace fnd::unittests
