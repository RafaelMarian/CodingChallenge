/*
 * LESSON — Classic binary search on a sorted array
 *
 * Student, the array is sorted in non-decreasing order. Return the
 * index of key, or -1 if it is absent. Sample {2,3,5,6,7,8,9,11,13,14}
 * with key 10 returns -1: 10 is not present, and the search proves it
 * after discarding half of the remaining range at every step.
 *
 * Intuition
 *   Keep a closed range [l, h] that must contain key if key is
 *   anywhere. Compare key to the middle element. If equal, return mid.
 *   If key is smaller, the right half cannot contain it: h = mid - 1.
 *   If key is larger, the left half cannot: l = mid + 1. The range
 *   shrinks until it is empty (l > h) or you hit.
 *
 *   This requires random access: you must load nums[mid] in O(1).
 *   A linked list has no useful binary search; you would spend O(n)
 *   walking to mid. Arrays (and std::vector) give pointer arithmetic.
 *
 * Complexity
 *   Time O(log n): the range halves each iteration. Extra memory O(1).
 *   Recursion would use O(log n) stack frames; the loop does not.
 *
 * Memory management
 *   const std::vector<int>&: no copy. l, h, mid are automatic ints.
 *   The buffer is contiguous on the heap. Binary search jumps around
 *   that buffer: first the middle, then a quarter, and so on. For
 *   large n those loads miss cache. Sequential linear search over a
 *   small array that already sits in L1 can beat binary search on
 *   wall-clock time, despite worse big-O, because it prefetches and
 *   has a tight predictable loop. Branch prediction: each comparison
 *   is data-dependent. Linear scan on tiny n is often the right call.
 *   Binary search is the right call when n is large and the array is
 *   already sorted (or you will search it many times).
 *
 * C theory — midpoint overflow, half-invariants, UB
 *   The naive mid = (l + h) / 2 adds two ints. If l and h are large,
 *   l + h overflows. Signed overflow is undefined behavior. The
 *   compiler may assume it never happens. The safe form is
 *
 *       mid = l + (h - l) / 2
 *
 *   h - l is non-negative and fits in int if h and l do. Then add l.
 *   Unsigned size_t wrap of (l+h)/2 is well-defined but still gives
 *   the wrong index. Same recipe: l + (h - l) / 2.
 *
 *   Loop condition is l <= h because the range is closed. Using l < h
 *   without care drops the last element. When you set h = mid - 1 you
 *   exclude mid (you already tested it). Off-by-one here is the
 *   classic binary-search bug: infinite loop or skipped cell.
 *
 *   C: int bsearch(const int *a, int n, int key). a[mid] is
 *   *(a + mid). Out-of-bounds mid is UB. The loop invariant keeps
 *   0 <= l <= h < n or l > h (empty).
 *
 *   Sortedness is a precondition. If the array is not sorted the
 *   algorithm still "runs" and returns a number that means nothing.
 *   That is not UB; it is a wrong answer. UB would be an index off
 *   the end, which a correct loop does not do.
 *
 * Sample prints -1.
 */

#include <iostream>
#include <vector>

int binarySearch(const std::vector<int>& nums, int key) {
    int l = 0;
    int h = static_cast<int>(nums.size()) - 1;
    while (l <= h) {
        const int mid = l + (h - l) / 2;
        if (key == nums[static_cast<std::size_t>(mid)]) {
            return mid;
        }
        if (key < nums[static_cast<std::size_t>(mid)]) {
            h = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return -1;
}

int main() {
    const std::vector<int> nums{2, 3, 5, 6, 7, 8, 9, 11, 13, 14};
    std::cout << binarySearch(nums, 10) << '\n';
    return 0;
}
