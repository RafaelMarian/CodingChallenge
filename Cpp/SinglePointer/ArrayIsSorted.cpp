/*
 * LESSON — Is the array non-decreasing?
 *
 * Problem
 *   Return true iff nums[i] <= nums[i+1] for every adjacent pair.
 *
 * Intuition
 *   A single left-to-right pointer is enough. The moment you see a descent,
 *   you can reject. You do not need a second pass.
 *
 * Memory
 *   Pure read. No extra buffer. `int nums[]` decays to a pointer, so you
 *   MUST pass n. The CPU prefetches sequential ints, so this is about as
 *   cache-friendly as a loop gets.
 *
 * C theory — off-by-one
 *   The last valid index is n-1. The last *pair* starts at n-2.
 *   Writing `i < n` and then reading nums[i+1] is an out-of-bounds
 *   access: undefined behavior. The compiler owes you nothing: crash,
 *   silent wrong answer, or "works on this machine." Loop while
 *   `i < n - 1` so that `i + 1` is always in range.
 *
 * Complexity: O(n) time, O(1) extra space.
 */

#include <iostream>
using namespace std;

bool isSorted(int nums[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (nums[i] > nums[i + 1])
            return false;
    }
    return true;
}

int main() {
    int nums[] = {2, 3, 5, 5, 6, 7, 8, 9, 12, 15};
    int n = sizeof(nums) / sizeof(nums[0]);
    bool ok = isSorted(nums, n);
    cout << "ans" << (ok ? "true" : "false") << "\n";
    return 0;
}
