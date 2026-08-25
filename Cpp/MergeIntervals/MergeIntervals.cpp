/*
 * LESSON — Merge overlapping intervals, in place, after a sort
 *
 * Student, you are given a list of closed intervals [start, end]
 * stored as a two-column C array: int nums[][2]. Overlapping or
 * touching intervals merge into one. Return the new length of the
 * compacted list. The surviving intervals sit at the front of the
 * same array.
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
 *   Sort O(n log n) in general; this file uses a simple O(n^2) row
 *   swap on n = 4. Merge pass O(n). Extra memory O(1). Output is
 *   written over the input. Return value is the new logical length.
 *   Callers must use the returned length, not the original n.
 *
 * Memory
 *   int nums[][2]: a contiguous block of n pairs of ints. nums[i][0]
 *   is start, nums[i][1] is end. In a parameter the first dimension
 *   decays: the type is pointer-to-array-of-2-ints, int (*p)[2].
 *   sizeof(nums) inside mergeOverlap is the size of that pointer,
 *   not n * 2 * sizeof(int). We pass n. The second dimension [2]
 *   stays in the type so the compiler can scale row i by 8 bytes.
 *
 *   Why not sort(nums, nums + n)? sort needs an assignable element
 *   type. A row int[2] is an array; arrays cannot be assigned. We
 *   swap the two columns ourselves. That is honest C.
 *
 *   The write-index compact does not allocate. It copies two ints
 *   into an earlier row. No new rows.
 *
 * C theory — overlap, in-place compact, cache
 *   Layout: four intervals are eight ints in a row in memory:
 *       6, 8, 1, 9, 2, 4, 4, 7
 *   nums[i][j] is *(*(nums + i) + j), which the compiler turns into
 *   a single scaled offset from the base. Contiguous structs
 *   {int s, e;} are the same bytes with names.
 *
 *   Overlap for closed intervals: prev.end >= cur.start. If the
 *   problem used half-open [s, e), touching ends would not overlap
 *   and the test would be prev.end > cur.start. Know which topology
 *   you are in. The sample treats [2,4] and [4,7] as overlapping.
 *
 *   In-place compact is the same pattern as removing duplicates with
 *   a slow writer: a read index i and a write index prevIdx. Slots
 *   behind prevIdx are finished. We do not shrink the array; we
 *   return how many slots are live. Reading past that length is a
 *   logic error (you would see leftover unmerged rows). Out-of-bounds
 *   of the array itself is UB; leftover rows are still in-bounds.
 *
 *   Cache: the merge pass is sequential on a contiguous 2-column
 *   buffer. start and end of one interval sit in the same line.
 *
 * Print: "The Merged Intervals are: " then [start, end] pairs.
 * Sample prints: The Merged Intervals are: [1, 9]
 */

#include <iostream>
using namespace std;

int mergeOverlap(int nums[][2], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (nums[j][0] < nums[i][0]) {
                int t0 = nums[i][0];
                int t1 = nums[i][1];
                nums[i][0] = nums[j][0];
                nums[i][1] = nums[j][1];
                nums[j][0] = t0;
                nums[j][1] = t1;
            }
        }
    }
    int prevIdx = 0;
    for (int i = 1; i < n; i++) {
        if (nums[prevIdx][1] >= nums[i][0]) {
            if (nums[i][1] > nums[prevIdx][1]) {
                nums[prevIdx][1] = nums[i][1];
            }
        } else {
            prevIdx++;
            nums[prevIdx][0] = nums[i][0];
            nums[prevIdx][1] = nums[i][1];
        }
    }
    return prevIdx + 1;
}

int main() {
    int nums[][2] = {{6, 8}, {1, 9}, {2, 4}, {4, 7}};
    int n = sizeof(nums) / sizeof(nums[0]);
    int newSize = mergeOverlap(nums, n);
    cout << "The Merged Intervals are: ";
    for (int i = 0; i < newSize; i++) {
        cout << "[" << nums[i][0] << ", " << nums[i][1] << "] ";
    }
    cout << "\n";
    return 0;
}
