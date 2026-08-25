/*
 * LESSON — Longest run of 1s
 *
 * Problem
 *   In a binary array, return the length of the longest consecutive
 *   sequence of ones.
 *
 * Intuition
 *   A run is a streak. On a 1, increment the streak. On a 0, the run is
 *   over: harvest it into `best`, reset the streak to 0. After the loop,
 *   harvest once more — the array may end on a run.
 *
 * Memory
 *   Two ints. You do not store the runs. You only keep the best length
 *   seen so far. That is the sliding-window idea in miniature: the
 *   "window" is the current run, and it only ever grows or resets.
 *
 * C theory
 *   `std::max(a, b)` is a template in <algorithm>. Prefer it over a
 *   handwritten if when the intent is "keep the larger." The compiler
 *   will inline it.
 *
 *   Do not forget the final max. Forgetting it is a classic off-by-one
 *   in state machines: the accepting state is never flushed.
 *
 * Complexity: O(n) time, O(1) extra space.
 */

#include <algorithm>
#include <iostream>
#include <vector>

int maxOnes(const std::vector<int>& nums) {
    int best = 0;
    int count = 0;
    for (int x : nums) {
        if (x == 1) {
            ++count;
        } else {
            best = std::max(best, count);
            count = 0;
        }
    }
    return std::max(best, count);
}

int main() {
    std::vector<int> nums{1, 0, 1, 1, 1, 0, 1, 1, 1, 1};
    std::cout << "ans" << maxOnes(nums) << '\n';  // 4
    return 0;
}
