# Foundations: C and C++, taught from the machine up

Read this before the challenges. Excellent software engineers do not only know
*what* an algorithm does. They know *where the bytes live*, *who owns them*,
and *what the language promises* (and does not promise).

C is the portable assembly of UNIX: types, pointers, and a thin runtime.
C++ is C's model plus types that can own resources. These lessons are C++
source. Underneath every `std::vector` is the same C story: a pointer, a
length, and a heap buffer you are responsible for.

---

## 1. What a program actually is

The compiler produces **machine code**. Rough pipeline:

```
source.cpp  ->  preprocessor  ->  compiler  ->  assembler  ->  linker  ->  executable
   .cpp           #include           .s / .o        .o          libc++        a.out
```

- **Preprocessor**: text substitution (`#include`, `#define`). It does not
  understand types.
- **Compiler**: parses C++, type-checks, emits object code.
- **Linker**: stitches object files and libraries, resolves `main`, `printf`,
  `std::cout`.
- **Loader** (OS): maps the binary into a process: code, static data, heap, stack.

A missing `#include` is a **compile** error. A missing library is a **link**
error. A wild pointer is a **runtime** crash — or silent corruption.

Compile every lesson with warnings on:

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -O0 -g file.cpp -o file
```

`-O0 -g` keeps the mapping from source to machine honest while you learn.
Later, `-O2` changes codegen (inlining, unrolling) but not the *meaning* of
well-defined programs.

C compilation is the same pipeline with `gcc` and a `.c` file. C++ adds name
mangling, constructors, and a richer standard library. The CPU still executes
loads, stores, and jumps.

---

## 2. Process memory layout

A typical user-space process (addresses grow as drawn):

```
high addresses
  ┌─────────────────────────┐
  │ stack                   │  function frames, locals, return addresses
  │         ↓ grows down    │
  ├─────────────────────────┤
  │ ... unused ...          │
  ├─────────────────────────┤
  │         ↑ grows up      │
  │ heap                    │  malloc / new / std::vector buffer
  ├─────────────────────────┤
  │ BSS  (zero-initialized  │  global/static with no explicit init
  │       static storage)   │
  ├─────────────────────────┤
  │ data (initialized       │  global/static with values
  │       static storage)   │
  ├─────────────────────────┤
  │ text (machine code)     │  your functions, usually read-only
  └─────────────────────────┘
