/*
 * LECȚIE — Rotație la stânga cu un loc (deplasarea care te învață mutația)
 *
 * Problemă
 *   Mută fiecare element un indice la stânga. Capul original devine coada.
 *   [1,2,3,4] -> [2,3,4,1]
 *
 * Intuiție
 *   Salvează nums[0]. Glisează totul la stânga prin atribuire. Pune valoarea
 *   salvată în ultimul loc. Un int temporar.
 *
 * Memorie
 *   Asta e in-place. Suprascriem celule `int` contigue. Adresa buffer-ului
 *   nu se schimbă. `int arr[]` decade la un pointer, deci TREBUIE să
 *   transmiți n.
 *
 *   Cost: O(n) atribuiri. Nu există o rotație-cu-unul in-place mai ieftină;
 *   fiecare valoare trebuie să se mute.
 *
 * Teorie C — memmove
 *   Bucla e exact ce face memmove(dst, src, bytes) pentru regiuni care se
 *   suprapun. În C ai scrie:
 *     int tmp = a[0];
 *     memmove(a, a+1, (n-1)*sizeof(int));
 *     a[n-1] = tmp;
 *   memmove are voie să se suprapună; memcpy nu (UB dacă se suprapun).
 *   Știi diferența. Păstrăm bucla explicită ca să vezi fiecare scriere.
 *
 * Complexitate: O(n) timp, O(1) spațiu extra.
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
