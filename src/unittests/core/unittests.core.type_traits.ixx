module;
#include "foundation/unittests.h"


export module unittests.core:type_traits;
import foundation.core;

namespace fnd::unittests {

export void unittests_core_type_traits();

void unittests_core_type_traits_pod_type()
{
  struct pod_test_t final {
    int_t i;
    float_t f;
  };
  // Constructors and default member initializers are allowed: copying stays
  // a plain copy of the bytes (like the math structs).
  struct pod_with_ctor_t final {
    int_t i{0};
    constexpr pod_with_ctor_t() = default;
    constexpr explicit pod_with_ctor_t(int_t i) : i{i} {}
  };
  // Not trivially copyable: a user copy constructor or destructor.
  struct user_copy_t final {
    int_t i;
    user_copy_t(const user_copy_t& other) : i{other.i} {}
  };
  struct user_dtor_t final {
    int_t i;
    ~user_dtor_t() {}
  };
  // Not standard layout: data members with different access, or a virtual
  // function (which adds a hidden vtable pointer).
  struct mixed_access_t final {
    int_t i;

  private:
    int_t j;
  };
  struct virtual_t final {
    int_t i;
    virtual void f() {}
  };

  // Built-in types, pointers and arrays of them.
  static_assert(PodType<int_t>);
  static_assert(PodType<float_t>);
  static_assert(PodType<bool_t>);
  static_assert(PodType<int_t*>);
  static_assert(PodType<const int_t*>);
  static_assert(PodType<int_t[3]>);

  // Plain structs, also with constructors, and arrays of them.
  static_assert(PodType<pod_test_t>);
  static_assert(PodType<pod_with_ctor_t>);
  static_assert(PodType<pod_test_t[2]>);

  // Either property missing is enough to fail.
  static_assert(!PodType<user_copy_t>);
  static_assert(!PodType<user_dtor_t>);
  static_assert(!PodType<mixed_access_t>);
  static_assert(!PodType<virtual_t>);
}

void unittests_core_type_traits_unref()
{
  struct unref_test_t final { int_t i; };

  // A type that is not a reference stays as it is.
  static_assert(is_same<Unref<int_t>, int_t>());
  static_assert(is_same<Unref<unref_test_t>, unref_test_t>());
  static_assert(is_same<Unref<int_t*>, int_t*>());
  static_assert(is_same<Unref<int_t[3]>, int_t[3]>());

  // Both kinds of reference are removed.
  static_assert(is_same<Unref<int_t&>, int_t>());
  static_assert(is_same<Unref<int_t&&>, int_t>());
  static_assert(is_same<Unref<unref_test_t&>, unref_test_t>());
  static_assert(is_same<Unref<unref_test_t&&>, unref_test_t>());

  // const and volatile are kept.
  static_assert(is_same<Unref<const int_t>, const int_t>());
  static_assert(is_same<Unref<const int_t&>, const int_t>());
  static_assert(is_same<Unref<volatile int_t&&>, volatile int_t>());
  static_assert(is_same<Unref<const volatile int_t&>, const volatile int_t>());

  // Only the outer reference goes: a pointer stays a pointer, and the const
  // of a const pointer stays.
  static_assert(is_same<Unref<int_t*&>, int_t*>());
  static_assert(is_same<Unref<int_t* const&>, int_t* const>());
  static_assert(is_same<Unref<const int_t*&&>, const int_t*>());

  // References to arrays and to functions.
  static_assert(is_same<Unref<int_t(&)[3]>, int_t[3]>());
  static_assert(is_same<Unref<int_t(&&)[3]>, int_t[3]>());
  static_assert(is_same<Unref<void (&)(int_t)>, void(int_t)>());

  // Removing it again changes nothing.
  static_assert(is_same<Unref<Unref<int_t&>>, int_t>());
}

void unittests_core_type_traits_is_const()
{
  struct is_const_test_t final { int_t i; };

  // const and const volatile types are const.
  static_assert(is_const<const int_t>());
  static_assert(is_const<const volatile int_t>());
  static_assert(is_const<const is_const_test_t>());
  static_assert(is_const<const void>());

  // Types without const, including volatile alone.
  static_assert(!is_const<int_t>());
  static_assert(!is_const<volatile int_t>());
  static_assert(!is_const<is_const_test_t>());
  static_assert(!is_const<void>());

  // A reference is never const itself, even to a const type; the type it
  // refers to is.
  static_assert(!is_const<int_t&>());
  static_assert(!is_const<const int_t&>());
  static_assert(!is_const<const int_t&&>());
  static_assert(is_const<Unref<const int_t&>>());

  // A pointer to const is not const; a const pointer is.
  static_assert(!is_const<const int_t*>());
  static_assert(is_const<int_t* const>());
  static_assert(is_const<const int_t* const>());

  // An array of const elements is a const type.
  static_assert(is_const<const int_t[3]>());
  static_assert(!is_const<int_t[3]>());

  // A function type is never const.
  static_assert(!is_const<void(int_t)>());
}

void unittests_core_type_traits_is_convertible()
{
  struct base_t { int_t i; };
  struct derived_t final : base_t { int_t j; };
  struct implicit_t final {
    int_t i;
    implicit_t(int_t i) : i{i} {}
  };
  struct explicit_t final {
    int_t i;
    explicit explicit_t(int_t i) : i{i} {}
  };

  // A type converts to itself; arithmetic types convert to each other,
  // narrowing included.
  static_assert(is_convertible<int_t, int_t>());
  static_assert(is_convertible<int_t, float_t>());
  static_assert(is_convertible<float_t, int_t>());
  static_assert(is_convertible<int_t, bool_t>());

  // Pointers: to a base class, to void and to const, not the other way.
  static_assert(is_convertible<derived_t*, base_t*>());
  static_assert(!is_convertible<base_t*, derived_t*>());
  static_assert(is_convertible<int_t*, void*>());
  static_assert(!is_convertible<void*, int_t*>());
  static_assert(is_convertible<int_t*, const int_t*>());
  static_assert(!is_convertible<const int_t*, int_t*>());
  static_assert(is_convertible<decltype(nullptr), int_t*>());
  static_assert(!is_convertible<int_t, int_t*>());

  // A constructor converts only if it is not explicit.
  static_assert(is_convertible<int_t, implicit_t>());
  static_assert(!is_convertible<int_t, explicit_t>());

  // TSrc is used as an rvalue: it binds to const T& but not to T&.
  static_assert(is_convertible<int_t, const int_t&>());
  static_assert(!is_convertible<int_t, int_t&>());
  static_assert(is_convertible<int_t&, int_t&>());

  // The order of the arguments matters.
  static_assert(is_convertible<derived_t, base_t>());
  static_assert(!is_convertible<base_t, derived_t>());
}

void unittests_core_type_traits_is_same()
{
  struct is_same_test_t final { int_t i; };
  using is_same_test_alias_t = is_same_test_t;

  // A type is the same as itself and as its aliases.
  static_assert(is_same<int_t, int_t>());
  static_assert(is_same<int_t, int>());
  static_assert(is_same<float_t, float>());
  static_assert(is_same<is_same_test_t, is_same_test_alias_t>());

  // Different types, even of the same size or with a conversion.
  static_assert(!is_same<int_t, uint_t>());
  static_assert(!is_same<int_t, long_t>());
  static_assert(!is_same<float_t, double_t>());
  static_assert(!is_same<int_t, float_t>());
  static_assert(!is_same<char_t, byte_t>());
  static_assert(!is_same<char_t, ubyte_t>());

  // const, volatile, references and pointers make a different type.
  static_assert(!is_same<int_t, const int_t>());
  static_assert(!is_same<int_t, volatile int_t>());
  static_assert(!is_same<int_t, int_t&>());
  static_assert(!is_same<int_t&, int_t&&>());
  static_assert(!is_same<int_t, int_t*>());
  static_assert(!is_same<int_t*, const int_t*>());
  static_assert(is_same<const int_t*, const int_t*>());

  // The order of the arguments does not matter.
  static_assert(!is_same<uint_t, int_t>());
  static_assert(is_same<int, int_t>());
}

void unittests_core_type_traits()
{
  unittests_core_type_traits_pod_type();
  unittests_core_type_traits_unref();
  unittests_core_type_traits_is_const();
  unittests_core_type_traits_is_convertible();
  unittests_core_type_traits_is_same();
}

} // namespace fnd::unittests
