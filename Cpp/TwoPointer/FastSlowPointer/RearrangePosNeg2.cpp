/*
 * LESSON — Negatives first, with more of the original relative order
 *
 * Student, Hoare partition from both ends is O(n) and destroys order.
 * This lesson uses a slow/fast pair that both run forward. It keeps the
 * relative order of the negatives. It does not keep the relative order
 * of the positives. It can do quadratic work. You should know it exists
 * so you can refuse it.
 *
 * Problem
 *   Move every negative before every positive. Prefer preserving the
 *   order of negatives. In-place with swaps. The sample is
 *   {-2, 6, 3, -4, 1, 10, -5, 8, -7, -9}.
 *
 * Algorithm intuition
 *   Slow index i finds the leftmost value that is not negative (the
 *   first positive sitting in the way). Fast index j then starts just
 *   after i and finds the next negative. Swap them. That negative has
 *   jumped left into the first hole. Repeat. Negatives encountered
 *   later still swap into later holes, so negatives keep their order.
 *   Each swap dumps a positive into the slot the negative came from,
 *   which may be far to the right, so positives are permuted.
 *
 *   After enough swaps the prefix is all negatives in original order
 *   and the suffix is the leftover positives in some order.
 *
 *   This is not a stable partition of both classes. A stable partition
 *   that keeps both orders needs extra memory (a buffer of n, or a
 *   list) or a more sophisticated in-place rotation algorithm.
 *
 * Complexity
 *   Time  O(n^2) worst case. Each swap moves one negative into place,
 *   but i and j restart their scans from the current hole. If negatives
 *   and positives strictly alternate, you walk long stretches repeatedly.
 *   Extra space O(1).
 *
 *   Contrast: Hoare sign-partition is O(n) time, O(1) space, not stable.
 *   Buffer method: one pass into a new array, O(n) time, O(n) space,
 *   stable for both sides if you push negatives first in order then
 *   positives in order.
 *
 * Memory management
 *   int arr[] decays to a pointer; n is the length. In-place swaps in
 *   the caller's buffer. No second allocation. We avoid vector on
 *   purpose. That is the only virtue of this quadratic scan. The extra
 *   memory you refused is often cheaper than the extra time you accepted.
 *   Measure before you keep an O(n^2) in-place method on large n.
 *
 * C theory — slow/fast, swap, cache, why quadratic
 *   Two indices that both increase is the "slow and fast" pattern you
 *   will also see in cycle detection, but here they are not a cycle.
 *   Slow marks a hole (a positive in the negative prefix). Fast hunts
 *   the next occupant for that hole (a negative). After the swap, the
 *   hole has moved: the positive is now at j, and i may still point at
 *   a positive (the next one), so the outer loop continues.
 *
 *   Each inner while is a linear scan. Nested linear scans over the
 *   same array, restarting, is the classic O(n^2) cache-friendly but
 *   still quadratic pattern. Sequential access does not cancel an extra
 *   factor of n. It only makes each of the O(n^2) steps a cheap load.
 *
 *   Swap uses a temporary int. The two indices i and j are distinct
 *   when we swap (j starts at i+1 and only swaps when both are in
 *   range and a negative was found). No XOR.
 *
 *   Bounds: every while checks i < n and j < n before dereferencing.
 *   That is the difference between a defined program and a buffer
 *   overflow. AddressSanitizer will catch the latter; do not rely on
 *   it as a substitute for the checks.
 *
 *   No overflow on values. In-place mutation again means the original
 *   permutation is gone.
 *
 *   You may print i and j before each swap when tracing. The program
 *   below prints only the final array, space-separated.
 */

#include <iostream>
using namespace std;

void rearrange2(int arr[], int n) {
    int i = 0;
    while (i < n) {
        while (i < n && arr[i] < 0) {
            i++;
        }
        int j = i + 1;
        while (j < n && arr[j] > 0) {
            j++;
        }
        if (i < n && j < n) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        } else {
            break;
        }
    }
}

int main() {
    int arr[] = {-2, 6, 3, -4, 1, 10, -5, 8, -7, -9};
    int n = sizeof(arr) / sizeof(arr[0]);
    rearrange2(arr, n);
    for (int i = 0; i < n; i++) {
        if (i != 0) {
            cout << ' ';
        }
        cout << arr[i];
    }
    cout << '\n';
    return 0;
}
