module;
#include <math.h>
#include "foundation/core/macros.h"

export module foundation.core:arithmetic;
import :arithmetic_types;

// NOTE:
// Arithmetic functions on the built-in types are split between this partition and
// foundation.math by one rule: a function lives here if its result is exact
// (no rounding: min, clamp, abs, floor, fmod, isnan, bit casts, ...), and in
// foundation.math if it approximates a real-valued function (sin, exp, log,
// sqrt, lerp, degrees, ...). 
// The goal is that importing foundation.core alone
// is enough to work with the built-in types; foundation.math is needed only
// for numerical, geometric or graphics code.

namespace fnd {

export template<typename TDest, typename TSrc>
requires (sizeof(TDest) == sizeof(TSrc)
    && __is_trivially_copyable(TDest) 
    && __is_trivially_copyable(TSrc))
constexpr TDest bit_cast(const TSrc& val)
{
    return __builtin_bit_cast(TDest, val);
}

export constexpr byte_t abs(const byte_t x)
{
    // x is promoted to int before the negation, so -x cannot overflow and no
    // unsigned arithmetic is needed. In builds without assertions abs(-128) is
    // 128, which the cast back to byte_t wraps to -128, as in the other overloads.
    FND_ASSERT(x != kByteMinValue);

    return static_cast<byte_t>(x < 0 ? -x : x);
}

export constexpr int_t abs(const int_t x)
{
    // NOTE:
    // MinValue has no positive counterpart: abs(int_t{-2147483648}) would be
    // 2147483648, but kIntMaxValue is 2147483647 (likewise for long_t). MinValue
    // is therefore outside the domain of the integer overloads and is asserted.
    //
    // The negation is done in the unsigned domain, so that in builds without
    // assertions abs(MinValue) wraps back to MinValue, as in HLSL, instead of being
    // signed overflow (undefined behaviour in C++).

    FND_ASSERT(x != kIntMinValue);

    const uint_t ux = static_cast<uint_t>(x);
    return static_cast<int_t>(x < 0 ? uint_t{0} - ux : ux);
}

export constexpr long_t abs(const long_t x)
{
    FND_ASSERT(x != kLongMinValue);

    const ulong_t ux = static_cast<ulong_t>(x);
    return static_cast<long_t>(x < 0 ? ulong_t{0} - ux : ux);
}

export FND_INLINE float_t abs(const float_t x)
{
    return ::fabsf(x);
}

export FND_INLINE double_t abs(const double_t x)
{
    return ::fabs(x);
}

export FND_INLINE bool_t isfinite(const float_t x)
{
    return ::isfinite(x);
}

export FND_INLINE bool_t isfinite(const double_t x)
{
    return ::isfinite(x);
}

export FND_INLINE bool_t isinf(const float_t x)
{
    return ::isinf(x);
}

export FND_INLINE bool_t isinf(const double_t x)
{
    return ::isinf(x);
}

export FND_INLINE bool_t isnan(const float_t x)
{
    return ::isnan(x);
}

export FND_INLINE bool_t isnan(const double_t x)
{
    return ::isnan(x);
}

export FND_INLINE bool_t approx_equal(
    const float_t a, const float_t b, const float_t max_abs_diff = 1e-5f)
{
    FND_ASSERT(max_abs_diff >= 0);

    // NOTE:
    // inf - inf is NaN, and abs(NaN) <= max_abs_diff is false.
    // Checking exact equality first makes approx_equal(inf, inf) true.
    return a == b || abs(a - b) <= max_abs_diff;
}

export FND_INLINE bool_t approx_equal(
    const double_t a, const double_t b, const double_t max_abs_diff = 1e-5)
{
    FND_ASSERT(max_abs_diff >= 0);

    return a == b || abs(a - b) <= max_abs_diff;
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

export constexpr byte_t clamp(
    const byte_t x, const byte_t lower, const byte_t upper)
{
    FND_ASSERT(lower <= upper);
    return min(max(x, lower), upper);
}

export constexpr int_t clamp(
    const int_t x, const int_t lower, const int_t upper)
{
    FND_ASSERT(lower <= upper);
    return min(max(x, lower), upper);
}

export constexpr long_t clamp(
    const long_t x, const long_t lower, const long_t upper)
{
    FND_ASSERT(lower <= upper);
    return min(max(x, lower), upper);
}

export constexpr ubyte_t clamp(
    const ubyte_t x, const ubyte_t lower, const ubyte_t upper)
{
    FND_ASSERT(lower <= upper);
    return min(max(x, lower), upper);
}

export constexpr uint_t clamp(
    const uint_t x, const uint_t lower, const uint_t upper)
{
    FND_ASSERT(lower <= upper);
    return min(max(x, lower), upper);
}

export constexpr ulong_t clamp(
    const ulong_t x, const ulong_t lower, const ulong_t upper)
{
    FND_ASSERT(lower <= upper);
    return min(max(x, lower), upper);
}

export FND_INLINE float_t clamp(
    const float_t x, const float_t lower, const float_t upper)
{
    // NOTE:
    // The result of clamp(NaN, -1, 1) depends on how clamp is composed from min and max: 
    // it can be -1 or 1. Rather than committing to one of those, x is asserted
    // to not be NaN.
    FND_ASSERT(!isnan(x)); 
    FND_ASSERT(lower <= upper);
    return min(max(x, lower), upper);
}

export FND_INLINE double_t clamp(
    const double_t x, const double_t lower, const double_t upper)
{
    FND_ASSERT(!isnan(x));
    FND_ASSERT(lower <= upper);
    return min(max(x, lower), upper);
}

export FND_INLINE float_t saturate(const float_t x)
{
    return clamp(x, 0.0f, 1.0f);
}

export FND_INLINE double_t saturate(const double_t x)
{
    return clamp(x, 0.0, 1.0);
}

// Returns -1, 0 or 1 in the type of x. Both zeros and NaN give +0.
export constexpr byte_t sign(const byte_t x)
{
    return static_cast<byte_t>((x > 0) - (x < 0));
}

export constexpr int_t sign(const int_t x)
{
    return (x > 0) - (x < 0);
}

export constexpr long_t sign(const long_t x)
{
    return (x > 0) - (x < 0);
}

export FND_INLINE float_t sign(const float_t x)
{
    // NOTE:
    // Not constexpr: MSVC 19.51's constant evaluator treats NaN < x and x < NaN
    // as true, so a compile-time sign(NaN) would return -1 instead of 0.
    return (x > 0.0f ? 1.0f : 0.0f) - (x < 0.0f ? 1.0f : 0.0f);
}

export FND_INLINE double_t sign(const double_t x)
{
    return (x > 0.0 ? 1.0 : 0.0) - (x < 0.0 ? 1.0 : 0.0);
}

export FND_INLINE float_t ceil(const float_t x)
{
    return ::ceilf(x);
}

export FND_INLINE double_t ceil(const double_t x)
{
    return ::ceil(x);
}

export FND_INLINE float_t floor(const float_t x)
{
    return ::floorf(x);
}

export FND_INLINE double_t floor(const double_t x)
{
    return ::floor(x);
}

export FND_INLINE float_t trunc(const float_t x)
{
    return ::truncf(x);
}

export FND_INLINE double_t trunc(const double_t x)
{
    return ::trunc(x);
}

export FND_INLINE float_t fmod(const float_t x, const float_t y)
{
    return ::fmodf(x, y);
}

export FND_INLINE double_t fmod(const double_t x, const double_t y)
{
    return ::fmod(x, y);
}

export FND_INLINE float_t modf(const float_t x, float_t& integer)
{
    return ::modff(x, &integer);
}

export FND_INLINE double_t modf(const double_t x, double_t& integer)
{
    return ::modf(x, &integer);
}

// Fractional part of |x|, in [0, 1). 
// fractional(-1e-10f) = 1e-10f;
// fractional(+-inf) is 0 and fractional(NaN) is NaN;
export FND_INLINE float_t fractional(const float_t x)
{
    // NOTE:
    // Not implemented as x - floor(x), because that returns 1 for tiny negative x. 
    // For x = -1e-10f, floor(x) is -1, and x + 1 is 0.9999999999.
    // That value doesn't fit in a float: the float just below 1 is 0.99999994f
    // (1 - 2^-24), and 1.0f is closer, so the result rounds to 1.

    float_t integer;
    return abs(modf(x, integer));
}

export FND_INLINE double_t fractional(const double_t x)
{
    double_t integer;
    return abs(modf(x, integer));
}

} // namespace fnd
