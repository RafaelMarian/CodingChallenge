/*
 * LESSON — Three-way partition (Dutch national flag)
 *
 * Student, we partition an array into three contiguous bands:
 *
 *     [ values < 2 | values == 2 | values > 2 ]
 *
 * The sample is 1s, 2s, and 3s, not the textbook 0/1/2 coloring.
 * The pivot is 2. The algorithm does not care what the three
 * labels are, only that we can test < pivot, == pivot, > pivot.
 *
 * Intuition
 *   Three indices:
 *     low  — first slot that is not yet known to be < 2
 *     mid  — the cursor; everything in [low, mid) is == 2 already
 *            actually: [0, low) is < 2, [low, mid) is == 2,
 *            (high, n) is > 2, and [mid, high] is unexamined.
 *     high — last slot that is not yet known to be > 2
 *
 *   Loop while mid <= high (the unexamined closed range is non-empty):
 *     nums[mid] <  2: swap with nums[low], low++, mid++.
 *                     The value we swapped in came from [0, low) wait
 *                     no: from the ==2 band's left edge. It is a 2 we
 *                     already saw, or it is the same cell. Either way
 *                     it is examined. Advance mid.
 *     nums[mid] == 2: already in the middle band. mid++.
 *     nums[mid] >  2: swap with nums[high], high--.
 *                     Do NOT increment mid. The value that just
 *                     arrived from the right is unexamined. It might
 *                     be < 2, == 2, or > 2. Mid must look at it on
 *                     the next iteration.
 *
 *   That last point is the whole lesson. Swapping with high pulls an
 *   unknown into mid's seat. Swapping with low pulls a known 2 (or
 *   the same element) into mid's seat, so mid may advance.
 *
 * Complexity
 *   One pass. Each iteration either mid++ or high-- (or both, on the
 *   < 2 branch). The unexamined range shrinks every step. Time O(n).
 *   Extra memory O(1): three indices and a temporary for the swap.
 *   In-place. The caller's array is mutated.
 *
 * Memory management
 *   std::vector<int>& nums is a non-const reference: we permute in
 *   place. No extra buffer. std::swap of two ints is three moves of
 *   a register-width word; no heap. The array is contiguous, so each
 *   swap touches two cache lines at worst (low/mid/high may sit far
 *   apart). Still O(1) extra space and sequential-enough in practice.
 *
 * C theory — partition, swap, aliasing, UB
 *   This is Dijkstra's three-way partition, the same idea that makes
 *   3-way quicksort fast on duplicates. In C:
 *       void flag(int *a, int n);
 *       // swap: int t = a[i]; a[i] = a[j]; a[j] = t;
 *
 *   Pointers: low, mid, high could be int* into the buffer instead of
 *   indices. a[mid] is *(a + mid). The invariant is about ranges of
 *   addresses, not about objects.
 *
 *   Why not increment mid on the high swap: if you did, you would
 *   skip an unexamined value. That value would sit in the middle
 *   band forever. The invariant "[low, mid) is all 2s" would be
 *   false. That is a logic bug, not a crash; the output would be
 *   mis-partitioned. Trace {2,1,3} by hand both ways.
 *
 *   Bounds: mid and high are valid as long as mid <= high and both
 *   started inside the array. After high--, high can become -1; the
 *   loop test mid <= high then fails. Do not read nums[high] after
 *   that. The while condition is the guard. Reading nums[-1] is UB.
 *
 *   Cache: three moving indices, not one sequential scan. Still
 *   linear touches of a contiguous buffer. Far better than allocating
 *   three output arrays and concatenating.
 *
 * Sample {2,1,3,2,1,3,3,1,2,1} becomes 1,1,1,1,2,2,2,3,3,3
 * printed one per line.
 */

#include <algorithm>
#include <iostream>
#include <vector>

void arrangeColors(std::vector<int>& nums) {
    int low = 0;
    int mid = 0;
    int high = static_cast<int>(nums.size()) - 1;
    while (mid <= high) {
        if (nums[static_cast<std::size_t>(mid)] < 2) {
            std::swap(nums[static_cast<std::size_t>(low)],
                      nums[static_cast<std::size_t>(mid)]);
            ++low;
            ++mid;
        } else if (nums[static_cast<std::size_t>(mid)] > 2) {
            std::swap(nums[static_cast<std::size_t>(high)],
                      nums[static_cast<std::size_t>(mid)]);
            --high;
        } else {
            ++mid;
        }
    }
}

int main() {
    std::vector<int> nums{2, 1, 3, 2, 1, 3, 3, 1, 2, 1};
    arrangeColors(nums);
    for (int x : nums) {
        std::cout << x << '\n';
    }
    return 0;
}
