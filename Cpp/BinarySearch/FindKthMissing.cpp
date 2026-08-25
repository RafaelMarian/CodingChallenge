/*
 * LESSON — Kth missing positive, by binary search on the gap count
 *
 * Student, arr is a strictly increasing sequence of positive ints,
 * conceptually starting from 1 as the first natural number that
 * might be missing. Return the k-th positive integer that does not
 * appear in arr. Sample {2,3,4,7,11}, k = 1: the missing positives
 * are 1, 5, 6, 8, 9, 10, ... so the 1st is 1.
 *
 * Intuition
 *   At index mid, the value arr[mid] "should" have been mid+1 if the
 *   array had been 1,2,3,... with nothing missing. The number of
 *   missing positives strictly before this slot (among 1..arr[mid])
 *   is
 *
 *       totMissing = arr[mid] - (mid + 1)
 *
 *   Example: arr[0] = 2, totMissing = 2 - 1 = 1 (the missing 1).
 *   arr[3] = 7, totMissing = 7 - 4 = 3 (missing 1,5,6).
 *
 *   If totMissing < k, the k-th missing is to the right of mid:
 *   low = mid + 1. Otherwise it is at mid or to the left:
 *   high = mid - 1.
 *
 *   After the loop, high is the last index with totMissing < k
 *   (or -1 if even index 0 has enough missing). How many numbers
 *   have we "consumed" from the 1..infinity line? We have high+1
 *   array elements before the answer, so the k-th missing is
 *
 *       k + high + 1
 *
 *   For the sample, high becomes -1, return 1 + (-1) + 1 = 1.
 *
 * Complexity
 *   O(log n) time, O(1) extra memory. A linear scan that increments
 *   k whenever arr[i] <= k is O(n) and also correct; binary search
 *   is the lesson.
 *
 * Memory management
 *   const std::vector<int>&. A few ints. No extra buffer. We never
 *   materialize the missing numbers.
 *
 * C theory — searching a count, not a value; overflow
 *   This is binary search on an implicit monotone predicate:
 *   "are there fewer than k missing before index mid?" The array
 *   is the random-access structure that lets us evaluate the
 *   predicate in O(1). We are not looking up k inside arr; k may
 *   not appear at all.
 *
 *   arr[mid] - (mid + 1) can theoretically underflow if arr were
 *   not strictly increasing positives. The precondition keeps it
 *   non-negative. Signed underflow of a negative result is just a
 *   negative int here (well-defined if it does not overflow past
 *   INT_MIN); a broken input would simply give a wrong answer.
 *
 *   Return k + high + 1: high can be -1, so this is k. high can be
 *   n-1, so the answer may lie past the end of the array (more
 *   missing after the last element). That addition is ordinary int
 *   arithmetic; for huge k use long long.
 *
 *   mid = (low + high) / 2 is the overflow hazard. We write
 *   low + (high - low) / 2.
 *
 *   Cache: logarithmic loads of a contiguous strictly increasing
 *   buffer. Fine.
 *
 *   C: int kth(const int *a, int n, int k); same formula.
 *
 * Sample prints 1.
 */

#include <iostream>
#include <vector>

int findKthPositive(const std::vector<int>& arr, int k) {
    int low = 0;
    int high = static_cast<int>(arr.size()) - 1;
    while (low <= high) {
        const int mid = low + (high - low) / 2;
        const int totMissing = arr[static_cast<std::size_t>(mid)] - (mid + 1);
        if (totMissing < k) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return k + high + 1;
}

int main() {
    const std::vector<int> nums{2, 3, 4, 7, 11};
    std::cout << findKthPositive(nums, 1) << '\n';
    return 0;
}
