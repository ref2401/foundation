module;
#include "foundation/core/macros.h"

export module foundation.math:quat;
import foundation.core;
import :scalar;
import :vector_float3;

namespace fnd {

// NOTE:
// A quaternion x * i + y * j + z * k + w: (x, y, z) is the vector part and w
// the scalar part. A rotation is a unit quaternion
//   (axis * sin(angle / 2), cos(angle / 2)),
// the same rotation as make_float3x3_axis_angle(axis, angle). q and -q are the
// same rotation. The product is the Hamilton product, and a * b applies b
// first, then a, as for matrices.
export struct quat_t final {
    static const quat_t kZero;
    static const quat_t kIdentity;

    float_t x{0};
    float_t y{0};
    float_t z{0};
    float_t w{0};

    constexpr quat_t() = default;

    constexpr quat_t(
        const float_t x, const float_t y, const float_t z, const float_t w)
        : x{x}, y{y}, z{z}, w{w}
    {
    }
};

constexpr quat_t quat_t::kZero{0, 0, 0, 0};
constexpr quat_t quat_t::kIdentity{0, 0, 0, 1};

export constexpr quat_t operator-(const quat_t q)
{
    return quat_t{-q.x, -q.y, -q.z, -q.w};
}

// Compares the components: q != -q, although they are the same rotation.
export constexpr bool_t operator==(const quat_t a, const quat_t b)
{
    return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

export constexpr bool_t operator!=(const quat_t a, const quat_t b)
{
    return !(a == b);
}

// The Hamilton product: the rotation b followed by the rotation a.
export constexpr quat_t operator*(const quat_t a, const quat_t b)
{
    return quat_t{
        a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
        a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
        a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w,
        a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z};
}

export constexpr quat_t operator*(const quat_t q, const float_t scalar)
{
    return quat_t{q.x * scalar, q.y * scalar, q.z * scalar, q.w * scalar};
}

export constexpr quat_t operator*(const float_t scalar, const quat_t q)
{
    return quat_t{scalar * q.x, scalar * q.y, scalar * q.z, scalar * q.w};
}

export constexpr quat_t operator+(const quat_t a, const quat_t b)
{
    return quat_t{a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

export constexpr quat_t& operator*=(quat_t& a, const quat_t b)
{
    a = a * b;
    return a;
}

export constexpr quat_t& operator*=(quat_t& a, const float_t scalar)
{
    a = a * scalar;
    return a;
}

export constexpr quat_t& operator+=(quat_t& a, const quat_t b)
{
    a = a + b;
    return a;
}

export FND_INLINE bool_t approx_equal(
    const quat_t a, const quat_t b, const float_t max_abs_diff = 1e-5f)
{
    FND_ASSERT(max_abs_diff >= 0);
    return approx_equal(a.x, b.x, max_abs_diff)
        && approx_equal(a.y, b.y, max_abs_diff)
        && approx_equal(a.z, b.z, max_abs_diff)
        && approx_equal(a.w, b.w, max_abs_diff);
}

// The vector part negated. For a unit quaternion it is the inverse rotation.
export constexpr quat_t conjugate(const quat_t q)
{
    return quat_t{-q.x, -q.y, -q.z, q.w};
}

export constexpr float_t dot(const quat_t a, const quat_t b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

export constexpr float_t length_sqr(const quat_t q)
{
    return q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
}

// conjugate(q) / length_sqr(q): q * inverse(q) == kIdentity for any nonzero q,
// not only for a unit one.
export constexpr quat_t inverse(const quat_t q)
{
    const float_t l2 = length_sqr(q);
    FND_ASSERT(l2 != 0.0f); // q is zero

    const float_t inv_l2 = 1.0f / l2;
    return inv_l2 * conjugate(q);
}

export FND_INLINE bool_t is_normalized(
    const quat_t q, const float_t max_abs_diff = 1e-4f)
{
    return approx_equal(length_sqr(q), 1.0f, max_abs_diff);
}

export FND_INLINE float_t length(const quat_t q)
{
    return sqrt(length_sqr(q));
}

// The rotation by angle_radians about axis, which must be normalized.
// Right-handed: a positive angle_radians rotates counter-clockwise when
// looking from the tip of axis toward the origin.
export FND_INLINE quat_t make_quat_axis_angle(
    const float3_t axis, const float_t angle_radians)
{
    FND_ASSERT(is_normalized(axis));

    const float_t ha = 0.5f * angle_radians;
    const float_t s = sin(ha);
    return quat_t{axis.x * s, axis.y * s, axis.z * s, cos(ha)};
}

// Rotates v by the unit quaternion q: q * v * conjugate(q).
export FND_INLINE float3_t mul(const quat_t q, const float3_t v)
{
    FND_ASSERT(is_normalized(q));

    // With u the vector part of q:
    //   v + 2 * w * (u x v) + 2 * u x (u x v)
    const float3_t u{q.x, q.y, q.z};
    const float3_t t = 2.0f * cross(u, v);
    return v + q.w * t + cross(u, t);
}

export FND_INLINE quat_t normalize(const quat_t q)
{
    const float_t l2 = length_sqr(q);
    FND_ASSERT(l2 > kFloatMinNormal);

    return q * rsqrt(l2);
}

// Normalized linear interpolation from a (t = 0) to b (t = 1); t outside
// [0, 1] extrapolates. b is negated when dot(a, b) < 0, so the result takes
// the shorter way between the rotations. The result is normalized; its
// angular speed is not constant (see slerp).
export FND_INLINE quat_t nlerp(const quat_t a, const quat_t b, const float_t t)
{
    FND_ASSERT(is_normalized(a));
    FND_ASSERT(is_normalized(b));

    const quat_t b_near = dot(a, b) < 0 ? -b : b;
    return normalize(a * (1 - t) + b_near * t);
}

// normalize(q), or default_value when q is too short to normalize.
export FND_INLINE quat_t normalize_safe(
    const quat_t q, const quat_t default_value = quat_t::kIdentity)
{
    FND_ASSERT(!isnan(q.x) && !isnan(q.y) && !isnan(q.z) && !isnan(q.w));

    quat_t res_quat = default_value;
    const float_t l2 = length_sqr(q);

    if (isinf(l2)) {
        // NOTE:
        // l2 is infinity (e.g. q = {1e20f, 1, 1, 1}).
        // q should be rescaled so there is no overflow.
        // Rescaling is ok because normalize(q) == normalize(q * s), s > 0
        //
        // Scaling by the largest absolute component needs no constant, but
        // costs abs, max and division instead of multiplication.
        //
        // 0x1p-66f is 2^-66. A power of two is exact: multiplying by it
        // lowers the exponent of each component by 66 and does not round.
        // Any 2^-k with 65 <= k <= 126 works:
        // - k >= 65: the scaled squares of four kFloatMaxValue components
        //      do not overflow;
        // - k <= 126: the scaled l2 stays a normal float.

        const quat_t scaled_quat = q * 0x1p-66f;
        res_quat = scaled_quat * rsqrt(length_sqr(scaled_quat));
    }
    else if (l2 > kFloatMinNormal) {
        res_quat = q * rsqrt(l2);
    }

    // post condition
    FND_ASSERT(
        !isnan(res_quat.x) && !isnan(res_quat.y) && !isnan(res_quat.z)
        && !isnan(res_quat.w));
    return res_quat;
}

// Spherical linear interpolation from a (t = 0) to b (t = 1) at constant
// angular speed; t outside [0, 1] extrapolates. b is negated when
// dot(a, b) < 0, so the result takes the shorter way between the rotations.
// For unit a and b the result is a unit quaternion up to rounding; it is not
// normalized again.
export FND_INLINE quat_t slerp(const quat_t a, const quat_t b, const float_t t)
{
    FND_ASSERT(is_normalized(a));
    FND_ASSERT(is_normalized(b));

    quat_t b_near = b;
    float_t d = dot(a, b);
    if (d < 0) {
        b_near = -b;
        d = -d;
    }

    // Fall back to nlerp when d is above this: the angle between a and b is
    // then below ~1.8 degrees, sin(angle) is close to 0 and dividing by it
    // loses precision, while nlerp is accurate there.
    if (d > 0.9995f) {
        return nlerp(a, b_near, t);
    }

    const float_t angle = acos(d);
    const float_t inv_sin_angle = 1.0f / sin(angle);
    const float_t wa = sin((1 - t) * angle) * inv_sin_angle;
    const float_t wb = sin(t * angle) * inv_sin_angle;
    return a * wa + b_near * wb;
}

} // namespace fnd
