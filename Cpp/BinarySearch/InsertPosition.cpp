/*
 * LESSON — Search insert position (lower_bound)
 *
 * Student, return the index of target if it is present. If not, return
 * the index where it would be inserted to keep the array sorted.
 * Sample {3,4,6,7,10,11,13,15}, target 16: 16 belongs at the end,
 * index 8.
 *
 * Intuition
 *   This is lower_bound: the first position where the element is
 *   not less than target, i.e. the first i with nums[i] >= target.
 *   Binary search as usual. On nums[mid] == target return mid (any
 *   equal index is a legal "found"; lower_bound would return the
 *   leftmost, which this version does not guarantee if duplicates
 *   exist — the sample has none).
 *
 *   When the loop ends, l > h. The invariant is: everything left of
 *   l is < target, everything right of h is > target. So l is the
 *   insertion index. Return l. Do not inspect mid after the loop.
 *   mid is stale: it is whatever the last iteration computed, and a
 *   test like (target < nums[mid] ? mid : mid+1) is a fragile way to
 *   reconstruct what l already is. For target 16, l finishes at 8.
 *
 * Complexity
 *   O(log n) time, O(1) extra memory.
 *
 * Memory
 *   int nums[], int n. No extra buffer. We do not insert; we only
 *   report the index. Insertion itself would be O(n) to shift a
 *   contiguous array. That is a different function. nums decayed
 *   to int*; n is the live length.
 *
 * C theory — lower_bound, one-past-the-end, overflow
 *   If target is larger than every element, l becomes n. That is a
 *   valid insertion index and not a valid access index. Do not
 *   return nums[l] without a bounds check. Returning l as an integer
 *   is fine: the caller decides whether to insert.
 *
 *   If target is smaller than every element, l stays 0.
 *
 *   C's analogue is the insertion point into a sorted buffer:
 *       int i = 0;
 *       while (i < n && a[i] < target) i++;
 *   that is linear. Binary search is the logarithmic version of the
 *   same predicate "is this slot still < target?"
 *
 *   mid = l + (h - l) / 2. (l + h) / 2 can overflow. You have heard
 *   this before because it is the bug that keeps shipping.
 *
 * Sample prints 8.
 */

#include <iostream>
using namespace std;

int searchInsert(int nums[], int n, int target) {
    int l = 0;
    int h = n - 1;
    while (l <= h) {
        int mid = l + (h - l) / 2;
        if (nums[mid] == target) {
            return mid;
        }
        if (nums[mid] > target) {
            h = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return l;
}

int main() {
    int nums[] = {3, 4, 6, 7, 10, 11, 13, 15};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << searchInsert(nums, n, 16) << "\n";
    return 0;
}
