module;
#include "foundation/unittests.h"


export module unittests.memory:utility;
import foundation.memory;

namespace fnd::unittests {

export void unittests_memory_utility();

// Every power-of-two alignment up to that of the test buffers.
constexpr ulong_t kAlignments[]{1, 2, 4, 8, 16, 32, 64, 128, 256};

void unittests_memory_utility_align_up()
{
    alignas(256) ubyte_t buffer[512]{};

    // An aligned pointer stays where it is.
    FND_TEST_TRUE(align_up(buffer, 256) == buffer);
    FND_TEST_TRUE(align_up(buffer + 16, 16) == buffer + 16);

    // Otherwise it moves forward to the next multiple of alignment.
    FND_TEST_TRUE(align_up(buffer + 1, 16) == buffer + 16);
    FND_TEST_TRUE(align_up(buffer + 15, 16) == buffer + 16);
    FND_TEST_TRUE(align_up(buffer + 17, 16) == buffer + 32);
    FND_TEST_TRUE(align_up(buffer + 33, 64) == buffer + 64);
    FND_TEST_TRUE(align_up(buffer + 1, 256) == buffer + 256);

    // Every offset and alignment: the result is aligned, not before the
    // pointer, less than alignment after it, and the closest such address.
    // A pointer to const gives the same address.
    for (ulong_t offset{0}; offset < 128; ++offset) {
        for (const ulong_t alignment : kAlignments) {
            ubyte_t* const ptr{buffer + offset};
            const ulong_t expected_offset{
                (offset + alignment - 1) / alignment * alignment};

            ubyte_t* const res_ptr{
                static_cast<ubyte_t*>(align_up(ptr, alignment))};
            FND_TEST_TRUE(res_ptr == buffer + expected_offset);
            FND_TEST_TRUE(is_aligned(res_ptr, alignment));
            FND_TEST_TRUE(res_ptr >= ptr);
            FND_TEST_TRUE(res_ptr < ptr + alignment);

            const ubyte_t* const const_ptr{ptr};
            FND_TEST_TRUE(align_up(const_ptr, alignment) == res_ptr);
        }
    }

    // Alignment 1 never moves a pointer; nullptr stays nullptr.
    FND_TEST_TRUE(align_up(buffer + 7, 1) == buffer + 7);
    FND_TEST_TRUE(align_up(static_cast<void*>(nullptr), 64) == nullptr);
    FND_TEST_TRUE(align_up(static_cast<const void*>(nullptr), 64) == nullptr);

    // A pointer to const keeps its constness; an aligned one stays where it
    // is.
    const ubyte_t* const const_ptr{buffer + 3};
    static_assert(is_same<decltype(align_up(const_ptr, 16)), const void*>());
    static_assert(is_same<decltype(align_up(buffer, 16)), void*>());
    FND_TEST_TRUE(align_up(const_ptr, 16) == buffer + 16);
    FND_TEST_TRUE(align_up(const_ptr + 13, 16) == const_ptr + 13);
}

void unittests_memory_utility_gibibytes()
{
    FND_TEST_TRUE(gibibytes(0) == 0);
    FND_TEST_TRUE(gibibytes(1) == ulong_t{1} << 30);
    FND_TEST_TRUE(gibibytes(1) == mebibytes(1024));
    // Beyond what a uint_t holds.
    FND_TEST_TRUE(gibibytes(4) == ulong_t{1} << 32);
    FND_TEST_TRUE(gibibytes(3) == 3 * gibibytes(1));

    // The largest count that does not overflow.
    constexpr ulong_t kMaxCount{kULongMaxValue >> 30};
    FND_TEST_TRUE(gibibytes(kMaxCount) == kMaxCount << 30);
    FND_TEST_TRUE(gibibytes(kMaxCount) > kULongMaxValue - gibibytes(1));

    // Usable in constant expressions.
    static_assert(gibibytes(2) == 2147483648);
}

void unittests_memory_utility_is_aligned()
{
    alignas(256) ubyte_t buffer[128]{};

    // The start of the buffer is aligned to every alignment up to 256.
    for (const ulong_t alignment : kAlignments) {
        FND_TEST_TRUE(is_aligned(buffer, alignment));
    }

    // buffer + offset is aligned exactly when offset is a multiple of
    // alignment.
    for (ulong_t offset{0}; offset < 128; ++offset) {
        for (const ulong_t alignment : kAlignments) {
            FND_TEST_TRUE(
                is_aligned(buffer + offset, alignment)
                == (offset % alignment == 0));
        }
    }
    FND_TEST_TRUE(is_aligned(buffer + 48, 16));
    FND_TEST_FALSE(is_aligned(buffer + 48, 32));
    FND_TEST_FALSE(is_aligned(buffer + 1, 2));

    // Alignment 1 holds for every address; nullptr is aligned to anything.
    FND_TEST_TRUE(is_aligned(buffer + 7, 1));
    FND_TEST_TRUE(is_aligned(nullptr, 64));
    FND_TEST_TRUE(is_aligned(nullptr, ulong_t{1} << 63));

    // A pointer to const works the same.
    const ubyte_t* const const_ptr{buffer + 16};
    FND_TEST_TRUE(is_aligned(const_ptr, 16));
    FND_TEST_FALSE(is_aligned(const_ptr, 32));
}

void unittests_memory_utility_kibibytes()
{
    FND_TEST_TRUE(kibibytes(0) == 0);
    FND_TEST_TRUE(kibibytes(1) == 1024);
    FND_TEST_TRUE(kibibytes(4) == 4096);
    FND_TEST_TRUE(kibibytes(3) == 3 * kibibytes(1));

    // The largest count that does not overflow.
    constexpr ulong_t kMaxCount{kULongMaxValue >> 10};
    FND_TEST_TRUE(kibibytes(kMaxCount) == kMaxCount << 10);
    FND_TEST_TRUE(kibibytes(kMaxCount) > kULongMaxValue - kibibytes(1));

    // Usable in constant expressions.
    static_assert(kibibytes(2) == 2048);
}

void unittests_memory_utility_mebibytes()
{
    FND_TEST_TRUE(mebibytes(0) == 0);
    FND_TEST_TRUE(mebibytes(1) == ulong_t{1} << 20);
    FND_TEST_TRUE(mebibytes(1) == kibibytes(1024));
    FND_TEST_TRUE(mebibytes(3) == 3 * mebibytes(1));
    // Beyond what a uint_t holds.
    FND_TEST_TRUE(mebibytes(4096) == gibibytes(4));

    // The largest count that does not overflow.
    constexpr ulong_t kMaxCount{kULongMaxValue >> 20};
    FND_TEST_TRUE(mebibytes(kMaxCount) == kMaxCount << 20);
    FND_TEST_TRUE(mebibytes(kMaxCount) > kULongMaxValue - mebibytes(1));

    // Usable in constant expressions.
    static_assert(mebibytes(2) == 2097152);
}

void unittests_memory_utility()
{
    unittests_memory_utility_align_up();
    unittests_memory_utility_gibibytes();
    unittests_memory_utility_is_aligned();
    unittests_memory_utility_kibibytes();
    unittests_memory_utility_mebibytes();
}

} // namespace fnd::unittests
