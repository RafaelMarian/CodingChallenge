/*
 * LECȚIE — Lideri de la stânga („bătrânul din stânga”)
 *
 * Problemă
 *   Parcurge de la stânga la dreapta. Emite o valoare dacă e strict mai mare
 *   decât orice valoare văzută până acum (un maxim stânga-dreapta). Exemplu:
 *   [7,5,4,11,3,8,13,2,16,9] -> 7 11 13 16
 *
 * Intuiție
 *   Un max curent. Dacă nums[i] > maxSoFar, e un lider; actualizează maxSoFar.
 *
 * Memorie
 *   Dimensiunea răspunsului e între 1 și n (prefixe unice strict crescătoare).
 *   Scriem liderii într-un tablou de ieșire furnizat de apelant
 *   `int out[]` și întoarcem câți am scris. Apelantul dimensionează `out` la
 *   n (cazul cel mai rău: un tablou strict crescător). Nu folosim vector
 *   aici; ăsta e un tablou C.
 *
 * Teorie C
 *   `int nums[]` decade la un pointer, deci TREBUIE să transmiți n. La fel
 *   e și `out[]`: e doar un pointer la stocarea pe care o deține apelantul.
 *   Să întorci un count (nu un buffer nou) e felul C de a da înapoi un
 *   rezultat de lungime variabilă, fără alocare.
 *
 * Complexitate: O(n) timp, O(k) spațiu extra pentru k lideri (aici, out[0..k)).
 */

#include <climits>
#include <iostream>
using namespace std;

int leftElder(int nums[], int n, int out[]) {
    int maxSoFar = INT_MIN;
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (nums[i] > maxSoFar) {
            maxSoFar = nums[i];
            out[count] = nums[i];
            count++;
        }
    }
    return count;
}

int main() {
    int nums[] = {7, 5, 4, 11, 3, 8, 13, 2, 16, 9};
    int n = sizeof(nums) / sizeof(nums[0]);
    int out[10];
    int k = leftElder(nums, n, out);
    for (int i = 0; i < k; i++) {
        cout << out[i] << " ";
    }
    cout << "\n";
    return 0;
}
