/*
 * LESSON — Move zeros to the end, preserve the order of the rest
 *
 * Student, this is an in-place stable partition: nonzero values keep
 * their relative order, zeros fill the tail. Two pointers, two jobs.
 *
 * Problem
 *   Mutate the array so every non-zero appears first, in the same order
 *   they originally appeared, and every zero occupies the suffix. Do not
 *   allocate a second buffer of n ints.
 *
 * Algorithm intuition
 *   Maintain a write index and a read index. Read scans the whole array.
 *   Whenever read sees a non-zero, that value belongs at write. Copy it
 *   there (and, if the cells differ, store a zero in the hole you just
 *   vacated so the tail is already zeros as you go). Then advance write.
 *   When read finishes, write is the count of non-zeros and [write, n)
 *   is already zero if you planted zeros as you swapped, or you can fill
 *   that range with zeros in a second pass.
 *
 *   write is the destination for the next kept value. read is the source.
 *   write <= read always. The region [0, write) is the finished nonzero
 *   prefix. The region (write, read] has been scavenged and holds only
 *   zeros (or is empty). [read, n) has not been looked at.
 *
 * Complexity
 *   Time  O(n): each index is visited a constant number of times.
 *   Extra space O(1): two indices, no second array.
 *
 * Memory management
 *   std::vector<int>& because we mutate the caller's buffer. The vector
 *   object is not resized. size() and capacity() stay the same. We only
 *   store into existing cells. That is true in-place: the heap allocation
 *   is reused as both input and output.
 *
 *   The lazy alternative is allocate a new vector, push nonzeros, then
 *   pad zeros. That is O(n) extra heap, a second allocation, a copy
 *   back, and a worse cache story (write a cold buffer, then write the
 *   original). Do not do that when the API allows mutation.
 *
 * C theory — partition, aliasing of write and read, cache, UB
 *   This is the same skeleton as a stable partition in C:
 *     size_t w = 0;
 *     for (size_t r = 0; r < n; ++r)
 *         if (a[r] != 0) { int t = a[r]; a[r] = 0; a[w++] = t; }
 *   When r == w and a[r] is nonzero, the store of zero would wipe the
 *   value before you copy it if you zeroed first. Order the assignments:
 *   either swap, or copy then zero only when w != r. The implementation
 *   below copies first, then zeros the old cell only on a real move.
 *
 *   If you wrote a[w++] = a[r]; a[r] = 0; with w == r, you copy the
 *   value onto itself and then zero it. That is a bug: you destroy the
 *   nonzero you meant to keep. The w != r guard is not style; it is
 *   correctness when the two indices alias.
 *
 *   Out-of-bounds: w never exceeds r, and r < n, so w < n. No write
 *   past the end. No reallocation, so no iterator invalidation (there
 *   are no iterators being held).
 *
 *   Overflow does not arise: we copy ints, we do not add them.
 *
 *   Cache: a single forward scan. One stream. This is the best case for
 *   prefetchers. You overwrite some cells you already passed; those
 *   lines are still hot.
 *
 *   Relative order of nonzeros is preserved because we write them in
 *   the order we read them. Zeros have no order worth keeping; they are
 *   indistinguishable. If zeros were unique objects, this would still
 *   be a stable partition of the nonzero class.
 */

#include <iostream>
#include <vector>

void moveZeroes(std::vector<int>& nums) {
    std::size_t write = 0;
    for (std::size_t read = 0; read < nums.size(); ++read) {
        if (nums[read] != 0) {
            if (write != read) {
                nums[write] = nums[read];
                nums[read] = 0;
            }
            ++write;
        }
    }
}

int main() {
    std::vector<int> nums{8, 0, 0, 3, 4, 0, 6, 3, 0, 2};
    moveZeroes(nums);
    for (int x : nums) {
        std::cout << x << '\n';
    }
    return 0;
}
