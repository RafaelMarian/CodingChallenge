/*
 * LESSON — Linear search (the baseline every other search is measured against)
 *
 * Problem
 *   Given an unordered array, return the index of `key`, or -1 if absent.
 *
 * Why this is first
 *   Before binary search, hashing, or two pointers, you must be honest about
 *   the naive scan. It is O(n) time and O(1) extra memory. On a cold cache it
 *   is still the fastest way to search a *tiny* array, because there is no
 *   extra setup. On a large unordered array it is the *only* correct general
 *   method unless you build an index.
 *
 * Memory
 *   A std::vector is a small stack object (typically three words: pointer,
 *   size, capacity) whose *buffer* is on the heap. Passing
 *   `const std::vector<int>&` passes the address of that stack object: no
 *   copy of the buffer. The parameter is one machine word. No allocation,
 *   no free. `v.size()` is `size_t` (unsigned) — not a signed int.
 *
 * C theory
 *   A C version would be `int search(const int *a, int n, int key)`. That is
 *   the decayed-array interface: a pointer to the first int, plus a length
 *   because the pointer does not know the size. `v.data()` and `v.size()`
 *   give you exactly that C interface if you ever need to call C code.
 *
 * Complexity: O(n) time, O(1) extra space.
 */

#include <iostream>
#include <vector>

int search(const std::vector<int>& nums, int key) {
    for (std::size_t i = 0; i < nums.size(); ++i) {
        if (nums[i] == key) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

int main() {
    std::vector<int> nums{8, 3, 10, 5, 7, 1, 9, 6, 4, 2};
    std::cout << search(nums, 9) << '\n';  // 6
    return 0;
}
