module;
#include <stdint.h>

export module foundation.core:api_types;

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

} // namespace fnd
