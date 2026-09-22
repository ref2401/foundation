#include "foundation/core/macros.h"
import foundation.core;

using namespace fnd;

int main()
{
    byte_t t{10};
    FND_ASSERT(t > 50);
    
    return 0;
}