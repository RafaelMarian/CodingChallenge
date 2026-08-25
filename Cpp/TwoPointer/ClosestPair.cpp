/*
 * LESSON — k closest elements to x in a sorted array
 *
 * Student, "closest k" sounds like a heap of size k. When the array is
 * already sorted, a heap is extra machinery. The k closest form a
 * contiguous window, and you can find that window by shrinking from
 * the ends.
 *
 * Problem
 *   arr is sorted non-decreasing. Print the k elements closest to x,
 *   in their original (sorted) order. Sample: arr =
 *   {1,3,5,7,9,11,13,15}, k = 3, x = 7, answer 5 7 9.
 *
 * Algorithm intuition
 *   The answer is some subarray arr[l..r] of length k. Start with the
 *   full range l = 0, r = n-1. While the window is longer than k,
 *   discard the end that is farther from x. Compare |arr[l] - x| and
 *   |arr[r] - x|. If the left is strictly farther, l++; otherwise r--
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
 *   Extra space O(1) if you print arr[l..r] directly. Filling a second
 *   array of k ints is optional.
 *
 * Memory management
 *   int arr[] decays to a pointer; pass n. We avoid vector on purpose.
 *   We do not copy the n-array. After the window is k long we print
 *   those cells. If you only needed to print, you allocate nothing.
 *
 * C theory — abs of differences, overflow, windows, cache
 *   |a - x| for int a, x is not abs(a - x) in general. If a is
 *   INT_MIN and x is 1, a - x overflows before abs. Signed overflow
 *   is UB. Compare in long long:
 *     long long d = 1LL * arr[l] - x;
 *     if (d < 0) d = -d;
 *   1LL * arr[l] - x promotes before subtracting. The range is about
 *   +/- 2^32, which fits in long long. Negating that is defined.
 *   abs(INT_MIN) on 32-bit int remains UB; we never call that.
 *
 *   Window length: r - l + 1 > k. With int indices, r >= l is
 *   maintained so the subtraction is non-negative. Equivalent test:
 *   r - l >= k, which is (r - l + 1) > k.
 *
 *   Empty or k <= 0: print nothing. k > n: the problem usually
 *   guarantees k <= n. We shrink only while r - l + 1 > k and the
 *   range is valid.
 *
 *   Cache: you only load the two ends until the window is small, then
 *   you stream k consecutive ints. Very local.
 *
 *   No in-place mutation of arr. The window is a view of the input.
 *
 *   Binary-search alternatives find the left edge of the window in
 *   O(log n) comparisons; learn this linear shrink first. It is
 *   obviously correct and has no subtle midpoint overflow.
 */

#include <iostream>
using namespace std;

void findClosestElements(int arr[], int n, int k, int x) {
    if (n == 0 || k <= 0) {
        return;
    }
    int l = 0;
    int r = n - 1;
    while (r - l + 1 > k) {
        long long dleft = 1LL * arr[l] - x;
        if (dleft < 0) {
            dleft = -dleft;
        }
        long long dright = 1LL * arr[r] - x;
        if (dright < 0) {
            dright = -dright;
        }
        if (dleft > dright) {
            l++;
        } else {
            r--;
        }
    }
    for (int i = l; i <= r; i++) {
        if (i != l) {
            cout << ' ';
        }
        cout << arr[i];
    }
    cout << '\n';
}

int main() {
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    findClosestElements(arr, n, 3, 7);
    return 0;
}
