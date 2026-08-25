/*
 * LESSON — Next greater to the right: a monotonic decreasing stack
 *
 * Student, for each index i, find the nearest value to the right of i
 * that is strictly greater than nums[i]. If none exists, write -1.
 *
 * Intuition
 *   Scan right to left. Maintain a stack of values that are still
 *   candidates for someone to their left. Keep that stack strictly
 *   decreasing from bottom to top (the top is the nearest, smallest
 *   remaining candidate).
 *
 *   At index i:
 *     1. Pop while the top is smaller than or equal to nums[i].
 *        Those values can never be the next greater for i, and they
 *        can never be the next greater for anyone further left either:
 *        nums[i] is closer and at least as large, so it dominates them.
 *     2. If the stack is empty, nothing to the right is greater: -1.
 *        Otherwise the top is the nearest greater value.
 *     3. Push nums[i]. It is now the nearest candidate for the left.
 *
 *   We store values, not indices, because the API asks for the next
 *   greater *value*. If you later need the index, push indices instead
 *   and read nums[stk[top]].
 *
 *   Why pop equal values? "Next greater" is strict. An equal is not
 *   greater, and a later left-hand element that wanted something
 *   strictly above nums[i] would not want that equal either.
 *
 * Complexity
 *   Each value is pushed once and popped at most once. The inner
 *   while looks like O(n) per step but is amortized O(1): across the
 *   whole scan there are at most n pushes and n pops. Time O(n).
 *   Extra memory: the stack is O(n) in the worst case (a strictly
 *   decreasing array: nothing ever pops). The answer array is O(n)
 *   as well; that is output, not auxiliary, depending on how you
 *   count.
 *
 * Memory
 *   The stack is a C array plus an index:
 *
 *       int stk[100];
 *       int top = -1;          // empty: nothing at stk[top]
 *       stk[++top] = value;    // push
 *       value = stk[top--];    // pop
 *
 *   100 is a fixed capacity. The sample has 10 elements, so it fits.
 *   Pushing past 99 is a buffer overflow: UB. Production code would
 *   allocate n ints (malloc / new int[n]) so capacity equals length.
 *   nmv[] is the output array, same length as arr, owned by main.
 *   arr decayed to a pointer; n is the length.
 *
 * C theory — LIFO, pointers, cache, empty-stack UB
 *   A stack is last-in, first-out. The "nearest to the right" we have
 *   already seen is the last thing we pushed, so it sits at stk[top].
 *   Pop is O(1): decrement top. No shift of other elements.
 *
 *   Do not confuse this with the CPU call stack. This is an explicit
 *   array we use as a stack. The call stack is the frame of
 *   nextMaxValue; overflowing *that* is a different bug (deep
 *   recursion). Here recursion depth is 1.
 *
 *   Cache: we scan nums right to left (still sequential, prefetch
 *   works in reverse on most CPUs well enough) and touch the tail of
 *   stk. The tail is hot. A linked-list stack would chase heap nodes
 *   and miss.
 *
 *   The values themselves are ints; we do not add them, so overflow
 *   is not the issue. Out-of-bounds on an empty stack is: reading
 *   stk[top] when top == -1 is UB. The guard top >= 0 is the check.
 *   Never skip it.
 *
 * Sample {2,1,3,2,6,3,5,9,1,7} -> 3 3 6 6 9 5 9 -1 7 -1
 */

#include <iostream>
using namespace std;

void nextMaxValue(int arr[], int n, int nmv[]) {
    int stk[100];
    int top = -1;
    for (int i = n - 1; i >= 0; i--) {
        while (top >= 0 && arr[i] >= stk[top]) {
            top--;
        }
        nmv[i] = (top < 0) ? -1 : stk[top];
        top++;
        stk[top] = arr[i];
    }
}

int main() {
    int arr[] = {2, 1, 3, 2, 6, 3, 5, 9, 1, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int nmv[sizeof(arr) / sizeof(arr[0])];
    nextMaxValue(arr, n, nmv);
    for (int i = 0; i < n; i++) {
        cout << nmv[i] << " ";
    }
    cout << "\n";
    return 0;
}
