module;
#include "foundation/unittests.h"


export module unittests.core:arithmetic_types;
import foundation.core;

namespace fnd::unittests {

export void unittests_core_arithmetic_types();

// ---------------------------------------------------------------------------
// Built in types
// ---------------------------------------------------------------------------

void unittests_core_arithmetic_type_definitions()
{
    // byte_t
    static_assert(sizeof(byte_t) == 1, "byte_t must be 1 byte");
    static_assert(byte_t{-1} < byte_t{0}, "byte_t must be signed");
    // int_t
    static_assert(sizeof(int_t) == 4, "int_t must be 4 bytes");
    static_assert(int_t{-1} < int_t{0}, "int_t must be signed");
    // long_t
    static_assert(sizeof(long_t) == 8, "long_t must be 8 bytes");
    static_assert(long_t{-1} < long_t{0}, "long_t must be signed");
    // float
    static_assert(sizeof(float_t) == 4, "float_t must be 4 bytes");
    static_assert(sizeof(double_t) == 8, "float_t must be 8 bytes");

    // ubyte_t
    static_assert(sizeof(ubyte_t) == 1, "ubyte_t must be 1 byte");
    static_assert(ubyte_t(-1) > ubyte_t{0}, "ubyte_t must be unsigned");
    // uint_t
    static_assert(sizeof(uint_t) == 4, "uint_t must be 4 bytes");
    static_assert(uint_t(-1) > uint_t{0}, "uint_t must be unsigned");
    // ulong_t
    static_assert(sizeof(ulong_t) == 8, "ulong_t must be 8 bytes");
    static_assert(ulong_t(-1) > ulong_t{0}, "ulong_t must be unsigned");

    static_assert(sizeof(void*) == 8, "foundation targets 64-bit only");
}

void unittests_core_arithmetic_types()
{
    unittests_core_arithmetic_type_definitions();
}

} // namespace fnd::unittests
