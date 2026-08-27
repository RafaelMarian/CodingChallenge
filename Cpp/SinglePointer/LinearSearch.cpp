/*
 * LECȚIE — Căutare liniară (baza cu care se măsoară orice altă căutare)
 *
 * Problemă
 *   Dat un tablou neordonat, întoarce indicele lui `key`, sau -1 dacă lipsește.
 *
 * De ce e prima
 *   Înainte de căutare binară, hashing sau doi pointeri, trebuie să fii
 *   cinstit cu scanarea naivă. E O(n) timp și O(1) memorie extra. Pe un
 *   cache rece tot e cea mai rapidă cale să cauți într-un tablou *mic*,
 *   pentru că nu există pregătire extra. Pe un tablou mare neordonat e
 *   *singura* metodă generală corectă, decât dacă construiești un index.
 *
 * Memorie
 *   Nu folosim vector aici; ăsta e un tablou C. `int nums[]` într-un
 *   parametru de funcție *nu* e un tablou. Decade la `int *` — un pointer
 *   la primul element. Pointerul nu stochează lungimea, deci TREBUIE să
 *   transmiți `n` tu însuți. În main, `sizeof(nums) / sizeof(nums[0])`
 *   funcționează doar cât `nums` e încă un tablou adevărat (încă n-a
 *   făcut decay).
 *
 * Teorie C
 *   `int search(int nums[], int n, int key)` e interfața după decay:
 *   un pointer la primul int, plus o lungime. `nums[i]` e `*(nums + i)`.
 *   Transmiterea tabloului nu copiază buffer-ul; transmite o singură adresă.
 *
 * Complexitate: O(n) timp, O(1) spațiu extra.
 */

#include <iostream>
using namespace std;

int search(int nums[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (nums[i] == key)
            return i;
    }
    return -1;
}

int main() {
    int nums[] = {8, 3, 10, 5, 7, 1, 9, 6, 4, 2};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << search(nums, n, 9) << "\n";  // 6
    return 0;
}
