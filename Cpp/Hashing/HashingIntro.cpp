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
 * Memory — new / malloc, and why we free
 *   U is data-dependent. A stack array int hash[U+1] is a VLA (not
 *   portable C++) and can smash the stack if U is large. So we
 *   allocate on the heap:
 *
 *       int *hash = new int[maxv + 1]();   // () zeroes every slot
 *       ...
 *       delete[] hash;                     // one delete[] per new[]
 *
 *   C is the same story with a different spelling:
 *
 *       int *hash = (int *)malloc((maxv + 1) * sizeof(int));
 *       memset(hash, 0, (maxv + 1) * sizeof(int));
 *       ...
 *       free(hash);                        // one free per malloc
 *
 *   new[] returns a pointer to the first int. hash[x] is *(hash + x).
 *   The pointer does not know maxv; we keep maxv in a local. Miss the
 *   delete[] and you leak. Use delete (no brackets) on new[] and you
 *   corrupt the heap. Use the array after delete[] and you have a
 *   dangling pointer: UB.
 *
 *   For this sample maxv is 14, so int hash[15] on the stack would
 *   also work. We heap-allocate on purpose so you see the lifetime.
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
 *   If x is negative, you index before the buffer: UB, a classic
 *   heap underflow. If x > maxv, heap overflow. AddressSanitizer is
 *   how you catch that in a lab. This algorithm is only correct for
 *   keys in [0, maxv] where maxv is the maximum value present (so
 *   every key is a valid index).
 *
 *   maxv+1 can overflow int if maxv == INT_MAX. Passing a huge size
 *   to the allocator can also wrap. For classroom data it does not.
 *   For untrusted data, check.
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
 *
 * Sample prints 8.
 */

#include <iostream>
using namespace std;

int mostOccurring(int nums[], int n) {
    int maxv = nums[0];
    for (int i = 1; i < n; i++) {
        if (nums[i] > maxv) {
            maxv = nums[i];
        }
    }
    int *hash = new int[maxv + 1]();
    for (int i = 0; i < n; i++) {
        hash[nums[i]]++;
    }
    int best = 0;
    for (int i = 0; i <= maxv; i++) {
        if (hash[i] > hash[best]) {
            best = i;
        }
    }
    delete[] hash;
    return best;
}

int main() {
    int nums[] = {8, 3, 11, 8, 7, 8, 14, 3, 9, 7};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << mostOccurring(nums, n) << "\n";
    return 0;
}
