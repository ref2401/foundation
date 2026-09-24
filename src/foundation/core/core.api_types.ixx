module;
#include <float.h>
#include <math.h>
#include <stdint.h>
#include "foundation/core/macros.h"

export module foundation.core:api_types;
import :bits;

namespace fnd {

// signed
export using byte_t = ::int8_t;
export using int_t = ::int32_t;
export using long_t = ::int64_t;
export using float_t = float;
export using double_t = double;
// unsigned
export using ubyte_t = ::uint8_t;
export using uint_t = ::uint32_t;
export using ulong_t = ::uint64_t;
// characters
export using char_t = char;

export constexpr byte_t kByteMinValue{-128};
export constexpr byte_t kByteMaxValue{127};
export constexpr int_t kIntMinValue{INT32_MIN};
export constexpr int_t kIntMaxValue{INT32_MAX};
export constexpr long_t kLongMinValue{INT64_MIN};
export constexpr long_t kLongMaxValue{INT64_MAX};
export constexpr ubyte_t kUByteMinValue{0};
export constexpr ubyte_t kUByteMaxValue{UINT8_MAX};
export constexpr uint_t kUIntMinValue{0};
export constexpr uint_t kUIntMaxValue{UINT32_MAX};
export constexpr ulong_t kULongMinValue{0};
export constexpr ulong_t kULongMaxValue{UINT64_MAX};

export constexpr float_t kFloatMinValue{-FLT_MAX};
export constexpr float_t kFloatMaxValue{FLT_MAX};
export constexpr float_t kFloatNaN{NAN};
export constexpr float_t kFloatInfinity{INFINITY};
export constexpr float_t kFloatPi{3.14159265358979323846f};
export constexpr float_t kFloatMinSubnormal{FLT_TRUE_MIN};
export constexpr float_t kFloatMinNormal{FLT_MIN};
export constexpr float_t kFloatEpsilon{FLT_EPSILON};

export constexpr double_t kDoubleMinValue{-DBL_MAX};
export constexpr double_t kDoubleMaxValue{DBL_MAX};
export constexpr double_t kDoubleNaN{NAN};
export constexpr double_t kDoubleInfinity{INFINITY};
export constexpr double_t kDoublePi{3.14159265358979323846};
export constexpr double_t kDoubleMinSubnormal{DBL_TRUE_MIN};
export constexpr double_t kDoubleMinNormal{DBL_MIN};
export constexpr double_t kDoubleEpsilon{DBL_EPSILON};

export FND_INLINE bool isfinite(const float_t x)
{
    return ::isfinite(x);
}

export FND_INLINE bool isfinite(const double_t x)
{
    return ::isfinite(x);
}

export FND_INLINE bool isinf(const float_t x)
{
    return ::isinf(x);
}

export FND_INLINE bool isinf(const double_t x)
{
    return ::isinf(x);
}

export FND_INLINE bool isnan(const float_t x)
{
    return ::isnan(x);
}

export FND_INLINE bool isnan(const double_t x)
{
    return ::isnan(x);
}

export constexpr byte_t min(const byte_t a, const byte_t b)
{
    return a < b ? a : b;
}

export constexpr int_t min(const int_t a, const int_t b)
{
    return a < b ? a : b;
}

export constexpr long_t min(const long_t a, const long_t b)
{
    return a < b ? a : b;
}

export constexpr ubyte_t min(const ubyte_t a, const ubyte_t b)
{
    return a < b ? a : b;
}

export constexpr uint_t min(const uint_t a, const uint_t b)
{
    return a < b ? a : b;
}

export constexpr ulong_t min(const ulong_t a, const ulong_t b)
{
    return a < b ? a : b;
}

export FND_INLINE float_t min(const float_t a, const float_t b)
{
    return isnan(b) || a < b ? a : b;
}

export FND_INLINE double_t min(const double_t a, const double_t b)
{
    return isnan(b) || a < b ? a : b;
}

export constexpr byte_t max(const byte_t a, const byte_t b)
{
    return a > b ? a : b;
}

export constexpr int_t max(const int_t a, const int_t b)
{
    return a > b ? a : b;
}

export constexpr long_t max(const long_t a, const long_t b)
{
    return a > b ? a : b;
}

export constexpr ubyte_t max(const ubyte_t a, const ubyte_t b)
{
    return a > b ? a : b;
}

export constexpr uint_t max(const uint_t a, const uint_t b)
{
    return a > b ? a : b;
}

export constexpr ulong_t max(const ulong_t a, const ulong_t b)
{
    return a > b ? a : b;
}

export FND_INLINE float_t max(const float_t a, const float_t b)
{
    return isnan(b) || a > b ? a : b;
}

export FND_INLINE double_t max(const double_t a, const double_t b)
{
    return isnan(b) || a > b ? a : b;
}

export constexpr byte_t clamp(const byte_t x, const byte_t lower, const byte_t upper)
{
    FND_ASSERT(lower <= upper);
    return min(max(x, lower), upper);
}

export constexpr int_t clamp(const int_t x, const int_t lower, const int_t upper)
{
    FND_ASSERT(lower <= upper);
    return min(max(x, lower), upper);
}

export constexpr long_t clamp(const long_t x, const long_t lower, const long_t upper)
{
    FND_ASSERT(lower <= upper);
    return min(max(x, lower), upper);
}

export constexpr ubyte_t clamp(const ubyte_t x, const ubyte_t lower, const ubyte_t upper)
{
    FND_ASSERT(lower <= upper);
    return min(max(x, lower), upper);
}

export constexpr uint_t clamp(const uint_t x, const uint_t lower, const uint_t upper)
{
    FND_ASSERT(lower <= upper);
    return min(max(x, lower), upper);
}

export constexpr ulong_t clamp(const ulong_t x, const ulong_t lower, const ulong_t upper)
{
    FND_ASSERT(lower <= upper);
    return min(max(x, lower), upper);
}

export FND_INLINE float_t clamp(const float_t x, const float_t lower, const float_t upper)
{
    // NOTE:
    // The result of clamp(NaN, -1, 1) depends on how clamp is composed from min and max: 
    // it can be -1 or 1. Rather than committing to one of those, x is asserted
    // to not be NaN.
    FND_ASSERT(!isnan(x)); 
    FND_ASSERT(lower <= upper);
    return min(max(x, lower), upper);
}

export FND_INLINE double_t clamp(const double_t x, const double_t lower, const double_t upper)
{
    FND_ASSERT(!isnan(x));
    FND_ASSERT(lower <= upper);
    return min(max(x, lower), upper);
}

} // namespace fnd
