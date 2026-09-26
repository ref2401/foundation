export module unittests.math;
import :scalar;
import :vector_bool;
import :vector_int;

namespace fnd::unittests {

export void run_unittests_math()
{
    unittests_math_scalar();
    unittests_math_vector_bool();
    unittests_math_vector_int();
}

} // namespace fnd::unittests
