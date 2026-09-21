module;

#include <stdint.h>

export module foundation.core;

namespace fnd {

// ---------------------------------------------------------------------------
// Built in types
// ---------------------------------------------------------------------------

// signed
export using byte_t = ::int8_t;
export using int_t = ::int32_t;
export using long_t = ::int64_t;
export using float_t = float;
// unsigned
export using ubyte_t = ::uint8_t;
export using uint_t = ::uint32_t;
export using ulong_t = ::uint64_t;
// characters
export using char_t = char;

// ---------------------------------------------------------------------------
// source_location_t
// ---------------------------------------------------------------------------

export struct source_location_t final {
    const char_t* filename;
    const char_t* function_name;
    uint_t line;
};

export consteval source_location_t make_source_location(
    const char_t* const filename = __builtin_FILE(), 
    const char_t* const function_name = __builtin_FUNCTION(), 
    const uint_t line = __builtin_LINE())
{
    return{filename, function_name, line};
}

}
