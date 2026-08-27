/*
 * LECȚIE — Un element vârf: urci panta cu căutare binară
 *
 * Studentule, un vârf e un indice i unde nums[i] e strict mai mare decât vecinii
 * (și mai mare decât singurul vecin pe care îl are, dacă i e un capăt).
 * Întoarce orice indice de vârf. Exemplul {2,3,4,7,9,10,11,12,5,4,3,1}:
 * indicele 7 ține 12, vârful unic al acestei urcări-și-căderi unimodale.
 *
 * Intuiție
 *   Uită-te la nums[m] versus nums[m+1].
 *     Dacă nums[m] < nums[m+1], ești pe o pantă în sus. Există un
 *     vârf la dreapta (tabloul nu poate urca la nesfârșit; chiar dacă
 *     o face până la capăt, ultimul indice e vârf prin definiție).
 *     Pune l = m + 1.
 *     Dacă nums[m] >= nums[m+1], ești pe o pantă în jos sau pe un
 *     vârf. Există un vârf la m sau la stânga lui. Pune r = m.
 *   Bucla e while (l < r). Când se întâlnesc, indicele ăla e un vârf.
 *
 *   Nu cauți o valoare. Cauți un maxim local al unui șir urmând
 *   derivata discretă. Pe un tablou unimodal e un singur vârf; pe
 *   unul oarecare e cel puțin unul (maximul global e un vârf) și
 *   plimbarea asta găsește un vârf local, nu neapărat maximul global.
 *
 * Complexitate
 *   Timp O(log n), memorie extra O(1). O parcurgere liniară găsește
 *   și ea un vârf (chiar maximul global) în O(n). Căutarea binară e
 *   punctul exercițiului: predicatul „panta de aici merge la dreapta”
 *   taie intervalul de indici în două.
 *
 * Memorie
 *   int nums[], int n. Doi indici. Fără buffer extra. Întorci un
 *   indice în tabloul apelantului; apelantul îl deține deja.
 *   nums a decăzut la int*. n a venit din sizeof în main.
 *
 * Teorie C — vecini la capăt, overflow, urcare unimodală
 *   Bucla e l < r, deci m = l + (r - l) / 2 satisface m < r, deci
 *   m + 1 <= r < n. nums[m+1] e în interval. Dacă ai folosi l <= r
 *   ai ajunge la m == n-1 și nums[m+1] ar fi UB. Forma buclei e
 *   verificarea de limite.
 *
 *   Capetele sunt vârfuri prin definiție dacă bat singurul vecin.
 *   Nu tratăm special indicele 0 sau n-1; regula pantei plus un
 *   interval care se strânge aterizează pe ele când sunt vârfuri.
 *
 *   Overflow la mid: l + (r - l) / 2, niciodată (l + r) / 2.
 *
 *   Cache: load-uri logaritmice pe perechi vecine. nums[m] și
 *   nums[m+1] sunt vecini: o linie. Apoi sari la un alt m. Același
 *   tipar de acces aleator ca la căutarea binară.
 *
 * Exemplul afișează 7. Nu afișăm l și r pe parcurs.
 */

#include <iostream>
using namespace std;

int findPeakElement(int nums[], int n) {
    int l = 0;
    int r = n - 1;
    while (l < r) {
        int m = l + (r - l) / 2;
        if (nums[m] < nums[m + 1]) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    return r;
}

int main() {
    int nums[] = {2, 3, 4, 7, 9, 10, 11, 12, 5, 4, 3, 1};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << findPeakElement(nums, n) << "\n";
    return 0;
}
