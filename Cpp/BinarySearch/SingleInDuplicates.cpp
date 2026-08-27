/*
 * LECȚIE — Elementul singur într-un tablou sortat de perechi
 *
 * Studentule, fiecare valoare apare de două ori, alăturată, în afară de una
 * care apare o dată. Tabloul e sortat. Întoarce pe cel singur.
 * Exemplul {2,2,3,3,4,4,5,6,6,7,7} dă 5.
 *
 * Intuiție
 *   Înainte de cel singur, perechile încep la indici pari: (0,1),
 *   (2,3), ... După cel singur, tiparul se mută cu unu: perechile
 *   încep la indici impari. Căutare binară pe invariantul ăla de
 *   împerechere.
 *
 *   Forțează mid pe un indice par: dacă mid e impar, mid--. Apoi
 *   nums[mid] și nums[mid+1] ar trebui să fie o pereche dacă ești
 *   încă la stânga celui singur.
 *     Dacă diferă, cel singur e la mid sau la stânga: h = mid.
 *     Dacă se potrivesc, cel singur e la dreapta: l = mid + 2.
 *   Când l == h, indicele ăla e cel singur. Întoarce nums[h]
 *   (aceeași celulă).
 *
 * Complexitate
 *   Timp O(log n), memorie extra O(1). n e impar (2k + 1).
 *
 * Memorie
 *   int nums[], int n. Fără buffer extra. Nu scriem. Împerecherea
 *   e o observație despre indici, nu un al doilea tablou de flag-uri.
 *   Parametrul nums e un pointer; n e lungimea impară.
 *
 * Teorie C — indici pari, limite la mid+1, overflow
 *   Dacă mid e impar, decrementăm ca să aterizăm pe începutul unei
 *   perechi-ar-fi. Asta ține invariantul aliniat cu începuturi pare.
 *   Garantează și că mid + 1 e în interval cât timp l < h: ultimul
 *   indice e par (n impar => n-1 par), și când mid == h n-am intra
 *   în corp pentru că l < h a eșuat... while l < h, mid = l+(h-l)/2
 *   e mai mic decât h, deci mid+1 <= h. Sigur. Dacă buclezi l <= h
 *   trebuie să păzești mid+1 < n.
 *
 *   Să citești nums[mid+1] fără raționamentul ăla e cum ieși din
 *   capăt: UB. Desenează indicii pe hârtie o dată. nums[mid] e
 *   *(nums + mid). Cuvintele vecine sunt o pereche în memorie.
 *
 *   mid = l + (h - l) / 2. Aceeași regulă de overflow.
 *
 * Exemplul afișează 5.
 */

#include <iostream>
using namespace std;

int singleInDuplicate(int nums[], int n) {
    int l = 0;
    int h = n - 1;
    while (l < h) {
        int mid = l + (h - l) / 2;
        if (mid % 2 == 1) {
            mid--;
        }
        if (nums[mid] != nums[mid + 1]) {
            h = mid;
        } else {
            l = mid + 2;
        }
    }
    return nums[h];
}

int main() {
    int nums[] = {2, 2, 3, 3, 4, 4, 5, 6, 6, 7, 7};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << singleInDuplicate(nums, n) << "\n";
    return 0;
}
