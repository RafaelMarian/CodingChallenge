/*
 * LECȚIE — Maximul unui tablou, și de ce INT_MIN e o constantă cu capcană
 *
 * Problemă
 *   Întoarce cea mai mare valoare din tablou.
 *
 * Intuiție
 *   Ține un campion curent. Compară fiecare element cu el. O singură parcurgere.
 *
 * Memorie
 *   Trei cuvinte de mașină pe lângă input: indicele, valoarea curentă
 *   (adesea într-un registru) și campionul. Fără heap. `int nums[]` decade
 *   la un pointer, deci TREBUIE să transmiți n.
 *
 * Teorie C — sentinele
 *   INT_MIN din <climits> e -2^31 pe mașina asta. Să-l folosești ca
 *   prim campion e corect *doar dacă* fiecare element e >= INT_MIN,
 *   ceea ce e mereu adevărat pentru int. E *greșit* dacă mai târziu vrei
 *   „încă n-am văzut niciun element” ca stare distinctă (tablou gol):
 *   INT_MIN e o valoare validă, deci nu poți distinge „gol” de „maximul
 *   chiar e INT_MIN”.
 *
 *   Tiparul profesionist pentru un tablou nevid: inițializează max cu nums[0]
 *   și pornește bucla de la 1. Atunci tablourile goale sunt o eroare explicită,
 *   nu o minciună tăcută.
 *
 * Complexitate: O(n) timp, O(1) spațiu extra.
 */

#include <climits>
#include <iostream>
using namespace std;

int getMax(int nums[], int n) {
    int maxVal = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (nums[i] > maxVal)
            maxVal = nums[i];
    }
    return maxVal;
}

int main() {
    int nums[] = {7, 5, 4, 16, 3, 9, 11, 13, 12, 8};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << getMax(nums, n) << "\n";  // 16
    return 0;
}
