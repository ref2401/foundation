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

// ---------------------------------------------------------------------------
// bool3_t
// ---------------------------------------------------------------------------

constexpr bool_t test_components(
    const bool3_t v, const bool_t x, const bool_t y, const bool_t z)
{
    return v.x == x && v.y == y && v.z == z;
}

void unittests_math_vector_bool3_type()
{
    static_assert(PodType<bool3_t>);
    static_assert(sizeof(bool3_t) == 3 * sizeof(bool_t));
    // The ctor(bool_t) is explicit: no bool_t (or pointer, or int) converts to bool3_t by accident.
    static_assert(!is_convertible<bool_t, bool3_t>());
    // Likewise, a bool2_t never widens to bool3_t silently.
    static_assert(!is_convertible<bool2_t, bool3_t>());
}

void unittests_math_vector_bool3_constructors()
{
    FND_TEST_TRUE(test_components(bool3_t{}, false, false, false));
    FND_TEST_TRUE(test_components(bool3_t{true}, true, true, true));
    FND_TEST_TRUE(test_components(bool3_t{false}, false, false, false));
    FND_TEST_TRUE(test_components(bool3_t{true, false, false}, true, false, false));
    FND_TEST_TRUE(test_components(bool3_t{false, true, false}, false, true, false));
    FND_TEST_TRUE(test_components(bool3_t{false, false, true}, false, false, true));
    // From a bool2_t: z is false unless given.
    FND_TEST_TRUE(test_components(bool3_t{bool2_t{true, false}}, true, false, false));
    FND_TEST_TRUE(test_components(bool3_t{bool2_t{true, true}}, true, true, false));
    FND_TEST_TRUE(test_components(bool3_t{bool2_t{true, false}, true}, true, false, true));
    FND_TEST_TRUE(test_components(bool3_t{bool2_t{false, true}, false}, false, true, false));
}

void unittests_math_vector_bool3_subscript_operator()
{
    const bool3_t v{true, false, true};
    FND_TEST_TRUE(v[0]);
    FND_TEST_FALSE(v[1]);
    FND_TEST_TRUE(v[2]);

    // The non-const overload returns a reference into the vector itself.
    bool3_t w;
    w[2] = true;
    FND_TEST_TRUE(test_components(w, false, false, true));

    w[0] = true;
    w[1] = true;
    w[2] = false;
    FND_TEST_TRUE(test_components(w, true, true, false));
}

void unittests_math_vector_bool3_not_operator()
{
    FND_TEST_TRUE(test_components(!bool3_t{true, false, true}, false, true, false));
    FND_TEST_TRUE(test_components(!bool3_t{false, false, false}, true, true, true));
    FND_TEST_TRUE(test_components(!bool3_t{true, true, true}, false, false, false));
}

void unittests_math_vector_bool3_all()
{
    FND_TEST_TRUE(all(bool3_t{true, true, true}));
    FND_TEST_FALSE(all(bool3_t{false, true, true}));
    FND_TEST_FALSE(all(bool3_t{true, false, true}));
    FND_TEST_FALSE(all(bool3_t{true, true, false}));
    FND_TEST_FALSE(all(bool3_t{false, false, false}));
}

void unittests_math_vector_bool3_any()
{
    FND_TEST_TRUE(any(bool3_t{true, true, true}));
    FND_TEST_TRUE(any(bool3_t{true, false, false}));
    FND_TEST_TRUE(any(bool3_t{false, true, false}));
    FND_TEST_TRUE(any(bool3_t{false, false, true}));
    FND_TEST_FALSE(any(bool3_t{false, false, false}));
}

