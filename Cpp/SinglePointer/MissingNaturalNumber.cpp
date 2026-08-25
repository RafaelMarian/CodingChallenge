/*
 * LESSON — Missing natural number via Gauss, and the overflow trap
 *
 * Problem
 *   The array holds n distinct integers from 1..n+1 with exactly one
 *   missing. Return the missing value.
 *
 * Intuition (Gauss)
 *   Sum(1..n+1) = (n+1)*(n+2)/2. Subtract every present element. What
 *   remains is the hole. One pass, no extra set.
 *
 * Memory
 *   One integer accumulator. Contrast with a boolean[n+2] mark array
 *   (O(n) extra) or a hash set. `int nums[]` decays to a pointer, so you
 *   MUST pass n. We are not using vector here; this is a C array.
 *
 * C theory — THIS is the overflow lesson
 *   Signed overflow of `int` is undefined behavior. For n around 50_000,
 *   (n+1)*(n+2) already exceeds 2^31-1. Unsigned wrap is defined; signed
 *   wrap is not. Never "let it overflow and hope."
 *
 *   Wrong:  int sum = (n + 1) * (n + 2) / 2;
 *   Right:  long long sum = 1LL * (n + 1) * (n + 2) / 2;
 *
 *   The 1LL forces 64-bit arithmetic before the multiply. Division by 2
 *   is exact because the product of two consecutive integers is even.
 *
 *   XOR trick (optional homework): xor all of 1..n+1 and xor all array
 *   values. The missing number remains. No overflow at all, still O(1)
 *   extra memory. Engineers pick XOR when the range is a complete set
 *   of ids and they do not want a wide accumulator.
 *
 * Complexity: O(n) time, O(1) extra space.
 */

#include <iostream>
using namespace std;

int missingNumber(int nums[], int n) {
    long long sum = 1LL * (n + 1) * (n + 2) / 2;
    for (int i = 0; i < n; i++) {
        sum -= nums[i];
    }
    return sum;
}

int main() {
    int nums[] = {8, 5, 3, 1, 9, 4, 7, 10, 2};  // missing 6
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << missingNumber(nums, n) << "\n";
    return 0;
}
