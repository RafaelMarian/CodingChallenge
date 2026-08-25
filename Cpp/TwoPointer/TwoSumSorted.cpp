/*
 * LESSON — Two-sum on a sorted array, 1-based indices
 *
 * Student, unsorted two-sum wants a hash table. Sorted two-sum does not.
 * The order is information. Use it.
 *
 * Problem
 *   The input is sorted non-decreasing. Print one pair of 1-based indices
 *   i j, i < j, such that nums[i-1] + nums[j-1] == target. The sample
 *   has a unique answer. If none exists, print 0 0, which is not a
 *   valid 1-based pair.
 *
 * Algorithm intuition
 *   i starts at the smallest value, j at the largest. Let s be their sum.
 *   Because the array is sorted:
 *     - if s == target, you are done;
 *     - if s < target, no larger partner for nums[i] exists to the
 *       left of j, so the only way to increase s is i++;
 *     - if s > target, the only way to decrease s is j--.
 *   Each step discards one index forever. You examine O(n) candidate
 *   pairs, not O(n^2).
 *
 *   Why moving the other pointer cannot help: if s is too small, every
 *   pair (i, k) for k < j is even smaller, so those pairs are dead.
 *   The sorted order makes that statement true. Unsorted, it is false,
 *   and this algorithm is incorrect.
 *
 * Complexity
 *   Time  O(n) after the array is already sorted. If you had to sort,
 *   that would be O(n log n) and would scramble the original indices;
 *   this problem gives you a sorted array and asks for indices into it,
 *   so you must not sort a copy that you then index.
 *   Extra space O(1): two indices. We print them. We do not pack them
 *   into a pair object.
 *
 * Memory management
 *   int nums[] decays to int*. Pass n because the pointer has no length.
 *   We avoid vector on purpose. Read-only: no copy, no heap. The answer
 *   is two ints we print. The input buffer stays where the caller put
 *   it. We only load.
 *
 * C theory — overflow of the sum, pointers vs indices, cache
 *   The dangerous operation is nums[i] + nums[j]. Both are int.
 *   Signed addition overflow is undefined behavior. INT_MAX + 1 is not
 *   guaranteed to wrap; the compiler may delete branches that assume
 *   it cannot happen. Compute the sum in long long:
 *     1LL * nums[i] + nums[j]
 *   The 1LL forces the first multiplication/promotion; the rest of the
 *   addition then happens in at least 64 bits. INT_MAX + INT_MAX fits
 *   in a signed 64-bit long long.
 *
 *   Compare that long long to target after promoting target, or write
 *   sum == (long long)target. Mixed-width comparison promotes the int.
 *
 *   Indices versus pointers: you could walk with int *p = nums and
 *   int *q = nums + (n-1), and compare p < q. Pointer comparison
 *   is well-defined only inside the same array object (or one-past-end).
 *   Indices are harder to get wrong when you also need 1-based output:
 *   the answer is i+1 and j+1. Here i < n, so i+1 fits in int for the
 *   sizes in this course.
 *
 *   Cache: i walks forward, j walks backward, each sequentially. You
 *   touch every element at most once. Linear and prefetchable.
 *
 *   1-based indices are an API choice (common in "the first number is
 *   position 1" problem statements). Off-by-one lives here: printing
 *   i and j without +1 is a silent wrong answer, not a crash. Check
 *   the sample: {2,3,5,7,9,12,16,23,26,29} target 30 -> 4 8
 *   (values 7 and 23).
 */

#include <iostream>
using namespace std;

void twoSum(int nums[], int n, int target) {
    if (n < 2) {
        cout << "0 0\n";
        return;
    }
    int i = 0;
    int j = n - 1;
    long long need = target;
    while (i < j) {
        long long sum = 1LL * nums[i] + nums[j];
        if (sum == need) {
            cout << i + 1 << ' ' << j + 1 << '\n';
            return;
        }
        if (sum < need) {
            i++;
        } else {
            j--;
        }
    }
    cout << "0 0\n";
}

int main() {
    int nums[] = {2, 3, 5, 7, 9, 12, 16, 23, 26, 29};
    int n = sizeof(nums) / sizeof(nums[0]);
    twoSum(nums, n, 30);
    return 0;
}
