/*
 * LESSON — Previous greater to the left: the same stack, opposite scan
 *
 * Student, for each index i, find the nearest value to the *left* of i
 * that is strictly greater than nums[i]. If none exists, write -1.
 *
 * Intuition
 *   This is next-greater with the time axis reversed. Scan left to
 *   right. The stack holds candidates to the left, still monotonic
 *   decreasing toward the top. At i, pop everything smaller than or
 *   equal to nums[i] (they are hidden by nums[i] from anyone further
 *   right). The new top, if any, is the previous greater. Then push.
 *
 *   Same three steps, opposite direction. If you understood
 *   NextMaxValue.cpp, this file is that argument with "right" and
 *   "left" swapped. Keep both in your hands: many problems (histogram
 *   rectangles, trapping rain, span of stock quotes) need one or both.
 *
 * Complexity
 *   Amortized O(n): each value pushed once, popped at most once.
 *   Extra memory O(n) worst case (a strictly increasing array: the
 *   stack never shrinks, because each new value is a new maximum and
 *   we pop the smaller ones... wait. Strictly increasing: each new
 *   value is greater, so we pop *everything* and the stack holds one
 *   element. Worst case is strictly *decreasing*: nothing is greater
 *   than what is already on the stack, nothing pops, stack grows to n).
 *
 * Memory management
 *   std::vector<int> as the stack (push_back / pop_back / back). One
 *   heap buffer for the stack, one for the answer. Input is a const
 *   reference: no copy. Both vectors free themselves in their
 *   destructors. No new/delete.
 *
 * C theory — symmetry, empty-stack UB, cache
 *   The stack is a pointer (or index) into a contiguous buffer plus a
 *   length. Growing past capacity reallocates: allocate a larger
 *   buffer, copy, free the old one. vector does that. Amortized O(1)
 *   push. If you know n up front you may reserve(n) to avoid
 *   reallocations; it is optional here.
 *
 *   back() on an empty vector is undefined behavior: you would read
 *   one-past-the-start, or a dangling slot. The ternary
 *   stk.empty() ? -1 : stk.back() is the C equivalent of checking
 *   top == 0 before reading stk[top-1].
 *
 *   Scan is left to right: the textbook sequential load. The stack
 *   tail is the hot cache line. Same locality story as next-greater.
 *
 *   Values are compared, not added. Integer overflow is not in play.
 *   What is in play is the signed index i walking 0 .. n-1, which is
 *   safe as long as n fits in int. For huge arrays use size_t and a
 *   different loop shape.
 *
 * Sample {7,1,3,2,9,5,6,3,1,2} -> -1 7 7 3 -1 9 9 6 3 3
 */

#include <iostream>
#include <vector>

std::vector<int> previousMaxValue(const std::vector<int>& arr) {
    std::vector<int> stk;
    std::vector<int> pmv(arr.size());
    for (std::size_t i = 0; i < arr.size(); ++i) {
        while (!stk.empty() && arr[i] >= stk.back()) {
            stk.pop_back();
        }
        pmv[i] = stk.empty() ? -1 : stk.back();
        stk.push_back(arr[i]);
    }
    return pmv;
}

int main() {
    const std::vector<int> arr{7, 1, 3, 2, 9, 5, 6, 3, 1, 2};
    const std::vector<int> pmv = previousMaxValue(arr);
    for (int x : pmv) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
    return 0;
}
