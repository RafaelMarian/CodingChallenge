/*
 * LESSON — Fixed-length sliding window: amortized O(n), two indices
 *
 * Student, the problem is: given an array and a length k, return the
 * maximum sum of any contiguous subarray of exactly k elements.
 *
 * Intuition
 *   The window of length k that starts at index i is nums[i .. i+k-1].
 *   The next window, starting at i+1, is almost the same array: it has
 *   lost nums[i] on the left and gained nums[i+k] on the right.
 *
 *       sum(i+1) = sum(i) - nums[i] + nums[i+k]
 *
 *   Seed the first window with a O(k) scan. Then slide: one subtract,
 *   one add, one compare, until the right edge hits the end. You never
 *   rescan the k-1 shared elements.
 *
 *   The window is two indices. Call the left edge i (the element about
 *   to leave) and the right edge j (the element about to enter). The
 *   invariant is j - i + 1 == k after the seed, and every slide does
 *   i++, j++ together. Two pointers, one lockstep.
 *
 * Complexity
 *   Seed: O(k). Slide: O(n - k) steps, O(1) work each. Total O(n).
 *   That is amortized O(1) per element: each index enters the window
 *   once and leaves the window once. Naive "for each start, sum k
 *   elements" is O(n k). Same answer, wasted arithmetic.
 *   Extra memory: O(1). The window is indices, not a copy of the slice.
 *
 * Memory management
 *   const std::vector<int>& nums: we do not copy the buffer. sum and
 *   max live in registers or the stack frame. No heap allocation in
 *   the function. The CPU sees a single contiguous stream of ints.
 *
 * C theory — why the slide is cache-friendly, and where overflow hides
 *   nums is a contiguous heap buffer. The seed pass reads nums[0..k).
 *   Each slide reads two ints that are k apart: nums[i] and nums[j].
 *   Sequential i and j walk forward, so both streams prefetch. The
 *   distance k means they may sit in different cache lines; that is
 *   still two sequential streams, not random pointer chasing.
 *
 *   sum += nums[j] is a signed add. A window of large ints can overflow
 *   int. Signed overflow is undefined behavior. If the true window sums
 *   may leave 32-bit range, accumulate in long long. The sample does
 *   not, so int matches the original arithmetic.
 *
 *   Bounds: the seed loop must not run past n. If k > n the problem is
 *   ill-posed; if k == 0 you must not index nums[0] from an empty
 *   window. Out-of-bounds is UB — C will not throw. The sample has
 *   n = 10, k = 3.
 *
 *   In C the same algorithm is:
 *       int max_window(const int *a, int n, int k);
 *   Two pointers into one array. a[i] is *(a + i). No container, no
 *   iterator: just indices and a length.
 *
 *   Branch: if (sum > max) is a data-dependent branch. For random data
 *   it mispredicts often; for monotonic windows it is stable. On tiny
 *   n a recompute of each window can beat a clever slide because the
 *   whole array is already in L1. Measure when n is small; reason when
 *   n is large.
 *
 * Sample: {1,2,0,4,3,6,2,1,9,-1}, k = 3. Windows 3,6,7,13,11,9,12,9.
 * The maximum is 13.
 */

#include <iostream>
#include <vector>

int maxSubArray(const std::vector<int>& nums, int k) {
    int sum = 0;
    for (int j = 0; j < k; ++j) {
        sum += nums[j];
    }
    int max = sum;
    int i = 0;
    int j = k - 1;
    while (j + 1 < static_cast<int>(nums.size())) {
        sum -= nums[i];
        ++i;
        ++j;
        sum += nums[j];
        if (sum > max) {
            max = sum;
        }
    }
    return max;
}

int main() {
    const std::vector<int> nums{1, 2, 0, 4, 3, 6, 2, 1, 9, -1};
    std::cout << maxSubArray(nums, 3) << '\n';
    return 0;
}
