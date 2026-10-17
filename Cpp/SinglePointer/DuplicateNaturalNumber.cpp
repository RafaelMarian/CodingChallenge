/*
 * LECȚIE — Duplicatul din 1..n prin aceeași identitate a lui Gauss
 *
 * Problemă
 *   Un tablou de lungime n conține 1..n-1 plus un duplicat extra (exemplul
 *   e 1..10 cu un al doilea 7, lungime 11). Suma valorilor unice e
 *   n*(n-1)/2. Copia extra e `actualSum - expectedSum`.
 *
 * Intuiție
 *   Ca la numărul lipsă, cu semnul inversat. Un acumulator.
 *
 * Memorie
 *   O(1). Un hash set ar fi soluția leneșă cu O(n) spațiu extra. Găsirea
 *   de ciclu a lui Floyd pe graful „index = value” e soluția cu O(1) spațiu
 *   extra care merge și când nu poți folosi suma (overflow, sau
 *   duplicate multiple). Învață mai întâi suma; apoi învață Floyd.
 *
 * Teorie C
 *   `int nums[]` decade la un pointer, deci TREBUIE să transmiți n. Înmulțește
 *   în long long (`1LL * n * (n - 1) / 2`) ca produsul să nu poată face
 *   overflow pe un int de 32 de biți. `actual - expected` face semnul evident.
 *
 * Complexitate: O(n) timp, O(1) spațiu extra.
 */

#include <iostream>
using namespace std;

int duplicateNumber(int nums[], int n) {
    long long expected = 1LL * n * (n - 1) / 2;  // 1 + 2 + ... + (n-1)
    long long actual = 0;
    for (int i = 0; i < n; i++) {
        actual += nums[i];
    }
    return actual - expected;
}

int main() {
    int nums[] = {8, 5, 7, 3, 6, 1, 9, 4, 7, 10, 2};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << duplicateNumber(nums, n) << "\n";  // 7
    return 0;
}
