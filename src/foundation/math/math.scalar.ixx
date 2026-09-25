module;
#include <math.h>
#include "foundation/core/macros.h"


export module foundation.math:scalar;
export import foundation.core;

namespace fnd {

export constexpr float_t kFloatPi{3.14159265358979323846f};
export constexpr double_t kDoublePi{3.14159265358979323846};

export constexpr double_t kDoubleToDegrees{57.29577951308232};
export constexpr double_t kDoubleToRadians{0.017453292519943295};
export constexpr float_t kFloatToDegrees = static_cast<float_t>(kDoubleToDegrees);
export constexpr float_t kFloatToRadians = static_cast<float_t>(kDoubleToRadians);

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

} // namespace fnd
