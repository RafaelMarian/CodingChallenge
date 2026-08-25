/*
 * LESSON — A peak element: climb the slope with binary search
 *
 * Student, a peak is an index i where nums[i] is strictly greater than
 * its neighbors (and greater than the one neighbor it has, if i is an
 * end). Return any peak index. Sample {2,3,4,7,9,10,11,12,5,4,3,1}:
 * index 7 holds 12, the unique peak of this unimodal climb-and-drop.
 *
 * Intuition
 *   Look at nums[m] versus nums[m+1].
 *     If nums[m] < nums[m+1], you are on an upslope. A peak exists
 *     to the right (the array cannot rise forever; even if it does
 *     until the end, the last index is a peak by definition). Set
 *     l = m + 1.
 *     If nums[m] >= nums[m+1], you are on a downslope or a peak.
 *     A peak exists at m or to its left. Set r = m.
 *   Loop while l < r. When they meet, that index is a peak.
 *
 *   You are not searching for a value. You are searching for a local
 *   maximum of a sequence by following the discrete derivative. On a
 *   unimodal array there is one peak; on a general array there is at
 *   least one (the global max is a peak) and this walk finds some
 *   local peak, not necessarily the global max.
 *
 * Complexity
 *   O(log n) time, O(1) extra memory. A linear scan also finds a
 *   peak (the global max, even) in O(n). Binary search is the point
 *   of the exercise: the predicate "the slope here goes right"
 *   bisects the index range.
 *
 * Memory
 *   int nums[], int n. Two indices. No extra buffer. We return an
 *   index into the caller's array; the caller already owns it.
 *   nums decayed to int*. n came from sizeof in main.
 *
 * C theory — neighbors at the end, overflow, unimodal climb
 *   Loop is l < r, so m = l + (r - l) / 2 satisfies m < r, hence
 *   m + 1 <= r < n. nums[m+1] is in range. If you used l <= r you
 *   would eventually have m == n-1 and nums[m+1] would be UB.
 *   The loop shape is the bounds check.
 *
 *   Ends are peaks by definition if they beat their single neighbor.
 *   We never special-case index 0 or n-1; the slope rule plus a
 *   shrinking range lands on them when they are peaks.
 *
 *   mid overflow: l + (r - l) / 2, never (l + r) / 2.
 *
 *   Cache: logarithmic adjacent-pair loads. nums[m] and nums[m+1]
 *   are neighbors: one line. Then you jump to a different m. Same
 *   random-access pattern as binary search.
 *
 * Sample prints 7. We do not print l and r along the way.
 */

#include <iostream>
using namespace std;

int findPeakElement(int nums[], int n) {
    int l = 0;
    int r = n - 1;
    while (l < r) {
        int m = l + (r - l) / 2;
        if (nums[m] < nums[m + 1]) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    return r;
}

int main() {
    int nums[] = {2, 3, 4, 7, 9, 10, 11, 12, 5, 4, 3, 1};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << findPeakElement(nums, n) << "\n";
    return 0;
}
