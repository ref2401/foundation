module;
#include "foundation/unittests.h"


export module unittests.math:vector_uint4;
import foundation.core;
import foundation.math;

namespace fnd::unittests {

export void unittests_math_vector_uint4();

// ---------------------------------------------------------------------------
// uint4_t
// ---------------------------------------------------------------------------

constexpr bool_t test_components(const uint4_t v, const uint_t x,
    const uint_t y, const uint_t z, const uint_t w)
{
    return v.x == x && v.y == y && v.z == z && v.w == w;
}

void unittests_math_vector_uint4_type()
{
    static_assert(PodType<uint4_t>);
    static_assert(sizeof(uint4_t) == 4 * sizeof(uint_t));
    // The ctor(uint_t) is explicit.
    static_assert(!is_convertible<uint_t, uint4_t>());
    static_assert(!is_convertible<int_t, uint4_t>());
}

void unittests_math_vector_uint4_constants()
{
    FND_TEST_TRUE(test_components(uint4_t::kZero, 0u, 0u, 0u, 0u));
    FND_TEST_TRUE(test_components(uint4_t::kUnitX, 1u, 0u, 0u, 0u));
    FND_TEST_TRUE(test_components(uint4_t::kUnitY, 0u, 1u, 0u, 0u));
    FND_TEST_TRUE(test_components(uint4_t::kUnitZ, 0u, 0u, 1u, 0u));
    FND_TEST_TRUE(test_components(uint4_t::kUnitW, 0u, 0u, 0u, 1u));
    FND_TEST_TRUE(all(uint4_t::kZero == uint4_t{}));
    FND_TEST_TRUE(all(uint4_t::kUnitX + uint4_t::kUnitY
        + uint4_t::kUnitZ + uint4_t::kUnitW == uint4_t{1u}));
    // The constants are usable in constant expressions.
    static_assert(uint4_t::kUnitW.w == 1u);
}

void unittests_math_vector_uint4_constructors()
{
    FND_TEST_TRUE(test_components(uint4_t{}, 0u, 0u, 0u, 0u));
    FND_TEST_TRUE(test_components(uint4_t{5u}, 5u, 5u, 5u, 5u));
    FND_TEST_TRUE(test_components(uint4_t{3u, 4u, 6u, 8u}, 3u, 4u, 6u, 8u));
    FND_TEST_TRUE(test_components(
        uint4_t{0u, kUIntMaxValue, 1u, 2u}, 0u, kUIntMaxValue, 1u, 2u));
}

void unittests_math_vector_uint4_subscript_operator()
{
    const uint4_t v{3u, 4u, 6u, 8u};
    FND_TEST_TRUE(v[0] == 3u);
    FND_TEST_TRUE(v[1] == 4u);
    FND_TEST_TRUE(v[2] == 6u);
    FND_TEST_TRUE(v[3] == 8u);

    // The non-const overload returns a reference into the vector itself.
    uint4_t w;
    w[3] = 9u;
    FND_TEST_TRUE(test_components(w, 0u, 0u, 0u, 9u));

    w[0] = kUIntMaxValue;
    FND_TEST_TRUE(test_components(w, kUIntMaxValue, 0u, 0u, 9u));
}

void unittests_math_vector_uint4_increment_operators()
{
    // kUIntMaxValue wraps around to 0.
    uint4_t v{1u, kUIntMaxValue, 0u, 5u};
    FND_TEST_TRUE(test_components(++v, 2u, 0u, 1u, 6u));
    FND_TEST_TRUE(test_components(v, 2u, 0u, 1u, 6u));

    // Postfix returns the value before the increment.
    FND_TEST_TRUE(test_components(v++, 2u, 0u, 1u, 6u));
    FND_TEST_TRUE(test_components(v, 3u, 1u, 2u, 7u));
}

void unittests_math_vector_uint4_decrement_operators()
{
    // 0 wraps around to kUIntMaxValue.
    uint4_t v{1u, 0u, 5u, 2u};
    FND_TEST_TRUE(test_components(--v, 0u, kUIntMaxValue, 4u, 1u));
    FND_TEST_TRUE(test_components(v, 0u, kUIntMaxValue, 4u, 1u));

    // Postfix returns the value before the decrement.
    FND_TEST_TRUE(test_components(v--, 0u, kUIntMaxValue, 4u, 1u));
    FND_TEST_TRUE(test_components(v, kUIntMaxValue, kUIntMaxValue - 1, 3u, 0u));
}

void unittests_math_vector_uint4_bitwise_not_operator()
{
    FND_TEST_TRUE(test_components(~uint4_t{0u, 5u, kUIntMaxValue, 1u},
        kUIntMaxValue, kUIntMaxValue - 5, 0u, kUIntMaxValue - 1));
    FND_TEST_TRUE(test_components(~uint4_t{0x80000000u, 1u, 0x7FFFFFFFu, 0u},
        0x7FFFFFFFu, kUIntMaxValue - 1, 0x80000000u, kUIntMaxValue));
}

void unittests_math_vector_uint4_compound_assignment_operators()
{
    uint4_t v{7u, 3u, 2u, 1u};

    // Each operator returns a reference to its left operand.
    FND_TEST_TRUE(&(v += uint4_t{1u, 2u, 3u, 4u}) == &v);
    FND_TEST_TRUE(test_components(v, 8u, 5u, 5u, 5u));
    FND_TEST_TRUE(test_components(v += 2u, 10u, 7u, 7u, 7u));
    FND_TEST_TRUE(test_components(v += 1, 11u, 8u, 8u, 8u));

    FND_TEST_TRUE(
        test_components(v -= uint4_t{4u, 3u, 2u, 1u}, 7u, 5u, 6u, 7u));
    FND_TEST_TRUE(test_components(v -= 1u, 6u, 4u, 5u, 6u));
    FND_TEST_TRUE(test_components(v -= 1, 5u, 3u, 4u, 5u));

    FND_TEST_TRUE(
        test_components(v *= uint4_t{2u, 3u, 4u, 2u}, 10u, 9u, 16u, 10u));
    FND_TEST_TRUE(test_components(v *= 3u, 30u, 27u, 48u, 30u));
    FND_TEST_TRUE(test_components(v *= 2, 60u, 54u, 96u, 60u));

    FND_TEST_TRUE(
        test_components(v /= uint4_t{3u, 2u, 4u, 5u}, 20u, 27u, 24u, 12u));
    FND_TEST_TRUE(test_components(v /= 2u, 10u, 13u, 12u, 6u));
    FND_TEST_TRUE(test_components(v /= 3, 3u, 4u, 4u, 2u));

    FND_TEST_TRUE(
        test_components(v %= uint4_t{2u, 3u, 3u, 3u}, 1u, 1u, 1u, 2u));
    v = uint4_t{7u, 9u, 10u, 11u};
    FND_TEST_TRUE(test_components(v %= 4u, 3u, 1u, 2u, 3u));
    v = uint4_t{7u, 9u, 10u, 11u};
    FND_TEST_TRUE(test_components(v %= 5, 2u, 4u, 0u, 1u));

    v = uint4_t{0b1100u, 0b1010u, 0b1111u, 0b0000u};
    FND_TEST_TRUE(
        test_components(v &= uint4_t{0b1010u, 0b0110u, 0b0011u, 0b1111u},
            0b1000u, 0b0010u, 0b0011u, 0u));
    FND_TEST_TRUE(test_components(v &= 0b1010u, 0b1000u, 0b0010u, 0b0010u, 0u));
    FND_TEST_TRUE(test_components(v &= 0b1000, 0b1000u, 0u, 0u, 0u));

    FND_TEST_TRUE(
        test_components(v |= uint4_t{0b0001u, 0b0010u, 0b0100u, 0b1000u},
            0b1001u, 0b0010u, 0b0100u, 0b1000u));
    FND_TEST_TRUE(
        test_components(v |= 0b0100u, 0b1101u, 0b0110u, 0b0100u, 0b1100u));
    FND_TEST_TRUE(
        test_components(v |= 0b10000, 0b11101u, 0b10110u, 0b10100u, 0b11100u));

    FND_TEST_TRUE(
        test_components(v ^= uint4_t{0b11101u, 0u, 0b00100u, 0b01100u}, 0u,
            0b10110u, 0b10000u, 0b10000u));
    FND_TEST_TRUE(
        test_components(v ^= 0b0011u, 0b0011u, 0b10101u, 0b10011u, 0b10011u));
    FND_TEST_TRUE(
        test_components(v ^= 0b0001, 0b0010u, 0b10100u, 0b10010u, 0b10010u));

    FND_TEST_TRUE(
        test_components(v <<= uint4_t{1u, 2u, 1u, 1u}, 4u, 80u, 36u, 36u));
    FND_TEST_TRUE(test_components(v <<= 1u, 8u, 160u, 72u, 72u));
    FND_TEST_TRUE(test_components(v <<= 1, 16u, 320u, 144u, 144u));

    FND_TEST_TRUE(
        test_components(v >>= uint4_t{2u, 3u, 2u, 2u}, 4u, 40u, 36u, 36u));
    FND_TEST_TRUE(test_components(v >>= 1u, 2u, 20u, 18u, 18u));
    FND_TEST_TRUE(test_components(v >>= 1, 1u, 10u, 9u, 9u));
}

void unittests_math_vector_uint4_compound_assignment_matches_operators()
{
    // a op= b must give the same result as a op b, for every right-hand side.
    const uint4_t a{7u, 3u, 4u, 6u};
    const uint4_t b{2u, 5u, 3u, 1u};
    const uint_t uval{3u};
    const int_t ival{3};
    // Shift counts must be in [0, 32).
    const uint4_t shift{1u, 4u, 2u, 3u};
    const uint_t ushift{2u};
    const int_t ishift{2};
    uint4_t c;

    c = a;
    c += b;
    FND_TEST_TRUE(all(c == (a + b)));
    c = a;
    c += uval;
    FND_TEST_TRUE(all(c == (a + uval)));
    c = a;
    c += ival;
    FND_TEST_TRUE(all(c == (a + ival)));

    c = a;
    c -= b;
    FND_TEST_TRUE(all(c == (a - b)));
    c = a;
    c -= uval;
    FND_TEST_TRUE(all(c == (a - uval)));
    c = a;
    c -= ival;
    FND_TEST_TRUE(all(c == (a - ival)));

    c = a;
    c *= b;
    FND_TEST_TRUE(all(c == (a * b)));
    c = a;
    c *= uval;
    FND_TEST_TRUE(all(c == (a * uval)));
    c = a;
    c *= ival;
    FND_TEST_TRUE(all(c == (a * ival)));

    c = a;
    c /= b;
    FND_TEST_TRUE(all(c == (a / b)));
    c = a;
    c /= uval;
    FND_TEST_TRUE(all(c == (a / uval)));
    c = a;
    c /= ival;
    FND_TEST_TRUE(all(c == (a / ival)));

    c = a;
    c %= b;
    FND_TEST_TRUE(all(c == (a % b)));
    c = a;
    c %= uval;
    FND_TEST_TRUE(all(c == (a % uval)));
    c = a;
    c %= ival;
    FND_TEST_TRUE(all(c == (a % ival)));

    c = a;
    c &= b;
    FND_TEST_TRUE(all(c == (a & b)));
    c = a;
    c &= uval;
    FND_TEST_TRUE(all(c == (a & uval)));
    c = a;
    c &= ival;
    FND_TEST_TRUE(all(c == (a & ival)));

    c = a;
    c |= b;
    FND_TEST_TRUE(all(c == (a | b)));
    c = a;
    c |= uval;
    FND_TEST_TRUE(all(c == (a | uval)));
    c = a;
    c |= ival;
    FND_TEST_TRUE(all(c == (a | ival)));

    c = a;
    c ^= b;
    FND_TEST_TRUE(all(c == (a ^ b)));
    c = a;
    c ^= uval;
    FND_TEST_TRUE(all(c == (a ^ uval)));
    c = a;
    c ^= ival;
    FND_TEST_TRUE(all(c == (a ^ ival)));

    c = a;
    c <<= shift;
    FND_TEST_TRUE(all(c == (a << shift)));
    c = a;
    c <<= ushift;
    FND_TEST_TRUE(all(c == (a << ushift)));
    c = a;
    c <<= ishift;
    FND_TEST_TRUE(all(c == (a << ishift)));

    c = a;
    c >>= shift;
    FND_TEST_TRUE(all(c == (a >> shift)));
    c = a;
    c >>= ushift;
    FND_TEST_TRUE(all(c == (a >> ushift)));
    c = a;
    c >>= ishift;
    FND_TEST_TRUE(all(c == (a >> ishift)));
}

void unittests_math_vector_uint4_equality_operators()
{
    const uint4_t a{7u, 3u, 4u, 6u};
    FND_TEST_TRUE(
        all((a == uint4_t{7u, 3u, 4u, 6u}) == bool4_t{true, true, true, true}));
    FND_TEST_TRUE(all(
        (a == uint4_t{7u, 5u, 4u, 1u}) == bool4_t{true, false, true, false}));
    FND_TEST_TRUE(all(
        (a == uint4_t{2u, 5u, 1u, 0u}) == bool4_t{false, false, false, false}));
    FND_TEST_TRUE(all((a == 7u) == bool4_t{true, false, false, false}));
    FND_TEST_TRUE(all((6u == a) == bool4_t{false, false, false, true}));
    FND_TEST_TRUE(all((a == 7) == bool4_t{true, false, false, false}));
    FND_TEST_TRUE(all((6 == a) == bool4_t{false, false, false, true}));

    FND_TEST_TRUE(all(
        (a != uint4_t{7u, 3u, 4u, 6u}) == bool4_t{false, false, false, false}));
    FND_TEST_TRUE(all(
        (a != uint4_t{7u, 5u, 4u, 1u}) == bool4_t{false, true, false, true}));
    FND_TEST_TRUE(
        all((a != uint4_t{2u, 5u, 1u, 0u}) == bool4_t{true, true, true, true}));
    FND_TEST_TRUE(all((a != 7u) == bool4_t{false, true, true, true}));
    FND_TEST_TRUE(all((6u != a) == bool4_t{true, true, true, false}));
    FND_TEST_TRUE(all((a != 7) == bool4_t{false, true, true, true}));
    FND_TEST_TRUE(all((6 != a) == bool4_t{true, true, true, false}));
}

void unittests_math_vector_uint4_relational_operators()
{
    const uint4_t a{7u, 3u, 4u, 6u};
    const uint4_t b{2u, 5u, 4u, 6u};
    const uint4_t c{7u, 5u, 1u, 9u};

    FND_TEST_TRUE(all((a < b) == bool4_t{false, true, false, false}));
    FND_TEST_TRUE(all((a < c) == bool4_t{false, true, false, true}));
    FND_TEST_TRUE(all((a < 5u) == bool4_t{false, true, true, false}));
    FND_TEST_TRUE(all((5u < a) == bool4_t{true, false, false, true}));
    FND_TEST_TRUE(all((a < 5) == bool4_t{false, true, true, false}));
    FND_TEST_TRUE(all((5 < a) == bool4_t{true, false, false, true}));

    FND_TEST_TRUE(all((a <= b) == bool4_t{false, true, true, true}));
    FND_TEST_TRUE(all((a <= c) == bool4_t{true, true, false, true}));
    FND_TEST_TRUE(all((a <= 4u) == bool4_t{false, true, true, false}));
    FND_TEST_TRUE(all((7u <= a) == bool4_t{true, false, false, false}));
    FND_TEST_TRUE(all((a <= 4) == bool4_t{false, true, true, false}));
    FND_TEST_TRUE(all((7 <= a) == bool4_t{true, false, false, false}));

    FND_TEST_TRUE(all((a > b) == bool4_t{true, false, false, false}));
    FND_TEST_TRUE(all((a > c) == bool4_t{false, false, true, false}));
    FND_TEST_TRUE(all((a > 5u) == bool4_t{true, false, false, true}));
    FND_TEST_TRUE(all((5u > a) == bool4_t{false, true, true, false}));
    FND_TEST_TRUE(all((a > 5) == bool4_t{true, false, false, true}));
    FND_TEST_TRUE(all((5 > a) == bool4_t{false, true, true, false}));

    FND_TEST_TRUE(all((a >= b) == bool4_t{true, false, true, true}));
    FND_TEST_TRUE(all((a >= c) == bool4_t{true, false, true, false}));
    FND_TEST_TRUE(all((a >= 7u) == bool4_t{true, false, false, false}));
    FND_TEST_TRUE(all((4u >= a) == bool4_t{false, true, true, false}));
    FND_TEST_TRUE(all((a >= 7) == bool4_t{true, false, false, false}));
    FND_TEST_TRUE(all((4 >= a) == bool4_t{false, true, true, false}));
}

void unittests_math_vector_uint4_bitwise_and_operator()
{
    const uint4_t a{0b1100u, 0b1010u, 0b1111u, 0b0000u};
    FND_TEST_TRUE(
        test_components(a & uint4_t{0b1010u, 0b0110u, 0b0011u, 0b1111u},
            0b1000u, 0b0010u, 0b0011u, 0u));
    FND_TEST_TRUE(test_components(a & 0b0110u, 0b0100u, 0b0010u, 0b0110u, 0u));
    FND_TEST_TRUE(test_components(0b0110u & a, 0b0100u, 0b0010u, 0b0110u, 0u));
    FND_TEST_TRUE(test_components(a & 0b0110, 0b0100u, 0b0010u, 0b0110u, 0u));
    FND_TEST_TRUE(test_components(0b0110 & a, 0b0100u, 0b0010u, 0b0110u, 0u));
    FND_TEST_TRUE(test_components(
        uint4_t{kUIntMaxValue, 0x80000000u, 0x1FFu, 0x100u} & 0xFFu, 0xFFu, 0u,
        0xFFu, 0u));
}

void unittests_math_vector_uint4_multiplication_operator()
{
    const uint4_t a{7u, 3u, 4u, 6u};
    FND_TEST_TRUE(
        test_components(a * uint4_t{2u, 5u, 3u, 2u}, 14u, 15u, 12u, 12u));
    FND_TEST_TRUE(test_components(a * 2u, 14u, 6u, 8u, 12u));
    FND_TEST_TRUE(test_components(2u * a, 14u, 6u, 8u, 12u));
    FND_TEST_TRUE(test_components(a * 2, 14u, 6u, 8u, 12u));
    FND_TEST_TRUE(test_components(2 * a, 14u, 6u, 8u, 12u));
    // Overflow wraps around.
    FND_TEST_TRUE(
        test_components(uint4_t{0x80000000u, 3u, 1u, 0x40000000u} * 2u, 0u, 6u,
            2u, 0x80000000u));
    FND_TEST_TRUE(test_components(uint4_t{0x10000u, 0x10000u, 0x10000u, 3u}
            * uint4_t{0x10000u, 2u, 0x10000u, 5u},
        0u, 0x20000u, 0u, 15u));
}

void unittests_math_vector_uint4_addition_operator()
{
    const uint4_t a{7u, 3u, 4u, 6u};
    FND_TEST_TRUE(test_components(a + uint4_t{2u, 5u, 1u, 3u}, 9u, 8u, 5u, 9u));
    FND_TEST_TRUE(test_components(a + 1u, 8u, 4u, 5u, 7u));
    FND_TEST_TRUE(test_components(1u + a, 8u, 4u, 5u, 7u));
    FND_TEST_TRUE(test_components(a + 1, 8u, 4u, 5u, 7u));
    FND_TEST_TRUE(test_components(1 + a, 8u, 4u, 5u, 7u));
    // Overflow wraps around.
    FND_TEST_TRUE(test_components(
        uint4_t{kUIntMaxValue, 1u, 0u, 2u} + uint4_t{1u, 1u, 0u, 0u}, 0u, 2u,
        0u, 2u));
    FND_TEST_TRUE(test_components(uint4_t{kUIntMaxValue} + 2u, 1u, 1u, 1u, 1u));
}

void unittests_math_vector_uint4_subtraction_operator()
{
    const uint4_t a{7u, 3u, 4u, 6u};
    FND_TEST_TRUE(test_components(a - uint4_t{2u, 1u, 4u, 6u}, 5u, 2u, 0u, 0u));
    FND_TEST_TRUE(test_components(a - 1u, 6u, 2u, 3u, 5u));
    FND_TEST_TRUE(test_components(10u - a, 3u, 7u, 6u, 4u));
    FND_TEST_TRUE(test_components(a - 1, 6u, 2u, 3u, 5u));
    FND_TEST_TRUE(test_components(10 - a, 3u, 7u, 6u, 4u));
    // Overflow wraps around.
    FND_TEST_TRUE(test_components(
        a - uint4_t{2u, 5u, 1u, 7u}, 5u, kUIntMaxValue - 1, 3u, kUIntMaxValue));
    FND_TEST_TRUE(test_components(
        uint4_t{0u, 5u, 1u, 2u} - 1u, kUIntMaxValue, 4u, 0u, 1u));
}

void unittests_math_vector_uint4_modulo_operator()
{
    const uint4_t a{7u, 3u, 4u, 6u};
    FND_TEST_TRUE(test_components(a % uint4_t{2u, 5u, 3u, 4u}, 1u, 3u, 1u, 2u));
    FND_TEST_TRUE(test_components(a % 2u, 1u, 1u, 0u, 0u));
    FND_TEST_TRUE(
        test_components(21u % uint4_t{2u, 5u, 4u, 7u}, 1u, 1u, 1u, 0u));
    FND_TEST_TRUE(test_components(a % 2, 1u, 1u, 0u, 0u));
    FND_TEST_TRUE(
        test_components(21 % uint4_t{2u, 5u, 4u, 7u}, 1u, 1u, 1u, 0u));
    FND_TEST_TRUE(test_components(
        uint4_t{kUIntMaxValue, 9u, 8u, 6u} % uint4_t{2u, 4u, 8u, 4u}, 1u, 1u,
        0u, 2u));
}

void unittests_math_vector_uint4_division_operator()
{
    const uint4_t a{7u, 3u, 4u, 6u};
    FND_TEST_TRUE(test_components(a / uint4_t{2u, 5u, 3u, 4u}, 3u, 0u, 1u, 1u));
    FND_TEST_TRUE(test_components(a / 2u, 3u, 1u, 2u, 3u));
    FND_TEST_TRUE(
        test_components(21u / uint4_t{2u, 5u, 4u, 7u}, 10u, 4u, 5u, 3u));
    FND_TEST_TRUE(test_components(a / 2, 3u, 1u, 2u, 3u));
    FND_TEST_TRUE(
        test_components(21 / uint4_t{2u, 5u, 4u, 7u}, 10u, 4u, 5u, 3u));
    FND_TEST_TRUE(test_components(
        uint4_t{kUIntMaxValue, 9u, 8u, 6u} / uint4_t{1u, 3u, 8u, 4u},
        kUIntMaxValue, 3u, 1u, 1u));
}

void unittests_math_vector_uint4_shift_left_operator()
{
    FND_TEST_TRUE(test_components(
        uint4_t{1u, 3u, 5u, 7u} << uint4_t{4u, 1u, 0u, 2u}, 16u, 6u, 5u, 28u));
    FND_TEST_TRUE(
        test_components(uint4_t{1u, 3u, 5u, 7u} << 2u, 4u, 12u, 20u, 28u));
    FND_TEST_TRUE(test_components(
        1u << uint4_t{0u, 31u, 4u, 1u}, 1u, 0x80000000u, 16u, 2u));
    FND_TEST_TRUE(
        test_components(uint4_t{1u, 3u, 5u, 7u} << 2, 4u, 12u, 20u, 28u));
    FND_TEST_TRUE(test_components(
        1 << uint4_t{0u, 31u, 4u, 1u}, 1u, 0x80000000u, 16u, 2u));
    // Bits shifted out are discarded.
    FND_TEST_TRUE(
        test_components(uint4_t{0x80000000u, 3u, 1u, 0x40000000u} << 1u, 0u, 6u,
            2u, 0x80000000u));
}

void unittests_math_vector_uint4_shift_right_operator()
{
    FND_TEST_TRUE(test_components(
        uint4_t{16u, 6u, 5u, 28u} >> uint4_t{4u, 1u, 0u, 2u}, 1u, 3u, 5u, 7u));
    FND_TEST_TRUE(
        test_components(uint4_t{16u, 6u, 5u, 28u} >> 1u, 8u, 3u, 2u, 14u));
    FND_TEST_TRUE(
        test_components(256u >> uint4_t{4u, 8u, 0u, 9u}, 16u, 1u, 256u, 0u));
    FND_TEST_TRUE(
        test_components(uint4_t{16u, 6u, 5u, 28u} >> 1, 8u, 3u, 2u, 14u));
    FND_TEST_TRUE(
        test_components(256 >> uint4_t{4u, 8u, 0u, 9u}, 16u, 1u, 256u, 0u));
    // Zeros are shifted in, whatever the top bit is.
    FND_TEST_TRUE(test_components(
        uint4_t{0x80000000u, 8u, 1u, 2u} >> 1u, 0x40000000u, 4u, 0u, 1u));
    FND_TEST_TRUE(test_components(
        uint4_t{kUIntMaxValue, 1u, 0x80000000u, 0x7FFFFFFFu} >> 31u, 1u, 0u, 1u,
        0u));
}

void unittests_math_vector_uint4_bitwise_xor_operator()
{
    const uint4_t a{0b1100u, 0b1010u, 0b1111u, 0b0000u};
    FND_TEST_TRUE(
        test_components(a ^ uint4_t{0b1010u, 0b0110u, 0b1111u, 0b0101u},
            0b0110u, 0b1100u, 0u, 0b0101u));
    FND_TEST_TRUE(test_components(a ^ 0b1111u, 0b0011u, 0b0101u, 0u, 0b1111u));
    FND_TEST_TRUE(test_components(0b1111u ^ a, 0b0011u, 0b0101u, 0u, 0b1111u));
    FND_TEST_TRUE(test_components(a ^ 0b1111, 0b0011u, 0b0101u, 0u, 0b1111u));
    FND_TEST_TRUE(test_components(0b1111 ^ a, 0b0011u, 0b0101u, 0u, 0b1111u));
    FND_TEST_TRUE(test_components(a ^ a, 0u, 0u, 0u, 0u));
}

void unittests_math_vector_uint4_bitwise_or_operator()
{
    const uint4_t a{0b1100u, 0b1010u, 0b1111u, 0b0000u};
    FND_TEST_TRUE(
        test_components(a | uint4_t{0b1010u, 0b0110u, 0b0000u, 0b0001u},
            0b1110u, 0b1110u, 0b1111u, 0b0001u));
    FND_TEST_TRUE(
        test_components(a | 0b0001u, 0b1101u, 0b1011u, 0b1111u, 0b0001u));
    FND_TEST_TRUE(
        test_components(0b0001u | a, 0b1101u, 0b1011u, 0b1111u, 0b0001u));
    FND_TEST_TRUE(
        test_components(a | 0b0001, 0b1101u, 0b1011u, 0b1111u, 0b0001u));
    FND_TEST_TRUE(
        test_components(0b0001 | a, 0b1101u, 0b1011u, 0b1111u, 0b0001u));
    FND_TEST_TRUE(
        test_components(uint4_t{0u, 0x7FFFFFFFu, 1u, 0x80000000u} | 0x80000000u,
            0x80000000u, kUIntMaxValue, 0x80000001u, 0x80000000u));
}

void unittests_math_vector_uint4_clamp()
{
    const uint4_t lower{0u, 2u, 1u, 4u};
    const uint4_t upper{10u, 5u, 1u, 8u};
    // Each component is clamped to its own bounds.
    FND_TEST_TRUE(test_components(
        clamp(uint4_t{3u, 3u, 0u, 6u}, lower, upper), 3u, 3u, 1u, 6u));
    FND_TEST_TRUE(test_components(
        clamp(uint4_t{0u, 1u, 5u, 2u}, lower, upper), 0u, 2u, 1u, 4u));
    FND_TEST_TRUE(test_components(
        clamp(uint4_t{20u, 6u, 1u, 9u}, lower, upper), 10u, 5u, 1u, 8u));
    FND_TEST_TRUE(test_components(
        clamp(uint4_t{0u, 5u, 1u, 8u}, lower, upper), 0u, 5u, 1u, 8u));
    FND_TEST_TRUE(test_components(
        clamp(uint4_t{20u, 1u, 1u, 4u}, lower, upper), 10u, 2u, 1u, 4u));
    FND_TEST_TRUE(
        test_components(clamp(uint4_t{9u, 9u, 9u, 9u}, uint4_t{3u, 3u, 3u, 3u},
                            uint4_t{3u, 3u, 3u, 3u}),
            3u, 3u, 3u, 3u));

    // uint_t bounds apply to every component.
    FND_TEST_TRUE(test_components(
        clamp(uint4_t{3u, 9u, 0u, 4u}, 2u, 5u), 3u, 5u, 2u, 4u));
    FND_TEST_TRUE(test_components(
        clamp(uint4_t{0u, 20u, 7u, 1u}, 2u, 10u), 2u, 10u, 7u, 2u));
    FND_TEST_TRUE(test_components(
        clamp(uint4_t{2u, 10u, 5u, 6u}, 2u, 10u), 2u, 10u, 5u, 6u));
    FND_TEST_TRUE(test_components(
        clamp(uint4_t{9u, 0u, 3u, 4u}, 3u, 3u), 3u, 3u, 3u, 3u));

    // uint4_t lower bound, uint_t upper bound.
    FND_TEST_TRUE(test_components(
        clamp(uint4_t{0u, 0u, 0u, 0u}, uint4_t{1u, 2u, 3u, 4u}, 5u), 1u, 2u, 3u,
        4u));
    FND_TEST_TRUE(test_components(
        clamp(uint4_t{20u, 3u, 9u, 4u}, uint4_t{1u, 2u, 3u, 4u}, 5u), 5u, 3u,
        5u, 4u));
    FND_TEST_TRUE(test_components(
        clamp(uint4_t{9u, 0u, 4u, 1u}, uint4_t{3u, 5u, 1u, 2u}, 5u), 5u, 5u, 4u,
        2u));

    // uint_t lower bound, uint4_t upper bound.
    FND_TEST_TRUE(test_components(
        clamp(uint4_t{0u, 0u, 0u, 0u}, 1u, uint4_t{10u, 5u, 2u, 3u}), 1u, 1u,
        1u, 1u));
    FND_TEST_TRUE(test_components(
        clamp(uint4_t{20u, 3u, 9u, 2u}, 1u, uint4_t{10u, 5u, 2u, 3u}), 10u, 3u,
        2u, 2u));
    FND_TEST_TRUE(test_components(
        clamp(uint4_t{9u, 0u, 4u, 8u}, 3u, uint4_t{3u, 7u, 6u, 5u}), 3u, 3u, 4u,
        5u));
}

void unittests_math_vector_uint4_cmax()
{
    // The maximum in each position.
    FND_TEST_TRUE(cmax(uint4_t{7u, 3u, 4u, 5u}) == 7u);
    FND_TEST_TRUE(cmax(uint4_t{3u, 7u, 4u, 5u}) == 7u);
    FND_TEST_TRUE(cmax(uint4_t{4u, 3u, 7u, 5u}) == 7u);
    FND_TEST_TRUE(cmax(uint4_t{4u, 3u, 5u, 7u}) == 7u);
    FND_TEST_TRUE(cmax(uint4_t{4u, 4u, 4u, 4u}) == 4u);
    FND_TEST_TRUE(cmax(uint4_t{0u, kUIntMaxValue, 1u, 2u}) == kUIntMaxValue);
}

void unittests_math_vector_uint4_cmin()
{
    // The minimum in each position.
    FND_TEST_TRUE(cmin(uint4_t{3u, 7u, 4u, 5u}) == 3u);
    FND_TEST_TRUE(cmin(uint4_t{7u, 3u, 4u, 5u}) == 3u);
    FND_TEST_TRUE(cmin(uint4_t{7u, 4u, 3u, 5u}) == 3u);
    FND_TEST_TRUE(cmin(uint4_t{7u, 4u, 5u, 3u}) == 3u);
    FND_TEST_TRUE(cmin(uint4_t{4u, 4u, 4u, 4u}) == 4u);
    FND_TEST_TRUE(cmin(uint4_t{kUIntMaxValue, 0u, 1u, 2u}) == 0u);
}

void unittests_math_vector_uint4_cmul()
{
    FND_TEST_TRUE(cmul(uint4_t{7u, 3u, 2u, 1u}) == 42u);
    FND_TEST_TRUE(
        cmul(uint4_t{0u, kUIntMaxValue, kUIntMaxValue, kUIntMaxValue}) == 0u);
    // 255^4 is the largest fourth power that fits in uint_t; 256^4 is 2^32.
    FND_TEST_TRUE(cmul(uint4_t{255u, 255u, 255u, 255u}) == 4228250625u);
    // Overflow wraps around.
    FND_TEST_TRUE(cmul(uint4_t{256u, 256u, 256u, 256u}) == 0u);
    FND_TEST_TRUE(cmul(uint4_t{0x80000000u, 3u, 1u, 1u}) == 0x80000000u);
}

void unittests_math_vector_uint4_csum()
{
    FND_TEST_TRUE(csum(uint4_t{7u, 3u, 4u, 6u}) == 20u);
    FND_TEST_TRUE(csum(uint4_t{0u, 0u, 0u, 0u}) == 0u);
    FND_TEST_TRUE(
        csum(uint4_t{kUIntMaxValue - 3, 1u, 1u, 1u}) == kUIntMaxValue);
    // Overflow wraps around.
    FND_TEST_TRUE(csum(uint4_t{kUIntMaxValue, 1u, 0u, 0u}) == 0u);
    FND_TEST_TRUE(csum(uint4_t{kUIntMaxValue}) == kUIntMaxValue - 3);
}

void unittests_math_vector_uint4_max()
{
    const uint4_t a{7u, 3u, 4u, 6u};
    FND_TEST_TRUE(
        test_components(max(a, uint4_t{2u, 5u, 4u, 1u}), 7u, 5u, 4u, 6u));
    FND_TEST_TRUE(
        test_components(max(uint4_t{2u, 5u, 4u, 1u}, a), 7u, 5u, 4u, 6u));
    FND_TEST_TRUE(test_components(
        max(uint4_t{4u, 4u, 4u, 4u}, uint4_t{4u, 4u, 4u, 4u}), 4u, 4u, 4u, 4u));
    FND_TEST_TRUE(test_components(max(uint4_t{0u, kUIntMaxValue, 1u, 2u},
                                      uint4_t{kUIntMaxValue, 0u, 1u, 3u}),
        kUIntMaxValue, kUIntMaxValue, 1u, 3u));
    // uint_t on either side is compared with every component.
    FND_TEST_TRUE(test_components(max(a, 5u), 7u, 5u, 5u, 6u));
    FND_TEST_TRUE(test_components(max(5u, a), 7u, 5u, 5u, 6u));
    FND_TEST_TRUE(test_components(max(a, 10u), 10u, 10u, 10u, 10u));
    FND_TEST_TRUE(test_components(max(0u, a), 7u, 3u, 4u, 6u));
}

void unittests_math_vector_uint4_min()
{
    const uint4_t a{7u, 3u, 4u, 6u};
    FND_TEST_TRUE(
        test_components(min(a, uint4_t{2u, 5u, 4u, 1u}), 2u, 3u, 4u, 1u));
    FND_TEST_TRUE(
        test_components(min(uint4_t{2u, 5u, 4u, 1u}, a), 2u, 3u, 4u, 1u));
    FND_TEST_TRUE(test_components(
        min(uint4_t{4u, 4u, 4u, 4u}, uint4_t{4u, 4u, 4u, 4u}), 4u, 4u, 4u, 4u));
    FND_TEST_TRUE(test_components(min(uint4_t{0u, kUIntMaxValue, 1u, 2u},
                                      uint4_t{kUIntMaxValue, 0u, 1u, 3u}),
        0u, 0u, 1u, 2u));
    // uint_t on either side is compared with every component.
    FND_TEST_TRUE(test_components(min(a, 5u), 5u, 3u, 4u, 5u));
    FND_TEST_TRUE(test_components(min(5u, a), 5u, 3u, 4u, 5u));
    FND_TEST_TRUE(test_components(min(a, 0u), 0u, 0u, 0u, 0u));
    FND_TEST_TRUE(test_components(min(kUIntMaxValue, a), 7u, 3u, 4u, 6u));
}

// int4_t and uint4_t must agree wherever int4_t is defined: non-negative inputs
// and no int_t overflow. int4_t results are compared by their bits, so that the
// negative result of 3 - 5 matches the wrapped 3u - 5u.
bool_t same_bits(const int4_t i, const uint4_t u)
{
    return all(bit_cast<uint4_t>(i) == u);
}

void unittests_math_vector_uint4_matches_int4()
{
    const int4_t ia{7, 3, 4, 6};
    const int4_t ib{2, 5, 3, 1};
    const uint4_t ua{7u, 3u, 4u, 6u};
    const uint4_t ub{2u, 5u, 3u, 1u};
    // Shift counts must be in [0, 32), and left shifts must not overflow int_t.
    const int4_t ishift{1, 4, 2, 3};
    const uint4_t ushift{1u, 4u, 2u, 3u};

    // Comparisons.
    FND_TEST_TRUE(all((ia == ib) == (ua == ub)));
    FND_TEST_TRUE(all((ia == 3) == (ua == 3u)));
    FND_TEST_TRUE(all((3 == ia) == (3u == ua)));
    FND_TEST_TRUE(all((ia != ib) == (ua != ub)));
    FND_TEST_TRUE(all((ia != 3) == (ua != 3u)));
    FND_TEST_TRUE(all((3 != ia) == (3u != ua)));
    FND_TEST_TRUE(all((ia < ib) == (ua < ub)));
    FND_TEST_TRUE(all((ia < 3) == (ua < 3u)));
    FND_TEST_TRUE(all((3 < ia) == (3u < ua)));
    FND_TEST_TRUE(all((ia <= ib) == (ua <= ub)));
    FND_TEST_TRUE(all((ia <= 3) == (ua <= 3u)));
    FND_TEST_TRUE(all((3 <= ia) == (3u <= ua)));
    FND_TEST_TRUE(all((ia > ib) == (ua > ub)));
    FND_TEST_TRUE(all((ia > 3) == (ua > 3u)));
    FND_TEST_TRUE(all((3 > ia) == (3u > ua)));
    FND_TEST_TRUE(all((ia >= ib) == (ua >= ub)));
    FND_TEST_TRUE(all((ia >= 3) == (ua >= 3u)));
    FND_TEST_TRUE(all((3 >= ia) == (3u >= ua)));

    // Arithmetic and bit operators.
    FND_TEST_TRUE(same_bits(ia + ib, ua + ub));
    FND_TEST_TRUE(same_bits(ia + 3, ua + 3u));
    FND_TEST_TRUE(same_bits(21 + ib, 21u + ub));
    FND_TEST_TRUE(same_bits(ia - ib, ua - ub));
    FND_TEST_TRUE(same_bits(ia - 3, ua - 3u));
    FND_TEST_TRUE(same_bits(21 - ib, 21u - ub));
    FND_TEST_TRUE(same_bits(ia * ib, ua * ub));
    FND_TEST_TRUE(same_bits(ia * 3, ua * 3u));
    FND_TEST_TRUE(same_bits(21 * ib, 21u * ub));
    FND_TEST_TRUE(same_bits(ia / ib, ua / ub));
    FND_TEST_TRUE(same_bits(ia / 3, ua / 3u));
    FND_TEST_TRUE(same_bits(21 / ib, 21u / ub));
    FND_TEST_TRUE(same_bits(ia % ib, ua % ub));
    FND_TEST_TRUE(same_bits(ia % 3, ua % 3u));
    FND_TEST_TRUE(same_bits(21 % ib, 21u % ub));
    FND_TEST_TRUE(same_bits(ia & ib, ua & ub));
    FND_TEST_TRUE(same_bits(ia & 3, ua & 3u));
    FND_TEST_TRUE(same_bits(21 & ib, 21u & ub));
    FND_TEST_TRUE(same_bits(ia | ib, ua | ub));
    FND_TEST_TRUE(same_bits(ia | 3, ua | 3u));
    FND_TEST_TRUE(same_bits(21 | ib, 21u | ub));
    FND_TEST_TRUE(same_bits(ia ^ ib, ua ^ ub));
    FND_TEST_TRUE(same_bits(ia ^ 3, ua ^ 3u));
    FND_TEST_TRUE(same_bits(21 ^ ib, 21u ^ ub));
    FND_TEST_TRUE(same_bits(ia << ishift, ua << ushift));
    FND_TEST_TRUE(same_bits(ia << 2, ua << 2u));
    FND_TEST_TRUE(same_bits(21 << ishift, 21u << ushift));
    FND_TEST_TRUE(same_bits(ia >> ishift, ua >> ushift));
    FND_TEST_TRUE(same_bits(ia >> 2, ua >> 2u));
    FND_TEST_TRUE(same_bits(21 >> ishift, 21u >> ushift));
    FND_TEST_TRUE(same_bits(~ia, ~ua));

    // Compound assignments.
    int4_t ic;
    uint4_t uc;
    ic = ia;
    uc = ua;
    FND_TEST_TRUE(same_bits(ic += ib, uc += ub));
    ic = ia;
    uc = ua;
    FND_TEST_TRUE(same_bits(ic += 3, uc += 3u));
    ic = ia;
    uc = ua;
    FND_TEST_TRUE(same_bits(ic -= ib, uc -= ub));
    ic = ia;
    uc = ua;
    FND_TEST_TRUE(same_bits(ic -= 3, uc -= 3u));
    ic = ia;
    uc = ua;
    FND_TEST_TRUE(same_bits(ic *= ib, uc *= ub));
    ic = ia;
    uc = ua;
    FND_TEST_TRUE(same_bits(ic *= 3, uc *= 3u));
    ic = ia;
    uc = ua;
    FND_TEST_TRUE(same_bits(ic /= ib, uc /= ub));
    ic = ia;
    uc = ua;
    FND_TEST_TRUE(same_bits(ic /= 3, uc /= 3u));
    ic = ia;
    uc = ua;
    FND_TEST_TRUE(same_bits(ic %= ib, uc %= ub));
    ic = ia;
    uc = ua;
    FND_TEST_TRUE(same_bits(ic %= 3, uc %= 3u));
    ic = ia;
    uc = ua;
    FND_TEST_TRUE(same_bits(ic &= ib, uc &= ub));
    ic = ia;
    uc = ua;
    FND_TEST_TRUE(same_bits(ic &= 3, uc &= 3u));
    ic = ia;
    uc = ua;
    FND_TEST_TRUE(same_bits(ic |= ib, uc |= ub));
    ic = ia;
    uc = ua;
    FND_TEST_TRUE(same_bits(ic |= 3, uc |= 3u));
    ic = ia;
    uc = ua;
    FND_TEST_TRUE(same_bits(ic ^= ib, uc ^= ub));
    ic = ia;
    uc = ua;
    FND_TEST_TRUE(same_bits(ic ^= 3, uc ^= 3u));
    ic = ia;
    uc = ua;
    FND_TEST_TRUE(same_bits(ic <<= ishift, uc <<= ushift));
    ic = ia;
    uc = ua;
    FND_TEST_TRUE(same_bits(ic <<= 2, uc <<= 2u));
    ic = ia;
    uc = ua;
    FND_TEST_TRUE(same_bits(ic >>= ishift, uc >>= ushift));
    ic = ia;
    uc = ua;
    FND_TEST_TRUE(same_bits(ic >>= 2, uc >>= 2u));

    // Functions.
    FND_TEST_TRUE(same_bits(min(ia, ib), min(ua, ub)));
    FND_TEST_TRUE(same_bits(min(ia, 4), min(ua, 4u)));
    FND_TEST_TRUE(same_bits(min(4, ia), min(4u, ua)));
    FND_TEST_TRUE(same_bits(max(ia, ib), max(ua, ub)));
    FND_TEST_TRUE(same_bits(max(ia, 4), max(ua, 4u)));
    FND_TEST_TRUE(same_bits(max(4, ia), max(4u, ua)));
    FND_TEST_TRUE(same_bits(clamp(ia, int4_t{2, 4, 1, 2}, int4_t{5, 6, 3, 5}),
        clamp(ua, uint4_t{2u, 4u, 1u, 2u}, uint4_t{5u, 6u, 3u, 5u})));
    FND_TEST_TRUE(same_bits(clamp(ia, int4_t{2, 4, 1, 2}, 5),
        clamp(ua, uint4_t{2u, 4u, 1u, 2u}, 5u)));
    FND_TEST_TRUE(same_bits(clamp(ia, 4, int4_t{5, 6, 7, 5}),
        clamp(ua, 4u, uint4_t{5u, 6u, 7u, 5u})));
    FND_TEST_TRUE(same_bits(clamp(ia, 4, 5), clamp(ua, 4u, 5u)));
    FND_TEST_TRUE(cmin(ia) == static_cast<int_t>(cmin(ua)));
    FND_TEST_TRUE(cmax(ia) == static_cast<int_t>(cmax(ua)));
    FND_TEST_TRUE(csum(ia) == static_cast<int_t>(csum(ua)));
    FND_TEST_TRUE(cmul(ia) == static_cast<int_t>(cmul(ua)));
}

void unittests_math_vector_uint4()
{
    unittests_math_vector_uint4_type();
    unittests_math_vector_uint4_constants();
    unittests_math_vector_uint4_constructors();
    unittests_math_vector_uint4_subscript_operator();
    unittests_math_vector_uint4_increment_operators();
    unittests_math_vector_uint4_decrement_operators();
    unittests_math_vector_uint4_bitwise_not_operator();
    unittests_math_vector_uint4_compound_assignment_operators();
    unittests_math_vector_uint4_compound_assignment_matches_operators();
    unittests_math_vector_uint4_equality_operators();
    unittests_math_vector_uint4_relational_operators();
    unittests_math_vector_uint4_bitwise_and_operator();
    unittests_math_vector_uint4_multiplication_operator();
    unittests_math_vector_uint4_addition_operator();
    unittests_math_vector_uint4_subtraction_operator();
    unittests_math_vector_uint4_modulo_operator();
    unittests_math_vector_uint4_division_operator();
    unittests_math_vector_uint4_shift_left_operator();
    unittests_math_vector_uint4_shift_right_operator();
    unittests_math_vector_uint4_bitwise_xor_operator();
    unittests_math_vector_uint4_bitwise_or_operator();
    unittests_math_vector_uint4_clamp();
    unittests_math_vector_uint4_cmax();
    unittests_math_vector_uint4_cmin();
    unittests_math_vector_uint4_cmul();
    unittests_math_vector_uint4_csum();
    unittests_math_vector_uint4_max();
    unittests_math_vector_uint4_min();
    unittests_math_vector_uint4_matches_int4();
}

} // namespace fnd::unittests
