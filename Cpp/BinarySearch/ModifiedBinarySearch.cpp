/*
 * LESSON — Search in a rotated sorted array (distinct elements)
 *
 * Student, the array was sorted ascending, then rotated at some
 * unknown pivot: a suffix moved to the front. Example
 * {6,7,8,9,11,13,14,2,3,5} is {2,3,5,6,7,8,9,11,13,14} rotated.
 * Find the index of key, or -1. Sample key 3 is at index 8.
 *
 * Intuition
 *   In a rotated array with distinct values, one of the two halves
 *   around mid is always sorted (the other contains the rotation
 *   seam). Test which half is sorted, then ask whether key lies
 *   inside that sorted half. If yes, discard the other half. If no,
 *   discard the sorted half. You still throw away about half the
 *   range per step, so the search is binary.
 *
 *   How to tell a half is sorted: nums[l] <= nums[mid] means [l, mid]
 *   is sorted (no seam in there). Otherwise the seam is on the left
 *   and [mid, h] is sorted.
 *
 *   Then, for a sorted left half, key is in it when
 *   nums[l] <= key < nums[mid]. Symmetric on the right:
 *   nums[mid] < key <= nums[h]. The equalities on the ends are
 *   because the range is closed; mid itself was already tested.
 *
 * Complexity
 *   O(log n) time, O(1) extra memory. Same as ordinary binary search.
 *   Distinctness is required for the "one half is sorted" test to be
 *   decisive. Duplicates need a different lesson (SearchRotatedDuplicate.cpp).
 *
 * Memory management
 *   const std::vector<int>&, three ints. No allocation. Random access
 *   into a contiguous buffer, same cache story as classic binary
 *   search: logarithmic loads, not a linear scan.
 *
 * C theory — rotation, invariants, overflow, distinctness
 *   Rotation does not shuffle. It is a cut: concatenate nums[k..n)
 *   with nums[0..k). Both pieces are sorted. That is why a half
 *   without the cut is sorted. If you needed to unrotate, you would
 *   search for the minimum (FindMinRotatedArray.cpp) and then binary
 *   search one of the two sorted pieces. The one-loop version below
 *   does both jobs at once.
 *
 *   mid = l + (h - l) / 2, never (l + h) / 2. Signed overflow of
 *   l + h is UB. Review BinarySearch.cpp if that sentence is not
 *   automatic yet.
 *
 *   Distinct values: if nums[l] == nums[mid] you cannot tell which
 *   half is sorted. The sample has no duplicates, so <= is enough.
 *
 *   C: same indices into const int *a. a[mid] is *(a + mid). The
 *   rotation is a property of the sequence, not of the pointer.
 *
 *   Branching is heavier than classic binary search (nested
 *   conditions). On small n a linear scan still wins. On large n
 *   the log n bound dominates.
 *
 * Sample prints 8.
 */

#include <iostream>
#include <vector>

int modBinarySearch(const std::vector<int>& nums, int key) {
    int l = 0;
    int h = static_cast<int>(nums.size()) - 1;
    while (l <= h) {
        const int mid = l + (h - l) / 2;
        if (key == nums[static_cast<std::size_t>(mid)]) {
            return mid;
        }
        if (nums[static_cast<std::size_t>(l)] <= nums[static_cast<std::size_t>(mid)]) {
            if (key >= nums[static_cast<std::size_t>(l)] &&
                key < nums[static_cast<std::size_t>(mid)]) {
                h = mid - 1;
            } else {
                l = mid + 1;
            }
        } else if (key > nums[static_cast<std::size_t>(mid)] &&
                   key <= nums[static_cast<std::size_t>(h)]) {
            l = mid + 1;
        } else {
            h = mid - 1;
        }
    }
    return -1;
}

int main() {
    const std::vector<int> nums{6, 7, 8, 9, 11, 13, 14, 2, 3, 5};
    std::cout << modBinarySearch(nums, 3) << '\n';
    return 0;
}
