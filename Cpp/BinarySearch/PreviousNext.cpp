/*
 * LECȚIE — Valorile anterioară și următoare în jurul unui key, tablou sortat
 *
 * Studentule, tabloul e sortat, distinct în exemplul ăsta. key poate sau nu să
 * fie prezent. Afișează doi int: predecesorul și succesorul ca
 * valoare, cu -1 când vecinul ăla nu există.
 *
 *   Dacă key e prezent la indicele i: afișează nums[i-1] (sau -1) și
 *   nums[i+1] (sau -1). Ăia sunt vecinii acelui indice.
 *   Dacă key lipsește: afișează cel mai mare element < key și cel
 *   mai mic element > key, iar -1 la capete.
 *
 * Exemplul {3,4,6,7,10,11,13,15}, key 14: 14 nu e prezent. Cel mai
 * mare de sub e 13, cel mai mic de deasupra e 15.
 *
 * Intuiție
 *   Căutare binară ca lower_bound. Dacă lovești, ai indicele.
 *   Dacă ratezi, când bucla se termină l e punctul de inserare:
 *   primul indice cu nums[l] > key (tot ce e la stânga lui l e < key).
 *   Apoi
 *     prev = (l == 0) ? -1 : nums[l - 1]
 *     next = (l == n) ? -1 : nums[l]
 *   Ăsta e tot cazul de miss. Nu reconstrui vecinii dintr-un mid
 *   vechi după ieșire; așa a crescut originalul o pădure de
 *   verificări de capăt. l e deja lower_bound.
 *
 * Complexitate
 *   Timp O(log n), memorie extra O(1).
 *
 * Memorie
 *   int nums[], int n. Scrie doi int în out[2]. Fără buffer extra.
 *   Nu inserăm key-ul lipsă; doar îi numim vecinii. Doi int, nu un
 *   tip pair. nums a decăzut la un pointer.
 *
 * Teorie C — vecini de lower_bound, capete, overflow
 *   Indicele de inserare l == n înseamnă că key e mai mare decât
 *   orice element: next e -1, prev e nums[n-1]. l == 0 înseamnă că
 *   key e mai mic decât orice element: prev e -1, next e nums[0].
 *   Ăia sunt cei doi sentineli de capăt. Folosirea lui -1 ca „fără
 *   vecin” se ciocnește cu o valoare legală -1 în tablou; exemplul
 *   e pozitiv, deci e în regulă.
 *
 *   Dacă citești nums[mid-1] când mid == 0, ăsta e UB. Ramura de
 *   hit păzește mid == 0. Ramura de miss folosește l, care poate
 *   fi 0 sau n, și păzește ambele.
 *
 *   mid = l + (h - l) / 2. Overflow-ul lui l+h tot e UB.
 *
 * Exemplul afișează 13 15.
 */

#include <iostream>
using namespace std;

void prevNext(int nums[], int n, int key, int out[]) {
    int l = 0;
    int h = n - 1;
    while (l <= h) {
        int mid = l + (h - l) / 2;
        if (key == nums[mid]) {
            out[0] = (mid == 0) ? -1 : nums[mid - 1];
            out[1] = (mid == n - 1) ? -1 : nums[mid + 1];
            return;
        }
        if (key < nums[mid]) {
            h = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    out[0] = (l == 0) ? -1 : nums[l - 1];
    out[1] = (l == n) ? -1 : nums[l];
}

int main() {
    int nums[] = {3, 4, 6, 7, 10, 11, 13, 15};
    int n = sizeof(nums) / sizeof(nums[0]);
    int out[2];
    prevNext(nums, n, 14, out);
    cout << out[0] << " " << out[1] << "\n";
    return 0;
}
