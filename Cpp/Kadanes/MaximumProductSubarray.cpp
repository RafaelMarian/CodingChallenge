/*
 * LESSON — Maximum product subarray: two directions, zeros as walls
 *
 * Student, return the maximum product of any contiguous subarray.
 * Products grow (and change sign) in a way sums do not, so Kadane's
 * "reset when negative" is the wrong move. A negative prefix can
 * become the best answer the moment you multiply by another negative.
 *
 * Intuition
 *   Three facts govern every product-subarray:
 *
 *   1. Zeros split the array. A 0 is a wall: the product through a 0
 *      is 0, and the next non-zero starts a fresh segment. We reset
 *      the running product to 1 after a 0 (in this code: if the
 *      running product is 0 at the top of the next iteration, set it
 *      to 1 before multiplying).
 *
 *   2. An even count of negatives in a segment gives a positive
 *      product. An odd count leaves the overall product negative.
 *      The best slice then drops a prefix or a suffix that contains
 *      the leftover negative — whichever drop hurts less.
 *
 *   3. One left-to-right running product sees "drop a suffix." One
 *      right-to-left running product sees "drop a prefix." Together
 *      they cover both ends without an O(n) extra table. We also
 *      consider 0 itself as a candidate (a subarray [0] has product 0).
 *
 *   Sample {-2, 6, -3, -10, 0, 2}:
 *     Left-to-right running products:  -2, -12, 36, -360, 0, 2.
 *     Right-to-left:                    2, 0, -10, 30, 180, -360.
 *     The champion is 180 = 6 * (-3) * (-10). A single left-to-right
 *     pass never reports 180, because that slice does not start at
 *     index 0 of its segment. The reverse pass finds it. That is why
 *     two directions are not optional.
 *
 * Complexity
 *   Time O(n): one combined pass (or two sequential passes). Extra
 *   memory O(1): a handful of long long scalars. No extra array.
 *
 * Memory
 *   int arr[], int n: no copy of the input. leftToRight, rightToLeft,
 *   and maxProd are automatic storage. The two running products are
 *   just integers; we do not store the product arrays. Collapsing
 *   those arrays to scalars is the same lesson as Kadane. arr decayed
 *   to a pointer; n is the length.
 *
 * C theory — long long, overflow, zeros, and cache
 *   Products overflow int almost immediately. 10 modest factors can
 *   leave 32-bit range. We accumulate in long long (at least 64-bit).
 *   Signed overflow of long long is still UB; the sample fits. If
 *   products may hit 2^63, you need a bigger strategy (big integers,
 *   or a problem constraint that forbids it).
 *
 *   Reset on 0 is a control-flow decision, not a memory one. After
 *   multiplying by 0 the running product is 0; we record it (0 can
 *   be the answer if everything else is negative), then restore 1
 *   so the next factor starts a new segment rather than staying 0
 *   forever (0 * x == 0, which would hide every later slice).
 *
 *   Indexing from both ends in one loop: arr[i] and arr[n-1-i]. Both
 *   are valid as long as i is in [0, n). The two streams walk toward
 *   each other. Cache: two sequential scans of a contiguous buffer.
 *   Fine. Do not allocate two product arrays of length n unless you
 *   need them for a proof; the scalars suffice.
 *
 *   INT_MIN as a factor: negating INT_MIN in 32-bit is UB, but we
 *   multiply into long long, so promote first. arr[i] converts to
 *   long long on *= with a long long left operand.
 *
 * Sample prints 180.
 */

#include <climits>
#include <iostream>
using namespace std;

long long maxProduct(int arr[], int n) {
    long long maxProd = LLONG_MIN;
    long long leftToRight = 1;
    long long rightToLeft = 1;
    for (int i = 0; i < n; i++) {
        if (leftToRight == 0) {
            leftToRight = 1;
        }
        if (rightToLeft == 0) {
            rightToLeft = 1;
        }
        leftToRight *= arr[i];
        int j = n - i - 1;
        rightToLeft *= arr[j];
        if (leftToRight > maxProd) {
            maxProd = leftToRight;
        }
        if (rightToLeft > maxProd) {
            maxProd = rightToLeft;
        }
    }
    return maxProd;
}

int main() {
    int arr[] = {-2, 6, -3, -10, 0, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << maxProduct(arr, n) << "\n";
    return 0;
}
