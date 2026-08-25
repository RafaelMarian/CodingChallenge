/*
 * LESSON — Trapping rain water with two pointers
 *
 * Student, water sitting on index i is bounded by the tallest wall to
 * its left and the tallest wall to its right: water[i] =
 * max(0, min(leftMax[i], rightMax[i]) - height[i]). Building those
 * two arrays is O(n) extra memory. Two pointers compute the same
 * total with two running maxima and O(1) extra words.
 *
 * Problem
 *   An elevation map. Units of water that can pool (cannot flow off
 *   the ends). Sample: {4,0,8,0,1,6,2,5} traps 18.
 *
 * Algorithm intuition
 *   leftMax is the highest bar in [0, left], rightMax in [right, n).
 *   The water at a cell is limited by the smaller of those two
 *   bounding maxima, once that cell is under both bounds.
 *
 *   If leftMax < rightMax, the water at `left` is already decided:
 *   its limiting bound is leftMax, because the right side can offer
 *   at least rightMax, which is bigger. You can add
 *   leftMax - height[left] (when positive, i.e. when you are not on
 *   a new max) and then move left inward, updating leftMax.
 *   Symmetrically if rightMax <= leftMax, process `right` and move
 *   right inward.
 *
 *   You always process the side whose current max is smaller. That
 *   side's next cell has a known min(leftMax, rightMax). The other
 *   side is "at least this tall," which is enough.
 *
 * Complexity
 *   Time  O(n): left and right together cover the array once.
 *   Extra space O(1): two indices, two maxima, an accumulator.
 *   The prefix/suffix max arrays are the O(n)-space training wheels.
 *
 * Memory management
 *   int height[] decays to a pointer; pass n. We only load. No extra
 *   n-array of leftMax. Those n ints would be another buffer, another
 *   cold pass, then a third pass to add water. We avoid vector on
 *   purpose. Collapsing the tables into two running values is the
 *   same collapse you saw when a DP recurrence only needs the previous
 *   cell.
 *
 *   water is a running long long. It lives in a register / stack slot.
 *   Nothing to free.
 *
 * C theory — bounds, overflow, empty input, cache, UB
 *   height[0] and height[n-1] on n == 0 is UB. n < 2: return 0. n == 1:
 *   no interior to fill, return 0. We initialize leftMax and rightMax
 *   from the two ends only after n >= 2, and the loop is while left <
 *   right, so n == 1 never enters.
 *
 *   water += leftMax - height[left]. Both are int. If leftMax is
 *   always >= height[left] by the update order, the difference is
 *   non-negative and the add can still overflow the accumulator if
 *   the total water exceeds INT_MAX. Use long long for water in
 *   production. The sample is tiny; we keep a long long accumulator
 *   and print it as the API value 18.
 *
 *   Update order matters. Move the pointer first (or after the
 *   comparison of maxima), then raise the max or add water. If you
 *   add water before the cell is a candidate interior, you double
 *   count ends. Trace the sample with a table of left, right,
 *   leftMax, rightMax, water until it matches 18.
 *
 *   Never subtract in an order that goes negative and then clamp
 *   without a reason: if your invariant is leftMax >= height[left]
 *   when you add, the subtraction is non-negative and you should
 *   not hit a negative intermediate. If you break the invariant,
 *   you have a logic bug.
 *
 *   Cache: two sequential streams from the ends. Same shape as the
 *   container problem. In-place mutation is not used; the map is
 *   read-only. The "in-place" story here is in-place in the sense of
 *   extra memory, not in the sense of overwriting height.
 *
 *   Pointers: left and right are indices into a contiguous int
 *   array. left < right implies both are < n given the initialization.
 */

#include <iostream>
using namespace std;

int trap(int height[], int n) {
    if (n < 2) {
        return 0;
    }
    int left = 0;
    int right = n - 1;
    int leftMax = height[left];
    int rightMax = height[right];
    long long water = 0;
    while (left < right) {
        if (leftMax < rightMax) {
            left++;
            if (height[left] > leftMax) {
                leftMax = height[left];
            } else {
                water += leftMax - height[left];
            }
        } else {
            right--;
            if (height[right] > rightMax) {
                rightMax = height[right];
            } else {
                water += rightMax - height[right];
            }
        }
    }
    return water;
}

int main() {
    int arr[] = {4, 0, 8, 0, 1, 6, 2, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << trap(arr, n) << '\n';
    return 0;
}
