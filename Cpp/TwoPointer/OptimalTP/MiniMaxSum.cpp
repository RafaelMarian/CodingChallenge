/*
 * LESSON — Minimize the maximum pair sum
 *
 * Student, you must pair 2n numbers into n pairs. The cost of a
 * pairing is the maximum of the pair sums. You want that cost as
 * small as possible. Pairing the current smallest with the current
 * largest is the unique structure of the optimum.
 *
 * Problem
 *   Even-length array. Pair every element with exactly one other.
 *   Minimize the maximum of (a + b) over those pairs. Sample:
 *   {2,6,3,4,7,11,5,8} prints 13, from the pair 2+11 (the other
 *   pairs 3+8, 4+7, 5+6 are all 11).
 *
 * Algorithm intuition
 *   Sort. Pair nums[0] with nums[n-1], nums[1] with nums[n-2], and
 *   so on. Track the maximum of those n/2 sums. Return that maximum.
 *
 *   Why not pair large with large: 11+8 = 19, worse. Why not pair
 *   small with small: you then have to pair 11 with something medium
 *   like 7, still 18, and you wasted the small values on each other
 *   where they could have been neutralizing the giants. The sorted
 *   extremes balance the sums. Any inversion (a smaller large-side
 *   value swapped with a larger one) increases the bigger pair sum
 *   or leaves it equal; the max does not improve.
 *
 *   This is the same two-pointer walk as reverse: i++, j--, but you
 *   add instead of swap, and you keep a running max.
 *
 * Complexity
 *   Time  O(n log n) sort plus O(n) pairing.
 *   Extra space O(1) extra besides sort, if we sort in place.
 *
 * Memory management
 *   std::vector<int>&, sorted in the existing heap buffer. No pair
 *   list is stored. We do not allocate n/2 pair objects. The output
 *   is one integer. If you materialized the pairs you would spend
 *   O(n) extra words for no gain in this API.
 *
 *   The vector object remains the caller's. We permute it. Ownership
 *   of the buffer does not change. Destructor still frees it at the
 *   end of main.
 *
 * C theory — pairing extremes, overflow, even n, cache, UB
 *   nums[i] + nums[j] overflow: same rule as always. 1LL * nums[i] +
 *   nums[j], keep max as long long. INT_MAX+INT_MAX fits in 64-bit
 *   signed. Returning int is only valid if the answer fits; the
 *   sample does.
 *
 *   Odd length is not a pairing of everyone. The problem guarantees
 *   even n. If n were odd, one element would be left; the spec would
 *   have to say whether it sits as a singleton "pair." We do not
 *   guess. n < 2: return 0.
 *
 *   i < j with signed indices, or size_t with i < j and no j-- below
 *   zero: because we stop at i < j, when n is even we process n/2
 *   pairs and i meets j in the middle without a leftover cell. For
 *   size_t, start j = n-1 only if n > 0.
 *
 *   std::sort: in-place, introsort, O(log n) stack. Afterward the
 *   pairing reads sequentially from both ends. Two streams, like
 *   reverse, but the values are only loaded, not swapped (the array
 *   is already in the order we need). We could skip writing; we
 *   already wrote during sort.
 *
 *   In-place mutation is the sort, not the pairing. The pairing is
 *   read-only on the sorted permutation.
 *
 *   Cache after sort is excellent. Do not put the numbers in a node
 *   list just to pair them.
 *
 *   C form: qsort the array, then the same i/j loop. qsort's
 *   comparator must not overflow in a compare-by-subtraction; use
 *   (a > b) - (a < b) or a three-way if. std::sort with operator<
 *   on int does not subtract.
 */

#include <algorithm>
#include <iostream>
#include <vector>

int minPairSum(std::vector<int>& nums) {
    if (nums.size() < 2) {
        return 0;
    }
    std::sort(nums.begin(), nums.end());
    std::size_t i = 0;
    std::size_t j = nums.size() - 1;
    long long best = 0;
    while (i < j) {
        const long long s = 1LL * nums[i] + nums[j];
        if (s > best) {
            best = s;
        }
        ++i;
        --j;
    }
    return static_cast<int>(best);
}

int main() {
    std::vector<int> nums{2, 6, 3, 4, 7, 11, 5, 8};
    std::cout << minPairSum(nums) << '\n';
    return 0;
}
