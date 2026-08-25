/*
 * LESSON — Pivot integer by binary search on 1..n
 *
 * Student, find x in 1..n such that 1+...+x equals x+...+n, or -1.
 * Algebra (see also Cpp/Gussai/PivotInteger.cpp): this is equivalent
 * to x * x == n * (n + 1) / 2. The right-hand side is the n-th
 * triangular number. Sample n = 50: T_50 = 1275 is not a square, so
 * -1.
 *
 * Intuition
 *   You are searching the number line [1, n], not an array. The
 *   predicate "mid * mid compared to total" is monotone: squares
 *   grow. Binary search for an exact hit. If the search exits
 *   without equality, there is no integer x.
 *
 *   This is the same Gauss identity as the Gussai lesson, with the
 *   search written as the algorithm rather than as a comment next
 *   to a hardcoded table. There is no array because every "index"
 *   is the candidate x itself. Random access is a multiply.
 *
 * Complexity
 *   O(log n) multiplies. Extra memory O(1). No heap.
 *
 * Memory management
 *   A handful of integers on the stack. Nothing to allocate. The
 *   "data structure" is the integers 1..n, which you do not store.
 *
 * C theory — overflow of m*m, triangular overflow, no float
 *   total = n*(n+1)/2 in int overflows for n around 2^16. Compute
 *   1LL * n * (n + 1LL) / 2 in long long. n + 1LL promotes before
 *   the add, so n == INT_MAX does not overflow the add.
 *
 *   m * m in int overflows for m > 46340. Always 1LL * m * m.
 *   Signed overflow is UB: the program would be meaningless, not
 *   "wrap and get a lucky wrong answer." The compiler may delete
 *   your comparison. long long multiply is the fix, not a cast
 *   after the fact: (long long)(m * m) multiplies in int first.
 *
 *   Do not take sqrt((double)total) and round. Double has 53 bits
 *   of mantissa; large triangular numbers are not exact, and you
 *   would be testing the wrong integer. Exact 64-bit multiply and
 *   compare is the point of this file.
 *
 *   mid = l + (h - l) / 2 on the value range. l + h can still
 *   overflow if you wrote it that way with l and h near INT_MAX.
 *
 *   There is no cache lesson beyond "there is no buffer." Arithmetic
 *   lives in registers. That is the cheapest memory you have.
 *
 *   C: long long total = (long long)n * (n + 1LL) / 2; same loop.
 *
 * Sample prints -1.
 */

#include <iostream>

int pivotInteger(int n) {
    const long long total = 1LL * n * (n + 1LL) / 2;
    int l = 1;
    int h = n;
    while (l <= h) {
        const int m = l + (h - l) / 2;
        const long long square = 1LL * m * m;
        if (square == total) {
            return m;
        }
        if (square < total) {
            l = m + 1;
        } else {
            h = m - 1;
        }
    }
    return -1;
}

int main() {
    std::cout << pivotInteger(50) << '\n';
    return 0;
}
