/*
 * LESSON — Third maximum: the same idea, one more slot
 *
 * Problem
 *   Track the top three values in one left-to-right pass.
 *
 * Intuition
 *   A 3-element sorted window of "best so far." A new value is inserted
 *   into the correct slot, shifting the worse ones down. After n steps
 *   the window holds the answer.
 *
 * Why not sort?
 *   Sorting is the right tool when you need the full order. For a fixed
 *   k (here k = 3) a k-slot scan is O(n) vs O(n log n), and uses O(1)
 *   extra memory. This is selection, not sorting.
 *
 * C theory — assignment order is data flow
 *   third = second; second = first; first = x;
 *   Reverse those three lines and you clobber first before you save it.
 *   Compilers will not warn. Draw the registers on paper once.
 *
 *   Same INT_MIN caveat as FindingMaximum: if the array has fewer than
 *   three elements, you will return INT_MIN, which may or may not be what
 *   the caller wanted. Production code would check n >= 3.
 *
 * Complexity: O(n) time, O(1) extra space.
 */

#include <iostream>
#include <limits>
#include <vector>

int thirdMaximum(const std::vector<int>& nums) {
    int firstMax = std::numeric_limits<int>::min();
    int secondMax = std::numeric_limits<int>::min();
    int thirdMax = std::numeric_limits<int>::min();
    for (int x : nums) {
        if (x > firstMax) {
            thirdMax = secondMax;
            secondMax = firstMax;
            firstMax = x;
        } else if (x > secondMax) {
            thirdMax = secondMax;
            secondMax = x;
        } else if (x > thirdMax) {
            thirdMax = x;
        }
    }
    return thirdMax;
}

int main() {
    std::vector<int> nums{8, 5, 3, 11, 9, 4, 16, 7, 12, 13};
    std::cout << thirdMaximum(nums) << '\n';  // 13
    return 0;
}
