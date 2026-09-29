module;
#include "foundation/unittests.h"


export module unittests.math:vector_uint3;
import foundation.core;
import foundation.math;

namespace fnd::unittests {

export void unittests_math_vector_uint3();

constexpr bool_t test_components(
    const uint3_t v, const uint_t x, const uint_t y, const uint_t z)
{
    return v.x == x && v.y == y && v.z == z;
}

void unittests_math_vector_uint3_type()
{
    static_assert(PodType<uint3_t>);
    static_assert(sizeof(uint3_t) == 3 * sizeof(uint_t));
    // The ctor(uint_t) is explicit.
    static_assert(!is_convertible<uint_t, uint3_t>());
    static_assert(!is_convertible<int_t, uint3_t>());
}

void unittests_math_vector_uint3_constants()
{
    FND_TEST_TRUE(test_components(uint3_t::kZero, 0u, 0u, 0u));
    FND_TEST_TRUE(test_components(uint3_t::kUnitX, 1u, 0u, 0u));
    FND_TEST_TRUE(test_components(uint3_t::kUnitY, 0u, 1u, 0u));
    FND_TEST_TRUE(test_components(uint3_t::kUnitZ, 0u, 0u, 1u));
    FND_TEST_TRUE(all(uint3_t::kZero == uint3_t{}));
    FND_TEST_TRUE(all(uint3_t::kUnitX + uint3_t::kUnitY
        + uint3_t::kUnitZ == uint3_t{1u}));
    // The constants are usable in constant expressions.
    static_assert(uint3_t::kUnitZ.z == 1u);
}

void unittests_math_vector_uint3_constructors()
{
    FND_TEST_TRUE(test_components(uint3_t{}, 0u, 0u, 0u));
    FND_TEST_TRUE(test_components(uint3_t{5u}, 5u, 5u, 5u));
    FND_TEST_TRUE(test_components(uint3_t{3u, 4u, 6u}, 3u, 4u, 6u));
    FND_TEST_TRUE(
        test_components(uint3_t{0u, kUIntMaxValue, 1u}, 0u, kUIntMaxValue, 1u));
}

void unittests_math_vector_uint3_subscript_operator()
{
    const uint3_t v{3u, 4u, 6u};
    FND_TEST_TRUE(v[0] == 3u);
    FND_TEST_TRUE(v[1] == 4u);
    FND_TEST_TRUE(v[2] == 6u);

    // The non-const overload returns a reference into the vector itself.
    uint3_t w;
    w[2] = 9u;
    FND_TEST_TRUE(test_components(w, 0u, 0u, 9u));

    w[0] = kUIntMaxValue;
    FND_TEST_TRUE(test_components(w, kUIntMaxValue, 0u, 9u));
}

void unittests_math_vector_uint3_increment_operators()
{
    // kUIntMaxValue wraps around to 0.
    uint3_t v{1u, kUIntMaxValue, 0u};
    FND_TEST_TRUE(test_components(++v, 2u, 0u, 1u));
    FND_TEST_TRUE(test_components(v, 2u, 0u, 1u));

    // Postfix returns the value before the increment.
    FND_TEST_TRUE(test_components(v++, 2u, 0u, 1u));
    FND_TEST_TRUE(test_components(v, 3u, 1u, 2u));
}

void unittests_math_vector_uint3_decrement_operators()
{
    // 0 wraps around to kUIntMaxValue.
    uint3_t v{1u, 0u, 5u};
    FND_TEST_TRUE(test_components(--v, 0u, kUIntMaxValue, 4u));
    FND_TEST_TRUE(test_components(v, 0u, kUIntMaxValue, 4u));

    // Postfix returns the value before the decrement.
    FND_TEST_TRUE(test_components(v--, 0u, kUIntMaxValue, 4u));
    FND_TEST_TRUE(test_components(v, kUIntMaxValue, kUIntMaxValue - 1, 3u));
}

void unittests_math_vector_uint3_bitwise_not_operator()
{
    FND_TEST_TRUE(test_components(
        ~uint3_t{0u, 5u, kUIntMaxValue}, kUIntMaxValue, kUIntMaxValue - 5, 0u));
    FND_TEST_TRUE(test_components(~uint3_t{0x80000000u, 1u, 0x7FFFFFFFu},
        0x7FFFFFFFu, kUIntMaxValue - 1, 0x80000000u));
}

void unittests_math_vector_uint3_compound_assignment_operators()
{
    uint3_t v{7u, 3u, 2u};

    // Each operator returns a reference to its left operand.
    FND_TEST_TRUE(&(v += uint3_t{1u, 2u, 3u}) == &v);
    FND_TEST_TRUE(test_components(v, 8u, 5u, 5u));
    FND_TEST_TRUE(test_components(v += 2u, 10u, 7u, 7u));
    FND_TEST_TRUE(test_components(v += 1, 11u, 8u, 8u));

    FND_TEST_TRUE(test_components(v -= uint3_t{4u, 3u, 2u}, 7u, 5u, 6u));
    FND_TEST_TRUE(test_components(v -= 1u, 6u, 4u, 5u));
    FND_TEST_TRUE(test_components(v -= 1, 5u, 3u, 4u));

    FND_TEST_TRUE(test_components(v *= uint3_t{2u, 3u, 4u}, 10u, 9u, 16u));
    FND_TEST_TRUE(test_components(v *= 3u, 30u, 27u, 48u));
    FND_TEST_TRUE(test_components(v *= 2, 60u, 54u, 96u));

    FND_TEST_TRUE(test_components(v /= uint3_t{3u, 2u, 4u}, 20u, 27u, 24u));
    FND_TEST_TRUE(test_components(v /= 2u, 10u, 13u, 12u));
    FND_TEST_TRUE(test_components(v /= 3, 3u, 4u, 4u));

    FND_TEST_TRUE(test_components(v %= uint3_t{2u, 3u, 3u}, 1u, 1u, 1u));
    v = uint3_t{7u, 9u, 10u};
    FND_TEST_TRUE(test_components(v %= 4u, 3u, 1u, 2u));
    v = uint3_t{7u, 9u, 10u};
    FND_TEST_TRUE(test_components(v %= 5, 2u, 4u, 0u));

    v = uint3_t{0b1100u, 0b1010u, 0b1111u};
    FND_TEST_TRUE(test_components(
        v &= uint3_t{0b1010u, 0b0110u, 0b0011u}, 0b1000u, 0b0010u, 0b0011u));
    FND_TEST_TRUE(test_components(v &= 0b1010u, 0b1000u, 0b0010u, 0b0010u));
    FND_TEST_TRUE(test_components(v &= 0b1000, 0b1000u, 0u, 0u));

    FND_TEST_TRUE(test_components(
        v |= uint3_t{0b0001u, 0b0010u, 0b0100u}, 0b1001u, 0b0010u, 0b0100u));
    FND_TEST_TRUE(test_components(v |= 0b0100u, 0b1101u, 0b0110u, 0b0100u));
    FND_TEST_TRUE(test_components(v |= 0b10000, 0b11101u, 0b10110u, 0b10100u));

    FND_TEST_TRUE(test_components(
        v ^= uint3_t{0b11101u, 0u, 0b00100u}, 0u, 0b10110u, 0b10000u));
    FND_TEST_TRUE(test_components(v ^= 0b0011u, 0b0011u, 0b10101u, 0b10011u));
    FND_TEST_TRUE(test_components(v ^= 0b0001, 0b0010u, 0b10100u, 0b10010u));

    FND_TEST_TRUE(test_components(v <<= uint3_t{1u, 2u, 1u}, 4u, 80u, 36u));
    FND_TEST_TRUE(test_components(v <<= 1u, 8u, 160u, 72u));
    FND_TEST_TRUE(test_components(v <<= 1, 16u, 320u, 144u));

    FND_TEST_TRUE(test_components(v >>= uint3_t{2u, 3u, 2u}, 4u, 40u, 36u));
    FND_TEST_TRUE(test_components(v >>= 1u, 2u, 20u, 18u));
    FND_TEST_TRUE(test_components(v >>= 1, 1u, 10u, 9u));
}

void unittests_math_vector_uint3_compound_assignment_matches_operators()
{
    // a op= b must give the same result as a op b, for every right-hand side.
    const uint3_t a{7u, 3u, 4u};
    const uint3_t b{2u, 5u, 3u};
    const uint_t uval{3u};
    const int_t ival{3};
    // Shift counts must be in [0, 32).
    const uint3_t shift{1u, 4u, 2u};
    const uint_t ushift{2u};
    const int_t ishift{2};
    uint3_t c;

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

void unittests_math_vector_uint3_equality_operators()
{
    const uint3_t a{7u, 3u, 4u};
    FND_TEST_TRUE(all((a == uint3_t{7u, 3u, 4u}) == bool3_t{true, true, true}));
    FND_TEST_TRUE(
        all((a == uint3_t{7u, 5u, 4u}) == bool3_t{true, false, true}));
    FND_TEST_TRUE(
        all((a == uint3_t{2u, 5u, 1u}) == bool3_t{false, false, false}));
    FND_TEST_TRUE(all((a == 7u) == bool3_t{true, false, false}));
    FND_TEST_TRUE(all((4u == a) == bool3_t{false, false, true}));
    FND_TEST_TRUE(all((a == 7) == bool3_t{true, false, false}));
    FND_TEST_TRUE(all((4 == a) == bool3_t{false, false, true}));

    FND_TEST_TRUE(
        all((a != uint3_t{7u, 3u, 4u}) == bool3_t{false, false, false}));
    FND_TEST_TRUE(
        all((a != uint3_t{7u, 5u, 4u}) == bool3_t{false, true, false}));
    FND_TEST_TRUE(all((a != uint3_t{2u, 5u, 1u}) == bool3_t{true, true, true}));
    FND_TEST_TRUE(all((a != 7u) == bool3_t{false, true, true}));
    FND_TEST_TRUE(all((4u != a) == bool3_t{true, true, false}));
    FND_TEST_TRUE(all((a != 7) == bool3_t{false, true, true}));
    FND_TEST_TRUE(all((4 != a) == bool3_t{true, true, false}));
}

void unittests_math_vector_uint3_relational_operators()
{
    const uint3_t a{7u, 3u, 4u};
    const uint3_t b{2u, 5u, 4u};
    const uint3_t c{7u, 5u, 1u};

    FND_TEST_TRUE(all((a < b) == bool3_t{false, true, false}));
    FND_TEST_TRUE(all((a < c) == bool3_t{false, true, false}));
    FND_TEST_TRUE(all((a < 5u) == bool3_t{false, true, true}));
    FND_TEST_TRUE(all((5u < a) == bool3_t{true, false, false}));
    FND_TEST_TRUE(all((a < 5) == bool3_t{false, true, true}));
    FND_TEST_TRUE(all((5 < a) == bool3_t{true, false, false}));

    FND_TEST_TRUE(all((a <= b) == bool3_t{false, true, true}));
    FND_TEST_TRUE(all((a <= c) == bool3_t{true, true, false}));
    FND_TEST_TRUE(all((a <= 4u) == bool3_t{false, true, true}));
    FND_TEST_TRUE(all((7u <= a) == bool3_t{true, false, false}));
    FND_TEST_TRUE(all((a <= 4) == bool3_t{false, true, true}));
    FND_TEST_TRUE(all((7 <= a) == bool3_t{true, false, false}));

    FND_TEST_TRUE(all((a > b) == bool3_t{true, false, false}));
    FND_TEST_TRUE(all((a > c) == bool3_t{false, false, true}));
    FND_TEST_TRUE(all((a > 5u) == bool3_t{true, false, false}));
    FND_TEST_TRUE(all((5u > a) == bool3_t{false, true, true}));
    FND_TEST_TRUE(all((a > 5) == bool3_t{true, false, false}));
    FND_TEST_TRUE(all((5 > a) == bool3_t{false, true, true}));

    FND_TEST_TRUE(all((a >= b) == bool3_t{true, false, true}));
    FND_TEST_TRUE(all((a >= c) == bool3_t{true, false, true}));
    FND_TEST_TRUE(all((a >= 7u) == bool3_t{true, false, false}));
    FND_TEST_TRUE(all((4u >= a) == bool3_t{false, true, true}));
    FND_TEST_TRUE(all((a >= 7) == bool3_t{true, false, false}));
    FND_TEST_TRUE(all((4 >= a) == bool3_t{false, true, true}));
}

void unittests_math_vector_uint3_bitwise_and_operator()
{
    const uint3_t a{0b1100u, 0b1010u, 0b1111u};
    FND_TEST_TRUE(test_components(
        a & uint3_t{0b1010u, 0b0110u, 0b0011u}, 0b1000u, 0b0010u, 0b0011u));
    FND_TEST_TRUE(test_components(a & 0b0110u, 0b0100u, 0b0010u, 0b0110u));
    FND_TEST_TRUE(test_components(0b0110u & a, 0b0100u, 0b0010u, 0b0110u));
    FND_TEST_TRUE(test_components(a & 0b0110, 0b0100u, 0b0010u, 0b0110u));
    FND_TEST_TRUE(test_components(0b0110 & a, 0b0100u, 0b0010u, 0b0110u));
    FND_TEST_TRUE(test_components(
        uint3_t{kUIntMaxValue, 0x80000000u, 0x1FFu} & 0xFFu, 0xFFu, 0u, 0xFFu));
}

void unittests_math_vector_uint3_multiplication_operator()
{
    const uint3_t a{7u, 3u, 4u};
    FND_TEST_TRUE(test_components(a * uint3_t{2u, 5u, 3u}, 14u, 15u, 12u));
    FND_TEST_TRUE(test_components(a * 2u, 14u, 6u, 8u));
    FND_TEST_TRUE(test_components(2u * a, 14u, 6u, 8u));
    FND_TEST_TRUE(test_components(a * 2, 14u, 6u, 8u));
    FND_TEST_TRUE(test_components(2 * a, 14u, 6u, 8u));
    // Overflow wraps around.
    FND_TEST_TRUE(
        test_components(uint3_t{0x80000000u, 3u, 1u} * 2u, 0u, 6u, 2u));
    FND_TEST_TRUE(test_components(
        uint3_t{0x10000u, 0x10000u, 0x10000u} * uint3_t{0x10000u, 2u, 0x10000u},
        0u, 0x20000u, 0u));
}

void unittests_math_vector_uint3_addition_operator()
{
    const uint3_t a{7u, 3u, 4u};
    FND_TEST_TRUE(test_components(a + uint3_t{2u, 5u, 1u}, 9u, 8u, 5u));
    FND_TEST_TRUE(test_components(a + 1u, 8u, 4u, 5u));
    FND_TEST_TRUE(test_components(1u + a, 8u, 4u, 5u));
    FND_TEST_TRUE(test_components(a + 1, 8u, 4u, 5u));
    FND_TEST_TRUE(test_components(1 + a, 8u, 4u, 5u));
    // Overflow wraps around.
    FND_TEST_TRUE(test_components(
        uint3_t{kUIntMaxValue, 1u, 0u} + uint3_t{1u, 1u, 0u}, 0u, 2u, 0u));
    FND_TEST_TRUE(test_components(uint3_t{kUIntMaxValue} + 2u, 1u, 1u, 1u));
}

void unittests_math_vector_uint3_subtraction_operator()
{
    const uint3_t a{7u, 3u, 4u};
    FND_TEST_TRUE(test_components(a - uint3_t{2u, 1u, 4u}, 5u, 2u, 0u));
    FND_TEST_TRUE(test_components(a - 1u, 6u, 2u, 3u));
    FND_TEST_TRUE(test_components(10u - a, 3u, 7u, 6u));
    FND_TEST_TRUE(test_components(a - 1, 6u, 2u, 3u));
    FND_TEST_TRUE(test_components(10 - a, 3u, 7u, 6u));
    // Overflow wraps around.
    FND_TEST_TRUE(
        test_components(a - uint3_t{2u, 5u, 1u}, 5u, kUIntMaxValue - 1, 3u));
    FND_TEST_TRUE(
        test_components(uint3_t{0u, 5u, 1u} - 1u, kUIntMaxValue, 4u, 0u));
}

void unittests_math_vector_uint3_modulo_operator()
{
    const uint3_t a{7u, 3u, 4u};
    FND_TEST_TRUE(test_components(a % uint3_t{2u, 5u, 3u}, 1u, 3u, 1u));
    FND_TEST_TRUE(test_components(a % 2u, 1u, 1u, 0u));
    FND_TEST_TRUE(test_components(21u % uint3_t{2u, 5u, 4u}, 1u, 1u, 1u));
    FND_TEST_TRUE(test_components(a % 2, 1u, 1u, 0u));
    FND_TEST_TRUE(test_components(21 % uint3_t{2u, 5u, 4u}, 1u, 1u, 1u));
    FND_TEST_TRUE(test_components(
        uint3_t{kUIntMaxValue, 9u, 8u} % uint3_t{2u, 4u, 8u}, 1u, 1u, 0u));
}

void unittests_math_vector_uint3_division_operator()
{
    const uint3_t a{7u, 3u, 4u};
    FND_TEST_TRUE(test_components(a / uint3_t{2u, 5u, 3u}, 3u, 0u, 1u));
    FND_TEST_TRUE(test_components(a / 2u, 3u, 1u, 2u));
    FND_TEST_TRUE(test_components(21u / uint3_t{2u, 5u, 4u}, 10u, 4u, 5u));
    FND_TEST_TRUE(test_components(a / 2, 3u, 1u, 2u));
    FND_TEST_TRUE(test_components(21 / uint3_t{2u, 5u, 4u}, 10u, 4u, 5u));
    FND_TEST_TRUE(
        test_components(uint3_t{kUIntMaxValue, 9u, 8u} / uint3_t{1u, 3u, 8u},
            kUIntMaxValue, 3u, 1u));
}

void unittests_math_vector_uint3_shift_left_operator()
{
    FND_TEST_TRUE(test_components(
        uint3_t{1u, 3u, 5u} << uint3_t{4u, 1u, 0u}, 16u, 6u, 5u));
    FND_TEST_TRUE(test_components(uint3_t{1u, 3u, 5u} << 2u, 4u, 12u, 20u));
    FND_TEST_TRUE(
        test_components(1u << uint3_t{0u, 31u, 4u}, 1u, 0x80000000u, 16u));
    FND_TEST_TRUE(test_components(uint3_t{1u, 3u, 5u} << 2, 4u, 12u, 20u));
    FND_TEST_TRUE(
        test_components(1 << uint3_t{0u, 31u, 4u}, 1u, 0x80000000u, 16u));
    // Bits shifted out are discarded.
    FND_TEST_TRUE(
        test_components(uint3_t{0x80000000u, 3u, 1u} << 1u, 0u, 6u, 2u));
}

void unittests_math_vector_uint3_shift_right_operator()
{
    FND_TEST_TRUE(test_components(
        uint3_t{16u, 6u, 5u} >> uint3_t{4u, 1u, 0u}, 1u, 3u, 5u));
    FND_TEST_TRUE(test_components(uint3_t{16u, 6u, 5u} >> 1u, 8u, 3u, 2u));
    FND_TEST_TRUE(test_components(256u >> uint3_t{4u, 8u, 0u}, 16u, 1u, 256u));
    FND_TEST_TRUE(test_components(uint3_t{16u, 6u, 5u} >> 1, 8u, 3u, 2u));
    FND_TEST_TRUE(test_components(256 >> uint3_t{4u, 8u, 0u}, 16u, 1u, 256u));
    // Zeros are shifted in, whatever the top bit is.
    FND_TEST_TRUE(test_components(
        uint3_t{0x80000000u, 8u, 1u} >> 1u, 0x40000000u, 4u, 0u));
    FND_TEST_TRUE(test_components(
        uint3_t{kUIntMaxValue, 1u, 0x80000000u} >> 31u, 1u, 0u, 1u));
}

void unittests_math_vector_uint3_bitwise_xor_operator()
{
    const uint3_t a{0b1100u, 0b1010u, 0b1111u};
    FND_TEST_TRUE(test_components(
        a ^ uint3_t{0b1010u, 0b0110u, 0b1111u}, 0b0110u, 0b1100u, 0u));
    FND_TEST_TRUE(test_components(a ^ 0b1111u, 0b0011u, 0b0101u, 0u));
    FND_TEST_TRUE(test_components(0b1111u ^ a, 0b0011u, 0b0101u, 0u));
    FND_TEST_TRUE(test_components(a ^ 0b1111, 0b0011u, 0b0101u, 0u));
    FND_TEST_TRUE(test_components(0b1111 ^ a, 0b0011u, 0b0101u, 0u));
    FND_TEST_TRUE(test_components(a ^ a, 0u, 0u, 0u));
}

void unittests_math_vector_uint3_bitwise_or_operator()
{
    const uint3_t a{0b1100u, 0b1010u, 0b1111u};
    FND_TEST_TRUE(test_components(
        a | uint3_t{0b1010u, 0b0110u, 0b0000u}, 0b1110u, 0b1110u, 0b1111u));
    FND_TEST_TRUE(test_components(a | 0b0001u, 0b1101u, 0b1011u, 0b1111u));
    FND_TEST_TRUE(test_components(0b0001u | a, 0b1101u, 0b1011u, 0b1111u));
    FND_TEST_TRUE(test_components(a | 0b0001, 0b1101u, 0b1011u, 0b1111u));
    FND_TEST_TRUE(test_components(0b0001 | a, 0b1101u, 0b1011u, 0b1111u));
    FND_TEST_TRUE(test_components(uint3_t{0u, 0x7FFFFFFFu, 1u} | 0x80000000u,
        0x80000000u, kUIntMaxValue, 0x80000001u));
}

void unittests_math_vector_uint3_clamp()
{
    const uint3_t lower{0u, 2u, 1u};
    const uint3_t upper{10u, 5u, 1u};
    // Each component is clamped to its own bounds.
    FND_TEST_TRUE(
        test_components(clamp(uint3_t{3u, 3u, 0u}, lower, upper), 3u, 3u, 1u));
    FND_TEST_TRUE(
        test_components(clamp(uint3_t{0u, 1u, 5u}, lower, upper), 0u, 2u, 1u));
    FND_TEST_TRUE(test_components(
        clamp(uint3_t{20u, 6u, 1u}, lower, upper), 10u, 5u, 1u));
    FND_TEST_TRUE(
        test_components(clamp(uint3_t{0u, 5u, 1u}, lower, upper), 0u, 5u, 1u));
    FND_TEST_TRUE(test_components(
        clamp(uint3_t{20u, 1u, 1u}, lower, upper), 10u, 2u, 1u));
    FND_TEST_TRUE(test_components(
        clamp(uint3_t{9u, 9u, 9u}, uint3_t{3u, 3u, 3u}, uint3_t{3u, 3u, 3u}),
        3u, 3u, 3u));

    // uint_t bounds apply to every component.
    FND_TEST_TRUE(
        test_components(clamp(uint3_t{3u, 9u, 0u}, 2u, 5u), 3u, 5u, 2u));
    FND_TEST_TRUE(
        test_components(clamp(uint3_t{0u, 20u, 7u}, 2u, 10u), 2u, 10u, 7u));
    FND_TEST_TRUE(
        test_components(clamp(uint3_t{2u, 10u, 5u}, 2u, 10u), 2u, 10u, 5u));
    FND_TEST_TRUE(
        test_components(clamp(uint3_t{9u, 0u, 3u}, 3u, 3u), 3u, 3u, 3u));

    // uint3_t lower bound, uint_t upper bound.
    FND_TEST_TRUE(test_components(
        clamp(uint3_t{0u, 0u, 0u}, uint3_t{1u, 2u, 3u}, 5u), 1u, 2u, 3u));
    FND_TEST_TRUE(test_components(
        clamp(uint3_t{20u, 3u, 9u}, uint3_t{1u, 2u, 3u}, 5u), 5u, 3u, 5u));
    FND_TEST_TRUE(test_components(
        clamp(uint3_t{9u, 0u, 4u}, uint3_t{3u, 5u, 1u}, 5u), 5u, 5u, 4u));

    // uint_t lower bound, uint3_t upper bound.
    FND_TEST_TRUE(test_components(
        clamp(uint3_t{0u, 0u, 0u}, 1u, uint3_t{10u, 5u, 2u}), 1u, 1u, 1u));
    FND_TEST_TRUE(test_components(
        clamp(uint3_t{20u, 3u, 9u}, 1u, uint3_t{10u, 5u, 2u}), 10u, 3u, 2u));
    FND_TEST_TRUE(test_components(
        clamp(uint3_t{9u, 0u, 4u}, 3u, uint3_t{3u, 7u, 6u}), 3u, 3u, 4u));
}

void unittests_math_vector_uint3_cmax()
{
    // The maximum in each position.
    FND_TEST_TRUE(cmax(uint3_t{7u, 3u, 4u}) == 7u);
    FND_TEST_TRUE(cmax(uint3_t{3u, 7u, 4u}) == 7u);
    FND_TEST_TRUE(cmax(uint3_t{4u, 3u, 7u}) == 7u);
    FND_TEST_TRUE(cmax(uint3_t{4u, 4u, 4u}) == 4u);
    FND_TEST_TRUE(cmax(uint3_t{0u, kUIntMaxValue, 1u}) == kUIntMaxValue);
}

void unittests_math_vector_uint3_cmin()
{
    // The minimum in each position.
    FND_TEST_TRUE(cmin(uint3_t{3u, 7u, 4u}) == 3u);
    FND_TEST_TRUE(cmin(uint3_t{7u, 3u, 4u}) == 3u);
    FND_TEST_TRUE(cmin(uint3_t{7u, 4u, 3u}) == 3u);
    FND_TEST_TRUE(cmin(uint3_t{4u, 4u, 4u}) == 4u);
    FND_TEST_TRUE(cmin(uint3_t{kUIntMaxValue, 0u, 1u}) == 0u);
}

void unittests_math_vector_uint3_cmul()
{
    FND_TEST_TRUE(cmul(uint3_t{7u, 3u, 2u}) == 42u);
    FND_TEST_TRUE(cmul(uint3_t{0u, kUIntMaxValue, kUIntMaxValue}) == 0u);
    // 1625^3 is the largest cube that fits in uint_t.
    FND_TEST_TRUE(cmul(uint3_t{1625u, 1625u, 1625u}) == 4291015625u);
    // Overflow wraps around.
    FND_TEST_TRUE(cmul(uint3_t{0x10000u, 0x10000u, 1u}) == 0u);
    FND_TEST_TRUE(cmul(uint3_t{0x80000000u, 3u, 1u}) == 0x80000000u);
}

void unittests_math_vector_uint3_csum()
{
    FND_TEST_TRUE(csum(uint3_t{7u, 3u, 4u}) == 14u);
    FND_TEST_TRUE(csum(uint3_t{0u, 0u, 0u}) == 0u);
    FND_TEST_TRUE(csum(uint3_t{kUIntMaxValue - 2, 1u, 1u}) == kUIntMaxValue);
    // Overflow wraps around.
    FND_TEST_TRUE(csum(uint3_t{kUIntMaxValue, 1u, 0u}) == 0u);
    FND_TEST_TRUE(csum(uint3_t{kUIntMaxValue, kUIntMaxValue, kUIntMaxValue})
        == kUIntMaxValue - 2);
}

void unittests_math_vector_uint3_max()
{
    const uint3_t a{7u, 3u, 4u};
    FND_TEST_TRUE(test_components(max(a, uint3_t{2u, 5u, 4u}), 7u, 5u, 4u));
    FND_TEST_TRUE(test_components(max(uint3_t{2u, 5u, 4u}, a), 7u, 5u, 4u));
    FND_TEST_TRUE(test_components(
        max(uint3_t{4u, 4u, 4u}, uint3_t{4u, 4u, 4u}), 4u, 4u, 4u));
    FND_TEST_TRUE(test_components(
        max(uint3_t{0u, kUIntMaxValue, 1u}, uint3_t{kUIntMaxValue, 0u, 1u}),
        kUIntMaxValue, kUIntMaxValue, 1u));
    // uint_t on either side is compared with every component.
    FND_TEST_TRUE(test_components(max(a, 5u), 7u, 5u, 5u));
    FND_TEST_TRUE(test_components(max(5u, a), 7u, 5u, 5u));
    FND_TEST_TRUE(test_components(max(a, 10u), 10u, 10u, 10u));
    FND_TEST_TRUE(test_components(max(0u, a), 7u, 3u, 4u));
}

void unittests_math_vector_uint3_min()
{
    const uint3_t a{7u, 3u, 4u};
    FND_TEST_TRUE(test_components(min(a, uint3_t{2u, 5u, 4u}), 2u, 3u, 4u));
    FND_TEST_TRUE(test_components(min(uint3_t{2u, 5u, 4u}, a), 2u, 3u, 4u));
    FND_TEST_TRUE(test_components(
        min(uint3_t{4u, 4u, 4u}, uint3_t{4u, 4u, 4u}), 4u, 4u, 4u));
    FND_TEST_TRUE(test_components(
        min(uint3_t{0u, kUIntMaxValue, 1u}, uint3_t{kUIntMaxValue, 0u, 1u}), 0u,
        0u, 1u));
    // uint_t on either side is compared with every component.
    FND_TEST_TRUE(test_components(min(a, 5u), 5u, 3u, 4u));
    FND_TEST_TRUE(test_components(min(5u, a), 5u, 3u, 4u));
    FND_TEST_TRUE(test_components(min(a, 0u), 0u, 0u, 0u));
    FND_TEST_TRUE(test_components(min(kUIntMaxValue, a), 7u, 3u, 4u));
}

// int3_t and uint3_t must agree wherever int3_t is defined: non-negative inputs
// and no int_t overflow. int3_t results are compared by their bits, so that the
// negative result of 3 - 5 matches the wrapped 3u - 5u.
bool_t same_bits(const int3_t i, const uint3_t u)
{
    return all(bit_cast<uint3_t>(i) == u);
}

void unittests_math_vector_uint3_matches_int3()
{
    const int3_t ia{7, 3, 4};
    const int3_t ib{2, 5, 3};
    const uint3_t ua{7u, 3u, 4u};
    const uint3_t ub{2u, 5u, 3u};
    // Shift counts must be in [0, 32), and left shifts must not overflow int_t.
    const int3_t ishift{1, 4, 2};
    const uint3_t ushift{1u, 4u, 2u};

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
    int3_t ic;
    uint3_t uc;
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
    FND_TEST_TRUE(same_bits(clamp(ia, int3_t{2, 4, 1}, int3_t{5, 6, 3}),
        clamp(ua, uint3_t{2u, 4u, 1u}, uint3_t{5u, 6u, 3u})));
    FND_TEST_TRUE(same_bits(
        clamp(ia, int3_t{2, 4, 1}, 5), clamp(ua, uint3_t{2u, 4u, 1u}, 5u)));
    FND_TEST_TRUE(same_bits(
        clamp(ia, 4, int3_t{5, 6, 7}), clamp(ua, 4u, uint3_t{5u, 6u, 7u})));
    FND_TEST_TRUE(same_bits(clamp(ia, 4, 5), clamp(ua, 4u, 5u)));
    FND_TEST_TRUE(cmin(ia) == static_cast<int_t>(cmin(ua)));
    FND_TEST_TRUE(cmax(ia) == static_cast<int_t>(cmax(ua)));
    FND_TEST_TRUE(csum(ia) == static_cast<int_t>(csum(ua)));
    FND_TEST_TRUE(cmul(ia) == static_cast<int_t>(cmul(ua)));
}

void unittests_math_vector_uint3()
{
    unittests_math_vector_uint3_type();
    unittests_math_vector_uint3_constants();
    unittests_math_vector_uint3_constructors();
    unittests_math_vector_uint3_subscript_operator();
    unittests_math_vector_uint3_increment_operators();
    unittests_math_vector_uint3_decrement_operators();
    unittests_math_vector_uint3_bitwise_not_operator();
    unittests_math_vector_uint3_compound_assignment_operators();
    unittests_math_vector_uint3_compound_assignment_matches_operators();
    unittests_math_vector_uint3_equality_operators();
    unittests_math_vector_uint3_relational_operators();
    unittests_math_vector_uint3_bitwise_and_operator();
    unittests_math_vector_uint3_multiplication_operator();
    unittests_math_vector_uint3_addition_operator();
    unittests_math_vector_uint3_subtraction_operator();
    unittests_math_vector_uint3_modulo_operator();
    unittests_math_vector_uint3_division_operator();
    unittests_math_vector_uint3_shift_left_operator();
    unittests_math_vector_uint3_shift_right_operator();
    unittests_math_vector_uint3_bitwise_xor_operator();
    unittests_math_vector_uint3_bitwise_or_operator();
    unittests_math_vector_uint3_clamp();
    unittests_math_vector_uint3_cmax();
    unittests_math_vector_uint3_cmin();
    unittests_math_vector_uint3_cmul();
    unittests_math_vector_uint3_csum();
    unittests_math_vector_uint3_max();
    unittests_math_vector_uint3_min();
    unittests_math_vector_uint3_matches_int3();
}

} // namespace fnd::unittests
