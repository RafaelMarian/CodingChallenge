/*
 * LESSON — Three-sum existence after sorting
 *
 * Student, two-sum on a sorted array is one pair of pointers. Three-sum
 * is that algorithm inside a loop that fixes the third value. You pay
 * a factor of n and you still do not go to O(n^3) brute force.
 *
 * Problem
 *   Return whether three (not necessarily distinct-index) values exist
 *   that add to a target. Indices must be distinct: each position is
 *   used at most once. Sample: {1,4,45,6,10,8} and target 22 is true
 *   (4 + 8 + 10).
 *
 * Algorithm intuition
 *   Sort first. For each index i from 0 to n-3, search for two values
 *   in the strict suffix i+1..n-1 that sum to target - nums[i], using
 *   the sorted two-pointer method: l = i+1, r = n-1, move l if the
 *   triple is too small, move r if too large, return true on equality.
 *
 *   Sorting is allowed because we return a boolean, not original
 *   indices. If you needed indices into the unsorted array, sort
 *   pairs of (value, index) or search without destroying identity.
 *
 *   Skipping duplicate nums[i] is optional for a boolean; it only
 *   helps the "list all unique triples" variant. We skip nothing
 *   extra here beyond the i,l,r distinctness of positions.
 *
 * Complexity
 *   Time  O(n^2): O(n log n) sort plus n times an O(n) two-pointer
 *   scan. Brute force is O(n^3).
 *   Extra space O(1) besides the sort. std::sort on a vector is
 *   in-place (introsort / pattern-defeating sort) with O(log n)
 *   stack for recursion, which we still call O(1) extra relative to
 *   the input in casual speech, or O(log n) if we are precise about
 *   sort's stack. We mutate the caller's array by sorting it.
 *
 * Memory management
 *   std::vector<int>& because we sort in place. If the caller needed
 *   the original order, we would copy first: that copy is O(n) heap.
 *   This function treats the buffer as scratch. Document that.
 *
 *   No hash set. A hash set of complements is the unsorted two-sum
 *   approach and would be O(n) extra heap per i, worse constants, and
 *   worse locality.
 *
 * C theory — sort, overflow of three ints, pointers, cache, UB
 *   Three ints can overflow int: INT_MAX + INT_MAX + INT_MAX does not
 *   fit in 32 bits. The expression a + b + c is left-associative and
 *   all int, so the first addition may already be UB. Accumulate in
 *   long long:
 *     1LL * nums[i] + nums[l] + nums[r]
 *   which is ((1LL * nums[i]) + nums[l]) + nums[r]. Safe.
 *
 *   std::sort needs random-access iterators. vector provides them.
 *   It moves ints by assignment. For int that is copies of machine
 *   words. The comparator must be a strict weak ordering; default
 *   operator< on int is that.
 *
 *   After sort, the two-pointer argument from TwoSumSorted applies
 *   on the suffix: the suffix is still sorted.
 *
 *   Cache: sort is the heavy, less sequential part (it jumps). The
 *   n two-pointer scans are sequential on a hot array. For moderate
 *   n the quadratic scans dominate time and they are cache-friendly.
 *
 *   Bounds: l and r stay inside (i, n) with l < r. i runs only while
 *   at least two cells remain to the right: i + 2 < n, written
 *   i + 2 < nums.size() to avoid unsigned underflow.
 *
 *   Empty / n < 3: return false. No n-1 wrap.
 *
 *   In-place mutation: the sorted permutation replaces the input.
 *   The boolean does not need the original order after the sort.
 */

#include <algorithm>
#include <iostream>
#include <vector>

bool find3Numbers(std::vector<int>& arr, int sum) {
    if (arr.size() < 3) {
        return false;
    }
    std::sort(arr.begin(), arr.end());
    const long long need = sum;
    for (std::size_t i = 0; i + 2 < arr.size(); ++i) {
        std::size_t l = i + 1;
        std::size_t r = arr.size() - 1;
        while (l < r) {
            const long long cur = 1LL * arr[i] + arr[l] + arr[r];
            if (cur == need) {
                return true;
            }
            if (cur < need) {
                ++l;
            } else {
                --r;
            }
        }
    }
    return false;
}

int main() {
    std::vector<int> arr{1, 4, 45, 6, 10, 8};
    std::cout << std::boolalpha << find3Numbers(arr, 22) << '\n';
    return 0;
}
