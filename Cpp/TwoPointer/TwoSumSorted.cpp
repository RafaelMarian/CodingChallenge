/*
 * LESSON — Two-sum on a sorted array, 1-based indices
 *
 * Student, unsorted two-sum wants a hash table. Sorted two-sum does not.
 * The order is information. Use it.
 *
 * Problem
 *   The input is sorted non-decreasing. Return one pair of 1-based indices
 *   (i, j), i < j, such that numbers[i-1] + numbers[j-1] == target. The
 *   sample has a unique answer. If none exists, the implementation below
 *   returns {0, 0}, which is not a valid 1-based pair.
 *
 * Algorithm intuition
 *   i starts at the smallest value, j at the largest. Let s be their sum.
 *   Because the array is sorted:
 *     - if s == target, you are done;
 *     - if s < target, no larger partner for numbers[i] exists to the
 *       left of j, so the only way to increase s is ++i;
 *     - if s > target, the only way to decrease s is --j.
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
 *   Extra space O(1) besides the two-integer answer.
 *
 * Memory management
 *   const std::vector<int>&: read-only alias, no copy, no heap traffic
 *   in this function. The answer is two ints. Returning std::pair<int,int>
 *   by value is cheap (two registers). Do not allocate a heap vector of
 *   length 2 for two integers.
 *
 *   The input buffer stays where the caller put it. We only load.
 *
 * C theory — overflow of the sum, pointers vs indices, cache
 *   The dangerous operation is numbers[i] + numbers[j]. Both are int.
 *   Signed addition overflow is undefined behavior. INT_MAX + 1 is not
 *   guaranteed to wrap; the compiler may delete branches that assume
 *   it cannot happen. Compute the sum in long long:
 *     1LL * numbers[i] + numbers[j]
 *   The 1LL forces the first multiplication/promotion; the rest of the
 *   addition then happens in at least 64 bits. INT_MAX + INT_MAX fits
 *   in a signed 64-bit long long.
 *
 *   Compare that long long to target after promoting target, or write
 *   sum == static_cast<long long>(target). Mixed-width comparison
 *   promotes the int.
 *
 *   Indices versus pointers: you could walk with int *p = v.data() and
 *   int *q = v.data() + (n-1), and compare p < q. Pointer comparison
 *   is well-defined only inside the same array object (or one-past-end).
 *   Indices are harder to get wrong when you also need 1-based output:
 *   the answer is i+1 and j+1. Adding 1 to a size_t that is SIZE_MAX
 *   would wrap; here i < n, so i+1 fits in size_t, and for n that fit
 *   in int (this course), the 1-based index fits in int after a cast.
 *
 *   Cache: i walks forward, j walks backward, each sequentially. You
 *   touch every element at most once. Linear and prefetchable.
 *
 *   1-based indices are an API choice (common in "the first number is
 *   position 1" problem statements). Off-by-one lives here: returning
 *   i and j without +1 is a silent wrong answer, not a crash. Check
 *   the sample.
 */

#include <iostream>
#include <utility>
#include <vector>

std::pair<int, int> twoSum(const std::vector<int>& numbers, int target) {
    if (numbers.size() < 2) {
        return {0, 0};
    }
    std::size_t i = 0;
    std::size_t j = numbers.size() - 1;
    const long long need = target;
    while (i < j) {
        const long long sum = 1LL * numbers[i] + numbers[j];
        if (sum == need) {
            return {static_cast<int>(i + 1), static_cast<int>(j + 1)};
        }
        if (sum < need) {
            ++i;
        } else {
            --j;
        }
    }
    return {0, 0};
}

int main() {
    std::vector<int> nums{2, 3, 5, 7, 9, 12, 16, 23, 26, 29};
    const std::pair<int, int> res = twoSum(nums, 30);
    std::cout << res.first << ' ' << res.second << '\n';
    return 0;
}
