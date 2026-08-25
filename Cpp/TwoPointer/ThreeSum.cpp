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
 *   Extra space O(1) besides the sort. sort(nums, nums+n) is in-place
 *   (introsort) with O(log n) stack for recursion, which we still call
 *   O(1) extra relative to the input in casual speech, or O(log n) if
 *   we are precise about sort's stack. We mutate the caller's array by
 *   sorting it.
 *
 * Memory management
 *   int arr[] decays to a pointer. We sort in place with sort(arr, arr+n).
 *   If the caller needed the original order, we would copy first: that
 *   copy is O(n) extra. This function treats the buffer as scratch.
 *   Document that. We avoid vector on purpose.
 *
 *   No hash set. A hash set of complements is the unsorted two-sum
 *   approach and would be O(n) extra memory per i, worse constants, and
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
 *   sort needs random-access iterators. A C array decays to a pointer,
 *   and pointers into an array are random-access. sort(arr, arr+n)
 *   sorts the n ints in place. For int that is copies of machine words.
 *
 *   After sort, the two-pointer argument from TwoSumSorted applies
 *   on the suffix: the suffix is still sorted.
 *
 *   Cache: sort is the heavy, less sequential part (it jumps). The
 *   n two-pointer scans are sequential on a hot array. For moderate
 *   n the quadratic scans dominate time and they are cache-friendly.
 *
 *   Bounds: l and r stay inside (i, n) with l < r. i runs only while
 *   at least two cells remain to the right: i + 2 < n.
 *
 *   Empty / n < 3: return false. No n-1 on a too-short array.
 *
 *   In-place mutation: the sorted permutation replaces the input.
 *   The boolean does not need the original order after the sort.
 */

#include <algorithm>
#include <iostream>
using namespace std;

bool find3Numbers(int arr[], int n, int sum) {
    if (n < 3) {
        return false;
    }
    sort(arr, arr + n);
    long long need = sum;
    for (int i = 0; i + 2 < n; i++) {
        int l = i + 1;
        int r = n - 1;
        while (l < r) {
            long long cur = 1LL * arr[i] + arr[l] + arr[r];
            if (cur == need) {
                return true;
            }
            if (cur < need) {
                l++;
            } else {
                r--;
            }
        }
    }
    return false;
}

int main() {
    int arr[] = {1, 4, 45, 6, 10, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    if (find3Numbers(arr, n, 22)) {
        cout << "true\n";
    } else {
        cout << "false\n";
    }
    return 0;
}
