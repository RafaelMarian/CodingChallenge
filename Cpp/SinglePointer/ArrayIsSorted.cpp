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
 *   Pure read. No extra buffer. The CPU prefetches sequential ints, so this
 *   is about as cache-friendly as a loop gets.
 *
 * C theory — off-by-one
 *   The last valid index is size-1. The last *pair* starts at size-2.
 *   Writing `i < nums.size()` and then reading nums[i+1] is an out-of-bounds
 *   access: undefined behavior. The compiler owes you nothing: crash,
 *   silent wrong answer, or "works on this machine." This is why we loop
 *   so that `i + 1` is always in range.
 *
 *   size_t is unsigned. `i < nums.size() - 1` is dangerous if size() is 0
 *   because unsigned wrap: 0-1 becomes a huge number. We write
 *   `i + 1 < nums.size()` instead, which is well-defined for empty arrays.
 *
 * Complexity: O(n) time, O(1) extra space.
 */

#include <iostream>
#include <vector>

bool isSorted(const std::vector<int>& nums) {
    for (std::size_t i = 0; i + 1 < nums.size(); ++i) {
        if (nums[i] > nums[i + 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    std::vector<int> nums{2, 3, 5, 5, 6, 7, 8, 9, 12, 15};
    std::cout << "ans" << std::boolalpha << isSorted(nums) << '\n';
    return 0;
}
