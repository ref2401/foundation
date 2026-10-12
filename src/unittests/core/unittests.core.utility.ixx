module;
#include "foundation/unittests.h"


export module unittests.core:utility;
import foundation.core;

namespace fnd::unittests {

export void unittests_core_utility();

// Cannot be copied: exchange and swap compile for it only if they never copy.
class MoveOnly final {
public:
  constexpr explicit MoveOnly(const int_t value) : value_{value} {}
  MoveOnly(const MoveOnly&) = delete;
  MoveOnly(MoveOnly&&) = default;
  MoveOnly& operator=(const MoveOnly&) = delete;
  MoveOnly& operator=(MoveOnly&&) = default;

  constexpr int_t value() const { return value_; }

private:
  int_t value_;
};

// Tells how an int_t argument arrived: a non-const lvalue, a const lvalue or an
// rvalue.
constexpr int_t forward_test_category(int_t&)
{
  return 1;
}
constexpr int_t forward_test_category(const int_t&)
{
  return 2;
}
constexpr int_t forward_test_category(int_t&&)
{
  return 3;
}

// Passes value on through a forwarding reference, as forward is meant to be
// used, and without forward for comparison.
template<typename T> constexpr int_t forward_test_pass(T&& value)
{
  return forward_test_category(forward<T>(value));
}

template<typename T> constexpr int_t forward_test_pass_named(T&& value)
{
  return forward_test_category(value);
}

// Constructs a MoveOnly from a forwarded argument: compiles only if an rvalue
// MoveOnly arrives as an rvalue (the copy constructor is deleted).
template<typename T> MoveOnly forward_test_make(T&& value)
{
  return MoveOnly{forward<T>(value)};
}

void unittests_core_utility_bit_cast_int_to_float()
{
  FND_TEST_TRUE(bit_cast<float_t>(int_t{0}) == 0.0f);
  FND_TEST_TRUE(bit_cast<float_t>(int_t{0x3F800000}) == 1.0f);
  FND_TEST_TRUE(bit_cast<float_t>(static_cast<int_t>(0xBF800000u)) == -1.0f);
  FND_TEST_TRUE(bit_cast<float_t>(int_t{0x7F800000}) == kFloatInfinity);
  // Bits, not a value conversion: 1 is the smallest subnormal, not 1.0f.
  FND_TEST_TRUE(bit_cast<float_t>(int_t{1}) == kFloatMinSubnormal);
}

void unittests_core_utility_bit_cast_uint_to_float()
{
  FND_TEST_TRUE(bit_cast<float_t>(0u) == 0.0f);
  FND_TEST_TRUE(bit_cast<float_t>(0x3F800000u) == 1.0f);
  FND_TEST_TRUE(bit_cast<float_t>(0xBF800000u) == -1.0f);
  FND_TEST_TRUE(bit_cast<float_t>(0x7F800000u) == kFloatInfinity);
  FND_TEST_TRUE(bit_cast<float_t>(0xFF800000u) == -kFloatInfinity);
  FND_TEST_TRUE(bit_cast<float_t>(0x7F7FFFFFu) == kFloatMaxValue);
  FND_TEST_TRUE(bit_cast<float_t>(0x00800000u) == kFloatMinNormal);
  FND_TEST_TRUE(bit_cast<float_t>(1u) == kFloatMinSubnormal);
}

void unittests_core_utility_bit_cast_float_to_int()
{
  FND_TEST_TRUE(bit_cast<int_t>(0.0f) == 0);
  FND_TEST_TRUE(bit_cast<int_t>(-0.0f) == kIntMinValue);
  FND_TEST_TRUE(bit_cast<int_t>(1.0f) == 0x3F800000);
  FND_TEST_TRUE(bit_cast<int_t>(-1.0f) == static_cast<int_t>(0xBF800000u));
  FND_TEST_TRUE(bit_cast<int_t>(kFloatInfinity) == 0x7F800000);
}

void unittests_core_utility_bit_cast_uint_to_int()
{
  FND_TEST_TRUE(bit_cast<int_t>(0u) == 0);
  FND_TEST_TRUE(bit_cast<int_t>(1u) == 1);
  FND_TEST_TRUE(bit_cast<int_t>(0x7FFFFFFFu) == kIntMaxValue);
  FND_TEST_TRUE(bit_cast<int_t>(0x80000000u) == kIntMinValue);
  FND_TEST_TRUE(bit_cast<int_t>(0xFFFFFFFFu) == -1);
}

void unittests_core_utility_bit_cast_float_to_uint()
{
  FND_TEST_TRUE(bit_cast<uint_t>(0.0f) == 0u);
  FND_TEST_TRUE(bit_cast<uint_t>(-0.0f) == 0x80000000u);
  FND_TEST_TRUE(bit_cast<uint_t>(1.0f) == 0x3F800000u);
  FND_TEST_TRUE(bit_cast<uint_t>(-1.0f) == 0xBF800000u);
  FND_TEST_TRUE(bit_cast<uint_t>(kFloatInfinity) == 0x7F800000u);
  FND_TEST_TRUE(bit_cast<uint_t>(-kFloatInfinity) == 0xFF800000u);
  // NaN: all exponent bits set and a non-zero mantissa, whatever its sign.
  FND_TEST_TRUE((bit_cast<uint_t>(kFloatNaN) & 0x7FFFFFFFu) > 0x7F800000u);
  FND_TEST_TRUE(bit_cast<float_t>(bit_cast<uint_t>(1.5f)) == 1.5f);
}

void unittests_core_utility_bit_cast_int_to_uint()
{
  FND_TEST_TRUE(bit_cast<uint_t>(int_t{0}) == 0u);
  FND_TEST_TRUE(bit_cast<uint_t>(int_t{1}) == 1u);
  FND_TEST_TRUE(bit_cast<uint_t>(int_t{-1}) == 0xFFFFFFFFu);
  FND_TEST_TRUE(bit_cast<uint_t>(kIntMaxValue) == 0x7FFFFFFFu);
  FND_TEST_TRUE(bit_cast<uint_t>(kIntMinValue) == 0x80000000u);
}

void unittests_core_utility_bit_cast_long_to_double()
{
  FND_TEST_TRUE(bit_cast<double_t>(long_t{0}) == 0.0);
  FND_TEST_TRUE(bit_cast<double_t>(long_t{0x3FF0000000000000}) == 1.0);
  FND_TEST_TRUE(
    bit_cast<double_t>(static_cast<long_t>(0xBFF0000000000000ull)) == -1.0);
  FND_TEST_TRUE(
    bit_cast<double_t>(long_t{0x7FF0000000000000}) == kDoubleInfinity);
  // Bits, not a value conversion: 1 is the smallest subnormal, not 1.0.
  FND_TEST_TRUE(bit_cast<double_t>(long_t{1}) == kDoubleMinSubnormal);
}

void unittests_core_utility_bit_cast_ulong_to_double()
{
  FND_TEST_TRUE(bit_cast<double_t>(0ull) == 0.0);
  FND_TEST_TRUE(bit_cast<double_t>(0x3FF0000000000000ull) == 1.0);
  FND_TEST_TRUE(bit_cast<double_t>(0xBFF0000000000000ull) == -1.0);
  FND_TEST_TRUE(bit_cast<double_t>(0x7FF0000000000000ull) == kDoubleInfinity);
  FND_TEST_TRUE(bit_cast<double_t>(0xFFF0000000000000ull) == -kDoubleInfinity);
  FND_TEST_TRUE(bit_cast<double_t>(0x7FEFFFFFFFFFFFFFull) == kDoubleMaxValue);
  FND_TEST_TRUE(bit_cast<double_t>(0x0010000000000000ull) == kDoubleMinNormal);
  FND_TEST_TRUE(bit_cast<double_t>(1ull) == kDoubleMinSubnormal);
}

void unittests_core_utility_bit_cast_double_to_long()
{
  FND_TEST_TRUE(bit_cast<long_t>(0.0) == 0);
  FND_TEST_TRUE(bit_cast<long_t>(-0.0) == kLongMinValue);
  FND_TEST_TRUE(bit_cast<long_t>(1.0) == 0x3FF0000000000000);
  FND_TEST_TRUE(
    bit_cast<long_t>(-1.0) == static_cast<long_t>(0xBFF0000000000000ull));
  FND_TEST_TRUE(bit_cast<long_t>(kDoubleInfinity) == 0x7FF0000000000000);
}

void unittests_core_utility_bit_cast_ulong_to_long()
{
  FND_TEST_TRUE(bit_cast<long_t>(0ull) == 0);
  FND_TEST_TRUE(bit_cast<long_t>(1ull) == 1);
  FND_TEST_TRUE(bit_cast<long_t>(0x7FFFFFFFFFFFFFFFull) == kLongMaxValue);
  FND_TEST_TRUE(bit_cast<long_t>(0x8000000000000000ull) == kLongMinValue);
  FND_TEST_TRUE(bit_cast<long_t>(0xFFFFFFFFFFFFFFFFull) == -1);
}

void unittests_core_utility_bit_cast_double_to_ulong()
{
  FND_TEST_TRUE(bit_cast<ulong_t>(0.0) == 0ull);
  FND_TEST_TRUE(bit_cast<ulong_t>(-0.0) == 0x8000000000000000ull);
  FND_TEST_TRUE(bit_cast<ulong_t>(1.0) == 0x3FF0000000000000ull);
  FND_TEST_TRUE(bit_cast<ulong_t>(-1.0) == 0xBFF0000000000000ull);
  FND_TEST_TRUE(bit_cast<ulong_t>(kDoubleInfinity) == 0x7FF0000000000000ull);
  FND_TEST_TRUE(bit_cast<ulong_t>(-kDoubleInfinity) == 0xFFF0000000000000ull);
  // NaN: all exponent bits set and a non-zero mantissa, whatever its sign.
  FND_TEST_TRUE(
    (bit_cast<ulong_t>(kDoubleNaN) & 0x7FFFFFFFFFFFFFFFull)
    > 0x7FF0000000000000ull);
  FND_TEST_TRUE(bit_cast<double_t>(bit_cast<ulong_t>(1.5)) == 1.5);
}

void unittests_core_utility_bit_cast_long_to_ulong()
{
  FND_TEST_TRUE(bit_cast<ulong_t>(long_t{0}) == 0ull);
  FND_TEST_TRUE(bit_cast<ulong_t>(long_t{1}) == 1ull);
  FND_TEST_TRUE(bit_cast<ulong_t>(long_t{-1}) == 0xFFFFFFFFFFFFFFFFull);
  FND_TEST_TRUE(bit_cast<ulong_t>(kLongMaxValue) == 0x7FFFFFFFFFFFFFFFull);
  FND_TEST_TRUE(bit_cast<ulong_t>(kLongMinValue) == 0x8000000000000000ull);
}

void unittests_core_utility_forward()
{
  int_t a{1};
  const int_t ca{2};

  // T is what a forwarding reference deduces: an lvalue reference for an
  // lvalue, the type itself for an rvalue.
  static_assert(is_same<decltype(forward<int_t&>(a)), int_t&>());
  static_assert(is_same<decltype(forward<const int_t&>(ca)), const int_t&>());
  static_assert(is_same<decltype(forward<int_t>(a)), int_t&&>());
  static_assert(is_same<decltype(forward<int_t>(int_t{3})), int_t&&>());
  static_assert(is_same<decltype(forward<const int_t>(ca)), const int_t&&>());

  // It is only a cast: the result refers to the object itself.
  int_t& lr{forward<int_t&>(a)};
  int_t&& rr{forward<int_t>(a)};
  FND_TEST_TRUE(&lr == &a);
  FND_TEST_TRUE(&rr == &a);
  FND_TEST_TRUE(a == 1);

  // Through a forwarding reference the callee sees the argument as the
  // caller passed it: a non-const lvalue, a const lvalue or an rvalue.
  FND_TEST_TRUE(forward_test_pass(a) == 1);
  FND_TEST_TRUE(forward_test_pass(ca) == 2);
  FND_TEST_TRUE(forward_test_pass(int_t{3}) == 3);
  FND_TEST_TRUE(forward_test_pass(move(a)) == 3);
  // Without forward a named parameter is always an lvalue: the rvalue
  // arrives as a non-const lvalue.
  FND_TEST_TRUE(forward_test_pass_named(int_t{3}) == 1);

  // A forwarded rvalue reaches the move constructor.
  MoveOnly m{forward_test_make(MoveOnly{5})};
  FND_TEST_TRUE(m.value() == 5);
  FND_TEST_TRUE(forward_test_make(move(m)).value() == 5);

  // Usable in constant expressions.
  static_assert(
    [] {
      int_t b{4};
      return forward<int_t&>(b);
    }()
    == 4);
}

void unittests_core_utility_move()
{
  int_t a{1};
  volatile int_t va{2};
  int_t* p{&a};
  const int_t* pc{&a};

  // move makes an rvalue reference to the referred type. A const object is
  // rejected at compile time, so move(const_object) is not tested here.
  static_assert(is_same<decltype(move(a)), int_t&&>());
  static_assert(is_same<decltype(move(int_t{3})), int_t&&>());
  static_assert(is_same<decltype(move(move(a))), int_t&&>());
  static_assert(is_same<decltype(move(va)), volatile int_t&&>());

  // A pointer is moved itself, not the object it points to: a pointer to a
  // const int_t is not const itself and can be moved.
  static_assert(is_same<decltype(move(p)), int_t*&&>());
  static_assert(is_same<decltype(move(pc)), const int_t*&&>());

  // It is only a cast: the result refers to the object itself, which is not
  // changed.
  int_t&& r{move(a)};
  FND_TEST_TRUE(&r == &a);
  FND_TEST_TRUE(a == 1);

  // Usable in constant expressions.
  static_assert([] { return move(5); }() == 5);
}

void unittests_core_utility_exchange()
{
  struct exchange_test_t final {
    int_t x;
    int_t y;
  };

  int_t a{1};
  const int_t ca{2};
  int_t* p{&a};
  exchange_test_t s{1, 2};
  MoveOnly m{1};

  // The result is the type of object, whatever new_value is: an rvalue, an
  // lvalue, nullptr or a braced list (U falls back to T).
  static_assert(is_same<decltype(exchange(a, 2)), int_t>());
  static_assert(is_same<decltype(exchange(a, ca)), int_t>());
  static_assert(is_same<decltype(exchange(p, nullptr)), int_t*>());
  static_assert(is_same<decltype(exchange(s, {3, 4})), exchange_test_t>());
  static_assert(is_same<decltype(exchange(m, MoveOnly{2})), MoveOnly>());

  // object gets new_value, the previous value is returned.
  FND_TEST_TRUE(exchange(a, 3) == 1);
  FND_TEST_TRUE(a == 3);
  FND_TEST_TRUE(exchange(a, ca) == 3);
  FND_TEST_TRUE(a == 2);

  FND_TEST_TRUE(exchange(p, nullptr) == &a);
  FND_TEST_TRUE(p == nullptr);

  const exchange_test_t old_s{exchange(s, {3, 4})};
  FND_TEST_TRUE(old_s.x == 1 && old_s.y == 2);
  FND_TEST_TRUE(s.x == 3 && s.y == 4);

  const MoveOnly old_m{exchange(m, MoveOnly{2})};
  FND_TEST_TRUE(old_m.value() == 1);
  FND_TEST_TRUE(m.value() == 2);

  // Usable in constant expressions.
  static_assert([] {
    int_t b{1};
    const int_t old_value{exchange(b, 2)};
    return old_value == 1 && b == 2;
  }());
}

void unittests_core_utility_swap()
{
  struct swap_test_t final {
    int_t x;
    int_t y;
  };

  int_t a{1};
  int_t b{2};
  swap(a, b);
  FND_TEST_TRUE(a == 2);
  FND_TEST_TRUE(b == 1);

  int_t* p{&a};
  int_t* q{&b};
  swap(p, q);
  FND_TEST_TRUE(p == &b);
  FND_TEST_TRUE(q == &a);

  swap_test_t s{1, 2};
  swap_test_t t{3, 4};
  swap(s, t);
  FND_TEST_TRUE(s.x == 3 && s.y == 4);
  FND_TEST_TRUE(t.x == 1 && t.y == 2);

  MoveOnly m{1};
  MoveOnly n{2};
  swap(m, n);
  FND_TEST_TRUE(m.value() == 2);
  FND_TEST_TRUE(n.value() == 1);

  // Swapping an object with itself leaves it unchanged.
  swap(a, a);
  FND_TEST_TRUE(a == 2);
  swap(m, m);
  FND_TEST_TRUE(m.value() == 2);

  // Usable in constant expressions.
  static_assert([] {
    int_t c{1};
    int_t d{2};
    swap(c, d);
    return c == 2 && d == 1;
  }());
}

void unittests_core_utility()
{
  unittests_core_utility_bit_cast_int_to_float();
  unittests_core_utility_bit_cast_uint_to_float();
  unittests_core_utility_bit_cast_float_to_int();
  unittests_core_utility_bit_cast_uint_to_int();
  unittests_core_utility_bit_cast_float_to_uint();
  unittests_core_utility_bit_cast_int_to_uint();
  unittests_core_utility_bit_cast_long_to_double();
  unittests_core_utility_bit_cast_ulong_to_double();
  unittests_core_utility_bit_cast_double_to_long();
  unittests_core_utility_bit_cast_ulong_to_long();
  unittests_core_utility_bit_cast_double_to_ulong();
  unittests_core_utility_bit_cast_long_to_ulong();
  unittests_core_utility_forward();
  unittests_core_utility_move();
  unittests_core_utility_exchange();
  unittests_core_utility_swap();
}

} // namespace fnd::unittests
