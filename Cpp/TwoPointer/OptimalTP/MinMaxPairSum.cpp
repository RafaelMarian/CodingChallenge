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
 *   int nums[] decays to a pointer. sort(nums, nums+n) sorts the
 *   existing n cells. Two indices and a long long max on the stack.
 *   We avoid vector on purpose. No second array. The caller's buffer
 *   is permuted; there is no destructor to free it.
 *
 *   Passing a copy would preserve the original at O(n) extra memory.
 *   This API does not need the original.
 *
 * C theory — extremes, overflow, even length, cache, UB, in-place
 *   The pair sum must be computed in long long. Two int addends at
 *   the positive extreme overflow signed 32-bit. UB is not "wrap
 *   to negative and then your max is wrong"; UB means the compiler
 *   may delete the max update. 1LL * nums[i] + nums[j] is the
 *   habit. Track best in long long. Return int only when you know
 *   the result fits, as in this sample.
 *
 *   n even: i and j land on a clean split. We loop while i < j, so
 *   we never pair an element with itself. j = n-1 is valid after
 *   an n < 2 guard. Decrementing j is safe while i < j.
 *
 *   sort requires operator< to be a strict weak ordering. For int
 *   it is. Do not compare ints by subtracting them in a qsort
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
 *   prevent a bogus n-1.
 *
 *   Printing the int is the whole API. There is no pair list to
 *   format.
 */

#include <algorithm>
#include <iostream>
using namespace std;

int minPairSum(int nums[], int n) {
    if (n < 2) {
        return 0;
    }
    sort(nums, nums + n);
    int i = 0;
    int j = n - 1;
    long long best = 0;
    while (i < j) {
        long long s = 1LL * nums[i] + nums[j];
        if (s > best) {
            best = s;
        }
        i++;
        j--;
    }
    return best;
}

int main() {
    int nums[] = {7, 3, 1, 8, 6, 1, 7, 5};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << minPairSum(nums, n) << '\n';
    return 0;
}
