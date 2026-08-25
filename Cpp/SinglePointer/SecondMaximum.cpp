/*
 * LESSON — Second maximum in one pass
 *
 * Problem
 *   Return the second-largest value. This implementation does not skip
 *   duplicates of the maximum, so [5, 16, 16] yields 16 as second max.
 *   (Interview variants often want the second *distinct* maximum — decide
 *   which contract you are implementing before you write the loop.)
 *
 * Intuition
 *   Two champions: firstMax and secondMax. When a new first arrives, the
 *   old first becomes second. When a value sits between them, it becomes
 *   second. Never scan twice.
 *
 * Memory
 *   Two ints. That is the whole extra state. Compare this to sorting
 *   (O(n log n) time, maybe O(n) space) just to read the last two cells.
 *   `int nums[]` decays to a pointer, so you MUST pass n.
 *
 * C theory
 *   Updating two variables has an *order*. You must shift second <- first
 *   before overwriting first, or you lose information. Registers are cheap;
 *   lost values are not recoverable. Think of it as a tiny insertion into
 *   a sorted 2-slot window. INT_MIN from <climits> seeds both slots.
 *
 * Complexity: O(n) time, O(1) extra space.
 */

#include <climits>
#include <iostream>
using namespace std;

int secMax(int nums[], int n) {
    int firstMax = INT_MIN;
    int secondMax = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (nums[i] > firstMax) {
            secondMax = firstMax;
            firstMax = nums[i];
        } else if (nums[i] > secondMax) {
            secondMax = nums[i];
        }
    }
    return secondMax;
}

int main() {
    int nums[] = {5, 9, 4, 7, 3, 11, 8, 16, 13, 12};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << secMax(nums, n) << "\n";  // 13
    return 0;
}
