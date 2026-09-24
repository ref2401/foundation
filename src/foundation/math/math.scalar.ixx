module;
#include <math.h>
#include "foundation/core/macros.h"


export module foundation.math:scalar;
export import foundation.core;

namespace fnd {

// ---------------------------------------------------------------------------
// Abs
// ---------------------------------------------------------------------------

// NOTE:
// MinValue has no positive counterpart: abs(int_t{-2147483648}) would be
// 2147483648, but kIntMaxValue is 2147483647 (likewise for long_t). MinValue
// is therefore outside the domain of the integer overloads and is asserted.
//
// The negation is done in the unsigned domain, so that in builds without
// assertions abs(MinValue) wraps back to MinValue, as in HLSL, instead of being
// signed overflow (undefined behaviour in C++).
//
// byte_t could negate directly, since x is promoted to int before the
// negation, so -x cannot overflow. It uses the same form for symmetry.

export constexpr byte_t abs(const byte_t x)
{
    FND_ASSERT(x != kByteMinValue);

    const ubyte_t ux = static_cast<ubyte_t>(x);
    return static_cast<byte_t>(x < 0 ? ubyte_t{0} - ux : ux);
}

export constexpr int_t abs(const int_t x)
{
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

// ---------------------------------------------------------------------------
// Comparison
// ---------------------------------------------------------------------------

export FND_INLINE bool approx_equal(
    const float_t a, const float_t b, const float_t max_abs_diff = 1e-5f)
{
    return abs(a - b) <= max_abs_diff;
}

// ---------------------------------------------------------------------------
// Trigonometry
// ---------------------------------------------------------------------------

export FND_INLINE float_t acos(const float_t x)
{
    return ::acosf(x);
}

export FND_INLINE double_t acos(const double_t x)
{
    return ::acos(x);
}

export FND_INLINE float_t asin(const float_t x)
{
    return ::asinf(x);
}

export FND_INLINE double_t asin(const double_t x)
{
    return ::asin(x);
}

export FND_INLINE float_t atan(const float_t x)
{
    return ::atanf(x);
}

export FND_INLINE double_t atan(const double_t x)
{
    return ::atan(x);
}

export FND_INLINE float_t atan2(const float_t y, const float_t x)
{
    return ::atan2f(y, x);
}

export FND_INLINE double_t atan2(const double_t y, const double_t x)
{
    return ::atan2(y, x);
}

export FND_INLINE float_t cos(const float_t x)
{
    return ::cosf(x);
}

export FND_INLINE double_t cos(const double_t x)
{
    return ::cos(x);
}

export FND_INLINE float_t sin(const float_t x)
{
    return ::sinf(x);
}

export FND_INLINE double_t sin(const double_t x)
{
    return ::sin(x);
}

export FND_INLINE float_t tan(const float_t x)
{
    return ::tanf(x);
}

export FND_INLINE double_t tan(const double_t x)
{
    return ::tan(x);
}

} // namespace fnd
