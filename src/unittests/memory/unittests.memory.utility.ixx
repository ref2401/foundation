module;
#include "foundation/unittests.h"


export module unittests.memory:utility;
import foundation.memory;

namespace fnd::unittests {

export void unittests_memory_utility();

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
    unittests_memory_utility_gibibytes();
    unittests_memory_utility_kibibytes();
    unittests_memory_utility_mebibytes();
}

} // namespace fnd::unittests
