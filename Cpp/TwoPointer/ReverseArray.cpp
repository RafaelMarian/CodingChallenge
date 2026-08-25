/*
 * LESSON — Reverse an array in place with two indices
 *
 * Student, start here. Reversal is the simplest two-pointer mutation, and
 * every later in-place algorithm in this folder is a variation of the same
 * idea: two indices, a loop invariant, and a handful of assignments.
 *
 * Problem
 *   Reverse the sequence so that the first element becomes last and the last
 *   becomes first. Do it in the existing buffer. Do not allocate a second
 *   array.
 *
 * Algorithm intuition
 *   Place i on the leftmost cell and j on the rightmost cell. While i < j,
 *   exchange the two cells, then move inward: i++, j--. When the indices
 *   meet or cross, every pair (k, n-1-k) has been swapped exactly once.
 *   An odd-length array leaves the middle element untouched, which is
 *   correct: it is already in its final position.
 *
 *   The invariant is: after t swaps, the prefix of length t and the suffix
 *   of length t are the finished reversed ends, and the open interval
 *   (i, j) is the still-unreversed middle.
 *
 * Complexity
 *   Time  O(n): each element is read and written a constant number of times.
 *   Extra space O(1): one temporary int, plus the two indices. The array
 *   does not grow. We overwrite the same n cells.
 *
 * Memory management
 *   The parameter is int nums[] plus int n. In C and C++, an array
 *   parameter decays to a pointer to the first int. nums is really int*.
 *   The pointer does not know how many cells follow, which is why we
 *   always pass n ourselves. We avoid vector on purpose: a C array in
 *   main is a contiguous block of ints (these samples live on the stack).
 *   Passing nums passes one pointer. We never copy the n ints. We
 *   overwrite cells. No heap allocation, no destructor to remember.
 *
 *   nums[i] is *(nums + i). That is pointer arithmetic. i must stay in
 *   [0, n). The length lives in n, not inside the pointer.
 *
 * C theory — swap, aliasing, XOR, cache
 *   A correct swap of two ints is three assignments through a temporary:
 *     int temp = a[i];
 *     a[i]     = a[j];
 *     a[j]     = temp;
 *   temp is a stack local, almost certainly a register. Two loads, two
 *   stores. That is the machine code you want.
 *
 *   Do not XOR-swap. The folklore sequence
 *     x ^= y; y ^= x; x ^= y;
 *   fails if x and y alias the same object: x ^= x clears the cell to
 *   zero, and the value is gone. Even when the cells are distinct, XOR
 *   creates a serial dependency chain of three operations. A register
 *   temporary is faster on every modern CPU. XOR also does not generalize
 *   to types that are not bitwise integers. Treat it as a curiosity, not
 *   a tool.
 *
 *   Signed integers are not overflowed here: we only copy bits from one
 *   cell to another. Out-of-bounds is the UB to fear. If you wrote
 *   j = n with no -1, the first read of nums[j] is past the end. The
 *   compiler owes you nothing: crash, silent corruption, or "it worked
 *   on my machine." Guard n < 2 before computing n-1 so you never form
 *   a bogus index on an empty array.
 *
 *   The walk is sequential from both ends. Each end streams through
 *   cache lines (typically 64 bytes, 16 ints). Two sequential streams
 *   are still cache-friendly. A linked-list reverse would chase heap
 *   nodes and miss constantly. Contiguous storage is the point.
 *
 *   In-place mutation means the caller's array is the output. After
 *   reverse returns, the original order is gone unless the caller
 *   copied it first.
 */

#include <iostream>
using namespace std;

void reverse(int nums[], int n) {
    if (n < 2) {
        return;
    }
    int i = 0;
    int j = n - 1;
    while (i < j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
        i++;
        j--;
    }
}

int main() {
    int nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(nums) / sizeof(nums[0]);
    reverse(nums, n);
    for (int i = 0; i < n; i++) {
        cout << nums[i] << '\n';
    }
    return 0;
}
