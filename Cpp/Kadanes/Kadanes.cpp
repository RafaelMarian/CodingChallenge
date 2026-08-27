/*
 * LECȚIE — Kadane: suma maximă de subtablou, DP prăbușit în doi întregi
 *
 * Studentule, dat un tablou de int cu semn (negative permise), întoarce cea mai
 * mare sumă a oricărui subtablou contig. Tabloul e ne-gol.
 *
 * Intuiție
 *   Un subtablou care a devenit negativ nu poate fi un prefix util
 *   al unui răspuns ulterior: să-l anexezi ar doar strica. Deci ții
 *   o sumă care rulează, și când suma aia cade sub zero arunci
 *   prefixul și reîncepi de la indicele următor.
 *
 *   Bucla exactă, pe care nu trebuie s-o reordonezi:
 *
 *       sum += nums[i];
 *       if (sum > maxSum) maxSum = sum;
 *       if (sum < 0)      sum    = 0;
 *
 *   Actualizează campionul ÎNAINTE de reset. Asta nu e o alegere
 *   de stil. E cum rămân corecte tablourile doar cu negative.
 *
 * Urmărirea exemplului {-2, 1, -3, 4, -1, 2, 1, -5, 4, -1}
 *   sum începe 0, maxSum începe INT_MIN.
 *   -2: sum=-2, maxSum=-2, reset sum=0
 *    1: sum= 1, maxSum= 1
 *   -3: sum=-2, maxSum= 1, reset
 *    4: sum= 4, maxSum= 4
 *   -1: sum= 3, maxSum= 4
 *    2: sum= 5, maxSum= 5
 *    1: sum= 6, maxSum= 6
 *   -5: sum= 1, maxSum= 6
 *    4: sum= 5, maxSum= 6
 *   -1: sum= 4, maxSum= 6
 *   Răspuns 6, din felia [4, -1, 2, 1].
 *
 * Tablouri doar cu negative, urmărite
 *   Ia {-5, -2, -8}. Primul element: sum devine -5, maxSum devine -5,
 *   apoi reset. Al doilea: sum devine -2, maxSum devine -2, reset.
 *   Al treilea: sum devine -8, maxSum rămâne -2. Algoritmul a
 *   înregistrat fiecare negativ ca și candidat *înainte* să șteargă
 *   suma. Răspunsul e cel mai mare element, care e subtabloul maxim
 *   corect când fiecare felie e negativă. Dacă resetezi întâi, n-ai
 *   înregistra niciodată valorile astea și maxSum ar rămâne INT_MIN
 *   — o minciună.
 *
 * Complexitate
 *   Timp O(n), o trecere. Memorie extra O(1): doi int. Naivul
 *   O(n^2) „fiecare pereche de capete” e aceeași problemă cu un
 *   tabel de care n-ai nevoie.
 *
 * Memorie
 *   int nums[], int n: fără copie. sum și maxSum sunt stocare
 *   automată (stivă / registre). Nimic alocat. Buffer-ul de input
 *   e un tablou contig deținut de apelant. Decay: nums e int*; n e
 *   lungimea calculată în main cu sizeof.
 *
 * Teorie C — DP, INT_MIN, overflow, acces secvențial
 *   Recurența e
 *       best_ending_here[i] = nums[i] + max(best_ending_here[i-1], 0)
 *       answer[i]           = max(answer[i-1], best_ending_here[i])
 *   Când o recurență are nevoie doar de celula anterioară, prăbușește
 *   tabelul la un scalar. Așa O(n) memorie extra devine O(1). Tabloul
 *   best_ending_here nu există decât ca variabila sum.
 *
 *   maxSum e inițializat la INT_MIN (cea mai mică valoare pe 32 de
 *   biți în complement față de doi, -2^31, din <climits>). Ăsta e
 *   un sentinel care înseamnă „niciun candidat încă”. E un int
 *   valid, deci un tablou gol ar fi de nedistins de „maximul chiar
 *   e INT_MIN”. Cerem un input ne-gol.
 *
 *   sum += nums[i] poate da overflow pe int. Overflow-ul pe signed
 *   e UB. Kadane pe date de 32 de biți ale căror sume parțiale ies
 *   din [-2^31, 2^31) trebuie să folosească long long pentru sum
 *   și maxSum. Minusul unar al lui INT_MIN e și el UB (nu poate fi
 *   reprezentat); aici nu negăm niciodată maxSum.
 *
 *   Parcurgerea e secvențială: un load pe element, prefetch perfect,
 *   o linie de cache pe rând. Niciun indice aleator și niciun buffer
 *   extra care să polueze L1.
 */

#include <climits>
#include <iostream>
using namespace std;

int maxSubArray(int nums[], int n) {
    int maxSum = INT_MIN;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += nums[i];
        if (sum > maxSum) {
            maxSum = sum;
        }
        if (sum < 0) {
            sum = 0;
        }
    }
    return maxSum;
}

int main() {
    int nums[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4, -1};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << maxSubArray(nums, n) << "\n";
    return 0;
}
