/*
 * LESSON — Squares of a sorted array, including negatives
 *
 * Student, squaring a sorted array of only non-negative values is a
 * single forward pass: squares are already ordered. Negatives break
 * that. The largest magnitude sits at one of the two ends, not in the
 * middle.
 *
 * Problem
 *   nums is sorted non-decreasing and may contain negatives. Return a
 *   new array of the squares, also sorted non-decreasing. Sample:
 *   {-8,-6,-5,1,2,3,4} -> 1,4,9,16,25,36,64 each on its own line.
 *
 * Algorithm intuition
 *   Compare the squares (or the magnitudes) of nums[l] and nums[r].
 *   The larger square is the next value to place at the back of the
 *   result. Fill res from index n-1 down to 0. Advance the end that
 *   donated the larger square. Because each step takes the current
 *   maximum remaining square, the result is filled in sorted order
 *   from the right.
 *
 *   The middle of nums has the values closest to zero, hence the
 *   smallest squares. They land at the front of res last.
 *
 * Complexity
 *   Time  O(n).
 *   Extra space O(n) for the result buffer. The input is const; we do
 *   not overwrite it. You could overwrite nums from the back only if
 *   the caller allowed mutation and you were careful about clobbering
 *   unread ends — the extra array is the honest, safe design here.
 *
 * Memory management
 *   const std::vector<int>& nums: no copy of the input, no mutation.
 *   std::vector<int> res(n) allocates a heap buffer of n ints, value-
 *   initialized to zero, then we fill every cell. The result is
 *   returned by value. C++17 copy elision / move makes returning a
 *   local vector cheap: you transfer the three-word object (pointer,
 *   size, capacity). You do not memcpy n ints on the return if the
 *   compiler elides, and a move only copies the three words and
 *   nulls the source. The destructor of the moved-from vector frees
 *   nothing of consequence.
 *
 *   In C you would malloc n ints, fill them, return the pointer, and
 *   the caller would free. Ownership is explicit and easy to leak.
 *   The C++ vector destructor is the owner.
 *
 * C theory — abs(INT_MIN), square overflow, cache, UB
 *   Do not rank the ends with abs as a 32-bit int. abs(INT_MIN) cannot
 *   be represented in 32-bit two's complement: the magnitude is 2^31,
 *   and INT_MAX is 2^31-1. Calling std::abs(INT_MIN) on int is
 *   undefined behavior. labs on a long that is still 32-bit has the
 *   same trap. llabs on long long is safe for INT_MIN because 2^31
 *   fits in 64-bit signed.
 *
 *   Prefer not to take abs at all. Compare squares in 64-bit:
 *     1LL * nums[l] * nums[l]  versus  1LL * nums[r] * nums[r]
 *   Left-associative: (1LL * nums[l]) * nums[l] promotes first, then
 *   multiplies. INT_MIN * INT_MIN = 2^62, which fits in signed 64-bit
 *   (up to 2^63-1). The square stored in res is still an int in this
 *   lesson's sample; if |x| > 46340, x*x does not fit in 32-bit int
 *   and storing it in int is a bug. Use long long for the result type
 *   when the problem allows large magnitudes. Here the sample values
 *   fit, and we still compute the comparison in long long so the
 *   ranking cannot overflow.
 *
 *   Writing res[index] = static_cast<int>(square) is only valid if
 *   square is in int's range. Know that conversion from a too-large
 *   long long to int is implementation-defined (often truncation).
 *
 *   Cache: we read nums from both ends sequentially and write res
 *   from the back sequentially. Three sequential streams. The result
 *   allocation may be cold on the first write; after that the lines
 *   fill nicely.
 *
 *   Indices: a signed write index from n-1 down to 0 is simpler than
 *   size_t decrementing through zero. l and r stay in range because
 *   each step consumes one of n cells. Empty input: the loop does
 *   not run.
 */

#include <iostream>
#include <vector>

std::vector<int> sortedSquares(const std::vector<int>& nums) {
    const int n = static_cast<int>(nums.size());
    std::vector<int> res(n);
    int l = 0;
    int r = n - 1;
    for (int index = n - 1; index >= 0; --index) {
        const long long left_sq = 1LL * nums[l] * nums[l];
        const long long right_sq = 1LL * nums[r] * nums[r];
        if (left_sq > right_sq) {
            res[index] = static_cast<int>(left_sq);
            ++l;
        } else {
            res[index] = static_cast<int>(right_sq);
            --r;
        }
    }
    return res;
}

int main() {
    std::vector<int> arr{-8, -6, -5, 1, 2, 3, 4};
    const std::vector<int> res = sortedSquares(arr);
    for (int x : res) {
        std::cout << x << '\n';
    }
    return 0;
}
