module;
#include "foundation/core/macros.h"

export module foundation.memory:unique_ptr;
import foundation.core;
import :allocator;
import :block;
import :utility;

namespace fnd {

// Owns one T in memory from an IAllocator and the allocator it came from.
// Destroys the T and frees its memory, {pointer, sizeof(T)}, through that
// allocator when it is destroyed or given another object.
// A pointer to a type derived from T is rejected: memory freed would be
// sizeof(T) bytes at the T* address, not the memory allocate() returned.
export template<typename T> class UniquePtr final {
public:
  constexpr UniquePtr() = default;

  constexpr UniquePtr(T* const p, IAllocator* const a)
      : pointer_{p}, allocator_{a}
  {
    FND_ASSERT((p == nullptr) == (a == nullptr));
  }

  // forbid UniquePtr<Base> ptr{derived_ptr, allocator};
  template<typename U> UniquePtr(U*, IAllocator*) = delete;
  UniquePtr(const UniquePtr<T>&) = delete;

  constexpr UniquePtr(UniquePtr<T>&& up)
      : pointer_{exchange(up.pointer_, nullptr)},
        allocator_{exchange(up.allocator_, nullptr)}
  {
  }

  inline ~UniquePtr() { destroy_and_free(pointer_, allocator_); }


  constexpr explicit operator bool() const
  {
    return static_cast<bool_t>(pointer_);
  }

  constexpr T& operator*() const
  {
    FND_ASSERT(pointer_ != nullptr);
    return *pointer_;
  }

  constexpr T* operator->() const
  {
    FND_ASSERT(pointer_ != nullptr);
    return pointer_;
  }

  UniquePtr& operator=(const UniquePtr<T>&) = delete;

  inline UniquePtr& operator=(UniquePtr<T>&& up)
  {
    if (this == &up) return *this;

    T* const p{exchange(up.pointer_, nullptr)};
    IAllocator* const a{exchange(up.allocator_, nullptr)};
    set(p, a);

    return *this;
  }

  inline UniquePtr& operator=(nullptr_t)
  {
    destroy();
    return *this;
  }


  constexpr IAllocator* allocator() const { return allocator_; }

  inline void destroy() { set(nullptr, nullptr); }

  constexpr T* pointer() const { return pointer_; }

  inline void set(T* const p, IAllocator* const a)
  {
    FND_ASSERT((p == nullptr) == (a == nullptr));

    if (p == pointer_) {
      FND_ASSERT(a == allocator_);
      return;
    }

    T* const old_p{exchange(pointer_, p)};
    IAllocator* const old_a{exchange(allocator_, a)};
    destroy_and_free(old_p, old_a);
  }

  template<typename U> void set(U*, IAllocator*) = delete;

private:
  static void destroy_and_free(T* const p, IAllocator* const a)
  {
    FND_ASSERT((p == nullptr) == (a == nullptr));

    if (!p) return;

    p->~T();
    const memory_block_t block{p, sizeof(T)};
    a->free(block);
  }

  // Invariants:
  // 1. pointer_ and allocator_ are both null (an empty UniquePtr) or both set.
  T* pointer_{nullptr};
  IAllocator* allocator_{nullptr};
};


export template<typename T>
constexpr bool_t operator==(const UniquePtr<T>& l, const UniquePtr<T>& r)
{
  return l.pointer() == r.pointer() && l.allocator() == r.allocator();
}

export template<typename T>
constexpr bool_t operator==(const UniquePtr<T>& l, nullptr_t)
{
  return l.pointer() == nullptr && l.allocator() == nullptr;
}

// True if p owns no object.
export template<typename T> constexpr bool_t is_empty(const UniquePtr<T>& p)
{
  return p.pointer() == nullptr;
}

// Returns the block p's object occupies, {pointer, sizeof(T)}.
// Returns the empty block if p is empty.
// p still owns it: don't free it.
export template<typename T>
constexpr memory_block_t make_memory_block(const UniquePtr<T>& p)
{
  return memory_block_t{p.pointer(), is_empty(p) ? 0 : sizeof(T)};
}

// Returns a UniquePtr owning T{args...}, allocated with allocator.
// Returns the empty UniquePtr if the allocation fails: then no T is
// constructed and args are left as they are.
export template<typename T, typename... Args>
UniquePtr<T> make_unique_ptr(IAllocator* const allocator, Args&&... args)
{
  FND_ASSERT(allocator != nullptr);

  const memory_block_t block{allocator->allocate(sizeof(T), alignof(T))};
  if (is_empty(block)) return UniquePtr<T>{};

  T* const p{construct_at<T>(block.ptr, forward<Args>(args)...)};
  return UniquePtr<T>{p, allocator};
}

} // namespace fnd
