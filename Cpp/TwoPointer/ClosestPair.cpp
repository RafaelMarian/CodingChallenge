/*
 * LESSON — k closest elements to x in a sorted array
 *
 * Student, "closest k" sounds like a heap of size k. When the array is
 * already sorted, a heap is extra machinery. The k closest form a
 * contiguous window, and you can find that window by shrinking from
 * the ends.
 *
 * Problem
 *   arr is sorted non-decreasing. Return the k elements closest to x,
 *   in their original (sorted) order. Sample: arr =
 *   {1,3,5,7,9,11,13,15}, k = 3, x = 7, answer 5 7 9.
 *
 * Algorithm intuition
 *   The answer is some subarray arr[l..r] of length k. Start with the
 *   full range l = 0, r = n-1. While the window is longer than k,
 *   discard the end that is farther from x. Compare |arr[l] - x| and
 *   |arr[r] - x|. If the left is strictly farther, ++l; otherwise --r
 *   (this tie-break keeps the smaller value, which is the usual
 *   convention when distances are equal). When the window length is k,
 *   stop. What remains is the unique closest window under that rule.
 *
 *   Why a contiguous window: in a sorted array, the distance to x is
 *   unimodal enough that the k nearest values occupy consecutive
 *   indices. You would not skip a middle element while keeping both
 *   a far-left and a far-right one.
 *
 *   Greedy shrink is correct because the element you drop is worse
 *   than the one you keep at the other end, so it cannot belong to
 *   any closest-k set (with the documented tie-break).
 *
 * Complexity
 *   Time  O(n - k): each iteration drops one index, and you drop n-k
 *   of them. For k close to n this is cheap; for k = 1 it is a full
 *   scan, which you could replace with binary search plus expansion.
 *   Extra space O(k) only if you copy the window out; the window
 *   itself is a view of the input.
 *
 * Memory management
 *   const std::vector<int>& arr: no copy of the n-vector. We allocate
 *   a result of k ints to return a value the caller owns. That is k
 *   heap cells, not n. If you only needed to print, you could stream
 *   arr[l..r] and allocate nothing.
 *
 *   Returning vector by value transfers ownership of that k-buffer
 *   via move/elision. The input is untouched.
 *
 * C theory — abs of differences, overflow, size_t windows, cache
 *   |a - x| for int a, x is not std::abs(a - x) in general. If a is
 *   INT_MIN and x is 1, a - x overflows before abs. Signed overflow
 *   is UB. Compare in long long:
 *     std::llabs(1LL * arr[l] - x)  or simply compare squared
 *     distances, or compare the two 64-bit differences' magnitudes
 *     without a 32-bit subtract.
 *   1LL * arr[l] - x promotes before subtracting. The range is about
 *   +/- 2^32, which fits in long long. llabs on that is defined.
 *   abs(INT_MIN) on 32-bit int remains UB; we never call that.
 *
 *   Window length: r - l + 1 > k. With size_t, r - l is well-defined
 *   unsigned subtraction as long as r >= l, which we maintain. Write
 *   r - l + 1 > k carefully: +1 on size_t is fine here because
 *   r - l + 1 <= n. Equivalent test used in many codes: r - l >= k,
 *   which is (r - l + 1) > k when all are size_t and r >= l.
 *
 *   Empty or k == 0: return an empty vector. k > n: the problem
 *   usually guarantees k <= n. We clamp by shrinking only while
 *   r - l + 1 > k and the range is valid.
 *
 *   Cache: you only load the two ends until the window is small, then
 *   you copy k consecutive ints. The copy is a sequential memcpy-
 *   shaped loop. Very local.
 *
 *   No in-place mutation of arr. The result is a separate heap buffer.
 *
 *   Binary-search alternatives find the left edge of the window in
 *   O(log n) comparisons; learn this linear shrink first. It is
 *   obviously correct and has no subtle midpoint overflow.
 */

#include <cstdlib>
#include <iostream>
#include <vector>

std::vector<int> findClosestElements(const std::vector<int>& arr, int k, int x) {
    if (arr.empty() || k <= 0) {
        return {};
    }
    std::size_t l = 0;
    std::size_t r = arr.size() - 1;
    const std::size_t need = static_cast<std::size_t>(k);
    while (r - l + 1 > need) {
        const long long dleft = std::llabs(1LL * arr[l] - x);
        const long long dright = std::llabs(1LL * arr[r] - x);
        if (dleft > dright) {
            ++l;
        } else {
            --r;
        }
    }
    return std::vector<int>(arr.begin() + l, arr.begin() + r + 1);
}

int main() {
    const std::vector<int> arr{1, 3, 5, 7, 9, 11, 13, 15};
    const std::vector<int> ans = findClosestElements(arr, 3, 7);
    for (std::size_t i = 0; i < ans.size(); ++i) {
        if (i != 0) {
            std::cout << ' ';
        }
        std::cout << ans[i];
    }
    std::cout << '\n';
    return 0;
}
