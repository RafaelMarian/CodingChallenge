/*
 * LESSON — Minimum of a rotated sorted array (unique elements)
 *
 * Student, the array is sorted ascending then rotated. All values
 * distinct. Return the minimum. Sample {10,11,12,13,3,4,5,6,7}:
 * the cut is between 13 and 3, so the min is 3.
 *
 * Intuition
 *   In an unrotated array nums[h] is the largest of the remaining
 *   range and nums[0] is the min. After a rotation, the minimum is
 *   the first element of the right sorted piece — the value that is
 *   smaller than its left neighbor, if it has one.
 *
 *   Probe mid.
 *     If mid != 0 and nums[mid] < nums[mid-1], mid is the rotation
 *     point: return nums[mid]. That is the min.
 *     If mid == 0, there is no left neighbor. Do not read nums[-1].
 *     That load is undefined behavior. Fall through to the half test.
 *
 *   Half test: if nums[h] > nums[mid], the right side from mid to h
 *   is increasing, so the min is in the left piece *including* mid
 *   (mid might still be the min if we skipped the neighbor test).
 *   Set h = mid. Otherwise the seam is to the right of mid (nums[mid]
 *   sits in the large left piece): set l = mid + 1.
 *
 *   Loop while l < h so the range keeps shrinking. When l == h you
 *   hold the min.
 *
 * Complexity
 *   O(log n) time, O(1) extra memory. Distinctness keeps the half
 *   test honest. Duplicates would force linear worst case, as in
 *   the rotated-search-with-duplicates lesson.
 *
 * Memory
 *   int nums[], int n. Two or three ints. No extra array. We return
 *   a value, not an index, so the caller never indexes with our
 *   internals. nums decayed to a pointer; n is the length.
 *
 * C theory — neighbor access, overflow, rotation
 *   The guard mid != 0 is a bounds check. C will not do it for you.
 *   nums[mid - 1] with mid == 0 reads before the buffer: UB, a
 *   possible segfault or a silent load of a saved register in the
 *   frame. Write the guard every time you look left.
 *
 *   mid = l + (h - l) / 2. Including mid on the left (h = mid) is
 *   safe with while (l < h): if you wrote h = mid - 1 you could
 *   drop the min unless the neighbor test already returned it.
 *
 *   Unrotated input: nums[h] > nums[mid] always in a strictly
 *   increasing range, h shrinks toward 0, answer nums[0]. Good.
 *
 *   Cache: logarithmic random loads in a contiguous buffer. Same
 *   as binary search. For n = 9 this is academic; for n = 10^7 it
 *   is why you do not scan.
 *
 * Sample prints 3.
 */

#include <iostream>
using namespace std;

int findMin(int nums[], int n) {
    int l = 0;
    int h = n - 1;
    while (l < h) {
        int mid = l + (h - l) / 2;
        if (mid != 0 && nums[mid] < nums[mid - 1]) {
            return nums[mid];
        }
        if (nums[h] > nums[mid]) {
            h = mid;
        } else {
            l = mid + 1;
        }
    }
    return nums[l];
}

int main() {
    int nums[] = {10, 11, 12, 13, 3, 4, 5, 6, 7};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << findMin(nums, n) << "\n";
    return 0;
}
