module;
#include <math.h>
#include "foundation/core/macros.h"


export module foundation.math:scalar;
export import foundation.core;

namespace fnd {

export constexpr double_t kDoubleToDegrees{57.29577951308232};
export constexpr double_t kDoubleToRadians{0.017453292519943295};
export constexpr float_t kFloatToDegrees = static_cast<float_t>(kDoubleToDegrees);
export constexpr float_t kFloatToRadians = static_cast<float_t>(kDoubleToRadians);


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

export FND_INLINE bool approx_equal(
    const float_t a, const float_t b, const float_t max_abs_diff = 1e-5f)
{
    FND_ASSERT(max_abs_diff >= 0);

    // NOTE:
    // inf - inf is NaN, and abs(NaN) <= max_abs_diff is false. 
    // Checking exact equality first makes approx_equal(inf, inf) true.
    return a == b || abs(a - b) <= max_abs_diff;
}

export FND_INLINE bool approx_equal(
    const double_t a, const double_t b, const double_t max_abs_diff = 1e-5)
{
    FND_ASSERT(max_abs_diff >= 0);

    return a == b || abs(a - b) <= max_abs_diff;
}

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

export constexpr float_t degrees(const float_t rads)
{
    return rads * kFloatToDegrees;
}

export constexpr double_t degrees(const double_t rads)
{
    return rads * kDoubleToDegrees;
}

export constexpr float_t radians(const float_t degs)
{
    return degs * kFloatToRadians;
}

export constexpr double_t radians(const double_t degs)
{
    return degs * kDoubleToRadians;
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

export FND_INLINE float_t saturate(const float_t x)
{
    return clamp(x, 0.0f, 1.0f);
}

export FND_INLINE double_t saturate(const double_t x)
{
    return clamp(x, 0.0, 1.0);
}

export FND_INLINE float_t lerp(
    const float_t a, const float_t b, const float_t t)
{
    // NOTE: Unclamped t outside [0, 1] extrapolates.
    return a + t * (b - a);
}

export FND_INLINE double_t lerp(
    const double_t a, const double_t b, const double_t t)
{
    return a + t * (b - a);
}

export FND_INLINE float_t smoothstep(
    const float_t edge0, const float_t edge1, const float_t x)
{
    FND_ASSERT(edge0 != edge1);
    
    const float_t t = saturate((x - edge0) / (edge1 - edge0));
    return t * t * (3.0f - 2.0f * t);
}

export FND_INLINE double_t smoothstep(
    const double_t edge0, const double_t edge1, const double_t x)
{
    FND_ASSERT(edge0 != edge1);

    const double_t t = saturate((x - edge0) / (edge1 - edge0));
    return t * t * (3.0 - 2.0 * t);
}

export FND_INLINE float_t pow(const float_t base, const float_t exponent)
{
    // NOTE:
    // Domain errors as the C standard defines them for pow: a finite negative
    // base with a finite non-integer exponent (the result would be complex), and
    // 0 to the power 0.
    FND_ASSERT(!(isfinite(base) && base < 0 && isfinite(exponent) && trunc(exponent) != exponent));
    FND_ASSERT(!(base == 0 && exponent == 0));

    return ::powf(base, exponent);
}

export FND_INLINE double_t pow(const double_t base, const double_t exponent)
{
    FND_ASSERT(!(isfinite(base) && base < 0 && isfinite(exponent) && trunc(exponent) != exponent));
    FND_ASSERT(!(base == 0 && exponent == 0));

    return ::pow(base, exponent);
}

export FND_INLINE float_t rcp(const float_t x)
{
    FND_ASSERT(x != 0);
    FND_ASSERT(!isnan(x));

    return 1.0f / x;
}

export FND_INLINE double_t rcp(const double_t x)
{
    FND_ASSERT(x != 0);
    FND_ASSERT(!isnan(x));

    return 1.0 / x;
}

export FND_INLINE float_t sqrt(const float_t x)
{
    FND_ASSERT(x >= 0);

    return ::sqrtf(x);
}

export FND_INLINE double_t sqrt(const double_t x)
{
    FND_ASSERT(x >= 0);

    return ::sqrt(x);
}

export FND_INLINE float_t rsqrt(const float_t x)
{
    FND_ASSERT(x > 0);

    return 1.0f / ::sqrtf(x);
}

export FND_INLINE double_t rsqrt(const double_t x)
{
    FND_ASSERT(x > 0);

    return 1.0 / ::sqrt(x);
}

export FND_INLINE float_t exp(const float_t x)
{
    return ::expf(x);
}

export FND_INLINE double_t exp(const double_t x)
{
    return ::exp(x);
}

export FND_INLINE float_t exp2(const float_t x)
{
    return ::exp2f(x);
}

export FND_INLINE double_t exp2(const double_t x)
{
    return ::exp2(x);
}

export FND_INLINE float_t log(const float_t x)
{
    FND_ASSERT(x > 0);

    return ::logf(x);
}

export FND_INLINE double_t log(const double_t x)
{
    FND_ASSERT(x > 0);

    return ::log(x);
}

export FND_INLINE float_t log2(const float_t x)
{
    FND_ASSERT(x > 0);

    return ::log2f(x);
}

export FND_INLINE double_t log2(const double_t x)
{
    FND_ASSERT(x > 0);

    return ::log2(x);
}

export FND_INLINE float_t log10(const float_t x)
{
    FND_ASSERT(x > 0);

    return ::log10f(x);
}

export FND_INLINE double_t log10(const double_t x)
{
    FND_ASSERT(x > 0);

    return ::log10(x);
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
