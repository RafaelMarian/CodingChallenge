/*
 * LESSON — Left rotate by k using three reversals
 *
 * Student, you already know rotate-by-one: save the head, shift left,
 * put the head at the tail. Doing that k times is O(k n) assignments.
 * Three reversals do the same permutation in O(n) time and O(1) extra
 * memory, using the two-pointer reverse you just wrote.
 *
 * Problem
 *   Left rotate the array by k positions. Index 0 moves to index n-k
 *   (modulo n), and so on. For {1,2,3,4} and k = 5, k modulo 4 is 1,
 *   so the result is {2,3,4,1}.
 *
 * Algorithm intuition
 *   A left rotate by k is: the prefix of length k moves to the end,
 *   the suffix of length n-k moves to the front, both blocks keeping
 *   their internal order.
 *
 *   Identity: reverse(reverse(A) + reverse(B)) = B + A for concatenation.
 *   In an array that is prefix A of length k and suffix B:
 *     reverse A, reverse B, reverse the whole array
 *   yields B then A, which is a left rotate by k.
 *
 *   Walk it on {1,2,3,4}, k = 1:
 *     reverse [0,0]:        {1,2,3,4}
 *     reverse [1,3]:        {1,4,3,2}
 *     reverse [0,3]:        {2,3,4,1}
 *
 *   k %= n so rotating by n, 2n, ... is a no-op, and k = 5 on n = 4
 *   is the same as k = 1. If k is negative in some API, you would
 *   convert to an equivalent left rotate in [0, n). This lesson takes
 *   k >= 0.
 *
 * Complexity
 *   Time  O(n): three linear reversals, each O(n).
 *   Extra space O(1): the reverse temporary. No second buffer.
 *   A new array that writes nums[(i+k)%n] into dst[i] is O(n) extra
 *   memory. The reversal method avoids that allocation.
 *
 * Memory management
 *   int nums[] decays to a pointer. In-place mutation of the caller's
 *   n cells. Reverse writes pairs of existing cells. We avoid vector
 *   on purpose. No resize. Ownership does not change because there is
 *   no owner object: the array is just n ints.
 *
 *   Guard n == 0 before k %= n. Remainder with divisor 0 is undefined
 *   behavior in C and C++ (on integers). An empty array has nothing
 *   to rotate; return.
 *
 * C theory — modulo, reverse bounds, overflow, cache, memmove
 *   k %= n. If k and n are int and n is positive, the result is in
 *   [0, n). Keep both types int so a negative k does not silently
 *   become a huge unsigned remainder.
 *
 *   reverse(0, k-1) on k == 0: do not form k-1. A zero-length rotate
 *   is a no-op; skip the reversals or make reverse a no-op when the
 *   interval is empty. We return early on r == 0.
 *
 *   The two-pointer reverse must not read past the ends. Pass inclusive
 *   indices that are < n. Forming lo + hi as an int midpoint is not
 *   needed here; we only walk inward.
 *
 *   Block rotate by memmove: save the prefix of k ints, shift the suffix
 *   left by k, copy the prefix into the tail. That is also O(n) time
 *   and O(k) extra memory for the saved prefix (or you memmove in
 *   overlapping fashion with a temp of k). Three reversals use O(1)
 *   extra and only swaps. memmove is allowed to overlap; memcpy is
 *   not. If you ever shift with memcpy on overlapping ranges, that is
 *   UB.
 *
 *   Cache: each reverse is two sequential streams. Three of them still
 *   beat k full shifts. The permutation is done with good locality.
 *
 *   Integer overflow: we do not add element values. Indices stay in
 *   range if you reduce k and skip n == 0.
 *
 *   In-place: the original order is replaced by the rotated order in
 *   the same cells.
 */

#include <iostream>
using namespace std;

void reverseRange(int nums[], int i, int j) {
    while (i < j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
        i++;
        j--;
    }
}

void rotateLeft(int nums[], int n, int k) {
    if (n == 0) {
        return;
    }
    int r = k % n;
    if (r == 0) {
        return;
    }
    reverseRange(nums, 0, r - 1);
    reverseRange(nums, r, n - 1);
    reverseRange(nums, 0, n - 1);
}

int main() {
    int nums[] = {1, 2, 3, 4};
    int n = sizeof(nums) / sizeof(nums[0]);
    rotateLeft(nums, n, 5);
    for (int i = 0; i < n; i++) {
        cout << nums[i] << '\n';
    }
    return 0;
}
