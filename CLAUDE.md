# foundation

## Building and formatting

- The project's compiler is MSVC 19.51 (toolset 14.51) from Visual Studio 2026
  Community (`C:\Program Files\Microsoft Visual Studio\18\Community`, instance
  `b1500950`). Visual Studio 2022 (MSVC 19.41, instance `cbc839fd`) is also
  installed; don't build with it.
- `cl.exe` is not on the PATH. Load the VS 2026 developer environment first,
  then run the build script (`-Configuration Debug|Release`, optional `-Clean`):
v
  ```
  cmd /c '"C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat" >nul 2>&1 && powershell -NoProfile -ExecutionPolicy Bypass -File scripts\build_unittests.ps1 -Configuration Debug'
  ```

  Then run `bin\debug\unittests.exe` (or `bin\release\`). Build both
  configurations before claiming that something compiles or passes.
  `bin\<config>\asm\` holds `/Fa` assembly listings per translation unit.
- No exceptions (`/EH` is absent), no RTTI (`/GR-`). `FND_DEBUG` is defined in
  Debug only; it turns `FND_ASSERT` into a real check (`__noop` in Release).
- The traditional MSVC preprocessor is used (no `/Zc:preprocessor`):
  `__VA_ARGS__` is forwarded as a single argument, so macros have fixed arity
  (`FND_ASSERT(condition)`, `FND_ASSERT_MSG(condition, message)`).
- Format with clang-format 23.1+ (the VS-bundled 22.x rejects `.clang-format`):
  `C:\Users\ref2401\.vscode\extensions\ms-vscode.cpptools-1.34.4-win32-x64\LLVM\bin\clang-format.exe -i <files>`.

## Layout

- Partition files: `src/foundation/<module>/<module>.<name>.ixx` declaring
  `foundation.<module>:<name>`; the primary unit `<module>.ixx` re-exports them.
- Tests mirror them: `src/unittests/<module>/unittests.<module>.<name>.ixx`
  declaring `unittests.<module>:<name>`, with one exported runner
  `unittests_<module>_<name>()` called from `run_unittests_<module>()`.
- A new `.ixx` must be added to `$moduleNames` in `scripts/build_unittests.ps1`,
  after every unit it imports.
- Math partition order (imports and build): vectors -> vector_quat ->
  vector_conversion -> matrix_float3x3 -> matrix_float3x4 -> matrix_float4x4 ->
  matrix_conversion -> matrix_construction.
  - A type's own file holds only the type and its algebra.
  - Conversions go to `vector_conversion` (vectors, quat <-> float4) or
    `matrix_conversion` (matrices, quat <-> matrix).
  - Matrix builders (`_axis_angle`, `_scale`, `_translation`, `_trs`,
    projection, view) go to `matrix_construction`.
- The project provides its own `move`, `forward`, `exchange`, `swap`
  (`foundation.core:utility`), type traits (`foundation.core:type_traits`) and
  placement new; don't use the C++ standard library for these.

## Naming

| Kind | Style | Examples |
|---|---|---|
| POD struct | `snake_case_t` | `float3_t`, `span_t` |
| Class (keeps an invariant, has member functions) | `PascalCase` | `Array<T>`, `UniquePtr<T>` |
| Interface (pure virtual) | `I` + `PascalCase` | `IAllocator` |
| Concept | `PascalCase` | `PodType` |
| Type trait (yields a type) | `PascalCase` alias, named as the resulting type | `Unref<T>`, later `Unqual<T>` |
| Value trait (yields a value) | `snake_case` constexpr function | `is_same<T, U>()`, `is_const<T>()` |
| Constant | `kPascalCase` | `kUnitX`, `kItemCount` |
| Data member of a class | `snake_case_` | `data_`, `count_` |
| Function, variable, parameter | `snake_case` | `make_quat`, `position_ws` |

- Struct-producing functions are `make_<struct without _t>[_<what it is built
  from>]`: `make_float3x3_axis_angle`, `make_float3x4_trs`, and conversions
  `make_float3x3(const float3x4_t&)`, `make_quat(const float3x3_t&)`.
  Exception: vector conversions are `float4(...)`, `int3(...)`, also
  `float4(quat_t)` and `quat(float4_t)`.
- Boolean functions and variables read as a yes/no question once the
  arguments are filled in:
  - a property or state of one subject: `is_` + adjective (`is_aligned(p, 16)`,
    `is_empty(s)`, `is_normalized(v)`; variables `is_copied`, `is_visible`);
  - an ability: `can_` + verb (`can_trunc_to_int(x)`);
  - possession: `has_` + noun (`has_capacity(a, n)`);
  - the subject does or relates to something: a third-person verb
    (`contains(s, x)`, `overlaps(r0, r1)`, `starts_with(s, prefix)`);
  - a symmetric relation between two operands of equal standing: the
    relation's adjective alone (`approx_equal(a, b)`,
    `equal_bytes(a, b, byte_count)`).

  Never `does_`/`do_` (`does_overlap`), `is_` before a verb (`is_contains`), a
  participle in place of the verb (`bytes_compared`), or a negated name
  (`is_not_empty`, `no_overlap`). Names taken from C or `std` keep their
  spelling: `isnan`, `isinf`, `isfinite`, `is_same`, `is_constant_evaluated`.
- Parameters taking a scalar are named `scalar`.
- Matrix variables use `m`: `m`, `m_inv`, `rm`/`mr` for rotations, `sm`/`ms`
  for scales.
- Coordinate-space suffixes: world `_ws` (`position_ws`, `f_ws`), view `_vs`,
  clip `_cs`; constants `kPositionWs`, `kOriginCs`. Ask before inventing others.

## Types

- Every struct is `final` by default (`export struct float3_t final {`), test
  structs included; leave it out only when the struct is a base. A class is
  `final` unless it is meant to be derived from (interfaces never are `final`).
- POD structs are used "as in C": data members, constructors and static
  constants only. Accessors and helpers are free functions (`column0(m)`,
  `set_row1(m, r)`); only operators the language requires to be members
  (`operator[]`, `operator=`, ...) go inside.
- Classes keep invariants and have member functions. Their move assignment must
  be safe for self-assignment (`x = move(x)` leaves `x` unchanged):
  `swap(x, x)` relies on it.
- Matrices (structs of 16 bytes or more) are passed as `const T&` by default,
  by value where it measurably helps (say why in a `NOTE`). Vectors and scalars
  are passed by value.
- Integer roles: sizes and alignments are `ulong_t`; an address used for bit
  math (aligning, masking, `>>`) is `uptr_t`, unsigned on purpose (it wraps
  instead of overflowing and orders like the address space); a signed
  difference is `long_t`. Otherwise pointers stay pointers.
  - `reinterpret_cast` only between a pointer and `uptr_t`; `static_cast`
    between integer types.
  - Signed difference of two addresses: subtract as `uptr_t`, then convert,
    `static_cast<long_t>(p0 - p1)` (exact because pointers are 64-bit, as
    `long_t` is). For two pointers into one allocation, subtract byte pointers
    instead.

## Code

- Parameters passed by value are `const`, pointers included:
  `abs(const int_t x)`, `const char_t* const filename`.
- Every function, and every overload of it, asserts its own preconditions with
  `FND_ASSERT` at its top, even when it only forwards to a callee that asserts
  the same thing. An assert that calls a non-`constexpr` function
  (`is_normalized`, `isnan`) makes the function `FND_INLINE` instead of
  `constexpr`.
- Postconditions are checked by unittests, not asserted. The exception is a
  result produced by code the tests can't cover, such as a virtual
  implementation behind an interface: the non-virtual wrapper asserts the
  contract (`IAllocator::realloc` checks that the pointer is aligned).
- Prefer brace initialization: `int_t a{1}`, `int_t* p{&a}`,
  `const float3_t v{normalize(a)}`. Use `=` with `auto`, and in generic code
  initializing a `T` from a single `T` (`T old_value = move(object);`).
- Initialize with plain integers when the value converts exactly: `float_t x{0}`,
  `kUnitX{1, 0, 0}`, not `0.0f`/`0u`. Keep the suffix where it changes meaning
  (`1 / 3`, `-0.0f`, `0.5f`, overloaded arguments, `auto`/template deduction).
- MSVC 19.51 bug: in constant evaluation `NaN < x` and `x < NaN` are true. Float
  functions whose NaN behavior matters are `FND_INLINE`, not `constexpr`, and
  their NaN cases are tested at runtime.
- `[[msvc::intrinsic]]` (`FND_CAST_FUNCTION`) only on functions whose body is a
  single cast, such as `move` and `forward`.
- A helper that belongs to one function lives inside it: a lambda
  (`const auto name = [](...) { ... };`), a local struct, a local constant.
  Collapsing the function then hides its helpers, and nothing else can use
  them. A helper shared by several functions goes at namespace scope. Where the
  local form can't work (a template, a member template, a partial
  specialization, an overload set, recursion), the helper stays next to its
  function, as in Source order.

## Source order

- Constants first, right after `namespace fnd {`. Exception: a non-exported
  helper that implements exactly one function or alias (`kIsConst`,
  `UnrefImpl`) stays next to it.
- Type files: the struct, its static constants, then all its operators as one
  block, then the functions.
  - Operators: `++`/`--` and unary (`-`, `~`, `!`) first; then comparisons
    (`==`, `!=`, `<`, `<=`, `>`, `>=`); then binary `& * + - % / << >> ^ |`;
    then compound assignments in the same order, implemented as
    `a = a op b; return a;` but repeating the binary operator's asserts.
- Functions: if A calls B, B goes first (calls inside `FND_ASSERT` count); ties
  are broken alphabetically by plain character order.

## Unittests

- Test files mirror the library order. Test constants go at the top, right
  after the exported runner declaration. A runner calls its tests in the order
  they are defined; aggregate runners follow import order.
- Use runtime `FND_TEST_TRUE`/`FND_TEST_FALSE` by default, even for `constexpr`
  functions. `static_assert` only for compile-time properties (types,
  `decltype`, `PodType`, `sizeof`), plus one check that a function is usable in
  constant expressions.
- Name reused inputs (`constexpr float3_t kScale0{2, -0.5f, 4};`) and derive
  expected values from them through the library where the check is a
  relationship. File-scope test constants must be unique across all partitions
  of a test module (`kMatrixA3x3`, `kMatrixA4x4`).
- Test-only types are defined inside the test function, or at file scope when
  several tests share them.
