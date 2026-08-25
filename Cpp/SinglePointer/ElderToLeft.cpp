/*
 * LESSON — Leaders from the left ("elder to the left")
 *
 * Problem
 *   Walk left to right. Emit a value if it is strictly greater than every
 *   value seen so far (a left-to-right maximum). Sample:
 *   [7,5,4,11,3,8,13,2,16,9] -> 7 11 13 16
 *
 * Intuition
 *   One running max. If nums[i] > max, it is a leader; update max.
 *
 * Memory
 *   The answer size is between 1 and n (strictly increasing unique
 *   prefixes). We store it in a std::vector that grows. Growth is
 *   geometric (capacity doubles), so appends are amortized O(1).
 *
 *   std::vector<int> stores raw ints in one contiguous buffer. That is
 *   why a scan of the leaders is cache-friendly: no per-element heap
 *   object, no extra pointer chase.
 *
 * C theory — amortized growth
 *   vector::push_back: if size == capacity, allocate 2*capacity, copy
 *   (or move) old elements, free old buffer. Sum of copies over n
 *   appends is < 2n, hence amortized O(1). Never reserve-and-hope unless
 *   you know n; here n is known, so we could v.reserve(nums.size()) to
 *   avoid realloc entirely. We skip it because the output is usually
 *   much smaller than n.
 *
 * Complexity: O(n) time, O(k) extra space for k leaders.
 */

#include <iostream>
#include <limits>
#include <vector>

std::vector<int> leftElder(const std::vector<int>& nums) {
    int max = std::numeric_limits<int>::min();
    std::vector<int> leaders;
    for (int x : nums) {
        if (x > max) {
            max = x;
            leaders.push_back(x);
        }
    }
    return leaders;  // NRVO / move: no deep copy of the buffer in practice
}

int main() {
    std::vector<int> nums{7, 5, 4, 11, 3, 8, 13, 2, 16, 9};
    for (int x : leftElder(nums)) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
    return 0;
}
