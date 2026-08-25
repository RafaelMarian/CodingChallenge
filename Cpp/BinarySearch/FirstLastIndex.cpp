/*
 * LESSON — First and last index of a target in a sorted array
 *
 * Student, the array is sorted. Target may appear zero or more times.
 * Return the first and last indices where it occurs, or -1 -1 if it
 * is absent. Sample {3,3,3,4,6,6,6,6,7}, target 6: first 4, last 7.
 *
 * Intuition — the version we implement (faithful, O(n) worst)
 *   Binary search until nums[mid] == target. Then walk left while
 *   the previous element is still target, and walk right while the
 *   next is still target. Return those two bounds.
 *
 *   That expand is simple and matches the original. It is O(n) in
 *   the worst case: an array of all target, the walks run to both
 *   ends. You paid for a binary search and then threw the log n
 *   away on the plateau.
 *
 * The O(log n) way you should know
 *   Two binary searches. lower_bound: first index with nums[i] >=
 *   target. upper_bound: first index with nums[i] > target. Then
 *   first = lower, last = upper - 1, after checking that lower
 *   is in range and nums[lower] == target. Each search is O(log n),
 *   even if the whole array is target, because you never scan the
 *   plateau: you keep bisecting with a different predicate
 *   ("still equal to target on the left?" / "still equal on the
 *   right?"). std::equal_range in <algorithm> is that pair.
 *
 *   We implement the expand-after-find so you can see the original
 *   control flow. The comment above is the version you ship.
 *
 * Complexity
 *   This file: O(log n) typical, O(n) worst. Extra memory O(1).
 *   Two-bound binary search: O(log n) always, O(1) extra.
 *
 * Memory management
 *   const std::vector<int>&. We return two ints (a pair). No extra
 *   array. The walks only read. Expanding does not allocate.
 *
 * C theory — plateaus, overflow, bounds on the walks
 *   Sorted arrays turn a run of equals into a contiguous plateau.
 *   Binary search lands somewhere on that plateau, not necessarily
 *   the left edge. That is why a single hit is not enough for
 *   "first" and "last."
 *
 *   Left walk: while (l > 0 && nums[l] == nums[l-1]) l--.
 *   The l > 0 is the guard against nums[-1], which is UB.
 *   Right walk: while (h + 1 < n && nums[h] == nums[h+1]) h++.
 *   The h+1 < n is the guard against one-past-the-end.
 *
 *   mid = l + (h - l) / 2 during the search. Same overflow rule.
 *
 *   Cache: the expand walks are sequential from mid, very local,
 *   until the plateau is huge. Then they are a linear scan. The
 *   two-bound method stays on the logarithmic random-access path.
 *
 *   C: fill two ints *first, *last. Or return a struct of two ints.
 *
 * Sample prints 4 7.
 */

#include <iostream>
#include <utility>
#include <vector>

std::pair<int, int> searchRange(const std::vector<int>& nums, int target) {
    int l = 0;
    int h = static_cast<int>(nums.size()) - 1;
    while (l <= h) {
        const int mid = l + (h - l) / 2;
        if (target == nums[static_cast<std::size_t>(mid)]) {
            l = mid;
            while (l > 0 &&
                   nums[static_cast<std::size_t>(l)] ==
                       nums[static_cast<std::size_t>(l - 1)]) {
                --l;
            }
            h = mid;
            while (h + 1 < static_cast<int>(nums.size()) &&
                   nums[static_cast<std::size_t>(h)] ==
                       nums[static_cast<std::size_t>(h + 1)]) {
                ++h;
            }
            return {l, h};
        }
        if (target < nums[static_cast<std::size_t>(mid)]) {
            h = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return {-1, -1};
}

int main() {
    const std::vector<int> nums{3, 3, 3, 4, 6, 6, 6, 6, 7};
    const std::pair<int, int> res = searchRange(nums, 6);
    std::cout << res.first << ' ' << res.second << '\n';
    return 0;
}
