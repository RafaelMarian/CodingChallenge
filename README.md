# Coding Challenges in C++

A course of algorithm drills written in C++, taught with the C machine model:
memory layout, pointers, ownership, undefined behavior, and complexity.

1. Read [`Cpp/00_FOUNDATIONS.md`](Cpp/00_FOUNDATIONS.md) once, slowly.
2. Work through the folders **in the order below**.
3. Compile and run every file. Do not only read.
4. After each file, close it and re-implement the function from memory.

```bash
# one lesson
g++ -std=c++17 -Wall -Wextra -Wpedantic -O0 -g Cpp/SinglePointer/LinearSearch.cpp -o /tmp/cc && /tmp/cc

# sanitizers (catch UB: out-of-bounds, signed overflow, use-after-free)
g++ -std=c++17 -O0 -g -fsanitize=address,undefined Cpp/SinglePointer/LinearSearch.cpp -o /tmp/cc && /tmp/cc

# every lesson, compiled and executed
make -C Cpp
```

---

## Study order (do not skip)

| Step | Folder | What you are learning |
|------|--------|------------------------|
| 1 | `Cpp/00_FOUNDATIONS.md` | Compilation, process memory, pointers, RAII, UB |
| 2 | `Cpp/SinglePointer/` | Contiguous arrays, overflow, one-pass scans |
| 3 | `Cpp/TwoPointer/` | In-place mutation, swaps, C strings `char s[]` |
| 4 | `Cpp/ThreePointers/` | Partitioning a range in one pass |
| 5 | `Cpp/PrefixSum/` | Extra memory as a time trade |
| 6 | `Cpp/SlidingWindow/` | Amortized O(n) windows |
| 7 | `Cpp/Kadanes/` | Local decisions that keep a global optimum |
| 8 | `Cpp/Stack/` | Monotonic stacks, LIFO, C array + `top` index |
| 9 | `Cpp/Hashing/` | Counting arrays vs hash tables, collisions |
| 10 | `Cpp/BoyerMooreMajority/` | Constant extra memory algorithms |
| 11 | `Cpp/BinarySearch/` | Search on indices *and* on the answer |
| 12 | `Cpp/MergeIntervals/` | Sorting + greedy merge |
| 13 | `Cpp/Gussai/` | Closed-form math vs hardcoding |

Each `.cpp` file is a lesson: problem, why the algorithm is correct, complexity,
memory and C theory, then working code you compile.
