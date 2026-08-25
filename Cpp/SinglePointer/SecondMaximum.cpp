/*
 * LESSON — Second maximum in one pass
 *
 * Problem
 *   Return the second-largest value. This implementation does not skip
 *   duplicates of the maximum, so [5, 16, 16] yields 16 as second max.
 *   (Interview variants often want the second *distinct* maximum — decide
 *   which contract you are implementing before you write the loop.)
 *
 * Intuition
 *   Two champions: firstMax and secondMax. When a new first arrives, the
 *   old first becomes second. When a value sits between them, it becomes
 *   second. Never scan twice.
 *
 * Memory
 *   Two ints. That is the whole extra state. Compare this to sorting
 *   (O(n log n) time, maybe O(n) space) just to read the last two cells.
 *
 * C theory
 *   Updating two variables has an *order*. You must shift third <- second
 *   <- first before overwriting first, or you lose information. Registers
 *   are cheap; lost values are not recoverable. Think of it as a tiny
 *   insertion into a sorted 2-slot window.
 *
 * Complexity: O(n) time, O(1) extra space.
 */

#include <iostream>
#include <limits>
#include <vector>

int secMax(const std::vector<int>& nums) {
    int firstMax = std::numeric_limits<int>::min();
    int secondMax = std::numeric_limits<int>::min();
    for (int x : nums) {
        if (x > firstMax) {
            secondMax = firstMax;
            firstMax = x;
        } else if (x > secondMax) {
            secondMax = x;
        }
    }
    return secondMax;
}

int main() {
    std::vector<int> nums{5, 9, 4, 7, 3, 11, 8, 16, 13, 12};
    std::cout << secMax(nums) << '\n';  // 13
    return 0;
}
