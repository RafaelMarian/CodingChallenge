/*
 * LESSON — Partition negatives to the left, positives to the right
 *
 * Student, this is Hoare's partition idea applied to sign. It is not a
 * stable sort. Relative order inside each side is not preserved. If you
 * need order, this is the wrong algorithm; see RearrangePosNeg2 and then
 * a true stable partition.
 *
 * Problem
 *   Given an array of nonzero integers, rearrange so every negative value
 *   occupies some prefix and every positive value occupies the remaining
 *   suffix. In-place. Order within a side does not matter.
 *
 * Algorithm intuition
 *   i starts at 0 and advances while the cell is already negative (it
 *   belongs on the left). j starts at n-1 and retreats while the cell is
 *   already positive (it belongs on the right). When both stop, nums[i]
 *   is a positive on the left side of the unpartitioned region and
 *   nums[j] is a negative on the right side. Swap them. Repeat until
 *   i >= j. The two pointers have crossed, so the whole array is
 *   partitioned.
 *
 *   This is the Hoare scheme: grow a "good left" from the left, a "good
 *   right" from the right, and exchange misplaced pairs. Quicksort's
 *   original partition is the same skeleton with a pivot comparison
 *   instead of a sign test.
 *
 * Complexity
 *   Time  O(n): each index is scanned at most a constant number of times.
 *   Extra space O(1): two indices and a temporary for the swap.
 *
 * Memory management
 *   int nums[] decays to a pointer. In-place stores, no second array.
 *   The caller's n ints are reused. Stack: i, j, temp. The swap's
 *   temporary is one int; it is not an array. We avoid vector on purpose.
 *
 *   You could allocate two arrays, copy negatives then positives, and
 *   copy back. That is O(n) extra memory and two passes. The two-pointer
 *   partition does the job with a handful of words.
 *
 * C theory — Hoare pointers, zeros, overflow, UB, cache
 *   The inner loops need the guard i < j (or i < n, j >= 0). Without it,
 *   i can run off the right end looking for a positive that does not
 *   exist (all remaining cells negative). Reading nums[i] with i == n is
 *   undefined behavior. The same on the left for j.
 *
 *   Zero: this sample has no zeros. A strict < 0 / > 0 test treats 0 as
 *   "not negative" and "not positive," so both inner loops stop on zero.
 *   The algorithm would then swap zeros around without a defined side.
 *   Decide a policy (zeros with positives, or a three-way partition)
 *   before you ship this. Dutch-national-flag is the three-way version.
 *
 *   Swap by temporary, not XOR. Two indices can alias if you swapped
 *   without i < j; we only swap when i < j, so the cells are distinct,
 *   but XOR is still the wrong habit.
 *
 *   No arithmetic on the element values except the sign test. No overflow.
 *   The values are copied bitwise.
 *
 *   Cache: two streams from the ends, like reverse. Swaps write two
 *   hot lines. After a swap, i and j continue, so the next inner-loop
 *   loads are the next sequential cells. Good locality.
 *
 *   In-place mutation discards the original order. If the caller still
 *   needs it, they must copy first. Document that.
 *
 *   C form:
 *     void partition_sign(int a[], int n);
 *   Empty array: return before n-1.
 */

#include <iostream>
using namespace std;

void rearrange(int arr[], int n) {
    if (n < 2) {
        return;
    }
    int i = 0;
    int j = n - 1;
    while (i < j) {
        while (i < j && arr[i] < 0) {
            i++;
        }
        while (i < j && arr[j] > 0) {
            j--;
        }
        if (i < j) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
}

int main() {
    int arr[] = {-2, 6, 3, -4, 1, 10, -5, 8, -7, -6};
    int n = sizeof(arr) / sizeof(arr[0]);
    rearrange(arr, n);
    for (int i = 0; i < n; i++) {
        if (i != 0) {
            cout << ' ';
        }
        cout << arr[i];
    }
    cout << '\n';
    return 0;
}
