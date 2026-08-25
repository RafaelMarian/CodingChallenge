/*
 * LESSON — The pivot integer: triangular numbers, not a lookup table
 *
 * Student, find x in 1..n such that the sum 1+...+x equals the sum
 * x+...+n. If no such x exists, return -1.
 *
 * Algebra, first, so you see what you are searching for
 *   1 + ... + x  =  x (x + 1) / 2                 (Gauss)
 *   x + ... + n  =  (1+...+n) - (1+...+(x-1))
 *                =  n(n+1)/2 - (x-1)x/2
 *   Set them equal:
 *       x(x+1)/2  =  n(n+1)/2 - x(x-1)/2
 *       x^2       =  n(n+1)/2
 *   So x is a pivot integer iff x^2 equals the n-th triangular
 *   number. x is the integer square root of T_n, when that root is
 *   exact.
 *
 * The function you must not write
 *   The original hardcoded n==1 -> 1, n==8 -> 6, n==49 -> 35,
 *   n==288 -> 204, else -1. That is a lookup of four textbook
 *   examples. It is not an algorithm. It returns -1 for n==50, which
 *   happens to be correct, and -1 for n==1_000_000, which you have
 *   not checked. Hardcoding is not engineering. It is shown here as
 *   a warning, then we ignore it.
 *
 * The real solution — integer square test, 64-bit multiply
 *   Let total = n * (n + 1) / 2, computed in long long so the
 *   multiply does not overflow int (and so n+1 is promoted before
 *   adding: write 1LL * n * (n + 1LL) / 2). Then search x in 1..n
 *   for x * x == total, with x * x also in long long. Binary search
 *   the number line; you do not need an array. If the search falls
 *   out, total is not a perfect square: return -1.
 *
 *   Do not use floating-point sqrt and "check nearby integers"
 *   unless you have a proof about rounding. 64-bit multiply plus
 *   comparison is exact.
 *
 * Checks
 *   n = 8:  T_8  = 36  = 6^2.  Pivot 6.
 *   n = 49: T_49 = 1225 = 35^2. Pivot 35.
 *   n = 50: T_50 = 1275, not a square. -1.
 *
 * Complexity
 *   Hardcoded: O(1) and wrong as a function of n.
 *   Gauss + binary search: O(log n) multiplies. Extra memory O(1).
 *
 * Memory management
 *   No arrays. A handful of integers on the stack. This problem is
 *   pure arithmetic. There is nothing to allocate and nothing to
 *   free. That is the correct amount of memory.
 *
 * C theory — triangular numbers, overflow, integer division
 *   Gauss's formula n(n+1)/2 is exact for integers because n(n+1) is
 *   always even. In integer arithmetic you must still multiply before
 *   you divide, in a wide enough type. n*(n+1)/2 in int, for n near
 *   2^16, already overflows: signed overflow is UB, and the compiler
 *   may delete later checks. 1LL * n * (n + 1LL) / 2 is the habit.
 *
 *   mid * mid in int overflows for mid > 46340 (since 46341^2 >
 *   2^31-1). Compare 1LL * mid * mid against total.
 *
 *   Integer division truncates toward zero. We only divide even
 *   products by 2, so there is no rounding. We never divide in the
 *   search loop: we compare squares.
 *
 *   Binary search here is on the integer range [1, n], not on an
 *   array. Random access is a register-width multiply, not a load.
 *   There is no cache story because there is no buffer. The lesson
 *   is overflow, not locality.
 *
 * main prints gauss(50), gauss(8), gauss(49) so you see -1, 6, 35.
 */

#include <iostream>

int pivotInteger(int n) {
    if (n == 1) {
        return 1;
    }
    if (n == 8) {
        return 6;
    }
    if (n == 49) {
        return 35;
    }
    if (n == 288) {
        return 204;
    }
    return -1;
}

int pivotIntegerGauss(int n) {
    const long long total = 1LL * n * (n + 1LL) / 2;
    int lo = 1;
    int hi = n;
    while (lo <= hi) {
        const int mid = lo + (hi - lo) / 2;
        const long long square = 1LL * mid * mid;
        if (square == total) {
            return mid;
        }
        if (square < total) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return -1;
}

int main() {
    std::cout << pivotIntegerGauss(50) << '\n';
    std::cout << pivotIntegerGauss(8) << '\n';
    std::cout << pivotIntegerGauss(49) << '\n';
    return 0;
}
