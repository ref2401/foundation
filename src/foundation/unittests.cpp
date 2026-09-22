#include "foundation/unittests.h"

#include <stdio.h>
#include <windows.h>

namespace fnd {

void test_true(
    const bool condition, const char_t* const message, 
    const source_location_t srcloc)
{
    if (condition) return;

    constexpr uint_t kMessageBufferByteCount{2048};
    char_t message_buffer[kMessageBufferByteCount];

    snprintf(
        message_buffer, kMessageBufferByteCount, 
        "[Unittest '%s' failed]: \"%s\"; %s(%u)\n", srcloc.function_name, message,
        srcloc.filename, srcloc.line);
    OutputDebugStringA(message_buffer);
}

} // namespace fnd
