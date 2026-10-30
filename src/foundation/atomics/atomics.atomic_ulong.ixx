module;
#include <intrin.h>
#include "foundation/core/macros.h"

export module foundation.atomics:atomic_ulong;
import foundation.core;
import :memory_order;

namespace fnd {

struct atomic_ulong_t final { volatile ulong_t value_{}; };

static_assert(sizeof(atomic_ulong_t) == sizeof(ulong_t));
static_assert(alignof(atomic_ulong_t) == 8);


} // namespace fnd
