/*
 * LESSON — Left rotate by one (the shift that teaches mutation)
 *
 * Problem
 *   Move every element one index left. The original head becomes the tail.
 *   [1,2,3,4] -> [2,3,4,1]
 *
 * Intuition
 *   Save nums[0]. Slide everything left by assignment. Put the saved
 *   value in the last slot. One temporary int.
 *
 * Memory
 *   This is in-place. The vector object does not reallocate. We overwrite
 *   contiguous `int` cells. The buffer address does not change.
 *
 *   Cost: O(n) assignments. There is no cheaper in-place rotate-by-one;
 *   every value must move. (A deque would make this O(1) at the ends, at
 *   the cost of worse locality for random access.)
 *
 * C theory — memmove
 *   The loop is exactly what memmove(dst, src, bytes) does for overlapping
 *   regions. In C you would write:
 *     int tmp = a[0];
 *     memmove(a, a+1, (n-1)*sizeof(int));
 *     a[n-1] = tmp;
 *   memmove is allowed to overlap; memcpy is not (UB if they overlap).
 *   Know the difference. We keep the explicit loop so you see every write.
 *
 * Complexity: O(n) time, O(1) extra space.
 */

#include <iostream>
#include <vector>

void rotateLeft(std::vector<int>& nums) {
    if (nums.empty()) {
        return;
    }
    const int temp = nums[0];
    for (std::size_t i = 0; i + 1 < nums.size(); ++i) {
        nums[i] = nums[i + 1];
    }
    nums.back() = temp;
}

int main() {
    std::vector<int> arr{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    rotateLeft(arr);
    for (int x : arr) {
        std::cout << x << '\n';
    }
    return 0;
}
