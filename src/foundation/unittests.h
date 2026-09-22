#pragma once

import foundation.core;

#define FND_TEST_TRUE(condition) \
    fnd::test_true((condition), #condition, fnd::make_source_location())

namespace fnd {

void test_true(
    const bool condition, const char_t* const message, 
    const source_location_t srcloc);

} // namespace fnd
