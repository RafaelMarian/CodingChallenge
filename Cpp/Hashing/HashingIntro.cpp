/*
 * LESSON — Counting array: most frequent value when keys are 0..U
 *
 * Student, given a non-empty array of non-negative ints, return the
 * value that occurs most often (not the count; the value). Ties go
 * to the smallest value, because we scan the count buffer from 0
 * and keep a strict greater.
 *
 * Intuition
 *   If every key is an integer in 0..U, you do not need a hash table.
 *   Allocate a buffer of length U+1, zero it, and do hash[x]++ for
 *   each element. Then scan the buffer once: the index with the
 *   largest count is the answer. That is the counting-sort idea,
 *   stopped before the write-back pass. Frequency is an array
 *   lookup, O(1), because the key *is* the index.
 *
 *   Sample {8, 3, 11, 8, 7, 8, 14, 3, 9, 7}: U = 14. After counting,
 *   hash[8] == 3 is the unique maximum. Return 8.
 *
 * Complexity
 *   Time O(n + U): one pass over nums, one pass over the count
 *   buffer. Extra memory O(U). When U is O(n) this is linear. When
 *   U is 10^9 and n is 10, you have just allocated a fantasy.
 *
 * Memory management
 *   vector<int> hash(max+1, 0) is one contiguous heap allocation of
 *   (U+1) ints, value-initialized to zero. The allocator asks the OS
 *   for a block; the constructor writes zeros (or the OS may hand
 *   you already-zero pages from mmap). Destructor frees it. We never
 *   new[] / delete[].
 *
 *   const std::vector<int>& for the input. The count buffer is local.
 *
 * C theory — dense maps, sparse waste, overflow of the index
 *   This is an array used as a map from key to count. It is dense:
 *   every integer in 0..U has a slot, even keys that never appear.
 *   Those zeros are wasted space and wasted scan time. That is fine
 *   when U is small and you want O(1) indexing plus a cold-cache
 *   sequential scan of a compact buffer. It is not fine when the
 *   key domain is sparse or huge. Then you want a hash table
 *   (see UsingMap.cpp) whose memory is O(distinct keys), not O(U).
 *
 *   C:
 *       int *hash = calloc(max + 1, sizeof *hash);  // zeroed
 *       hash[x]++;
 *       free(hash);
 *   hash[x] is *(hash + x). If x is negative, you index before the
 *   buffer: UB, a classic heap underflow. If x > max, heap overflow.
 *   AddressSanitizer is how you catch that in a lab. This algorithm
 *   is only correct for keys in [0, max] where max is the maximum
 *   value present (so every key is a valid index).
 *
 *   max+1 can overflow int if max == INT_MAX. Passing a huge size to
 *   the allocator can also wrap a size_t. For classroom data it does
 *   not. For untrusted data, check.
 *
 *   Cache: the increment pass is random access into hash[], driven
 *   by nums[i]. If nums is shuffled over a large U, you miss cache
 *   on almost every ++. If U is small, hash[] fits in L1 and ++ is
 *   cheap. That is the real "when is a counting array OK": U small
 *   enough that the buffer is hot, and keys non-negative.
 *
 *   hash as a name: it is a count array, not a hash table. There is
 *   no hash function. The identity function is the "hash." We keep
 *   the name because that is how this family of lessons speaks.
 */

#include <climits>
#include <iostream>
#include <vector>

int mostOccurring(const std::vector<int>& nums) {
    int max = INT_MIN;
    for (int x : nums) {
        if (x > max) {
            max = x;
        }
    }
    std::vector<int> hash(static_cast<std::size_t>(max) + 1, 0);
    for (int x : nums) {
        ++hash[static_cast<std::size_t>(x)];
    }
    int best = 0;
    for (std::size_t i = 0; i < hash.size(); ++i) {
        if (hash[i] > hash[static_cast<std::size_t>(best)]) {
            best = static_cast<int>(i);
        }
    }
    return best;
}

int main() {
    const std::vector<int> nums{8, 3, 11, 8, 7, 8, 14, 3, 9, 7};
    std::cout << mostOccurring(nums) << '\n';
    return 0;
}