void unittests_math_vector_bool3_equality_operator()
{
    const bool3_t tft{true, false, true};
    FND_TEST_TRUE(test_components(tft == bool3_t{true, false, true}, true, true, true));
    FND_TEST_TRUE(test_components(tft == bool3_t{true, true, true}, true, false, true));
    FND_TEST_TRUE(test_components(tft == bool3_t{false, true, false}, false, false, false));
    // bool_t on either side is compared with every component.
    FND_TEST_TRUE(test_components(tft == true, true, false, true));
    FND_TEST_TRUE(test_components(tft == false, false, true, false));
    FND_TEST_TRUE(test_components(true == tft, true, false, true));
    FND_TEST_TRUE(test_components(false == tft, false, true, false));
}

void unittests_math_vector_bool3_inequality_operator()
{
    const bool3_t tft{true, false, true};
    FND_TEST_TRUE(test_components(tft != bool3_t{true, false, true}, false, false, false));
    FND_TEST_TRUE(test_components(tft != bool3_t{true, true, true}, false, true, false));
    FND_TEST_TRUE(test_components(tft != bool3_t{false, true, false}, true, true, true));
    FND_TEST_TRUE(test_components(tft != true, false, true, false));
    FND_TEST_TRUE(test_components(tft != false, true, false, true));
    FND_TEST_TRUE(test_components(true != tft, false, true, false));
    FND_TEST_TRUE(test_components(false != tft, true, false, true));
}

void unittests_math_vector_bool3_logical_and_operator()
{
    const bool3_t tft{true, false, true};
    FND_TEST_TRUE(test_components(tft && bool3_t{true, true, true}, true, false, true));
    FND_TEST_TRUE(test_components(tft && bool3_t{false, true, true}, false, false, true));
    FND_TEST_TRUE(test_components(
        bool3_t{true, true, true} && bool3_t{true, true, true}, true, true, true));
    FND_TEST_TRUE(test_components(tft && true, true, false, true));
    FND_TEST_TRUE(test_components(tft && false, false, false, false));
    FND_TEST_TRUE(test_components(true && tft, true, false, true));
    FND_TEST_TRUE(test_components(false && tft, false, false, false));
}

void unittests_math_vector_bool3_logical_or_operator()
{
    const bool3_t tft{true, false, true};
    FND_TEST_TRUE(test_components(tft || bool3_t{false, false, false}, true, false, true));
    FND_TEST_TRUE(test_components(tft || bool3_t{false, true, false}, true, true, true));
    FND_TEST_TRUE(test_components(
        bool3_t{false, false, false} || bool3_t{false, false, false}, false, false, false));
    FND_TEST_TRUE(test_components(tft || true, true, true, true));
    FND_TEST_TRUE(test_components(tft || false, true, false, true));
    FND_TEST_TRUE(test_components(true || tft, true, true, true));
    FND_TEST_TRUE(test_components(false || tft, true, false, true));
}

// ---------------------------------------------------------------------------
// bool4_t
// ---------------------------------------------------------------------------

constexpr bool_t test_components(
    const bool4_t v, const bool_t x, const bool_t y, const bool_t z, const bool_t w)
{
    return v.x == x && v.y == y && v.z == z && v.w == w;
}

void unittests_math_vector_bool4_type()
{
    static_assert(PodType<bool4_t>);
    static_assert(sizeof(bool4_t) == 4 * sizeof(bool_t));
    // The ctor(bool_t) is explicit: no bool_t (or pointer, or int) converts to bool4_t by accident.
    static_assert(!is_convertible<bool_t, bool4_t>());
    // Likewise, a bool2_t or bool3_t never widens to bool4_t silently.
    static_assert(!is_convertible<bool3_t, bool4_t>());
    static_assert(!is_convertible<bool2_t, bool4_t>());
}

