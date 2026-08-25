/*
 * LESSON — Merge overlapping intervals, in place, after a sort
 *
 * Student, you are given a list of closed intervals [start, end].
 * Overlapping or touching intervals merge into one. Return the new
 * length of the compacted list. The surviving intervals sit at the
 * front of the same array.
 *
 * Intuition
 *   After you sort by start, overlaps become a local question: does
 *   the current interval start before or at the end of the interval
 *   we are currently extending? If prev.end >= cur.start, they
 *   overlap (or touch). Stretch prev.end to max(prev.end, cur.end).
 *   If they do not overlap, advance a write index and copy cur into
 *   that slot. The write index is the in-place compact: we overwrite
 *   slots that held intervals already absorbed.
 *
 *   Sample {{6,8},{1,9},{2,4},{4,7}}:
 *     sorted by start: {1,9}, {2,4}, {4,7}, {6,8}
 *     {1,9} swallows all three later ones because 9 >= each start.
 *     One interval remains: [1, 9].
 *
 * Complexity
 *   Sort O(n log n), merge pass O(n). Extra memory O(1) besides the
 *   sort's (introsort is in-place plus O(log n) stack). Output is
 *   written over the input. Return value is the new logical length;
 *   the vector's size() may still be n. Callers must use the returned
 *   length, not size().
 *
 * Memory management
 *   std::vector<std::vector<int>>& : we mutate the caller's table.
 *   Each inner vector<int> is a tiny heap buffer of two ints (or a
 *   small-buffer, depending on the library; two ints often still
 *   heap-allocate). A stronger layout is one vector of pair<int,int>
 *   or a struct Interval { int start, end; } in a single contiguous
 *   array. We keep vector<vector<int>> to match the usual interface.
 *
 *   The write-index compact does not allocate. It assigns inner
 *   vectors (pointer steal / copy of two ints). No new rows.
 *
 * C theory — comparators, overlap, in-place compact, cache
 *   std::sort with a lambda comparator:
 *       (a, b) => a[0] < b[0]
 *   The comparator must be a strict weak ordering. Returning a[0] <=
 *   b[0] is a bug: equality must be false both ways. We compare
 *   starts only; equal starts are fine in either order because the
 *   merge uses max of ends.
 *
 *   In C: qsort with a comparison function, or your own sort, on an
 *   array of struct { int s, e; }. Contiguous structs are the honest
 *   layout. Two-element heap vectors are a convenience tax.
 *
 *   Overlap for closed intervals: prev.end >= cur.start. If the
 *   problem used half-open [s, e), touching ends would not overlap
 *   and the test would be prev.end > cur.start. Know which topology
 *   you are in. The sample treats [2,4] and [4,7] as overlapping.
 *
 *   In-place compact is the same pattern as removing duplicates with
 *   a slow writer: a read index i and a write index prevIdx. Slots
 *   behind prevIdx are finished. We do not shrink the vector; we
 *   return how many slots are live. Reading past that length is a
 *   logic error (you would see leftover unmerged rows). Out-of-bounds
 *   of the vector itself is UB; leftover rows are still in-bounds.
 *
 *   Cache: sort jumps around, then the merge pass is sequential on
 *   the outer array. Prefer a struct Interval[] so start and end
 *   sit in the same cache line. vector<vector<int>> stores pointers
 *   in the outer buffer and the two ints elsewhere: an extra miss
 *   per interval. Fine for n = 4; think about it for n = 10^6.
 *
 * Print: "The Merged Intervals are: " then [start, end] pairs.
 */

#include <algorithm>
#include <iostream>
#include <vector>

int mergeOverlap(std::vector<std::vector<int>>& nums) {
    std::sort(nums.begin(), nums.end(),
              [](const std::vector<int>& a, const std::vector<int>& b) {
                  return a[0] < b[0];
              });
    int prevIdx = 0;
    for (std::size_t i = 1; i < nums.size(); ++i) {
        if (nums[static_cast<std::size_t>(prevIdx)][1] >= nums[i][0]) {
            nums[static_cast<std::size_t>(prevIdx)][1] =
                std::max(nums[static_cast<std::size_t>(prevIdx)][1], nums[i][1]);
        } else {
            ++prevIdx;
            nums[static_cast<std::size_t>(prevIdx)] = nums[i];
        }
    }
    return prevIdx + 1;
}

int main() {
    std::vector<std::vector<int>> nums{{6, 8}, {1, 9}, {2, 4}, {4, 7}};
    const int newSize = mergeOverlap(nums);
    std::cout << "The Merged Intervals are: ";
    for (int i = 0; i < newSize; ++i) {
        std::cout << '[' << nums[static_cast<std::size_t>(i)][0] << ", "
                  << nums[static_cast<std::size_t>(i)][1] << "] ";
    }
    std::cout << '\n';
    return 0;
}
