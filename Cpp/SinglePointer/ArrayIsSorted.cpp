/*
 * LECȚIE — E tabloul nedescrescător?
 *
 * Problemă
 *   Întoarce true dacă și numai dacă nums[i] <= nums[i+1] pentru fiecare
 *   pereche adiacentă.
 *
 * Intuiție
 *   Un singur pointer de la stânga la dreapta e destul. În clipa în care
 *   vezi o coborâre, poți respinge. Nu-ți trebuie o a doua parcurgere.
 *
 * Memorie
 *   Doar citire. Fără buffer extra. `int nums[]` decade la un pointer, deci
 *   TREBUIE să transmiți n. CPU-ul face prefetch pe int-uri consecutive,
 *   deci bucla e cam cât de cache-friendly poate fi o buclă.
 *
 * Teorie C — off-by-one
 *   Ultimul indice valid e n-1. Ultima *pereche* începe la n-2.
 *   Dacă scrii `i < n` și apoi citești nums[i+1], ieși din limite:
 *   comportament nedefinit. Compilatorul nu-ți datorează nimic: crash,
 *   răspuns greșit în tăcere, sau „merge pe mașina asta.” Parcurge cât
 *   `i < n - 1`, ca `i + 1` să fie mereu în interval.
 *
 * Complexitate: O(n) timp, O(1) spațiu extra.
 */

#include <iostream>
using namespace std;

bool isSorted(int nums[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (nums[i] > nums[i + 1])
            return false;
    }
    return true;
}

int main() {
    int nums[] = {2, 3, 5, 5, 6, 7, 8, 9, 12, 15};
    int n = sizeof(nums) / sizeof(nums[0]);
    bool ok = isSorted(nums, n);
    cout << "ans" << (ok ? "true" : "false") << "\n";
    return 0;
}