void unittests_math_vector_bool4_constructors()
{
    FND_TEST_TRUE(test_components(bool4_t{}, false, false, false, false));
    FND_TEST_TRUE(test_components(bool4_t{true}, true, true, true, true));
    FND_TEST_TRUE(test_components(bool4_t{false}, false, false, false, false));
    FND_TEST_TRUE(test_components(bool4_t{true, false, false, false}, true, false, false, false));
    FND_TEST_TRUE(test_components(bool4_t{false, true, false, false}, false, true, false, false));
    FND_TEST_TRUE(test_components(bool4_t{false, false, true, false}, false, false, true, false));
    FND_TEST_TRUE(test_components(bool4_t{false, false, false, true}, false, false, false, true));
    // From a bool2_t: z and w are false unless given.
    FND_TEST_TRUE(test_components(
        bool4_t{bool2_t{true, false}}, true, false, false, false));
    FND_TEST_TRUE(test_components(
        bool4_t{bool2_t{true, true}, true}, true, true, true, false));
    FND_TEST_TRUE(test_components(
        bool4_t{bool2_t{false, true}, false, true}, false, true, false, true));
    FND_TEST_TRUE(test_components(
        bool4_t{bool2_t{true, false}, true, true}, true, false, true, true));
    // From a bool3_t: w is false unless given.
    FND_TEST_TRUE(test_components(
        bool4_t{bool3_t{true, false, true}}, true, false, true, false));
    FND_TEST_TRUE(test_components(
        bool4_t{bool3_t{true, true, true}}, true, true, true, false));
    FND_TEST_TRUE(test_components(
        bool4_t{bool3_t{true, false, true}, true}, true, false, true, true));
    FND_TEST_TRUE(test_components(
        bool4_t{bool3_t{false, true, false}, false}, false, true, false, false));
}

void unittests_math_vector_bool4_subscript_operator()
{
    const bool4_t v{true, false, true, false};
    FND_TEST_TRUE(v[0]);
    FND_TEST_FALSE(v[1]);
    FND_TEST_TRUE(v[2]);
    FND_TEST_FALSE(v[3]);

    // The non-const overload returns a reference into the vector itself.
    bool4_t w;
    w[3] = true;
    FND_TEST_TRUE(test_components(w, false, false, false, true));

    w[0] = true;
    w[1] = true;
    w[2] = true;
    w[3] = false;
    FND_TEST_TRUE(test_components(w, true, true, true, false));
}

void unittests_math_vector_bool4_not_operator()
{
    FND_TEST_TRUE(test_components(!bool4_t{true, false, true, false}, false, true, false, true));
    FND_TEST_TRUE(test_components(!bool4_t{false, false, false, false}, true, true, true, true));
    FND_TEST_TRUE(test_components(!bool4_t{true, true, true, true}, false, false, false, false));
}

void unittests_math_vector_bool4_all()
{
    FND_TEST_TRUE(all(bool4_t{true, true, true, true}));
    FND_TEST_FALSE(all(bool4_t{false, true, true, true}));
    FND_TEST_FALSE(all(bool4_t{true, false, true, true}));
    FND_TEST_FALSE(all(bool4_t{true, true, false, true}));
    FND_TEST_FALSE(all(bool4_t{true, true, true, false}));
    FND_TEST_FALSE(all(bool4_t{false, false, false, false}));
}

void unittests_math_vector_bool4_any()
{
    FND_TEST_TRUE(any(bool4_t{true, true, true, true}));
    FND_TEST_TRUE(any(bool4_t{true, false, false, false}));
    FND_TEST_TRUE(any(bool4_t{false, true, false, false}));
    FND_TEST_TRUE(any(bool4_t{false, false, true, false}));
    FND_TEST_TRUE(any(bool4_t{false, false, false, true}));
    FND_TEST_FALSE(any(bool4_t{false, false, false, false}));
}

void unittests_math_vector_bool4_equality_operator()
{
    const bool4_t tftf{true, false, true, false};
    FND_TEST_TRUE(test_components(
        tftf == bool4_t{true, false, true, false}, true, true, true, true));
    FND_TEST_TRUE(test_components(
        tftf == bool4_t{true, true, true, true}, true, false, true, false));
    FND_TEST_TRUE(test_components(
        tftf == bool4_t{false, true, false, true}, false, false, false, false));
    // bool_t on either side is compared with every component.
    FND_TEST_TRUE(test_components(tftf == true, true, false, true, false));
    FND_TEST_TRUE(test_components(tftf == false, false, true, false, true));
    FND_TEST_TRUE(test_components(true == tftf, true, false, true, false));
    FND_TEST_TRUE(test_components(false == tftf, false, true, false, true));
}

