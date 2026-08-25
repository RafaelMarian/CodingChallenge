/*
 * LESSON — All unique quadruplets that sum to a target
 *
 * Student, four-sum is two nested loops plus the sorted two-pointer
 * pair. The new work is skipping duplicates so each quadruplet of
 * values appears once, and adding four ints without overflowing.
 *
 * Problem
 *   Return every unique non-decreasing quadruplet (a,b,c,d) of values
 *   from the array (distinct indices) that sum to target. Sample:
 *   {0,1,0,2,1,2,2}, target 3, prints the single line 0 0 1 2.
 *
 * Algorithm intuition
 *   Sort. Fix i, then j > i. On the remaining suffix, two pointers
 *   l = j+1, h = n-1 search for target - nums[i] - nums[j]. On a hit,
 *   record the four values, step both pointers, and skip equal values
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
 *   Extra space O(1) besides the output. The output can be O(n^3)
 *   quadruplets in the worst case; that memory is required by the
 *   answer, not by the algorithm's working set. Sort is in-place.
 *
 * Memory management
 *   We take std::vector<int> by value or we sort a local copy. The
 *   function below takes a mutable reference and sorts it, matching
 *   the "scratch the input" pattern of three-sum. The result is
 *   std::vector<std::vector<int>>: a heap vector of small heap
 *   vectors of four ints. Each inner vector is a separate allocation
 *   (small-object optimization does not apply to vector). If you
 *   emitted millions of quadruplets, that allocator traffic would
 *   dominate. For the sample there is one inner vector of four ints.
 *
 *   Push a quadruplet with res.push_back({a,b,c,d}). That constructs
 *   a temporary vector of four, which allocates, then moves into res.
 *
 *   In C you would realloc an array of struct {int a,b,c,d;}, one
 *   allocation, better locality. C++ vector-of-vector is the clear
 *   teaching type, not the fastest packing.
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
 *   Compare to target as long long: static_cast<long long>(target)
 *   or 0LL + target.
 *
 *   Duplicate skip uses l > 0 logically by comparing nums[l] to
 *   nums[l-1] only when l has just been incremented and l < h.
 *   Reading nums[l-1] is in range then. Off-by-one here either
 *   skips a valid quadruplet or emits duplicates. Trace the sample
 *   on paper: sorted 0,0,1,1,2,2,2.
 *
 *   i runs while i+3 < n so four cells exist. Write i + 3 < size()
 *   with size_t. j + 2 < size() similarly.
 *
 *   Cache: after sort, the inner two-pointer walks are sequential.
 *   The outer loops jump j around; still the same array, likely hot.
 *   The result writes are small allocations; they miss relative to
 *   the scan, which is fine at this size.
 *
 *   std::sort mutates. Original index identity is destroyed. We
 *   return values, not indices.
 *
 *   Empty / n < 4: return an empty list. No wrap of n-1.
 */

#include <algorithm>
#include <iostream>
#include <vector>

std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target) {
    std::vector<std::vector<int>> res;
    const std::size_t n = nums.size();
    if (n < 4) {
        return res;
    }
    std::sort(nums.begin(), nums.end());
    const long long need = target;
    for (std::size_t i = 0; i + 3 < n; ++i) {
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }
        for (std::size_t j = i + 1; j + 2 < n; ++j) {
            if (j > i + 1 && nums[j] == nums[j - 1]) {
                continue;
            }
            std::size_t l = j + 1;
            std::size_t h = n - 1;
            while (l < h) {
                const long long sum =
                    1LL * nums[i] + nums[j] + nums[l] + nums[h];
                if (sum == need) {
                    res.push_back({nums[i], nums[j], nums[l], nums[h]});
                    ++l;
                    --h;
                    while (l < h && nums[l] == nums[l - 1]) {
                        ++l;
                    }
                    while (l < h && nums[h] == nums[h + 1]) {
                        --h;
                    }
                } else if (sum < need) {
                    ++l;
                } else {
                    --h;
                }
            }
        }
    }
    return res;
}

int main() {
    std::vector<int> arr{0, 1, 0, 2, 1, 2, 2};
    const std::vector<std::vector<int>> ans = fourSum(arr, 3);
    for (const std::vector<int>& quad : ans) {
        for (std::size_t i = 0; i < quad.size(); ++i) {
            if (i != 0) {
                std::cout << ' ';
            }
            std::cout << quad[i];
        }
        std::cout << '\n';
    }
    return 0;
}
