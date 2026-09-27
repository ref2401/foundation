module;
#include "foundation/unittests.h"


export module unittests.math:vector_int4;
import foundation.core;
import foundation.math;

namespace fnd::unittests {

export void unittests_math_vector_int4();

// ---------------------------------------------------------------------------
// int4_t
// ---------------------------------------------------------------------------

constexpr bool_t test_components(
    const int4_t v, const int_t x, const int_t y, const int_t z, const int_t w)
{
    return v.x == x && v.y == y && v.z == z && v.w == w;
}

void unittests_math_vector_int4_type()
{
    static_assert(PodType<int4_t>);
    static_assert(sizeof(int4_t) == 4 * sizeof(int_t));
    // The ctor(int_t), ctor(bool2_t, z, w), ctor(bool4_t), ctor(int2_t, z, w) and
    // ctor(int3_t, w) are explicit.
    static_assert(!is_convertible<int_t, int4_t>());
    static_assert(!is_convertible<bool2_t, int4_t>());
    static_assert(!is_convertible<bool4_t, int4_t>());
    static_assert(!is_convertible<int2_t, int4_t>());
    static_assert(!is_convertible<int3_t, int4_t>());
}

void unittests_math_vector_int4_constructors()
{
    FND_TEST_TRUE(test_components(int4_t{}, 0, 0, 0, 0));
    FND_TEST_TRUE(test_components(int4_t{5}, 5, 5, 5, 5));
    FND_TEST_TRUE(test_components(int4_t{-5}, -5, -5, -5, -5));
    FND_TEST_TRUE(test_components(int4_t{3, -4, 6, -8}, 3, -4, 6, -8));
    FND_TEST_TRUE(test_components(
        int4_t{kIntMinValue, kIntMaxValue, 0, 1}, kIntMinValue, kIntMaxValue, 0, 1));
    // From a bool2_t: true is 1, false is 0; z and w are 0 unless given.
    FND_TEST_TRUE(test_components(int4_t{bool2_t{true, false}}, 1, 0, 0, 0));
    FND_TEST_TRUE(test_components(int4_t{bool2_t{false, true}, 6}, 0, 1, 6, 0));
    FND_TEST_TRUE(test_components(int4_t{bool2_t{true, true}, 6, -8}, 1, 1, 6, -8));
    // From a bool4_t: true is 1, false is 0.
    FND_TEST_TRUE(test_components(int4_t{bool4_t{true, false, true, false}}, 1, 0, 1, 0));
    FND_TEST_TRUE(test_components(int4_t{bool4_t{false, true, false, true}}, 0, 1, 0, 1));
    // From an int2_t: z and w are 0 unless given.
    FND_TEST_TRUE(test_components(int4_t{int2_t{3, -4}}, 3, -4, 0, 0));
    FND_TEST_TRUE(test_components(int4_t{int2_t{3, -4}, 6}, 3, -4, 6, 0));
    FND_TEST_TRUE(test_components(int4_t{int2_t{3, -4}, 6, -8}, 3, -4, 6, -8));
    // From an int3_t: w is 0 unless given.
    FND_TEST_TRUE(test_components(int4_t{int3_t{3, -4, 6}}, 3, -4, 6, 0));
    FND_TEST_TRUE(test_components(int4_t{int3_t{3, -4, 6}, -8}, 3, -4, 6, -8));
}

void unittests_math_vector_int4_subscript_operator()
{
    const int4_t v{3, -4, 6, -8};
    FND_TEST_TRUE(v[0] == 3);
    FND_TEST_TRUE(v[1] == -4);
    FND_TEST_TRUE(v[2] == 6);
    FND_TEST_TRUE(v[3] == -8);

    // The non-const overload returns a reference into the vector itself.
    int4_t w;
    w[3] = 9;
    FND_TEST_TRUE(test_components(w, 0, 0, 0, 9));

    w[0] = -1;
    FND_TEST_TRUE(test_components(w, -1, 0, 0, 9));
}

void unittests_math_vector_int4_increment_operators()
{
    int4_t v{1, -1, 0, 5};
    FND_TEST_TRUE(test_components(++v, 2, 0, 1, 6));
    FND_TEST_TRUE(test_components(v, 2, 0, 1, 6));

    // Postfix returns the value before the increment.
    FND_TEST_TRUE(test_components(v++, 2, 0, 1, 6));
    FND_TEST_TRUE(test_components(v, 3, 1, 2, 7));

    int4_t limits{kIntMaxValue - 1, kIntMinValue, 0, -1};
    ++limits;
    FND_TEST_TRUE(test_components(limits, kIntMaxValue, kIntMinValue + 1, 1, 0));
}

void unittests_math_vector_int4_decrement_operators()
{
    int4_t v{1, -1, 0, 5};
    FND_TEST_TRUE(test_components(--v, 0, -2, -1, 4));
    FND_TEST_TRUE(test_components(v, 0, -2, -1, 4));

    // Postfix returns the value before the decrement.
    FND_TEST_TRUE(test_components(v--, 0, -2, -1, 4));
    FND_TEST_TRUE(test_components(v, -1, -3, -2, 3));

    int4_t limits{kIntMinValue + 1, kIntMaxValue, 0, 1};
    --limits;
    FND_TEST_TRUE(test_components(limits, kIntMinValue, kIntMaxValue - 1, -1, 0));
}

void unittests_math_vector_int4_unary_minus_operator()
{
    FND_TEST_TRUE(test_components(-int4_t{7, -3, 4, -6}, -7, 3, -4, 6));
    FND_TEST_TRUE(test_components(-int4_t{0, 0, 0, 0}, 0, 0, 0, 0));
    FND_TEST_TRUE(test_components(
        -int4_t{kIntMaxValue, -kIntMaxValue, 0, 1}, -kIntMaxValue, kIntMaxValue, 0, -1));
}

void unittests_math_vector_int4_equality_operators()
{
    const int4_t a{7, -3, 4, -6};
    FND_TEST_TRUE(all((a == int4_t{7, -3, 4, -6}) == bool4_t{true, true, true, true}));
    FND_TEST_TRUE(all((a == int4_t{7, 5, 4, 6}) == bool4_t{true, false, true, false}));
    FND_TEST_TRUE(all((a == int4_t{2, 5, 1, 0}) == bool4_t{false, false, false, false}));
    FND_TEST_TRUE(all((a == 7) == bool4_t{true, false, false, false}));
    FND_TEST_TRUE(all((-6 == a) == bool4_t{false, false, false, true}));

    FND_TEST_TRUE(all((a != int4_t{7, -3, 4, -6}) == bool4_t{false, false, false, false}));
    FND_TEST_TRUE(all((a != int4_t{7, 5, 4, 6}) == bool4_t{false, true, false, true}));
    FND_TEST_TRUE(all((a != int4_t{2, 5, 1, 0}) == bool4_t{true, true, true, true}));
    FND_TEST_TRUE(all((a != 7) == bool4_t{false, true, true, true}));
    FND_TEST_TRUE(all((-6 != a) == bool4_t{true, true, true, false}));
}

void unittests_math_vector_int4_relational_operators()
{
    const int4_t a{7, -3, 4, -6};
    const int4_t b{2, 5, 4, -6};
    const int4_t c{7, 5, -1, -7};

    FND_TEST_TRUE(all((a < b) == bool4_t{false, true, false, false}));
    FND_TEST_TRUE(all((a < c) == bool4_t{false, true, false, false}));
    FND_TEST_TRUE(all((a < 0) == bool4_t{false, true, false, true}));
    FND_TEST_TRUE(all((0 < a) == bool4_t{true, false, true, false}));

    FND_TEST_TRUE(all((a <= b) == bool4_t{false, true, true, true}));
    FND_TEST_TRUE(all((a <= c) == bool4_t{true, true, false, false}));
    FND_TEST_TRUE(all((a <= 4) == bool4_t{false, true, true, true}));
    FND_TEST_TRUE(all((7 <= a) == bool4_t{true, false, false, false}));

    FND_TEST_TRUE(all((a > b) == bool4_t{true, false, false, false}));
    FND_TEST_TRUE(all((a > c) == bool4_t{false, false, true, true}));
    FND_TEST_TRUE(all((a > 0) == bool4_t{true, false, true, false}));
    FND_TEST_TRUE(all((0 > a) == bool4_t{false, true, false, true}));

    FND_TEST_TRUE(all((a >= b) == bool4_t{true, false, true, true}));
    FND_TEST_TRUE(all((a >= c) == bool4_t{true, false, true, true}));
    FND_TEST_TRUE(all((a >= 7) == bool4_t{true, false, false, false}));
    FND_TEST_TRUE(all((4 >= a) == bool4_t{false, true, true, true}));
}

void unittests_math_vector_int4_addition_operator()
{
    const int4_t a{7, -3, 4, -6};
    FND_TEST_TRUE(test_components(a + int4_t{2, 5, -3, 4}, 9, 2, 1, -2));
    FND_TEST_TRUE(test_components(a + 1, 8, -2, 5, -5));
    FND_TEST_TRUE(test_components(1 + a, 8, -2, 5, -5));
    FND_TEST_TRUE(test_components(
        int4_t{kIntMaxValue - 1, kIntMinValue + 1, 0, 5} + int4_t{1, -1, 0, -5},
        kIntMaxValue, kIntMinValue, 0, 0));
}

void unittests_math_vector_int4_subtraction_operator()
{
    const int4_t a{7, -3, 4, -6};
    FND_TEST_TRUE(test_components(a - int4_t{2, 5, -3, 4}, 5, -8, 7, -10));
    FND_TEST_TRUE(test_components(a - 1, 6, -4, 3, -7));
    FND_TEST_TRUE(test_components(1 - a, -6, 4, -3, 7));
    FND_TEST_TRUE(test_components(
        int4_t{kIntMinValue + 1, kIntMaxValue - 1, 0, 5} - int4_t{1, -1, 0, 5},
        kIntMinValue, kIntMaxValue, 0, 0));
}

void unittests_math_vector_int4_multiplication_operator()
{
    const int4_t a{7, -3, 4, -6};
    FND_TEST_TRUE(test_components(a * int4_t{2, 5, -3, 4}, 14, -15, -12, -24));
    FND_TEST_TRUE(test_components(a * 2, 14, -6, 8, -12));
    FND_TEST_TRUE(test_components(2 * a, 14, -6, 8, -12));
    // 46340^2 is the largest square that fits in int_t.
    FND_TEST_TRUE(test_components(
        int4_t{46340, -46340, 1, -1} * 46340, 2147395600, -2147395600, 46340, -46340));
}

void unittests_math_vector_int4_division_operator()
{
    // Division truncates toward zero.
    const int4_t a{7, -3, 4, -6};
    FND_TEST_TRUE(test_components(a / int4_t{2, 5, -3, 4}, 3, 0, -1, -1));
    FND_TEST_TRUE(test_components(a / 2, 3, -1, 2, -3));
    FND_TEST_TRUE(test_components(21 / int4_t{2, 5, -4, -21}, 10, 4, -5, -1));
    FND_TEST_TRUE(test_components(
        int4_t{kIntMinValue, kIntMaxValue, 9, -9} / int4_t{1, -1, 3, -3},
        kIntMinValue, -kIntMaxValue, 3, 3));
}

void unittests_math_vector_int4_modulo_operator()
{
    // The result has the sign of the left operand.
    const int4_t a{7, -3, 4, -6};
    FND_TEST_TRUE(test_components(a % int4_t{2, 5, -3, 4}, 1, -3, 1, -2));
    FND_TEST_TRUE(test_components(a % 2, 1, -1, 0, 0));
    FND_TEST_TRUE(test_components(21 % int4_t{2, 5, -4, -21}, 1, 1, 1, 0));
    FND_TEST_TRUE(test_components(
        int4_t{kIntMinValue, 7, -7, kIntMaxValue} % int4_t{kIntMaxValue, -2, 3, kIntMaxValue},
        -1, 1, -1, 0));
}

void unittests_math_vector_int4_bitwise_not_operator()
{
    FND_TEST_TRUE(test_components(~int4_t{0, -1, 5, -6}, -1, 0, -6, 5));
    FND_TEST_TRUE(test_components(
        ~int4_t{kIntMaxValue, kIntMinValue, 1, -2}, kIntMinValue, kIntMaxValue, -2, 1));
}

void unittests_math_vector_int4_bitwise_and_operator()
{
    const int4_t a{0b1100, 0b1010, 0b1111, 0b0000};
    FND_TEST_TRUE(test_components(
        a & int4_t{0b1010, 0b0110, 0b0011, 0b1111}, 0b1000, 0b0010, 0b0011, 0));
    FND_TEST_TRUE(test_components(a & 0b0110, 0b0100, 0b0010, 0b0110, 0));
    FND_TEST_TRUE(test_components(0b0110 & a, 0b0100, 0b0010, 0b0110, 0));
    FND_TEST_TRUE(test_components(
        int4_t{-1, kIntMinValue, 0x1FF, 0x100} & 0xFF, 0xFF, 0, 0xFF, 0));
}

void unittests_math_vector_int4_bitwise_or_operator()
{
    const int4_t a{0b1100, 0b1010, 0b1111, 0b0000};
    FND_TEST_TRUE(test_components(
        a | int4_t{0b1010, 0b0110, 0b0000, 0b0001}, 0b1110, 0b1110, 0b1111, 0b0001));
    FND_TEST_TRUE(test_components(a | 0b0001, 0b1101, 0b1011, 0b1111, 0b0001));
    FND_TEST_TRUE(test_components(0b0001 | a, 0b1101, 0b1011, 0b1111, 0b0001));
    FND_TEST_TRUE(test_components(
        int4_t{0, kIntMaxValue, 1, -2} | kIntMinValue, kIntMinValue, -1, kIntMinValue + 1, -2));
}

void unittests_math_vector_int4_bitwise_xor_operator()
{
    const int4_t a{0b1100, 0b1010, 0b1111, 0b0000};
    FND_TEST_TRUE(test_components(
        a ^ int4_t{0b1010, 0b0110, 0b1111, 0b0101}, 0b0110, 0b1100, 0, 0b0101));
    FND_TEST_TRUE(test_components(a ^ 0b1111, 0b0011, 0b0101, 0, 0b1111));
    FND_TEST_TRUE(test_components(0b1111 ^ a, 0b0011, 0b0101, 0, 0b1111));
    FND_TEST_TRUE(test_components(a ^ a, 0, 0, 0, 0));
}

void unittests_math_vector_int4_shift_left_operator()
{
    FND_TEST_TRUE(test_components(int4_t{1, 3, 5, -1} << int4_t{4, 1, 0, 3}, 16, 6, 5, -8));
    FND_TEST_TRUE(test_components(int4_t{1, 3, 5, -1} << 2, 4, 12, 20, -4));
    FND_TEST_TRUE(test_components(1 << int4_t{0, 31, 4, 1}, 1, kIntMinValue, 16, 2));
    FND_TEST_TRUE(test_components(int4_t{-1, -2, -3, -4} << 1, -2, -4, -6, -8));
}

void unittests_math_vector_int4_shift_right_operator()
{
    FND_TEST_TRUE(test_components(int4_t{16, 6, 5, -8} >> int4_t{4, 1, 0, 3}, 1, 3, 5, -1));
    // Negative values shift in sign bits.
    FND_TEST_TRUE(test_components(int4_t{-8, 8, -1, 1} >> 1, -4, 4, -1, 0));
    FND_TEST_TRUE(test_components(256 >> int4_t{4, 8, 0, 9}, 16, 1, 256, 0));
    FND_TEST_TRUE(test_components(
        int4_t{kIntMinValue, kIntMaxValue, -1, 1} >> 31, -1, 0, -1, 0));
}

void unittests_math_vector_int4_compound_assignment_operators()
{
    int4_t v{7, -3, 2, -5};

    // Each operator returns a reference to its left operand.
    FND_TEST_TRUE(&(v += int4_t{1, 2, 3, 4}) == &v);
    FND_TEST_TRUE(test_components(v, 8, -1, 5, -1));
    FND_TEST_TRUE(test_components(v += 2, 10, 1, 7, 1));

    FND_TEST_TRUE(test_components(v -= int4_t{4, 3, 2, 1}, 6, -2, 5, 0));
    FND_TEST_TRUE(test_components(v -= 1, 5, -3, 4, -1));

    FND_TEST_TRUE(test_components(v *= int4_t{2, -2, 3, -3}, 10, 6, 12, 3));
    FND_TEST_TRUE(test_components(v *= 3, 30, 18, 36, 9));

    FND_TEST_TRUE(test_components(v /= int4_t{3, 2, 4, 2}, 10, 9, 9, 4));
    FND_TEST_TRUE(test_components(v /= 2, 5, 4, 4, 2));

    FND_TEST_TRUE(test_components(v %= int4_t{3, 3, 3, 3}, 2, 1, 1, 2));
    v = int4_t{7, 9, 10, 11};
    FND_TEST_TRUE(test_components(v %= 4, 3, 1, 2, 3));

    v = int4_t{0b1100, 0b1010, 0b1111, 0b0000};
    FND_TEST_TRUE(test_components(
        v &= int4_t{0b1010, 0b0110, 0b0011, 0b1111}, 0b1000, 0b0010, 0b0011, 0));
    FND_TEST_TRUE(test_components(v &= 0b1000, 0b1000, 0, 0, 0));

    FND_TEST_TRUE(test_components(
        v |= int4_t{0b0001, 0b0010, 0b0100, 0b1000}, 0b1001, 0b0010, 0b0100, 0b1000));
    FND_TEST_TRUE(test_components(v |= 0b0100, 0b1101, 0b0110, 0b0100, 0b1100));

    FND_TEST_TRUE(test_components(
        v ^= int4_t{0b1101, 0b0000, 0b0100, 0b1100}, 0, 0b0110, 0, 0));
    FND_TEST_TRUE(test_components(v ^= 0b0011, 0b0011, 0b0101, 0b0011, 0b0011));

    FND_TEST_TRUE(test_components(
        v <<= int4_t{1, 2, 3, 1}, 0b0110, 0b10100, 0b11000, 0b0110));
    FND_TEST_TRUE(test_components(v <<= 1, 0b1100, 0b101000, 0b110000, 0b1100));

    FND_TEST_TRUE(test_components(v >>= int4_t{2, 3, 4, 2}, 0b0011, 0b0101, 0b0011, 0b0011));
    FND_TEST_TRUE(test_components(v >>= 1, 0b0001, 0b0010, 0b0001, 0b0001));
}

void unittests_math_vector_int4_compound_assignment_matches_operators()
{
    // a op= b must give the same result as a op b.
    const int4_t a{7, -3, 4, -6};
    const int4_t b{2, 5, -3, 4};
    const int_t val{3};
    // Shift counts must be in [0, 32).
    const int4_t shift{1, 4, 2, 3};
    const int_t shift_val{2};
    int4_t c;

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

void unittests_math_vector_int4_abs()
{
    FND_TEST_TRUE(test_components(abs(int4_t{7, -3, 0, -1}), 7, 3, 0, 1));
    FND_TEST_TRUE(test_components(
        abs(int4_t{kIntMaxValue, -kIntMaxValue, -1, 1}), kIntMaxValue, kIntMaxValue, 1, 1));
}

void unittests_math_vector_int4_min()
{
    const int4_t a{7, -3, 4, -6};
    FND_TEST_TRUE(test_components(min(a, int4_t{2, 5, 4, -7}), 2, -3, 4, -7));
    FND_TEST_TRUE(test_components(min(int4_t{2, 5, 4, -7}, a), 2, -3, 4, -7));
    FND_TEST_TRUE(test_components(min(int4_t{4, 4, 4, 4}, int4_t{4, 4, 4, 4}), 4, 4, 4, 4));
    FND_TEST_TRUE(test_components(
        min(int4_t{kIntMinValue, kIntMaxValue, 0, 1}, int4_t{kIntMaxValue, kIntMinValue, 0, -1}),
        kIntMinValue, kIntMinValue, 0, -1));
    // int_t on either side is compared with every component.
    FND_TEST_TRUE(test_components(min(a, 0), 0, -3, 0, -6));
    FND_TEST_TRUE(test_components(min(0, a), 0, -3, 0, -6));
    FND_TEST_TRUE(test_components(min(a, -5), -5, -5, -5, -6));
    FND_TEST_TRUE(test_components(min(10, a), 7, -3, 4, -6));
}

void unittests_math_vector_int4_max()
{
    const int4_t a{7, -3, 4, -6};
    FND_TEST_TRUE(test_components(max(a, int4_t{2, 5, 4, -7}), 7, 5, 4, -6));
    FND_TEST_TRUE(test_components(max(int4_t{2, 5, 4, -7}, a), 7, 5, 4, -6));
    FND_TEST_TRUE(test_components(max(int4_t{4, 4, 4, 4}, int4_t{4, 4, 4, 4}), 4, 4, 4, 4));
    FND_TEST_TRUE(test_components(
        max(int4_t{kIntMinValue, kIntMaxValue, 0, 1}, int4_t{kIntMaxValue, kIntMinValue, 0, -1}),
        kIntMaxValue, kIntMaxValue, 0, 1));
    // int_t on either side is compared with every component.
    FND_TEST_TRUE(test_components(max(a, 0), 7, 0, 4, 0));
    FND_TEST_TRUE(test_components(max(0, a), 7, 0, 4, 0));
    FND_TEST_TRUE(test_components(max(a, 10), 10, 10, 10, 10));
    FND_TEST_TRUE(test_components(max(-5, a), 7, -3, 4, -5));
}

void unittests_math_vector_int4_clamp()
{
    const int4_t lower{-10, 0, -1, 2};
    const int4_t upper{10, 5, 1, 2};
    // Each component is clamped to its own bounds.
    FND_TEST_TRUE(test_components(clamp(int4_t{3, 3, 0, 0}, lower, upper), 3, 3, 0, 2));
    FND_TEST_TRUE(test_components(clamp(int4_t{-20, -1, -5, 9}, lower, upper), -10, 0, -1, 2));
    FND_TEST_TRUE(test_components(clamp(int4_t{20, 6, 5, -9}, lower, upper), 10, 5, 1, 2));
    FND_TEST_TRUE(test_components(clamp(int4_t{-10, 5, 1, 2}, lower, upper), -10, 5, 1, 2));
    FND_TEST_TRUE(test_components(clamp(int4_t{-20, 6, 0, 2}, lower, upper), -10, 5, 0, 2));
    FND_TEST_TRUE(test_components(
        clamp(int4_t{9, 9, 9, 9}, int4_t{3, 3, 3, 3}, int4_t{3, 3, 3, 3}), 3, 3, 3, 3));

    // int_t bounds apply to every component.
    FND_TEST_TRUE(test_components(clamp(int4_t{3, -3, 9, 5}, 0, 5), 3, 0, 5, 5));
    FND_TEST_TRUE(test_components(clamp(int4_t{-20, 20, 0, -10}, -10, 10), -10, 10, 0, -10));
    FND_TEST_TRUE(test_components(clamp(int4_t{-10, 10, 5, -5}, -10, 10), -10, 10, 5, -5));
    FND_TEST_TRUE(test_components(clamp(int4_t{9, -9, 0, 3}, 3, 3), 3, 3, 3, 3));

    // int4_t lower bound, int_t upper bound.
    FND_TEST_TRUE(test_components(
        clamp(int4_t{-20, -20, -20, -20}, int4_t{-10, 0, -5, 5}, 5), -10, 0, -5, 5));
    FND_TEST_TRUE(test_components(
        clamp(int4_t{20, 3, 7, 0}, int4_t{-10, 0, -5, 5}, 5), 5, 3, 5, 5));
    FND_TEST_TRUE(test_components(
        clamp(int4_t{-10, 5, -5, 5}, int4_t{-10, 0, -5, 5}, 5), -10, 5, -5, 5));
    FND_TEST_TRUE(test_components(
        clamp(int4_t{9, -9, 0, 1}, int4_t{3, 5, 1, -1}, 5), 5, 5, 1, 1));

    // int_t lower bound, int4_t upper bound.
    FND_TEST_TRUE(test_components(
        clamp(int4_t{-20, -20, -20, -20}, 0, int4_t{10, 5, 1, 0}), 0, 0, 0, 0));
    FND_TEST_TRUE(test_components(
        clamp(int4_t{20, 3, 7, 5}, 0, int4_t{10, 5, 1, 0}), 10, 3, 1, 0));
    FND_TEST_TRUE(test_components(
        clamp(int4_t{0, 5, 1, 0}, 0, int4_t{10, 5, 1, 0}), 0, 5, 1, 0));
    FND_TEST_TRUE(test_components(
        clamp(int4_t{9, -9, 0, 5}, 3, int4_t{3, 7, 4, 9}), 3, 3, 3, 5));
}

void unittests_math_vector_int4_sign()
{
    FND_TEST_TRUE(test_components(sign(int4_t{7, -3, 0, -1}), 1, -1, 0, -1));
    FND_TEST_TRUE(test_components(sign(int4_t{0, 5, -5, 0}), 0, 1, -1, 0));
    FND_TEST_TRUE(test_components(sign(int4_t{kIntMinValue, kIntMaxValue, 0, 1}), -1, 1, 0, 1));
}

void unittests_math_vector_int4_cmin()
{
    // The minimum in each position.
    FND_TEST_TRUE(cmin(int4_t{-3, 7, 4, 5}) == -3);
    FND_TEST_TRUE(cmin(int4_t{7, -3, 4, 5}) == -3);
    FND_TEST_TRUE(cmin(int4_t{7, 4, -3, 5}) == -3);
    FND_TEST_TRUE(cmin(int4_t{7, 4, 5, -3}) == -3);
    FND_TEST_TRUE(cmin(int4_t{4, 4, 4, 4}) == 4);
    FND_TEST_TRUE(cmin(int4_t{kIntMaxValue, 0, kIntMinValue, 1}) == kIntMinValue);
}

void unittests_math_vector_int4_cmax()
{
    // The maximum in each position.
    FND_TEST_TRUE(cmax(int4_t{9, -3, 4, 5}) == 9);
    FND_TEST_TRUE(cmax(int4_t{-3, 9, 4, 5}) == 9);
    FND_TEST_TRUE(cmax(int4_t{4, -3, 9, 5}) == 9);
    FND_TEST_TRUE(cmax(int4_t{4, -3, 5, 9}) == 9);
    FND_TEST_TRUE(cmax(int4_t{4, 4, 4, 4}) == 4);
    FND_TEST_TRUE(cmax(int4_t{kIntMinValue, 0, kIntMaxValue, 1}) == kIntMaxValue);
}

void unittests_math_vector_int4_csum()
{
    FND_TEST_TRUE(csum(int4_t{7, -3, 4, -6}) == 2);
    FND_TEST_TRUE(csum(int4_t{0, 0, 0, 0}) == 0);
    FND_TEST_TRUE(csum(int4_t{-7, -3, -1, -2}) == -13);
    FND_TEST_TRUE(csum(int4_t{kIntMaxValue - 3, 1, 1, 1}) == kIntMaxValue);
    FND_TEST_TRUE(csum(int4_t{kIntMinValue, kIntMaxValue, 1, 0}) == 0);
}

void unittests_math_vector_int4_cmul()
{
    FND_TEST_TRUE(cmul(int4_t{7, -3, 2, -1}) == 42);
    FND_TEST_TRUE(cmul(int4_t{0, kIntMaxValue, kIntMaxValue, kIntMaxValue}) == 0);
    FND_TEST_TRUE(cmul(int4_t{-7, -3, -2, -1}) == 42);
    // 215^4 is the largest fourth power that fits in int_t.
    FND_TEST_TRUE(cmul(int4_t{215, 215, 215, 215}) == 2136750625);
    FND_TEST_TRUE(cmul(int4_t{kIntMinValue, 1, 1, 1}) == kIntMinValue);
}

void unittests_math_vector_int4()
{
    unittests_math_vector_int4_type();
    unittests_math_vector_int4_constructors();
    unittests_math_vector_int4_subscript_operator();
    unittests_math_vector_int4_increment_operators();
    unittests_math_vector_int4_decrement_operators();
    unittests_math_vector_int4_unary_minus_operator();
    unittests_math_vector_int4_equality_operators();
    unittests_math_vector_int4_relational_operators();
    unittests_math_vector_int4_addition_operator();
    unittests_math_vector_int4_subtraction_operator();
    unittests_math_vector_int4_multiplication_operator();
    unittests_math_vector_int4_division_operator();
    unittests_math_vector_int4_modulo_operator();
    unittests_math_vector_int4_bitwise_not_operator();
    unittests_math_vector_int4_bitwise_and_operator();
    unittests_math_vector_int4_bitwise_or_operator();
    unittests_math_vector_int4_bitwise_xor_operator();
    unittests_math_vector_int4_shift_left_operator();
    unittests_math_vector_int4_shift_right_operator();
    unittests_math_vector_int4_compound_assignment_operators();
    unittests_math_vector_int4_compound_assignment_matches_operators();
    unittests_math_vector_int4_abs();
    unittests_math_vector_int4_min();
    unittests_math_vector_int4_max();
    unittests_math_vector_int4_clamp();
    unittests_math_vector_int4_sign();
    unittests_math_vector_int4_cmin();
    unittests_math_vector_int4_cmax();
    unittests_math_vector_int4_csum();
    unittests_math_vector_int4_cmul();
}

} // namespace fnd::unittests