low addresses
```

**Stack**

- Each call pushes a **frame**: return address, spilled registers, locals.
- Allocation is a pointer bump (`sub rsp, N`). Freeing is `ret`. Extremely fast.
- Size is limited (often a few MB). `int a[10'000'000];` as a local can
  smash the stack.
- Objects on the stack die when the scope ends. That is the heart of RAII.

**Heap**

- `malloc` / `new` / the buffer inside `std::vector` live here.
- The allocator talks to the OS (`brk` / `mmap`) in chunks, then hands you
  pieces.
- Someone **must** free it. In C that is `free`. In C++ that is a destructor
  (or `delete`, which you should not write by hand in these lessons).

**Static storage**

- Globals and `static` locals live for the whole program.
- `.data` holds explicit initializers; `.bss` is zeroed by the loader.

C equivalent of a vector:

```c
int *a = malloc(n * sizeof *a);
if (!a) abort();
/* use a[0..n) */
free(a);
```

C++ equivalent you will actually write:

```cpp
std::vector<int> a(n);  // constructor mallocs, destructor frees
```

The vector *object* is a few words on the stack (pointer, size, capacity).
The *elements* are on the heap. Passing `const std::vector<int>&` passes the
address of that stack object: no copy of the buffer.

---

## 3. Values, pointers, references, arrays

```cpp
int  x  = 42;   // a value: 42 lives in this object
int* p  = &x;   // a pointer: p holds the address of x
int& r  = x;    // a reference: another name for x, bound at initialization
```

| | Pointer `T*` | Reference `T&` |
|---|---|---|
| Can be null? | Yes (`NULL` / `nullptr`) | No, in well-defined code |
| Can reseat? | Yes (`p = q`) | No |
| Arithmetic? | Yes (`p + 1`) | No |
| Must dereference? | Yes (`*p`, `p->`) | Implicit |

**Pointer arithmetic** is how C arrays work: `a[i]` is defined as `*(a + i)`.
If `p` points to an `int`, `p + 1` advances **one int**, not one byte. The
compiler multiplies by `sizeof(int)`.

**Array-to-pointer decay** is the C rule you must never forget:

```c
void f(int a[10]);   /* lie: this is still int *a */
void f(int *a, size_t n);  /* honest C interface */
```

A parameter declared as an array **decays** to a pointer. `sizeof(a)` inside
`f` is the size of a pointer (8 bytes on LP64), not the array. That is why C
functions take a length, and why C++ prefers `std::vector` or `std::span`.

**Pass by value vs pass by reference**

```cpp
void by_value(std::vector<int> v);        // copies the vector (heap alloc + memcpy)
void by_ref  (std::vector<int>& v);       // alias; callee can mutate
void by_cref (const std::vector<int>& v); // alias, read-only — default for input
void by_ptr  (const int *a, std::size_t n); // C interface; no ownership
```

Prefer `const T&` for large inputs. Prefer `T` (by value) for small types
(`int`, `double`, pointers). Prefer `T*` when you mean "optional" or "C array."

---

## 4. Ownership and RAII (C++ on top of C)

In C, every `malloc` has a matching `free` on every path, including errors.
Miss one path and you leak. Free twice and you corrupt the heap.

**RAII** = Resource Acquisition Is Initialization. Tie the resource to an
object's lifetime:

- Constructor acquires (memory, file, lock).
- Destructor releases. Destructors run when the object leaves scope,
  including during exception unwinding.

```cpp
{
    std::vector<int> v{1, 2, 3};  // constructor allocates
} // destructor frees. You never call delete.
```

Do **not** write `new` / `delete` in these lessons. The STL already does it
correctly. Raw `new` is how leaks, double-frees, and use-after-free are born.

Mental model: **every resource has exactly one owner**. `std::vector` owns
its buffer. `std::unique_ptr` owns a single heap object. `std::shared_ptr`
is refcounted shared ownership — use it rarely.

The C analogue of RAII is `goto cleanup;` plus a single `free` at the bottom
of a function. C++ automates that pattern with destructors.

---

## 5. Integer types, overflow, and undefined behavior

On this machine `int` is 32-bit two's complement. The C and C++ standards
only *guarantee* `INT_MIN <= -32767` and `INT_MAX >= 32767`. These lessons
treat `int` as 32-bit.

**Signed overflow is undefined behavior (UB).**

```cpp
int s = (n * (n + 1)) / 2;   // if n*(n+1) overflows, the program is meaningless
```

The compiler may assume overflow never happens and delete "impossible"
checks. Unsigned overflow wraps modulo 2^w and is well-defined. That is why
`size_t` wrap-around is sneaky but legal, while `int` wrap-around is not.

Fixes you will see in the course:

- Compute in `long long` (at least 64-bit). Force it with `1LL * a * b`.
- Use `l + (r - l) / 2` instead of `(l + r) / 2` so the midpoint cannot overflow.
- Watch `INT_MIN`: unary minus of `INT_MIN` cannot be represented in 32-bit
  two's complement.

**Other UB you will meet:** out-of-bounds access, use of uninitialized
storage, dangling pointers, data races. The compiler owes you **nothing**.
The program may crash, appear to work, or corrupt data later.

Professional habit:

```bash
g++ -std=c++17 -O0 -g -fsanitize=address,undefined file.cpp -o file
```

AddressSanitizer catches heap/stack overflows and use-after-free.
UndefinedBehaviorSanitizer catches signed overflow and many misaligned loads.

---

## 6. Cache, locality, and why arrays win

The CPU fetches **cache lines** (typically 64 bytes), not single ints.
A contiguous `int a[n]` or `std::vector<int>` is friendly: walking
`a[i], a[i+1], ...` hits the same line, then the next.

A node-based structure (`std::list`, a pointer graph) jumps around the heap.
Same big-O, worse constants, worse branch prediction, worse prefetching.

This is why so many of these challenges stay on arrays: O(1) extra memory
and sequential access is how real systems stay fast.

`sizeof(int)` is 4. A 64-byte line holds 16 ints. A linear scan of a million
ints is a few tens of thousands of line fills. A pointer-chasing scan of a
million nodes can be a million cache misses.

---

## 7. Complexity you must say out loud

For every function, state:

- **Time**: worst case in `n` (and extra parameters `k`, `W`, ...).
- **Extra space**: besides the input. In-place O(1) vs a copy O(n).
- **What you mutate**: does the caller still have the original array?

Big-O hides constants. `O(n)` hashing with a cold cache can lose to
`O(n log n)` on sorted arrays of moderate `n`. Reason first; measure when
it matters.

---

## 8. C library vs C++ STL you will use

| Need | C | C++ |
|------|---|-----|
| Dynamic array | `malloc` + length | `std::vector<T>` |
| Bytes of text | `char *` + `strlen` | `std::string` |
| Sort | `qsort` | `std::sort` |
| Min / max | ternary | `std::min` / `std::max` |
| Hash table | roll your own | `std::unordered_map` |
| Ordered map | roll your own | `std::map` |
| Stack | array + `top` index | `std::vector` used as a stack |
| Limits | `INT_MIN` in `<limits.h>` | `std::numeric_limits<int>::min()` |
| Print | `printf` | `std::cout` (`'\n'` not `std::endl`) |

`std::endl` flushes the stream. Prefer `'\n'` unless you need a flush.

`std::vector::size()` returns `size_t` (unsigned). `i < v.size() - 1` is
wrong on an empty vector: unsigned 0 - 1 wraps to a huge number. Write
`i + 1 < v.size()` instead.

---

## 9. How to study each challenge

1. Read the header comment (problem + why the algorithm is correct).
2. Trace the sample on paper with indices. Draw the array in memory.
3. Compile and run. Change the input. Break it on purpose.
4. Ask: *where do the bytes live? who frees them? can `int` overflow?*
5. Re-implement in a blank file without looking.

When you can explain **correctness, complexity, and memory** without the
comments, you are done with that lesson.
