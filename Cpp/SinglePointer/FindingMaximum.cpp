/*
 * LESSON — Maximum of an array, and why INT_MIN is a loaded constant
 *
 * Problem
 *   Return the largest value in the array.
 *
 * Intuition
 *   Keep a running champion. Compare each element to it. One pass.
 *
 * Memory
 *   Three machine words besides the input: the index, the current value
 *   (often in a register), and `max`. No heap.
 *
 * C theory — sentinels
 *   std::numeric_limits<int>::min() (or INT_MIN from <climits>) is -2^31
 *   on this machine. Using that as the initial champion is correct
 *   *only if* every element is >= INT_MIN, which is always true for int.
 *   It is *wrong* if you later want "no element seen yet" as a distinct
 *   state (an empty array): INT_MIN is a valid value, so you cannot tell
 *   "empty" from "the max really is INT_MIN".
 *
 *   Professional pattern for a non-empty array: initialize max to nums[0]
 *   and start the loop at 1. Then empty arrays are an explicit error, not a
 *   silent lie.
 *
 * Complexity: O(n) time, O(1) extra space.
 */

#include <iostream>
#include <limits>
#include <vector>

int getMax(const std::vector<int>& nums) {
    int max = std::numeric_limits<int>::min();
    for (int x : nums) {
        if (x > max) {
            max = x;
        }
    }
    return max;
}

int main() {
    std::vector<int> nums{7, 5, 4, 16, 3, 9, 11, 13, 12, 8};
    std::cout << getMax(nums) << '\n';  // 16
    return 0;
}
