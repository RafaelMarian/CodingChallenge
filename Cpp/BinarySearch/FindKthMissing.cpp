/*
 * LECȚIE — Al k-lea pozitiv lipsă, prin căutare binară pe numărul de goluri
 *
 * Studentule, arr e un șir strict crescător de int pozitivi, conceptual începând
 * de la 1 ca primul natural care ar putea lipsi. Întoarce al k-lea
 * întreg pozitiv care nu apare în arr. Exemplul {2,3,4,7,11}, k = 1:
 * pozitivele lipsă sunt 1, 5, 6, 8, 9, 10, ... deci primul e 1.
 *
 * Intuiție
 *   La indicele mid, valoarea arr[mid] „ar fi trebuit” să fie mid+1
 *   dacă tabloul era 1,2,3,... fără nimic lipsă. Numărul de pozitive
 *   lipsă strict înainte de acest loc (printre 1..arr[mid]) e
 *
 *       totMissing = arr[mid] - (mid + 1)
 *
 *   Exemplu: arr[0] = 2, totMissing = 2 - 1 = 1 (lipsește 1).
 *   arr[3] = 7, totMissing = 7 - 4 = 3 (lipsesc 1,5,6).
 *
 *   Dacă totMissing < k, al k-lea lipsă e la dreapta lui mid:
 *   low = mid + 1. Altfel e la mid sau la stânga:
 *   high = mid - 1.
 *
 *   După buclă, high e ultimul indice cu totMissing < k
 *   (sau -1 dacă și indicele 0 are destule lipsă). Câte numere am
 *   „consumat” de pe linia 1..infinit? Avem high+1 elemente din
 *   tablou înainte de răspuns, deci al k-lea lipsă e
 *
 *       k + high + 1
 *
 *   Pe exemplu, high devine -1, întorci 1 + (-1) + 1 = 1.
 *
 * Complexitate
 *   Timp O(log n), memorie extra O(1). O parcurgere liniară care
 *   incrementează k ori de câte ori arr[i] <= k e O(n) și tot
 *   corectă; lecția e căutarea binară.
 *
 * Memorie
 *   int arr[], int n. Câțiva int. Fără buffer extra. Nu materializezi
 *   niciodată numerele lipsă. arr a decăzut la un pointer.
 *
 * Teorie C — cauți un numărător, nu o valoare; overflow
 *   E căutare binară pe un predicat monoton implicit: „sunt mai
 *   puține de k lipsă înainte de indicele mid?” Tabloul e structura
 *   cu acces aleator care îți lasă să evaluezi predicatul în O(1).
 *   Nu cauți k în arr; k poate să nu apară deloc.
 *
 *   arr[mid] - (mid + 1) poate, teoretic, da underflow dacă arr n-ar
 *   fi strict crescător de pozitive. Precondiția îl ține nenegativ.
 *   Underflow pe signed al unui rezultat negativ e doar un int
 *   negativ aici (bine definit dacă nu trece de INT_MIN); un input
 *   stricat ți-ar da pur și simplu un răspuns greșit.
 *
 *   Întorci k + high + 1: high poate fi -1, deci asta e k. high poate
 *   fi n-1, deci răspunsul poate sta după capătul tabloului (mai
 *   multe lipsă după ultimul element). Adunarea e aritmetică obișnuită
 *   pe int; pentru k uriaș folosește long long.
 *
 *   mid = (low + high) / 2 e pericolul de overflow. Scriem
 *   low + (high - low) / 2.
 *
 * Exemplul afișează 1.
 */

#include <iostream>
using namespace std;

int findKthPositive(int arr[], int n, int k) {
    int low = 0;
    int high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int totMissing = arr[mid] - (mid + 1);
        if (totMissing < k) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return k + high + 1;
}

int main() {
    int nums[] = {2, 3, 4, 7, 11};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << findKthPositive(nums, n, 1) << "\n";
    return 0;
}
