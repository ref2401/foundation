#include "foundation/core/macros.h"

#include <stdio.h>

namespace fnd {

void print_assert_message(
    const char* const message, const char* const filename, 
    const char* const function_name, const uint32_t line)
{
    fprintf_s(
        stderr, "%s(%u): assert failed in '%s'. \"%s\"\n",
        filename, line, function_name, message);
}

} // namespace fnd
