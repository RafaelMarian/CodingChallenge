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
 *   `int nums[]` decays to a pointer, so you MUST pass n. Multiply in
 *   long long (`1LL * n * (n - 1) / 2`) so the product cannot overflow
 *   a 32-bit int. Computing `actual - expected` makes the sign obvious.
 *
 * Complexity: O(n) time, O(1) extra space.
 */

#include <iostream>
using namespace std;

int duplicateNumber(int nums[], int n) {
    long long expected = 1LL * n * (n - 1) / 2;  // 1 + 2 + ... + (n-1)
    long long actual = 0;
    for (int i = 0; i < n; i++) {
        actual += nums[i];
    }
    return actual - expected;
}

int main() {
    int nums[] = {8, 5, 7, 3, 6, 1, 9, 4, 7, 10, 2};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << duplicateNumber(nums, n) << "\n";  // 7
    return 0;
}
