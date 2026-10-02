module;
#include "foundation/unittests.h"


export module unittests.core:type_traits;
import foundation.core;

namespace fnd::unittests {

export void unittests_core_type_traits();

struct is_same_test_t {
    int_t i;
};

using is_same_test_alias_t = is_same_test_t;

void unittests_core_type_traits_is_same()
{
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
    unittests_core_type_traits_is_same();
}

} // namespace fnd::unittests
