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

void unittests_core_utility()
{
    unittests_core_utility_forward();
    unittests_core_utility_move();
}

} // namespace fnd::unittests
