/*
 * LESSON — Unique a sorted array in place; return the new length
 *
 * Student, uniqueness is easy with a hash set and a new buffer. It is
 * more interesting when the array is already sorted and you must keep
 * the unique run in the same allocation.
 *
 * Problem
 *   nums is sorted non-decreasing, so duplicates are adjacent. Overwrite
 *   the array so that the unique values occupy a prefix, in order, and
 *   return k, the number of unique values. The prefix [0, k) is the
 *   answer. Cells [k, n) are unspecified leftover; callers must not read
 *   them as part of the unique sequence. We do not shrink the vector.
 *
 * Algorithm intuition
 *   Slow pointer k is the length of the unique prefix so far, equivalently
 *   the destination index of the next new value. Fast pointer i scans.
 *   When nums[i] differs from the last kept value nums[k-1], it is a new
 *   run: store it at nums[k] and increment k. When it equals nums[k-1],
 *   skip it. Because equals only occur in adjacent runs of a sorted
 *   array, comparing to the last kept value is enough; you never need
 *   a set.
 *
 *   After the scan, [0, k) is strictly increasing (or non-decreasing
 *   with all duplicates squeezed out — here values are unique, so
 *   strictly increasing).
 *
 * Complexity
 *   Time  O(n).
 *   Extra space O(1). The unique values occupy the front of the same
 *   heap buffer. A std::vector erase in a loop from the front would be
 *   O(n^2) moves. A new vector of uniques is O(k) extra memory and a
 *   second allocation. This algorithm needs neither.
 *
 * Memory management
 *   std::vector<int>&: we write unique values into the existing buffer.
 *   We do not call resize(k). The destructor will still free n ints of
 *   capacity, which is correct. If the caller wanted the vector shorter,
 *   they would resize after seeing k. This function's contract is the
 *   LeetCode-style one: return k, leave the tail alone.
 *
 *   k never exceeds n, so we never write past the allocation. We also
 *   never read past it: i < nums.size().
 *
 * C theory — overlapping source and destination, size_t, leftover tail
 *   The copy nums[k] = nums[i] may have k < i (after skipping duplicates)
 *   or k == i (no duplicate yet, the unique prefix is still the whole
 *   scan). When k == i the assignment is a no-op. When k < i we write
 *   into a cell whose original value was already consumed as a duplicate
 *   or already copied forward. Source and destination overlap in the
 *   sense of being the same array, but each assignment is one cell to
 *   one cell, so this is not the memmove/memcpy overlap problem.
 *
 *   memcpy of overlapping regions is undefined behavior. memmove is
 *   defined for overlap. We are not calling either; we assign one int
 *   at a time. That is always well-defined if both indices are in range.
 *
 *   Empty array: there is no nums[k-1]. Return 0 before the loop.
 *   One element: k starts at 1, the loop does not run, return 1.
 *
 *   size_t is unsigned. k - 1 on k == 0 would wrap. We keep k >= 1
 *   after the empty check, so nums[k - 1] is valid.
 *
 *   Cache: one forward scan, mostly streaming. Writes go to the left
 *   side of the same lines. Excellent locality.
 *
 *   Overflow is not involved. In-place mutation is the whole point:
 *   the unique sequence reuses the input's heap cells.
 *
 *   Printing "ans" concatenated with the integer is the sample's
 *   convention, not a format you should use in a library.
 */

#include <iostream>
#include <vector>

int removeDuplicates(std::vector<int>& nums) {
    if (nums.empty()) {
        return 0;
    }
    std::size_t k = 1;
    for (std::size_t i = 1; i < nums.size(); ++i) {
        if (nums[i] != nums[k - 1]) {
            nums[k] = nums[i];
            ++k;
        }
    }
    return static_cast<int>(k);
}

int main() {
    std::vector<int> nums{1, 1, 1, 2, 2, 3, 3, 4, 5, 5};
    std::cout << "ans" << removeDuplicates(nums) << '\n';
    return 0;
}
