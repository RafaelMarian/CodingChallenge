/*
 * LECȚIE — Minimizează suma maximă a perechilor
 *
 * Studentule, trebuie să împerechezi 2n numere în n perechi. Costul
 * unei împerecheri e maximul sumelor perechilor. Vrei costul ăla cât
 * mai mic. Să împerechezi cel mai mic curent cu cel mai mare curent
 * e structura unică a optimumului.
 *
 * Problemă
 *   Tablou de lungime pară. Împerechează fiecare element cu exact unul
 *   altul. Minimizează maximul lui (a + b) peste perechile alea.
 *   Exemplu: {2,6,3,4,7,11,5,8} tipărește 13, din perechea 2+11 (celelalte
 *   perechi 3+8, 4+7, 5+6 sunt toate 11).
 *
 * Intuiție / Algoritm
 *   Sortează. Împerechează nums[0] cu nums[n-1], nums[1] cu nums[n-2],
 *   și tot așa. Ține maximul acelor n/2 sume. Întoarce maximul ăla.
 *
 *   De ce să nu împerechezi mare cu mare: 11+8 = 19, mai rău. De ce să
 *   nu împerechezi mic cu mic: atunci trebuie să împerechezi 11 cu ceva
 *   mediu ca 7, tot 18, și ai irosit valorile mici una pe alta, unde
 *   ar fi putut neutraliza giganții. Extremele sortate echilibrează
 *   sumele. Orice inversiune (o valoare mai mică de pe partea mare
 *   schimbată cu una mai mare) crește suma perechii mai mari sau o
 *   lasă egală; maximul nu se îmbunătățește.
 *
 *   E aceeași plimbare cu doi pointeri ca la reverse: i++, j--, dar
 *   aduni în loc să faci swap, și ții un max care rulează.
 *
 * Complexitate
 *   Timp  O(n log n) sort plus O(n) împerechere.
 *   Memorie extra O(1) extra pe lângă sort, dacă sortăm pe loc.
 *
 * Memorie
 *   int nums[] decade la un pointer. sort(nums, nums+n) permutează
 *   cele n celule existente. Nicio listă de perechi nu e stocată. Nu
 *   alocăm n/2 obiecte pair. Output-ul e un întreg. Evităm vector
 *   dinadins. Dacă ai materializa perechile, ai cheltui O(n) cuvinte
 *   extra fără câștig în API-ul ăsta.
 *
 * Teorie C — împerecherea extremelor, overflow, n par, cache, UB
 *   nums[i] + nums[j] overflow: aceeași regulă ca întotdeauna.
 *   1LL * nums[i] + nums[j], ține max-ul ca long long. INT_MAX+INT_MAX
 *   încape pe signed pe 64 de biți. Să întorci int e valid doar dacă
 *   răspunsul încape; exemplul încape.
 *
 *   Lungimea impară nu e o împerechere a tuturor. Problema garantează
 *   n par. Dacă n ar fi impar, un element ar rămâne; specificația ar
 *   trebui să spună dacă stă ca o „pereche” singleton. Nu ghicim.
 *   n < 2: întoarce 0.
 *
 *   i < j cu indici signed: pentru că ne oprim la i < j, când n e par
 *   procesăm n/2 perechi și i se întâlnește cu j la mijloc fără o
 *   celulă rămasă. Pornește j = n-1 doar dacă n > 0.
 *
 *   sort: pe loc, introsort, O(log n) stivă. După aia împerecherea
 *   citește secvențial de la ambele capete. Două fluxuri, ca la reverse,
 *   dar valorile sunt doar încărcate, nu prin swap (tabloul e deja în
 *   ordinea de care avem nevoie). Am putea sări scrierea; am scris
 *   deja în timpul lui sort.
 *
 *   Mutația pe loc e sort-ul, nu împerecherea. Împerecherea e doar
 *   citire pe permutarea sortată.
 *
 *   Cache-ul după sort e excelent. Nu pune numerele într-o listă de
 *   noduri doar ca să le împerechezi.
 *
 *   Formă C: qsort tabloul, apoi aceeași buclă i/j. Comparatorul lui
 *   qsort nu trebuie să dea overflow într-un compare-by-subtraction;
 *   folosește (a > b) - (a < b) sau un if pe trei căi. sort cu
 *   operator< pe int nu scade.
 */

#include <algorithm>
#include <iostream>
using namespace std;

int minPairSum(int nums[], int n) {
    if (n < 2) {
        return 0;
    }
    sort(nums, nums + n);
    int i = 0;
    int j = n - 1;
    long long best = 0;
    while (i < j) {
        long long s = 1LL * nums[i] + nums[j];
        if (s > best) {
            best = s;
        }
        i++;
        j--;
    }
    return best;
}

int main() {
    int nums[] = {2, 6, 3, 4, 7, 11, 5, 8};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << minPairSum(nums, n) << '\n';
    return 0;
}
