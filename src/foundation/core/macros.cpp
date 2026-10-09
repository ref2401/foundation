#include "foundation/core/macros.h"

#include <stdio.h>

namespace fnd {

void print_assert_message(
    const char* const failed_condition, const char* const message,
    const char* const filename, const char* const function_name,
    const uint32_t line)
{
    if (message != nullptr && message[0] != '\0') {
        fprintf_s(
            stderr, "%s(%u): assert failed in '%s'. \"%s\" - %s\n", filename,
            line, function_name, failed_condition, message);
    }
    else {
        fprintf_s(
            stderr, "%s(%u): assert failed in '%s'. \"%s\"\n", filename, line,
            function_name, failed_condition);
    }
}

} // namespace fnd
