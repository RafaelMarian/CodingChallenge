/*
 * LESSON — Container with most water
 *
 * Student, the brute force is every pair of indices (l, r) as the two
 * walls, area = min(height[l], height[r]) * (r - l), take the max.
 * That is O(n^2) pairs. Two pointers drop the pairs that cannot beat
 * the current best, in O(n) steps.
 *
 * Problem
 *   height[i] is a vertical line at x = i. Choose two lines. The
 *   container's area is the min of the two heights times the distance
 *   between indices. Maximize that area. Sample: {1,4,10,5,2,6,7,3}
 *   prints 28 (the lines of height 10 and 7, width 4).
 *
 * Algorithm intuition
 *   Start at the widest container: l = 0, r = n-1. Compute that area.
 *   Then you must shrink the width by one. Moving the taller wall
 *   cannot increase the min-height (the short wall still limits) and
 *   strictly decreases width, so that area is worse. Moving the
 *   shorter wall is the only move that might raise the limiting
 *   height enough to compensate for the lost width. If the walls are
 *   equal, moving either is symmetric; we move one of them (here, r).
 *
 *   Repeat until l and r meet. Every index is a candidate left or
 *   right wall at most once. The global maximum is among the O(n)
 *   containers you evaluate, because any discarded inner pair with
 *   the old short wall sat under a shorter or equal min-height and a
 *   smaller width.
 *
 * Complexity
 *   Time  O(n). Extra space O(1): two indices and the running max.
 *
 * Memory management
 *   const std::vector<int>&: read-only, no copy, no heap. The answer
 *   is one integer. Stack locals only. This is a pure load-and-compare
 *   scan of the caller's buffer.
 *
 *   In C: int max_area(const int *h, size_t n). Same loads.
 *
 * C theory — why not move the tall side; overflow of area; cache; UB
 *   Let h[l] < h[r]. Any container (l, k) with k < r has width
 *   smaller than (r-l) and min-height at most h[l], because the left
 *   wall is still the short one or the other wall is even shorter.
 *   So those areas are <= h[l] * (r-l), which you already considered
 *   (or will, as the current area). Discarding them by ++l is safe.
 *   That is the invariant. If you moved r instead, you would throw
 *   away pairs that still use a tall right wall and a better left
 *   wall you have not met yet.
 *
 *   Area = min(h[l], h[r]) * (r - l). Both factors can be large.
 *   2^31 * n does not fit in 32-bit int. Signed overflow of that
 *   multiply is UB. Compute
 *     1LL * std::min(height[l], height[r]) * (r - l)
 *   in long long, then keep ans as long long. The sample fits in
 *   int; we still accumulate in 64-bit and cast for printing if the
 *   API wants int. Here we print the int value of the sample.
 *
 *   r - l as size_t is a width. Mixing int min-height and size_t
 *   width: promote explicitly to long long rather than hoping the
 *   usual arithmetic conversions do what you think.
 *
 *   Empty or n < 2: area 0. Do not form n-1.
 *
 *   Cache: two ends, sequential inward, like reverse. Each step
 *   loads one new cell. Excellent.
 *
 *   No mutation. Heights are never written. No overflow of the
 *   height values themselves; we only min and multiply in 64-bit.
 *
 *   Indices as size_t, l < r before any height[r]. After ++l or --r
 *   the loop condition rechecks.
 */

#include <algorithm>
#include <iostream>
#include <vector>

int maxArea(const std::vector<int>& height) {
    if (height.size() < 2) {
        return 0;
    }
    std::size_t l = 0;
    std::size_t r = height.size() - 1;
    long long ans = 0;
    while (l < r) {
        const int min_h = std::min(height[l], height[r]);
        const long long area = 1LL * min_h * (r - l);
        if (area > ans) {
            ans = area;
        }
        if (height[l] < height[r]) {
            ++l;
        } else {
            --r;
        }
    }
    return static_cast<int>(ans);
}

int main() {
    const std::vector<int> arr{1, 4, 10, 5, 2, 6, 7, 3};
    std::cout << maxArea(arr) << '\n';
    return 0;
}
