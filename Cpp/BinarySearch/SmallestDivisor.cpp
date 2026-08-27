/*
 * LECȚIE — Căutare binară pe răspuns: cel mai mic divisor
 *
 * Studentule, ai nums pozitive și un threshold; găsește cel mai mic întreg
 * pozitiv d astfel încât suma lui ceil(nums[i] / d) peste i
 * e <= threshold. Exemplul {1,3,6,11}, threshold 7. Răspunsul e 4:
 *   d=3 -> ceil(1/3)+ceil(3/3)+ceil(6/3)+ceil(11/3) = 1+1+2+4 = 8 > 7
 *   d=4 -> 1+1+2+3 = 7 <= 7
 *
 * Intuiție
 *   Regiunea fezabilă e monotonă în d. Un d mai mare face fiecare
 *   ceil(nums[i]/d) mai mic sau egal, deci suma nu crește niciodată.
 *   Există un cel mai mic d care merge, și fiecare d deasupra lui
 *   merge și el. Căutare binară pe tăietura aia pe linia numerelor
 *   de divisori posibili: 1 .. max(nums) (pentru că d >= max(nums)
 *   dă o sumă de n, și dacă nici aia nu trece de threshold problema
 *   e imposibilă; exemplul e posibil).
 *
 *   Nu cauți în nums. Cauți răspunsul însuși. Tabloul e folosit doar
 *   ca să evaluezi predicatul „candidatul ăsta d trece threshold?”
 *
 * ceil pe întregi, fără virgulă mobilă
 *   ceil(a / d) pentru a, d pozitive e (a + d - 1) / d în împărțire
 *   întreagă. Alternativ (a - 1) / d + 1, care evită să aduni
 *   a + d - 1 (adunarea aia poate da overflow pe int). Folosim forma
 *   (a + d - 1) / d pe exemplul ăsta mic și menționăm overflow-ul
 *   la teorie.
 *
 * Complexitate
 *   Intervalul de căutare e 1..U cu U = max(nums), O(log U) teste
 *   de candidat. Fiecare test e O(n). Total O(n log U). Memorie
 *   extra O(1).
 *
 * Memorie
 *   int nums[], int n. Doar locale. Fără buffer extra. „Spațiul de
 *   căutare” sunt întregi în registre, nu un tabel alocat de
 *   divisori. Parcurgem tabloul apelantului; nu-l copiem.
 *
 * Teorie C — predicate monotone, împărțire întreagă, overflow, cache
 *   Căutarea binară merge pe orice predicat monoton peste un domeniu
 *   total ordonat, nu doar pe tablouri sortate. Domeniul aici e
 *   {1,2,...,U}. Accesul aleator e „pune d în sumă”, care e lucru
 *   O(n), nu O(1). Factorul log tot se aplică lui U.
 *
 *   Împărțirea întreagă trunchiază spre zero. Pentru pozitive ăsta
 *   e floor. Bump-ul + (d-1) îl face ceil. Nu scrie niciodată
 *   (int)ceil((double)a / d) pentru asta: virgula mobilă nu poate
 *   reprezenta orice întreg, și ai importa bug-uri de rotunjire.
 *
 *   (a + d - 1) poate da overflow pe int înainte de împărțire.
 *   Overflow-ul pe signed e UB. Forma sigură pentru a >= 1, d >= 1:
 *   1 + (a - 1) / d. Pe exemplul ăsta a și d sunt mici. Codul de
 *   producție folosește forma sigură sau long long.
 *
 *   Suma interioară sum += dă și ea overflow dacă n e uriaș și d
 *   e 1. long long pe acumulator e obiceiul. Exemplul încape în int.
 *
 *   Cache: fiecare evaluare de predicat e o parcurgere secvențială
 *   a lui nums, localitate excelentă, de log U ori. E în regulă.
 *
 *   mid = l + (h - l) / 2. Bucla while (l < h), pune h = m la succes
 *   (include m: poate fi cel mai mic), l = m + 1 la eșec.
 *   Întoarce l. Ăsta e lower_bound pe predicat.
 *
 * Exemplul afișează 4.
 */

#include <climits>
#include <iostream>
using namespace std;

int smallestDivisor(int nums[], int n, int threshold) {
    int mx = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (nums[i] > mx) {
            mx = nums[i];
        }
    }
    int l = 1;
    int h = mx;
    while (l < h) {
        int m = l + (h - l) / 2;
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += (nums[i] + m - 1) / m;
        }
        if (sum <= threshold) {
            h = m;
        } else {
            l = m + 1;
        }
    }
    return l;
}

int main() {
    int nums[] = {1, 3, 6, 11};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << smallestDivisor(nums, n, 7) << "\n";
    return 0;
}
