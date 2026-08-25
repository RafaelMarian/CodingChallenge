/*
 * LESSON — Minimize the maximum pair sum (pairing the extremes)
 *
 * Student, this is an independent write-up of the same pairing
 * strategy as MiniMaxSum, with a different sample, so you can
 * re-implement from the comment without looking at that file.
 *
 * Problem
 *   You are given an even count of integers. Pair them all. The
 *   score of a pairing is the largest pair sum. Minimize that score.
 *   Sample: {7,3,1,8,6,1,7,5}. After sorting, 1 1 3 5 6 7 7 8. The
 *   extreme pairs are 1+8=9, 1+7=8, 3+7=10, 5+6=11. The maximum of
 *   those is 11. That is the answer.
 *
 * Algorithm intuition
 *   Sort the array into non-decreasing order. The smallest remaining
 *   value is the best counterweight for the largest remaining value:
 *   it raises that large number's pair sum as little as possible.
 *   Then repeat on the leftover inner interval. Two indices, one at
 *   each end, walk until they cross. The running max of (nums[i] +
 *   nums[j]) is the minimax score.
 *
 *   If you pair two large numbers, their sum is a high bar you can
 *   never lower later. If you pair two small numbers, you spend
 *   cheap addends on each other and leave a large number to pair
 *   with a medium one, which is usually a worse max. The extreme
 *   pairing equalizes.
 *
 * Complexity
 *   Time  O(n log n) dominated by sort, then a linear scan of n/2
 *   pairs.
 *   Extra space O(1) working memory if sort is in-place. The output
 *   is a single int. Do not store the pairs.
 *
 * Memory management
 *   We take std::vector<int>& and sort the existing heap allocation.
 *   Three words on the stack for the vector object in main; n ints
 *   on the heap. minPairSum adds two indices and a long long max.
 *   No new[]. No second vector. When main's vector goes out of
 *   scope, its destructor returns the n ints to the allocator.
 *
 *   Passing by value would copy n ints before sorting the copy,
 *   preserving the original at O(n) extra heap. This API does not
 *   need the original. const T& would not compile with std::sort.
 *
 * C theory — extremes, overflow, even length, cache, UB, in-place
 *   The pair sum must be computed in long long. Two int addends at
 *   the positive extreme overflow signed 32-bit. UB is not "wrap
 *   to negative and then your max is wrong"; UB means the compiler
 *   may delete the max update. 1LL * nums[i] + nums[j] is the
 *   habit. Track best in long long. Cast to int only when you know
 *   the result fits, as in this sample.
 *
 *   n even: i and j land on a clean split. We loop while i < j, so
 *   we never pair an element with itself. size_t j = n-1 is valid
 *   after an n < 2 guard. Decrementing j is safe while i < j.
 *
 *   std::sort requires operator< to be a strict weak ordering. For
 *   int it is. Do not compare ints by subtracting them in a qsort
 *   comparator; that subtraction overflows. C++ operator< does not
 *   subtract.
 *
 *   After sort, the array is contiguous and monotonic. Loading
 *   nums[i] and nums[j] in a lockstep inward walk hits two
 *   sequential streams. Prefetchers like this. A pointer-linked
 *   list of nodes with the same values would turn each step into
 *   a potential cache miss.
 *
 *   In-place: sort overwrites the input permutation. The pairing
 *   loop does not write. If a later function needed the unsorted
 *   people list, you already lost it. Copy-and-sort if that matters.
 *
 *   Empty array: 0. One element: not a pair, 0. Those guards also
 *   prevent the unsigned n-1 wrap.
 *
 *   Printing the int is the whole API. There is no pair list to
 *   format.
 */

#include <algorithm>
#include <iostream>
#include <vector>

int minPairSum(std::vector<int>& nums) {
    if (nums.size() < 2) {
        return 0;
    }
    std::sort(nums.begin(), nums.end());
    std::size_t i = 0;
    std::size_t j = nums.size() - 1;
    long long best = 0;
    while (i < j) {
        const long long s = 1LL * nums[i] + nums[j];
        if (s > best) {
            best = s;
        }
        ++i;
        --j;
    }
    return static_cast<int>(best);
}

int main() {
    std::vector<int> nums{7, 3, 1, 8, 6, 1, 7, 5};
    std::cout << minPairSum(nums) << '\n';
    return 0;
}
