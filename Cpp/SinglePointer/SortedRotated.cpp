/*
 * LESSON — Sorted and rotated: at most one "drop"
 *
 * Problem
 *   A rotated sorted array looks like [5,6,7,8,9,12,15,2,3,5]: two
 *   increasing runs, and the join is a single descent. Duplicates at the
 *   wrap (last <= first) are allowed by this implementation.
 *
 * Intuition
 *   Count how many times nums[i] > nums[i+1]. More than one drop means it
 *   is not a single rotation of a sorted array. Zero drops: already
 *   sorted. One drop: the wrap must satisfy last <= first.
 *
 * Memory
 *   One counter. You do not copy or rotate the array to test it.
 *
 * C theory
 *   This is a finite-state scan: you are verifying a *shape*, not
 *   searching for a value. Engineers do this for invariants
 *   ("is this buffer a valid ring?"). Early-exit when count > 1 so you
 *   do not pay for the rest of a clearly-invalid input.
 *
 * Complexity: O(n) time, O(1) extra space.
 */

#include <iostream>
#include <vector>

bool isSortedRotated(const std::vector<int>& nums) {
    int count = 0;
    for (std::size_t i = 0; i + 1 < nums.size(); ++i) {
        if (nums[i] > nums[i + 1]) {
            ++count;
            if (count > 1) {
                return false;
            }
        }
    }
    if (count == 0) {
        return true;
    }
    return nums.back() <= nums.front();
}

int main() {
    std::vector<int> nums{5, 6, 7, 8, 9, 12, 15, 2, 3, 5};
    std::cout << "ans" << std::boolalpha << isSortedRotated(nums) << '\n';
    return 0;
}
