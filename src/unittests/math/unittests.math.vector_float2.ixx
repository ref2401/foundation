module;
#include "foundation/unittests.h"


export module unittests.math:vector_float2;
import foundation.core;
import foundation.math;

namespace fnd::unittests {

export void unittests_math_vector_float2();

// All expected values below are exact in binary, so == is reliable.
constexpr bool_t test_components(
    const float2_t v, const float_t x, const float_t y)
{
    return v.x == x && v.y == y;
}

void unittests_math_vector_float2_type()
{
    static_assert(PodType<float2_t>);
    static_assert(sizeof(float2_t) == 2 * sizeof(float_t));
    // The ctor(float_t) and ctor(bool2_t) are explicit.
    static_assert(!is_convertible<float_t, float2_t>());
    static_assert(!is_convertible<bool2_t, float2_t>());
}

void unittests_math_vector_float2_constructors()
{
    FND_TEST_TRUE(test_components(float2_t{}, 0.0f, 0.0f));
    FND_TEST_TRUE(test_components(float2_t{2.5f}, 2.5f, 2.5f));
    FND_TEST_TRUE(test_components(float2_t{-2.5f}, -2.5f, -2.5f));
    FND_TEST_TRUE(test_components(float2_t{3.0f, -4.5f}, 3.0f, -4.5f));
    FND_TEST_TRUE(test_components(float2_t{kFloatMinValue, kFloatMaxValue},
        kFloatMinValue, kFloatMaxValue));
    // From a bool2_t: true is 1, false is 0.
    FND_TEST_TRUE(test_components(float2_t{bool2_t{true, false}}, 1.0f, 0.0f));
    FND_TEST_TRUE(test_components(float2_t{bool2_t{false, true}}, 0.0f, 1.0f));
}

void unittests_math_vector_float2_subscript_operator()
{
    const float2_t v{3.0f, -4.5f};
    FND_TEST_TRUE(v[0] == 3.0f);
    FND_TEST_TRUE(v[1] == -4.5f);

    // The non-const overload returns a reference into the vector itself.
    float2_t w;
    w[1] = 9.5f;
    FND_TEST_TRUE(test_components(w, 0.0f, 9.5f));

    w[0] = -1.0f;
    FND_TEST_TRUE(test_components(w, -1.0f, 9.5f));
}

void unittests_math_vector_float2_increment_operators()
{
    float2_t v{1.5f, -1.0f};
    FND_TEST_TRUE(test_components(++v, 2.5f, 0.0f));
    FND_TEST_TRUE(test_components(v, 2.5f, 0.0f));

    // Postfix returns the value before the increment.
    FND_TEST_TRUE(test_components(v++, 2.5f, 0.0f));
    FND_TEST_TRUE(test_components(v, 3.5f, 1.0f));
}

void unittests_math_vector_float2_decrement_operators()
{
    float2_t v{1.5f, -1.0f};
    FND_TEST_TRUE(test_components(--v, 0.5f, -2.0f));
    FND_TEST_TRUE(test_components(v, 0.5f, -2.0f));

    // Postfix returns the value before the decrement.
    FND_TEST_TRUE(test_components(v--, 0.5f, -2.0f));
    FND_TEST_TRUE(test_components(v, -0.5f, -3.0f));
}

void unittests_math_vector_float2_unary_minus_operator()
{
    FND_TEST_TRUE(test_components(-float2_t{7.5f, -3.0f}, -7.5f, 3.0f));
    FND_TEST_TRUE(test_components(-float2_t{0.0f, 0.0f}, 0.0f, 0.0f));
    FND_TEST_TRUE(test_components(-float2_t{kFloatInfinity, kFloatMaxValue},
        -kFloatInfinity, kFloatMinValue));

    const float2_t n = -float2_t{kFloatNaN, 1.0f};
    FND_TEST_TRUE(isnan(n.x));
    FND_TEST_TRUE(n.y == -1.0f);
}

void unittests_math_vector_float2_compound_assignment_operators()
{
    float2_t v{7.5f, -3.0f};

    // Each operator returns a reference to its left operand.
    FND_TEST_TRUE(&(v += float2_t{1.0f, 2.0f}) == &v);
    FND_TEST_TRUE(test_components(v, 8.5f, -1.0f));
    FND_TEST_TRUE(test_components(v += 2.0f, 10.5f, 1.0f));

    FND_TEST_TRUE(test_components(v -= float2_t{4.0f, 3.0f}, 6.5f, -2.0f));
    FND_TEST_TRUE(test_components(v -= 1.0f, 5.5f, -3.0f));

    FND_TEST_TRUE(test_components(v *= float2_t{2.0f, -2.0f}, 11.0f, 6.0f));
    FND_TEST_TRUE(test_components(v *= 0.5f, 5.5f, 3.0f));

    FND_TEST_TRUE(test_components(v /= float2_t{2.0f, 4.0f}, 2.75f, 0.75f));
    FND_TEST_TRUE(test_components(v /= 0.25f, 11.0f, 3.0f));

    FND_TEST_TRUE(test_components(v %= float2_t{4.0f, 2.0f}, 3.0f, 1.0f));
    FND_TEST_TRUE(test_components(v %= 2.0f, 1.0f, 1.0f));
}

void unittests_math_vector_float2_compound_assignment_matches_operators()
{
    // a op= b must give the same result as a op b.
    const float2_t a{7.5f, -3.0f};
    const float2_t b{2.0f, 4.0f};
    const float_t val{2.0f};
    float2_t c;

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

void unittests_math_vector_float2_equality_operators()
{
    const float2_t a{7.5f, -3.0f};
    FND_TEST_TRUE(all((a == float2_t{7.5f, -3.0f}) == bool2_t{true, true}));
    FND_TEST_TRUE(all((a == float2_t{7.5f, 5.0f}) == bool2_t{true, false}));
    FND_TEST_TRUE(all((a == float2_t{2.0f, 5.0f}) == bool2_t{false, false}));
    FND_TEST_TRUE(all((a == 7.5f) == bool2_t{true, false}));
    FND_TEST_TRUE(all((-3.0f == a) == bool2_t{false, true}));

    FND_TEST_TRUE(all((a != float2_t{7.5f, -3.0f}) == bool2_t{false, false}));
    FND_TEST_TRUE(all((a != float2_t{7.5f, 5.0f}) == bool2_t{false, true}));
    FND_TEST_TRUE(all((a != float2_t{2.0f, 5.0f}) == bool2_t{true, true}));
    FND_TEST_TRUE(all((a != 7.5f) == bool2_t{false, true}));
    FND_TEST_TRUE(all((-3.0f != a) == bool2_t{true, false}));

    // NaN compares unequal to everything, itself included; -0 equals +0.
    const float2_t n{kFloatNaN, -0.0f};
    FND_TEST_TRUE(
        all((n == float2_t{kFloatNaN, 0.0f}) == bool2_t{false, true}));
    FND_TEST_TRUE(
        all((n != float2_t{kFloatNaN, 0.0f}) == bool2_t{true, false}));
}

void unittests_math_vector_float2_relational_operators()
{
    const float2_t a{7.5f, -3.0f};
    const float2_t b{2.0f, 5.0f};
    const float2_t c{7.5f, 5.0f};

    FND_TEST_TRUE(all((a < b) == bool2_t{false, true}));
    FND_TEST_TRUE(all((a < c) == bool2_t{false, true}));
    FND_TEST_TRUE(all((a < 0.0f) == bool2_t{false, true}));
    FND_TEST_TRUE(all((0.0f < a) == bool2_t{true, false}));

    FND_TEST_TRUE(all((a <= b) == bool2_t{false, true}));
    FND_TEST_TRUE(all((a <= c) == bool2_t{true, true}));
    FND_TEST_TRUE(all((a <= -3.0f) == bool2_t{false, true}));
    FND_TEST_TRUE(all((7.5f <= a) == bool2_t{true, false}));

    FND_TEST_TRUE(all((a > b) == bool2_t{true, false}));
    FND_TEST_TRUE(all((a > c) == bool2_t{false, false}));
    FND_TEST_TRUE(all((a > 0.0f) == bool2_t{true, false}));
    FND_TEST_TRUE(all((0.0f > a) == bool2_t{false, true}));

    FND_TEST_TRUE(all((a >= b) == bool2_t{true, false}));
    FND_TEST_TRUE(all((a >= c) == bool2_t{true, false}));
    FND_TEST_TRUE(all((a >= 7.5f) == bool2_t{true, false}));
    FND_TEST_TRUE(all((7.5f >= a) == bool2_t{true, true}));

    // Every ordered comparison with NaN is false.
    const float2_t n{kFloatNaN, 1.0f};
    FND_TEST_TRUE(all((n < 2.0f) == bool2_t{false, true}));
    FND_TEST_TRUE(all((n <= 1.0f) == bool2_t{false, true}));
    FND_TEST_TRUE(all((n > 0.0f) == bool2_t{false, true}));
    FND_TEST_TRUE(all((n >= 1.0f) == bool2_t{false, true}));
}

void unittests_math_vector_float2_multiplication_operator()
{
    const float2_t a{7.5f, -3.0f};
    FND_TEST_TRUE(test_components(a * float2_t{2.0f, 5.0f}, 15.0f, -15.0f));
    FND_TEST_TRUE(test_components(a * 2.0f, 15.0f, -6.0f));
    FND_TEST_TRUE(test_components(2.0f * a, 15.0f, -6.0f));
    // Overflow gives infinity.
    FND_TEST_TRUE(test_components(
        float2_t{kFloatMaxValue, 2.0f} * 2.0f, kFloatInfinity, 4.0f));
}

void unittests_math_vector_float2_addition_operator()
{
    const float2_t a{7.5f, -3.0f};
    FND_TEST_TRUE(test_components(a + float2_t{2.0f, 5.0f}, 9.5f, 2.0f));
    FND_TEST_TRUE(test_components(a + 1.0f, 8.5f, -2.0f));
    FND_TEST_TRUE(test_components(1.0f + a, 8.5f, -2.0f));
    // Overflow gives infinity.
    FND_TEST_TRUE(test_components(float2_t{kFloatMaxValue, 1.0f}
            + float2_t{kFloatMaxValue, kFloatInfinity},
        kFloatInfinity, kFloatInfinity));
}

void unittests_math_vector_float2_subtraction_operator()
{
    const float2_t a{7.5f, -3.0f};
    FND_TEST_TRUE(test_components(a - float2_t{2.0f, 5.0f}, 5.5f, -8.0f));
    FND_TEST_TRUE(test_components(a - 1.0f, 6.5f, -4.0f));
    FND_TEST_TRUE(test_components(1.0f - a, -6.5f, 4.0f));
    // Overflow gives -infinity.
    FND_TEST_TRUE(test_components(
        float2_t{kFloatMinValue, 0.0f} - float2_t{kFloatMaxValue, 0.0f},
        -kFloatInfinity, 0.0f));
}

void unittests_math_vector_float2_modulo_operator()
{
    // fmod: the result has the sign of the left operand.
    const float2_t a{7.5f, -3.0f};
    FND_TEST_TRUE(test_components(a % float2_t{2.0f, 2.0f}, 1.5f, -1.0f));
    FND_TEST_TRUE(test_components(a % 2.0f, 1.5f, -1.0f));
    FND_TEST_TRUE(test_components(7.0f % float2_t{2.0f, 4.0f}, 1.0f, 3.0f));
    FND_TEST_TRUE(test_components(
        float2_t{-7.5f, 7.5f} % float2_t{2.0f, -2.0f}, -1.5f, 1.5f));
}

void unittests_math_vector_float2_division_operator()
{
    const float2_t a{7.5f, -3.0f};
    FND_TEST_TRUE(test_components(a / float2_t{2.0f, 4.0f}, 3.75f, -0.75f));
    FND_TEST_TRUE(test_components(a / 2.0f, 3.75f, -1.5f));
    FND_TEST_TRUE(test_components(3.0f / float2_t{2.0f, 4.0f}, 1.5f, 0.75f));
    FND_TEST_TRUE(
        test_components(float2_t{kFloatInfinity, 1.0f} / float2_t{2.0f, 4.0f},
            kFloatInfinity, 0.25f));
}

void unittests_math_vector_float2_abs()
{
    FND_TEST_TRUE(test_components(abs(float2_t{7.5f, -3.0f}), 7.5f, 3.0f));
    FND_TEST_TRUE(test_components(
        abs(float2_t{-0.0f, -kFloatInfinity}), 0.0f, kFloatInfinity));
    FND_TEST_TRUE(test_components(abs(float2_t{kFloatMinValue, kFloatMaxValue}),
        kFloatMaxValue, kFloatMaxValue));

    const float2_t n = abs(float2_t{kFloatNaN, -1.0f});
    FND_TEST_TRUE(isnan(n.x));
    FND_TEST_TRUE(n.y == 1.0f);
}

// The float2_t math functions apply the float_t ones per component. Comparing
// against the float_t function catches wrong or swapped components exactly.

void unittests_math_vector_float2_inverse_trigonometry()
{
    const float2_t v{0.5f, -1.0f};
    FND_TEST_TRUE(test_components(acos(v), acos(0.5f), acos(-1.0f)));
    FND_TEST_TRUE(test_components(asin(v), asin(0.5f), asin(-1.0f)));
    FND_TEST_TRUE(
        test_components(atan(float2_t{1.0f, -2.0f}), atan(1.0f), atan(-2.0f)));
    FND_TEST_TRUE(
        test_components(atan2(float2_t{1.0f, -1.0f}, float2_t{-1.0f, 2.0f}),
            atan2(1.0f, -1.0f), atan2(-1.0f, 2.0f)));
    FND_TEST_TRUE(approx_equal(acos(float2_t{-1.0f, 1.0f}).x, kFloatPi));
}

void unittests_math_vector_float2_ceil()
{
    FND_TEST_TRUE(test_components(ceil(float2_t{2.25f, -2.75f}), 3.0f, -2.0f));
    FND_TEST_TRUE(test_components(ceil(float2_t{-0.5f, 4.0f}), 0.0f, 4.0f));
    FND_TEST_TRUE(
        test_components(ceil(float2_t{-kFloatInfinity, kFloatInfinity}),
            -kFloatInfinity, kFloatInfinity));
    FND_TEST_TRUE(isnan(ceil(float2_t{kFloatNaN, 1.0f}).x));
}

void unittests_math_vector_float2_clamp()
{
    const float2_t lower{-10.0f, 0.0f};
    const float2_t upper{10.0f, 5.0f};
    // Each component is clamped to its own bounds.
    FND_TEST_TRUE(
        test_components(clamp(float2_t{3.0f, 3.0f}, lower, upper), 3.0f, 3.0f));
    FND_TEST_TRUE(test_components(
        clamp(float2_t{-20.0f, -1.0f}, lower, upper), -10.0f, 0.0f));
    FND_TEST_TRUE(test_components(
        clamp(float2_t{20.0f, 6.0f}, lower, upper), 10.0f, 5.0f));
    FND_TEST_TRUE(test_components(
        clamp(float2_t{-10.0f, 5.0f}, lower, upper), -10.0f, 5.0f));
    FND_TEST_TRUE(test_components(
        clamp(float2_t{-kFloatInfinity, kFloatInfinity}, lower, upper), -10.0f,
        5.0f));
    FND_TEST_TRUE(test_components(
        clamp(float2_t{9.0f, 9.0f}, float2_t{3.0f, 3.0f}, float2_t{3.0f, 3.0f}),
        3.0f, 3.0f));

    // float_t bounds apply to every component.
    FND_TEST_TRUE(
        test_components(clamp(float2_t{0.5f, 9.5f}, 0.0f, 1.0f), 0.5f, 1.0f));
    FND_TEST_TRUE(test_components(
        clamp(float2_t{-20.0f, 20.0f}, -10.0f, 10.0f), -10.0f, 10.0f));
    FND_TEST_TRUE(
        test_components(clamp(float2_t{9.0f, -9.0f}, 3.0f, 3.0f), 3.0f, 3.0f));

    // float2_t lower bound, float_t upper bound.
    FND_TEST_TRUE(test_components(
        clamp(float2_t{-20.0f, -20.0f}, float2_t{-10.0f, 0.0f}, 5.0f), -10.0f,
        0.0f));
    FND_TEST_TRUE(test_components(
        clamp(float2_t{20.0f, 3.0f}, float2_t{-10.0f, 0.0f}, 5.0f), 5.0f,
        3.0f));

    // float_t lower bound, float2_t upper bound.
    FND_TEST_TRUE(test_components(
        clamp(float2_t{-20.0f, -20.0f}, 0.0f, float2_t{10.0f, 5.0f}), 0.0f,
        0.0f));
    FND_TEST_TRUE(test_components(
        clamp(float2_t{20.0f, 3.0f}, 0.0f, float2_t{10.0f, 5.0f}), 10.0f,
        3.0f));
}

void unittests_math_vector_float2_cmax()
{
    FND_TEST_TRUE(cmax(float2_t{7.5f, -3.0f}) == 7.5f);
    FND_TEST_TRUE(cmax(float2_t{-3.0f, 7.5f}) == 7.5f);
    FND_TEST_TRUE(cmax(float2_t{4.0f, 4.0f}) == 4.0f);
    FND_TEST_TRUE(
        cmax(float2_t{-kFloatInfinity, kFloatInfinity}) == kFloatInfinity);
    // A NaN component is ignored, as for the float_t max.
    FND_TEST_TRUE(cmax(float2_t{kFloatNaN, 1.0f}) == 1.0f);
    FND_TEST_TRUE(cmax(float2_t{1.0f, kFloatNaN}) == 1.0f);
}

void unittests_math_vector_float2_cmin()
{
    FND_TEST_TRUE(cmin(float2_t{7.5f, -3.0f}) == -3.0f);
    FND_TEST_TRUE(cmin(float2_t{-3.0f, 7.5f}) == -3.0f);
    FND_TEST_TRUE(cmin(float2_t{4.0f, 4.0f}) == 4.0f);
    FND_TEST_TRUE(
        cmin(float2_t{kFloatInfinity, -kFloatInfinity}) == -kFloatInfinity);
    // A NaN component is ignored, as for the float_t min.
    FND_TEST_TRUE(cmin(float2_t{kFloatNaN, 1.0f}) == 1.0f);
    FND_TEST_TRUE(cmin(float2_t{1.0f, kFloatNaN}) == 1.0f);
}

void unittests_math_vector_float2_cmul()
{
    FND_TEST_TRUE(cmul(float2_t{7.5f, -3.0f}) == -22.5f);
    FND_TEST_TRUE(cmul(float2_t{0.0f, kFloatMaxValue}) == 0.0f);
    FND_TEST_TRUE(cmul(float2_t{kFloatMaxValue, 2.0f}) == kFloatInfinity);
    FND_TEST_TRUE(isnan(cmul(float2_t{0.0f, kFloatInfinity})));
}

void unittests_math_vector_float2_trigonometry()
{
    const float2_t v{0.5f, -1.25f};
    FND_TEST_TRUE(test_components(cos(v), cos(0.5f), cos(-1.25f)));
    FND_TEST_TRUE(test_components(sin(v), sin(0.5f), sin(-1.25f)));
    FND_TEST_TRUE(test_components(tan(v), tan(0.5f), tan(-1.25f)));
    FND_TEST_TRUE(test_components(cos(float2_t{0.0f, kFloatPi}), 1.0f, -1.0f));
}

void unittests_math_vector_float2_csum()
{
    FND_TEST_TRUE(csum(float2_t{7.5f, -3.0f}) == 4.5f);
    FND_TEST_TRUE(csum(float2_t{0.0f, 0.0f}) == 0.0f);
    FND_TEST_TRUE(
        csum(float2_t{kFloatMaxValue, kFloatMaxValue}) == kFloatInfinity);
    FND_TEST_TRUE(isnan(csum(float2_t{kFloatInfinity, -kFloatInfinity})));
}

void unittests_math_vector_float2_degrees_radians()
{
    FND_TEST_TRUE(test_components(
        degrees(float2_t{kFloatPi, -kFloatPi / 2}), 180.0f, -90.0f));
    FND_TEST_TRUE(test_components(
        radians(float2_t{180.0f, -90.0f}), kFloatPi, -kFloatPi / 2));
    FND_TEST_TRUE(test_components(
        degrees(float2_t{1.0f, -2.0f}), degrees(1.0f), degrees(-2.0f)));
    FND_TEST_TRUE(test_components(
        radians(float2_t{1.0f, -2.0f}), radians(1.0f), radians(-2.0f)));
}

void unittests_math_vector_float2_exp_log()
{
    FND_TEST_TRUE(
        test_components(exp(float2_t{0.0f, 1.0f}), exp(0.0f), exp(1.0f)));
    FND_TEST_TRUE(
        test_components(exp2(float2_t{3.0f, -1.0f}), exp2(3.0f), exp2(-1.0f)));
    FND_TEST_TRUE(
        test_components(log(float2_t{1.0f, 2.0f}), log(1.0f), log(2.0f)));
    FND_TEST_TRUE(
        test_components(log2(float2_t{8.0f, 0.5f}), log2(8.0f), log2(0.5f)));
    FND_TEST_TRUE(test_components(
        log10(float2_t{1000.0f, 0.01f}), log10(1000.0f), log10(0.01f)));
    FND_TEST_TRUE(test_components(exp2(float2_t{3.0f, -1.0f}), 8.0f, 0.5f));
    FND_TEST_TRUE(test_components(log2(float2_t{8.0f, 0.5f}), 3.0f, -1.0f));
}

void unittests_math_vector_float2_floor()
{
    FND_TEST_TRUE(test_components(floor(float2_t{2.25f, -2.75f}), 2.0f, -3.0f));
    FND_TEST_TRUE(test_components(floor(float2_t{0.5f, -4.0f}), 0.0f, -4.0f));
    FND_TEST_TRUE(
        test_components(floor(float2_t{-kFloatInfinity, kFloatInfinity}),
            -kFloatInfinity, kFloatInfinity));
    FND_TEST_TRUE(isnan(floor(float2_t{1.0f, kFloatNaN}).y));
}

void unittests_math_vector_float2_fmod()
{
    // The result has the sign of the left operand.
    FND_TEST_TRUE(test_components(
        fmod(float2_t{7.5f, -7.5f}, float2_t{2.0f, 2.0f}), 1.5f, -1.5f));
    FND_TEST_TRUE(test_components(
        fmod(float2_t{7.5f, 7.5f}, float2_t{2.0f, -4.0f}), 1.5f, 3.5f));
    // float_t on either side is used with every component.
    FND_TEST_TRUE(
        test_components(fmod(float2_t{7.5f, -5.25f}, 2.0f), 1.5f, -1.25f));
    FND_TEST_TRUE(
        test_components(fmod(7.5f, float2_t{2.0f, 4.0f}), 1.5f, 3.5f));
    // A finite x with an infinite y returns x.
    FND_TEST_TRUE(test_components(
        fmod(float2_t{1.5f, -1.5f}, kFloatInfinity), 1.5f, -1.5f));
    // Unlike operator%, fmod does not assert on a zero divisor: the result is
    // NaN.
    const float2_t zero_divisor
        = fmod(float2_t{1.0f, 2.0f}, float2_t{0.0f, 1.0f});
    FND_TEST_TRUE(isnan(zero_divisor.x));
    FND_TEST_TRUE(zero_divisor.y == 0.0f);
    FND_TEST_TRUE(isnan(fmod(kFloatInfinity, float2_t{2.0f, 2.0f}).y));
}

void unittests_math_vector_float2_fractional()
{
    FND_TEST_TRUE(
        test_components(fractional(float2_t{2.75f, 4.0f}), 0.75f, 0.0f));
    // Negative x gives the magnitude of its fractional part, in [0, 1).
    FND_TEST_TRUE(
        test_components(fractional(float2_t{-2.75f, -1e-10f}), 0.75f, 1e-10f));
    FND_TEST_TRUE(test_components(
        fractional(float2_t{-kFloatInfinity, kFloatInfinity}), 0.0f, 0.0f));
    FND_TEST_TRUE(isnan(fractional(float2_t{kFloatNaN, 1.0f}).x));
}

void unittests_math_vector_float2_lerp()
{
    const float2_t a{0.0f, 10.0f};
    const float2_t b{10.0f, 20.0f};
    FND_TEST_TRUE(test_components(lerp(a, b, 0.0f), 0.0f, 10.0f));
    FND_TEST_TRUE(test_components(lerp(a, b, 1.0f), 10.0f, 20.0f));
    FND_TEST_TRUE(test_components(lerp(a, b, 0.25f), 2.5f, 12.5f));
    // t outside [0, 1] extrapolates.
    FND_TEST_TRUE(test_components(lerp(a, b, 2.0f), 20.0f, 30.0f));
    // A float2_t t gives each component its own t.
    FND_TEST_TRUE(
        test_components(lerp(a, b, float2_t{0.25f, 0.5f}), 2.5f, 15.0f));
    FND_TEST_TRUE(
        test_components(lerp(a, b, float2_t{-1.0f, 1.0f}), -10.0f, 20.0f));
}

void unittests_math_vector_float2_max()
{
    const float2_t a{7.5f, -3.0f};
    FND_TEST_TRUE(test_components(max(a, float2_t{2.0f, 4.0f}), 7.5f, 4.0f));
    FND_TEST_TRUE(test_components(max(float2_t{2.0f, 4.0f}, a), 7.5f, 4.0f));
    FND_TEST_TRUE(test_components(
        max(float2_t{4.0f, 4.0f}, float2_t{4.0f, 4.0f}), 4.0f, 4.0f));
    FND_TEST_TRUE(test_components(
        max(float2_t{kFloatInfinity, -kFloatInfinity}, float2_t{1.0f, 1.0f}),
        kFloatInfinity, 1.0f));
    // float_t on either side is compared with every component.
    FND_TEST_TRUE(test_components(max(a, 0.0f), 7.5f, 0.0f));
    FND_TEST_TRUE(test_components(max(0.0f, a), 7.5f, 0.0f));
    FND_TEST_TRUE(test_components(max(a, 10.0f), 10.0f, 10.0f));
    FND_TEST_TRUE(test_components(max(-5.0f, a), 7.5f, -3.0f));
    // A NaN argument is ignored, as for the float_t max.
    FND_TEST_TRUE(test_components(
        max(float2_t{kFloatNaN, 1.0f}, float2_t{2.0f, kFloatNaN}), 2.0f, 1.0f));
}

void unittests_math_vector_float2_min()
{
    const float2_t a{7.5f, -3.0f};
    FND_TEST_TRUE(test_components(min(a, float2_t{2.0f, 4.0f}), 2.0f, -3.0f));
    FND_TEST_TRUE(test_components(min(float2_t{2.0f, 4.0f}, a), 2.0f, -3.0f));
    FND_TEST_TRUE(test_components(
        min(float2_t{4.0f, 4.0f}, float2_t{4.0f, 4.0f}), 4.0f, 4.0f));
    FND_TEST_TRUE(test_components(
        min(float2_t{kFloatInfinity, -kFloatInfinity}, float2_t{1.0f, 1.0f}),
        1.0f, -kFloatInfinity));
    // float_t on either side is compared with every component.
    FND_TEST_TRUE(test_components(min(a, 0.0f), 0.0f, -3.0f));
    FND_TEST_TRUE(test_components(min(0.0f, a), 0.0f, -3.0f));
    FND_TEST_TRUE(test_components(min(a, -5.0f), -5.0f, -5.0f));
    FND_TEST_TRUE(test_components(min(10.0f, a), 7.5f, -3.0f));
    // A NaN argument is ignored, as for the float_t min.
    FND_TEST_TRUE(test_components(
        min(float2_t{kFloatNaN, 1.0f}, float2_t{2.0f, kFloatNaN}), 2.0f, 1.0f));
}

void unittests_math_vector_float2_pow()
{
    FND_TEST_TRUE(
        test_components(pow(float2_t{2.0f, 9.0f}, float2_t{10.0f, 0.5f}),
            pow(2.0f, 10.0f), pow(9.0f, 0.5f)));
    FND_TEST_TRUE(test_components(
        pow(float2_t{3.0f, -4.0f}, 2.0f), pow(3.0f, 2.0f), pow(-4.0f, 2.0f)));
    FND_TEST_TRUE(
        approx_equal(pow(float2_t{2.0f, 9.0f}, float2_t{10.0f, 0.5f}).y, 3.0f));
}

void unittests_math_vector_float2_rcp_sqrt_rsqrt()
{
    FND_TEST_TRUE(test_components(rcp(float2_t{2.0f, -4.0f}), 0.5f, -0.25f));
    FND_TEST_TRUE(test_components(sqrt(float2_t{4.0f, 2.25f}), 2.0f, 1.5f));
    FND_TEST_TRUE(
        test_components(sqrt(float2_t{2.0f, 3.0f}), sqrt(2.0f), sqrt(3.0f)));
    FND_TEST_TRUE(test_components(rsqrt(float2_t{4.0f, 0.25f}), 0.5f, 2.0f));
    FND_TEST_TRUE(
        test_components(rsqrt(float2_t{2.0f, 3.0f}), rsqrt(2.0f), rsqrt(3.0f)));
}

void unittests_math_vector_float2_saturate()
{
    FND_TEST_TRUE(
        test_components(saturate(float2_t{0.25f, 0.75f}), 0.25f, 0.75f));
    FND_TEST_TRUE(test_components(saturate(float2_t{-0.5f, 1.5f}), 0.0f, 1.0f));
    FND_TEST_TRUE(test_components(saturate(float2_t{0.0f, 1.0f}), 0.0f, 1.0f));
    FND_TEST_TRUE(test_components(
        saturate(float2_t{-kFloatInfinity, kFloatInfinity}), 0.0f, 1.0f));
}

void unittests_math_vector_float2_sign()
{
    FND_TEST_TRUE(test_components(sign(float2_t{7.5f, -3.0f}), 1.0f, -1.0f));
    FND_TEST_TRUE(test_components(sign(float2_t{0.0f, -0.0f}), 0.0f, 0.0f));
    FND_TEST_TRUE(test_components(
        sign(float2_t{kFloatInfinity, -kFloatInfinity}), 1.0f, -1.0f));
    FND_TEST_TRUE(test_components(
        sign(float2_t{kFloatMinSubnormal, -kFloatMinSubnormal}), 1.0f, -1.0f));
    // NaN has no sign: 0.
    FND_TEST_TRUE(test_components(sign(float2_t{kFloatNaN, 2.0f}), 0.0f, 1.0f));
}

void unittests_math_vector_float2_smoothstep()
{
    // Each component has its own edges.
    const float2_t edge0{0.0f, 2.0f};
    const float2_t edge1{1.0f, 4.0f};
    FND_TEST_TRUE(test_components(
        smoothstep(edge0, edge1, float2_t{0.25f, 3.0f}), 0.15625f, 0.5f));
    FND_TEST_TRUE(test_components(
        smoothstep(edge0, edge1, float2_t{-1.0f, 5.0f}), 0.0f, 1.0f));
    // float_t edges apply to every component.
    FND_TEST_TRUE(test_components(
        smoothstep(0.0f, 1.0f, float2_t{0.25f, 0.75f}), 0.15625f, 0.84375f));
    FND_TEST_TRUE(test_components(
        smoothstep(0.0f, 1.0f, float2_t{-1.0f, 2.0f}), 0.0f, 1.0f));
}

void unittests_math_vector_float2_trunc()
{
    // Rounds toward zero: down for positive, up for negative.
    FND_TEST_TRUE(test_components(trunc(float2_t{2.75f, -2.75f}), 2.0f, -2.0f));
    FND_TEST_TRUE(test_components(trunc(float2_t{-0.5f, 4.0f}), 0.0f, 4.0f));
    FND_TEST_TRUE(
        test_components(trunc(float2_t{-kFloatInfinity, kFloatInfinity}),
            -kFloatInfinity, kFloatInfinity));
    FND_TEST_TRUE(isnan(trunc(float2_t{kFloatNaN, 1.0f}).x));
}

void unittests_math_vector_float2()
{
    unittests_math_vector_float2_type();
    unittests_math_vector_float2_constructors();
    unittests_math_vector_float2_subscript_operator();
    unittests_math_vector_float2_increment_operators();
    unittests_math_vector_float2_decrement_operators();
    unittests_math_vector_float2_unary_minus_operator();
    unittests_math_vector_float2_compound_assignment_operators();
    unittests_math_vector_float2_compound_assignment_matches_operators();
    unittests_math_vector_float2_equality_operators();
    unittests_math_vector_float2_relational_operators();
    unittests_math_vector_float2_multiplication_operator();
    unittests_math_vector_float2_addition_operator();
    unittests_math_vector_float2_subtraction_operator();
    unittests_math_vector_float2_modulo_operator();
    unittests_math_vector_float2_division_operator();
    unittests_math_vector_float2_abs();
    unittests_math_vector_float2_inverse_trigonometry();
    unittests_math_vector_float2_ceil();
    unittests_math_vector_float2_clamp();
    unittests_math_vector_float2_cmax();
    unittests_math_vector_float2_cmin();
    unittests_math_vector_float2_cmul();
    unittests_math_vector_float2_trigonometry();
    unittests_math_vector_float2_csum();
    unittests_math_vector_float2_degrees_radians();
    unittests_math_vector_float2_exp_log();
    unittests_math_vector_float2_floor();
    unittests_math_vector_float2_fmod();
    unittests_math_vector_float2_fractional();
    unittests_math_vector_float2_lerp();
    unittests_math_vector_float2_max();
    unittests_math_vector_float2_min();
    unittests_math_vector_float2_pow();
    unittests_math_vector_float2_rcp_sqrt_rsqrt();
    unittests_math_vector_float2_saturate();
    unittests_math_vector_float2_sign();
    unittests_math_vector_float2_smoothstep();
    unittests_math_vector_float2_trunc();
}

} // namespace fnd::unittests
