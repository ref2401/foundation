module;
#include "foundation/unittests.h"


export module unittests.math:vector_int3;
import foundation.core;
import foundation.math;

namespace fnd::unittests {

export void unittests_math_vector_int3();

// ---------------------------------------------------------------------------
// int3_t
// ---------------------------------------------------------------------------

constexpr bool_t test_components(
    const int3_t v, const int_t x, const int_t y, const int_t z)
{
    return v.x == x && v.y == y && v.z == z;
}

void unittests_math_vector_int3_type()
{
    static_assert(PodType<int3_t>);
    static_assert(sizeof(int3_t) == 3 * sizeof(int_t));
    // The ctor(int_t) is explicit.
    static_assert(!is_convertible<int_t, int3_t>());
}

void unittests_math_vector_int3_constants()
{
    FND_TEST_TRUE(test_components(int3_t::kZero, 0, 0, 0));
    FND_TEST_TRUE(test_components(int3_t::kUnitX, 1, 0, 0));
    FND_TEST_TRUE(test_components(int3_t::kUnitY, 0, 1, 0));
    FND_TEST_TRUE(test_components(int3_t::kUnitZ, 0, 0, 1));
    FND_TEST_TRUE(all(int3_t::kZero == int3_t{}));
    FND_TEST_TRUE(all(int3_t::kUnitX + int3_t::kUnitY
        + int3_t::kUnitZ == int3_t{1}));
    // The constants are usable in constant expressions.
    static_assert(int3_t::kUnitZ.z == 1);
}

void unittests_math_vector_int3_constructors()
{
    FND_TEST_TRUE(test_components(int3_t{}, 0, 0, 0));
    FND_TEST_TRUE(test_components(int3_t{5}, 5, 5, 5));
    FND_TEST_TRUE(test_components(int3_t{-5}, -5, -5, -5));
    FND_TEST_TRUE(test_components(int3_t{3, -4, 6}, 3, -4, 6));
    FND_TEST_TRUE(test_components(
        int3_t{kIntMinValue, kIntMaxValue, 0}, kIntMinValue, kIntMaxValue, 0));
}

void unittests_math_vector_int3_subscript_operator()
{
    const int3_t v{3, -4, 6};
    FND_TEST_TRUE(v[0] == 3);
    FND_TEST_TRUE(v[1] == -4);
    FND_TEST_TRUE(v[2] == 6);

    // The non-const overload returns a reference into the vector itself.
    int3_t w;
    w[2] = 9;
    FND_TEST_TRUE(test_components(w, 0, 0, 9));

    w[0] = -1;
    FND_TEST_TRUE(test_components(w, -1, 0, 9));
}

void unittests_math_vector_int3_increment_operators()
{
    int3_t v{1, -1, 0};
    FND_TEST_TRUE(test_components(++v, 2, 0, 1));
    FND_TEST_TRUE(test_components(v, 2, 0, 1));

    // Postfix returns the value before the increment.
    FND_TEST_TRUE(test_components(v++, 2, 0, 1));
    FND_TEST_TRUE(test_components(v, 3, 1, 2));

    int3_t limits{kIntMaxValue - 1, kIntMinValue, 0};
    ++limits;
    FND_TEST_TRUE(test_components(limits, kIntMaxValue, kIntMinValue + 1, 1));
}

void unittests_math_vector_int3_decrement_operators()
{
    int3_t v{1, -1, 0};
    FND_TEST_TRUE(test_components(--v, 0, -2, -1));
    FND_TEST_TRUE(test_components(v, 0, -2, -1));

    // Postfix returns the value before the decrement.
    FND_TEST_TRUE(test_components(v--, 0, -2, -1));
    FND_TEST_TRUE(test_components(v, -1, -3, -2));

    int3_t limits{kIntMinValue + 1, kIntMaxValue, 0};
    --limits;
    FND_TEST_TRUE(test_components(limits, kIntMinValue, kIntMaxValue - 1, -1));
}

void unittests_math_vector_int3_unary_minus_operator()
{
    FND_TEST_TRUE(test_components(-int3_t{7, -3, 4}, -7, 3, -4));
    FND_TEST_TRUE(test_components(-int3_t{0, 0, 0}, 0, 0, 0));
    FND_TEST_TRUE(test_components(-int3_t{kIntMaxValue, -kIntMaxValue, 0},
        -kIntMaxValue, kIntMaxValue, 0));
}

void unittests_math_vector_int3_bitwise_not_operator()
{
    FND_TEST_TRUE(test_components(~int3_t{0, -1, 5}, -1, 0, -6));
    FND_TEST_TRUE(test_components(~int3_t{kIntMaxValue, kIntMinValue, 1},
        kIntMinValue, kIntMaxValue, -2));
}

void unittests_math_vector_int3_compound_assignment_operators()
{
    int3_t v{7, -3, 2};

    // Each operator returns a reference to its left operand.
    FND_TEST_TRUE(&(v += int3_t{1, 2, 3}) == &v);
    FND_TEST_TRUE(test_components(v, 8, -1, 5));
    FND_TEST_TRUE(test_components(v += 2, 10, 1, 7));

    FND_TEST_TRUE(test_components(v -= int3_t{4, 3, 2}, 6, -2, 5));
    FND_TEST_TRUE(test_components(v -= 1, 5, -3, 4));

    FND_TEST_TRUE(test_components(v *= int3_t{2, -2, 3}, 10, 6, 12));
    FND_TEST_TRUE(test_components(v *= 3, 30, 18, 36));

    FND_TEST_TRUE(test_components(v /= int3_t{3, 2, 4}, 10, 9, 9));
    FND_TEST_TRUE(test_components(v /= 2, 5, 4, 4));

    FND_TEST_TRUE(test_components(v %= int3_t{3, 3, 3}, 2, 1, 1));
    v = int3_t{7, 9, 10};
    FND_TEST_TRUE(test_components(v %= 4, 3, 1, 2));

    v = int3_t{0b1100, 0b1010, 0b1111};
    FND_TEST_TRUE(test_components(
        v &= int3_t{0b1010, 0b0110, 0b0011}, 0b1000, 0b0010, 0b0011));
    FND_TEST_TRUE(test_components(v &= 0b1000, 0b1000, 0, 0));

    FND_TEST_TRUE(test_components(
        v |= int3_t{0b0001, 0b0010, 0b0100}, 0b1001, 0b0010, 0b0100));
    FND_TEST_TRUE(test_components(v |= 0b0100, 0b1101, 0b0110, 0b0100));

    FND_TEST_TRUE(
        test_components(v ^= int3_t{0b1101, 0b0000, 0b0100}, 0, 0b0110, 0));
    FND_TEST_TRUE(test_components(v ^= 0b0011, 0b0011, 0b0101, 0b0011));

    FND_TEST_TRUE(
        test_components(v <<= int3_t{1, 2, 3}, 0b0110, 0b10100, 0b11000));
    FND_TEST_TRUE(test_components(v <<= 1, 0b1100, 0b101000, 0b110000));

    FND_TEST_TRUE(
        test_components(v >>= int3_t{2, 3, 4}, 0b0011, 0b0101, 0b0011));
    FND_TEST_TRUE(test_components(v >>= 1, 0b0001, 0b0010, 0b0001));
}

void unittests_math_vector_int3_compound_assignment_matches_operators()
{
    // a op= b must give the same result as a op b.
    const int3_t a{7, -3, 4};
    const int3_t b{2, 5, -3};
    const int_t val{3};
    // Shift counts must be in [0, 32).
    const int3_t shift{1, 4, 2};
    const int_t shift_val{2};
    int3_t c;

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

    c = a;
    c &= b;
    FND_TEST_TRUE(all(c == (a & b)));
    c = a;
    c &= val;
    FND_TEST_TRUE(all(c == (a & val)));

    c = a;
    c |= b;
    FND_TEST_TRUE(all(c == (a | b)));
    c = a;
    c |= val;
    FND_TEST_TRUE(all(c == (a | val)));

    c = a;
    c ^= b;
    FND_TEST_TRUE(all(c == (a ^ b)));
    c = a;
    c ^= val;
    FND_TEST_TRUE(all(c == (a ^ val)));

    c = a;
    c <<= shift;
    FND_TEST_TRUE(all(c == (a << shift)));
    c = a;
    c <<= shift_val;
    FND_TEST_TRUE(all(c == (a << shift_val)));

    c = a;
    c >>= shift;
    FND_TEST_TRUE(all(c == (a >> shift)));
    c = a;
    c >>= shift_val;
    FND_TEST_TRUE(all(c == (a >> shift_val)));
}

void unittests_math_vector_int3_equality_operators()
{
    const int3_t a{7, -3, 4};
    FND_TEST_TRUE(all((a == int3_t{7, -3, 4}) == bool3_t{true, true, true}));
    FND_TEST_TRUE(all((a == int3_t{7, 5, 4}) == bool3_t{true, false, true}));
    FND_TEST_TRUE(all((a == int3_t{2, 5, 1}) == bool3_t{false, false, false}));
    FND_TEST_TRUE(all((a == 7) == bool3_t{true, false, false}));
    FND_TEST_TRUE(all((4 == a) == bool3_t{false, false, true}));

    FND_TEST_TRUE(all((a != int3_t{7, -3, 4}) == bool3_t{false, false, false}));
    FND_TEST_TRUE(all((a != int3_t{7, 5, 4}) == bool3_t{false, true, false}));
    FND_TEST_TRUE(all((a != int3_t{2, 5, 1}) == bool3_t{true, true, true}));
    FND_TEST_TRUE(all((a != 7) == bool3_t{false, true, true}));
    FND_TEST_TRUE(all((4 != a) == bool3_t{true, true, false}));
}

void unittests_math_vector_int3_relational_operators()
{
    const int3_t a{7, -3, 4};
    const int3_t b{2, 5, 4};
    const int3_t c{7, 5, -1};

    FND_TEST_TRUE(all((a < b) == bool3_t{false, true, false}));
    FND_TEST_TRUE(all((a < c) == bool3_t{false, true, false}));
    FND_TEST_TRUE(all((a < 0) == bool3_t{false, true, false}));
    FND_TEST_TRUE(all((0 < a) == bool3_t{true, false, true}));

    FND_TEST_TRUE(all((a <= b) == bool3_t{false, true, true}));
    FND_TEST_TRUE(all((a <= c) == bool3_t{true, true, false}));
    FND_TEST_TRUE(all((a <= 4) == bool3_t{false, true, true}));
    FND_TEST_TRUE(all((7 <= a) == bool3_t{true, false, false}));

    FND_TEST_TRUE(all((a > b) == bool3_t{true, false, false}));
    FND_TEST_TRUE(all((a > c) == bool3_t{false, false, true}));
    FND_TEST_TRUE(all((a > 0) == bool3_t{true, false, true}));
    FND_TEST_TRUE(all((0 > a) == bool3_t{false, true, false}));

    FND_TEST_TRUE(all((a >= b) == bool3_t{true, false, true}));
    FND_TEST_TRUE(all((a >= c) == bool3_t{true, false, true}));
    FND_TEST_TRUE(all((a >= 7) == bool3_t{true, false, false}));
    FND_TEST_TRUE(all((4 >= a) == bool3_t{false, true, true}));
}

void unittests_math_vector_int3_bitwise_and_operator()
{
    const int3_t a{0b1100, 0b1010, 0b1111};
    FND_TEST_TRUE(test_components(
        a & int3_t{0b1010, 0b0110, 0b0011}, 0b1000, 0b0010, 0b0011));
    FND_TEST_TRUE(test_components(a & 0b0110, 0b0100, 0b0010, 0b0110));
    FND_TEST_TRUE(test_components(0b0110 & a, 0b0100, 0b0010, 0b0110));
    FND_TEST_TRUE(
        test_components(int3_t{-1, kIntMinValue, 0x1FF} & 0xFF, 0xFF, 0, 0xFF));
}

void unittests_math_vector_int3_multiplication_operator()
{
    const int3_t a{7, -3, 4};
    FND_TEST_TRUE(test_components(a * int3_t{2, 5, -2}, 14, -15, -8));
    FND_TEST_TRUE(test_components(a * 2, 14, -6, 8));
    FND_TEST_TRUE(test_components(2 * a, 14, -6, 8));
    // 46340^2 is the largest square that fits in int_t.
    FND_TEST_TRUE(test_components(
        int3_t{46340, -46340, 1} * 46340, 2147395600, -2147395600, 46340));
}

void unittests_math_vector_int3_addition_operator()
{
    const int3_t a{7, -3, 4};
    FND_TEST_TRUE(test_components(a + int3_t{2, 5, -2}, 9, 2, 2));
    FND_TEST_TRUE(test_components(a + 1, 8, -2, 5));
    FND_TEST_TRUE(test_components(1 + a, 8, -2, 5));
    FND_TEST_TRUE(test_components(
        int3_t{kIntMaxValue - 1, kIntMinValue + 1, 0} + int3_t{1, -1, 0},
        kIntMaxValue, kIntMinValue, 0));
}

void unittests_math_vector_int3_subtraction_operator()
{
    const int3_t a{7, -3, 4};
    FND_TEST_TRUE(test_components(a - int3_t{2, 5, -2}, 5, -8, 6));
    FND_TEST_TRUE(test_components(a - 1, 6, -4, 3));
    FND_TEST_TRUE(test_components(1 - a, -6, 4, -3));
    FND_TEST_TRUE(test_components(
        int3_t{kIntMinValue + 1, kIntMaxValue - 1, 0} - int3_t{1, -1, 0},
        kIntMinValue, kIntMaxValue, 0));
}

void unittests_math_vector_int3_modulo_operator()
{
    // The result has the sign of the left operand.
    const int3_t a{7, -3, 4};
    FND_TEST_TRUE(test_components(a % int3_t{2, 5, -3}, 1, -3, 1));
    FND_TEST_TRUE(test_components(a % 2, 1, -1, 0));
    FND_TEST_TRUE(test_components(21 % int3_t{2, 5, -4}, 1, 1, 1));
    FND_TEST_TRUE(test_components(
        int3_t{kIntMinValue, 7, -7} % int3_t{kIntMaxValue, -2, 3}, -1, 1, -1));
}

void unittests_math_vector_int3_division_operator()
{
    // Division truncates toward zero.
    const int3_t a{7, -3, 4};
    FND_TEST_TRUE(test_components(a / int3_t{2, 5, -2}, 3, 0, -2));
    FND_TEST_TRUE(test_components(a / 2, 3, -1, 2));
    FND_TEST_TRUE(test_components(21 / int3_t{2, 5, -4}, 10, 4, -5));
    FND_TEST_TRUE(test_components(
        int3_t{kIntMinValue, kIntMaxValue, 9} / int3_t{1, -1, 3}, kIntMinValue,
        -kIntMaxValue, 3));
}

void unittests_math_vector_int3_shift_left_operator()
{
    FND_TEST_TRUE(
        test_components(int3_t{1, 3, 5} << int3_t{4, 1, 0}, 16, 6, 5));
    FND_TEST_TRUE(test_components(int3_t{1, 3, 5} << 2, 4, 12, 20));
    FND_TEST_TRUE(test_components(1 << int3_t{0, 31, 4}, 1, kIntMinValue, 16));
    FND_TEST_TRUE(test_components(int3_t{-1, -2, -3} << 1, -2, -4, -6));
}

void unittests_math_vector_int3_shift_right_operator()
{
    FND_TEST_TRUE(
        test_components(int3_t{16, 6, 5} >> int3_t{4, 1, 0}, 1, 3, 5));
    // Negative values shift in sign bits.
    FND_TEST_TRUE(test_components(int3_t{-8, 8, -1} >> 1, -4, 4, -1));
    FND_TEST_TRUE(test_components(256 >> int3_t{4, 8, 0}, 16, 1, 256));
    FND_TEST_TRUE(test_components(
        int3_t{kIntMinValue, kIntMaxValue, -1} >> 31, -1, 0, -1));
}

void unittests_math_vector_int3_bitwise_xor_operator()
{
    const int3_t a{0b1100, 0b1010, 0b1111};
    FND_TEST_TRUE(
        test_components(a ^ int3_t{0b1010, 0b0110, 0b1111}, 0b0110, 0b1100, 0));
    FND_TEST_TRUE(test_components(a ^ 0b1111, 0b0011, 0b0101, 0));
    FND_TEST_TRUE(test_components(0b1111 ^ a, 0b0011, 0b0101, 0));
    FND_TEST_TRUE(test_components(a ^ a, 0, 0, 0));
}

void unittests_math_vector_int3_bitwise_or_operator()
{
    const int3_t a{0b1100, 0b1010, 0b1111};
    FND_TEST_TRUE(test_components(
        a | int3_t{0b1010, 0b0110, 0b0000}, 0b1110, 0b1110, 0b1111));
    FND_TEST_TRUE(test_components(a | 0b0001, 0b1101, 0b1011, 0b1111));
    FND_TEST_TRUE(test_components(0b0001 | a, 0b1101, 0b1011, 0b1111));
    FND_TEST_TRUE(test_components(int3_t{0, kIntMaxValue, 1} | kIntMinValue,
        kIntMinValue, -1, kIntMinValue + 1));
}

void unittests_math_vector_int3_abs()
{
    FND_TEST_TRUE(test_components(abs(int3_t{7, -3, 0}), 7, 3, 0));
    FND_TEST_TRUE(test_components(abs(int3_t{kIntMaxValue, -kIntMaxValue, -1}),
        kIntMaxValue, kIntMaxValue, 1));
}

void unittests_math_vector_int3_clamp()
{
    const int3_t lower{-10, 0, -1};
    const int3_t upper{10, 5, 1};
    // Each component is clamped to its own bounds.
    FND_TEST_TRUE(
        test_components(clamp(int3_t{3, 3, 0}, lower, upper), 3, 3, 0));
    FND_TEST_TRUE(
        test_components(clamp(int3_t{-20, -1, -5}, lower, upper), -10, 0, -1));
    FND_TEST_TRUE(
        test_components(clamp(int3_t{20, 6, 5}, lower, upper), 10, 5, 1));
    FND_TEST_TRUE(
        test_components(clamp(int3_t{-10, 5, 1}, lower, upper), -10, 5, 1));
    FND_TEST_TRUE(
        test_components(clamp(int3_t{-20, 6, 0}, lower, upper), -10, 5, 0));
    FND_TEST_TRUE(test_components(
        clamp(int3_t{9, 9, 9}, int3_t{3, 3, 3}, int3_t{3, 3, 3}), 3, 3, 3));

    // int_t bounds apply to every component.
    FND_TEST_TRUE(test_components(clamp(int3_t{3, -3, 9}, 0, 5), 3, 0, 5));
    FND_TEST_TRUE(
        test_components(clamp(int3_t{-20, 20, 0}, -10, 10), -10, 10, 0));
    FND_TEST_TRUE(
        test_components(clamp(int3_t{-10, 10, 5}, -10, 10), -10, 10, 5));
    FND_TEST_TRUE(test_components(clamp(int3_t{9, -9, 0}, 3, 3), 3, 3, 3));

    // int3_t lower bound, int_t upper bound.
    FND_TEST_TRUE(test_components(
        clamp(int3_t{-20, -20, -20}, int3_t{-10, 0, -5}, 5), -10, 0, -5));
    FND_TEST_TRUE(test_components(
        clamp(int3_t{20, 3, 7}, int3_t{-10, 0, -5}, 5), 5, 3, 5));
    FND_TEST_TRUE(test_components(
        clamp(int3_t{-10, 5, -5}, int3_t{-10, 0, -5}, 5), -10, 5, -5));
    FND_TEST_TRUE(
        test_components(clamp(int3_t{9, -9, 0}, int3_t{3, 5, 1}, 5), 5, 5, 1));

    // int_t lower bound, int3_t upper bound.
    FND_TEST_TRUE(test_components(
        clamp(int3_t{-20, -20, -20}, 0, int3_t{10, 5, 1}), 0, 0, 0));
    FND_TEST_TRUE(test_components(
        clamp(int3_t{20, 3, 7}, 0, int3_t{10, 5, 1}), 10, 3, 1));
    FND_TEST_TRUE(
        test_components(clamp(int3_t{0, 5, 1}, 0, int3_t{10, 5, 1}), 0, 5, 1));
    FND_TEST_TRUE(
        test_components(clamp(int3_t{9, -9, 0}, 3, int3_t{3, 7, 4}), 3, 3, 3));
}

void unittests_math_vector_int3_cmax()
{
    // The maximum in each position.
    FND_TEST_TRUE(cmax(int3_t{7, -3, 4}) == 7);
    FND_TEST_TRUE(cmax(int3_t{-3, 7, 4}) == 7);
    FND_TEST_TRUE(cmax(int3_t{4, -3, 7}) == 7);
    FND_TEST_TRUE(cmax(int3_t{4, 4, 4}) == 4);
    FND_TEST_TRUE(cmax(int3_t{kIntMinValue, 0, kIntMaxValue}) == kIntMaxValue);
}

void unittests_math_vector_int3_cmin()
{
    // The minimum in each position.
    FND_TEST_TRUE(cmin(int3_t{-3, 7, 4}) == -3);
    FND_TEST_TRUE(cmin(int3_t{7, -3, 4}) == -3);
    FND_TEST_TRUE(cmin(int3_t{7, 4, -3}) == -3);
    FND_TEST_TRUE(cmin(int3_t{4, 4, 4}) == 4);
    FND_TEST_TRUE(cmin(int3_t{kIntMaxValue, 0, kIntMinValue}) == kIntMinValue);
}

void unittests_math_vector_int3_cmul()
{
    FND_TEST_TRUE(cmul(int3_t{7, -3, 2}) == -42);
    FND_TEST_TRUE(cmul(int3_t{0, kIntMaxValue, kIntMaxValue}) == 0);
    FND_TEST_TRUE(cmul(int3_t{-7, -3, -2}) == -42);
    // 1290^3 is the largest cube that fits in int_t.
    FND_TEST_TRUE(cmul(int3_t{1290, 1290, 1290}) == 2146689000);
    FND_TEST_TRUE(cmul(int3_t{kIntMinValue, 1, 1}) == kIntMinValue);
}

void unittests_math_vector_int3_csum()
{
    FND_TEST_TRUE(csum(int3_t{7, -3, 4}) == 8);
    FND_TEST_TRUE(csum(int3_t{0, 0, 0}) == 0);
    FND_TEST_TRUE(csum(int3_t{-7, -3, -1}) == -11);
    FND_TEST_TRUE(csum(int3_t{kIntMaxValue - 2, 1, 1}) == kIntMaxValue);
    FND_TEST_TRUE(csum(int3_t{kIntMinValue, kIntMaxValue, 1}) == 0);
}

void unittests_math_vector_int3_max()
{
    const int3_t a{7, -3, 4};
    FND_TEST_TRUE(test_components(max(a, int3_t{2, 5, 4}), 7, 5, 4));
    FND_TEST_TRUE(test_components(max(int3_t{2, 5, 4}, a), 7, 5, 4));
    FND_TEST_TRUE(
        test_components(max(int3_t{4, 4, 4}, int3_t{4, 4, 4}), 4, 4, 4));
    FND_TEST_TRUE(test_components(max(int3_t{kIntMinValue, kIntMaxValue, 0},
                                      int3_t{kIntMaxValue, kIntMinValue, 0}),
        kIntMaxValue, kIntMaxValue, 0));
    // int_t on either side is compared with every component.
    FND_TEST_TRUE(test_components(max(a, 0), 7, 0, 4));
    FND_TEST_TRUE(test_components(max(0, a), 7, 0, 4));
    FND_TEST_TRUE(test_components(max(a, 10), 10, 10, 10));
    FND_TEST_TRUE(test_components(max(-5, a), 7, -3, 4));
}

void unittests_math_vector_int3_min()
{
    const int3_t a{7, -3, 4};
    FND_TEST_TRUE(test_components(min(a, int3_t{2, 5, 4}), 2, -3, 4));
    FND_TEST_TRUE(test_components(min(int3_t{2, 5, 4}, a), 2, -3, 4));
    FND_TEST_TRUE(
        test_components(min(int3_t{4, 4, 4}, int3_t{4, 4, 4}), 4, 4, 4));
    FND_TEST_TRUE(test_components(min(int3_t{kIntMinValue, kIntMaxValue, 0},
                                      int3_t{kIntMaxValue, kIntMinValue, 0}),
        kIntMinValue, kIntMinValue, 0));
    // int_t on either side is compared with every component.
    FND_TEST_TRUE(test_components(min(a, 0), 0, -3, 0));
    FND_TEST_TRUE(test_components(min(0, a), 0, -3, 0));
    FND_TEST_TRUE(test_components(min(a, -5), -5, -5, -5));
    FND_TEST_TRUE(test_components(min(10, a), 7, -3, 4));
}

void unittests_math_vector_int3_sign()
{
    FND_TEST_TRUE(test_components(sign(int3_t{7, -3, 0}), 1, -1, 0));
    FND_TEST_TRUE(test_components(sign(int3_t{0, 5, -5}), 0, 1, -1));
    FND_TEST_TRUE(
        test_components(sign(int3_t{kIntMinValue, kIntMaxValue, 0}), -1, 1, 0));
}

void unittests_math_vector_int3()
{
    unittests_math_vector_int3_type();
    unittests_math_vector_int3_constants();
    unittests_math_vector_int3_constructors();
    unittests_math_vector_int3_subscript_operator();
    unittests_math_vector_int3_increment_operators();
    unittests_math_vector_int3_decrement_operators();
    unittests_math_vector_int3_unary_minus_operator();
    unittests_math_vector_int3_bitwise_not_operator();
    unittests_math_vector_int3_compound_assignment_operators();
    unittests_math_vector_int3_compound_assignment_matches_operators();
    unittests_math_vector_int3_equality_operators();
    unittests_math_vector_int3_relational_operators();
    unittests_math_vector_int3_bitwise_and_operator();
    unittests_math_vector_int3_multiplication_operator();
    unittests_math_vector_int3_addition_operator();
    unittests_math_vector_int3_subtraction_operator();
    unittests_math_vector_int3_modulo_operator();
    unittests_math_vector_int3_division_operator();
    unittests_math_vector_int3_shift_left_operator();
    unittests_math_vector_int3_shift_right_operator();
    unittests_math_vector_int3_bitwise_xor_operator();
    unittests_math_vector_int3_bitwise_or_operator();
    unittests_math_vector_int3_abs();
    unittests_math_vector_int3_clamp();
    unittests_math_vector_int3_cmax();
    unittests_math_vector_int3_cmin();
    unittests_math_vector_int3_cmul();
    unittests_math_vector_int3_csum();
    unittests_math_vector_int3_max();
    unittests_math_vector_int3_min();
    unittests_math_vector_int3_sign();
}

} // namespace fnd::unittests
