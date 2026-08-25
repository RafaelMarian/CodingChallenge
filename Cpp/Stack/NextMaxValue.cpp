/*
 * LESSON — Next greater to the right: a monotonic decreasing stack
 *
 * Student, for each index i, find the nearest value to the right of i
 * that is strictly greater than nums[i]. If none exists, write -1.
 *
 * Intuition
 *   Scan right to left. Maintain a stack of values that are still
 *   candidates for someone to their left. Keep that stack strictly
 *   decreasing from bottom to top (the top is the nearest, smallest
 *   remaining candidate).
 *
 *   At index i:
 *     1. Pop while the top is smaller than or equal to nums[i].
 *        Those values can never be the next greater for i, and they
 *        can never be the next greater for anyone further left either:
 *        nums[i] is closer and at least as large, so it dominates them.
 *     2. If the stack is empty, nothing to the right is greater: -1.
 *        Otherwise the top is the nearest greater value.
 *     3. Push nums[i]. It is now the nearest candidate for the left.
 *
 *   We store values, not indices, because the API asks for the next
 *   greater *value*. If you later need the index, push indices instead
 *   and read nums[stack.back()].
 *
 *   Why pop equal values? "Next greater" is strict. An equal is not
 *   greater, and a later left-hand element that wanted something
 *   strictly above nums[i] would not want that equal either.
 *
 * Complexity
 *   Each value is pushed once and popped at most once. The inner
 *   while looks like O(n) per step but is amortized O(1): across the
 *   whole scan there are at most n pushes and n pops. Time O(n).
 *   Extra memory: the stack is O(n) in the worst case (a strictly
 *   decreasing array: nothing ever pops). The answer array is O(n)
 *   as well; that is output, not auxiliary, depending on how you
 *   count.
 *
 * Memory management
 *   std::vector<int> used as a stack: push_back, pop_back, back.
 *   That is the C++ default stack. Do not reach for a node-based
 *   std::stack adapter unless you have a reason; the adapter still
 *   sits on a deque or vector, and you want the contiguous buffer.
 *   The stack vector owns a heap buffer. Worst case it holds n ints
 *   plus the answer vector of n ints. Two heap allocations, both
 *   contiguous. Destructors free them.
 *
 *   const std::vector<int>& for the input. The answer is returned by
 *   value (move/NRVO).
 *
 * C theory — LIFO, pointers, cache, overflow of the stack buffer
 *   A stack is last-in, first-out. The "nearest to the right" we have
 *   already seen is the last thing we pushed, so it sits at the back.
 *   pop_back is O(1): decrement size. No shift of other elements.
 *
 *   C analogue:
 *       int *stk = malloc(n * sizeof *stk);
 *       int top = 0;          // next free slot
 *       stk[top++] = value;   // push
 *       value = stk[--top];   // pop
 *   top is an index, not a pointer, but a pointer into the same buffer
 *   is the same idea: a stack pointer. Do not confuse this with the
 *   CPU call stack. This is an explicit heap array we use as a stack.
 *   The call stack is the frame of nextMaxValue; overflowing *that*
 *   is a different bug (deep recursion). Here recursion depth is 1.
 *
 *   Cache: we scan nums right to left (still sequential, prefetch
 *   works in reverse on most CPUs well enough) and touch the tail of
 *   the stack vector. The tail is hot. A linked-list stack would
 *   chase heap nodes and miss.
 *
 *   The values themselves are ints; we do not add them, so overflow
 *   is not the issue. Out-of-bounds on an empty stack is: calling
 *   back() or pop_back() when empty is UB. The while condition
 *   !stk.empty() is the guard. Never skip it.
 *
 * Sample {2,1,3,2,6,3,5,9,1,7} -> 3 3 6 6 9 5 9 -1 7 -1
 */

#include <iostream>
#include <vector>

std::vector<int> nextMaxValue(const std::vector<int>& arr) {
    std::vector<int> stk;
    std::vector<int> nmv(arr.size());
    for (int i = static_cast<int>(arr.size()) - 1; i >= 0; --i) {
        while (!stk.empty() && arr[static_cast<std::size_t>(i)] >= stk.back()) {
            stk.pop_back();
        }
        nmv[static_cast<std::size_t>(i)] = stk.empty() ? -1 : stk.back();
        stk.push_back(arr[static_cast<std::size_t>(i)]);
    }
    return nmv;
}

int main() {
    const std::vector<int> arr{2, 1, 3, 2, 6, 3, 5, 9, 1, 7};
    const std::vector<int> nmv = nextMaxValue(arr);
    for (int x : nmv) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
    return 0;
}
