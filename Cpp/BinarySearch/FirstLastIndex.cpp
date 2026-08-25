/*
 * LESSON — First and last index of a target in a sorted array
 *
 * Student, the array is sorted. Target may appear zero or more times.
 * Print the first and last indices where it occurs, or -1 -1 if it
 * is absent. Sample {3,3,3,4,6,6,6,6,7}, target 6: first 4, last 7.
 *
 * Intuition — the version we implement (faithful, O(n) worst)
 *   Binary search until nums[mid] == target. Then walk left while
 *   the previous element is still target, and walk right while the
 *   next is still target. Write those two bounds into out[0] and
 *   out[1]. Two ints, not a pair type.
 *
 *   That expand is simple and matches the original. It is O(n) in
 *   the worst case: an array of all target, the walks run to both
 *   ends. You paid for a binary search and then threw the log n
 *   away on the plateau.
 *
 * The O(log n) way you should know
 *   Two binary searches. lower_bound: first index with nums[i] >=
 *   target. upper_bound: first index with nums[i] > target. Then
 *   first = lower, last = upper - 1, after checking that lower
 *   is in range and nums[lower] == target. Each search is O(log n),
 *   even if the whole array is target, because you never scan the
 *   plateau: you keep bisecting with a different predicate.
 *
 * Complexity
 *   This file: O(log n) typical, O(n) worst. Extra memory O(1).
 *   Two-bound binary search: O(log n) always, O(1) extra.
 *
 * Memory
 *   int nums[], int n: the array decayed to a pointer plus a length.
 *   We write two ints into out[] (length 2). No extra array. The
 *   walks only read. Expanding does not allocate.
 *
 * C theory — plateaus, overflow, bounds on the walks
 *   Sorted arrays turn a run of equals into a contiguous plateau.
 *   Binary search lands somewhere on that plateau, not necessarily
 *   the left edge. That is why a single hit is not enough for
 *   "first" and "last."
 *
 *   Left walk: while (l > 0 && nums[l] == nums[l-1]) l--.
 *   The l > 0 is the guard against nums[-1], which is UB.
 *   Right walk: while (h + 1 < n && nums[h] == nums[h+1]) h++.
 *   The h+1 < n is the guard against one-past-the-end.
 *
 *   mid = l + (h - l) / 2 during the search. Same overflow rule.
 *
 *   C: fill two ints *first, *last. Or an out[2] buffer, as here.
 *
 * Sample prints 4 7.
 */

#include <iostream>
using namespace std;

void searchRange(int nums[], int n, int target, int out[]) {
    int l = 0;
    int h = n - 1;
    while (l <= h) {
        int mid = l + (h - l) / 2;
        if (target == nums[mid]) {
            l = mid;
            while (l > 0 && nums[l] == nums[l - 1]) {
                l--;
            }
            h = mid;
            while (h + 1 < n && nums[h] == nums[h + 1]) {
                h++;
            }
            out[0] = l;
            out[1] = h;
            return;
        }
        if (target < nums[mid]) {
            h = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    out[0] = -1;
    out[1] = -1;
}

int main() {
    int nums[] = {3, 3, 3, 4, 6, 6, 6, 6, 7};
    int n = sizeof(nums) / sizeof(nums[0]);
    int out[2];
    searchRange(nums, n, 6, out);
    cout << out[0] << " " << out[1] << "\n";
    return 0;
}
