/*
 * LESSON — Previous and next values around a key in a sorted array
 *
 * Student, the array is sorted, distinct in this sample. Key may or
 * may not be present. Print two ints: the predecessor and the
 * successor in value, using -1 when that neighbor does not exist.
 *
 *   If key is present at index i: print nums[i-1] (or -1) and
 *   nums[i+1] (or -1). Those are the neighbors of that index.
 *   If key is absent: print the greatest element < key and the
 *   least element > key, again with -1 at the ends.
 *
 * Sample {3,4,6,7,10,11,13,15}, key 14: 14 is not present. The
 * greatest below is 13, the least above is 15.
 *
 * Intuition
 *   Binary search as lower_bound. If you hit, you have the index.
 *   If you miss, when the loop ends l is the insertion point: the
 *   first index with nums[l] > key (everything left of l is < key).
 *   Then
 *     prev = (l == 0) ? -1 : nums[l - 1]
 *     next = (l == n) ? -1 : nums[l]
 *   That is the whole miss case. Do not reconstruct neighbors from
 *   a stale mid after exit; that is how the original grew a thicket
 *   of end checks. l already is lower_bound.
 *
 * Complexity
 *   O(log n) time, O(1) extra memory.
 *
 * Memory management
 *   const std::vector<int>&. Return two ints. No extra buffer. We
 *   do not insert the missing key; we only name its neighbors.
 *
 * C theory — lower_bound neighbors, ends, overflow
 *   The insertion index l == n means key is larger than every
 *   element: next is -1, prev is nums[n-1]. l == 0 means key is
 *   smaller than every element: prev is -1, next is nums[0]. Those
 *   are the two end sentinels. Using -1 as "no neighbor" collides
 *   with a legal value of -1 in the array; the sample is positive
 *   so it is fine. A richer API would return optional<int>.
 *
 *   If you read nums[mid-1] when mid == 0, that is UB. The hit
 *   branch guards mid == 0. The miss branch uses l, which may be 0
 *   or n, and guards both.
 *
 *   mid = l + (h - l) / 2. Overflow of l+h is still UB.
 *
 *   Cache: logarithmic loads, then at most two more loads for the
 *   neighbors, which are adjacent to the hit (or to the insertion
 *   slot). Local.
 *
 *   C: fill two output ints. Same lower_bound loop.
 *
 * Sample prints 13 15.
 */

#include <iostream>
#include <utility>
#include <vector>

std::pair<int, int> prevNext(const std::vector<int>& nums, int key) {
    const int n = static_cast<int>(nums.size());
    int l = 0;
    int h = n - 1;
    while (l <= h) {
        const int mid = l + (h - l) / 2;
        if (key == nums[static_cast<std::size_t>(mid)]) {
            const int prev = (mid == 0) ? -1 : nums[static_cast<std::size_t>(mid - 1)];
            const int next = (mid == n - 1) ? -1 : nums[static_cast<std::size_t>(mid + 1)];
            return {prev, next};
        }
        if (key < nums[static_cast<std::size_t>(mid)]) {
            h = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    const int prev = (l == 0) ? -1 : nums[static_cast<std::size_t>(l - 1)];
    const int next = (l == n) ? -1 : nums[static_cast<std::size_t>(l)];
    return {prev, next};
}

int main() {
    const std::vector<int> nums{3, 4, 6, 7, 10, 11, 13, 15};
    const std::pair<int, int> res = prevNext(nums, 14);
    std::cout << res.first << ' ' << res.second << '\n';
    return 0;
}
