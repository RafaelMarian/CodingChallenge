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
 *   We are not using vector here; this is a C array. `int nums[]` in a
 *   function parameter is *not* an array. It decays to `int *` — a pointer
 *   to the first element. The pointer does not store the length, so you
 *   MUST pass `n` yourself. In main, `sizeof(nums) / sizeof(nums[0])` works
 *   only while `nums` is still a real array (not yet decayed).
 *
 * C theory
 *   `int search(int nums[], int n, int key)` is the decayed-array interface:
 *   a pointer to the first int, plus a length. `nums[i]` is `*(nums + i)`.
 *   Passing the array does not copy the buffer; it passes one address.
 *
 * Complexity: O(n) time, O(1) extra space.
 */

#include <iostream>
using namespace std;

int search(int nums[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (nums[i] == key)
            return i;
    }
    return -1;
}

int main() {
    int nums[] = {8, 3, 10, 5, 7, 1, 9, 6, 4, 2};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << search(nums, n, 9) << "\n";  // 6
    return 0;
}
