/*
 * LESSON — Prefix sums: pay O(n) memory once, answer range sums in O(1)
 *
 * Student, here is the contract. Given nums[0..n), build prefix so that
 *
 *     prefix[0] = nums[0]
 *     prefix[i] = prefix[i-1] + nums[i]     for i = 1 .. n-1
 *
 * After that, the sum of any closed range [L, R] is
 *
 *     prefix[R]                 if L == 0
 *     prefix[R] - prefix[L-1]   if L > 0
 *
 * That subtraction is two loads and an add. No loop. The extra buffer is
 * the price of admission.
 *
 * Intuition
 *   A running total is a cumulative integral of the array. Differences of
 *   a cumulative integral recover interval sums. You have seen this in
 *   discrete math as telescoping: (a0+...+aR) - (a0+...+aL-1) = aL+...+aR.
 *   Draw the array as a row of integers in memory. prefix[i] is the sum of
 *   every cell from the start through i. Once that row exists, a range is
 *   a pair of indices, not a scan.
 *
 * Complexity
 *   Time to build:  O(n). One sequential pass, one add per element.
 *   Time per range: O(1) after the build.
 *   Extra memory:   O(n) integers for the prefix buffer.
 *   Naive range sums without a prefix are O(n) per query. For Q queries
 *   that is O(nQ). The prefix turns it into O(n + Q). That is the trade.
 *
 * Memory management
 *   std::vector<int> prefix(n) asks the allocator for n contiguous ints
 *   on the heap. The vector object itself (pointer, size, capacity) lives
 *   on the stack of prefixSum. The destructor frees the buffer when the
 *   returned-by-value vector is later destroyed in main — or, with NRVO
 *   and moves, there is often no extra copy, just a pointer hand-off.
 *   We take const std::vector<int>& nums so we never copy the input
 *   buffer. One word (the address of the caller's vector) comes in.
 *
 *   The prefix buffer is contiguous. Walking prefix[i], prefix[i+1], ...
 *   streams through cache lines (typically 64 bytes, 16 ints). A linked
 *   structure of partial sums would be the same big-O and a worse machine.
 *
 * C theory — overflow, UB, and why the buffer is an array
 *   prefix[i] = prefix[i-1] + nums[i] is a signed add. Signed overflow is
 *   undefined behavior. If the true sums do not fit in 32-bit int, the
 *   program is meaningless: the compiler may assume overflow never happens
 *   and delete "impossible" branches. For real range-sum work store prefix
 *   as long long (at least 64-bit). Then a range still fits unless the
 *   data is adversarial on the order of 2^63.
 *
 *   prefix[0] = nums[0] is legal only if n > 0. An empty input has no
 *   nums[0]. Accessing it is out-of-bounds: UB. We do not special-case
 *   empty here because the sample is non-empty; you should, in production.
 *
 *   In C this is the same layout:
 *       int *prefix = malloc(n * sizeof *prefix);
 *       prefix[0] = nums[0];
 *       for (size_t i = 1; i < n; ++i) prefix[i] = prefix[i-1] + nums[i];
 *       ...
 *       free(prefix);
 *   a[i] is *(a + i). The compiler scales i by sizeof(int). There is no
 *   hidden length on the pointer; C++'s vector carries that length for you.
 *
 *   Cache: both nums and prefix are sequential. The build pass is two
 *   streams, both hot. This is why prefix arrays are the default first
 *   trick in array problems, not some clever tree.
 *
 * Compile and run. Then compute prefix[5] - prefix[1] by hand and check
 * that it equals nums[2]+nums[3]+nums[4]+nums[5].
 */

#include <iostream>
#include <vector>

std::vector<int> prefixSum(const std::vector<int>& nums) {
    std::vector<int> prefix(nums.size());
    prefix[0] = nums[0];
    for (std::size_t i = 1; i < nums.size(); ++i) {
        prefix[i] = prefix[i - 1] + nums[i];
    }
    return prefix;
}

int main() {
    const std::vector<int> nums{8, 7, 2, 1, 3, 6, 10, 4, 9, 5};
    for (int x : prefixSum(nums)) {
        std::cout << x << '\n';
    }
    return 0;
}
