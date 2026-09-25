module;
#include "foundation/unittests.h"


export module unittests.math:vector_bool;
import foundation.core;
import foundation.math;

namespace fnd::unittests {

export void unittests_math_vector_bool();

// ---------------------------------------------------------------------------
// bool2_t
// ---------------------------------------------------------------------------

constexpr bool_t test_components(const bool2_t v, const bool_t x, const bool_t y)
{
    return v.x == x && v.y == y;
}

void unittests_math_vector_bool2_type()
{
    static_assert(PodType<bool2_t>);
    static_assert(sizeof(bool2_t) == 2 * sizeof(bool_t));
    // The ctor(bool_t) is explicit: no bool_t (or pointer, or int) converts to bool2_t by accident.
    static_assert(!is_convertible<bool_t, bool2_t>());
}

void unittests_math_vector_bool2_constructors()
{
    FND_TEST_TRUE(test_components(bool2_t{}, false, false));
    FND_TEST_TRUE(test_components(bool2_t{true}, true, true));
    FND_TEST_TRUE(test_components(bool2_t{false}, false, false));
    FND_TEST_TRUE(test_components(bool2_t{true, false}, true, false));
    FND_TEST_TRUE(test_components(bool2_t{false, true}, false, true));
}

void unittests_math_vector_bool2_subscript_operator()
{
    const bool2_t v{true, false};
    FND_TEST_TRUE(v[0]);
    FND_TEST_FALSE(v[1]);

    // The non-const overload returns a reference into the vector itself.
    bool2_t w;
    w[1] = true;
    FND_TEST_TRUE(test_components(w, false, true));

    w[0] = true;
    w[1] = false;
    FND_TEST_TRUE(test_components(w, true, false));
}

void unittests_math_vector_bool2_not_operator()
{
    FND_TEST_TRUE(test_components(!bool2_t{true, false}, false, true));
    FND_TEST_TRUE(test_components(!bool2_t{false, false}, true, true));
    FND_TEST_TRUE(test_components(!bool2_t{true, true}, false, false));
}

void unittests_math_vector_bool2_all()
{
    FND_TEST_TRUE(all(bool2_t{true, true}));
    FND_TEST_FALSE(all(bool2_t{true, false}));
    FND_TEST_FALSE(all(bool2_t{false, true}));
    FND_TEST_FALSE(all(bool2_t{false, false}));
}

void unittests_math_vector_bool2_any()
{
    FND_TEST_TRUE(any(bool2_t{true, true}));
    FND_TEST_TRUE(any(bool2_t{true, false}));
    FND_TEST_TRUE(any(bool2_t{false, true}));
    FND_TEST_FALSE(any(bool2_t{false, false}));
}

void unittests_math_vector_bool2_equality_operator()
{
    const bool2_t tf{true, false};
    FND_TEST_TRUE(test_components(tf == bool2_t{true, false}, true, true));
    FND_TEST_TRUE(test_components(tf == bool2_t{true, true}, true, false));
    FND_TEST_TRUE(test_components(tf == bool2_t{false, true}, false, false));
    // bool_t on either side is compared with every component.
    FND_TEST_TRUE(test_components(tf == true, true, false));
    FND_TEST_TRUE(test_components(tf == false, false, true));
    FND_TEST_TRUE(test_components(true == tf, true, false));
    FND_TEST_TRUE(test_components(false == tf, false, true));
}

void unittests_math_vector_bool2_inequality_operator()
{
    const bool2_t tf{true, false};
    FND_TEST_TRUE(test_components(tf != bool2_t{true, false}, false, false));
    FND_TEST_TRUE(test_components(tf != bool2_t{true, true}, false, true));
    FND_TEST_TRUE(test_components(tf != bool2_t{false, true}, true, true));
    FND_TEST_TRUE(test_components(tf != true, false, true));
    FND_TEST_TRUE(test_components(tf != false, true, false));
    FND_TEST_TRUE(test_components(true != tf, false, true));
    FND_TEST_TRUE(test_components(false != tf, true, false));
}

void unittests_math_vector_bool2_logical_and_operator()
{
    const bool2_t tf{true, false};
    FND_TEST_TRUE(test_components(tf && bool2_t{true, true}, true, false));
    FND_TEST_TRUE(test_components(tf && bool2_t{false, true}, false, false));
    FND_TEST_TRUE(test_components(bool2_t{true, true} && bool2_t{true, true}, true, true));
    FND_TEST_TRUE(test_components(tf && true, true, false));
    FND_TEST_TRUE(test_components(tf && false, false, false));
    FND_TEST_TRUE(test_components(true && tf, true, false));
    FND_TEST_TRUE(test_components(false && tf, false, false));
}

void unittests_math_vector_bool2_logical_or_operator()
{
    const bool2_t tf{true, false};
    FND_TEST_TRUE(test_components(tf || bool2_t{false, false}, true, false));
    FND_TEST_TRUE(test_components(tf || bool2_t{false, true}, true, true));
    FND_TEST_TRUE(test_components(bool2_t{false, false} || bool2_t{false, false}, false, false));
    FND_TEST_TRUE(test_components(tf || true, true, true));
    FND_TEST_TRUE(test_components(tf || false, true, false));
    FND_TEST_TRUE(test_components(true || tf, true, true));
    FND_TEST_TRUE(test_components(false || tf, true, false));
}

void unittests_math_vector_bool()
{
    unittests_math_vector_bool2_type();
    unittests_math_vector_bool2_constructors();
    unittests_math_vector_bool2_subscript_operator();
    unittests_math_vector_bool2_not_operator();
    unittests_math_vector_bool2_all();
    unittests_math_vector_bool2_any();
    unittests_math_vector_bool2_equality_operator();
    unittests_math_vector_bool2_inequality_operator();
    unittests_math_vector_bool2_logical_and_operator();
    unittests_math_vector_bool2_logical_or_operator();
}

} // namespace fnd::unittests
