module;
#include "foundation/unittests.h"


export module unittests.memory:unique_ptr;
import foundation.memory;

namespace fnd::unittests {

export void unittests_memory_unique_ptr();

// Counts its destructions in destroy_count, which outlives it.
class DestroyCounter final {
public:
  int_t& destroy_count;
  int_t value;

  ~DestroyCounter() { ++destroy_count; }
};

// A HeapAllocator that counts frees and remembers the last block freed.
class CountingAllocator final : public IAllocator {
public:
  ulong_t free_count{0};
  memory_block_t last_freed{};

  memory_block_t allocate(
    const ulong_t byte_count, const ulong_t alignment,
    const source_location_t srcloc = make_source_location()) override
  {
    return heap_.allocate(byte_count, alignment, srcloc);
  }

  void free(const memory_block_t& block) override
  {
    ++free_count;
    last_freed = block;
    heap_.free(block);
  }

private:
  HeapAllocator heap_{};
};


void unittests_memory_unique_ptr_default_constructor()
{
  const UniquePtr<DestroyCounter> p{};
  FND_TEST_TRUE(p.pointer() == nullptr);
  FND_TEST_TRUE(p.allocator() == nullptr);
}

void unittests_memory_unique_ptr_constructor()
{
  CountingAllocator allocator{};
  int_t destroy_count{0};

  // Two nulls: the empty UniquePtr.
  const UniquePtr<DestroyCounter> empty{nullptr, nullptr};
  FND_TEST_TRUE(empty.pointer() == nullptr);
  FND_TEST_TRUE(empty.allocator() == nullptr);

  // An object and the allocator it came from: both are stored, and the
  // object stays alive while it is owned.
  const memory_block_t block{
    allocator.allocate(sizeof(DestroyCounter), alignof(DestroyCounter))};
  DestroyCounter* const object{
    construct_at<DestroyCounter>(block.ptr, destroy_count, 1)};
  {
    const UniquePtr p{object, &allocator};
    FND_TEST_TRUE(p.pointer() == object);
    FND_TEST_TRUE(p.allocator() == &allocator);
    FND_TEST_TRUE(destroy_count == 0);
    FND_TEST_TRUE(allocator.free_count == 0);
  }

  // The destructor destroys the object once and frees its block once,
  // through the allocator it was given.
  FND_TEST_TRUE(destroy_count == 1);
  FND_TEST_TRUE(allocator.free_count == 1);
  FND_TEST_TRUE(allocator.last_freed == block);
}

void unittests_memory_unique_ptr_move_constructor()
{
  CountingAllocator allocator{};
  int_t destroy_count{0};
  {
    UniquePtr src{
      make_unique_ptr<DestroyCounter>(&allocator, destroy_count, 1)};
    const DestroyCounter* const expected_ptr{src.pointer()};

    // dst takes over the object and its allocator; src is left empty.
    const UniquePtr dst{move(src)};
    FND_TEST_TRUE(dst.pointer() == expected_ptr);
    FND_TEST_TRUE(dst.allocator() == &allocator);
    FND_TEST_TRUE(src.pointer() == nullptr);
    FND_TEST_TRUE(src.allocator() == nullptr);
    FND_TEST_TRUE(destroy_count == 0);
  }

  // Only dst destroyed it: once.
  FND_TEST_TRUE(destroy_count == 1);
  FND_TEST_TRUE(allocator.free_count == 1);
}

void unittests_memory_unique_ptr_move_assignment_operator()
{
  CountingAllocator allocator{};
  int_t old_destroy_count{0};
  int_t new_destroy_count{0};

  UniquePtr dst{
    make_unique_ptr<DestroyCounter>(&allocator, old_destroy_count, 1)};
  UniquePtr src{
    make_unique_ptr<DestroyCounter>(&allocator, new_destroy_count, 2)};
  const memory_block_t old_block{make_memory_block(dst)};
  const DestroyCounter* const expected_ptr{src.pointer()};

  // The old object is destroyed and its block freed; the new one is taken
  // over, and src is left empty.
  dst = move(src);
  FND_TEST_TRUE(old_destroy_count == 1);
  FND_TEST_TRUE(new_destroy_count == 0);
  FND_TEST_TRUE(allocator.free_count == 1);
  FND_TEST_TRUE(allocator.last_freed == old_block);
  FND_TEST_TRUE(dst.pointer() == expected_ptr);
  FND_TEST_TRUE(dst.allocator() == &allocator);
  FND_TEST_TRUE(dst->value == 2);
  FND_TEST_TRUE(is_empty(src));
  FND_TEST_TRUE(src.allocator() == nullptr);

  // Self-move destroys nothing and keeps the object.
  dst = move(dst);
  FND_TEST_TRUE(new_destroy_count == 0);
  FND_TEST_TRUE(allocator.free_count == 1);
  FND_TEST_TRUE(dst.pointer() == expected_ptr);
  FND_TEST_TRUE(dst.allocator() == &allocator);

  // An empty source: the object is destroyed and dst is left empty.
  dst = UniquePtr<DestroyCounter>{};
  FND_TEST_TRUE(new_destroy_count == 1);
  FND_TEST_TRUE(allocator.free_count == 2);
  FND_TEST_TRUE(is_empty(dst));
  FND_TEST_TRUE(dst.allocator() == nullptr);
}

void unittests_memory_unique_ptr_move_assignment_operator_owned_source()
{
  // A node that owns the next one.
  class ListNode final {
  public:
    int_t& destroy_count;
    UniquePtr<ListNode> next;

    ~ListNode() { ++destroy_count; }
  };

  CountingAllocator allocator{};
  int_t head_destroy_count{0};
  int_t next_destroy_count{0};

  UniquePtr node{make_unique_ptr<ListNode>(&allocator, head_destroy_count)};
  node->next = make_unique_ptr<ListNode>(&allocator, next_destroy_count);
  const ListNode* const expected_ptr{node->next.pointer()};

  // node = move(node->next): the source lives inside the object node
  // destroys. The next node is taken over before the head dies.
  node = move(node->next);
  FND_TEST_TRUE(head_destroy_count == 1);
  FND_TEST_TRUE(next_destroy_count == 0);
  FND_TEST_TRUE(allocator.free_count == 1);
  FND_TEST_TRUE(node.pointer() == expected_ptr);
  FND_TEST_TRUE(is_empty(node->next));
}

void unittests_memory_unique_ptr_bool_operator()
{
  HeapAllocator heap{};

  const UniquePtr<int_t> empty{};
  const UniquePtr owner{make_unique_ptr<int_t>(&heap, 1)};
  FND_TEST_FALSE(static_cast<bool_t>(empty));
  FND_TEST_TRUE(static_cast<bool_t>(owner));
}

void unittests_memory_unique_ptr_dereference_operators()
{
  HeapAllocator heap{};

  struct dereference_test_t final {
    int_t i;
    float_t f;
  };
  const UniquePtr p{make_unique_ptr<dereference_test_t>(&heap, 7, 2.5f)};

  // Both reach the owned object.
  FND_TEST_TRUE(&*p == p.pointer());
  FND_TEST_TRUE((*p).i == 7);
  FND_TEST_TRUE(p->f == 2.5f);

  // A const UniquePtr doesn't make its object const: writes reach it.
  p->i = 8;
  (*p).f = 3.5f;
  FND_TEST_TRUE(p.pointer()->i == 8);
  FND_TEST_TRUE(p.pointer()->f == 3.5f);
}

void unittests_memory_unique_ptr_nullptr_assignment_operator()
{
  CountingAllocator allocator{};
  int_t destroy_count{0};

  UniquePtr p{make_unique_ptr<DestroyCounter>(&allocator, destroy_count, 1)};
  const memory_block_t block{make_memory_block(p)};

  // The object is destroyed, its block freed, and p is left empty.
  p = nullptr;
  FND_TEST_TRUE(destroy_count == 1);
  FND_TEST_TRUE(allocator.free_count == 1);
  FND_TEST_TRUE(allocator.last_freed == block);
  FND_TEST_TRUE(is_empty(p));
  FND_TEST_TRUE(p.allocator() == nullptr);

  // On an empty UniquePtr: nothing happens.
  p = nullptr;
  FND_TEST_TRUE(destroy_count == 1);
  FND_TEST_TRUE(allocator.free_count == 1);
  FND_TEST_TRUE(is_empty(p));
}

void unittests_memory_unique_ptr_destroy()
{
  CountingAllocator allocator{};
  int_t destroy_count{0};

  UniquePtr p{make_unique_ptr<DestroyCounter>(&allocator, destroy_count, 1)};
  const memory_block_t block{make_memory_block(p)};

  // The object is destroyed, its block freed, and p is left empty.
  p.destroy();
  FND_TEST_TRUE(destroy_count == 1);
  FND_TEST_TRUE(allocator.free_count == 1);
  FND_TEST_TRUE(allocator.last_freed == block);
  FND_TEST_TRUE(is_empty(p));
  FND_TEST_TRUE(p.allocator() == nullptr);

  // On an empty UniquePtr: nothing happens.
  p.destroy();
  FND_TEST_TRUE(destroy_count == 1);
  FND_TEST_TRUE(allocator.free_count == 1);
  FND_TEST_TRUE(is_empty(p));
}

void unittests_memory_unique_ptr_set()
{
  CountingAllocator allocator{};
  int_t old_destroy_count{0};
  int_t new_destroy_count{0};

  UniquePtr p{
    make_unique_ptr<DestroyCounter>(&allocator, old_destroy_count, 1)};
  const memory_block_t old_block{make_memory_block(p)};
  const memory_block_t new_block{
    allocator.allocate(sizeof(DestroyCounter), alignof(DestroyCounter))};
  DestroyCounter* const new_object{
    construct_at<DestroyCounter>(new_block.ptr, new_destroy_count, 2)};

  // The old object is destroyed and its block freed; the new one is owned.
  p.set(new_object, &allocator);
  FND_TEST_TRUE(old_destroy_count == 1);
  FND_TEST_TRUE(new_destroy_count == 0);
  FND_TEST_TRUE(allocator.free_count == 1);
  FND_TEST_TRUE(allocator.last_freed == old_block);
  FND_TEST_TRUE(p.pointer() == new_object);
  FND_TEST_TRUE(p.allocator() == &allocator);

  // The object it already owns: nothing happens.
  p.set(new_object, &allocator);
  FND_TEST_TRUE(new_destroy_count == 0);
  FND_TEST_TRUE(allocator.free_count == 1);
  FND_TEST_TRUE(p.pointer() == new_object);

  // Two nulls: the object is destroyed and p is left empty.
  p.set(nullptr, nullptr);
  FND_TEST_TRUE(new_destroy_count == 1);
  FND_TEST_TRUE(allocator.free_count == 2);
  FND_TEST_TRUE(allocator.last_freed == new_block);
  FND_TEST_TRUE(is_empty(p));
  FND_TEST_TRUE(p.allocator() == nullptr);
}

void unittests_memory_unique_ptr_equality_operators()
{
  HeapAllocator heap{};

  const UniquePtr<int_t> empty0{};
  const UniquePtr<int_t> empty1{};
  const UniquePtr p0{make_unique_ptr<int_t>(&heap, 1)};
  const UniquePtr p1{make_unique_ptr<int_t>(&heap, 1)};

  // UniquePtr vs UniquePtr: two empty ones are equal; an owner equals only
  // itself, not another owner of an equal value.
  FND_TEST_TRUE(empty0 == empty1);
  FND_TEST_FALSE(empty0 != empty1);
  FND_TEST_TRUE(p0 == p0);
  FND_TEST_FALSE(p0 != p0);
  FND_TEST_FALSE(p0 == p1);
  FND_TEST_TRUE(p0 != p1);
  FND_TEST_FALSE(p0 == empty0);
  FND_TEST_TRUE(p0 != empty0);

  // UniquePtr vs nullptr.
  FND_TEST_TRUE(empty0 == nullptr);
  FND_TEST_FALSE(empty0 != nullptr);
  FND_TEST_FALSE(p0 == nullptr);
  FND_TEST_TRUE(p0 != nullptr);

  // nullptr vs UniquePtr.
  FND_TEST_TRUE(nullptr == empty0);
  FND_TEST_FALSE(nullptr != empty0);
  FND_TEST_FALSE(nullptr == p0);
  FND_TEST_TRUE(nullptr != p0);
}

void unittests_memory_unique_ptr_is_empty()
{
  HeapAllocator heap{};

  FND_TEST_TRUE(is_empty(UniquePtr<int_t>{}));
  FND_TEST_FALSE(is_empty(make_unique_ptr<int_t>(&heap, 1)));
}

void unittests_memory_unique_ptr_make_memory_block()
{
  // An empty UniquePtr: the empty block.
  FND_TEST_TRUE(make_memory_block(UniquePtr<int_t>{}) == memory_block_t{});

  // An owning UniquePtr: exactly the block allocate returned, the one free
  // takes back. A scalar, and a struct of another size.
  HeapAllocator heap{};

  const memory_block_t int_block{heap.allocate(sizeof(int_t), alignof(int_t))};
  const UniquePtr int_ptr{construct_at<int_t>(int_block.ptr), &heap};
  FND_TEST_TRUE(make_memory_block(int_ptr) == int_block);

  struct make_block_test_t final {
    float_t x;
    float_t y;
    float_t z;
  };
  const memory_block_t struct_block{
    heap.allocate(sizeof(make_block_test_t), alignof(make_block_test_t))};
  const UniquePtr struct_ptr{
    construct_at<make_block_test_t>(struct_block.ptr), &heap};
  FND_TEST_TRUE(make_memory_block(struct_ptr) == struct_block);
}

void unittests_memory_unique_ptr_make_unique_ptr()
{
  HeapAllocator heap{};

  // An object built from the arguments, owned together with the allocator it
  // came from, in sizeof(T) bytes aligned for T.
  struct make_test_t final {
    int_t i;
    float_t f;
  };
  const UniquePtr p{make_unique_ptr<make_test_t>(&heap, -7, 2.5f)};
  FND_TEST_FALSE(is_empty(p));
  FND_TEST_TRUE(p.allocator() == &heap);
  FND_TEST_TRUE(p->i == -7);
  FND_TEST_TRUE(p->f == 2.5f);
  FND_TEST_TRUE(make_memory_block(p).byte_count == sizeof(make_test_t));
  FND_TEST_TRUE(is_aligned(p.pointer(), alignof(make_test_t)));

  // A type aligned more strictly than malloc's own alignment: alignof(T)
  // reaches allocate.
  constexpr ulong_t kAlignedByteCount{64};
  struct alignas(kAlignedByteCount) make_aligned_test_t final {
    ubyte_t bytes[kAlignedByteCount];
  };
  const UniquePtr aligned{make_unique_ptr<make_aligned_test_t>(&heap)};
  FND_TEST_TRUE(is_aligned(aligned.pointer(), kAlignedByteCount));

  // Each argument reaches the constructor as it was passed: an lvalue as an
  // lvalue, an rvalue as an rvalue.
  struct make_sink_t final {
    int_t value;
    bool_t is_from_rvalue;

    make_sink_t(const int_t& v) : value{v}, is_from_rvalue{false} {}

    make_sink_t(int_t&& v) : value{v}, is_from_rvalue{true} {}
  };
  int_t arg{5};

  const UniquePtr from_lvalue{make_unique_ptr<make_sink_t>(&heap, arg)};
  FND_TEST_TRUE(from_lvalue->value == 5);
  FND_TEST_FALSE(from_lvalue->is_from_rvalue);

  const UniquePtr from_rvalue{make_unique_ptr<make_sink_t>(&heap, move(arg))};
  FND_TEST_TRUE(from_rvalue->value == 5);
  FND_TEST_TRUE(from_rvalue->is_from_rvalue);
}

void unittests_memory_unique_ptr_make_unique_ptr_failure()
{
  // Every allocation fails.
  class FailingAllocator final : public IAllocator {
  public:
    memory_block_t allocate(
      const ulong_t, const ulong_t,
      const source_location_t = make_source_location()) override
    {
      return memory_block_t{};
    }

    void free(const memory_block_t&) override {}
  };

  // Counts its constructions and takes over the UniquePtr it is given.
  class ConstructCounter final {
  public:
    UniquePtr<int_t> owned;

    ConstructCounter(int_t& construct_count, UniquePtr<int_t>&& p)
        : owned{move(p)}
    {
      ++construct_count;
    }
  };

  HeapAllocator heap{};
  FailingAllocator failing{};
  int_t construct_count{0};
  UniquePtr inner{make_unique_ptr<int_t>(&heap, 7)};
  const int_t* const expected_ptr{inner.pointer()};

  // A failed allocation: the empty UniquePtr, no T constructed, and the
  // arguments left as they are (inner still owns its object).
  const UniquePtr failed{
    make_unique_ptr<ConstructCounter>(&failing, construct_count, move(inner))};
  FND_TEST_TRUE(is_empty(failed));
  FND_TEST_TRUE(failed.allocator() == nullptr);
  FND_TEST_TRUE(construct_count == 0);
  FND_TEST_TRUE(inner.pointer() == expected_ptr);

  // The same call with a working allocator constructs and takes inner over:
  // the checks above can fail.
  const UniquePtr succeeded{
    make_unique_ptr<ConstructCounter>(&heap, construct_count, move(inner))};
  FND_TEST_TRUE(construct_count == 1);
  FND_TEST_TRUE(is_empty(inner));
  FND_TEST_TRUE(succeeded->owned.pointer() == expected_ptr);
}

void unittests_memory_unique_ptr()
{
  unittests_memory_unique_ptr_default_constructor();
  unittests_memory_unique_ptr_constructor();
  unittests_memory_unique_ptr_move_constructor();
  unittests_memory_unique_ptr_move_assignment_operator();
  unittests_memory_unique_ptr_move_assignment_operator_owned_source();
  unittests_memory_unique_ptr_bool_operator();
  unittests_memory_unique_ptr_dereference_operators();
  unittests_memory_unique_ptr_nullptr_assignment_operator();
  unittests_memory_unique_ptr_destroy();
  unittests_memory_unique_ptr_set();
  unittests_memory_unique_ptr_equality_operators();
  unittests_memory_unique_ptr_is_empty();
  unittests_memory_unique_ptr_make_memory_block();
  unittests_memory_unique_ptr_make_unique_ptr();
  unittests_memory_unique_ptr_make_unique_ptr_failure();
}

} // namespace fnd::unittests
