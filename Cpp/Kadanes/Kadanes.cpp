/*
 * LESSON — Kadane: maximum subarray sum, DP collapsed to two integers
 *
 * Student, given an array of signed ints (negatives allowed), return the
 * largest sum of any contiguous subarray. The array is non-empty.
 *
 * Intuition
 *   A subarray that has gone negative cannot be a useful prefix of a
 *   later answer: appending it would only hurt. So we keep a running
 *   sum, and when that sum drops below zero we throw the prefix away
 *   and start again at the next index.
 *
 *   The exact loop, which you must not reorder:
 *
 *       sum += nums[i];
 *       if (sum > maxSum) maxSum = sum;
 *       if (sum < 0)      sum    = 0;
 *
 *   Update the champion BEFORE the reset. That is not a stylistic
 *   choice. It is how all-negative arrays stay correct.
 *
 * Trace of the sample {-2, 1, -3, 4, -1, 2, 1, -5, 4, -1}
 *   sum starts 0, maxSum starts INT_MIN.
 *   -2: sum=-2, maxSum=-2, reset sum=0
 *    1: sum= 1, maxSum= 1
 *   -3: sum=-2, maxSum= 1, reset
 *    4: sum= 4, maxSum= 4
 *   -1: sum= 3, maxSum= 4
 *    2: sum= 5, maxSum= 5
 *    1: sum= 6, maxSum= 6
 *   -5: sum= 1, maxSum= 6
 *    4: sum= 5, maxSum= 6
 *   -1: sum= 4, maxSum= 6
 *   Answer 6, from the slice [4, -1, 2, 1].
 *
 * All-negative arrays, traced
 *   Take {-5, -2, -8}. First element: sum becomes -5, maxSum becomes -5,
 *   then reset. Second: sum becomes -2, maxSum becomes -2, reset. Third:
 *   sum becomes -8, maxSum stays -2. The algorithm recorded each negative
 *   as a candidate *before* wiping the sum. The answer is the largest
 *   element, which is the correct maximum subarray when every slice is
 *   negative. If you reset first, you would never record those values
 *   and maxSum would stay INT_MIN — a lie.
 *
 * Complexity
 *   Time O(n), one pass. Extra memory O(1): two ints. The naive
 *   O(n^2) "every pair of endpoints" is the same problem with a table
 *   you do not need.
 *
 * Memory
 *   int nums[], int n: no copy. sum and maxSum are automatic storage
 *   (stack / registers). Nothing is allocated. The input buffer is a
 *   contiguous array owned by the caller. Decay: nums is int*; n is
 *   the length computed in main with sizeof.
 *
 * C theory — DP, INT_MIN, overflow, sequential access
 *   The recurrence is
 *       best_ending_here[i] = nums[i] + max(best_ending_here[i-1], 0)
 *       answer[i]           = max(answer[i-1], best_ending_here[i])
 *   When a recurrence only needs the previous cell, collapse the table
 *   to a scalar. That is how O(n) extra memory becomes O(1). The array
 *   best_ending_here never exists except as the variable sum.
 *
 *   maxSum is initialized to INT_MIN (the smallest 32-bit two's
 *   complement value, -2^31, from <climits>). That is a sentinel
 *   meaning "no candidate yet." It is a valid int, so an empty array
 *   would be indistinguishable from "the max really is INT_MIN." We
 *   require a non-empty input.
 *
 *   sum += nums[i] can overflow int. Signed overflow is UB. Kadane on
 *   32-bit data whose partial sums leave [-2^31, 2^31) must use
 *   long long for sum and maxSum. Unary minus of INT_MIN is also UB
 *   (it cannot be represented); we never negate maxSum here.
 *
 *   The scan is sequential: one load per element, perfect prefetch,
 *   one cache line at a time. There is no random index and no extra
 *   buffer to pollute L1.
 */

#include <climits>
#include <iostream>
using namespace std;

int maxSubArray(int nums[], int n) {
    int maxSum = INT_MIN;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += nums[i];
        if (sum > maxSum) {
            maxSum = sum;
        }
        if (sum < 0) {
            sum = 0;
        }
    }
    return maxSum;
}

int main() {
    int nums[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4, -1};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << maxSubArray(nums, n) << "\n";
    return 0;
}
