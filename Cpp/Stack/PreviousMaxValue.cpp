/*
 * LESSON — Previous greater to the left: the same stack, opposite scan
 *
 * Student, for each index i, find the nearest value to the *left* of i
 * that is strictly greater than nums[i]. If none exists, write -1.
 *
 * Intuition
 *   This is next-greater with the time axis reversed. Scan left to
 *   right. The stack holds candidates to the left, still monotonic
 *   decreasing toward the top. At i, pop everything smaller than or
 *   equal to nums[i] (they are hidden by nums[i] from anyone further
 *   right). The new top, if any, is the previous greater. Then push.
 *
 *   Same three steps, opposite direction. If you understood
 *   NextMaxValue.cpp, this file is that argument with "right" and
 *   "left" swapped. Keep both in your hands: many problems (histogram
 *   rectangles, trapping rain, span of stock quotes) need one or both.
 *
 * Complexity
 *   Amortized O(n): each value pushed once, popped at most once.
 *   Extra memory O(n) worst case. Strictly increasing: each new value
 *   is greater, so we pop everything and the stack holds one element.
 *   Worst case is strictly decreasing: nothing is greater than what
 *   is already on the stack, nothing pops, stack grows to n.
 *
 * Memory
 *   Same C-array stack as NextMaxValue:
 *
 *       int stk[100];
 *       int top = -1;
 *
 *   One stack buffer, one output array pmv[]. Input arr is a pointer
 *   plus n. Fixed capacity 100: the sample is 10. Overflowing stk is
 *   UB. Heap version: int *stk = new int[n]; ... delete[] stk;
 *
 * C theory — symmetry, empty-stack UB, cache
 *   The stack is an index into a contiguous buffer. Push is ++top and
 *   a store. Pop is --top. No hidden length; top is the length minus
 *   one. Reading stk[top] when top < 0 is UB: you would index before
 *   the buffer. The ternary (top < 0) ? -1 : stk[top] is the guard.
 *
 *   Scan is left to right: the textbook sequential load. The stack
 *   tail is the hot cache line. Same locality story as next-greater.
 *
 *   Values are compared, not added. Integer overflow is not in play.
 *   What is in play is the signed index i walking 0 .. n-1, which is
 *   safe as long as n fits in int.
 *
 * Sample {7,1,3,2,9,5,6,3,1,2} -> -1 7 7 3 -1 9 9 6 3 3
 */

#include <iostream>
using namespace std;

void previousMaxValue(int arr[], int n, int pmv[]) {
    int stk[100];
    int top = -1;
    for (int i = 0; i < n; i++) {
        while (top >= 0 && arr[i] >= stk[top]) {
            top--;
        }
        pmv[i] = (top < 0) ? -1 : stk[top];
        top++;
        stk[top] = arr[i];
    }
}

int main() {
    int arr[] = {7, 1, 3, 2, 9, 5, 6, 3, 1, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int pmv[sizeof(arr) / sizeof(arr[0])];
    previousMaxValue(arr, n, pmv);
    for (int i = 0; i < n; i++) {
        cout << pmv[i] << " ";
    }
    cout << "\n";
    return 0;
}
