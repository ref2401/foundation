#pragma once

#include <stdint.h>

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

#define FND_INLINE


namespace fnd {

void print_assert_message(
    const char* const failed_condition, const char* const message,
    const char* const filename, const char* const function_name,
    const uint32_t line);

} // namespace fnd
