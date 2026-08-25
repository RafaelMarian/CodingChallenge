/*
 * LESSON — Previous and next values around a key in a sorted array
 *
 * Student, the array is sorted, distinct in this sample. Key may or
 * may not be present. Print two ints: the predecessor and the
 * successor in value, using -1 when that neighbor does not exist.
 *
 *   If key is present at index i: print nums[i-1] (or -1) and
 *   nums[i+1] (or -1). Those are the neighbors of that index.
 *   If key is absent: print the greatest element < key and the
 *   least element > key, again with -1 at the ends.
 *
 * Sample {3,4,6,7,10,11,13,15}, key 14: 14 is not present. The
 * greatest below is 13, the least above is 15.
 *
 * Intuition
 *   Binary search as lower_bound. If you hit, you have the index.
 *   If you miss, when the loop ends l is the insertion point: the
 *   first index with nums[l] > key (everything left of l is < key).
 *   Then
 *     prev = (l == 0) ? -1 : nums[l - 1]
 *     next = (l == n) ? -1 : nums[l]
 *   That is the whole miss case. Do not reconstruct neighbors from
 *   a stale mid after exit; that is how the original grew a thicket
 *   of end checks. l already is lower_bound.
 *
 * Complexity
 *   O(log n) time, O(1) extra memory.
 *
 * Memory
 *   int nums[], int n. Write two ints into out[2]. No extra buffer.
 *   We do not insert the missing key; we only name its neighbors.
 *   Two ints, not a pair type. nums decayed to a pointer.
 *
 * C theory — lower_bound neighbors, ends, overflow
 *   The insertion index l == n means key is larger than every
 *   element: next is -1, prev is nums[n-1]. l == 0 means key is
 *   smaller than every element: prev is -1, next is nums[0]. Those
 *   are the two end sentinels. Using -1 as "no neighbor" collides
 *   with a legal value of -1 in the array; the sample is positive
 *   so it is fine.
 *
 *   If you read nums[mid-1] when mid == 0, that is UB. The hit
 *   branch guards mid == 0. The miss branch uses l, which may be 0
 *   or n, and guards both.
 *
 *   mid = l + (h - l) / 2. Overflow of l+h is still UB.
 *
 * Sample prints 13 15.
 */

#include <iostream>
using namespace std;

void prevNext(int nums[], int n, int key, int out[]) {
    int l = 0;
    int h = n - 1;
    while (l <= h) {
        int mid = l + (h - l) / 2;
        if (key == nums[mid]) {
            out[0] = (mid == 0) ? -1 : nums[mid - 1];
            out[1] = (mid == n - 1) ? -1 : nums[mid + 1];
            return;
        }
        if (key < nums[mid]) {
            h = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    out[0] = (l == 0) ? -1 : nums[l - 1];
    out[1] = (l == n) ? -1 : nums[l];
}

int main() {
    int nums[] = {3, 4, 6, 7, 10, 11, 13, 15};
    int n = sizeof(nums) / sizeof(nums[0]);
    int out[2];
    prevNext(nums, n, 14, out);
    cout << out[0] << " " << out[1] << "\n";
    return 0;
}
