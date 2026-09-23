module;
#include "foundation/unittests.h"


export module unittests.core:span;

namespace fnd::unittests {

export void unittests_span_t();

void unittests_span_t_equality_operator()
{
    const uint_t* expected_pointer{reinterpret_cast<uint_t*>(0x123ABC)};
    constexpr ulong_t kExpectedCount{42};

    const span_t<const uint_t> span{expected_pointer, kExpectedCount};
    const span_t<const uint_t> span_copy{span};

    FND_TEST_TRUE(span != span_t<const uint_t>{nullptr, kExpectedCount});
    FND_TEST_TRUE(span != span_t{expected_pointer, 16});
    FND_TEST_TRUE(span == span_copy);
    FND_TEST_FALSE(span != span_copy);
}

void unittests_span_t_is_empty()
{
    FND_TEST_TRUE(is_empty(span_t<uint_t>{}));
    FND_TEST_TRUE(is_empty(span_t{reinterpret_cast<uint_t*>(0x123ABC), 0}));
    FND_TEST_TRUE(is_empty(span_t<uint_t>{nullptr, 12}));
    FND_TEST_FALSE(is_empty(span_t{reinterpret_cast<uint_t*>(0x123ABC), 12}));
}

void unittests_span_t_is_pod_type()
{
    static_assert(PodType<span_t<char_t>>);
    static_assert(PodType<span_t<uint_t>>);
    static_assert(PodType<span_t<void*>>);
}

void unittests_span_t_subscript_operator()
{
    constexpr uint_t kItemCount{16};
    uint_t array[kItemCount] = { 
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    
    span_t<uint_t> span(array, kItemCount);
    for (uint_t i = 0; i < kItemCount; ++i)
        FND_TEST_TRUE(array[i] == span[i]);
    
    const span_t<uint_t> const_span(array, kItemCount);
    for (uint_t i = 0; i < kItemCount; ++i)
        FND_TEST_TRUE(array[i] == const_span[i]);
}

void unittests_span_t()
{
    unittests_span_t_equality_operator();
    unittests_span_t_is_empty();
    unittests_span_t_is_pod_type();
    unittests_span_t_subscript_operator();
}

} // namespace fnd::unittests 
