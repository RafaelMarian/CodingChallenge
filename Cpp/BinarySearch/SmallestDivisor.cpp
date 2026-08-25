/*
 * LESSON — Binary search on the answer: smallest divisor
 *
 * Student, given positive nums and a threshold, find the smallest
 * positive integer d such that the sum of ceil(nums[i] / d) over i
 * is <= threshold. Sample {1,3,6,11}, threshold 7. The answer is 4:
 *   d=3 -> ceil(1/3)+ceil(3/3)+ceil(6/3)+ceil(11/3) = 1+1+2+4 = 8 > 7
 *   d=4 -> 1+1+2+3 = 7 <= 7
 *
 * Intuition
 *   The feasible region is monotone in d. Larger d makes every
 *   ceil(nums[i]/d) smaller or equal, so the sum never increases.
 *   There is a smallest d that works, and every d above it also
 *   works. Binary search that cut on the number line of possible
 *   divisors: 1 .. max(nums) (because d >= max(nums) gives a sum of
 *   n, and if even that exceeds threshold the problem is impossible;
 *   the sample is possible).
 *
 *   You are not searching inside nums. You are searching the answer
 *   itself. The array is only used to evaluate the predicate
 *   "does this candidate d meet the threshold?"
 *
 * Integer ceil without floating point
 *   ceil(a / d) for positive a, d is (a + d - 1) / d in integer
 *   division. Alternatively (a - 1) / d + 1, which avoids adding
 *   a + d - 1 (that add can overflow int). We use the (a + d - 1) / d
 *   form on this small sample and mention the overflow in the theory.
 *
 * Complexity
 *   Search range is 1..U with U = max(nums), O(log U) candidate
 *   tests. Each test is O(n). Total O(n log U). Extra memory O(1).
 *
 * Memory management
 *   const std::vector<int>&. Locals only. No extra buffer. The
 *   "search space" is integers in registers, not an allocated table
 *   of divisors.
 *
 * C theory — monotone predicates, integer division, overflow, cache
 *   Binary search works on any monotone predicate over a totally
 *   ordered domain, not only on sorted arrays. The domain here is
 *   {1,2,...,U}. Random access is "plug d into the sum," which is
 *   O(n) work, not O(1). The log factor still applies to U.
 *
 *   Integer division truncates toward zero. For positives that is
 *   floor. The + (d-1) bump turns it into ceil. Never write
 *   (int)ceil((double)a / d) for this: floating point cannot
 *   represent every integer, and you would import rounding bugs.
 *
 *   (a + d - 1) can overflow int before the divide. Signed overflow
 *   is UB. Safe form for a >= 1, d >= 1: 1 + (a - 1) / d. For this
 *   sample a and d are tiny. Production code uses the safe form or
 *   long long.
 *
 *   The inner sum += also overflows if n is huge and d is 1. long
 *   long for the accumulator is the habit. Sample fits in int.
 *
 *   Cache: each predicate evaluation is a sequential scan of nums,
 *   excellent locality, done log U times. Fine.
 *
 *   mid = l + (h - l) / 2. Loop while l < h, set h = m on success
 *   (include m: it might be the smallest), l = m + 1 on failure.
 *   Return l. That is lower_bound on the predicate.
 *
 *   C: int smallest(const int *a, int n, int threshold); same two
 *   loops.
 *
 * Sample prints 4.
 */

#include <climits>
#include <iostream>
#include <vector>

int smallestDivisor(const std::vector<int>& nums, int threshold) {
    int max = INT_MIN;
    for (int x : nums) {
        if (x > max) {
            max = x;
        }
    }
    int l = 1;
    int h = max;
    while (l < h) {
        const int m = l + (h - l) / 2;
        int sum = 0;
        for (int data : nums) {
            sum += (data + m - 1) / m;
        }
        if (sum <= threshold) {
            h = m;
        } else {
            l = m + 1;
        }
    }
    return l;
}

int main() {
    const std::vector<int> nums{1, 3, 6, 11};
    std::cout << smallestDivisor(nums, 7) << '\n';
    return 0;
}
