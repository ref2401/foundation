#pragma once

#include <stdint.h>

#if defined(FND_DEBUG)
    #define FND_ASSERT(condition)                                       \
        do {                                                            \
            if (!(condition)) {                                         \
                fnd::print_assert_message(                              \
                    #condition, __FILE__, __FUNCTION__, __LINE__);      \
                __debugbreak();                                         \
            }                                                           \
        } while (0)
#else
    // __noop parses its argument without evaluating it, which keeps the
    // asserted expression compiling -- and its variables 'referenced' -- in
    // builds where assertions are off.
    #define FND_ASSERT(condition) __noop(condition)
#endif // defined(FND_DEBUG)

#define FND_INLINE


namespace fnd {

void print_assert_message(
    const char* const message, const char* const filename, 
    const char* const function_name, const uint32_t line);

} // namespace fnd
