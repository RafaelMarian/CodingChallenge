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
 *   (O(n) heap) or a hash set (O(n) heap + worse constants).
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
#include <vector>

int missingNumber(const std::vector<int>& nums) {
    const long long n = static_cast<long long>(nums.size());
    long long sum = (n + 1) * (n + 2) / 2;
    for (int x : nums) {
        sum -= x;
    }
    return static_cast<int>(sum);
}

int main() {
    std::vector<int> nums{8, 5, 3, 1, 9, 4, 7, 10, 2};  // missing 6
    std::cout << missingNumber(nums) << '\n';
    return 0;
}
