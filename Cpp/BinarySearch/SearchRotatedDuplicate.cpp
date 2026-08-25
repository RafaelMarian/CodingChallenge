/*
 * LESSON — Rotated search when duplicates are allowed (boolean)
 *
 * Student, same rotated-sorted setting as ModifiedBinarySearch, but
 * values may repeat. Return whether target appears, not its index.
 * Sample {6,6,6,6,7,3,3,3,4,4,5,5,6,6,6} contains 6: print true.
 *
 * Intuition
 *   The "one half is sorted" test used nums[l] <= nums[mid]. When
 *   nums[l] == nums[mid] == nums[h], that test tells you nothing:
 *   both halves can look "sorted" and still hide the seam, or hide
 *   the target, anywhere. The repair is to shrink the range from
 *   both ends:
 *
 *       if (nums[low] == nums[mid] && nums[mid] == nums[high]) {
 *           low++;
 *           high--;
 *           continue;
 *       }
 *
 *   You discard two copies you have already compared to target
 *   (mid was tested; low and high equal mid so they are not target
 *   either). Then resume. When the three are not equal, fall back
 *   to the distinct-elements logic.
 *
 * Complexity
 *   Average still logarithmic on well-behaved data. Worst case O(n):
 *   an array of all equal values that are not the target, or a long
 *   run of equals around both ends, forces you to shrink by one
 *   each step. Duplicates destroy the half-invariant. You cannot
 *   honestly quote O(log n) as a worst-case bound once equals are
 *   allowed. Extra memory still O(1).
 *
 * Memory management
 *   const std::vector<int>&, three indices. No extra buffer. The
 *   worst-case linear scan is still sequential-ish (the ends creep
 *   inward) plus occasional mids. No allocation.
 *
 * C theory — why equals break binary search, overflow, UB
 *   Binary search's power is an invariant: a predicate true on a
 *   prefix and false on a suffix (or the sorted-half analogue).
 *   Duplicates at the three probe points make the predicate
 *   unreadable. Shrinking both ends is the honest admission that
 *   you lost the invariant and must spend linear work until it
 *   returns. There is no clever O(log n) worst-case for this
 *   problem in the comparison model with duplicates — the lower
 *   bound becomes linear.
 *
 *   mid = low + (high - low) / 2. Same overflow lesson as always.
 *   After low++ and high--, the range can go empty (low > high);
 *   the while(low <= high) stops. Do not read nums[high] after
 *   that. That would be UB.
 *
 *   Returning bool, not an index: with duplicates, "the" index is
 *   not unique. Existence is the well-posed question.
 *
 *   Cache: shrinking both ends on a huge equal array is a linear
 *   scan from both sides. Fine. The painful case is mixed data that
 *   still hits the three-way equal often enough to degrade.
 *
 *   C: bool search(const int *a, int n, int target); same loop.
 *
 * Sample prints true.
 */

#include <iostream>
#include <vector>

bool search(const std::vector<int>& nums, int target) {
    int low = 0;
    int high = static_cast<int>(nums.size()) - 1;
    while (low <= high) {
        const int mid = low + (high - low) / 2;
        if (nums[static_cast<std::size_t>(mid)] == target) {
            return true;
        }
        if (nums[static_cast<std::size_t>(low)] == nums[static_cast<std::size_t>(mid)] &&
            nums[static_cast<std::size_t>(mid)] == nums[static_cast<std::size_t>(high)]) {
            ++low;
            --high;
            continue;
        }
        if (nums[static_cast<std::size_t>(low)] <= nums[static_cast<std::size_t>(mid)]) {
            if (nums[static_cast<std::size_t>(low)] <= target &&
                nums[static_cast<std::size_t>(mid)] > target) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        } else if (nums[static_cast<std::size_t>(mid)] < target &&
                   nums[static_cast<std::size_t>(high)] >= target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return false;
}

int main() {
    const std::vector<int> nums{6, 6, 6, 6, 7, 3, 3, 3, 4, 4, 5, 5, 6, 6, 6};
    std::cout << std::boolalpha << search(nums, 6) << '\n';
    return 0;
}
