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
 *   Extra space O(1): one temporary int, plus the two indices. The vector
 *   does not reallocate. Capacity is unchanged.
 *
 * Memory management
 *   The std::vector<int> object lives on the caller's stack: typically three
 *   words (data pointer, size, capacity). The n ints live in one contiguous
 *   heap allocation owned by that vector. Passing std::vector<int>& passes
 *   the address of the stack object. We never copy the buffer. We overwrite
 *   cells. When main returns, the vector destructor frees the heap block.
 *   There is no malloc/free for you to write, and no leak if you do not
 *   call new.
 *
 *   A C equivalent is:
 *     void reverse(int *a, size_t n);
 *   a points at a[0]. a[i] is *(a + i). The pointer is not an array; it
 *   does not know n. That is why C always takes a length. v.data() and
 *   v.size() are that C interface.
 *
 * C theory — swap, aliasing, XOR, cache
 *   A correct swap of two ints is three assignments through a temporary:
 *     int temp = a[i];
 *     a[i]     = a[j];
 *     a[j]     = temp;
 *   temp is a stack local, almost certainly a register. Two loads, two
 *   stores. That is the machine code you want.
 *
 *   std::swap(a[i], a[j]) is the same algorithm for int, wrapped in a
 *   function template. Prefer it in production. We write the temporary
 *   by hand in this lesson so you see every load and store.
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
 *   j = nums.size() with no -1, the first read of nums[j] is past the
 *   end. The compiler owes you nothing: crash, silent corruption, or
 *   "it worked on my machine." Guard empty arrays before computing n-1,
 *   because size_t is unsigned: 0u - 1u wraps to a huge index.
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
#include <vector>

void reverse(std::vector<int>& nums) {
    if (nums.size() < 2) {
        return;
    }
    std::size_t i = 0;
    std::size_t j = nums.size() - 1;
    while (i < j) {
        const int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
        ++i;
        --j;
    }
}

int main() {
    std::vector<int> arr{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    reverse(arr);
    for (int x : arr) {
        std::cout << x << '\n';
    }
    return 0;
}
