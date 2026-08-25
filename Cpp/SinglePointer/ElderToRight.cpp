/*
 * LESSON — Leaders from the right, and why insert-at-front is a trap
 *
 * Problem
 *   A right-leader is greater than everything to its *right*. Scan from
 *   the end, keep a running max, collect leaders.
 *
 * Naive approach: insert each new leader at the front of a growing array
 * so the result comes out left-to-right. That is O(k) per insert (shift
 * every element), O(k^2) total.
 *
 * The engineer version:
 *   Append while scanning right-to-left (O(1) per write into `out[]`),
 *   then reverse the first `count` cells (O(k)). Same order, O(n) time.
 *
 * Memory
 *   Caller provides `int out[]` sized to n. We return how many leaders
 *   we wrote. reverse is a swap loop in place; no second buffer.
 *   We are not using vector here; this is a C array.
 *
 * C theory — why add(0, x) hurts
 *   Contiguous arrays make append cheap and front-insert expensive.
 *   Linked lists make front-insert cheap and sequential scan expensive
 *   (no cache). Pick the structure that matches the hot operation.
 *   Here the hot operation is "append, then reverse once."
 *   `int nums[]` decays to a pointer, so you MUST pass n.
 *
 * Complexity: O(n) time, O(k) extra space.
 */

#include <climits>
#include <iostream>
using namespace std;

int rightElder(int nums[], int n, int out[]) {
    int maxSoFar = INT_MIN;
    int count = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (nums[i] > maxSoFar) {
            maxSoFar = nums[i];
            out[count] = maxSoFar;
            count++;
        }
    }
    for (int i = 0; i < count / 2; i++) {
        int tmp = out[i];
        out[i] = out[count - 1 - i];
        out[count - 1 - i] = tmp;
    }
    return count;
}

int main() {
    int nums[] = {7, 5, 4, 17, 3, 8, 13, 2, 6, 9};
    int n = sizeof(nums) / sizeof(nums[0]);
    int out[10];
    int k = rightElder(nums, n, out);
    for (int i = 0; i < k; i++) {
        cout << out[i] << " ";
    }
    cout << "\n";
    return 0;
}
