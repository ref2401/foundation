module;
#include "foundation/unittests.h"


export module unittests.math:matrix_conversion;
import foundation.core;
import foundation.math;

namespace fnd::unittests {

export void unittests_math_matrix_conversion();

// Small values whose products are exact in binary, so == is reliable for
// products and copies.
constexpr float3x3_t kConversionA3x3{
    float3_t{2, 1, 0}, float3_t{-1, 3, 1}, float3_t{0.5f, 0, 4}};
constexpr float3x3_t kConversionB3x3{
    float3_t{1, 0, -1}, float3_t{2, 1, 0}, float3_t{0, -1, 2}};

constexpr float3x4_t kConversionA3x4{
    float3_t{1, 0, 2}, float3_t{0, 1, 0}, float3_t{-1, 0, 1},
    float3_t{4, 5, 6}};
constexpr float3x4_t kConversionB3x4{
    float3_t{2, -1, 0}, float3_t{0.5f, 3, 1}, float3_t{-2, 0, 4},
    float3_t{-1, 2, 0.5f}};

// Not affine: its bottom row is 4, 8, 12, 16.
constexpr float4x4_t kConversion4x4{
    float4_t{1, 2, 3, 4}, float4_t{5, 6, 7, 8}, float4_t{9, 10, 11, 12},
    float4_t{13, 14, 15, 16}};

void unittests_math_matrix_conversion_make_float3x3()
{
    // From a float3x4_t: the linear part; the translation is dropped.
    FND_TEST_TRUE(make_float3x3(kConversionA3x4)
        == float3x3_t{kConversionA3x4.col0, kConversionA3x4.col1,
            kConversionA3x4.col2});
    FND_TEST_TRUE(
        make_float3x3(float3x4_t::kIdentity) == float3x3_t::kIdentity);

    // From a float4x4_t: the upper-left 3x3; the translation and the bottom
    // row are dropped.
    FND_TEST_TRUE(make_float3x3(kConversion4x4)
        == float3x3_t{
            float3_t{1, 2, 3}, float3_t{5, 6, 7}, float3_t{9, 10, 11}});
    FND_TEST_TRUE(
        make_float3x3(float4x4_t::kIdentity) == float3x3_t::kIdentity);

    // Round trips through a larger type give m back, and going through a
    // float4x4_t drops the same as going straight from the float3x4_t.
    FND_TEST_TRUE(
        make_float3x3(make_float3x4(kConversionA3x3)) == kConversionA3x3);
    FND_TEST_TRUE(
        make_float3x3(make_float4x4(kConversionA3x3)) == kConversionA3x3);
    FND_TEST_TRUE(make_float3x3(make_float4x4(kConversionA3x4))
        == make_float3x3(kConversionA3x4));

    // Usable in constant expressions.
    static_assert(make_float3x3(kConversion4x4).col2.z == 11.0f);
}

void unittests_math_matrix_conversion_make_float3x4()
{
    // From a float3x3_t: m as the linear part, with no translation; the same
    // as the trs builder with a zero translation.
    FND_TEST_TRUE(make_float3x4(kConversionA3x3)
        == float3x4_t{kConversionA3x3.col0, kConversionA3x3.col1,
            kConversionA3x3.col2, float3_t::kZero});
    FND_TEST_TRUE(make_float3x4(kConversionA3x3)
        == make_float3x4_trs(float3_t::kZero, kConversionA3x3));
    FND_TEST_TRUE(
        make_float3x4(float3x3_t::kIdentity) == float3x4_t::kIdentity);

    // From a float4x4_t: the top three rows; the bottom row is dropped.
    FND_TEST_TRUE(make_float3x4(kConversion4x4)
        == float3x4_t{float3_t{1, 2, 3}, float3_t{5, 6, 7},
            float3_t{9, 10, 11}, float3_t{13, 14, 15}});
    FND_TEST_TRUE(
        make_float3x4(float4x4_t::kIdentity) == float3x4_t::kIdentity);

    // A round trip through a float4x4_t gives m back.
    FND_TEST_TRUE(
        make_float3x4(make_float4x4(kConversionA3x4)) == kConversionA3x4);

    // A float3x3_t is a transform with no translation: the conversion
    // commutes with the product, the inverse and the determinant, and the
    // transformed direction is the same.
    FND_TEST_TRUE(make_float3x4(kConversionA3x3 * kConversionB3x3)
        == make_float3x4(kConversionA3x3) * make_float3x4(kConversionB3x3));
    FND_TEST_TRUE(approx_equal(make_float3x4(inverse(kConversionA3x3)),
        inverse(make_float3x4(kConversionA3x3))));
    FND_TEST_TRUE(approx_equal(determinant(make_float3x4(kConversionA3x3)),
        determinant(kConversionA3x3)));
    constexpr float3_t kDirection{3, -4, 12};
    FND_TEST_TRUE(all(mul_direction(make_float3x4(kConversionA3x3), kDirection)
        == mul(kConversionA3x3, kDirection)));

    // Usable in constant expressions.
    static_assert(make_float3x4(kConversion4x4).col3.z == 15.0f);
}

void unittests_math_matrix_conversion_make_float4x4()
{
    // From a float3x3_t: m as the upper-left 3x3, with no translation and the
    // bottom row 0, 0, 0, 1; the same as the trs builder with a zero
    // translation.
    FND_TEST_TRUE(make_float4x4(kConversionA3x3)
        == float4x4_t{float4_t{2, 1, 0, 0}, float4_t{-1, 3, 1, 0},
            float4_t{0.5f, 0, 4, 0}, float4_t{0, 0, 0, 1}});
    FND_TEST_TRUE(make_float4x4(kConversionA3x3)
        == make_float4x4_trs(float3_t::kZero, kConversionA3x3));
    FND_TEST_TRUE(
        make_float4x4(float3x3_t::kIdentity) == float4x4_t::kIdentity);

    // From a float3x4_t: m with its implicit bottom row 0, 0, 0, 1; the trs
    // builders agree.
    FND_TEST_TRUE(make_float4x4(kConversionA3x4)
        == float4x4_t{float4_t{1, 0, 2, 0}, float4_t{0, 1, 0, 0},
            float4_t{-1, 0, 1, 0}, float4_t{4, 5, 6, 1}});
    FND_TEST_TRUE(
        make_float4x4(float3x4_t::kIdentity) == float4x4_t::kIdentity);
    constexpr float3_t kTranslation{1, -2, 0.5f};
    FND_TEST_TRUE(
        make_float4x4(make_float3x4_trs(kTranslation, kConversionA3x3))
        == make_float4x4_trs(kTranslation, kConversionA3x3));

    // The float4x4_t is the same transform: the conversion commutes with the
    // product, the inverse and the determinant, and mul gives the same
    // vector, with w carried through.
    FND_TEST_TRUE(make_float4x4(kConversionA3x4 * kConversionB3x4)
        == make_float4x4(kConversionA3x4) * make_float4x4(kConversionB3x4));
    FND_TEST_TRUE(make_float4x4(kConversionA3x3 * kConversionB3x3)
        == make_float4x4(kConversionA3x3) * make_float4x4(kConversionB3x3));
    FND_TEST_TRUE(approx_equal(make_float4x4(inverse(kConversionB3x4)),
        inverse(make_float4x4(kConversionB3x4))));
    FND_TEST_TRUE(approx_equal(make_float4x4(inverse(kConversionA3x3)),
        inverse(make_float4x4(kConversionA3x3))));
    FND_TEST_TRUE(approx_equal(determinant(make_float4x4(kConversionB3x4)),
        determinant(kConversionB3x4)));
    FND_TEST_TRUE(approx_equal(determinant(make_float4x4(kConversionA3x3)),
        determinant(kConversionA3x3)));
    constexpr float4_t kPoint{3, -4, 12, 1};
    constexpr float4_t kDirection{3, -4, 12, 0};
    FND_TEST_TRUE(all(mul(make_float4x4(kConversionB3x4), kPoint)
        == float4(mul(kConversionB3x4, kPoint), 1)));
    FND_TEST_TRUE(all(mul(make_float4x4(kConversionB3x4), kDirection)
        == float4(mul(kConversionB3x4, kDirection), 0)));
    FND_TEST_TRUE(all(mul(make_float4x4(kConversionA3x3), kPoint)
        == float4(mul(kConversionA3x3, float3(kPoint)), 1)));

    // Usable in constant expressions.
    static_assert(make_float4x4(kConversionA3x4).col3.w == 1.0f);
}

void unittests_math_matrix_conversion()
{
    unittests_math_matrix_conversion_make_float3x3();
    unittests_math_matrix_conversion_make_float3x4();
    unittests_math_matrix_conversion_make_float4x4();
}

} // namespace fnd::unittests
