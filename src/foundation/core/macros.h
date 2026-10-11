#pragma once

#include <stdint.h>

// ---------------------------------------------------------------------------
// FND_ASSERT & FND_ASSERT_MSG
// ---------------------------------------------------------------------------

#if defined(FND_DEBUG)
    #define FND_ASSERT_IMPL(condition, failed_condition, message)      \
        do {                                                           \
            if (!(condition)) {                                        \
                fnd::print_assert_message(                             \
                    failed_condition, message, __FILE__, __FUNCTION__, \
                    __LINE__);                                         \
                __debugbreak();                                        \
            }                                                          \
        } while (0)
    #define FND_ASSERT(condition) FND_ASSERT_IMPL(condition, #condition, "")
    #define FND_ASSERT_MSG(condition, message) \
        FND_ASSERT_IMPL(condition, #condition, message)
#else
    // __noop parses its arguments without evaluating it, which keeps the
    // asserted expression compiling -- and its variables 'referenced' -- in
    // builds where assertions are off.
    #define FND_ASSERT(condition) __noop(condition)
    #define FND_ASSERT_MSG(condition, message) __noop(condition, message)
#endif // defined(FND_DEBUG)

// ---------------------------------------------------------------------------
// FND_INLINE
// ---------------------------------------------------------------------------

#define FND_INLINE

// ---------------------------------------------------------------------------
// FND_CAST_FUNCTION
// ---------------------------------------------------------------------------

// For a function whose body is a single cast of its parameter, such as move and
// forward: MSVC replaces each call with the cast itself, in Debug builds too.
#if __has_cpp_attribute(msvc::intrinsic)
    #define FND_CAST_FUNCTION [[msvc::intrinsic]]
#else
    #define FND_CAST_FUNCTION
#endif


namespace fnd {

void print_assert_message(
    const char* const failed_condition, const char* const message,
    const char* const filename, const char* const function_name,
    const uint32_t line);

} // namespace fnd
