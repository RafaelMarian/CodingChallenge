/*
 * LECȚIE — Toate cvadrupletele unice care se adună la un target
 *
 * Studentule, four-sum e două bucle imbricate plus perechea sortată
 * cu doi pointeri. Munca nouă e să sari duplicatele ca fiecare
 * cvadruplet de valori să apară o dată, și să aduni patru int-uri
 * fără overflow.
 *
 * Problemă
 *   Tipărește fiecare cvadruplet unic nedescrescător (a,b,c,d) de
 *   valori din tablou (indici distincți) care se adună la target.
 *   Exemplu: {0,1,0,2,1,2,2}, target 3, tipărește linia unică 0 0 1 2.
 *
 * Intuiție / Algoritm
 *   Sortează. Fixează i, apoi j > i. Pe sufixul rămas, doi pointeri
 *   l = j+1, h = n-1 caută target - nums[i] - nums[j]. La o lovitură,
 *   tipărește cele patru valori, mută ambii pointeri, și sari valorile
 *   egale ca să nu emiți același cvadruplet din nou. La o rată, mută
 *   l sau h după testul obișnuit de sumă.
 *
 *   Sari i duplicat: dacă i > 0 și nums[i] == nums[i-1], continue.
 *   Sari j duplicat: dacă j > i+1 și nums[j] == nums[j-1], continue.
 *   După o lovitură, sari l și h duplicate la fel. Sortarea a făcut
 *   duplicatele alăturate; să le sari e O(1) amortizat per pas.
 *
 * Complexitate
 *   Timp  O(n^3): două bucle de indici imbricate și o scanare cu doi
 *   pointeri O(n).
 *   Memorie extra O(1) în afară de output-ul tipărit. Nu stocăm un
 *   tabel de cvadruplete. sort e pe loc.
 *
 * Memorie
 *   int nums[] decade la un pointer. Îl sortăm cu sort(nums, nums+n)
 *   și tipărim fiecare lovitură pe măsură ce o găsim. Fără tablouri
 *   imbricate de răspunsuri. Evităm vector dinadins: să aduni
 *   un vector de vector ar fi o alocare pe heap per cvadruplet. Tipărirea
 *   curge patru int-uri și ține memoria de lucru la o mână de indici.
 *
 * Teorie C — acumulare long long, skip, overflow, UB, cache
 *   Patru adunări de int: 4 * INT_MAX nu încape pe signed pe 32 de biți.
 *   Construiește suma ca long long, asociativ la stânga de la un termen
 *   1LL:
 *     1LL * nums[i] + nums[j] + nums[l] + nums[h]
 *   Nu scrie nums[i] + nums[j] + nums[l] + nums[h] și apoi atribuie
 *   la long long; adunările se întâmplă mai întâi pe int, ceea ce e
 *   UB la overflow. Nu scrie nici 1LL * a + b + c + d ca
 *   1LL * (a + b + c + d); parantezele forțează adunări pe int.
 *
 *   Compară cu target ca long long: (long long)target sau 0LL + target.
 *
 *   Skip-ul de duplicate folosește l > 0 logic comparând nums[l] cu
 *   nums[l-1] doar când l tocmai a fost incrementat și l < h.
 *   Citirea lui nums[l-1] e atunci în interval. Off-by-one aici fie
 *   sare un cvadruplet valid, fie emite duplicate. Urmărește exemplul
 *   pe hârtie: sortat 0,0,1,1,2,2,2.
 *
 *   i rulează cât timp i+3 < n ca să existe patru celule. j + 2 < n
 *   la fel.
 *
 *   Cache: după sort, plimbările interioare cu doi pointeri sunt
 *   secvențiale. Buclele exterioare sar j în jur; tot același tablou,
 *   probabil fierbinte.
 *
 *   sort mutează. Identitatea originală a indicilor e distrusă.
 *   Tipărim valori, nu indici.
 *
 *   Gol / n < 4: nu tipări nimic. Fără wrap al lui n-1.
 */

#include <algorithm>
#include <iostream>
using namespace std;

void fourSum(int nums[], int n, int target) {
    if (n < 4) {
        return;
    }
    sort(nums, nums + n);
    long long need = target;
    for (int i = 0; i + 3 < n; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }
        for (int j = i + 1; j + 2 < n; j++) {
            if (j > i + 1 && nums[j] == nums[j - 1]) {
                continue;
            }
            int l = j + 1;
            int h = n - 1;
            while (l < h) {
                long long sum = 1LL * nums[i] + nums[j] + nums[l] + nums[h];
                if (sum == need) {
                    cout << nums[i] << ' ' << nums[j] << ' ' << nums[l] << ' '
                         << nums[h] << '\n';
                    l++;
                    h--;
                    while (l < h && nums[l] == nums[l - 1]) {
                        l++;
                    }
                    while (l < h && nums[h] == nums[h + 1]) {
                        h--;
                    }
                } else if (sum < need) {
                    l++;
                } else {
                    h--;
                }
            }
        }
    }
}

int main() {
    int nums[] = {0, 1, 0, 2, 1, 2, 2};
    int n = sizeof(nums) / sizeof(nums[0]);
    fourSum(nums, n, 3);
    return 0;
}
