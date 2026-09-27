module;
#include "foundation/unittests.h"


export module unittests.math:vector_uint2;
import foundation.core;
import foundation.math;

namespace fnd::unittests {

export void unittests_math_vector_uint2();

// ---------------------------------------------------------------------------
// uint2_t
// ---------------------------------------------------------------------------

constexpr bool_t test_components(
    const uint2_t v, const uint_t x, const uint_t y)
{
    return v.x == x && v.y == y;
}

void unittests_math_vector_uint2_type()
{
    static_assert(PodType<uint2_t>);
    static_assert(sizeof(uint2_t) == 2 * sizeof(uint_t));
    // The ctor(uint_t) and ctor(bool2_t) are explicit.
    static_assert(!is_convertible<uint_t, uint2_t>());
    static_assert(!is_convertible<int_t, uint2_t>());
    static_assert(!is_convertible<bool2_t, uint2_t>());
}

void unittests_math_vector_uint2_constructors()
{
    FND_TEST_TRUE(test_components(uint2_t{}, 0u, 0u));
    FND_TEST_TRUE(test_components(uint2_t{5u}, 5u, 5u));
    FND_TEST_TRUE(test_components(uint2_t{3u, 4u}, 3u, 4u));
    FND_TEST_TRUE(
        test_components(uint2_t{0u, kUIntMaxValue}, 0u, kUIntMaxValue));
    // From a bool2_t: true is 1, false is 0.
    FND_TEST_TRUE(test_components(uint2_t{bool2_t{true, false}}, 1u, 0u));
    FND_TEST_TRUE(test_components(uint2_t{bool2_t{false, true}}, 0u, 1u));
}

void unittests_math_vector_uint2_subscript_operator()
{
    const uint2_t v{3u, 4u};
    FND_TEST_TRUE(v[0] == 3u);
    FND_TEST_TRUE(v[1] == 4u);

    // The non-const overload returns a reference into the vector itself.
    uint2_t w;
    w[1] = 9u;
    FND_TEST_TRUE(test_components(w, 0u, 9u));

    w[0] = kUIntMaxValue;
    FND_TEST_TRUE(test_components(w, kUIntMaxValue, 9u));
}

void unittests_math_vector_uint2_increment_operators()
{
    // kUIntMaxValue wraps around to 0.
    uint2_t v{1u, kUIntMaxValue};
    FND_TEST_TRUE(test_components(++v, 2u, 0u));
    FND_TEST_TRUE(test_components(v, 2u, 0u));

    // Postfix returns the value before the increment.
    FND_TEST_TRUE(test_components(v++, 2u, 0u));
    FND_TEST_TRUE(test_components(v, 3u, 1u));
}

void unittests_math_vector_uint2_decrement_operators()
{
    // 0 wraps around to kUIntMaxValue.
    uint2_t v{1u, 0u};
    FND_TEST_TRUE(test_components(--v, 0u, kUIntMaxValue));
    FND_TEST_TRUE(test_components(v, 0u, kUIntMaxValue));

    // Postfix returns the value before the decrement.
    FND_TEST_TRUE(test_components(v--, 0u, kUIntMaxValue));
    FND_TEST_TRUE(test_components(v, kUIntMaxValue, kUIntMaxValue - 1));
}

void unittests_math_vector_uint2_equality_operators()
{
    const uint2_t a{7u, 3u};
    FND_TEST_TRUE(all((a == uint2_t{7u, 3u}) == bool2_t{true, true}));
    FND_TEST_TRUE(all((a == uint2_t{7u, 5u}) == bool2_t{true, false}));
    FND_TEST_TRUE(all((a == uint2_t{2u, 5u}) == bool2_t{false, false}));
    FND_TEST_TRUE(all((a == 7u) == bool2_t{true, false}));
    FND_TEST_TRUE(all((3u == a) == bool2_t{false, true}));
    FND_TEST_TRUE(all((a == 7) == bool2_t{true, false}));
    FND_TEST_TRUE(all((3 == a) == bool2_t{false, true}));

    FND_TEST_TRUE(all((a != uint2_t{7u, 3u}) == bool2_t{false, false}));
    FND_TEST_TRUE(all((a != uint2_t{7u, 5u}) == bool2_t{false, true}));
    FND_TEST_TRUE(all((a != uint2_t{2u, 5u}) == bool2_t{true, true}));
    FND_TEST_TRUE(all((a != 7u) == bool2_t{false, true}));
    FND_TEST_TRUE(all((3u != a) == bool2_t{true, false}));
    FND_TEST_TRUE(all((a != 7) == bool2_t{false, true}));
    FND_TEST_TRUE(all((3 != a) == bool2_t{true, false}));
}

void unittests_math_vector_uint2_relational_operators()
{
    const uint2_t a{7u, 3u};
    const uint2_t b{2u, 5u};
    const uint2_t c{7u, 5u};

    FND_TEST_TRUE(all((a < b) == bool2_t{false, true}));
    FND_TEST_TRUE(all((a < c) == bool2_t{false, true}));
    FND_TEST_TRUE(all((a < 5u) == bool2_t{false, true}));
    FND_TEST_TRUE(all((5u < a) == bool2_t{true, false}));
    FND_TEST_TRUE(all((a < 5) == bool2_t{false, true}));
    FND_TEST_TRUE(all((5 < a) == bool2_t{true, false}));

    FND_TEST_TRUE(all((a <= b) == bool2_t{false, true}));
    FND_TEST_TRUE(all((a <= c) == bool2_t{true, true}));
    FND_TEST_TRUE(all((a <= 3u) == bool2_t{false, true}));
    FND_TEST_TRUE(all((7u <= a) == bool2_t{true, false}));
    FND_TEST_TRUE(all((a <= 3) == bool2_t{false, true}));
    FND_TEST_TRUE(all((7 <= a) == bool2_t{true, false}));

    FND_TEST_TRUE(all((a > b) == bool2_t{true, false}));
    FND_TEST_TRUE(all((a > c) == bool2_t{false, false}));
    FND_TEST_TRUE(all((a > 5u) == bool2_t{true, false}));
    FND_TEST_TRUE(all((5u > a) == bool2_t{false, true}));
    FND_TEST_TRUE(all((a > 5) == bool2_t{true, false}));
    FND_TEST_TRUE(all((5 > a) == bool2_t{false, true}));

    FND_TEST_TRUE(all((a >= b) == bool2_t{true, false}));
    FND_TEST_TRUE(all((a >= c) == bool2_t{true, false}));
    FND_TEST_TRUE(all((a >= 7u) == bool2_t{true, false}));
    FND_TEST_TRUE(all((3u >= a) == bool2_t{false, true}));
    FND_TEST_TRUE(all((a >= 7) == bool2_t{true, false}));
    FND_TEST_TRUE(all((3 >= a) == bool2_t{false, true}));
}

void unittests_math_vector_uint2_addition_operator()
{
    const uint2_t a{7u, 3u};
    FND_TEST_TRUE(test_components(a + uint2_t{2u, 5u}, 9u, 8u));
    FND_TEST_TRUE(test_components(a + 1u, 8u, 4u));
    FND_TEST_TRUE(test_components(1u + a, 8u, 4u));
    FND_TEST_TRUE(test_components(a + 1, 8u, 4u));
    FND_TEST_TRUE(test_components(1 + a, 8u, 4u));
    // Overflow wraps around.
    FND_TEST_TRUE(
        test_components(uint2_t{kUIntMaxValue, 1u} + uint2_t{1u, 1u}, 0u, 2u));
    FND_TEST_TRUE(test_components(uint2_t{kUIntMaxValue} + 2u, 1u, 1u));
}

void unittests_math_vector_uint2_subtraction_operator()
{
    const uint2_t a{7u, 3u};
    FND_TEST_TRUE(test_components(a - uint2_t{2u, 1u}, 5u, 2u));
    FND_TEST_TRUE(test_components(a - 1u, 6u, 2u));
    FND_TEST_TRUE(test_components(10u - a, 3u, 7u));
    FND_TEST_TRUE(test_components(a - 1, 6u, 2u));
    FND_TEST_TRUE(test_components(10 - a, 3u, 7u));
    // Overflow wraps around.
    FND_TEST_TRUE(test_components(a - uint2_t{2u, 5u}, 5u, kUIntMaxValue - 1));
    FND_TEST_TRUE(test_components(uint2_t{0u, 5u} - 1u, kUIntMaxValue, 4u));
}

void unittests_math_vector_uint2_multiplication_operator()
{
    const uint2_t a{7u, 3u};
    FND_TEST_TRUE(test_components(a * uint2_t{2u, 5u}, 14u, 15u));
    FND_TEST_TRUE(test_components(a * 2u, 14u, 6u));
    FND_TEST_TRUE(test_components(2u * a, 14u, 6u));
    FND_TEST_TRUE(test_components(a * 2, 14u, 6u));
    FND_TEST_TRUE(test_components(2 * a, 14u, 6u));
    // Overflow wraps around.
    FND_TEST_TRUE(test_components(uint2_t{0x80000000u, 3u} * 2u, 0u, 6u));
    FND_TEST_TRUE(test_components(
        uint2_t{0x10000u, 0x10000u} * uint2_t{0x10000u, 2u}, 0u, 0x20000u));
}

void unittests_math_vector_uint2_division_operator()
{
    const uint2_t a{7u, 3u};
    FND_TEST_TRUE(test_components(a / uint2_t{2u, 5u}, 3u, 0u));
    FND_TEST_TRUE(test_components(a / 2u, 3u, 1u));
    FND_TEST_TRUE(test_components(21u / uint2_t{2u, 5u}, 10u, 4u));
    FND_TEST_TRUE(test_components(a / 2, 3u, 1u));
    FND_TEST_TRUE(test_components(21 / uint2_t{2u, 5u}, 10u, 4u));
    FND_TEST_TRUE(test_components(
        uint2_t{kUIntMaxValue, 9u} / uint2_t{1u, 3u}, kUIntMaxValue, 3u));
}

void unittests_math_vector_uint2_modulo_operator()
{
    const uint2_t a{7u, 3u};
    FND_TEST_TRUE(test_components(a % uint2_t{2u, 5u}, 1u, 3u));
    FND_TEST_TRUE(test_components(a % 2u, 1u, 1u));
    FND_TEST_TRUE(test_components(21u % uint2_t{2u, 5u}, 1u, 1u));
    FND_TEST_TRUE(test_components(a % 2, 1u, 1u));
    FND_TEST_TRUE(test_components(21 % uint2_t{2u, 5u}, 1u, 1u));
    FND_TEST_TRUE(
        test_components(uint2_t{kUIntMaxValue, 9u} % uint2_t{2u, 4u}, 1u, 1u));
}

void unittests_math_vector_uint2_bitwise_not_operator()
{
    FND_TEST_TRUE(
        test_components(~uint2_t{0u, 5u}, kUIntMaxValue, kUIntMaxValue - 5));
    FND_TEST_TRUE(
        test_components(~uint2_t{kUIntMaxValue, 0x80000000u}, 0u, 0x7FFFFFFFu));
}

void unittests_math_vector_uint2_bitwise_and_operator()
{
    const uint2_t a{0b1100u, 0b1010u};
    FND_TEST_TRUE(
        test_components(a & uint2_t{0b1010u, 0b0110u}, 0b1000u, 0b0010u));
    FND_TEST_TRUE(test_components(a & 0b0110u, 0b0100u, 0b0010u));
    FND_TEST_TRUE(test_components(0b0110u & a, 0b0100u, 0b0010u));
    FND_TEST_TRUE(test_components(a & 0b0110, 0b0100u, 0b0010u));
    FND_TEST_TRUE(test_components(0b0110 & a, 0b0100u, 0b0010u));
    FND_TEST_TRUE(test_components(
        uint2_t{kUIntMaxValue, 0x80000000u} & 0xFFu, 0xFFu, 0u));
}

void unittests_math_vector_uint2_bitwise_or_operator()
{
    const uint2_t a{0b1100u, 0b1010u};
    FND_TEST_TRUE(
        test_components(a | uint2_t{0b1010u, 0b0110u}, 0b1110u, 0b1110u));
    FND_TEST_TRUE(test_components(a | 0b0001u, 0b1101u, 0b1011u));
    FND_TEST_TRUE(test_components(0b0001u | a, 0b1101u, 0b1011u));
    FND_TEST_TRUE(test_components(a | 0b0001, 0b1101u, 0b1011u));
    FND_TEST_TRUE(test_components(0b0001 | a, 0b1101u, 0b1011u));
    FND_TEST_TRUE(test_components(
        uint2_t{0u, 0x7FFFFFFFu} | 0x80000000u, 0x80000000u, kUIntMaxValue));
}

void unittests_math_vector_uint2_bitwise_xor_operator()
{
    const uint2_t a{0b1100u, 0b1010u};
    FND_TEST_TRUE(
        test_components(a ^ uint2_t{0b1010u, 0b0110u}, 0b0110u, 0b1100u));
    FND_TEST_TRUE(test_components(a ^ 0b1111u, 0b0011u, 0b0101u));
    FND_TEST_TRUE(test_components(0b1111u ^ a, 0b0011u, 0b0101u));
    FND_TEST_TRUE(test_components(a ^ 0b1111, 0b0011u, 0b0101u));
    FND_TEST_TRUE(test_components(0b1111 ^ a, 0b0011u, 0b0101u));
    FND_TEST_TRUE(test_components(a ^ a, 0u, 0u));
}

void unittests_math_vector_uint2_shift_left_operator()
{
    FND_TEST_TRUE(test_components(uint2_t{1u, 3u} << uint2_t{4u, 1u}, 16u, 6u));
    FND_TEST_TRUE(test_components(uint2_t{1u, 3u} << 2u, 4u, 12u));
    FND_TEST_TRUE(test_components(1u << uint2_t{0u, 31u}, 1u, 0x80000000u));
    FND_TEST_TRUE(test_components(uint2_t{1u, 3u} << 2, 4u, 12u));
    FND_TEST_TRUE(test_components(1 << uint2_t{0u, 31u}, 1u, 0x80000000u));
    // Bits shifted out are discarded.
    FND_TEST_TRUE(test_components(uint2_t{0x80000000u, 3u} << 1u, 0u, 6u));
}

void unittests_math_vector_uint2_shift_right_operator()
{
    FND_TEST_TRUE(test_components(uint2_t{16u, 6u} >> uint2_t{4u, 1u}, 1u, 3u));
    FND_TEST_TRUE(test_components(uint2_t{16u, 6u} >> 1u, 8u, 3u));
    FND_TEST_TRUE(test_components(256u >> uint2_t{4u, 8u}, 16u, 1u));
    FND_TEST_TRUE(test_components(uint2_t{16u, 6u} >> 1, 8u, 3u));
    FND_TEST_TRUE(test_components(256 >> uint2_t{4u, 8u}, 16u, 1u));
    // Zeros are shifted in, whatever the top bit is.
    FND_TEST_TRUE(
        test_components(uint2_t{0x80000000u, 8u} >> 1u, 0x40000000u, 4u));
    FND_TEST_TRUE(test_components(uint2_t{kUIntMaxValue, 1u} >> 31u, 1u, 0u));
}

void unittests_math_vector_uint2_compound_assignment_operators()
{
    uint2_t v{7u, 3u};

    // Each operator returns a reference to its left operand.
    FND_TEST_TRUE(&(v += uint2_t{1u, 2u}) == &v);
    FND_TEST_TRUE(test_components(v, 8u, 5u));
    FND_TEST_TRUE(test_components(v += 2u, 10u, 7u));
    FND_TEST_TRUE(test_components(v += 1, 11u, 8u));

    FND_TEST_TRUE(test_components(v -= uint2_t{4u, 3u}, 7u, 5u));
    FND_TEST_TRUE(test_components(v -= 1u, 6u, 4u));
    FND_TEST_TRUE(test_components(v -= 1, 5u, 3u));

    FND_TEST_TRUE(test_components(v *= uint2_t{2u, 3u}, 10u, 9u));
    FND_TEST_TRUE(test_components(v *= 3u, 30u, 27u));
    FND_TEST_TRUE(test_components(v *= 2, 60u, 54u));

    FND_TEST_TRUE(test_components(v /= uint2_t{3u, 2u}, 20u, 27u));
    FND_TEST_TRUE(test_components(v /= 2u, 10u, 13u));
    FND_TEST_TRUE(test_components(v /= 3, 3u, 4u));

    FND_TEST_TRUE(test_components(v %= uint2_t{2u, 3u}, 1u, 1u));
    v = uint2_t{7u, 9u};
    FND_TEST_TRUE(test_components(v %= 4u, 3u, 1u));
    v = uint2_t{7u, 9u};
    FND_TEST_TRUE(test_components(v %= 5, 2u, 4u));

    v = uint2_t{0b1100u, 0b1010u};
    FND_TEST_TRUE(
        test_components(v &= uint2_t{0b1010u, 0b0110u}, 0b1000u, 0b0010u));
    FND_TEST_TRUE(test_components(v &= 0b1010u, 0b1000u, 0b0010u));
    FND_TEST_TRUE(test_components(v &= 0b1000, 0b1000u, 0u));

    FND_TEST_TRUE(
        test_components(v |= uint2_t{0b0001u, 0b0010u}, 0b1001u, 0b0010u));
    FND_TEST_TRUE(test_components(v |= 0b0100u, 0b1101u, 0b0110u));
    FND_TEST_TRUE(test_components(v |= 0b10000, 0b11101u, 0b10110u));

    FND_TEST_TRUE(test_components(v ^= uint2_t{0b11101u, 0u}, 0u, 0b10110u));
    FND_TEST_TRUE(test_components(v ^= 0b0011u, 0b0011u, 0b10101u));
    FND_TEST_TRUE(test_components(v ^= 0b0001, 0b0010u, 0b10100u));

    FND_TEST_TRUE(test_components(v <<= uint2_t{1u, 2u}, 0b0100u, 0b1010000u));
    FND_TEST_TRUE(test_components(v <<= 1u, 0b1000u, 0b10100000u));
    FND_TEST_TRUE(test_components(v <<= 1, 0b10000u, 0b101000000u));

    FND_TEST_TRUE(test_components(v >>= uint2_t{2u, 3u}, 0b100u, 0b101000u));
    FND_TEST_TRUE(test_components(v >>= 1u, 0b10u, 0b10100u));
    FND_TEST_TRUE(test_components(v >>= 1, 0b1u, 0b1010u));
}

void unittests_math_vector_uint2_compound_assignment_matches_operators()
{
    // a op= b must give the same result as a op b, for every right-hand side.
    const uint2_t a{7u, 3u};
    const uint2_t b{2u, 5u};
    const uint_t uval{3u};
    const int_t ival{3};
    // Shift counts must be in [0, 32).
    const uint2_t shift{1u, 4u};
    const uint_t ushift{2u};
    const int_t ishift{2};
    uint2_t c;

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

void unittests_math_vector_uint2_min()
{
    const uint2_t a{7u, 3u};
    FND_TEST_TRUE(test_components(min(a, uint2_t{2u, 5u}), 2u, 3u));
    FND_TEST_TRUE(test_components(min(uint2_t{2u, 5u}, a), 2u, 3u));
    FND_TEST_TRUE(
        test_components(min(uint2_t{4u, 4u}, uint2_t{4u, 4u}), 4u, 4u));
    FND_TEST_TRUE(test_components(
        min(uint2_t{0u, kUIntMaxValue}, uint2_t{kUIntMaxValue, 0u}), 0u, 0u));
    // uint_t on either side is compared with every component.
    FND_TEST_TRUE(test_components(min(a, 5u), 5u, 3u));
    FND_TEST_TRUE(test_components(min(5u, a), 5u, 3u));
    FND_TEST_TRUE(test_components(min(a, 0u), 0u, 0u));
    FND_TEST_TRUE(test_components(min(kUIntMaxValue, a), 7u, 3u));
}

void unittests_math_vector_uint2_max()
{
    const uint2_t a{7u, 3u};
    FND_TEST_TRUE(test_components(max(a, uint2_t{2u, 5u}), 7u, 5u));
    FND_TEST_TRUE(test_components(max(uint2_t{2u, 5u}, a), 7u, 5u));
    FND_TEST_TRUE(
        test_components(max(uint2_t{4u, 4u}, uint2_t{4u, 4u}), 4u, 4u));
    FND_TEST_TRUE(test_components(
        max(uint2_t{0u, kUIntMaxValue}, uint2_t{kUIntMaxValue, 0u}),
        kUIntMaxValue, kUIntMaxValue));
    // uint_t on either side is compared with every component.
    FND_TEST_TRUE(test_components(max(a, 5u), 7u, 5u));
    FND_TEST_TRUE(test_components(max(5u, a), 7u, 5u));
    FND_TEST_TRUE(test_components(max(a, 10u), 10u, 10u));
    FND_TEST_TRUE(test_components(max(0u, a), 7u, 3u));
}

void unittests_math_vector_uint2_clamp()
{
    const uint2_t lower{0u, 2u};
    const uint2_t upper{10u, 5u};
    // Each component is clamped to its own bounds.
    FND_TEST_TRUE(
        test_components(clamp(uint2_t{3u, 3u}, lower, upper), 3u, 3u));
    FND_TEST_TRUE(
        test_components(clamp(uint2_t{0u, 1u}, lower, upper), 0u, 2u));
    FND_TEST_TRUE(
        test_components(clamp(uint2_t{20u, 6u}, lower, upper), 10u, 5u));
    FND_TEST_TRUE(
        test_components(clamp(uint2_t{0u, 5u}, lower, upper), 0u, 5u));
    FND_TEST_TRUE(
        test_components(clamp(uint2_t{20u, 1u}, lower, upper), 10u, 2u));
    FND_TEST_TRUE(test_components(
        clamp(uint2_t{9u, 9u}, uint2_t{3u, 3u}, uint2_t{3u, 3u}), 3u, 3u));

    // uint_t bounds apply to every component.
    FND_TEST_TRUE(test_components(clamp(uint2_t{3u, 9u}, 2u, 5u), 3u, 5u));
    FND_TEST_TRUE(test_components(clamp(uint2_t{0u, 20u}, 2u, 10u), 2u, 10u));
    FND_TEST_TRUE(test_components(clamp(uint2_t{2u, 10u}, 2u, 10u), 2u, 10u));
    FND_TEST_TRUE(test_components(clamp(uint2_t{9u, 0u}, 3u, 3u), 3u, 3u));

    // uint2_t lower bound, uint_t upper bound.
    FND_TEST_TRUE(
        test_components(clamp(uint2_t{0u, 0u}, uint2_t{1u, 2u}, 5u), 1u, 2u));
    FND_TEST_TRUE(
        test_components(clamp(uint2_t{20u, 3u}, uint2_t{1u, 2u}, 5u), 5u, 3u));
    FND_TEST_TRUE(
        test_components(clamp(uint2_t{9u, 0u}, uint2_t{3u, 5u}, 5u), 5u, 5u));

    // uint_t lower bound, uint2_t upper bound.
    FND_TEST_TRUE(
        test_components(clamp(uint2_t{0u, 0u}, 1u, uint2_t{10u, 5u}), 1u, 1u));
    FND_TEST_TRUE(test_components(
        clamp(uint2_t{20u, 3u}, 1u, uint2_t{10u, 5u}), 10u, 3u));
    FND_TEST_TRUE(
        test_components(clamp(uint2_t{9u, 0u}, 3u, uint2_t{3u, 7u}), 3u, 3u));
}

void unittests_math_vector_uint2_cmin()
{
    FND_TEST_TRUE(cmin(uint2_t{7u, 3u}) == 3u);
    FND_TEST_TRUE(cmin(uint2_t{3u, 7u}) == 3u);
    FND_TEST_TRUE(cmin(uint2_t{4u, 4u}) == 4u);
    FND_TEST_TRUE(cmin(uint2_t{kUIntMaxValue, 0u}) == 0u);
}

void unittests_math_vector_uint2_cmax()
{
    FND_TEST_TRUE(cmax(uint2_t{7u, 3u}) == 7u);
    FND_TEST_TRUE(cmax(uint2_t{3u, 7u}) == 7u);
    FND_TEST_TRUE(cmax(uint2_t{4u, 4u}) == 4u);
    FND_TEST_TRUE(cmax(uint2_t{0u, kUIntMaxValue}) == kUIntMaxValue);
}

void unittests_math_vector_uint2_csum()
{
    FND_TEST_TRUE(csum(uint2_t{7u, 3u}) == 10u);
    FND_TEST_TRUE(csum(uint2_t{0u, 0u}) == 0u);
    FND_TEST_TRUE(csum(uint2_t{kUIntMaxValue - 1, 1u}) == kUIntMaxValue);
    // Overflow wraps around.
    FND_TEST_TRUE(csum(uint2_t{kUIntMaxValue, 1u}) == 0u);
    FND_TEST_TRUE(
        csum(uint2_t{kUIntMaxValue, kUIntMaxValue}) == kUIntMaxValue - 1);
}

void unittests_math_vector_uint2_cmul()
{
    FND_TEST_TRUE(cmul(uint2_t{7u, 3u}) == 21u);
    FND_TEST_TRUE(cmul(uint2_t{0u, kUIntMaxValue}) == 0u);
    // 65535 * 65537 is 2^32 - 1.
    FND_TEST_TRUE(cmul(uint2_t{65535u, 65537u}) == kUIntMaxValue);
    // Overflow wraps around.
    FND_TEST_TRUE(cmul(uint2_t{0x10000u, 0x10000u}) == 0u);
    FND_TEST_TRUE(cmul(uint2_t{0x80000000u, 3u}) == 0x80000000u);
}


// int2_t and uint2_t must agree wherever int2_t is defined: non-negative inputs
// and no int_t overflow. int2_t results are compared by their bits, so that the
// negative result of 3 - 5 matches the wrapped 3u - 5u.
bool_t same_bits(const int2_t i, const uint2_t u)
{
    return all(bit_cast<uint2_t>(i) == u);
}

void unittests_math_vector_uint2_matches_int2()
{
    const int2_t ia{7, 3};
    const int2_t ib{2, 5};
    const uint2_t ua{7u, 3u};
    const uint2_t ub{2u, 5u};
    // Shift counts must be in [0, 32), and left shifts must not overflow int_t.
    const int2_t ishift{1, 4};
    const uint2_t ushift{1u, 4u};

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
    int2_t ic;
    uint2_t uc;
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
    FND_TEST_TRUE(same_bits(clamp(ia, int2_t{2, 4}, int2_t{5, 6}),
        clamp(ua, uint2_t{2u, 4u}, uint2_t{5u, 6u})));
    FND_TEST_TRUE(
        same_bits(clamp(ia, int2_t{2, 4}, 5), clamp(ua, uint2_t{2u, 4u}, 5u)));
    FND_TEST_TRUE(
        same_bits(clamp(ia, 4, int2_t{5, 6}), clamp(ua, 4u, uint2_t{5u, 6u})));
    FND_TEST_TRUE(same_bits(clamp(ia, 4, 5), clamp(ua, 4u, 5u)));
    FND_TEST_TRUE(cmin(ia) == static_cast<int_t>(cmin(ua)));
    FND_TEST_TRUE(cmax(ia) == static_cast<int_t>(cmax(ua)));
    FND_TEST_TRUE(csum(ia) == static_cast<int_t>(csum(ua)));
    FND_TEST_TRUE(cmul(ia) == static_cast<int_t>(cmul(ua)));
}

void unittests_math_vector_uint2()
{
    unittests_math_vector_uint2_type();
    unittests_math_vector_uint2_constructors();
    unittests_math_vector_uint2_subscript_operator();
    unittests_math_vector_uint2_increment_operators();
    unittests_math_vector_uint2_decrement_operators();
    unittests_math_vector_uint2_equality_operators();
    unittests_math_vector_uint2_relational_operators();
    unittests_math_vector_uint2_addition_operator();
    unittests_math_vector_uint2_subtraction_operator();
    unittests_math_vector_uint2_multiplication_operator();
    unittests_math_vector_uint2_division_operator();
    unittests_math_vector_uint2_modulo_operator();
    unittests_math_vector_uint2_bitwise_not_operator();
    unittests_math_vector_uint2_bitwise_and_operator();
    unittests_math_vector_uint2_bitwise_or_operator();
    unittests_math_vector_uint2_bitwise_xor_operator();
    unittests_math_vector_uint2_shift_left_operator();
    unittests_math_vector_uint2_shift_right_operator();
    unittests_math_vector_uint2_compound_assignment_operators();
    unittests_math_vector_uint2_compound_assignment_matches_operators();
    unittests_math_vector_uint2_min();
    unittests_math_vector_uint2_max();
    unittests_math_vector_uint2_clamp();
    unittests_math_vector_uint2_cmin();
    unittests_math_vector_uint2_cmax();
    unittests_math_vector_uint2_csum();
    unittests_math_vector_uint2_cmul();
    unittests_math_vector_uint2_matches_int2();
}

} // namespace fnd::unittests
