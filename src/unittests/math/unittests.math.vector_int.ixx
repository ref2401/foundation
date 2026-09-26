module;
#include "foundation/unittests.h"


export module unittests.math:vector_int;
import foundation.core;
import foundation.math;

namespace fnd::unittests {

export void unittests_math_vector_int();

// ---------------------------------------------------------------------------
// int2_t
// ---------------------------------------------------------------------------

constexpr bool_t test_components(const int2_t v, const int_t x, const int_t y)
{
    return v.x == x && v.y == y;
}

void unittests_math_vector_int2_type()
{
    static_assert(PodType<int2_t>);
    static_assert(sizeof(int2_t) == 2 * sizeof(int_t));
    // The ctor(int_t) and ctor(bool2_t) are explicit.
    static_assert(!is_convertible<int_t, int2_t>());
    static_assert(!is_convertible<bool2_t, int2_t>());
}

void unittests_math_vector_int2_constructors()
{
    FND_TEST_TRUE(test_components(int2_t{}, 0, 0));
    FND_TEST_TRUE(test_components(int2_t{5}, 5, 5));
    FND_TEST_TRUE(test_components(int2_t{-5}, -5, -5));
    FND_TEST_TRUE(test_components(int2_t{3, -4}, 3, -4));
    FND_TEST_TRUE(test_components(int2_t{kIntMinValue, kIntMaxValue}, kIntMinValue, kIntMaxValue));
    // From a bool2_t: true is 1, false is 0.
    FND_TEST_TRUE(test_components(int2_t{bool2_t{true, false}}, 1, 0));
    FND_TEST_TRUE(test_components(int2_t{bool2_t{false, true}}, 0, 1));
}

void unittests_math_vector_int2_subscript_operator()
{
    const int2_t v{3, -4};
    FND_TEST_TRUE(v[0] == 3);
    FND_TEST_TRUE(v[1] == -4);

    // The non-const overload returns a reference into the vector itself.
    int2_t w;
    w[1] = 9;
    FND_TEST_TRUE(test_components(w, 0, 9));

    w[0] = -1;
    FND_TEST_TRUE(test_components(w, -1, 9));
}

void unittests_math_vector_int2_increment_operators()
{
    int2_t v{1, -1};
    FND_TEST_TRUE(test_components(++v, 2, 0));
    FND_TEST_TRUE(test_components(v, 2, 0));

    // Postfix returns the value before the increment.
    FND_TEST_TRUE(test_components(v++, 2, 0));
    FND_TEST_TRUE(test_components(v, 3, 1));

    int2_t limits{kIntMaxValue - 1, kIntMinValue};
    ++limits;
    FND_TEST_TRUE(test_components(limits, kIntMaxValue, kIntMinValue + 1));
}

void unittests_math_vector_int2_decrement_operators()
{
    int2_t v{1, -1};
    FND_TEST_TRUE(test_components(--v, 0, -2));
    FND_TEST_TRUE(test_components(v, 0, -2));

    // Postfix returns the value before the decrement.
    FND_TEST_TRUE(test_components(v--, 0, -2));
    FND_TEST_TRUE(test_components(v, -1, -3));

    int2_t limits{kIntMinValue + 1, kIntMaxValue};
    --limits;
    FND_TEST_TRUE(test_components(limits, kIntMinValue, kIntMaxValue - 1));
}

void unittests_math_vector_int2_unary_minus_operator()
{
    FND_TEST_TRUE(test_components(-int2_t{7, -3}, -7, 3));
    FND_TEST_TRUE(test_components(-int2_t{0, 0}, 0, 0));
    FND_TEST_TRUE(test_components(-int2_t{kIntMaxValue, -kIntMaxValue}, -kIntMaxValue, kIntMaxValue));
}

void unittests_math_vector_int2_equality_operators()
{
    const int2_t a{7, -3};
    FND_TEST_TRUE(all((a == int2_t{7, -3}) == bool2_t{true, true}));
    FND_TEST_TRUE(all((a == int2_t{7, 5}) == bool2_t{true, false}));
    FND_TEST_TRUE(all((a == int2_t{2, 5}) == bool2_t{false, false}));
    FND_TEST_TRUE(all((a == 7) == bool2_t{true, false}));
    FND_TEST_TRUE(all((-3 == a) == bool2_t{false, true}));

    FND_TEST_TRUE(all((a != int2_t{7, -3}) == bool2_t{false, false}));
    FND_TEST_TRUE(all((a != int2_t{7, 5}) == bool2_t{false, true}));
    FND_TEST_TRUE(all((a != int2_t{2, 5}) == bool2_t{true, true}));
    FND_TEST_TRUE(all((a != 7) == bool2_t{false, true}));
    FND_TEST_TRUE(all((-3 != a) == bool2_t{true, false}));
}

void unittests_math_vector_int2_relational_operators()
{
    const int2_t a{7, -3};
    const int2_t b{2, 5};
    const int2_t c{7, 5};

    FND_TEST_TRUE(all((a < b) == bool2_t{false, true}));
    FND_TEST_TRUE(all((a < c) == bool2_t{false, true}));
    FND_TEST_TRUE(all((a < 0) == bool2_t{false, true}));
    FND_TEST_TRUE(all((0 < a) == bool2_t{true, false}));

    FND_TEST_TRUE(all((a <= b) == bool2_t{false, true}));
    FND_TEST_TRUE(all((a <= c) == bool2_t{true, true}));
    FND_TEST_TRUE(all((a <= -3) == bool2_t{false, true}));
    FND_TEST_TRUE(all((7 <= a) == bool2_t{true, false}));

    FND_TEST_TRUE(all((a > b) == bool2_t{true, false}));
    FND_TEST_TRUE(all((a > c) == bool2_t{false, false}));
    FND_TEST_TRUE(all((a > 0) == bool2_t{true, false}));
    FND_TEST_TRUE(all((0 > a) == bool2_t{false, true}));

    FND_TEST_TRUE(all((a >= b) == bool2_t{true, false}));
    FND_TEST_TRUE(all((a >= c) == bool2_t{true, false}));
    FND_TEST_TRUE(all((a >= 7) == bool2_t{true, false}));
    FND_TEST_TRUE(all((7 >= a) == bool2_t{true, true}));
}

void unittests_math_vector_int2_addition_operator()
{
    const int2_t a{7, -3};
    FND_TEST_TRUE(test_components(a + int2_t{2, 5}, 9, 2));
    FND_TEST_TRUE(test_components(a + 1, 8, -2));
    FND_TEST_TRUE(test_components(1 + a, 8, -2));
    FND_TEST_TRUE(test_components(
        int2_t{kIntMaxValue - 1, kIntMinValue + 1} + int2_t{1, -1}, kIntMaxValue, kIntMinValue));
}

void unittests_math_vector_int2_subtraction_operator()
{
    const int2_t a{7, -3};
    FND_TEST_TRUE(test_components(a - int2_t{2, 5}, 5, -8));
    FND_TEST_TRUE(test_components(a - 1, 6, -4));
    FND_TEST_TRUE(test_components(1 - a, -6, 4));
    FND_TEST_TRUE(test_components(
        int2_t{kIntMinValue + 1, kIntMaxValue - 1} - int2_t{1, -1}, kIntMinValue, kIntMaxValue));
}

void unittests_math_vector_int2_multiplication_operator()
{
    const int2_t a{7, -3};
    FND_TEST_TRUE(test_components(a * int2_t{2, 5}, 14, -15));
    FND_TEST_TRUE(test_components(a * 2, 14, -6));
    FND_TEST_TRUE(test_components(2 * a, 14, -6));
    // 46340^2 is the largest square that fits in int_t.
    FND_TEST_TRUE(test_components(
        int2_t{46340, -46340} * 46340, 2147395600, -2147395600));
}

void unittests_math_vector_int2_division_operator()
{
    // Division truncates toward zero.
    const int2_t a{7, -3};
    FND_TEST_TRUE(test_components(a / int2_t{2, 5}, 3, 0));
    FND_TEST_TRUE(test_components(a / 2, 3, -1));
    FND_TEST_TRUE(test_components(21 / int2_t{2, 5}, 10, 4));
    FND_TEST_TRUE(test_components(int2_t{kIntMinValue, kIntMaxValue} / int2_t{1, -1},
        kIntMinValue, -kIntMaxValue));
}

void unittests_math_vector_int2_modulo_operator()
{
    // The result has the sign of the left operand.
    const int2_t a{7, -3};
    FND_TEST_TRUE(test_components(a % int2_t{2, 5}, 1, -3));
    FND_TEST_TRUE(test_components(a % 2, 1, -1));
    FND_TEST_TRUE(test_components(21 % int2_t{2, 5}, 1, 1));
    FND_TEST_TRUE(test_components(int2_t{kIntMinValue, 7} % int2_t{kIntMaxValue, -2}, -1, 1));
}

void unittests_math_vector_int2_bitwise_not_operator()
{
    FND_TEST_TRUE(test_components(~int2_t{0, -1}, -1, 0));
    FND_TEST_TRUE(test_components(~int2_t{5, kIntMaxValue}, -6, kIntMinValue));
}

void unittests_math_vector_int2_bitwise_and_operator()
{
    const int2_t a{0b1100, 0b1010};
    FND_TEST_TRUE(test_components(a & int2_t{0b1010, 0b0110}, 0b1000, 0b0010));
    FND_TEST_TRUE(test_components(a & 0b0110, 0b0100, 0b0010));
    FND_TEST_TRUE(test_components(0b0110 & a, 0b0100, 0b0010));
    FND_TEST_TRUE(test_components(int2_t{-1, kIntMinValue} & 0xFF, 0xFF, 0));
}

void unittests_math_vector_int2_bitwise_or_operator()
{
    const int2_t a{0b1100, 0b1010};
    FND_TEST_TRUE(test_components(a | int2_t{0b1010, 0b0110}, 0b1110, 0b1110));
    FND_TEST_TRUE(test_components(a | 0b0001, 0b1101, 0b1011));
    FND_TEST_TRUE(test_components(0b0001 | a, 0b1101, 0b1011));
    FND_TEST_TRUE(test_components(int2_t{0, kIntMaxValue} | kIntMinValue, kIntMinValue, -1));
}

void unittests_math_vector_int2_bitwise_xor_operator()
{
    const int2_t a{0b1100, 0b1010};
    FND_TEST_TRUE(test_components(a ^ int2_t{0b1010, 0b0110}, 0b0110, 0b1100));
    FND_TEST_TRUE(test_components(a ^ 0b1111, 0b0011, 0b0101));
    FND_TEST_TRUE(test_components(0b1111 ^ a, 0b0011, 0b0101));
    FND_TEST_TRUE(test_components(a ^ a, 0, 0));
}

void unittests_math_vector_int2_shift_left_operator()
{
    FND_TEST_TRUE(test_components(int2_t{1, 3} << int2_t{4, 1}, 16, 6));
    FND_TEST_TRUE(test_components(int2_t{1, 3} << 2, 4, 12));
    FND_TEST_TRUE(test_components(1 << int2_t{0, 31}, 1, kIntMinValue));
    FND_TEST_TRUE(test_components(int2_t{-1, -2} << 1, -2, -4));
}

void unittests_math_vector_int2_shift_right_operator()
{
    FND_TEST_TRUE(test_components(int2_t{16, 6} >> int2_t{4, 1}, 1, 3));
    // Negative values shift in sign bits.
    FND_TEST_TRUE(test_components(int2_t{-8, 8} >> 1, -4, 4));
    FND_TEST_TRUE(test_components(256 >> int2_t{4, 8}, 16, 1));
    FND_TEST_TRUE(test_components(int2_t{kIntMinValue, kIntMaxValue} >> 31, -1, 0));
}

void unittests_math_vector_int2_compound_assignment_operators()
{
    int2_t v{7, -3};

    // Each operator returns a reference to its left operand.
    FND_TEST_TRUE(&(v += int2_t{1, 2}) == &v);
    FND_TEST_TRUE(test_components(v, 8, -1));
    FND_TEST_TRUE(test_components(v += 2, 10, 1));

    FND_TEST_TRUE(test_components(v -= int2_t{4, 3}, 6, -2));
    FND_TEST_TRUE(test_components(v -= 1, 5, -3));

    FND_TEST_TRUE(test_components(v *= int2_t{2, -2}, 10, 6));
    FND_TEST_TRUE(test_components(v *= 3, 30, 18));

    FND_TEST_TRUE(test_components(v /= int2_t{3, 2}, 10, 9));
    FND_TEST_TRUE(test_components(v /= 2, 5, 4));

    FND_TEST_TRUE(test_components(v %= int2_t{3, 3}, 2, 1));
    v = int2_t{7, 9};
    FND_TEST_TRUE(test_components(v %= 4, 3, 1));

    v = int2_t{0b1100, 0b1010};
    FND_TEST_TRUE(test_components(v &= int2_t{0b1010, 0b0110}, 0b1000, 0b0010));
    FND_TEST_TRUE(test_components(v &= 0b1000, 0b1000, 0));

    FND_TEST_TRUE(test_components(v |= int2_t{0b0001, 0b0010}, 0b1001, 0b0010));
    FND_TEST_TRUE(test_components(v |= 0b0100, 0b1101, 0b0110));

    FND_TEST_TRUE(test_components(v ^= int2_t{0b1101, 0b0000}, 0, 0b0110));
    FND_TEST_TRUE(test_components(v ^= 0b0011, 0b0011, 0b0101));

    FND_TEST_TRUE(test_components(v <<= int2_t{1, 2}, 0b0110, 0b10100));
    FND_TEST_TRUE(test_components(v <<= 1, 0b1100, 0b101000));

    FND_TEST_TRUE(test_components(v >>= int2_t{2, 3}, 0b0011, 0b0101));
    FND_TEST_TRUE(test_components(v >>= 1, 0b0001, 0b0010));
}

void unittests_math_vector_int2_abs()
{
    FND_TEST_TRUE(test_components(abs(int2_t{7, -3}), 7, 3));
    FND_TEST_TRUE(test_components(abs(int2_t{0, -0}), 0, 0));
    FND_TEST_TRUE(test_components(abs(int2_t{kIntMaxValue, -kIntMaxValue}), kIntMaxValue, kIntMaxValue));
}

void unittests_math_vector_int2_min()
{
    FND_TEST_TRUE(test_components(min(int2_t{7, -3}, int2_t{2, 5}), 2, -3));
    FND_TEST_TRUE(test_components(min(int2_t{2, 5}, int2_t{7, -3}), 2, -3));
    FND_TEST_TRUE(test_components(min(int2_t{4, 4}, int2_t{4, 4}), 4, 4));
    FND_TEST_TRUE(test_components(
        min(int2_t{kIntMinValue, kIntMaxValue}, int2_t{kIntMaxValue, kIntMinValue}),
        kIntMinValue, kIntMinValue));
    // int_t on either side is compared with every component.
    FND_TEST_TRUE(test_components(min(int2_t{7, -3}, 0), 0, -3));
    FND_TEST_TRUE(test_components(min(0, int2_t{7, -3}), 0, -3));
    FND_TEST_TRUE(test_components(min(int2_t{7, -3}, -5), -5, -5));
    FND_TEST_TRUE(test_components(min(10, int2_t{7, -3}), 7, -3));
}

void unittests_math_vector_int2_max()
{
    FND_TEST_TRUE(test_components(max(int2_t{7, -3}, int2_t{2, 5}), 7, 5));
    FND_TEST_TRUE(test_components(max(int2_t{2, 5}, int2_t{7, -3}), 7, 5));
    FND_TEST_TRUE(test_components(max(int2_t{4, 4}, int2_t{4, 4}), 4, 4));
    FND_TEST_TRUE(test_components(
        max(int2_t{kIntMinValue, kIntMaxValue}, int2_t{kIntMaxValue, kIntMinValue}),
        kIntMaxValue, kIntMaxValue));
    // int_t on either side is compared with every component.
    FND_TEST_TRUE(test_components(max(int2_t{7, -3}, 0), 7, 0));
    FND_TEST_TRUE(test_components(max(0, int2_t{7, -3}), 7, 0));
    FND_TEST_TRUE(test_components(max(int2_t{7, -3}, 10), 10, 10));
    FND_TEST_TRUE(test_components(max(-5, int2_t{7, -3}), 7, -3));
}

void unittests_math_vector_int2_clamp()
{
    const int2_t lower{-10, 0};
    const int2_t upper{10, 5};
    // Each component is clamped to its own bounds.
    FND_TEST_TRUE(test_components(clamp(int2_t{3, 3}, lower, upper), 3, 3));
    FND_TEST_TRUE(test_components(clamp(int2_t{-20, -1}, lower, upper), -10, 0));
    FND_TEST_TRUE(test_components(clamp(int2_t{20, 6}, lower, upper), 10, 5));
    FND_TEST_TRUE(test_components(clamp(int2_t{-10, 5}, lower, upper), -10, 5));
    FND_TEST_TRUE(test_components(clamp(int2_t{-20, 6}, lower, upper), -10, 5));
    FND_TEST_TRUE(test_components(clamp(int2_t{9, 9}, int2_t{3, 3}, int2_t{3, 3}), 3, 3));

    // int_t bounds apply to every component.
    FND_TEST_TRUE(test_components(clamp(int2_t{3, -3}, 0, 5), 3, 0));
    FND_TEST_TRUE(test_components(clamp(int2_t{-20, 20}, -10, 10), -10, 10));
    FND_TEST_TRUE(test_components(clamp(int2_t{-10, 10}, -10, 10), -10, 10));
    FND_TEST_TRUE(test_components(clamp(int2_t{9, -9}, 3, 3), 3, 3));

    // int2_t lower bound, int_t upper bound.
    FND_TEST_TRUE(test_components(clamp(int2_t{-20, -20}, int2_t{-10, 0}, 5), -10, 0));
    FND_TEST_TRUE(test_components(clamp(int2_t{20, 3}, int2_t{-10, 0}, 5), 5, 3));
    FND_TEST_TRUE(test_components(clamp(int2_t{-10, 5}, int2_t{-10, 0}, 5), -10, 5));
    FND_TEST_TRUE(test_components(clamp(int2_t{9, -9}, int2_t{3, 5}, 5), 5, 5));

    // int_t lower bound, int2_t upper bound.
    FND_TEST_TRUE(test_components(clamp(int2_t{-20, -20}, 0, int2_t{10, 5}), 0, 0));
    FND_TEST_TRUE(test_components(clamp(int2_t{20, 3}, 0, int2_t{10, 5}), 10, 3));
    FND_TEST_TRUE(test_components(clamp(int2_t{0, 5}, 0, int2_t{10, 5}), 0, 5));
    FND_TEST_TRUE(test_components(clamp(int2_t{9, -9}, 3, int2_t{3, 7}), 3, 3));
}

void unittests_math_vector_int2_sign()
{
    FND_TEST_TRUE(test_components(sign(int2_t{7, -3}), 1, -1));
    FND_TEST_TRUE(test_components(sign(int2_t{0, 5}), 0, 1));
    FND_TEST_TRUE(test_components(sign(int2_t{kIntMinValue, kIntMaxValue}), -1, 1));
}

void unittests_math_vector_int2_cmin()
{
    FND_TEST_TRUE(cmin(int2_t{7, -3}) == -3);
    FND_TEST_TRUE(cmin(int2_t{-3, 7}) == -3);
    FND_TEST_TRUE(cmin(int2_t{4, 4}) == 4);
    FND_TEST_TRUE(cmin(int2_t{kIntMaxValue, kIntMinValue}) == kIntMinValue);
}

void unittests_math_vector_int2_cmax()
{
    FND_TEST_TRUE(cmax(int2_t{7, -3}) == 7);
    FND_TEST_TRUE(cmax(int2_t{-3, 7}) == 7);
    FND_TEST_TRUE(cmax(int2_t{4, 4}) == 4);
    FND_TEST_TRUE(cmax(int2_t{kIntMinValue, kIntMaxValue}) == kIntMaxValue);
}

void unittests_math_vector_int2_csum()
{
    FND_TEST_TRUE(csum(int2_t{7, -3}) == 4);
    FND_TEST_TRUE(csum(int2_t{0, 0}) == 0);
    FND_TEST_TRUE(csum(int2_t{-7, -3}) == -10);
    FND_TEST_TRUE(csum(int2_t{kIntMaxValue - 1, 1}) == kIntMaxValue);
    FND_TEST_TRUE(csum(int2_t{kIntMinValue, kIntMaxValue}) == -1);
}

void unittests_math_vector_int2_cmul()
{
    FND_TEST_TRUE(cmul(int2_t{7, -3}) == -21);
    FND_TEST_TRUE(cmul(int2_t{0, kIntMaxValue}) == 0);
    FND_TEST_TRUE(cmul(int2_t{-7, -3}) == 21);
    // 46340^2 is the largest square that fits in int_t.
    FND_TEST_TRUE(cmul(int2_t{46340, 46340}) == 2147395600);
    FND_TEST_TRUE(cmul(int2_t{kIntMinValue, 1}) == kIntMinValue);
}

void unittests_math_vector_int()
{
    unittests_math_vector_int2_type();
    unittests_math_vector_int2_constructors();
    unittests_math_vector_int2_subscript_operator();
    unittests_math_vector_int2_increment_operators();
    unittests_math_vector_int2_decrement_operators();
    unittests_math_vector_int2_unary_minus_operator();
    unittests_math_vector_int2_equality_operators();
    unittests_math_vector_int2_relational_operators();
    unittests_math_vector_int2_addition_operator();
    unittests_math_vector_int2_subtraction_operator();
    unittests_math_vector_int2_multiplication_operator();
    unittests_math_vector_int2_division_operator();
    unittests_math_vector_int2_modulo_operator();
    unittests_math_vector_int2_bitwise_not_operator();
    unittests_math_vector_int2_bitwise_and_operator();
    unittests_math_vector_int2_bitwise_or_operator();
    unittests_math_vector_int2_bitwise_xor_operator();
    unittests_math_vector_int2_shift_left_operator();
    unittests_math_vector_int2_shift_right_operator();
    unittests_math_vector_int2_compound_assignment_operators();
    unittests_math_vector_int2_abs();
    unittests_math_vector_int2_min();
    unittests_math_vector_int2_max();
    unittests_math_vector_int2_clamp();
    unittests_math_vector_int2_sign();
    unittests_math_vector_int2_cmin();
    unittests_math_vector_int2_cmax();
    unittests_math_vector_int2_csum();
    unittests_math_vector_int2_cmul();
}

} // namespace fnd::unittests
