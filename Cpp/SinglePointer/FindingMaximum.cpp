/*
 * LESSON — Maximum of an array, and why INT_MIN is a loaded constant
 *
 * Problem
 *   Return the largest value in the array.
 *
 * Intuition
 *   Keep a running champion. Compare each element to it. One pass.
 *
 * Memory
 *   Three machine words besides the input: the index, the current value
 *   (often in a register), and the champion. No heap. `int nums[]` decays
 *   to a pointer, so you MUST pass n.
 *
 * C theory — sentinels
 *   INT_MIN from <climits> is -2^31 on this machine. Using that as the
 *   initial champion is correct *only if* every element is >= INT_MIN,
 *   which is always true for int. It is *wrong* if you later want
 *   "no element seen yet" as a distinct state (an empty array): INT_MIN
 *   is a valid value, so you cannot tell "empty" from "the max really
 *   is INT_MIN".
 *
 *   Professional pattern for a non-empty array: initialize max to nums[0]
 *   and start the loop at 1. Then empty arrays are an explicit error, not a
 *   silent lie.
 *
 * Complexity: O(n) time, O(1) extra space.
 */

#include <climits>
#include <iostream>
using namespace std;

int getMax(int nums[], int n) {
    int maxVal = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (nums[i] > maxVal)
            maxVal = nums[i];
    }
    return maxVal;
}

int main() {
    int nums[] = {7, 5, 4, 16, 3, 9, 11, 13, 12, 8};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << getMax(nums, n) << "\n";  // 16
    return 0;
}
