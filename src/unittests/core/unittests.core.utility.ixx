module;
#include "foundation/unittests.h"


export module unittests.core:utility;
import foundation.core;

namespace fnd::unittests {

export void unittests_core_utility();

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
    static_assert([] {
        int_t b{4};
        int_t& lr{forward<int_t&>(b)};
        int_t&& rr{forward<int_t>(b)};
        return &lr == &b && &rr == &b && b == 4;
    }());
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
    static_assert([] {
        int_t b{1};
        int_t&& r{move(b)};
        return &r == &b && b == 1;
    }());

    // Usable in constant expressions.
    static_assert([] { return move(5); }() == 5);
}

void unittests_core_utility_exchange()
{
    struct exchange_test_t {
        int_t x;
        int_t y;
    };

    // Cannot be copied: exchange compiles for it only if it never copies.
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
    static_assert([] {
        int_t b{1};
        const int_t old_value{exchange(b, 2)};
        return old_value == 1 && b == 2;
    }());
    static_assert([] {
        int_t b{1};
        const int_t c{2};
        const int_t old_value{exchange(b, c)};
        return old_value == 1 && b == 2 && c == 2;
    }());
    static_assert([] {
        int_t b{1};
        int_t* q{&b};
        int_t* const old_value{exchange(q, nullptr)};
        return old_value == &b && q == nullptr;
    }());
    static_assert([] {
        exchange_test_t t{1, 2};
        const exchange_test_t old_value{exchange(t, {3, 4})};
        return old_value.x == 1 && old_value.y == 2 && t.x == 3 && t.y == 4;
    }());
    static_assert([] {
        MoveOnly n{1};
        const MoveOnly old_value{exchange(n, MoveOnly{2})};
        return old_value.value() == 1 && n.value() == 2;
    }());
}

void unittests_core_utility()
{
    unittests_core_utility_forward();
    unittests_core_utility_move();
    unittests_core_utility_exchange();
}

} // namespace fnd::unittests
