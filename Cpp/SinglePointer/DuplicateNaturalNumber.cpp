/*
 * LESSON — Duplicate in 1..n via the same Gauss identity
 *
 * Problem
 *   Array of length n contains 1..n-1 plus one extra duplicate (the
 *   sample is 1..10 with a second 7, length 11). Sum of unique values is
 *   n*(n-1)/2. The extra copy is `actualSum - expectedSum`.
 *
 * Intuition
 *   Same as missing-number, flipped sign. One accumulator.
 *
 * Memory
 *   O(1). A hash set would be the lazy O(n) extra-space solution. Floyd's
 *   cycle-finding on the "index = value" graph is the O(1) extra-space
 *   solution that also works when you cannot use the sum (overflow, or
 *   multiple duplicates). Learn the sum first; then learn Floyd.
 *
 * C theory
 *   Multiply in long long. Computing `actual - expected` makes the sign
 *   obvious. Subtracting from expected and negating is the same arithmetic
 *   with a harder-to-read sign.
 *
 * Complexity: O(n) time, O(1) extra space.
 */

#include <iostream>
#include <vector>

int duplicateNumber(const std::vector<int>& nums) {
    const long long n = static_cast<long long>(nums.size());
    long long expected = n * (n - 1) / 2;  // 1 + 2 + ... + (n-1)
    long long actual = 0;
    for (int x : nums) {
        actual += x;
    }
    return static_cast<int>(actual - expected);
}

int main() {
    std::vector<int> nums{8, 5, 7, 3, 6, 1, 9, 4, 7, 10, 2};
    std::cout << duplicateNumber(nums) << '\n';  // 7
    return 0;
}
