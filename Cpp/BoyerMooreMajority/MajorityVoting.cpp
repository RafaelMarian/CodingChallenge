/*
 * LESSON — Boyer–Moore majority vote, and the variant you are about to run
 *
 * Student, a majority element (when it exists) is a value that appears
 * strictly more than n/2 times. Boyer–Moore finds a candidate in one
 * pass with two machine words of extra memory.
 *
 * This file keeps a slightly nonstandard loop so the sample
 * {9,13,9,16,9,11,9,20,9,9} still prints 9, matching the original:
 *
 *     count starts at 1, lastElement starts at INT_MIN
 *     if nums[i] == lastElement: count++
 *     else if count > 1:         count--
 *     else:                      lastElement = nums[i]
 *
 * Trace the sample: count stays 1 on every mismatch, so lastElement
 * simply tracks the current value, until the final pair of 9s raises
 * count to 2 and locks 9 in. It works here. It is not the algorithm
 * you should ship.
 *
 * Production Boyer–Moore (the one you must remember)
 *     candidate undefined, count = 0
 *     for i in 0 .. n-1:
 *         if count == 0: candidate = nums[i]
 *         count += (nums[i] == candidate) ? 1 : -1
 *     then a second pass: count how many times candidate actually
 *     occurs. If that is <= n/2, there is no majority. Return it
 *     only after verification.
 *
 *   The first pass cancels one copy of the candidate against every
 *   mismatch. If a true majority exists, it cannot be cancelled
 *   completely: more than n/2 copies survive. If no majority exists,
 *   the candidate is meaningless — hence the second pass. The
 *   original loop above does not always decrement on mismatch (it
 *   only decrements when count > 1, otherwise it switches), and it
 *   never verifies. Treat it as a museum piece that happens to print
 *   9 on this input.
 *
 * Complexity
 *   Time O(n) one pass (plus O(n) to verify in the classic version).
 *   Extra memory O(1): two ints. That is the point. You do not need
 *   a hash table of counts, which would be O(U) or O(distinct).
 *
 * Memory
 *   int nums[], int n. Two automatic ints. No heap. The input is a
 *   contiguous buffer; we load it once sequentially. nums decayed
 *   to a pointer; n is the length from sizeof in main.
 *
 * C theory — constant extra memory, INT_MIN as a sentinel, cache
 *   O(1) extra memory means the auxiliary state is a few registers.
 *   The array stays where the caller put it. This is what you want
 *   in a tight inner loop or on a microcontroller: no allocator in
 *   the hot path.
 *
 *   lastElement = INT_MIN is a sentinel meaning "no candidate yet."
 *   INT_MIN is also a legal array value. If the array's majority
 *   really were INT_MIN, the first mismatch handling still works
 *   because equality with INT_MIN would increment count. If the
 *   array is empty, we would return INT_MIN as a lie. Require n > 0.
 *
 *   The classic count += ±1 cannot overflow for n that fit in
 *   memory: count stays in [-n, n]. The variant's count stays
 *   positive and small.
 *
 *   Cache: one sequential scan, one compare, one increment or
 *   decrement. Almost no extra traffic. A hash table of frequencies
 *   would allocate, hash, and chase nodes to solve the same job.
 *
 *   Majority is strict: more than n/2, not >=, unless the problem
 *   says so.
 *
 * Sample prints 9.
 */

#include <climits>
#include <iostream>
using namespace std;

int majority(int nums[], int n) {
    int count = 1;
    int lastElement = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (nums[i] == lastElement) {
            count++;
        } else if (count > 1) {
            count--;
        } else {
            lastElement = nums[i];
        }
    }
    return lastElement;
}

int main() {
    int nums[] = {9, 13, 9, 16, 9, 11, 9, 20, 9, 9};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << majority(nums, n) << "\n";
    return 0;
}
