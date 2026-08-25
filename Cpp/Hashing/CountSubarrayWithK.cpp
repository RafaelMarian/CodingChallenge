/*
 * LESSON — Subarrays with sum k: prefix sums plus a frequency map
 *
 * Student, count how many contiguous subarrays have sum equal to k.
 * Sample: {10, 2, -2, -20, 10}, k = -10. There are three:
 *   [10, 2, -2, -20],  [2, -2, -20, 10],  [-20, 10].
 *
 * Intuition
 *   Let prefix[j] be the sum of nums[0..j]. Then the sum of
 *   nums[i..j] is prefix[j] - prefix[i-1] (and prefix[-1] = 0).
 *   We want prefix[j] - prefix[i-1] == k, i.e.
 *
 *       prefix[i-1] == prefix[j] - k
 *
 *   For the current running sum curr, the number of earlier prefixes
 *   equal to curr - k is exactly the number of subarrays ending here
 *   that sum to k. Store prefix frequencies in an unordered_map.
 *   Seed the map with (0, 1): one empty prefix, so a subarray that
 *   starts at index 0 is counted when curr itself equals k.
 *
 *   Walk left to right: add nums[i] into curr, add map[curr - k] to
 *   the answer, then increment map[curr]. The increment is after the
 *   lookup so you do not count the empty suffix as a subarray unless
 *   k == 0 and you intend to (and even then the empty prefix is the
 *   seed, not a slice of the array). For k == 0 the seed still means
 *   "subarrays that sum to 0", which is correct; we never count a
 *   zero-length slice as an extra because we only query after adding
 *   a real element.
 *
 * Complexity
 *   Time average O(n). Each step is a hash lookup and a hash insert.
 *   Worst O(n^2) if the table degenerates. Extra memory O(n) prefixes
 *   in the map in the worst case (all prefix sums distinct).
 *
 * Memory
 *   The map holds up to n+1 keys (the seed plus one per index). Each
 *   is a heap node. The running sum is a scalar. We do not store the
 *   prefix array explicitly: the map *is* the compressed prefix
 *   history. int arr[], int n: the input decayed to a pointer plus
 *   a length. typedef unordered_map<int, int> Freq so the type has
 *   no std:: prefix.
 *
 * C theory — why the map, overflow, and the empty prefix
 *   If you stored prefix in an array you could, for each j, scan all
 *   i <= j and test equality. That is O(n^2). The map turns "how many
 *   earlier prefixes equal this value" into an expected O(1) query.
 *   You are indexing by the *value* of the prefix, not by an index,
 *   so a dense count array would need a slot per possible sum. Sums
 *   can be negative and large: U is not a small alphabet. Hash table.
 *
 *   curr += arr[i] can overflow int. Signed overflow is UB. A
 *   production version accumulates curr as long long and uses
 *   unordered_map<long long, int>. We keep int to match the original
 *   arithmetic on this sample; the idea is identical.
 *
 *   Map keys are prefix values, which may be negative. That is fine
 *   for a hash table and illegal for a counting array of size max+1.
 *   This is the example HashingIntro warned you about.
 *
 *   Cache: unordered_map lookups are pointer chasing in heap nodes.
 *   For competitive n (10^5) it is the right trade. For tiny n a
 *   nested loop over a prefix array can be faster because the prefix
 *   array is contiguous. Reason about n, then measure if it matters.
 *
 *   The seed (0, 1) is not a hack. It is the prefix of the empty
 *   head. Forgetting it undercounts every subarray that starts at 0.
 *
 * Print only the count. No debug dump of the map.
 * Sample prints 3.
 */

#include <iostream>
#include <unordered_map>
using namespace std;

typedef unordered_map<int, int> Freq;

int findSubarraySum(int arr[], int n, int sum) {
    Freq prevSum;
    prevSum[0] = 1;
    int res = 0;
    int currSum = 0;
    for (int i = 0; i < n; i++) {
        currSum += arr[i];
        int removeSum = currSum - sum;
        if (prevSum.count(removeSum)) {
            res += prevSum[removeSum];
        }
        prevSum[currSum]++;
    }
    return res;
}

int main() {
    int arr[] = {10, 2, -2, -20, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = -10;
    cout << findSubarraySum(arr, n, k) << "\n";
    return 0;
}
