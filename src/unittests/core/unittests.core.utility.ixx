module;
#include "foundation/unittests.h"


export module unittests.core:utility;
import foundation.core;

namespace fnd::unittests {

export void unittests_core_utility();

// Cannot be copied: exchange and swap compile for it only if they never copy.
class MoveOnly {
  public:
    constexpr explicit MoveOnly(int_t value) : value_{value} {}
    MoveOnly(const MoveOnly&) = delete;
    MoveOnly(MoveOnly&&) = default;
    MoveOnly& operator=(const MoveOnly&) = delete;
    MoveOnly& operator=(MoveOnly&&) = default;

    constexpr int_t value() const { return value_; }

  private:
    int_t value_;
};

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

    // Usable in constant expressions.
    static_assert([] {
        int_t b{4};
        return forward<int_t&>(b);
    }() == 4);
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
    struct exchange_test_t {
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
    struct swap_test_t {
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
    unittests_core_utility_forward();
    unittests_core_utility_move();
    unittests_core_utility_exchange();
    unittests_core_utility_swap();
}

} // namespace fnd::unittests
