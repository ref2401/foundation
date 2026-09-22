export module foundation.core;
export import :api_types;
export import :span;

namespace fnd {

// ---------------------------------------------------------------------------
// source_location_t
// ---------------------------------------------------------------------------

export struct source_location_t final {
    const char_t* filename;
    const char_t* function_name;
    uint_t line;
};

export consteval source_location_t make_source_location(
    const char_t* const filename = __builtin_FILE(), 
    const char_t* const function_name = __builtin_FUNCTION(), 
    const uint_t line = __builtin_LINE())
{
    return {filename, function_name, line};
}

} // namespace fnd