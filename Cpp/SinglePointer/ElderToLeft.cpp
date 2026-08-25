/*
 * LESSON — Leaders from the left ("elder to the left")
 *
 * Problem
 *   Walk left to right. Emit a value if it is strictly greater than every
 *   value seen so far (a left-to-right maximum). Sample:
 *   [7,5,4,11,3,8,13,2,16,9] -> 7 11 13 16
 *
 * Intuition
 *   One running max. If nums[i] > maxSoFar, it is a leader; update maxSoFar.
 *
 * Memory
 *   The answer size is between 1 and n (strictly increasing unique
 *   prefixes). We write leaders into a caller-provided output array
 *   `int out[]` and return how many we wrote. The caller sizes `out` to
 *   n (worst case: a strictly increasing array). We are not using vector
 *   here; this is a C array.
 *
 * C theory
 *   `int nums[]` decays to a pointer, so you MUST pass n. The same is
 *   true of `out[]`: it is just a pointer to storage the caller owns.
 *   Returning a count (not a new buffer) is the C way to hand back a
 *   variable-length result without allocating.
 *
 * Complexity: O(n) time, O(k) extra space for k leaders (here, out[0..k)).
 */

#include <climits>
#include <iostream>
using namespace std;

int leftElder(int nums[], int n, int out[]) {
    int maxSoFar = INT_MIN;
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (nums[i] > maxSoFar) {
            maxSoFar = nums[i];
            out[count] = nums[i];
            count++;
        }
    }
    return count;
}

int main() {
    int nums[] = {7, 5, 4, 11, 3, 8, 13, 2, 16, 9};
    int n = sizeof(nums) / sizeof(nums[0]);
    int out[10];
    int k = leftElder(nums, n, out);
    for (int i = 0; i < k; i++) {
        cout << out[i] << " ";
    }
    cout << "\n";
    return 0;
}
