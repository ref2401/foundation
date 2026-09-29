module;
#include "foundation/core/macros.h"

export module foundation.math:matrix_float3x3;
import foundation.core;
import :scalar;
import :vector_float3;
import :vector_float4;

namespace fnd {

export struct float3x3_t final {
    float3_t col0;
    float3_t col1;
    float3_t col2;
};

} // namespace fnd
