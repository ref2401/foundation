#include "foundation/core/macros.h"

#include <stdarg.h>
#include <stdio.h>
#include <windows.h>

namespace fnd {

void print_assert_message(
    const char* const message, const char* const filename, 
    const char* const function_name, const uint32_t line)
{
    constexpr uint32_t kByteCount{1024};

    char buffer[kByteCount];
    snprintf(
        buffer, kByteCount, "[ERROR] %s - %s(%u): %s", filename, 
        function_name, line, message);

    OutputDebugStringA(buffer);
}

} // namespace fnd
