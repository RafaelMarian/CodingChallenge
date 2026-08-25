/*
 * LESSON — Leaders from the right, and why insert-at-front is a trap
 *
 * Problem
 *   A right-leader is greater than everything to its *right*. Scan from
 *   the end, keep a running max, collect leaders.
 *
 * Naive approach: insert each new leader at the front of a growing array
 * so the result comes out left-to-right. That is O(k) per insert (shift
 * every element), O(k^2) total.
 *
 * The engineer version:
 *   push_back while scanning right-to-left (O(1) amortized), then
 *   std::reverse the result (O(k)). Same order, O(n) time.
 *
 * Memory
 *   Same as left-elders: a growing vector of ints. reverse() swaps in
 *   place; no second buffer.
 *
 * C theory — why add(0, x) hurts
 *   Contiguous arrays make append cheap and front-insert expensive.
 *   Linked lists make front-insert cheap and sequential scan expensive
 *   (no cache). Pick the structure that matches the hot operation.
 *   Here the hot operation is "append, then reverse once."
 *
 * Complexity: O(n) time, O(k) extra space.
 */

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

std::vector<int> rightElder(const std::vector<int>& nums) {
    int max = std::numeric_limits<int>::min();
    std::vector<int> leaders;
    for (int i = static_cast<int>(nums.size()) - 1; i >= 0; --i) {
        if (nums[static_cast<std::size_t>(i)] > max) {
            max = nums[static_cast<std::size_t>(i)];
            leaders.push_back(max);
        }
    }
    std::reverse(leaders.begin(), leaders.end());
    return leaders;
}

int main() {
    std::vector<int> nums{7, 5, 4, 17, 3, 8, 13, 2, 6, 9};
    for (int x : rightElder(nums)) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
    return 0;
}
