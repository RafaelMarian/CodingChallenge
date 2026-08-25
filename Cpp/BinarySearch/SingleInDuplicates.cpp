/*
 * LESSON — The single element in a sorted array of pairs
 *
 * Student, every value appears twice, adjacent, except one value that
 * appears once. The array is sorted. Return the single. Sample
 * {2,2,3,3,4,4,5,6,6,7,7} returns 5.
 *
 * Intuition
 *   Before the single, pairs start at even indices: (0,1), (2,3), ...
 *   After the single, the pattern shifts by one: pairs start at odd
 *   indices. Binary search on that pairing invariant.
 *
 *   Force mid onto an even index: if mid is odd, mid--. Then
 *   nums[mid] and nums[mid+1] should be a pair if we are still to
 *   the left of the single.
 *     If they differ, the single is at mid or to its left: h = mid.
 *     If they match, the single is to the right: l = mid + 2.
 *   When l == h, that index is the single. Return nums[h] (same cell).
 *
 *   Do not call some other function from main. This file's search is
 *   singleInDuplicate. The original driver called a missing name.
 *   That is a compile error, not a lesson.
 *
 * Complexity
 *   O(log n) time, O(1) extra memory. n is odd (2k + 1).
 *
 * Memory management
 *   const std::vector<int>&. No extra buffer. We never write. The
 *   pairing is an observation about indices, not a second array of
 *   flags.
 *
 * C theory — even indices, mid+1 bounds, overflow
 *   If mid is odd we decrement so we land on the start of a would-be
 *   pair. That keeps the invariant aligned with even starts. It also
 *   guarantees mid + 1 is in range while l < h: the last index is
 *   even (n odd => n-1 even), and when mid == h we would not enter
 *   the body because l < h failed... while l < h, mid = l+(h-l)/2
 *   is less than h, so mid+1 <= h. Safe. If you loop l <= h you
 *   must guard mid+1 < n.
 *
 *   Reading nums[mid+1] without that reasoning is how you walk off
 *   the end: UB. Draw the indices on paper once.
 *
 *   mid = l + (h - l) / 2. Same overflow rule.
 *
 *   Cache: logarithmic probes into a contiguous sorted buffer.
 *   The even/odd adjustment is arithmetic on an index, not an extra
 *   load (unless you then load nums[mid] and nums[mid+1], which are
 *   adjacent ints: one cache line).
 *
 *   C: int single(const int *a, int n); a[mid] == a[mid+1] is two
 *   adjacent words. That is the pairing, visible in memory.
 *
 * Sample prints 5.
 */

#include <iostream>
#include <vector>

int singleInDuplicate(const std::vector<int>& nums) {
    int l = 0;
    int h = static_cast<int>(nums.size()) - 1;
    while (l < h) {
        int mid = l + (h - l) / 2;
        if (mid % 2 == 1) {
            --mid;
        }
        if (nums[static_cast<std::size_t>(mid)] !=
            nums[static_cast<std::size_t>(mid + 1)]) {
            h = mid;
        } else {
            l = mid + 2;
        }
    }
    return nums[static_cast<std::size_t>(h)];
}

int main() {
    const std::vector<int> nums{2, 2, 3, 3, 4, 4, 5, 6, 6, 7, 7};
    std::cout << singleInDuplicate(nums) << '\n';
    return 0;
}
