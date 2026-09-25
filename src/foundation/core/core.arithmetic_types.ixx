module;
#include <float.h>
#include <math.h>
#include <stdint.h>

export module foundation.core:arithmetic_types;

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
export constexpr float_t kFloatMinSubnormal{FLT_TRUE_MIN};
export constexpr float_t kFloatMinNormal{FLT_MIN};
export constexpr float_t kFloatEpsilon{FLT_EPSILON};

export constexpr double_t kDoubleMinValue{-DBL_MAX};
export constexpr double_t kDoubleMaxValue{DBL_MAX};
export constexpr double_t kDoubleNaN{NAN};
export constexpr double_t kDoubleInfinity{INFINITY};
export constexpr double_t kDoubleMinSubnormal{DBL_TRUE_MIN};
export constexpr double_t kDoubleMinNormal{DBL_MIN};
export constexpr double_t kDoubleEpsilon{DBL_EPSILON};

} // namespace fnd
