export module unittests.math;
import :scalar;
import :vector_bool;
import :vector_conversion;
import :vector_float2;
import :vector_float3;
import :vector_float4;
import :vector_int2;
import :vector_int3;
import :vector_int4;
import :vector_uint2;
import :vector_uint3;
import :vector_uint4;

namespace fnd::unittests {

export void run_unittests_math()
{
    unittests_math_scalar();
    unittests_math_vector_bool();
    unittests_math_vector_conversion();
    unittests_math_vector_float2();
    unittests_math_vector_float3();
    unittests_math_vector_float4();
    unittests_math_vector_int2();
    unittests_math_vector_int3();
    unittests_math_vector_int4();
    unittests_math_vector_uint2();
    unittests_math_vector_uint3();
    unittests_math_vector_uint4();
}

} // namespace fnd::unittests
