/*
 * LESSON — Boats to save people
 *
 * Student, each boat carries at most two people and at most `limit`
 * total weight. Greedy pairing of the lightest remaining person with
 * the heaviest remaining person is optimal, and two pointers after a
 * sort implement that greedy in linear extra time.
 *
 * Problem
 *   people[i] is a weight. Count the minimum number of boats. Sample:
 *   {4,2,8,3,1,6,2,5}, limit 8, answer 5.
 *
 * Algorithm intuition
 *   Sort non-decreasing. i is the lightest unused, j the heaviest
 *   unused. The heaviest person always needs a boat. If the lightest
 *   can share that boat (people[i] + people[j] <= limit), take both;
 *   otherwise the heaviest goes alone. In both cases consume j. Only
 *   the share case consumes i. Repeat until i > j.
 *
 *   Why this is optimal: the heaviest person cannot share with anyone
 *   heavier (there is no one heavier). If they cannot share with the
 *   current lightest, they cannot share with anyone. If they can, you
 *   should pair them with someone, and pairing with the lightest
 *   leaves the medium weights for other pairings. Sending the
 *   heaviest alone when a pair was possible wastes a seat that the
 *   lightest might not need later — actually the proof is: giving
 *   the heaviest the lightest partner (when feasible) never hurts
 *   because that lightest was the most likely to fit.
 *
 *   When i == j, one person remains. The code still counts one boat.
 *   people[i] + people[j] is then twice that person; if that happens
 *   to be <= limit you still only increment once and move both
 *   pointers, which is one boat for one person. Correct, if a little
 *   accidental. The else branch also counts one boat and decrements
 *   j, leaving i > j. Also correct. Do not "pair" two copies of the
 *   last person onto two seats of one boat as if they were two people.
 *
 * Complexity
 *   Time  O(n log n) from sort, then O(n) pairing.
 *   Extra space O(1) besides sort's stack, if we sort in place.
 *
 * Memory management
 *   int people[] decays to a pointer. sort(people, people+n) sorts the
 *   caller's buffer. The original order of people is lost. If you
 *   needed it, copy first. The function allocates no second people
 *   array. We avoid vector on purpose. Two indices and a counter on
 *   the stack.
 *
 * C theory — sort, overflow of the pair sum, cache, UB
 *   people[i] + people[j] as int can overflow. A weight of INT_MAX
 *   plus anything positive is UB in signed addition. Compare with
 *     1LL * people[i] + people[j] <= limit
 *   promoting limit to long long. The sample is nowhere near that.
 *
 *   sort permutes the n ints with O(n log n) assignments. Afterward
 *   the two-pointer pass is sequential from both ends: good cache
 *   behavior on the sorted array. The sort itself has worse locality;
 *   it is still the right tool.
 *
 *   i and j as int, loop while i <= j. When they are equal, both
 *   index a live cell. After j-- from 0, j becomes -1. The condition
 *   is checked at the top: if i was 0 and j was 0, we process, j
 *   becomes -1, and i <= j is 0 <= -1, which is false. Signed is the
 *   natural fit for a shrinking high index that can pass zero.
 *
 *   Empty: 0 boats. We return 0 without n-1.
 *
 *   In-place mutation: sort. The pairing does not need further
 *   writes.
 */

#include <algorithm>
#include <iostream>
using namespace std;

int numRescueBoats(int people[], int n, int limit) {
    if (n == 0) {
        return 0;
    }
    sort(people, people + n);
    int i = 0;
    int j = n - 1;
    int boats = 0;
    long long cap = limit;
    while (i <= j) {
        if (1LL * people[i] + people[j] <= cap) {
            i++;
        }
        boats++;
        j--;
    }
    return boats;
}

int main() {
    int arr[] = {4, 2, 8, 3, 1, 6, 2, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << numRescueBoats(arr, n, 8) << '\n';
    return 0;
}
