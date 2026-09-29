module;
#include "foundation/unittests.h"


export module unittests.math:vector_float4;
import foundation.core;
import foundation.math;

namespace fnd::unittests {

export void unittests_math_vector_float4();

// All expected values below are exact in binary, so == is reliable.
constexpr bool_t test_components(const float4_t v, const float_t x,
    const float_t y, const float_t z, const float_t w)
{
    return v.x == x && v.y == y && v.z == z && v.w == w;
}

// Like all(a == b), but a NaN component equals a NaN component.
bool_t equal_or_both_nan(const float4_t a, const float4_t b)
{
    return all((a == b) || (isnan(a) && isnan(b)));
}

void unittests_math_vector_float4_type()
{
    static_assert(PodType<float4_t>);
    static_assert(sizeof(float4_t) == 4 * sizeof(float_t));
    // The ctor(float_t) is explicit.
    static_assert(!is_convertible<float_t, float4_t>());
}

void unittests_math_vector_float4_constants()
{
    FND_TEST_TRUE(test_components(float4_t::kZero, 0.0f, 0.0f, 0.0f, 0.0f));
    FND_TEST_TRUE(test_components(float4_t::kUnitX, 1.0f, 0.0f, 0.0f, 0.0f));
    FND_TEST_TRUE(test_components(float4_t::kUnitY, 0.0f, 1.0f, 0.0f, 0.0f));
    FND_TEST_TRUE(test_components(float4_t::kUnitZ, 0.0f, 0.0f, 1.0f, 0.0f));
    FND_TEST_TRUE(test_components(float4_t::kUnitW, 0.0f, 0.0f, 0.0f, 1.0f));
    FND_TEST_TRUE(all(float4_t::kZero == float4_t{}));
    FND_TEST_TRUE(all(float4_t::kUnitX + float4_t::kUnitY
        + float4_t::kUnitZ + float4_t::kUnitW == float4_t{1.0f}));
    // The constants are usable in constant expressions.
    static_assert(float4_t::kUnitW.w == 1.0f);
}

void unittests_math_vector_float4_constructors()
{
    FND_TEST_TRUE(test_components(float4_t{}, 0.0f, 0.0f, 0.0f, 0.0f));
    FND_TEST_TRUE(test_components(float4_t{2.5f}, 2.5f, 2.5f, 2.5f, 2.5f));
    FND_TEST_TRUE(test_components(float4_t{0.0f}, 0.0f, 0.0f, 0.0f, 0.0f));
    FND_TEST_TRUE(test_components(
        float4_t{3.0f, -4.5f, 6.25f, -8.0f}, 3.0f, -4.5f, 6.25f, -8.0f));
    FND_TEST_TRUE(
        test_components(float4_t{kFloatMinValue, kFloatMaxValue, 0.0f, -0.5f},
            kFloatMinValue, kFloatMaxValue, 0.0f, -0.5f));
}

void unittests_math_vector_float4_subscript_operator()
{
    const float4_t v{3.0f, -4.5f, 6.25f, -8.0f};
    FND_TEST_TRUE(v[0] == 3.0f);
    FND_TEST_TRUE(v[1] == -4.5f);
    FND_TEST_TRUE(v[2] == 6.25f);
    FND_TEST_TRUE(v[3] == -8.0f);

    // The non-const overload returns a reference into the vector itself.
    float4_t w;
    w[3] = 9.5f;
    FND_TEST_TRUE(test_components(w, 0.0f, 0.0f, 0.0f, 9.5f));

    w[2] = -1.0f;
    FND_TEST_TRUE(test_components(w, 0.0f, 0.0f, -1.0f, 9.5f));

    w[1] = 0.5f;
    FND_TEST_TRUE(test_components(w, 0.0f, 0.5f, -1.0f, 9.5f));

    w[0] = 2.0f;
    FND_TEST_TRUE(test_components(w, 2.0f, 0.5f, -1.0f, 9.5f));
}

void unittests_math_vector_float4_increment_operators()
{
    float4_t v{1.5f, -1.0f, 0.25f, -2.5f};
    FND_TEST_TRUE(test_components(++v, 2.5f, 0.0f, 1.25f, -1.5f));
    FND_TEST_TRUE(test_components(v, 2.5f, 0.0f, 1.25f, -1.5f));

    // Postfix returns the value before the increment.
    FND_TEST_TRUE(test_components(v++, 2.5f, 0.0f, 1.25f, -1.5f));
    FND_TEST_TRUE(test_components(v, 3.5f, 1.0f, 2.25f, -0.5f));
}

void unittests_math_vector_float4_decrement_operators()
{
    float4_t v{1.5f, -1.0f, 0.25f, -2.5f};
    FND_TEST_TRUE(test_components(--v, 0.5f, -2.0f, -0.75f, -3.5f));
    FND_TEST_TRUE(test_components(v, 0.5f, -2.0f, -0.75f, -3.5f));

    // Postfix returns the value before the decrement.
    FND_TEST_TRUE(test_components(v--, 0.5f, -2.0f, -0.75f, -3.5f));
    FND_TEST_TRUE(test_components(v, -0.5f, -3.0f, -1.75f, -4.5f));
}

void unittests_math_vector_float4_unary_minus_operator()
{
    FND_TEST_TRUE(test_components(
        -float4_t{7.5f, -3.0f, 0.5f, -0.25f}, -7.5f, 3.0f, -0.5f, 0.25f));
    FND_TEST_TRUE(test_components(-float4_t{0.0f}, 0.0f, 0.0f, 0.0f, 0.0f));
    FND_TEST_TRUE(test_components(
        -float4_t{
            kFloatInfinity, kFloatMaxValue, -kFloatInfinity, kFloatMinValue},
        -kFloatInfinity, kFloatMinValue, kFloatInfinity, kFloatMaxValue));

    const float4_t n = -float4_t{1.0f, kFloatNaN, 2.0f, -3.0f};
    FND_TEST_TRUE(n.x == -1.0f);
    FND_TEST_TRUE(isnan(n.y));
    FND_TEST_TRUE(n.z == -2.0f);
    FND_TEST_TRUE(n.w == 3.0f);
}

void unittests_math_vector_float4_compound_assignment_operators()
{
    float4_t v{7.5f, -3.0f, 1.0f, 2.0f};

    // Each operator returns a reference to its left operand.
    FND_TEST_TRUE(&(v += float4_t{1.0f, 2.0f, 3.0f, -1.0f}) == &v);
    FND_TEST_TRUE(test_components(v, 8.5f, -1.0f, 4.0f, 1.0f));
    FND_TEST_TRUE(test_components(v += 2.0f, 10.5f, 1.0f, 6.0f, 3.0f));

    FND_TEST_TRUE(test_components(
        v -= float4_t{4.0f, 3.0f, 2.0f, 1.0f}, 6.5f, -2.0f, 4.0f, 2.0f));
    FND_TEST_TRUE(test_components(v -= 1.0f, 5.5f, -3.0f, 3.0f, 1.0f));

    FND_TEST_TRUE(test_components(
        v *= float4_t{2.0f, -2.0f, 0.5f, 4.0f}, 11.0f, 6.0f, 1.5f, 4.0f));
    FND_TEST_TRUE(test_components(v *= 0.5f, 5.5f, 3.0f, 0.75f, 2.0f));

    FND_TEST_TRUE(test_components(
        v /= float4_t{2.0f, 4.0f, 0.25f, -0.5f}, 2.75f, 0.75f, 3.0f, -4.0f));
    FND_TEST_TRUE(test_components(v /= 0.25f, 11.0f, 3.0f, 12.0f, -16.0f));

    FND_TEST_TRUE(test_components(
        v %= float4_t{4.0f, 2.0f, 5.0f, 3.0f}, 3.0f, 1.0f, 2.0f, -1.0f));
    FND_TEST_TRUE(test_components(v %= 2.0f, 1.0f, 1.0f, 0.0f, -1.0f));
}

void unittests_math_vector_float4_compound_assignment_matches_operators()
{
    // a op= b must give the same result as a op b.
    const float4_t a{7.5f, -3.0f, 1.25f, -6.0f};
    const float4_t b{2.0f, 4.0f, -0.5f, 1.5f};
    const float_t val{2.0f};
    float4_t c;

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

void unittests_math_vector_float4_equality_operators()
{
    const float4_t a{7.5f, -3.0f, 1.0f, 0.5f};
    FND_TEST_TRUE(all((a == float4_t{7.5f, -3.0f, 1.0f, 0.5f})
        == bool4_t{true, true, true, true}));
    FND_TEST_TRUE(all((a == float4_t{7.5f, 5.0f, 1.0f, 0.0f})
        == bool4_t{true, false, true, false}));
    FND_TEST_TRUE(all((a == float4_t{2.0f, 5.0f, 0.0f, 1.0f})
        == bool4_t{false, false, false, false}));
    FND_TEST_TRUE(all((a == 7.5f) == bool4_t{true, false, false, false}));
    FND_TEST_TRUE(all((-3.0f == a) == bool4_t{false, true, false, false}));

    FND_TEST_TRUE(all((a != float4_t{7.5f, -3.0f, 1.0f, 0.5f})
        == bool4_t{false, false, false, false}));
    FND_TEST_TRUE(all((a != float4_t{7.5f, 5.0f, 1.0f, 0.0f})
        == bool4_t{false, true, false, true}));
    FND_TEST_TRUE(all((a != float4_t{2.0f, 5.0f, 0.0f, 1.0f})
        == bool4_t{true, true, true, true}));
    FND_TEST_TRUE(all((a != 7.5f) == bool4_t{false, true, true, true}));
    FND_TEST_TRUE(all((-3.0f != a) == bool4_t{true, false, true, true}));

    // NaN compares unequal to everything, itself included; -0 equals +0.
    const float4_t n{kFloatNaN, -0.0f, 1.0f, kFloatNaN};
    FND_TEST_TRUE(all((n == float4_t{kFloatNaN, 0.0f, 1.0f, 2.0f})
        == bool4_t{false, true, true, false}));
    FND_TEST_TRUE(all((n != float4_t{kFloatNaN, 0.0f, 1.0f, 2.0f})
        == bool4_t{true, false, false, true}));
}

void unittests_math_vector_float4_relational_operators()
{
    const float4_t a{7.5f, -3.0f, 1.0f, 0.5f};
    const float4_t b{2.0f, 5.0f, 1.0f, -1.0f};
    const float4_t c{7.5f, 5.0f, 0.0f, 0.5f};

    FND_TEST_TRUE(all((a < b) == bool4_t{false, true, false, false}));
    FND_TEST_TRUE(all((a < c) == bool4_t{false, true, false, false}));
    FND_TEST_TRUE(all((a < 0.0f) == bool4_t{false, true, false, false}));
    FND_TEST_TRUE(all((0.0f < a) == bool4_t{true, false, true, true}));

    FND_TEST_TRUE(all((a <= b) == bool4_t{false, true, true, false}));
    FND_TEST_TRUE(all((a <= c) == bool4_t{true, true, false, true}));
    FND_TEST_TRUE(all((a <= -3.0f) == bool4_t{false, true, false, false}));
    FND_TEST_TRUE(all((7.5f <= a) == bool4_t{true, false, false, false}));

    FND_TEST_TRUE(all((a > b) == bool4_t{true, false, false, true}));
    FND_TEST_TRUE(all((a > c) == bool4_t{false, false, true, false}));
    FND_TEST_TRUE(all((a > 0.0f) == bool4_t{true, false, true, true}));
    FND_TEST_TRUE(all((0.0f > a) == bool4_t{false, true, false, false}));

    FND_TEST_TRUE(all((a >= b) == bool4_t{true, false, true, true}));
    FND_TEST_TRUE(all((a >= c) == bool4_t{true, false, true, true}));
    FND_TEST_TRUE(all((a >= 7.5f) == bool4_t{true, false, false, false}));
    FND_TEST_TRUE(all((7.5f >= a) == bool4_t{true, true, true, true}));

    // Every ordered comparison with NaN is false.
    const float4_t n{kFloatNaN, 1.0f, 3.0f, -1.0f};
    FND_TEST_TRUE(all((n < 2.0f) == bool4_t{false, true, false, true}));
    FND_TEST_TRUE(all((n <= 1.0f) == bool4_t{false, true, false, true}));
    FND_TEST_TRUE(all((n > 0.0f) == bool4_t{false, true, true, false}));
    FND_TEST_TRUE(all((n >= 1.0f) == bool4_t{false, true, true, false}));
}

void unittests_math_vector_float4_multiplication_operator()
{
    const float4_t a{7.5f, -3.0f, 0.5f, -0.25f};
    FND_TEST_TRUE(test_components(
        a * float4_t{2.0f, 5.0f, -4.0f, 8.0f}, 15.0f, -15.0f, -2.0f, -2.0f));
    FND_TEST_TRUE(test_components(a * 2.0f, 15.0f, -6.0f, 1.0f, -0.5f));
    FND_TEST_TRUE(test_components(2.0f * a, 15.0f, -6.0f, 1.0f, -0.5f));
    // Overflow gives infinity.
    FND_TEST_TRUE(test_components(
        float4_t{kFloatMaxValue, 2.0f, -kFloatMaxValue, 0.0f} * 2.0f,
        kFloatInfinity, 4.0f, -kFloatInfinity, 0.0f));
}

void unittests_math_vector_float4_addition_operator()
{
    const float4_t a{7.5f, -3.0f, 0.5f, -0.25f};
    FND_TEST_TRUE(test_components(
        a + float4_t{2.0f, 5.0f, 0.25f, 1.0f}, 9.5f, 2.0f, 0.75f, 0.75f));
    FND_TEST_TRUE(test_components(a + 1.0f, 8.5f, -2.0f, 1.5f, 0.75f));
    FND_TEST_TRUE(test_components(1.0f + a, 8.5f, -2.0f, 1.5f, 0.75f));
    // Overflow gives infinity.
    FND_TEST_TRUE(test_components(
        float4_t{kFloatMaxValue, 1.0f, kFloatMinValue, 0.0f}
            + float4_t{kFloatMaxValue, kFloatInfinity, kFloatMinValue, 0.0f},
        kFloatInfinity, kFloatInfinity, -kFloatInfinity, 0.0f));
}

void unittests_math_vector_float4_subtraction_operator()
{
    const float4_t a{7.5f, -3.0f, 0.5f, -0.25f};
    FND_TEST_TRUE(test_components(
        a - float4_t{2.0f, 5.0f, 0.25f, 1.0f}, 5.5f, -8.0f, 0.25f, -1.25f));
    FND_TEST_TRUE(test_components(a - 1.0f, 6.5f, -4.0f, -0.5f, -1.25f));
    FND_TEST_TRUE(test_components(1.0f - a, -6.5f, 4.0f, 0.5f, 1.25f));
    // Overflow gives infinity.
    FND_TEST_TRUE(test_components(
        float4_t{kFloatMinValue, 0.0f, kFloatMaxValue, 1.0f}
            - float4_t{kFloatMaxValue, 0.0f, kFloatMinValue, 1.0f},
        -kFloatInfinity, 0.0f, kFloatInfinity, 0.0f));
}

void unittests_math_vector_float4_modulo_operator()
{
    // fmod: the result has the sign of the left operand.
    const float4_t a{7.5f, -3.0f, 5.0f, -7.0f};
    FND_TEST_TRUE(test_components(
        a % float4_t{2.0f, 2.0f, 3.0f, 4.0f}, 1.5f, -1.0f, 2.0f, -3.0f));
    FND_TEST_TRUE(test_components(a % 2.0f, 1.5f, -1.0f, 1.0f, -1.0f));
    FND_TEST_TRUE(test_components(
        7.0f % float4_t{2.0f, 4.0f, -5.0f, 0.5f}, 1.0f, 3.0f, 2.0f, 0.0f));
    FND_TEST_TRUE(test_components(
        float4_t{-7.5f, 7.5f, -1.0f, 1.0f}
            % float4_t{2.0f, -2.0f, 0.75f, 0.75f},
        -1.5f, 1.5f, -0.25f, 0.25f));
}

void unittests_math_vector_float4_modulo_operator_matches_fmod()
{
    // a % b must give the same result as fmod(a, b), for every divisor that
    // operator% accepts (non-zero).
    const float4_t a[] = {
        float4_t{7.5f, -7.5f, 0.25f, -0.25f},
        float4_t{-0.0f, 0.0f, -0.0f, 0.0f},
        float4_t{1e30f, -1e-30f, 3.0f, -1e30f},
        float4_t{kFloatInfinity, 2.5f, -kFloatInfinity, 0.0f},
        float4_t{kFloatNaN, -3.0f, 1.0f, kFloatNaN},
    };
    const float4_t b[] = {
        float4_t{2.0f, 2.0f, -2.0f, -2.0f},
        float4_t{-4.0f, 0.75f, 0.5f, 3.0f},
        float4_t{kFloatMinSubnormal, -1e-3f, 1e30f, -kFloatMinSubnormal},
        float4_t{kFloatInfinity, -kFloatInfinity, 1.0f, kFloatInfinity},
        float4_t{kFloatNaN, 3.0f, -kFloatInfinity, 1.0f},
    };
    const float_t sa[] = {7.5f, -0.0f, 1e30f, kFloatInfinity, kFloatNaN};
    const float_t sb[] = {2.0f, -0.75f, 1e-3f, kFloatInfinity, kFloatNaN};

    for (const float4_t va : a) {
        for (const float4_t vb : b) {
            FND_TEST_TRUE(equal_or_both_nan(va % vb, fmod(va, vb)));
        }
        for (const float_t vs : sb) {
            FND_TEST_TRUE(equal_or_both_nan(va % vs, fmod(va, vs)));
        }
    }
    for (const float_t vs : sa) {
        for (const float4_t vb : b) {
            FND_TEST_TRUE(equal_or_both_nan(vs % vb, fmod(vs, vb)));
        }
    }
}

void unittests_math_vector_float4_division_operator()
{
    const float4_t a{7.5f, -3.0f, 1.0f, -2.0f};
    FND_TEST_TRUE(test_components(
        a / float4_t{2.0f, 4.0f, -0.5f, 8.0f}, 3.75f, -0.75f, -2.0f, -0.25f));
    FND_TEST_TRUE(test_components(a / 2.0f, 3.75f, -1.5f, 0.5f, -1.0f));
    FND_TEST_TRUE(test_components(
        3.0f / float4_t{2.0f, 4.0f, -8.0f, 0.5f}, 1.5f, 0.75f, -0.375f, 6.0f));
    FND_TEST_TRUE(test_components(
        float4_t{kFloatInfinity, 1.0f, -kFloatInfinity, 0.0f}
            / float4_t{2.0f, 4.0f, 2.0f, 1.0f},
        kFloatInfinity, 0.25f, -kFloatInfinity, 0.0f));
}

void unittests_math_vector_float4_abs()
{
    FND_TEST_TRUE(test_components(
        abs(float4_t{7.5f, -3.0f, -0.25f, 0.0f}), 7.5f, 3.0f, 0.25f, 0.0f));
    FND_TEST_TRUE(test_components(
        abs(float4_t{-0.0f, -kFloatInfinity, kFloatInfinity, -1.5f}), 0.0f,
        kFloatInfinity, kFloatInfinity, 1.5f));
    FND_TEST_TRUE(test_components(
        abs(float4_t{kFloatMinValue, kFloatMaxValue, -1.0f, 1.0f}),
        kFloatMaxValue, kFloatMaxValue, 1.0f, 1.0f));

    const float4_t n = abs(float4_t{-1.0f, kFloatNaN, 2.0f, -0.5f});
    FND_TEST_TRUE(n.x == 1.0f);
    FND_TEST_TRUE(isnan(n.y));
    FND_TEST_TRUE(n.z == 2.0f);
    FND_TEST_TRUE(n.w == 0.5f);
}

// The float4_t math functions apply the float_t ones per component. Comparing
// against the float_t function catches wrong or swapped components exactly.

void unittests_math_vector_float4_inverse_trigonometry()
{
    const float4_t v{0.5f, -1.0f, 0.0f, 1.0f};
    FND_TEST_TRUE(test_components(
        acos(v), acos(0.5f), acos(-1.0f), acos(0.0f), acos(1.0f)));
    FND_TEST_TRUE(test_components(
        asin(v), asin(0.5f), asin(-1.0f), asin(0.0f), asin(1.0f)));
    FND_TEST_TRUE(test_components(atan(float4_t{1.0f, -2.0f, 0.5f, 0.0f}),
        atan(1.0f), atan(-2.0f), atan(0.5f), atan(0.0f)));
    FND_TEST_TRUE(test_components(
        atan2(float4_t{1.0f, -1.0f, 0.0f, 2.0f},
            float4_t{-1.0f, 2.0f, -3.0f, 0.0f}),
        atan2(1.0f, -1.0f), atan2(-1.0f, 2.0f), atan2(0.0f, -3.0f),
        atan2(2.0f, 0.0f)));
    FND_TEST_TRUE(
        approx_equal(acos(float4_t{-1.0f, 1.0f, 0.0f, 0.0f}).x, kFloatPi));
}

void unittests_math_vector_float4_approx_equal()
{
    const float4_t v{1.0f, -2.0f, 0.5f, 4.0f};
    FND_TEST_TRUE(all(approx_equal(v, v)));
    FND_TEST_TRUE(all(approx_equal(
        v, float4_t{1.000001f, -2.000001f, 0.500001f, 4.000001f})));
    // Each component is compared on its own.
    FND_TEST_TRUE(all(approx_equal(v, float4_t{1.1f, -2.0f, 0.5f, 4.0f})
        == bool4_t{false, true, true, true}));
    FND_TEST_TRUE(all(approx_equal(v, float4_t{1.0f, -2.1f, 0.5f, 4.0f})
        == bool4_t{true, false, true, true}));
    FND_TEST_TRUE(all(approx_equal(v, float4_t{1.0f, -2.0f, 0.6f, 4.0f})
        == bool4_t{true, true, false, true}));
    FND_TEST_TRUE(all(approx_equal(v, float4_t{1.0f, -2.0f, 0.5f, 4.1f})
        == bool4_t{true, true, true, false}));
    // max_abs_diff; the boundary is inclusive.
    FND_TEST_TRUE(
        all(approx_equal(v, float4_t{1.5f, -2.5f, 1.0f, 4.5f}, 0.5f)));
    FND_TEST_TRUE(
        all(approx_equal(v, float4_t{1.5f, -2.25f, 0.75f, 4.25f}, 0.25f)
            == bool4_t{false, true, true, true}));
    FND_TEST_TRUE(all(approx_equal(v, v, 0.0f)));
    // float_t on either side is compared with every component.
    FND_TEST_TRUE(
        all(approx_equal(v, 1.0f) == bool4_t{true, false, false, false}));
    FND_TEST_TRUE(
        all(approx_equal(1.0f, v) == bool4_t{true, false, false, false}));
    FND_TEST_TRUE(
        all(approx_equal(float4_t{-1.5f, -2.5f, -2.0f, -2.0f}, -2.0f, 0.5f)));
    FND_TEST_TRUE(
        all(approx_equal(-2.0f, float4_t{-1.5f, -2.5f, -2.0f, -2.0f}, 0.5f)));
    // inf equals inf and NaN equals nothing, as for the float_t approx_equal.
    const float4_t n{kFloatInfinity, kFloatNaN, -kFloatInfinity, 1.0f};
    FND_TEST_TRUE(
        all(approx_equal(n, n) == bool4_t{true, false, true, true}));
}

void unittests_math_vector_float4_ceil()
{
    FND_TEST_TRUE(test_components(
        ceil(float4_t{2.25f, -2.75f, 0.5f, -0.25f}), 3.0f, -2.0f, 1.0f, 0.0f));
    FND_TEST_TRUE(test_components(
        ceil(float4_t{-0.5f, 4.0f, -4.0f, 1.5f}), 0.0f, 4.0f, -4.0f, 2.0f));
    FND_TEST_TRUE(test_components(
        ceil(float4_t{-kFloatInfinity, kFloatInfinity, 1.0f, -1.0f}),
        -kFloatInfinity, kFloatInfinity, 1.0f, -1.0f));
    FND_TEST_TRUE(isnan(ceil(float4_t{kFloatNaN, 1.0f, 1.0f, 1.0f}).x));
}

void unittests_math_vector_float4_clamp()
{
    const float4_t lower{-10.0f, 0.0f, 1.0f, -1.0f};
    const float4_t upper{10.0f, 5.0f, 2.0f, 1.0f};
    // Each component is clamped to its own bounds.
    FND_TEST_TRUE(
        test_components(clamp(float4_t{3.0f, 3.0f, 1.5f, 0.0f}, lower, upper),
            3.0f, 3.0f, 1.5f, 0.0f));
    FND_TEST_TRUE(test_components(
        clamp(float4_t{-20.0f, -1.0f, 0.0f, -5.0f}, lower, upper), -10.0f,
        0.0f, 1.0f, -1.0f));
    FND_TEST_TRUE(
        test_components(clamp(float4_t{20.0f, 6.0f, 3.0f, 5.0f}, lower, upper),
            10.0f, 5.0f, 2.0f, 1.0f));
    FND_TEST_TRUE(test_components(
        clamp(float4_t{-10.0f, 5.0f, 1.0f, 1.0f}, lower, upper), -10.0f, 5.0f,
        1.0f, 1.0f));
    FND_TEST_TRUE(test_components(
        clamp(float4_t{-kFloatInfinity, kFloatInfinity, -kFloatInfinity,
                  kFloatInfinity},
            lower, upper),
        -10.0f, 5.0f, 1.0f, 1.0f));
    FND_TEST_TRUE(test_components(
        clamp(float4_t{9.0f}, float4_t{3.0f}, float4_t{3.0f}), 3.0f, 3.0f,
        3.0f, 3.0f));

    // float_t bounds apply to every component.
    FND_TEST_TRUE(
        test_components(clamp(float4_t{0.5f, 9.5f, -1.0f, 1.0f}, 0.0f, 1.0f),
            0.5f, 1.0f, 0.0f, 1.0f));
    FND_TEST_TRUE(test_components(
        clamp(float4_t{-20.0f, 20.0f, 0.0f, -10.0f}, -10.0f, 10.0f), -10.0f,
        10.0f, 0.0f, -10.0f));
    FND_TEST_TRUE(
        test_components(clamp(float4_t{9.0f, -9.0f, 3.0f, 0.0f}, 3.0f, 3.0f),
            3.0f, 3.0f, 3.0f, 3.0f));

    // float4_t lower bound, float_t upper bound.
    FND_TEST_TRUE(test_components(
        clamp(float4_t{-20.0f}, lower, 5.0f), -10.0f, 0.0f, 1.0f, -1.0f));
    FND_TEST_TRUE(
        test_components(clamp(float4_t{20.0f, 3.0f, 6.0f, 0.0f}, lower, 5.0f),
            5.0f, 3.0f, 5.0f, 0.0f));

    // float_t lower bound, float4_t upper bound.
    FND_TEST_TRUE(test_components(
        clamp(float4_t{-20.0f}, 0.0f, upper), 0.0f, 0.0f, 0.0f, 0.0f));
    FND_TEST_TRUE(
        test_components(clamp(float4_t{20.0f, 3.0f, 6.0f, 0.5f}, 0.0f, upper),
            10.0f, 3.0f, 2.0f, 0.5f));
}

void unittests_math_vector_float4_cmax()
{
    FND_TEST_TRUE(cmax(float4_t{7.5f, -3.0f, 1.0f, 0.0f}) == 7.5f);
    FND_TEST_TRUE(cmax(float4_t{-3.0f, 7.5f, 1.0f, 0.0f}) == 7.5f);
    FND_TEST_TRUE(cmax(float4_t{-3.0f, 1.0f, 7.5f, 0.0f}) == 7.5f);
    FND_TEST_TRUE(cmax(float4_t{-3.0f, 1.0f, 0.0f, 7.5f}) == 7.5f);
    FND_TEST_TRUE(cmax(float4_t{4.0f}) == 4.0f);
    FND_TEST_TRUE(cmax(float4_t{-kFloatInfinity, kFloatInfinity, 0.0f, 1.0f})
        == kFloatInfinity);
    // A NaN component is ignored, as for the float_t max.
    FND_TEST_TRUE(cmax(float4_t{kFloatNaN, 1.0f, 2.0f, 0.0f}) == 2.0f);
    FND_TEST_TRUE(cmax(float4_t{1.0f, kFloatNaN, 2.0f, 0.0f}) == 2.0f);
    FND_TEST_TRUE(cmax(float4_t{2.0f, 1.0f, kFloatNaN, 0.0f}) == 2.0f);
    FND_TEST_TRUE(cmax(float4_t{2.0f, 1.0f, 0.0f, kFloatNaN}) == 2.0f);
}

void unittests_math_vector_float4_cmin()
{
    FND_TEST_TRUE(cmin(float4_t{7.5f, -3.0f, 1.0f, 0.0f}) == -3.0f);
    FND_TEST_TRUE(cmin(float4_t{-3.0f, 7.5f, 1.0f, 0.0f}) == -3.0f);
    FND_TEST_TRUE(cmin(float4_t{1.0f, 7.5f, -3.0f, 0.0f}) == -3.0f);
    FND_TEST_TRUE(cmin(float4_t{1.0f, 7.5f, 0.0f, -3.0f}) == -3.0f);
    FND_TEST_TRUE(cmin(float4_t{4.0f}) == 4.0f);
    FND_TEST_TRUE(cmin(float4_t{kFloatInfinity, -kFloatInfinity, 0.0f, 1.0f})
        == -kFloatInfinity);
    // A NaN component is ignored, as for the float_t min.
    FND_TEST_TRUE(cmin(float4_t{kFloatNaN, 1.0f, 2.0f, 3.0f}) == 1.0f);
    FND_TEST_TRUE(cmin(float4_t{1.0f, kFloatNaN, 2.0f, 3.0f}) == 1.0f);
    FND_TEST_TRUE(cmin(float4_t{2.0f, 1.0f, kFloatNaN, 3.0f}) == 1.0f);
    FND_TEST_TRUE(cmin(float4_t{2.0f, 3.0f, 1.0f, kFloatNaN}) == 1.0f);
}

void unittests_math_vector_float4_cmul()
{
    FND_TEST_TRUE(cmul(float4_t{7.5f, -3.0f, 2.0f, -0.5f}) == 22.5f);
    FND_TEST_TRUE(cmul(float4_t{0.0f, kFloatMaxValue, kFloatMaxValue,
                      kFloatMaxValue})
        == 0.0f);
    FND_TEST_TRUE(
        cmul(float4_t{kFloatMaxValue, 2.0f, 1.0f, 1.0f}) == kFloatInfinity);
    FND_TEST_TRUE(isnan(cmul(float4_t{0.0f, kFloatInfinity, 1.0f, 1.0f})));
}

void unittests_math_vector_float4_trigonometry()
{
    const float4_t v{0.5f, -1.25f, 2.0f, -3.0f};
    FND_TEST_TRUE(test_components(
        cos(v), cos(0.5f), cos(-1.25f), cos(2.0f), cos(-3.0f)));
    FND_TEST_TRUE(test_components(
        sin(v), sin(0.5f), sin(-1.25f), sin(2.0f), sin(-3.0f)));
    FND_TEST_TRUE(test_components(
        tan(v), tan(0.5f), tan(-1.25f), tan(2.0f), tan(-3.0f)));
    FND_TEST_TRUE(test_components(cos(float4_t{0.0f, kFloatPi, 0.0f, kFloatPi}),
        1.0f, -1.0f, 1.0f, -1.0f));
}

void unittests_math_vector_float4_csum()
{
    FND_TEST_TRUE(csum(float4_t{7.5f, -3.0f, 0.5f, -1.0f}) == 4.0f);
    FND_TEST_TRUE(csum(float4_t{0.0f}) == 0.0f);
    FND_TEST_TRUE(csum(float4_t{kFloatMaxValue, kFloatMaxValue, 0.0f, 0.0f})
        == kFloatInfinity);
    FND_TEST_TRUE(
        isnan(csum(float4_t{kFloatInfinity, -kFloatInfinity, 1.0f, 1.0f})));
}

void unittests_math_vector_float4_degrees_radians()
{
    FND_TEST_TRUE(test_components(
        degrees(float4_t{kFloatPi, -kFloatPi / 2, 0.0f, kFloatPi}), 180.0f,
        -90.0f, 0.0f, 180.0f));
    FND_TEST_TRUE(
        test_components(radians(float4_t{180.0f, -90.0f, 0.0f, 180.0f}),
            kFloatPi, -kFloatPi / 2, 0.0f, kFloatPi));
    FND_TEST_TRUE(test_components(degrees(float4_t{1.0f, -2.0f, 0.5f, 4.0f}),
        degrees(1.0f), degrees(-2.0f), degrees(0.5f), degrees(4.0f)));
    FND_TEST_TRUE(test_components(radians(float4_t{1.0f, -2.0f, 0.5f, 4.0f}),
        radians(1.0f), radians(-2.0f), radians(0.5f), radians(4.0f)));
}

void unittests_math_vector_float4_distance_sqr()
{
    const float4_t a{1.0f, 2.0f, 3.0f, 4.0f};
    const float4_t b{4.0f, 6.0f, 15.0f, 4.0f};
    FND_TEST_TRUE(distance_sqr(a, a) == 0.0f);
    FND_TEST_TRUE(distance_sqr(a, b) == 169.0f);
    FND_TEST_TRUE(distance_sqr(b, a) == 169.0f);
    FND_TEST_TRUE(distance_sqr(a, float4_t{2.0f, 3.0f, 4.0f, 5.0f}) == 4.0f);
    FND_TEST_TRUE(distance_sqr(float4_t{0.0f, 0.0f, 0.0f, -1.5f},
                      float4_t{0.0f, 0.0f, 0.0f, 1.5f})
        == 9.0f);
    FND_TEST_TRUE(distance_sqr(a, float4_t{kFloatInfinity, 2.0f, 3.0f, 4.0f})
        == kFloatInfinity);
    FND_TEST_TRUE(
        isnan(distance_sqr(float4_t{kFloatNaN, 0.0f, 0.0f, 0.0f}, a)));
}

void unittests_math_vector_float4_distance()
{
    const float4_t a{1.0f, 2.0f, 3.0f, 4.0f};
    const float4_t b{4.0f, 6.0f, 15.0f, 4.0f};
    FND_TEST_TRUE(distance(a, a) == 0.0f);
    FND_TEST_TRUE(distance(a, b) == 13.0f);
    FND_TEST_TRUE(distance(b, a) == 13.0f);
    FND_TEST_TRUE(distance(a, float4_t{2.0f, 3.0f, 4.0f, 5.0f}) == 2.0f);
    FND_TEST_TRUE(distance(float4_t{0.0f, 0.0f, 0.0f, -1.5f},
                      float4_t{0.0f, 0.0f, 0.0f, 1.5f})
        == 3.0f);
    // distance(a, b) is the length of a - b.
    const float4_t c{-2.0f, 7.5f, 0.5f, -1.0f};
    FND_TEST_TRUE(distance(a, c) == length(a - c));
    FND_TEST_TRUE(distance(a, float4_t{kFloatInfinity, 2.0f, 3.0f, 4.0f})
        == kFloatInfinity);
}

void unittests_math_vector_float4_distance_matches_length()
{
    // distance(a, b) must give the same result as length(a - b), and
    // distance_sqr(a, b) the same as length_sqr(a - b) and dot(a - b, a - b).
    struct test_value {
        float4_t vec;
        float_t max_abs_diff;
    };

    // max_abs_diff is about 10 ulps of the largest squared distance the vector
    // takes part in.
    const test_value values[] = {
        {float4_t{1.0f, 2.0f, 3.0f, 4.0f}, 1e-4f},
        {float4_t{-2.0f, 7.5f, -1.0f, 0.5f}, 1e-4f},
        {float4_t{0.1f, -0.3f, 0.2f, -0.4f}, 1e-4f},
        {float4_t{-3e-5f, 4e6f, 1.0f, -2.0f}, 1e7f},
        {float4_t{1e19f, -1e-19f, 5e18f, -5e18f}, 1e32f},
    };

    for (const test_value a : values) {
        for (const test_value b : values) {
            // The larger vector of the pair sets the scale of the result.
            const float_t max_abs_diff = max(a.max_abs_diff, b.max_abs_diff);
            const float4_t diff = a.vec - b.vec;
            FND_TEST_TRUE(approx_equal(
                distance_sqr(a.vec, b.vec), length_sqr(diff), max_abs_diff));
            FND_TEST_TRUE(approx_equal(
                distance_sqr(a.vec, b.vec), dot(diff, diff), max_abs_diff));
            FND_TEST_TRUE(approx_equal(
                distance(a.vec, b.vec), length(diff), max_abs_diff));
        }
    }
}

void unittests_math_vector_float4_dot()
{
    const float4_t a{2.5f, -1.0f, 0.5f, 2.0f};
    const float4_t b{-3.0f, 4.0f, 2.0f, 0.5f};
    FND_TEST_TRUE(dot(a, b) == -9.5f);
    FND_TEST_TRUE(dot(b, a) == -9.5f);
    FND_TEST_TRUE(dot(float4_t{1.0f, 2.0f, 3.0f, 4.0f},
                      float4_t{5.0f, 6.0f, 7.0f, 8.0f})
        == 70.0f);
    // Perpendicular vectors.
    FND_TEST_TRUE(dot(float4_t{2.0f, 0.0f, 0.0f, 0.0f},
                      float4_t{0.0f, -5.0f, 3.0f, 1.0f})
        == 0.0f);
    FND_TEST_TRUE(dot(float4_t{1.0f, 1.0f, 0.0f, 1.0f},
                      float4_t{-1.0f, 1.0f, 5.0f, 0.0f})
        == 0.0f);
    // dot(v, v) is the squared length.
    FND_TEST_TRUE(dot(a, a) == 11.5f);
    FND_TEST_TRUE(dot(a, a) == length_sqr(a));
    // The true result 1e40 is out of range.
    const float4_t large{1e20f, 0.0f, 0.0f, 0.0f};
    FND_TEST_TRUE(dot(large, large) == kFloatInfinity);
    FND_TEST_TRUE(
        isnan(dot(float4_t{kFloatNaN, 1.0f, 1.0f, 1.0f}, float4_t{1.0f})));
    // inf * 0 is NaN.
    FND_TEST_TRUE(isnan(dot(float4_t{kFloatInfinity, 0.0f, 0.0f, 0.0f},
        float4_t{0.0f, 1.0f, 1.0f, 1.0f})));
}

void unittests_math_vector_float4_exp_log()
{
    FND_TEST_TRUE(test_components(exp(float4_t{0.0f, 1.0f, -1.0f, 2.0f}),
        exp(0.0f), exp(1.0f), exp(-1.0f), exp(2.0f)));
    FND_TEST_TRUE(test_components(exp2(float4_t{3.0f, -1.0f, 0.5f, 4.0f}),
        exp2(3.0f), exp2(-1.0f), exp2(0.5f), exp2(4.0f)));
    FND_TEST_TRUE(test_components(log(float4_t{1.0f, 2.0f, 0.5f, 4.0f}),
        log(1.0f), log(2.0f), log(0.5f), log(4.0f)));
    FND_TEST_TRUE(test_components(log2(float4_t{8.0f, 0.5f, 2.0f, 16.0f}),
        log2(8.0f), log2(0.5f), log2(2.0f), log2(16.0f)));
    FND_TEST_TRUE(
        test_components(log10(float4_t{1000.0f, 0.01f, 10.0f, 1.0f}),
            log10(1000.0f), log10(0.01f), log10(10.0f), log10(1.0f)));
    FND_TEST_TRUE(test_components(
        exp2(float4_t{3.0f, -1.0f, 0.0f, 4.0f}), 8.0f, 0.5f, 1.0f, 16.0f));
    FND_TEST_TRUE(test_components(
        log2(float4_t{8.0f, 0.5f, 1.0f, 16.0f}), 3.0f, -1.0f, 0.0f, 4.0f));
}

void unittests_math_vector_float4_floor()
{
    FND_TEST_TRUE(test_components(
        floor(float4_t{2.25f, -2.75f, 0.5f, -0.25f}), 2.0f, -3.0f, 0.0f,
        -1.0f));
    FND_TEST_TRUE(test_components(
        floor(float4_t{0.5f, -4.0f, -0.5f, 4.0f}), 0.0f, -4.0f, -1.0f, 4.0f));
    FND_TEST_TRUE(test_components(
        floor(float4_t{-kFloatInfinity, kFloatInfinity, 1.0f, -1.0f}),
        -kFloatInfinity, kFloatInfinity, 1.0f, -1.0f));
    FND_TEST_TRUE(isnan(floor(float4_t{1.0f, kFloatNaN, 1.0f, 1.0f}).y));
}

void unittests_math_vector_float4_fmod()
{
    // The result has the sign of the left operand.
    FND_TEST_TRUE(test_components(
        fmod(float4_t{7.5f, -7.5f, 7.5f, -1.0f},
            float4_t{2.0f, 2.0f, -4.0f, 0.75f}),
        1.5f, -1.5f, 3.5f, -0.25f));
    // float_t on either side is used with every component.
    FND_TEST_TRUE(
        test_components(fmod(float4_t{7.5f, -5.25f, 0.5f, -2.0f}, 2.0f), 1.5f,
            -1.25f, 0.5f, 0.0f));
    FND_TEST_TRUE(
        test_components(fmod(7.5f, float4_t{2.0f, 4.0f, -5.0f, 0.5f}), 1.5f,
            3.5f, 2.5f, 0.0f));
    // A finite x with an infinite y returns x.
    FND_TEST_TRUE(test_components(
        fmod(float4_t{1.5f, -1.5f, 0.0f, 3.0f}, kFloatInfinity), 1.5f, -1.5f,
        0.0f, 3.0f));
    // Unlike operator%, fmod does not assert on a zero divisor: the result is
    // NaN.
    const float4_t zero_divisor = fmod(
        float4_t{1.0f, 2.0f, 3.0f, 4.0f}, float4_t{0.0f, 1.0f, 2.0f, 0.0f});
    FND_TEST_TRUE(isnan(zero_divisor.x));
    FND_TEST_TRUE(zero_divisor.y == 0.0f);
    FND_TEST_TRUE(zero_divisor.z == 1.0f);
    FND_TEST_TRUE(isnan(zero_divisor.w));
    FND_TEST_TRUE(isnan(fmod(kFloatInfinity, float4_t{2.0f}).y));
}

void unittests_math_vector_float4_fractional()
{
    FND_TEST_TRUE(test_components(
        fractional(float4_t{2.75f, 4.0f, 0.5f, -0.5f}), 0.75f, 0.0f, 0.5f,
        0.5f));
    // Negative x gives the magnitude of its fractional part, in [0, 1).
    FND_TEST_TRUE(test_components(
        fractional(float4_t{-2.75f, -1e-10f, -0.25f, -3.0f}), 0.75f, 1e-10f,
        0.25f, 0.0f));
    FND_TEST_TRUE(test_components(
        fractional(float4_t{
            -kFloatInfinity, kFloatInfinity, -kFloatInfinity, kFloatInfinity}),
        0.0f, 0.0f, 0.0f, 0.0f));
    FND_TEST_TRUE(isnan(fractional(float4_t{kFloatNaN, 1.0f, 1.0f, 1.0f}).x));
}

void unittests_math_vector_float4_isfinite()
{
    FND_TEST_TRUE(all(isfinite(float4_t{0.0f, -2.5f, 1.0f, -1.0f})
        == bool4_t{true, true, true, true}));
    FND_TEST_TRUE(
        all(isfinite(float4_t{kFloatMinValue, kFloatMaxValue, 0.0f, -0.0f})
            == bool4_t{true, true, true, true}));
    FND_TEST_TRUE(all(isfinite(float4_t{
                          kFloatMinSubnormal, -0.0f, 1.0f, -kFloatMinSubnormal})
        == bool4_t{true, true, true, true}));
    FND_TEST_TRUE(all(isfinite(float4_t{kFloatInfinity, 1.0f, 1.0f, 1.0f})
        == bool4_t{false, true, true, true}));
    FND_TEST_TRUE(all(isfinite(float4_t{1.0f, -kFloatInfinity, 1.0f, 1.0f})
        == bool4_t{true, false, true, true}));
    FND_TEST_TRUE(all(isfinite(float4_t{1.0f, 1.0f, kFloatNaN, 1.0f})
        == bool4_t{true, true, false, true}));
    FND_TEST_TRUE(all(isfinite(float4_t{1.0f, 1.0f, 1.0f, kFloatInfinity})
        == bool4_t{true, true, true, false}));
    const float4_t non_finite{
        kFloatNaN, kFloatInfinity, -kFloatInfinity, kFloatNaN};
    FND_TEST_TRUE(
        all(isfinite(non_finite) == bool4_t{false, false, false, false}));
}

void unittests_math_vector_float4_isinf()
{
    FND_TEST_TRUE(all(isinf(float4_t{kFloatInfinity, -kFloatInfinity,
                          kFloatInfinity, -kFloatInfinity})
        == bool4_t{true, true, true, true}));
    FND_TEST_TRUE(all(isinf(float4_t{kFloatInfinity, 1.0f, 1.0f, 1.0f})
        == bool4_t{true, false, false, false}));
    FND_TEST_TRUE(all(isinf(float4_t{1.0f, -kFloatInfinity, 1.0f, 1.0f})
        == bool4_t{false, true, false, false}));
    FND_TEST_TRUE(all(isinf(float4_t{1.0f, 1.0f, kFloatInfinity, 1.0f})
        == bool4_t{false, false, true, false}));
    FND_TEST_TRUE(all(isinf(float4_t{1.0f, 1.0f, 1.0f, -kFloatInfinity})
        == bool4_t{false, false, false, true}));
    FND_TEST_TRUE(
        all(isinf(float4_t{kFloatMinValue, kFloatMaxValue, 0.0f, 1.0f})
            == bool4_t{false, false, false, false}));
    FND_TEST_TRUE(all(
        isinf(float4_t{0.0f, kFloatMinSubnormal, -0.0f, -kFloatMinSubnormal})
        == bool4_t{false, false, false, false}));
    // NaN is not infinite.
    FND_TEST_TRUE(
        all(isinf(float4_t{kFloatNaN, kFloatInfinity, 1.0f, kFloatNaN})
            == bool4_t{false, true, false, false}));
}

void unittests_math_vector_float4_isnan()
{
    FND_TEST_TRUE(
        all(isnan(float4_t{kFloatNaN}) == bool4_t{true, true, true, true}));
    FND_TEST_TRUE(all(isnan(float4_t{kFloatNaN, 1.0f, 1.0f, 1.0f})
        == bool4_t{true, false, false, false}));
    FND_TEST_TRUE(all(isnan(float4_t{1.0f, -kFloatNaN, 1.0f, 1.0f})
        == bool4_t{false, true, false, false}));
    FND_TEST_TRUE(all(isnan(float4_t{1.0f, 1.0f, kFloatNaN, 1.0f})
        == bool4_t{false, false, true, false}));
    FND_TEST_TRUE(all(isnan(float4_t{1.0f, 1.0f, 1.0f, kFloatNaN})
        == bool4_t{false, false, false, true}));
    FND_TEST_TRUE(all(isnan(float4_t{0.0f, -2.5f, 1.0f, -1.0f})
        == bool4_t{false, false, false, false}));
    FND_TEST_TRUE(all(isnan(float4_t{kFloatInfinity, -kFloatInfinity,
                          kFloatMaxValue, kFloatMinValue})
        == bool4_t{false, false, false, false}));
    FND_TEST_TRUE(
        all(isnan(float4_t{kFloatMinValue, kFloatMinSubnormal, 0.0f, -0.0f})
            == bool4_t{false, false, false, false}));
    // NaN produced by arithmetic, not only the constant.
    const float4_t inf{kFloatInfinity, 1.0f, -kFloatInfinity, 2.0f};
    FND_TEST_TRUE(
        all(isnan(inf - inf) == bool4_t{true, false, true, false}));
}

void unittests_math_vector_float4_length_sqr()
{
    FND_TEST_TRUE(length_sqr(float4_t{0.0f}) == 0.0f);
    FND_TEST_TRUE(length_sqr(float4_t{1.0f, 2.0f, 2.0f, -4.0f}) == 25.0f);
    FND_TEST_TRUE(length_sqr(float4_t{3.0f, -4.0f, 12.0f, 0.0f}) == 169.0f);
    FND_TEST_TRUE(length_sqr(float4_t{-0.5f, 0.0f, 0.0f, 0.0f}) == 0.25f);
    // The true result 1e40 is out of range.
    FND_TEST_TRUE(
        length_sqr(float4_t{1e20f, 0.0f, 0.0f, 0.0f}) == kFloatInfinity);
    FND_TEST_TRUE(length_sqr(float4_t{1.0f, -kFloatInfinity, 0.0f, 0.0f})
        == kFloatInfinity);
    FND_TEST_TRUE(isnan(length_sqr(float4_t{kFloatNaN, 1.0f, 1.0f, 1.0f})));
}

void unittests_math_vector_float4_length()
{
    FND_TEST_TRUE(length(float4_t{0.0f}) == 0.0f);
    FND_TEST_TRUE(length(float4_t{1.0f, 2.0f, 2.0f, -4.0f}) == 5.0f);
    FND_TEST_TRUE(length(float4_t{3.0f, -4.0f, 12.0f, 0.0f}) == 13.0f);
    FND_TEST_TRUE(length(float4_t{0.0f, -2.5f, 0.0f, 0.0f}) == 2.5f);
    FND_TEST_TRUE(length(float4_t{1.0f}) == 2.0f);
    FND_TEST_TRUE(
        length(float4_t{kFloatInfinity, 1.0f, 1.0f, 1.0f}) == kFloatInfinity);
    FND_TEST_TRUE(
        length(float4_t{1.0f, 1.0f, 1.0f, -kFloatInfinity}) == kFloatInfinity);
}

void unittests_math_vector_float4_lerp()
{
    const float4_t a{0.0f, 10.0f, -4.0f, 1.0f};
    const float4_t b{10.0f, 20.0f, 4.0f, -1.0f};
    FND_TEST_TRUE(test_components(lerp(a, b, 0.0f), 0.0f, 10.0f, -4.0f, 1.0f));
    FND_TEST_TRUE(test_components(lerp(a, b, 1.0f), 10.0f, 20.0f, 4.0f, -1.0f));
    FND_TEST_TRUE(
        test_components(lerp(a, b, 0.25f), 2.5f, 12.5f, -2.0f, 0.5f));
    // t outside [0, 1] extrapolates.
    FND_TEST_TRUE(
        test_components(lerp(a, b, 2.0f), 20.0f, 30.0f, 12.0f, -3.0f));
    // A float4_t t gives each component its own t.
    FND_TEST_TRUE(test_components(
        lerp(a, b, float4_t{0.25f, 0.5f, 0.75f, 1.0f}), 2.5f, 15.0f, 2.0f,
        -1.0f));
    FND_TEST_TRUE(test_components(
        lerp(a, b, float4_t{-1.0f, 1.0f, 0.0f, 0.5f}), -10.0f, 20.0f, -4.0f,
        0.0f));
}

void unittests_math_vector_float4_max()
{
    const float4_t a{7.5f, -3.0f, 0.5f, -1.0f};
    FND_TEST_TRUE(test_components(
        max(a, float4_t{2.0f, 4.0f, 0.5f, -2.0f}), 7.5f, 4.0f, 0.5f, -1.0f));
    FND_TEST_TRUE(test_components(
        max(float4_t{2.0f, 4.0f, 0.5f, -2.0f}, a), 7.5f, 4.0f, 0.5f, -1.0f));
    FND_TEST_TRUE(test_components(
        max(float4_t{4.0f}, float4_t{4.0f}), 4.0f, 4.0f, 4.0f, 4.0f));
    FND_TEST_TRUE(test_components(
        max(float4_t{kFloatInfinity, -kFloatInfinity, 1.0f, -kFloatInfinity},
            float4_t{1.0f, 1.0f, -kFloatInfinity, -kFloatInfinity}),
        kFloatInfinity, 1.0f, 1.0f, -kFloatInfinity));
    // float_t on either side is compared with every component.
    FND_TEST_TRUE(test_components(max(a, 0.0f), 7.5f, 0.0f, 0.5f, 0.0f));
    FND_TEST_TRUE(test_components(max(0.0f, a), 7.5f, 0.0f, 0.5f, 0.0f));
    FND_TEST_TRUE(
        test_components(max(a, 10.0f), 10.0f, 10.0f, 10.0f, 10.0f));
    FND_TEST_TRUE(test_components(max(-5.0f, a), 7.5f, -3.0f, 0.5f, -1.0f));
    // A NaN argument is ignored, as for the float_t max.
    FND_TEST_TRUE(test_components(
        max(float4_t{kFloatNaN, 1.0f, 3.0f, kFloatNaN},
            float4_t{2.0f, kFloatNaN, kFloatNaN, 4.0f}),
        2.0f, 1.0f, 3.0f, 4.0f));
}

void unittests_math_vector_float4_min()
{
    const float4_t a{7.5f, -3.0f, 0.5f, -1.0f};
    FND_TEST_TRUE(test_components(
        min(a, float4_t{2.0f, 4.0f, 0.5f, -2.0f}), 2.0f, -3.0f, 0.5f, -2.0f));
    FND_TEST_TRUE(test_components(
        min(float4_t{2.0f, 4.0f, 0.5f, -2.0f}, a), 2.0f, -3.0f, 0.5f, -2.0f));
    FND_TEST_TRUE(test_components(
        min(float4_t{4.0f}, float4_t{4.0f}), 4.0f, 4.0f, 4.0f, 4.0f));
    FND_TEST_TRUE(test_components(
        min(float4_t{kFloatInfinity, -kFloatInfinity, 1.0f, kFloatInfinity},
            float4_t{1.0f, 1.0f, -kFloatInfinity, kFloatInfinity}),
        1.0f, -kFloatInfinity, -kFloatInfinity, kFloatInfinity));
    // float_t on either side is compared with every component.
    FND_TEST_TRUE(test_components(min(a, 0.0f), 0.0f, -3.0f, 0.0f, -1.0f));
    FND_TEST_TRUE(test_components(min(0.0f, a), 0.0f, -3.0f, 0.0f, -1.0f));
    FND_TEST_TRUE(
        test_components(min(a, -5.0f), -5.0f, -5.0f, -5.0f, -5.0f));
    FND_TEST_TRUE(test_components(min(10.0f, a), 7.5f, -3.0f, 0.5f, -1.0f));
    // A NaN argument is ignored, as for the float_t min.
    FND_TEST_TRUE(test_components(
        min(float4_t{kFloatNaN, 1.0f, 3.0f, kFloatNaN},
            float4_t{2.0f, kFloatNaN, kFloatNaN, 4.0f}),
        2.0f, 1.0f, 3.0f, 4.0f));
}

void unittests_math_vector_float4_modf()
{
    float4_t vi;

    // Both parts have the sign of the component.
    FND_TEST_TRUE(test_components(
        modf(float4_t{3.75f, -3.75f, 0.5f, -0.5f}, vi), 0.75f, -0.75f, 0.5f,
        -0.5f));
    FND_TEST_TRUE(test_components(vi, 3.0f, -3.0f, 0.0f, 0.0f));
    FND_TEST_TRUE(test_components(
        modf(float4_t{-2.0f, 2.0f, 0.0f, 5.0f}, vi), 0.0f, 0.0f, 0.0f, 0.0f));
    FND_TEST_TRUE(test_components(vi, -2.0f, 2.0f, 0.0f, 5.0f));
    FND_TEST_TRUE(test_components(
        modf(float4_t{0.5f, -0.5f, kFloatMinSubnormal, -kFloatMinSubnormal},
            vi),
        0.5f, -0.5f, kFloatMinSubnormal, -kFloatMinSubnormal));
    FND_TEST_TRUE(test_components(vi, 0.0f, 0.0f, 0.0f, 0.0f));
    FND_TEST_TRUE(test_components(
        modf(float4_t{kFloatMaxValue, -1.25f, 1.5f, -2.75f}, vi), 0.0f,
        -0.25f, 0.5f, -0.75f));
    FND_TEST_TRUE(test_components(vi, kFloatMaxValue, -1.0f, 1.0f, -2.0f));
    FND_TEST_TRUE(test_components(
        modf(float4_t{kFloatInfinity, -kFloatInfinity, -2.5f, 2.5f}, vi), 0.0f,
        0.0f, -0.5f, 0.5f));
    FND_TEST_TRUE(
        test_components(vi, kFloatInfinity, -kFloatInfinity, -2.0f, 2.0f));
    // A NaN component gives NaN in both parts and does not affect the others.
    const float4_t frac = modf(float4_t{kFloatNaN, 7.5f, -0.25f, 1.0f}, vi);
    FND_TEST_TRUE(isnan(frac.x));
    FND_TEST_TRUE(isnan(vi.x));
    FND_TEST_TRUE(frac.y == 0.5f);
    FND_TEST_TRUE(vi.y == 7.0f);
    FND_TEST_TRUE(frac.z == -0.25f);
    FND_TEST_TRUE(vi.z == 0.0f);
    FND_TEST_TRUE(frac.w == 0.0f);
    FND_TEST_TRUE(vi.w == 1.0f);
    // The parts add up to the input.
    const float4_t v{-123.625f, 0.375f, 64.5f, -0.125f};
    const float4_t vf = modf(v, vi);
    FND_TEST_TRUE(all(vf + vi == v));
}

void unittests_math_vector_float4_normalize()
{
    FND_TEST_TRUE(test_components(
        normalize(float4_t{5.0f, 0.0f, 0.0f, 0.0f}), 1.0f, 0.0f, 0.0f, 0.0f));
    FND_TEST_TRUE(test_components(
        normalize(float4_t{0.0f, -0.5f, 0.0f, 0.0f}), 0.0f, -1.0f, 0.0f,
        0.0f));
    FND_TEST_TRUE(test_components(
        normalize(float4_t{0.0f, 0.0f, 2.0f, 0.0f}), 0.0f, 0.0f, 1.0f, 0.0f));
    FND_TEST_TRUE(test_components(
        normalize(float4_t{0.0f, 0.0f, 0.0f, -4.0f}), 0.0f, 0.0f, 0.0f,
        -1.0f));
    FND_TEST_TRUE(all(approx_equal(normalize(float4_t{1.0f, 2.0f, 2.0f, -4.0f}),
        float4_t{0.2f, 0.4f, 0.4f, -0.8f})));
    FND_TEST_TRUE(
        all(approx_equal(normalize(float4_t{3.0f, -4.0f, 12.0f, 0.0f}),
            float4_t{0.23076923f, -0.30769231f, 0.92307692f, 0.0f})));
    FND_TEST_TRUE(all(approx_equal(normalize(float4_t{-1.0f, 1.0f, 1.0f, 1.0f}),
        float4_t{-0.5f, 0.5f, 0.5f, 0.5f})));
    // The result has unit length and keeps the direction of v.
    const float4_t v{-2.5f, 7.0f, 1.0f, -3.0f};
    const float4_t n = normalize(v);
    FND_TEST_TRUE(approx_equal(length(n), 1.0f));
    FND_TEST_TRUE(all(approx_equal(n * length(v), v)));
    // Large and small vectors whose squared length is still a normal float.
    FND_TEST_TRUE(all(approx_equal(normalize(float4_t{1e19f, 0.0f, 0.0f, 0.0f}),
        float4_t{1.0f, 0.0f, 0.0f, 0.0f})));
    FND_TEST_TRUE(
        all(approx_equal(normalize(float4_t{0.0f, 0.0f, 0.0f, 1e-18f}),
            float4_t{0.0f, 0.0f, 0.0f, 1.0f})));
}

void unittests_math_vector_float4_normalize_safe()
{
    // A zero vector gives default_value.
    FND_TEST_TRUE(test_components(
        normalize_safe(float4_t{}), 0.0f, 0.0f, 0.0f, 0.0f));
    FND_TEST_TRUE(test_components(
        normalize_safe(float4_t{-0.0f, 0.0f, -0.0f, 0.0f},
            float4_t{1.0f, 0.0f, 0.0f, 0.0f}),
        1.0f, 0.0f, 0.0f, 0.0f));
    // So does a vector whose squared length does not exceed kFloatMinNormal.
    FND_TEST_TRUE(test_components(
        normalize_safe(float4_t{1e-20f, 0.0f, 0.0f, 0.0f},
            float4_t{0.0f, -1.0f, 0.0f, 0.0f}),
        0.0f, -1.0f, 0.0f, 0.0f));
    FND_TEST_TRUE(
        test_components(normalize_safe(float4_t{kFloatMinSubnormal},
                            float4_t{0.0f, -1.0f, 0.0f, 0.0f}),
            0.0f, -1.0f, 0.0f, 0.0f));
    // Any other vector is normalized and default_value is ignored.
    const float4_t d{9.0f};
    FND_TEST_TRUE(test_components(
        normalize_safe(float4_t{5.0f, 0.0f, 0.0f, 0.0f}, d), 1.0f, 0.0f, 0.0f,
        0.0f));
    FND_TEST_TRUE(all(
        approx_equal(normalize_safe(float4_t{1.0f, 2.0f, 2.0f, -4.0f}, d),
            float4_t{0.2f, 0.4f, 0.4f, -0.8f})));
    const float4_t v{-2.5f, 7.0f, 1.0f, -3.0f};
    FND_TEST_TRUE(all(normalize_safe(v, d) == normalize(v)));

    // Very large finite vectors are normalized too.
    FND_TEST_TRUE(
        all(approx_equal(normalize_safe(float4_t{1e20f, 1.0f, 1.0f, 1.0f}, d),
            float4_t{1.0f, 1e-20f, 1e-20f, 1e-20f})));
    FND_TEST_TRUE(all(approx_equal(
        normalize_safe(float4_t{2e19f, -1e19f, 2e19f, -4e19f}, d),
        float4_t{0.4f, -0.2f, 0.4f, -0.8f})));
    FND_TEST_TRUE(all(approx_equal(
        normalize_safe(float4_t{0.0f, 0.0f, 0.0f, -kFloatMaxValue}, d),
        float4_t{0.0f, 0.0f, 0.0f, -1.0f})));
    FND_TEST_TRUE(all(approx_equal(
        normalize_safe(float4_t{kFloatMaxValue, -kFloatMaxValue,
                           kFloatMaxValue, -kFloatMaxValue},
            d),
        float4_t{0.5f, -0.5f, 0.5f, -0.5f})));
    FND_TEST_TRUE(approx_equal(
        length(normalize_safe(float4_t{kFloatMaxValue}, d)), 1.0f));
    // A large vector gives the same result as normalize.
    const float4_t large{8e18f, -8e18f, 8e18f, -8e18f};
    FND_TEST_TRUE(all(normalize_safe(large, d) == normalize(large)));

    // Scaling a vector up by a large factor does not change the result.
    const float4_t dirs[] = {
        float4_t{1.0f, 2.0f, 2.0f, -4.0f},
        float4_t{-2.5f, 7.0f, 1.0f, -3.0f},
        float4_t{1.0f, 1.0f, 1.0f, 1.0f},
        float4_t{0.1f, -0.3f, 0.2f, -0.4f},
    };
    for (const float4_t dir : dirs) {
        const float4_t scaled = dir * 1e20f;
        const float4_t n = normalize_safe(scaled, d);
        FND_TEST_TRUE(all(approx_equal(n, normalize_safe(dir, d))));
        FND_TEST_TRUE(approx_equal(length(n), 1.0f));
    }
}

void unittests_math_vector_float4_pow()
{
    FND_TEST_TRUE(test_components(
        pow(float4_t{2.0f, 9.0f, 4.0f, 0.5f},
            float4_t{10.0f, 0.5f, -1.0f, 2.0f}),
        pow(2.0f, 10.0f), pow(9.0f, 0.5f), pow(4.0f, -1.0f), pow(0.5f, 2.0f)));
    FND_TEST_TRUE(
        test_components(pow(float4_t{3.0f, -4.0f, 0.5f, -1.0f}, 2.0f),
            pow(3.0f, 2.0f), pow(-4.0f, 2.0f), pow(0.5f, 2.0f),
            pow(-1.0f, 2.0f)));
    FND_TEST_TRUE(approx_equal(pow(float4_t{2.0f, 9.0f, 4.0f, 0.5f},
                                   float4_t{10.0f, 0.5f, -1.0f, 2.0f})
                                   .y,
        3.0f));
}

void unittests_math_vector_float4_rcp_sqrt_rsqrt()
{
    FND_TEST_TRUE(test_components(
        rcp(float4_t{2.0f, -4.0f, 0.5f, -0.125f}), 0.5f, -0.25f, 2.0f, -8.0f));
    FND_TEST_TRUE(test_components(
        sqrt(float4_t{4.0f, 2.25f, 0.25f, 16.0f}), 2.0f, 1.5f, 0.5f, 4.0f));
    FND_TEST_TRUE(test_components(sqrt(float4_t{2.0f, 3.0f, 5.0f, 7.0f}),
        sqrt(2.0f), sqrt(3.0f), sqrt(5.0f), sqrt(7.0f)));
    FND_TEST_TRUE(test_components(
        rsqrt(float4_t{4.0f, 0.25f, 16.0f, 1.0f}), 0.5f, 2.0f, 0.25f, 1.0f));
    FND_TEST_TRUE(test_components(rsqrt(float4_t{2.0f, 3.0f, 5.0f, 7.0f}),
        rsqrt(2.0f), rsqrt(3.0f), rsqrt(5.0f), rsqrt(7.0f)));
}

void unittests_math_vector_float4_saturate()
{
    FND_TEST_TRUE(test_components(
        saturate(float4_t{0.25f, 0.75f, 0.5f, 1.0f}), 0.25f, 0.75f, 0.5f,
        1.0f));
    FND_TEST_TRUE(test_components(
        saturate(float4_t{-0.5f, 1.5f, 2.0f, -2.0f}), 0.0f, 1.0f, 1.0f, 0.0f));
    FND_TEST_TRUE(test_components(
        saturate(float4_t{0.0f, 1.0f, 0.5f, 0.125f}), 0.0f, 1.0f, 0.5f,
        0.125f));
    FND_TEST_TRUE(test_components(
        saturate(float4_t{-kFloatInfinity, kFloatInfinity, -1.0f, 0.5f}), 0.0f,
        1.0f, 0.0f, 0.5f));
}

void unittests_math_vector_float4_sign()
{
    FND_TEST_TRUE(test_components(
        sign(float4_t{7.5f, -3.0f, 0.0f, -0.25f}), 1.0f, -1.0f, 0.0f, -1.0f));
    FND_TEST_TRUE(test_components(
        sign(float4_t{0.0f, -0.0f, 0.0f, -0.0f}), 0.0f, 0.0f, 0.0f, 0.0f));
    FND_TEST_TRUE(test_components(
        sign(float4_t{kFloatInfinity, -kFloatInfinity, 1.0f, -1.0f}), 1.0f,
        -1.0f, 1.0f, -1.0f));
    FND_TEST_TRUE(test_components(
        sign(float4_t{kFloatMinSubnormal, -kFloatMinSubnormal, -1.0f, 1.0f}),
        1.0f, -1.0f, -1.0f, 1.0f));
    // NaN has no sign: 0.
    FND_TEST_TRUE(test_components(
        sign(float4_t{kFloatNaN, 2.0f, -2.0f, 0.0f}), 0.0f, 1.0f, -1.0f, 0.0f));
}

void unittests_math_vector_float4_smoothstep()
{
    // Each component has its own edges; edge0 > edge1 reverses the curve.
    const float4_t edge0{0.0f, 2.0f, -1.0f, 4.0f};
    const float4_t edge1{1.0f, 4.0f, 1.0f, 0.0f};
    FND_TEST_TRUE(test_components(
        smoothstep(float4_t{0.25f, 3.0f, 0.0f, 1.0f}, edge0, edge1), 0.15625f,
        0.5f, 0.5f, 0.84375f));
    FND_TEST_TRUE(test_components(
        smoothstep(float4_t{-1.0f, 5.0f, 2.0f, 5.0f}, edge0, edge1), 0.0f,
        1.0f, 1.0f, 0.0f));
    // float_t edges apply to every component.
    FND_TEST_TRUE(test_components(
        smoothstep(float4_t{0.25f, 0.75f, 0.5f, 2.0f}, 0.0f, 1.0f), 0.15625f,
        0.84375f, 0.5f, 1.0f));
    FND_TEST_TRUE(test_components(
        smoothstep(float4_t{-1.0f, 2.0f, 0.0f, 1.0f}, 0.0f, 1.0f), 0.0f, 1.0f,
        0.0f, 1.0f));
}

void unittests_math_vector_float4_trunc()
{
    // Rounds toward zero: down for positive, up for negative.
    FND_TEST_TRUE(test_components(
        trunc(float4_t{2.75f, -2.75f, 0.5f, -0.5f}), 2.0f, -2.0f, 0.0f, 0.0f));
    FND_TEST_TRUE(test_components(
        trunc(float4_t{-0.5f, 4.0f, -4.0f, 1.5f}), 0.0f, 4.0f, -4.0f, 1.0f));
    FND_TEST_TRUE(test_components(
        trunc(float4_t{-kFloatInfinity, kFloatInfinity, 1.0f, -1.0f}),
        -kFloatInfinity, kFloatInfinity, 1.0f, -1.0f));
    FND_TEST_TRUE(isnan(trunc(float4_t{kFloatNaN, 1.0f, 1.0f, 1.0f}).x));
}

void unittests_math_vector_float4()
{
    unittests_math_vector_float4_type();
    unittests_math_vector_float4_constants();
    unittests_math_vector_float4_constructors();
    unittests_math_vector_float4_subscript_operator();
    unittests_math_vector_float4_increment_operators();
    unittests_math_vector_float4_decrement_operators();
    unittests_math_vector_float4_unary_minus_operator();
    unittests_math_vector_float4_compound_assignment_operators();
    unittests_math_vector_float4_compound_assignment_matches_operators();
    unittests_math_vector_float4_equality_operators();
    unittests_math_vector_float4_relational_operators();
    unittests_math_vector_float4_multiplication_operator();
    unittests_math_vector_float4_addition_operator();
    unittests_math_vector_float4_subtraction_operator();
    unittests_math_vector_float4_modulo_operator();
    unittests_math_vector_float4_modulo_operator_matches_fmod();
    unittests_math_vector_float4_division_operator();
    unittests_math_vector_float4_abs();
    unittests_math_vector_float4_inverse_trigonometry();
    unittests_math_vector_float4_approx_equal();
    unittests_math_vector_float4_ceil();
    unittests_math_vector_float4_clamp();
    unittests_math_vector_float4_cmax();
    unittests_math_vector_float4_cmin();
    unittests_math_vector_float4_cmul();
    unittests_math_vector_float4_trigonometry();
    unittests_math_vector_float4_csum();
    unittests_math_vector_float4_degrees_radians();
    unittests_math_vector_float4_distance_sqr();
    unittests_math_vector_float4_distance();
    unittests_math_vector_float4_distance_matches_length();
    unittests_math_vector_float4_dot();
    unittests_math_vector_float4_exp_log();
    unittests_math_vector_float4_floor();
    unittests_math_vector_float4_fmod();
    unittests_math_vector_float4_fractional();
    unittests_math_vector_float4_isfinite();
    unittests_math_vector_float4_isinf();
    unittests_math_vector_float4_isnan();
    unittests_math_vector_float4_length_sqr();
    unittests_math_vector_float4_length();
    unittests_math_vector_float4_lerp();
    unittests_math_vector_float4_max();
    unittests_math_vector_float4_min();
    unittests_math_vector_float4_modf();
    unittests_math_vector_float4_normalize();
    unittests_math_vector_float4_normalize_safe();
    unittests_math_vector_float4_pow();
    unittests_math_vector_float4_rcp_sqrt_rsqrt();
    unittests_math_vector_float4_saturate();
    unittests_math_vector_float4_sign();
    unittests_math_vector_float4_smoothstep();
    unittests_math_vector_float4_trunc();
}

} // namespace fnd::unittests
