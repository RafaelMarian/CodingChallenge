/*
 * LESSON — Is an integer array a palindrome?
 *
 * Student, a palindrome reads the same forward and backward. For an array
 * of ints that is a statement about pairs of cells, not about strings.
 *
 * Problem
 *   Return true if and only if nums[k] == nums[n-1-k] for every k in
 *   [0, n). An empty array and a one-element array are palindromes:
 *   there is no pair that can disagree.
 *
 * Algorithm intuition
 *   You do not need to reverse a copy and compare. Put i at 0 and j at
 *   n-1. While i < j, if the two cells differ, reject. Otherwise walk
 *   inward. If you exhaust the pairs, every required equality held.
 *
 *   This is the reverse loop with a comparison instead of a swap. The
 *   invariant is: all pairs outside [i, j] already matched.
 *
 * Complexity
 *   Time  O(n). Best case is O(1) if the ends already differ; we still
 *   quote the worst case.
 *   Extra space O(1). We do not build a reversed copy. A reversed copy
 *   would be O(n) extra memory and O(n) time before the first comparison.
 *   That is wasted work and wasted memory.
 *
 * Memory management
 *   The parameter is int nums[] plus int n. nums decays to int*: a
 *   pointer to the first cell. It does not store the length, so n is
 *   required. We avoid vector on purpose. We only load. The n ints stay
 *   where the caller put them (here, a stack array in main). Stack usage
 *   in this function is two indices.
 *
 *   const on the pointed-to ints would be a contract that the callee
 *   will not write. This lesson does not write either way. The bytes
 *   still live wherever the caller allocated them.
 *
 * C theory — comparison, not mutation; cache; UB
 *   This algorithm does not mutate. In-place is a property of writers.
 *   Here every access is a load. That is the cheapest thing a CPU does
 *   to memory besides not touching it.
 *
 *   i and j are indices, not pointers, but the hardware is doing pointer
 *   arithmetic: the load of nums[i] is *(nums + i). If i is in range,
 *   that address is inside the array. If it is not, the load is
 *   undefined behavior. We keep i < j and j = n-1 with n >= 2, so both
 *   indices are valid.
 *
 *   Empty-array trap: n = 0, then n-1 is -1. We return true before
 *   forming that index. Signed overflow of int is undefined behavior;
 *   forming -1 as an index is simply the wrong address. Know which
 *   mistake you are dealing with.
 *
 *   Cache: two sequential streams from the ends, same as reverse. For
 *   a palindrome check you often reject early, so you may not touch
 *   the middle at all. Early exit is a gift; do not disable it by
 *   reversing first.
 *
 *   Equality of int is bitwise on two's complement. No overflow occurs
 *   because we never add the elements.
 */

#include <iostream>
using namespace std;

bool isPalindrome(int nums[], int n) {
    if (n < 2) {
        return true;
    }
    int i = 0;
    int j = n - 1;
    while (i < j) {
        if (nums[i] != nums[j]) {
            return false;
        }
        i++;
        j--;
    }
    return true;
}

int main() {
    int nums[] = {1, 2, 3, 4, 3, 2, 1};
    int n = sizeof(nums) / sizeof(nums[0]);
    if (isPalindrome(nums, n)) {
        cout << "true\n";
    } else {
        cout << "false\n";
    }
    return 0;
}
