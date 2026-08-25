/*
 * LESSON — All unique quadruplets that sum to a target
 *
 * Student, four-sum is two nested loops plus the sorted two-pointer
 * pair. The new work is skipping duplicates so each quadruplet of
 * values appears once, and adding four ints without overflowing.
 *
 * Problem
 *   Print every unique non-decreasing quadruplet (a,b,c,d) of values
 *   from the array (distinct indices) that sum to target. Sample:
 *   {0,1,0,2,1,2,2}, target 3, prints the single line 0 0 1 2.
 *
 * Algorithm intuition
 *   Sort. Fix i, then j > i. On the remaining suffix, two pointers
 *   l = j+1, h = n-1 search for target - nums[i] - nums[j]. On a hit,
 *   print the four values, step both pointers, and skip equal values
 *   so you do not emit the same quadruplet again. On a miss, move l
 *   or h by the usual sum test.
 *
 *   Skip duplicate i: if i > 0 and nums[i] == nums[i-1], continue.
 *   Skip duplicate j: if j > i+1 and nums[j] == nums[j-1], continue.
 *   After a hit, skip duplicate l and h similarly. Sorting made
 *   duplicates adjacent; skipping them is O(1) amortized per step.
 *
 * Complexity
 *   Time  O(n^3): two nested index loops and an O(n) two-pointer scan.
 *   Extra space O(1) besides the printed output. We do not store a
 *   table of quadruplets. Sort is in-place.
 *
 * Memory management
 *   int nums[] decays to a pointer. We sort it with sort(nums, nums+n)
 *   and print each hit as we find it. No nested arrays of answers.
 *   We avoid vector on purpose: collecting vector-of-vector would be
 *   a heap allocation per quadruplet. Printing streams four ints and
 *   keeps working memory to a handful of indices.
 *
 * C theory — long long accumulation, skip, overflow, UB, cache
 *   Four int addends: 4 * INT_MAX does not fit in 32-bit signed.
 *   Build the sum as long long, left-associative from a 1LL term:
 *     1LL * nums[i] + nums[j] + nums[l] + nums[h]
 *   Do not write nums[i] + nums[j] + nums[l] + nums[h] and then
 *   assign to long long; the additions happen in int first, which
 *   is UB on overflow. Do not write 1LL * a + b + c + d as
 *   1LL * (a + b + c + d) either; the parentheses force int adds.
 *
 *   Compare to target as long long: (long long)target or 0LL + target.
 *
 *   Duplicate skip uses l > 0 logically by comparing nums[l] to
 *   nums[l-1] only when l has just been incremented and l < h.
 *   Reading nums[l-1] is in range then. Off-by-one here either
 *   skips a valid quadruplet or emits duplicates. Trace the sample
 *   on paper: sorted 0,0,1,1,2,2,2.
 *
 *   i runs while i+3 < n so four cells exist. j + 2 < n similarly.
 *
 *   Cache: after sort, the inner two-pointer walks are sequential.
 *   The outer loops jump j around; still the same array, likely hot.
 *
 *   sort mutates. Original index identity is destroyed. We print
 *   values, not indices.
 *
 *   Empty / n < 4: print nothing. No wrap of n-1.
 */

#include <algorithm>
#include <iostream>
using namespace std;

void fourSum(int nums[], int n, int target) {
    if (n < 4) {
        return;
    }
    sort(nums, nums + n);
    long long need = target;
    for (int i = 0; i + 3 < n; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }
        for (int j = i + 1; j + 2 < n; j++) {
            if (j > i + 1 && nums[j] == nums[j - 1]) {
                continue;
            }
            int l = j + 1;
            int h = n - 1;
            while (l < h) {
                long long sum = 1LL * nums[i] + nums[j] + nums[l] + nums[h];
                if (sum == need) {
                    cout << nums[i] << ' ' << nums[j] << ' ' << nums[l] << ' '
                         << nums[h] << '\n';
                    l++;
                    h--;
                    while (l < h && nums[l] == nums[l - 1]) {
                        l++;
                    }
                    while (l < h && nums[h] == nums[h + 1]) {
                        h--;
                    }
                } else if (sum < need) {
                    l++;
                } else {
                    h--;
                }
            }
        }
    }
}

int main() {
    int nums[] = {0, 1, 0, 2, 1, 2, 2};
    int n = sizeof(nums) / sizeof(nums[0]);
    fourSum(nums, n, 3);
    return 0;
}
