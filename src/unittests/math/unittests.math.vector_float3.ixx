module;
#include "foundation/unittests.h"


export module unittests.math:vector_float3;
import foundation.core;
import foundation.math;

namespace fnd::unittests {

export void unittests_math_vector_float3();

// All expected values below are exact in binary, so == is reliable.
constexpr bool_t test_components(
    const float3_t v, const float_t x, const float_t y, const float_t z)
{
    return v.x == x && v.y == y && v.z == z;
}

// Like all(a == b), but a NaN component equals a NaN component.
bool_t equal_or_both_nan(const float3_t a, const float3_t b)
{
    return all((a == b) || (isnan(a) && isnan(b)));
}

void unittests_math_vector_float3_type()
{
    static_assert(PodType<float3_t>);
    static_assert(sizeof(float3_t) == 3 * sizeof(float_t));
    // The ctor(float_t) is explicit.
    static_assert(!is_convertible<float_t, float3_t>());
}

void unittests_math_vector_float3_constructors()
{
    FND_TEST_TRUE(test_components(float3_t{}, 0.0f, 0.0f, 0.0f));
    FND_TEST_TRUE(test_components(float3_t{2.5f}, 2.5f, 2.5f, 2.5f));
    FND_TEST_TRUE(test_components(float3_t{-2.5f}, -2.5f, -2.5f, -2.5f));
    FND_TEST_TRUE(
        test_components(float3_t{3.0f, -4.5f, 6.25f}, 3.0f, -4.5f, 6.25f));
    FND_TEST_TRUE(
        test_components(float3_t{kFloatMinValue, kFloatMaxValue, 0.0f},
            kFloatMinValue, kFloatMaxValue, 0.0f));
}

void unittests_math_vector_float3_subscript_operator()
{
    const float3_t v{3.0f, -4.5f, 6.25f};
    FND_TEST_TRUE(v[0] == 3.0f);
    FND_TEST_TRUE(v[1] == -4.5f);
    FND_TEST_TRUE(v[2] == 6.25f);

    // The non-const overload returns a reference into the vector itself.
    float3_t w;
    w[2] = 9.5f;
    FND_TEST_TRUE(test_components(w, 0.0f, 0.0f, 9.5f));

    w[1] = -1.0f;
    FND_TEST_TRUE(test_components(w, 0.0f, -1.0f, 9.5f));

    w[0] = 0.5f;
    FND_TEST_TRUE(test_components(w, 0.5f, -1.0f, 9.5f));
}

void unittests_math_vector_float3_increment_operators()
{
    float3_t v{1.5f, -1.0f, 0.25f};
    FND_TEST_TRUE(test_components(++v, 2.5f, 0.0f, 1.25f));
    FND_TEST_TRUE(test_components(v, 2.5f, 0.0f, 1.25f));

    // Postfix returns the value before the increment.
    FND_TEST_TRUE(test_components(v++, 2.5f, 0.0f, 1.25f));
    FND_TEST_TRUE(test_components(v, 3.5f, 1.0f, 2.25f));
}

void unittests_math_vector_float3_decrement_operators()
{
    float3_t v{1.5f, -1.0f, 0.25f};
    FND_TEST_TRUE(test_components(--v, 0.5f, -2.0f, -0.75f));
    FND_TEST_TRUE(test_components(v, 0.5f, -2.0f, -0.75f));

    // Postfix returns the value before the decrement.
    FND_TEST_TRUE(test_components(v--, 0.5f, -2.0f, -0.75f));
    FND_TEST_TRUE(test_components(v, -0.5f, -3.0f, -1.75f));
}

void unittests_math_vector_float3_unary_minus_operator()
{
    FND_TEST_TRUE(
        test_components(-float3_t{7.5f, -3.0f, 0.5f}, -7.5f, 3.0f, -0.5f));
    FND_TEST_TRUE(test_components(-float3_t{}, 0.0f, 0.0f, 0.0f));
    FND_TEST_TRUE(test_components(
        -float3_t{kFloatInfinity, kFloatMaxValue, -kFloatInfinity},
        -kFloatInfinity, kFloatMinValue, kFloatInfinity));

    const float3_t n = -float3_t{1.0f, kFloatNaN, 2.0f};
    FND_TEST_TRUE(n.x == -1.0f);
    FND_TEST_TRUE(isnan(n.y));
    FND_TEST_TRUE(n.z == -2.0f);
}

void unittests_math_vector_float3_compound_assignment_operators()
{
    float3_t v{7.5f, -3.0f, 1.0f};

    // Each operator returns a reference to its left operand.
    FND_TEST_TRUE(&(v += float3_t{1.0f, 2.0f, 3.0f}) == &v);
    FND_TEST_TRUE(test_components(v, 8.5f, -1.0f, 4.0f));
    FND_TEST_TRUE(test_components(v += 2.0f, 10.5f, 1.0f, 6.0f));

    FND_TEST_TRUE(test_components(
        v -= float3_t{4.0f, 3.0f, 2.0f}, 6.5f, -2.0f, 4.0f));
    FND_TEST_TRUE(test_components(v -= 1.0f, 5.5f, -3.0f, 3.0f));

    FND_TEST_TRUE(test_components(
        v *= float3_t{2.0f, -2.0f, 0.5f}, 11.0f, 6.0f, 1.5f));
    FND_TEST_TRUE(test_components(v *= 0.5f, 5.5f, 3.0f, 0.75f));

    FND_TEST_TRUE(test_components(
        v /= float3_t{2.0f, 4.0f, 0.25f}, 2.75f, 0.75f, 3.0f));
    FND_TEST_TRUE(test_components(v /= 0.25f, 11.0f, 3.0f, 12.0f));

    FND_TEST_TRUE(test_components(
        v %= float3_t{4.0f, 2.0f, 5.0f}, 3.0f, 1.0f, 2.0f));
    FND_TEST_TRUE(test_components(v %= 2.0f, 1.0f, 1.0f, 0.0f));
}

void unittests_math_vector_float3_compound_assignment_matches_operators()
{
    // a op= b must give the same result as a op b.
    const float3_t a{7.5f, -3.0f, 1.25f};
    const float3_t b{2.0f, 4.0f, -0.5f};
    const float_t val{2.0f};
    float3_t c;

    c = a;
    c += b;
    FND_TEST_TRUE(all(c == (a + b)));
    c = a;
    c += val;
    FND_TEST_TRUE(all(c == (a + val)));

    c = a;
    c -= b;
    FND_TEST_TRUE(all(c == (a - b)));
    c = a;
    c -= val;
    FND_TEST_TRUE(all(c == (a - val)));

    c = a;
    c *= b;
    FND_TEST_TRUE(all(c == (a * b)));
    c = a;
    c *= val;
    FND_TEST_TRUE(all(c == (a * val)));

    c = a;
    c /= b;
    FND_TEST_TRUE(all(c == (a / b)));
    c = a;
    c /= val;
    FND_TEST_TRUE(all(c == (a / val)));

    c = a;
    c %= b;
    FND_TEST_TRUE(all(c == (a % b)));
    c = a;
    c %= val;
    FND_TEST_TRUE(all(c == (a % val)));
}

void unittests_math_vector_float3_equality_operators()
{
    const float3_t a{7.5f, -3.0f, 1.0f};
    FND_TEST_TRUE(all(
        (a == float3_t{7.5f, -3.0f, 1.0f}) == bool3_t{true, true, true}));
    FND_TEST_TRUE(all(
        (a == float3_t{7.5f, 5.0f, 1.0f}) == bool3_t{true, false, true}));
    FND_TEST_TRUE(all(
        (a == float3_t{2.0f, 5.0f, 0.0f}) == bool3_t{false, false, false}));
    FND_TEST_TRUE(all((a == 7.5f) == bool3_t{true, false, false}));
    FND_TEST_TRUE(all((-3.0f == a) == bool3_t{false, true, false}));

    FND_TEST_TRUE(all(
        (a != float3_t{7.5f, -3.0f, 1.0f}) == bool3_t{false, false, false}));
    FND_TEST_TRUE(all(
        (a != float3_t{7.5f, 5.0f, 1.0f}) == bool3_t{false, true, false}));
    FND_TEST_TRUE(all(
        (a != float3_t{2.0f, 5.0f, 0.0f}) == bool3_t{true, true, true}));
    FND_TEST_TRUE(all((a != 7.5f) == bool3_t{false, true, true}));
    FND_TEST_TRUE(all((-3.0f != a) == bool3_t{true, false, true}));

    // NaN compares unequal to everything, itself included; -0 equals +0.
    const float3_t n{kFloatNaN, -0.0f, 1.0f};
    FND_TEST_TRUE(all((n == float3_t{kFloatNaN, 0.0f, 1.0f})
        == bool3_t{false, true, true}));
    FND_TEST_TRUE(all((n != float3_t{kFloatNaN, 0.0f, 1.0f})
        == bool3_t{true, false, false}));
}

void unittests_math_vector_float3_relational_operators()
{
    const float3_t a{7.5f, -3.0f, 1.0f};
    const float3_t b{2.0f, 5.0f, 1.0f};
    const float3_t c{7.5f, 5.0f, 0.0f};

    FND_TEST_TRUE(all((a < b) == bool3_t{false, true, false}));
    FND_TEST_TRUE(all((a < c) == bool3_t{false, true, false}));
    FND_TEST_TRUE(all((a < 0.0f) == bool3_t{false, true, false}));
    FND_TEST_TRUE(all((0.0f < a) == bool3_t{true, false, true}));

    FND_TEST_TRUE(all((a <= b) == bool3_t{false, true, true}));
    FND_TEST_TRUE(all((a <= c) == bool3_t{true, true, false}));
    FND_TEST_TRUE(all((a <= -3.0f) == bool3_t{false, true, false}));
    FND_TEST_TRUE(all((7.5f <= a) == bool3_t{true, false, false}));

    FND_TEST_TRUE(all((a > b) == bool3_t{true, false, false}));
    FND_TEST_TRUE(all((a > c) == bool3_t{false, false, true}));
    FND_TEST_TRUE(all((a > 0.0f) == bool3_t{true, false, true}));
    FND_TEST_TRUE(all((0.0f > a) == bool3_t{false, true, false}));

    FND_TEST_TRUE(all((a >= b) == bool3_t{true, false, true}));
    FND_TEST_TRUE(all((a >= c) == bool3_t{true, false, true}));
    FND_TEST_TRUE(all((a >= 7.5f) == bool3_t{true, false, false}));
    FND_TEST_TRUE(all((7.5f >= a) == bool3_t{true, true, true}));

    // Every ordered comparison with NaN is false.
    const float3_t n{kFloatNaN, 1.0f, 3.0f};
    FND_TEST_TRUE(all((n < 2.0f) == bool3_t{false, true, false}));
    FND_TEST_TRUE(all((n <= 1.0f) == bool3_t{false, true, false}));
    FND_TEST_TRUE(all((n > 0.0f) == bool3_t{false, true, true}));
    FND_TEST_TRUE(all((n >= 1.0f) == bool3_t{false, true, true}));
}

void unittests_math_vector_float3_multiplication_operator()
{
    const float3_t a{7.5f, -3.0f, 0.5f};
    FND_TEST_TRUE(test_components(
        a * float3_t{2.0f, 5.0f, -4.0f}, 15.0f, -15.0f, -2.0f));
    FND_TEST_TRUE(test_components(a * 2.0f, 15.0f, -6.0f, 1.0f));
    FND_TEST_TRUE(test_components(2.0f * a, 15.0f, -6.0f, 1.0f));
    // Overflow gives infinity.
    FND_TEST_TRUE(
        test_components(float3_t{kFloatMaxValue, 2.0f, -kFloatMaxValue} * 2.0f,
            kFloatInfinity, 4.0f, -kFloatInfinity));
}

void unittests_math_vector_float3_addition_operator()
{
    const float3_t a{7.5f, -3.0f, 0.5f};
    FND_TEST_TRUE(test_components(
        a + float3_t{2.0f, 5.0f, 0.25f}, 9.5f, 2.0f, 0.75f));
    FND_TEST_TRUE(test_components(a + 1.0f, 8.5f, -2.0f, 1.5f));
    FND_TEST_TRUE(test_components(1.0f + a, 8.5f, -2.0f, 1.5f));
    // Overflow gives infinity.
    FND_TEST_TRUE(test_components(float3_t{kFloatMaxValue, 1.0f, kFloatMinValue}
            + float3_t{kFloatMaxValue, kFloatInfinity, kFloatMinValue},
        kFloatInfinity, kFloatInfinity, -kFloatInfinity));
}

void unittests_math_vector_float3_subtraction_operator()
{
    const float3_t a{7.5f, -3.0f, 0.5f};
    FND_TEST_TRUE(test_components(
        a - float3_t{2.0f, 5.0f, 0.25f}, 5.5f, -8.0f, 0.25f));
    FND_TEST_TRUE(test_components(a - 1.0f, 6.5f, -4.0f, -0.5f));
    FND_TEST_TRUE(test_components(1.0f - a, -6.5f, 4.0f, 0.5f));
    // Overflow gives infinity.
    FND_TEST_TRUE(test_components(float3_t{kFloatMinValue, 0.0f, kFloatMaxValue}
            - float3_t{kFloatMaxValue, 0.0f, kFloatMinValue},
        -kFloatInfinity, 0.0f, kFloatInfinity));
}

void unittests_math_vector_float3_modulo_operator()
{
    // fmod: the result has the sign of the left operand.
    const float3_t a{7.5f, -3.0f, 5.0f};
    FND_TEST_TRUE(test_components(
        a % float3_t{2.0f, 2.0f, 3.0f}, 1.5f, -1.0f, 2.0f));
    FND_TEST_TRUE(test_components(a % 2.0f, 1.5f, -1.0f, 1.0f));
    FND_TEST_TRUE(test_components(
        7.0f % float3_t{2.0f, 4.0f, -5.0f}, 1.0f, 3.0f, 2.0f));
    FND_TEST_TRUE(test_components(
        float3_t{-7.5f, 7.5f, -1.0f} % float3_t{2.0f, -2.0f, 0.75f}, -1.5f,
        1.5f, -0.25f));
}

void unittests_math_vector_float3_modulo_operator_matches_fmod()
{
    // a % b must give the same result as fmod(a, b), for every divisor that
    // operator% accepts (non-zero).
    const float3_t a[] = {
        float3_t{7.5f, -7.5f, 0.25f},
        float3_t{-0.0f, 0.0f, -0.0f},
        float3_t{1e30f, -1e-30f, 3.0f},
        float3_t{kFloatInfinity, 2.5f, -kFloatInfinity},
        float3_t{kFloatNaN, -3.0f, 1.0f},
    };
    const float3_t b[] = {
        float3_t{2.0f, 2.0f, -2.0f},
        float3_t{-4.0f, 0.75f, 0.5f},
        float3_t{kFloatMinSubnormal, -1e-3f, 1e30f},
        float3_t{kFloatInfinity, -kFloatInfinity, 1.0f},
        float3_t{kFloatNaN, 3.0f, -kFloatInfinity},
    };
    const float_t sa[] = {7.5f, -0.0f, 1e30f, kFloatInfinity, kFloatNaN};
    const float_t sb[] = {2.0f, -0.75f, 1e-3f, kFloatInfinity, kFloatNaN};

    for (const float3_t va : a) {
        for (const float3_t vb : b) {
            FND_TEST_TRUE(equal_or_both_nan(va % vb, fmod(va, vb)));
        }
        for (const float_t vs : sb) {
            FND_TEST_TRUE(equal_or_both_nan(va % vs, fmod(va, vs)));
        }
    }
    for (const float_t vs : sa) {
        for (const float3_t vb : b) {
            FND_TEST_TRUE(equal_or_both_nan(vs % vb, fmod(vs, vb)));
        }
    }
}

void unittests_math_vector_float3_division_operator()
{
    const float3_t a{7.5f, -3.0f, 1.0f};
    FND_TEST_TRUE(test_components(
        a / float3_t{2.0f, 4.0f, -0.5f}, 3.75f, -0.75f, -2.0f));
    FND_TEST_TRUE(test_components(a / 2.0f, 3.75f, -1.5f, 0.5f));
    FND_TEST_TRUE(test_components(
        3.0f / float3_t{2.0f, 4.0f, -8.0f}, 1.5f, 0.75f, -0.375f));
    FND_TEST_TRUE(test_components(
        float3_t{kFloatInfinity, 1.0f, -kFloatInfinity}
            / float3_t{2.0f, 4.0f, 2.0f},
        kFloatInfinity, 0.25f, -kFloatInfinity));
}

void unittests_math_vector_float3_abs()
{
    FND_TEST_TRUE(
        test_components(abs(float3_t{7.5f, -3.0f, -0.25f}), 7.5f, 3.0f, 0.25f));
    FND_TEST_TRUE(
        test_components(abs(float3_t{-0.0f, -kFloatInfinity, kFloatInfinity}),
            0.0f, kFloatInfinity, kFloatInfinity));
    FND_TEST_TRUE(
        test_components(abs(float3_t{kFloatMinValue, kFloatMaxValue, -1.0f}),
            kFloatMaxValue, kFloatMaxValue, 1.0f));

    const float3_t n = abs(float3_t{-1.0f, kFloatNaN, 2.0f});
    FND_TEST_TRUE(n.x == 1.0f);
    FND_TEST_TRUE(isnan(n.y));
    FND_TEST_TRUE(n.z == 2.0f);
}

// The float3_t math functions apply the float_t ones per component. Comparing
// against the float_t function catches wrong or swapped components exactly.

void unittests_math_vector_float3_inverse_trigonometry()
{
    const float3_t v{0.5f, -1.0f, 0.0f};
    FND_TEST_TRUE(
        test_components(acos(v), acos(0.5f), acos(-1.0f), acos(0.0f)));
    FND_TEST_TRUE(
        test_components(asin(v), asin(0.5f), asin(-1.0f), asin(0.0f)));
    FND_TEST_TRUE(test_components(
        atan(float3_t{1.0f, -2.0f, 0.5f}), atan(1.0f), atan(-2.0f),
        atan(0.5f)));
    FND_TEST_TRUE(test_components(
        atan2(float3_t{1.0f, -1.0f, 0.0f}, float3_t{-1.0f, 2.0f, -3.0f}),
        atan2(1.0f, -1.0f), atan2(-1.0f, 2.0f), atan2(0.0f, -3.0f)));
    FND_TEST_TRUE(approx_equal(acos(float3_t{-1.0f, 1.0f, 0.0f}).x, kFloatPi));
}

void unittests_math_vector_float3_approx_equal()
{
    const float3_t v{1.0f, -2.0f, 0.5f};
    FND_TEST_TRUE(all(approx_equal(v, v)));
    FND_TEST_TRUE(
        all(approx_equal(v, float3_t{1.000001f, -2.000001f, 0.500001f})));
    // Each component is compared on its own.
    FND_TEST_TRUE(all(approx_equal(v, float3_t{1.1f, -2.0f, 0.5f})
        == bool3_t{false, true, true}));
    FND_TEST_TRUE(all(approx_equal(v, float3_t{1.0f, -2.1f, 0.5f})
        == bool3_t{true, false, true}));
    FND_TEST_TRUE(all(approx_equal(v, float3_t{1.0f, -2.0f, 0.6f})
        == bool3_t{true, true, false}));
    // max_abs_diff; the boundary is inclusive.
    FND_TEST_TRUE(all(approx_equal(v, float3_t{1.5f, -2.5f, 1.0f}, 0.5f)));
    FND_TEST_TRUE(all(approx_equal(v, float3_t{1.5f, -2.25f, 0.75f}, 0.25f)
        == bool3_t{false, true, true}));
    FND_TEST_TRUE(all(approx_equal(v, float3_t{1.0f, -2.0f, 0.5f}, 0.0f)));
    // float_t on either side is compared with every component.
    FND_TEST_TRUE(all(approx_equal(v, 1.0f) == bool3_t{true, false, false}));
    FND_TEST_TRUE(all(approx_equal(1.0f, v) == bool3_t{true, false, false}));
    FND_TEST_TRUE(
        all(approx_equal(float3_t{-1.5f, -2.5f, -2.0f}, -2.0f, 0.5f)));
    FND_TEST_TRUE(
        all(approx_equal(-2.0f, float3_t{-1.5f, -2.5f, -2.0f}, 0.5f)));
    // inf equals inf and NaN equals nothing, as for the float_t approx_equal.
    const float3_t n{kFloatInfinity, kFloatNaN, -kFloatInfinity};
    FND_TEST_TRUE(all(approx_equal(n, n) == bool3_t{true, false, true}));
}

void unittests_math_vector_float3_ceil()
{
    FND_TEST_TRUE(test_components(
        ceil(float3_t{2.25f, -2.75f, 0.5f}), 3.0f, -2.0f, 1.0f));
    FND_TEST_TRUE(test_components(
        ceil(float3_t{-0.5f, 4.0f, -4.0f}), 0.0f, 4.0f, -4.0f));
    FND_TEST_TRUE(
        test_components(ceil(float3_t{-kFloatInfinity, kFloatInfinity, 1.0f}),
            -kFloatInfinity, kFloatInfinity, 1.0f));
    FND_TEST_TRUE(isnan(ceil(float3_t{kFloatNaN, 1.0f, 1.0f}).x));
}

void unittests_math_vector_float3_clamp()
{
    const float3_t lower{-10.0f, 0.0f, 1.0f};
    const float3_t upper{10.0f, 5.0f, 2.0f};
    // Each component is clamped to its own bounds.
    FND_TEST_TRUE(test_components(
        clamp(float3_t{3.0f, 3.0f, 1.5f}, lower, upper), 3.0f, 3.0f, 1.5f));
    FND_TEST_TRUE(test_components(
        clamp(float3_t{-20.0f, -1.0f, 0.0f}, lower, upper), -10.0f, 0.0f,
        1.0f));
    FND_TEST_TRUE(test_components(
        clamp(float3_t{20.0f, 6.0f, 3.0f}, lower, upper), 10.0f, 5.0f, 2.0f));
    FND_TEST_TRUE(test_components(
        clamp(float3_t{-10.0f, 5.0f, 1.0f}, lower, upper), -10.0f, 5.0f,
        1.0f));
    FND_TEST_TRUE(test_components(
        clamp(float3_t{-kFloatInfinity, kFloatInfinity, -kFloatInfinity},
            lower, upper),
        -10.0f, 5.0f, 1.0f));
    FND_TEST_TRUE(test_components(
        clamp(float3_t{9.0f}, float3_t{3.0f}, float3_t{3.0f}), 3.0f, 3.0f,
        3.0f));

    // float_t bounds apply to every component.
    FND_TEST_TRUE(test_components(
        clamp(float3_t{0.5f, 9.5f, -1.0f}, 0.0f, 1.0f), 0.5f, 1.0f, 0.0f));
    FND_TEST_TRUE(test_components(
        clamp(float3_t{-20.0f, 20.0f, 0.0f}, -10.0f, 10.0f), -10.0f, 10.0f,
        0.0f));
    FND_TEST_TRUE(test_components(
        clamp(float3_t{9.0f, -9.0f, 3.0f}, 3.0f, 3.0f), 3.0f, 3.0f, 3.0f));

    // float3_t lower bound, float_t upper bound.
    FND_TEST_TRUE(test_components(clamp(float3_t{-20.0f}, lower, 5.0f), -10.0f,
        0.0f, 1.0f));
    FND_TEST_TRUE(test_components(
        clamp(float3_t{20.0f, 3.0f, 6.0f}, lower, 5.0f), 5.0f, 3.0f, 5.0f));

    // float_t lower bound, float3_t upper bound.
    FND_TEST_TRUE(test_components(
        clamp(float3_t{-20.0f}, 0.0f, upper), 0.0f, 0.0f, 0.0f));
    FND_TEST_TRUE(test_components(
        clamp(float3_t{20.0f, 3.0f, 6.0f}, 0.0f, upper), 10.0f, 3.0f, 2.0f));
}

void unittests_math_vector_float3_cmax()
{
    FND_TEST_TRUE(cmax(float3_t{7.5f, -3.0f, 1.0f}) == 7.5f);
    FND_TEST_TRUE(cmax(float3_t{-3.0f, 7.5f, 1.0f}) == 7.5f);
    FND_TEST_TRUE(cmax(float3_t{-3.0f, 1.0f, 7.5f}) == 7.5f);
    FND_TEST_TRUE(cmax(float3_t{4.0f}) == 4.0f);
    FND_TEST_TRUE(cmax(float3_t{-kFloatInfinity, kFloatInfinity, 0.0f})
        == kFloatInfinity);
    // A NaN component is ignored, as for the float_t max.
    FND_TEST_TRUE(cmax(float3_t{kFloatNaN, 1.0f, 2.0f}) == 2.0f);
    FND_TEST_TRUE(cmax(float3_t{1.0f, kFloatNaN, 2.0f}) == 2.0f);
    FND_TEST_TRUE(cmax(float3_t{2.0f, 1.0f, kFloatNaN}) == 2.0f);
}

void unittests_math_vector_float3_cmin()
{
    FND_TEST_TRUE(cmin(float3_t{7.5f, -3.0f, 1.0f}) == -3.0f);
    FND_TEST_TRUE(cmin(float3_t{-3.0f, 7.5f, 1.0f}) == -3.0f);
    FND_TEST_TRUE(cmin(float3_t{1.0f, 7.5f, -3.0f}) == -3.0f);
    FND_TEST_TRUE(cmin(float3_t{4.0f}) == 4.0f);
    FND_TEST_TRUE(cmin(float3_t{kFloatInfinity, -kFloatInfinity, 0.0f})
        == -kFloatInfinity);
    // A NaN component is ignored, as for the float_t min.
    FND_TEST_TRUE(cmin(float3_t{kFloatNaN, 1.0f, 2.0f}) == 1.0f);
    FND_TEST_TRUE(cmin(float3_t{1.0f, kFloatNaN, 2.0f}) == 1.0f);
    FND_TEST_TRUE(cmin(float3_t{2.0f, 1.0f, kFloatNaN}) == 1.0f);
}

void unittests_math_vector_float3_cmul()
{
    FND_TEST_TRUE(cmul(float3_t{7.5f, -3.0f, 2.0f}) == -45.0f);
    FND_TEST_TRUE(cmul(float3_t{0.0f, kFloatMaxValue, kFloatMaxValue}) == 0.0f);
    FND_TEST_TRUE(cmul(float3_t{kFloatMaxValue, 2.0f, 1.0f}) == kFloatInfinity);
    FND_TEST_TRUE(isnan(cmul(float3_t{0.0f, kFloatInfinity, 1.0f})));
}

void unittests_math_vector_float3_trigonometry()
{
    const float3_t v{0.5f, -1.25f, 2.0f};
    FND_TEST_TRUE(test_components(cos(v), cos(0.5f), cos(-1.25f), cos(2.0f)));
    FND_TEST_TRUE(test_components(sin(v), sin(0.5f), sin(-1.25f), sin(2.0f)));
    FND_TEST_TRUE(test_components(tan(v), tan(0.5f), tan(-1.25f), tan(2.0f)));
    FND_TEST_TRUE(test_components(
        cos(float3_t{0.0f, kFloatPi, 0.0f}), 1.0f, -1.0f, 1.0f));
}

void unittests_math_vector_float3_cross()
{
    const float3_t x{1.0f, 0.0f, 0.0f};
    const float3_t y{0.0f, 1.0f, 0.0f};
    const float3_t z{0.0f, 0.0f, 1.0f};
    // Right-handed basis.
    FND_TEST_TRUE(test_components(cross(x, y), 0.0f, 0.0f, 1.0f));
    FND_TEST_TRUE(test_components(cross(y, z), 1.0f, 0.0f, 0.0f));
    FND_TEST_TRUE(test_components(cross(z, x), 0.0f, 1.0f, 0.0f));
    FND_TEST_TRUE(test_components(cross(y, x), 0.0f, 0.0f, -1.0f));

    const float3_t a{1.0f, 2.0f, 3.0f};
    const float3_t b{4.0f, 5.0f, 6.0f};
    FND_TEST_TRUE(test_components(cross(a, b), -3.0f, 6.0f, -3.0f));
    FND_TEST_TRUE(test_components(
        cross(float3_t{2.5f, -1.0f, 0.5f}, float3_t{-3.0f, 4.0f, 1.0f}), -3.0f,
        -4.0f, 7.0f));
    // cross(b, a) == -cross(a, b).
    FND_TEST_TRUE(all(cross(b, a) == -cross(a, b)));
    // The result is perpendicular to both arguments.
    FND_TEST_TRUE(dot(cross(a, b), a) == 0.0f);
    FND_TEST_TRUE(dot(cross(a, b), b) == 0.0f);
    // Parallel vectors give a zero vector.
    FND_TEST_TRUE(test_components(cross(a, a), 0.0f, 0.0f, 0.0f));
    FND_TEST_TRUE(test_components(cross(a, a * 2.0f), 0.0f, 0.0f, 0.0f));
}

void unittests_math_vector_float3_csum()
{
    FND_TEST_TRUE(csum(float3_t{7.5f, -3.0f, 0.5f}) == 5.0f);
    FND_TEST_TRUE(csum(float3_t{}) == 0.0f);
    FND_TEST_TRUE(
        csum(float3_t{kFloatMaxValue, kFloatMaxValue, 0.0f}) == kFloatInfinity);
    FND_TEST_TRUE(isnan(csum(float3_t{kFloatInfinity, -kFloatInfinity, 1.0f})));
}

void unittests_math_vector_float3_degrees_radians()
{
    FND_TEST_TRUE(test_components(
        degrees(float3_t{kFloatPi, -kFloatPi / 2, 0.0f}), 180.0f, -90.0f,
        0.0f));
    FND_TEST_TRUE(test_components(radians(float3_t{180.0f, -90.0f, 0.0f}),
        kFloatPi, -kFloatPi / 2, 0.0f));
    FND_TEST_TRUE(test_components(degrees(float3_t{1.0f, -2.0f, 0.5f}),
        degrees(1.0f), degrees(-2.0f), degrees(0.5f)));
    FND_TEST_TRUE(test_components(radians(float3_t{1.0f, -2.0f, 0.5f}),
        radians(1.0f), radians(-2.0f), radians(0.5f)));
}

void unittests_math_vector_float3_distance_sqr()
{
    const float3_t a{1.0f, 2.0f, 3.0f};
    const float3_t b{4.0f, 6.0f, 15.0f};
    FND_TEST_TRUE(distance_sqr(a, a) == 0.0f);
    FND_TEST_TRUE(distance_sqr(a, b) == 169.0f);
    FND_TEST_TRUE(distance_sqr(b, a) == 169.0f);
    FND_TEST_TRUE(
        distance_sqr(float3_t{-1.0f, 0.0f, 0.0f}, float3_t{1.0f, 0.0f, 0.0f})
        == 4.0f);
    FND_TEST_TRUE(distance_sqr(a, float3_t{kFloatInfinity, 2.0f, 3.0f})
        == kFloatInfinity);
    FND_TEST_TRUE(isnan(distance_sqr(float3_t{kFloatNaN, 0.0f, 0.0f}, a)));
}

void unittests_math_vector_float3_distance()
{
    const float3_t a{1.0f, 2.0f, 3.0f};
    const float3_t b{4.0f, 6.0f, 15.0f};
    FND_TEST_TRUE(distance(a, a) == 0.0f);
    FND_TEST_TRUE(distance(a, b) == 13.0f);
    FND_TEST_TRUE(distance(b, a) == 13.0f);
    FND_TEST_TRUE(
        distance(float3_t{0.0f, 0.0f, -1.5f}, float3_t{0.0f, 0.0f, 1.5f})
        == 3.0f);
    // distance(a, b) is the length of a - b.
    const float3_t c{-2.0f, 7.5f, 0.5f};
    FND_TEST_TRUE(distance(a, c) == length(a - c));
    FND_TEST_TRUE(
        distance(a, float3_t{kFloatInfinity, 2.0f, 3.0f}) == kFloatInfinity);
}

void unittests_math_vector_float3_distance_matches_length()
{
    // distance(a, b) must give the same result as length(a - b), and
    // distance_sqr(a, b) the same as length_sqr(a - b) and dot(a - b, a - b).
    struct test_value {
        float3_t vec;
        float_t max_abs_diff;
    };

    // max_abs_diff is about 10 ulps of the largest squared distance the vector
    // takes part in.
    const test_value values[] = {
        {float3_t{1.0f, 2.0f, 3.0f}, 1e-4f},
        {float3_t{-2.0f, 7.5f, -1.0f}, 1e-4f},
        {float3_t{0.1f, -0.3f, 0.2f}, 1e-4f},
        {float3_t{-3e-5f, 4e6f, 1.0f}, 1e7f},
        {float3_t{1e19f, -1e-19f, 5e18f}, 1e32f},
    };

    for (const test_value a : values) {
        for (const test_value b : values) {
            // The larger vector of the pair sets the scale of the result.
            const float_t max_abs_diff = max(a.max_abs_diff, b.max_abs_diff);
            const float3_t diff = a.vec - b.vec;
            FND_TEST_TRUE(approx_equal(
                distance_sqr(a.vec, b.vec), length_sqr(diff), max_abs_diff));
            FND_TEST_TRUE(approx_equal(
                distance_sqr(a.vec, b.vec), dot(diff, diff), max_abs_diff));
            FND_TEST_TRUE(approx_equal(
                distance(a.vec, b.vec), length(diff), max_abs_diff));
        }
    }
}

void unittests_math_vector_float3_dot()
{
    const float3_t a{2.5f, -1.0f, 0.5f};
    const float3_t b{-3.0f, 4.0f, 2.0f};
    FND_TEST_TRUE(dot(a, b) == -10.5f);
    FND_TEST_TRUE(dot(b, a) == -10.5f);
    FND_TEST_TRUE(
        dot(float3_t{1.0f, 2.0f, 3.0f}, float3_t{4.0f, 5.0f, 6.0f}) == 32.0f);
    // Perpendicular vectors.
    FND_TEST_TRUE(
        dot(float3_t{2.0f, 0.0f, 0.0f}, float3_t{0.0f, -5.0f, 3.0f}) == 0.0f);
    FND_TEST_TRUE(
        dot(float3_t{1.0f, 1.0f, 0.0f}, float3_t{-1.0f, 1.0f, 5.0f}) == 0.0f);
    // dot(v, v) is the squared length.
    FND_TEST_TRUE(dot(a, a) == 7.5f);
    FND_TEST_TRUE(dot(a, a) == length_sqr(a));
    // The true result 1e40 is out of range.
    FND_TEST_TRUE(
        dot(float3_t{1e20f, 0.0f, 0.0f}, float3_t{1e20f, 0.0f, 0.0f})
        == kFloatInfinity);
    FND_TEST_TRUE(
        isnan(dot(float3_t{kFloatNaN, 1.0f, 1.0f}, float3_t{1.0f})));
    // inf * 0 is NaN.
    FND_TEST_TRUE(isnan(dot(
        float3_t{kFloatInfinity, 0.0f, 0.0f}, float3_t{0.0f, 1.0f, 1.0f})));
}

void unittests_math_vector_float3_exp_log()
{
    FND_TEST_TRUE(test_components(
        exp(float3_t{0.0f, 1.0f, -1.0f}), exp(0.0f), exp(1.0f), exp(-1.0f)));
    FND_TEST_TRUE(test_components(exp2(float3_t{3.0f, -1.0f, 0.5f}),
        exp2(3.0f), exp2(-1.0f), exp2(0.5f)));
    FND_TEST_TRUE(test_components(
        log(float3_t{1.0f, 2.0f, 0.5f}), log(1.0f), log(2.0f), log(0.5f)));
    FND_TEST_TRUE(test_components(log2(float3_t{8.0f, 0.5f, 2.0f}),
        log2(8.0f), log2(0.5f), log2(2.0f)));
    FND_TEST_TRUE(test_components(log10(float3_t{1000.0f, 0.01f, 10.0f}),
        log10(1000.0f), log10(0.01f), log10(10.0f)));
    FND_TEST_TRUE(test_components(
        exp2(float3_t{3.0f, -1.0f, 0.0f}), 8.0f, 0.5f, 1.0f));
    FND_TEST_TRUE(test_components(
        log2(float3_t{8.0f, 0.5f, 1.0f}), 3.0f, -1.0f, 0.0f));
}

void unittests_math_vector_float3_floor()
{
    FND_TEST_TRUE(test_components(
        floor(float3_t{2.25f, -2.75f, 0.5f}), 2.0f, -3.0f, 0.0f));
    FND_TEST_TRUE(test_components(
        floor(float3_t{0.5f, -4.0f, -0.5f}), 0.0f, -4.0f, -1.0f));
    FND_TEST_TRUE(
        test_components(floor(float3_t{-kFloatInfinity, kFloatInfinity, 1.0f}),
            -kFloatInfinity, kFloatInfinity, 1.0f));
    FND_TEST_TRUE(isnan(floor(float3_t{1.0f, kFloatNaN, 1.0f}).y));
}

void unittests_math_vector_float3_fmod()
{
    // The result has the sign of the left operand.
    FND_TEST_TRUE(test_components(
        fmod(float3_t{7.5f, -7.5f, 7.5f}, float3_t{2.0f, 2.0f, -4.0f}), 1.5f,
        -1.5f, 3.5f));
    // float_t on either side is used with every component.
    FND_TEST_TRUE(test_components(
        fmod(float3_t{7.5f, -5.25f, 0.5f}, 2.0f), 1.5f, -1.25f, 0.5f));
    FND_TEST_TRUE(test_components(
        fmod(7.5f, float3_t{2.0f, 4.0f, -5.0f}), 1.5f, 3.5f, 2.5f));
    // A finite x with an infinite y returns x.
    FND_TEST_TRUE(test_components(
        fmod(float3_t{1.5f, -1.5f, 0.0f}, kFloatInfinity), 1.5f, -1.5f, 0.0f));
    // Unlike operator%, fmod does not assert on a zero divisor: the result is
    // NaN.
    const float3_t zero_divisor
        = fmod(float3_t{1.0f, 2.0f, 3.0f}, float3_t{0.0f, 1.0f, 2.0f});
    FND_TEST_TRUE(isnan(zero_divisor.x));
    FND_TEST_TRUE(zero_divisor.y == 0.0f);
    FND_TEST_TRUE(zero_divisor.z == 1.0f);
    FND_TEST_TRUE(isnan(fmod(kFloatInfinity, float3_t{2.0f}).y));
}

void unittests_math_vector_float3_fractional()
{
    FND_TEST_TRUE(test_components(
        fractional(float3_t{2.75f, 4.0f, 0.5f}), 0.75f, 0.0f, 0.5f));
    // Negative x gives the magnitude of its fractional part, in [0, 1).
    FND_TEST_TRUE(test_components(
        fractional(float3_t{-2.75f, -1e-10f, -0.25f}), 0.75f, 1e-10f, 0.25f));
    FND_TEST_TRUE(test_components(
        fractional(float3_t{-kFloatInfinity, kFloatInfinity, -kFloatInfinity}),
        0.0f, 0.0f, 0.0f));
    FND_TEST_TRUE(isnan(fractional(float3_t{kFloatNaN, 1.0f, 1.0f}).x));
}

void unittests_math_vector_float3_isfinite()
{
    FND_TEST_TRUE(all(
        isfinite(float3_t{0.0f, -2.5f, 1.0f}) == bool3_t{true, true, true}));
    FND_TEST_TRUE(all(isfinite(float3_t{kFloatMinValue, kFloatMaxValue, 0.0f})
        == bool3_t{true, true, true}));
    FND_TEST_TRUE(all(isfinite(float3_t{kFloatMinSubnormal, -0.0f, 1.0f})
        == bool3_t{true, true, true}));
    FND_TEST_TRUE(all(isfinite(float3_t{kFloatInfinity, 1.0f, 1.0f})
        == bool3_t{false, true, true}));
    FND_TEST_TRUE(all(isfinite(float3_t{1.0f, -kFloatInfinity, 1.0f})
        == bool3_t{true, false, true}));
    FND_TEST_TRUE(all(isfinite(float3_t{1.0f, 1.0f, kFloatNaN})
        == bool3_t{true, true, false}));
    FND_TEST_TRUE(
        all(isfinite(float3_t{kFloatNaN, kFloatInfinity, -kFloatInfinity})
            == bool3_t{false, false, false}));
}

void unittests_math_vector_float3_isinf()
{
    FND_TEST_TRUE(
        all(isinf(float3_t{kFloatInfinity, -kFloatInfinity, kFloatInfinity})
            == bool3_t{true, true, true}));
    FND_TEST_TRUE(all(isinf(float3_t{kFloatInfinity, 1.0f, 1.0f})
        == bool3_t{true, false, false}));
    FND_TEST_TRUE(all(isinf(float3_t{1.0f, -kFloatInfinity, 1.0f})
        == bool3_t{false, true, false}));
    FND_TEST_TRUE(all(isinf(float3_t{1.0f, 1.0f, kFloatInfinity})
        == bool3_t{false, false, true}));
    FND_TEST_TRUE(all(isinf(float3_t{kFloatMinValue, kFloatMaxValue, 0.0f})
        == bool3_t{false, false, false}));
    FND_TEST_TRUE(all(isinf(float3_t{0.0f, kFloatMinSubnormal, -0.0f})
        == bool3_t{false, false, false}));
    // NaN is not infinite.
    FND_TEST_TRUE(all(isinf(float3_t{kFloatNaN, kFloatInfinity, 1.0f})
        == bool3_t{false, true, false}));
}

void unittests_math_vector_float3_isnan()
{
    FND_TEST_TRUE(
        all(isnan(float3_t{kFloatNaN}) == bool3_t{true, true, true}));
    FND_TEST_TRUE(all(isnan(float3_t{kFloatNaN, 1.0f, 1.0f})
        == bool3_t{true, false, false}));
    FND_TEST_TRUE(all(isnan(float3_t{1.0f, -kFloatNaN, 1.0f})
        == bool3_t{false, true, false}));
    FND_TEST_TRUE(all(isnan(float3_t{1.0f, 1.0f, kFloatNaN})
        == bool3_t{false, false, true}));
    FND_TEST_TRUE(all(
        isnan(float3_t{0.0f, -2.5f, 1.0f}) == bool3_t{false, false, false}));
    FND_TEST_TRUE(
        all(isnan(float3_t{kFloatInfinity, -kFloatInfinity, kFloatMaxValue})
            == bool3_t{false, false, false}));
    FND_TEST_TRUE(
        all(isnan(float3_t{kFloatMinValue, kFloatMinSubnormal, 0.0f})
            == bool3_t{false, false, false}));
    // NaN produced by arithmetic, not only the constant.
    const float3_t inf{kFloatInfinity, 1.0f, -kFloatInfinity};
    FND_TEST_TRUE(all(isnan(inf - inf) == bool3_t{true, false, true}));
}

void unittests_math_vector_float3_length_sqr()
{
    FND_TEST_TRUE(length_sqr(float3_t{}) == 0.0f);
    FND_TEST_TRUE(length_sqr(float3_t{3.0f, -4.0f, 12.0f}) == 169.0f);
    FND_TEST_TRUE(length_sqr(float3_t{-0.5f, 0.0f, 0.0f}) == 0.25f);
    // The true result 1e40 is out of range.
    FND_TEST_TRUE(length_sqr(float3_t{1e20f, 0.0f, 0.0f}) == kFloatInfinity);
    FND_TEST_TRUE(
        length_sqr(float3_t{1.0f, -kFloatInfinity, 0.0f}) == kFloatInfinity);
    FND_TEST_TRUE(isnan(length_sqr(float3_t{kFloatNaN, 1.0f, 1.0f})));
}

void unittests_math_vector_float3_length()
{
    FND_TEST_TRUE(length(float3_t{}) == 0.0f);
    FND_TEST_TRUE(length(float3_t{3.0f, -4.0f, 12.0f}) == 13.0f);
    FND_TEST_TRUE(length(float3_t{0.0f, -2.5f, 0.0f}) == 2.5f);
    FND_TEST_TRUE(length(float3_t{1.0f}) == sqrt(3.0f));
    FND_TEST_TRUE(
        length(float3_t{kFloatInfinity, 1.0f, 1.0f}) == kFloatInfinity);
    FND_TEST_TRUE(
        length(float3_t{1.0f, 1.0f, -kFloatInfinity}) == kFloatInfinity);
}

void unittests_math_vector_float3_lerp()
{
    const float3_t a{0.0f, 10.0f, -4.0f};
    const float3_t b{10.0f, 20.0f, 4.0f};
    FND_TEST_TRUE(test_components(lerp(a, b, 0.0f), 0.0f, 10.0f, -4.0f));
    FND_TEST_TRUE(test_components(lerp(a, b, 1.0f), 10.0f, 20.0f, 4.0f));
    FND_TEST_TRUE(test_components(lerp(a, b, 0.25f), 2.5f, 12.5f, -2.0f));
    // t outside [0, 1] extrapolates.
    FND_TEST_TRUE(test_components(lerp(a, b, 2.0f), 20.0f, 30.0f, 12.0f));
    // A float3_t t gives each component its own t.
    FND_TEST_TRUE(test_components(
        lerp(a, b, float3_t{0.25f, 0.5f, 0.75f}), 2.5f, 15.0f, 2.0f));
    FND_TEST_TRUE(test_components(
        lerp(a, b, float3_t{-1.0f, 1.0f, 0.0f}), -10.0f, 20.0f, -4.0f));
}

void unittests_math_vector_float3_max()
{
    const float3_t a{7.5f, -3.0f, 0.5f};
    FND_TEST_TRUE(test_components(
        max(a, float3_t{2.0f, 4.0f, 0.5f}), 7.5f, 4.0f, 0.5f));
    FND_TEST_TRUE(test_components(
        max(float3_t{2.0f, 4.0f, 0.5f}, a), 7.5f, 4.0f, 0.5f));
    FND_TEST_TRUE(test_components(
        max(float3_t{4.0f}, float3_t{4.0f}), 4.0f, 4.0f, 4.0f));
    FND_TEST_TRUE(test_components(
        max(float3_t{kFloatInfinity, -kFloatInfinity, 1.0f},
            float3_t{1.0f, 1.0f, -kFloatInfinity}),
        kFloatInfinity, 1.0f, 1.0f));
    // float_t on either side is compared with every component.
    FND_TEST_TRUE(test_components(max(a, 0.0f), 7.5f, 0.0f, 0.5f));
    FND_TEST_TRUE(test_components(max(0.0f, a), 7.5f, 0.0f, 0.5f));
    FND_TEST_TRUE(test_components(max(a, 10.0f), 10.0f, 10.0f, 10.0f));
    FND_TEST_TRUE(test_components(max(-5.0f, a), 7.5f, -3.0f, 0.5f));
    // A NaN argument is ignored, as for the float_t max.
    FND_TEST_TRUE(test_components(
        max(float3_t{kFloatNaN, 1.0f, 3.0f},
            float3_t{2.0f, kFloatNaN, kFloatNaN}),
        2.0f, 1.0f, 3.0f));
}

void unittests_math_vector_float3_min()
{
    const float3_t a{7.5f, -3.0f, 0.5f};
    FND_TEST_TRUE(test_components(
        min(a, float3_t{2.0f, 4.0f, 0.5f}), 2.0f, -3.0f, 0.5f));
    FND_TEST_TRUE(test_components(
        min(float3_t{2.0f, 4.0f, 0.5f}, a), 2.0f, -3.0f, 0.5f));
    FND_TEST_TRUE(test_components(
        min(float3_t{4.0f}, float3_t{4.0f}), 4.0f, 4.0f, 4.0f));
    FND_TEST_TRUE(test_components(
        min(float3_t{kFloatInfinity, -kFloatInfinity, 1.0f},
            float3_t{1.0f, 1.0f, -kFloatInfinity}),
        1.0f, -kFloatInfinity, -kFloatInfinity));
    // float_t on either side is compared with every component.
    FND_TEST_TRUE(test_components(min(a, 0.0f), 0.0f, -3.0f, 0.0f));
    FND_TEST_TRUE(test_components(min(0.0f, a), 0.0f, -3.0f, 0.0f));
    FND_TEST_TRUE(test_components(min(a, -5.0f), -5.0f, -5.0f, -5.0f));
    FND_TEST_TRUE(test_components(min(10.0f, a), 7.5f, -3.0f, 0.5f));
    // A NaN argument is ignored, as for the float_t min.
    FND_TEST_TRUE(test_components(
        min(float3_t{kFloatNaN, 1.0f, 3.0f},
            float3_t{2.0f, kFloatNaN, kFloatNaN}),
        2.0f, 1.0f, 3.0f));
}

void unittests_math_vector_float3_modf()
{
    float3_t vi;

    // Both parts have the sign of the component.
    FND_TEST_TRUE(test_components(
        modf(float3_t{3.75f, -3.75f, 0.5f}, vi), 0.75f, -0.75f, 0.5f));
    FND_TEST_TRUE(test_components(vi, 3.0f, -3.0f, 0.0f));
    FND_TEST_TRUE(test_components(
        modf(float3_t{-2.0f, 2.0f, 0.0f}, vi), 0.0f, 0.0f, 0.0f));
    FND_TEST_TRUE(test_components(vi, -2.0f, 2.0f, 0.0f));
    FND_TEST_TRUE(
        test_components(modf(float3_t{0.5f, -0.5f, kFloatMinSubnormal}, vi),
            0.5f, -0.5f, kFloatMinSubnormal));
    FND_TEST_TRUE(test_components(vi, 0.0f, 0.0f, 0.0f));
    FND_TEST_TRUE(test_components(
        modf(float3_t{kFloatMaxValue, -1.25f, 1.5f}, vi), 0.0f, -0.25f, 0.5f));
    FND_TEST_TRUE(test_components(vi, kFloatMaxValue, -1.0f, 1.0f));
    FND_TEST_TRUE(test_components(
        modf(float3_t{kFloatInfinity, -kFloatInfinity, -2.5f}, vi), 0.0f,
        0.0f, -0.5f));
    FND_TEST_TRUE(
        test_components(vi, kFloatInfinity, -kFloatInfinity, -2.0f));
    // A NaN component gives NaN in both parts and does not affect the others.
    const float3_t frac = modf(float3_t{kFloatNaN, 7.5f, -0.25f}, vi);
    FND_TEST_TRUE(isnan(frac.x));
    FND_TEST_TRUE(isnan(vi.x));
    FND_TEST_TRUE(frac.y == 0.5f);
    FND_TEST_TRUE(vi.y == 7.0f);
    FND_TEST_TRUE(frac.z == -0.25f);
    FND_TEST_TRUE(vi.z == 0.0f);
    // The parts add up to the input.
    const float3_t v{-123.625f, 0.375f, 64.5f};
    const float3_t vf = modf(v, vi);
    FND_TEST_TRUE(all(vf + vi == v));
}

void unittests_math_vector_float3_normalize()
{
    FND_TEST_TRUE(test_components(
        normalize(float3_t{5.0f, 0.0f, 0.0f}), 1.0f, 0.0f, 0.0f));
    FND_TEST_TRUE(test_components(
        normalize(float3_t{0.0f, -0.5f, 0.0f}), 0.0f, -1.0f, 0.0f));
    FND_TEST_TRUE(test_components(
        normalize(float3_t{0.0f, 0.0f, 2.0f}), 0.0f, 0.0f, 1.0f));
    FND_TEST_TRUE(all(approx_equal(normalize(float3_t{2.0f, -1.0f, 2.0f}),
        float3_t{0.66666667f, -0.33333333f, 0.66666667f})));
    FND_TEST_TRUE(all(approx_equal(normalize(float3_t{3.0f, -4.0f, 12.0f}),
        float3_t{0.23076923f, -0.30769231f, 0.92307692f})));
    FND_TEST_TRUE(all(approx_equal(normalize(float3_t{-1.0f, 1.0f, 1.0f}),
        float3_t{-0.57735027f, 0.57735027f, 0.57735027f})));
    // The result has unit length and keeps the direction of v.
    const float3_t v{-2.5f, 7.0f, 1.0f};
    const float3_t n = normalize(v);
    FND_TEST_TRUE(approx_equal(length(n), 1.0f));
    FND_TEST_TRUE(all(approx_equal(n * length(v), v)));
    // Large and small vectors whose squared length is still a normal float.
    FND_TEST_TRUE(all(approx_equal(
        normalize(float3_t{1e19f, 0.0f, 0.0f}), float3_t{1.0f, 0.0f, 0.0f})));
    FND_TEST_TRUE(all(approx_equal(
        normalize(float3_t{0.0f, 0.0f, 1e-18f}), float3_t{0.0f, 0.0f, 1.0f})));
}

void unittests_math_vector_float3_normalize_safe()
{
    // A zero vector gives default_value.
    FND_TEST_TRUE(
        test_components(normalize_safe(float3_t{}), 0.0f, 0.0f, 0.0f));
    FND_TEST_TRUE(test_components(normalize_safe(float3_t{-0.0f, 0.0f, -0.0f},
                                      float3_t{1.0f, 0.0f, 0.0f}),
        1.0f, 0.0f, 0.0f));
    // So does a vector whose squared length does not exceed kFloatMinNormal.
    FND_TEST_TRUE(test_components(normalize_safe(float3_t{1e-20f, 0.0f, 0.0f},
                                      float3_t{0.0f, -1.0f, 0.0f}),
        0.0f, -1.0f, 0.0f));
    FND_TEST_TRUE(test_components(normalize_safe(float3_t{kFloatMinSubnormal},
                                      float3_t{0.0f, -1.0f, 0.0f}),
        0.0f, -1.0f, 0.0f));
    // Any other vector is normalized and default_value is ignored.
    const float3_t d{9.0f};
    FND_TEST_TRUE(test_components(
        normalize_safe(float3_t{5.0f, 0.0f, 0.0f}, d), 1.0f, 0.0f, 0.0f));
    FND_TEST_TRUE(all(approx_equal(
        normalize_safe(float3_t{2.0f, -1.0f, 2.0f}, d),
        float3_t{0.66666667f, -0.33333333f, 0.66666667f})));
    const float3_t v{-2.5f, 7.0f, 1.0f};
    FND_TEST_TRUE(all(normalize_safe(v, d) == normalize(v)));

    // Very large finite vectors are normalized too.
    FND_TEST_TRUE(
        all(approx_equal(normalize_safe(float3_t{1e20f, 1.0f, 1.0f}, d),
            float3_t{1.0f, 1e-20f, 1e-20f})));
    FND_TEST_TRUE(
        all(approx_equal(normalize_safe(float3_t{2e19f, -1e19f, 2e19f}, d),
            float3_t{0.66666667f, -0.33333333f, 0.66666667f})));
    FND_TEST_TRUE(all(
        approx_equal(normalize_safe(float3_t{0.0f, 0.0f, -kFloatMaxValue}, d),
            float3_t{0.0f, 0.0f, -1.0f})));
    FND_TEST_TRUE(all(approx_equal(
        normalize_safe(
            float3_t{kFloatMaxValue, -kFloatMaxValue, kFloatMaxValue}, d),
        float3_t{0.57735027f, -0.57735027f, 0.57735027f})));
    FND_TEST_TRUE(approx_equal(
        length(normalize_safe(float3_t{kFloatMaxValue}, d)), 1.0f));
    // A large vector gives the same result as normalize.
    const float3_t large{1e19f, -1e19f, 1e19f};
    FND_TEST_TRUE(all(normalize_safe(large, d) == normalize(large)));

    // Scaling a vector up by a large factor does not change the result.
    const float3_t dirs[] = {
        float3_t{3.0f, -4.0f, 12.0f},
        float3_t{-2.5f, 7.0f, 1.0f},
        float3_t{1.0f, 1.0f, 1.0f},
        float3_t{0.1f, -0.3f, 0.2f},
    };
    for (const float3_t dir : dirs) {
        const float3_t scaled = dir * 1e20f;
        const float3_t n = normalize_safe(scaled, d);
        FND_TEST_TRUE(all(approx_equal(n, normalize_safe(dir, d))));
        FND_TEST_TRUE(approx_equal(length(n), 1.0f));
    }
}

void unittests_math_vector_float3_pow()
{
    FND_TEST_TRUE(test_components(
        pow(float3_t{2.0f, 9.0f, 4.0f}, float3_t{10.0f, 0.5f, -1.0f}),
        pow(2.0f, 10.0f), pow(9.0f, 0.5f), pow(4.0f, -1.0f)));
    FND_TEST_TRUE(test_components(pow(float3_t{3.0f, -4.0f, 0.5f}, 2.0f),
        pow(3.0f, 2.0f), pow(-4.0f, 2.0f), pow(0.5f, 2.0f)));
    FND_TEST_TRUE(approx_equal(
        pow(float3_t{2.0f, 9.0f, 4.0f}, float3_t{10.0f, 0.5f, -1.0f}).y,
        3.0f));
}

void unittests_math_vector_float3_rcp_sqrt_rsqrt()
{
    FND_TEST_TRUE(test_components(
        rcp(float3_t{2.0f, -4.0f, 0.5f}), 0.5f, -0.25f, 2.0f));
    FND_TEST_TRUE(test_components(
        sqrt(float3_t{4.0f, 2.25f, 0.25f}), 2.0f, 1.5f, 0.5f));
    FND_TEST_TRUE(test_components(sqrt(float3_t{2.0f, 3.0f, 5.0f}),
        sqrt(2.0f), sqrt(3.0f), sqrt(5.0f)));
    FND_TEST_TRUE(test_components(
        rsqrt(float3_t{4.0f, 0.25f, 16.0f}), 0.5f, 2.0f, 0.25f));
    FND_TEST_TRUE(test_components(rsqrt(float3_t{2.0f, 3.0f, 5.0f}),
        rsqrt(2.0f), rsqrt(3.0f), rsqrt(5.0f)));
}

void unittests_math_vector_float3_saturate()
{
    FND_TEST_TRUE(test_components(
        saturate(float3_t{0.25f, 0.75f, 0.5f}), 0.25f, 0.75f, 0.5f));
    FND_TEST_TRUE(test_components(
        saturate(float3_t{-0.5f, 1.5f, 2.0f}), 0.0f, 1.0f, 1.0f));
    FND_TEST_TRUE(test_components(
        saturate(float3_t{0.0f, 1.0f, 0.5f}), 0.0f, 1.0f, 0.5f));
    FND_TEST_TRUE(test_components(
        saturate(float3_t{-kFloatInfinity, kFloatInfinity, -1.0f}), 0.0f, 1.0f,
        0.0f));
}

void unittests_math_vector_float3_sign()
{
    FND_TEST_TRUE(test_components(
        sign(float3_t{7.5f, -3.0f, 0.0f}), 1.0f, -1.0f, 0.0f));
    FND_TEST_TRUE(test_components(
        sign(float3_t{0.0f, -0.0f, 0.0f}), 0.0f, 0.0f, 0.0f));
    FND_TEST_TRUE(test_components(
        sign(float3_t{kFloatInfinity, -kFloatInfinity, 1.0f}), 1.0f, -1.0f,
        1.0f));
    FND_TEST_TRUE(test_components(
        sign(float3_t{kFloatMinSubnormal, -kFloatMinSubnormal, -1.0f}), 1.0f,
        -1.0f, -1.0f));
    // NaN has no sign: 0.
    FND_TEST_TRUE(test_components(
        sign(float3_t{kFloatNaN, 2.0f, -2.0f}), 0.0f, 1.0f, -1.0f));
}

void unittests_math_vector_float3_smoothstep()
{
    // Each component has its own edges.
    const float3_t edge0{0.0f, 2.0f, -1.0f};
    const float3_t edge1{1.0f, 4.0f, 1.0f};
    FND_TEST_TRUE(test_components(
        smoothstep(float3_t{0.25f, 3.0f, 0.0f}, edge0, edge1), 0.15625f, 0.5f,
        0.5f));
    FND_TEST_TRUE(test_components(
        smoothstep(float3_t{-1.0f, 5.0f, 2.0f}, edge0, edge1), 0.0f, 1.0f,
        1.0f));
    // float_t edges apply to every component.
    FND_TEST_TRUE(test_components(
        smoothstep(float3_t{0.25f, 0.75f, 0.5f}, 0.0f, 1.0f), 0.15625f,
        0.84375f, 0.5f));
    FND_TEST_TRUE(test_components(
        smoothstep(float3_t{-1.0f, 2.0f, 0.0f}, 0.0f, 1.0f), 0.0f, 1.0f, 0.0f));
}

void unittests_math_vector_float3_trunc()
{
    // Rounds toward zero: down for positive, up for negative.
    FND_TEST_TRUE(test_components(
        trunc(float3_t{2.75f, -2.75f, 0.5f}), 2.0f, -2.0f, 0.0f));
    FND_TEST_TRUE(test_components(
        trunc(float3_t{-0.5f, 4.0f, -4.0f}), 0.0f, 4.0f, -4.0f));
    FND_TEST_TRUE(
        test_components(trunc(float3_t{-kFloatInfinity, kFloatInfinity, 1.0f}),
            -kFloatInfinity, kFloatInfinity, 1.0f));
    FND_TEST_TRUE(isnan(trunc(float3_t{kFloatNaN, 1.0f, 1.0f}).x));
}

void unittests_math_vector_float3()
{
    unittests_math_vector_float3_type();
    unittests_math_vector_float3_constructors();
    unittests_math_vector_float3_subscript_operator();
    unittests_math_vector_float3_increment_operators();
    unittests_math_vector_float3_decrement_operators();
    unittests_math_vector_float3_unary_minus_operator();
    unittests_math_vector_float3_compound_assignment_operators();
    unittests_math_vector_float3_compound_assignment_matches_operators();
    unittests_math_vector_float3_equality_operators();
    unittests_math_vector_float3_relational_operators();
    unittests_math_vector_float3_multiplication_operator();
    unittests_math_vector_float3_addition_operator();
    unittests_math_vector_float3_subtraction_operator();
    unittests_math_vector_float3_modulo_operator();
    unittests_math_vector_float3_modulo_operator_matches_fmod();
    unittests_math_vector_float3_division_operator();
    unittests_math_vector_float3_abs();
    unittests_math_vector_float3_inverse_trigonometry();
    unittests_math_vector_float3_approx_equal();
    unittests_math_vector_float3_ceil();
    unittests_math_vector_float3_clamp();
    unittests_math_vector_float3_cmax();
    unittests_math_vector_float3_cmin();
    unittests_math_vector_float3_cmul();
    unittests_math_vector_float3_trigonometry();
    unittests_math_vector_float3_cross();
    unittests_math_vector_float3_csum();
    unittests_math_vector_float3_degrees_radians();
    unittests_math_vector_float3_distance_sqr();
    unittests_math_vector_float3_distance();
    unittests_math_vector_float3_distance_matches_length();
    unittests_math_vector_float3_dot();
    unittests_math_vector_float3_exp_log();
    unittests_math_vector_float3_floor();
    unittests_math_vector_float3_fmod();
    unittests_math_vector_float3_fractional();
    unittests_math_vector_float3_isfinite();
    unittests_math_vector_float3_isinf();
    unittests_math_vector_float3_isnan();
    unittests_math_vector_float3_length_sqr();
    unittests_math_vector_float3_length();
    unittests_math_vector_float3_lerp();
    unittests_math_vector_float3_max();
    unittests_math_vector_float3_min();
    unittests_math_vector_float3_modf();
    unittests_math_vector_float3_normalize();
    unittests_math_vector_float3_normalize_safe();
    unittests_math_vector_float3_pow();
    unittests_math_vector_float3_rcp_sqrt_rsqrt();
    unittests_math_vector_float3_saturate();
    unittests_math_vector_float3_sign();
    unittests_math_vector_float3_smoothstep();
    unittests_math_vector_float3_trunc();
}

} // namespace fnd::unittests
