module;
#include "foundation/unittests.h"


export module unittests.core:type_traits;
import foundation.core;

namespace fnd::unittests {

export void unittests_core_type_traits();

void unittests_core_type_traits_unref()
{
    struct unref_test_t { int_t i; };

    // A type that is not a reference stays as it is.
    static_assert(is_same<Unref<int_t>, int_t>());
    static_assert(is_same<Unref<unref_test_t>, unref_test_t>());
    static_assert(is_same<Unref<int_t*>, int_t*>());
    static_assert(is_same<Unref<int_t[3]>, int_t[3]>());

    // Both kinds of reference are removed.
    static_assert(is_same<Unref<int_t&>, int_t>());
    static_assert(is_same<Unref<int_t&&>, int_t>());
    static_assert(is_same<Unref<unref_test_t&>, unref_test_t>());
    static_assert(is_same<Unref<unref_test_t&&>, unref_test_t>());

    // const and volatile are kept.
    static_assert(is_same<Unref<const int_t>, const int_t>());
    static_assert(is_same<Unref<const int_t&>, const int_t>());
    static_assert(is_same<Unref<volatile int_t&&>, volatile int_t>());
    static_assert(
        is_same<Unref<const volatile int_t&>, const volatile int_t>());

    // Only the outer reference goes: a pointer stays a pointer, and the const
    // of a const pointer stays.
    static_assert(is_same<Unref<int_t*&>, int_t*>());
    static_assert(is_same<Unref<int_t* const&>, int_t* const>());
    static_assert(is_same<Unref<const int_t*&&>, const int_t*>());

    // References to arrays and to functions.
    static_assert(is_same<Unref<int_t(&)[3]>, int_t[3]>());
    static_assert(is_same<Unref<int_t(&&)[3]>, int_t[3]>());
    static_assert(is_same<Unref<void (&)(int_t)>, void(int_t)>());

    // Removing it again changes nothing.
    static_assert(is_same<Unref<Unref<int_t&>>, int_t>());
}

void unittests_core_type_traits_is_same()
{
    struct is_same_test_t { int_t i; };
    using is_same_test_alias_t = is_same_test_t;

    // A type is the same as itself and as its aliases.
    static_assert(is_same<int_t, int_t>());
    static_assert(is_same<int_t, int>());
    static_assert(is_same<float_t, float>());
    static_assert(is_same<is_same_test_t, is_same_test_alias_t>());

    // Different types, even of the same size or with a conversion.
    static_assert(!is_same<int_t, uint_t>());
    static_assert(!is_same<int_t, long_t>());
    static_assert(!is_same<float_t, double_t>());
    static_assert(!is_same<int_t, float_t>());
    static_assert(!is_same<char_t, byte_t>());
    static_assert(!is_same<char_t, ubyte_t>());

    // const, volatile, references and pointers make a different type.
    static_assert(!is_same<int_t, const int_t>());
    static_assert(!is_same<int_t, volatile int_t>());
    static_assert(!is_same<int_t, int_t&>());
    static_assert(!is_same<int_t&, int_t&&>());
    static_assert(!is_same<int_t, int_t*>());
    static_assert(!is_same<int_t*, const int_t*>());
    static_assert(is_same<const int_t*, const int_t*>());

    // The order of the arguments does not matter.
    static_assert(!is_same<uint_t, int_t>());
    static_assert(is_same<int, int_t>());
}

void unittests_core_type_traits()
{
    unittests_core_type_traits_unref();
    unittests_core_type_traits_is_same();
}

} // namespace fnd::unittests
