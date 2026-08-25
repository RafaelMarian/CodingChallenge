/*
 * LESSON — Left rotate by one (the shift that teaches mutation)
 *
 * Problem
 *   Move every element one index left. The original head becomes the tail.
 *   [1,2,3,4] -> [2,3,4,1]
 *
 * Intuition
 *   Save nums[0]. Slide everything left by assignment. Put the saved
 *   value in the last slot. One temporary int.
 *
 * Memory
 *   This is in-place. We overwrite contiguous `int` cells. The buffer
 *   address does not change. `int arr[]` decays to a pointer, so you
 *   MUST pass n.
 *
 *   Cost: O(n) assignments. There is no cheaper in-place rotate-by-one;
 *   every value must move.
 *
 * C theory — memmove
 *   The loop is exactly what memmove(dst, src, bytes) does for overlapping
 *   regions. In C you would write:
 *     int tmp = a[0];
 *     memmove(a, a+1, (n-1)*sizeof(int));
 *     a[n-1] = tmp;
 *   memmove is allowed to overlap; memcpy is not (UB if they overlap).
 *   Know the difference. We keep the explicit loop so you see every write.
 *
 * Complexity: O(n) time, O(1) extra space.
 */

#include <iostream>
using namespace std;

void rotateLeft(int arr[], int n) {
    if (n == 0)
        return;
    int temp = arr[0];
    for (int i = 0; i < n - 1; i++) {
        arr[i] = arr[i + 1];
    }
    arr[n - 1] = temp;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    rotateLeft(arr, n);
    for (int i = 0; i < n; i++) {
        cout << arr[i] << "\n";
    }
    return 0;
}
