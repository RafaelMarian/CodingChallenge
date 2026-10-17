/*
 * LECȚIE — Numărul natural lipsă prin Gauss, și capcana de overflow
 *
 * Problemă
 *   Tabloul ține n întregi distincți din 1..n+1, cu exact unul lipsă.
 *   Întoarce valoarea lipsă.
 *
 * Intuiție (Gauss)
 *   Sum(1..n+1) = (n+1)*(n+2)/2. Scade fiecare element prezent. Ce
 *   rămâne e gaura. O parcurgere, fără set extra.
 *
 * Memorie
 *   Un acumulator întreg. Contrast cu un tablou boolean[n+2] de marcaje
 *   (O(n) extra) sau un hash set. `int nums[]` decade la un pointer, deci
 *   TREBUIE să transmiți n. Nu folosim vector aici; ăsta e un tablou C.
 *
 * Teorie C — ASTA e lecția de overflow
 *   Overflow-ul signed al lui `int` e comportament nedefinit. Pentru n în
 *   jur de 50_000, (n+1)*(n+2) depășește deja 2^31-1. Wrap-ul unsigned e
 *   definit; wrap-ul signed nu e. Niciodată „lasă-l să facă overflow și
 *   speră.”
 *
 *   Greșit:  int sum = (n + 1) * (n + 2) / 2;
 *   Corect:  long long sum = 1LL * (n + 1) * (n + 2) / 2;
 *
 *   1LL forțează aritmetică pe 64 de biți înainte de înmulțire. Împărțirea
 *   la 2 e exactă pentru că produsul a doi întregi consecutivi e par.
 *
 *   Trick-ul XOR (temă opțională): xor pe toți din 1..n+1 și xor pe toate
 *   valorile din tablou. Rămâne numărul lipsă. Fără overflow deloc, tot
 *   O(1) memorie extra. Inginerii aleg XOR când intervalul e un set complet
 *   de id-uri și nu vor un acumulator lat.
 *
 * Complexitate: O(n) timp, O(1) spațiu extra.
 */

#include <iostream>
using namespace std;

int missingNumber(int nums[], int n) {
    long long sum = 1LL * (n + 1) * (n + 2) / 2;
    for (int i = 0; i < n; i++) {
        sum -= nums[i];
    }
    return sum;
}

int main() {
    int nums[] = {8, 5, 3, 1, 9, 4, 7, 10, 2};  // lipsește 6
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << missingNumber(nums, n) << "\n";
    return 0;
}