void unittests_math_vector_bool4_inequality_operator()
{
    const bool4_t tftf{true, false, true, false};
    FND_TEST_TRUE(test_components(
        tftf != bool4_t{true, false, true, false}, false, false, false, false));
    FND_TEST_TRUE(test_components(
        tftf != bool4_t{true, true, true, true}, false, true, false, true));
    FND_TEST_TRUE(test_components(
        tftf != bool4_t{false, true, false, true}, true, true, true, true));
    FND_TEST_TRUE(test_components(tftf != true, false, true, false, true));
    FND_TEST_TRUE(test_components(tftf != false, true, false, true, false));
    FND_TEST_TRUE(test_components(true != tftf, false, true, false, true));
    FND_TEST_TRUE(test_components(false != tftf, true, false, true, false));
}

void unittests_math_vector_bool4_logical_and_operator()
{
    const bool4_t tftf{true, false, true, false};
    FND_TEST_TRUE(test_components(
        tftf && bool4_t{true, true, true, true}, true, false, true, false));
    FND_TEST_TRUE(test_components(
        tftf && bool4_t{false, true, true, true}, false, false, true, false));
    FND_TEST_TRUE(test_components(
        bool4_t{true, true, true, true} && bool4_t{true, true, true, true}, true, true, true, true));
    FND_TEST_TRUE(test_components(tftf && true, true, false, true, false));
    FND_TEST_TRUE(test_components(tftf && false, false, false, false, false));
    FND_TEST_TRUE(test_components(true && tftf, true, false, true, false));
    FND_TEST_TRUE(test_components(false && tftf, false, false, false, false));
}

void unittests_math_vector_bool4_logical_or_operator()
{
    const bool4_t tftf{true, false, true, false};
    FND_TEST_TRUE(test_components(
        tftf || bool4_t{false, false, false, false}, true, false, true, false));
    FND_TEST_TRUE(test_components(
        tftf || bool4_t{false, true, false, false}, true, true, true, false));
    FND_TEST_TRUE(test_components(
        bool4_t{false, false, false, false} || bool4_t{false, false, false, false},
        false, false, false, false));
    FND_TEST_TRUE(test_components(tftf || true, true, true, true, true));
    FND_TEST_TRUE(test_components(tftf || false, true, false, true, false));
    FND_TEST_TRUE(test_components(true || tftf, true, true, true, true));
    FND_TEST_TRUE(test_components(false || tftf, true, false, true, false));
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

    unittests_math_vector_bool3_type();
    unittests_math_vector_bool3_constructors();
    unittests_math_vector_bool3_subscript_operator();
    unittests_math_vector_bool3_not_operator();
    unittests_math_vector_bool3_all();
    unittests_math_vector_bool3_any();
    unittests_math_vector_bool3_equality_operator();
    unittests_math_vector_bool3_inequality_operator();
    unittests_math_vector_bool3_logical_and_operator();
    unittests_math_vector_bool3_logical_or_operator();

    unittests_math_vector_bool4_type();
    unittests_math_vector_bool4_constructors();
    unittests_math_vector_bool4_subscript_operator();
    unittests_math_vector_bool4_not_operator();
    unittests_math_vector_bool4_all();
    unittests_math_vector_bool4_any();
    unittests_math_vector_bool4_equality_operator();
    unittests_math_vector_bool4_inequality_operator();
    unittests_math_vector_bool4_logical_and_operator();
    unittests_math_vector_bool4_logical_or_operator();
}

} // namespace fnd::unittests
