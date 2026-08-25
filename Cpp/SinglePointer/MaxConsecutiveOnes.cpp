/*
 * LESSON — Longest run of 1s
 *
 * Problem
 *   In a binary array, return the length of the longest consecutive
 *   sequence of ones.
 *
 * Intuition
 *   A run is a streak. On a 1, increment the streak. On a 0, the run is
 *   over: harvest it into `best`, reset the streak to 0. After the loop,
 *   harvest once more — the array may end on a run.
 *
 * Memory
 *   Two ints. You do not store the runs. You only keep the best length
 *   seen so far. That is the sliding-window idea in miniature: the
 *   "window" is the current run, and it only ever grows or resets.
 *   `int nums[]` decays to a pointer, so you MUST pass n.
 *
 * C theory
 *   A handwritten `if (count > best) best = count;` is the whole "keep
 *   the larger" idea. Do not forget the final harvest. Forgetting it is
 *   a classic off-by-one in state machines: the accepting state is never
 *   flushed.
 *
 * Complexity: O(n) time, O(1) extra space.
 */

#include <iostream>
using namespace std;

int maxOnes(int nums[], int n) {
    int best = 0;
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (nums[i] == 1) {
            count++;
        } else {
            if (count > best)
                best = count;
            count = 0;
        }
    }
    if (count > best)
        best = count;
    return best;
}

int main() {
    int nums[] = {1, 0, 1, 1, 1, 0, 1, 1, 1, 1};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << "ans" << maxOnes(nums, n) << "\n";  // ans4
    return 0;
}
