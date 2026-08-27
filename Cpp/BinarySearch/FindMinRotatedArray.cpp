/*
 * LECȚIE — Minimul unui tablou sortat rotit (elemente unice)
 *
 * Studentule, tabloul e sortat crescător, apoi rotit. Toate valorile distincte.
 * Întoarce minimul. Exemplul {10,11,12,13,3,4,5,6,7}: tăietura e
 * între 13 și 3, deci min e 3.
 *
 * Intuiție
 *   Într-un tablou nerotit, nums[h] e cel mai mare din intervalul
 *   rămas, iar nums[0] e min. După o rotație, minimul e primul
 *   element al bucății sortate din dreapta — valoarea mai mică
 *   decât vecinul din stânga, dacă are unul.
 *
 *   Sondează mid.
 *     Dacă mid != 0 și nums[mid] < nums[mid-1], mid e punctul de
 *     rotație: întoarce nums[mid]. Ăsta e min.
 *     Dacă mid == 0, n-ai vecin stânga. Nu citi nums[-1]. Load-ul
 *     ăla e UB. Cazi în testul pe jumătăți.
 *
 *   Testul pe jumătăți: dacă nums[h] > nums[mid], dreapta de la mid
 *   la h e crescătoare, deci min e în bucata stângă *inclusiv* mid
 *   (mid încă poate fi min dacă ai sărit testul pe vecin). Pune
 *   h = mid. Altfel cusătura e la dreapta lui mid (nums[mid] stă
 *   în bucata mare din stânga): pune l = mid + 1.
 *
 *   Bucla e while (l < h) ca intervalul să se strângă. Când l == h
 *   ții min.
 *
 * Complexitate
 *   Timp O(log n), memorie extra O(1). Distincția ține testul pe
 *   jumătăți cinstit. Duplicatele ar forța cazul cel mai rău liniar,
 *   ca în lecția de căutare rotită cu duplicate.
 *
 * Memorie
 *   int nums[], int n. Doi sau trei int. Fără tablou extra. Întorci
 *   o valoare, nu un indice, deci apelantul nu indexează niciodată
 *   cu internalele tale. nums a decăzut la un pointer; n e lungimea.
 *
 * Teorie C — acces la vecin, overflow, rotație
 *   Garda mid != 0 e o verificare de limite. C n-o face pentru tine.
 *   nums[mid - 1] cu mid == 0 citește înainte de buffer: UB, un
 *   segfault posibil sau un load tăcut dintr-un registru salvat în
 *   cadru. Scrie garda de fiecare dată când te uiți la stânga.
 *
 *   mid = l + (h - l) / 2. Includerea lui mid la stânga (h = mid) e
 *   sigură cu while (l < h): dacă ai scrie h = mid - 1 ai putea
 *   pierde min, decât dacă testul pe vecin l-a întors deja.
 *
 *   Input nerotit: nums[h] > nums[mid] mereu pe un interval strict
 *   crescător, h se strânge spre 0, răspuns nums[0]. Bine.
 *
 *   Cache: load-uri aleatoare logaritmice într-un buffer contig.
 *   La fel ca la căutarea binară. Pentru n = 9 e academic; pentru
 *   n = 10^7 de-asta nu parcurgi liniar.
 *
 * Exemplul afișează 3.
 */

#include <iostream>
using namespace std;

int findMin(int nums[], int n) {
    int l = 0;
    int h = n - 1;
    while (l < h) {
        int mid = l + (h - l) / 2;
        if (mid != 0 && nums[mid] < nums[mid - 1]) {
            return nums[mid];
        }
        if (nums[h] > nums[mid]) {
            h = mid;
        } else {
            l = mid + 1;
        }
    }
    return nums[l];
}

int main() {
    int nums[] = {10, 11, 12, 13, 3, 4, 5, 6, 7};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << findMin(nums, n) << "\n";
    return 0;
}
