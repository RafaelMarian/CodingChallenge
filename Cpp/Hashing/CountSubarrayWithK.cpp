/*
 * LECȚIE — Subtablouri cu suma k: sume prefix plus o mapă de frecvențe
 *
 * Studentule, numără câte subtablouri contigue au suma egală cu k.
 * Exemplu: {10, 2, -2, -20, 10}, k = -10. Sunt trei:
 *   [10, 2, -2, -20],  [2, -2, -20, 10],  [-20, 10].
 *
 * Intuiție
 *   Fie prefix[j] suma lui nums[0..j]. Atunci suma lui
 *   nums[i..j] e prefix[j] - prefix[i-1] (și prefix[-1] = 0).
 *   Vrem prefix[j] - prefix[i-1] == k, adică
 *
 *       prefix[i-1] == prefix[j] - k
 *
 *   Pentru suma curentă care rulează curr, numărul de prefixe
 *   anterioare egale cu curr - k e exact numărul de subtablouri
 *   care se termină aici și au suma k. Stochează frecvențele de
 *   prefix într-un unordered_map. Semănează mapa cu (0, 1): un
 *   prefix gol, ca un subtablou care începe la indicele 0 să fie
 *   numărat când curr însuși e egal cu k.
 *
 *   Mergi stânga-dreapta: adaugă nums[i] în curr, adaugă
 *   map[curr - k] la răspuns, apoi incrementează map[curr].
 *   Incrementul e după lookup ca să nu numeri sufixul gol ca
 *   subtablou decât dacă k == 0 și chiar vrei (și atunci prefixul
 *   gol e sămânța, nu o felie din tablou). Pentru k == 0 sămânța
 *   tot înseamnă „subtablouri care au suma 0”, ceea ce e corect;
 *   nu numărăm niciodată o felie de lungime zero ca extra pentru
 *   că interogăm doar după ce am adăugat un element real.
 *
 * Complexitate
 *   Timp mediu O(n). Fiecare pas e un lookup hash și un insert hash.
 *   Cel mai rău O(n^2) dacă tabela degenerează. Memorie extra O(n)
 *   prefixe în mapă în cazul cel mai rău (toate sumele prefix
 *   distincte).
 *
 * Memorie
 *   Mapa ține până la n+1 chei (sămânța plus una pe indice). Fiecare
 *   e un nod pe heap. Suma care rulează e un scalar. Nu stocăm
 *   tabloul prefix explicit: mapa *este* istoricul prefix comprimat.
 *   int arr[], int n: inputul a decăzut la un pointer plus o
 *   lungime. typedef unordered_map<int, int> Freq ca tipul să n-aibă
 *   prefix std::.
 *
 * Teorie C — de ce mapa, overflow, și prefixul gol
 *   Dacă ai stoca prefix într-un tablou, ai putea, pentru fiecare j,
 *   să parcurgi toți i <= j și să testezi egalitatea. Ăsta e O(n^2).
 *   Mapa transformă „câte prefixe anterioare egalează valoarea asta”
 *   într-o interogare O(1) așteptată. Indexezi după *valoarea*
 *   prefixului, nu după un indice, deci un tablou dens de numărare
 *   ar avea nevoie de un slot pe fiecare sumă posibilă. Sumele pot
 *   fi negative și mari: U nu e un alfabet mic. Tabelă hash.
 *
 *   curr += arr[i] poate da overflow pe int. Overflow-ul pe signed
 *   e UB. O versiune de producție acumulează curr ca long long și
 *   folosește unordered_map<long long, int>. Păstrăm int ca să
 *   potrivim aritmetica originală pe exemplul ăsta; ideea e identică.
 *
 *   Cheile mapei sunt valori prefix, care pot fi negative. Asta e
 *   în regulă pentru o tabelă hash și ilegal pentru un tablou de
 *   numărare de dimensiune max+1. Ăsta e exemplul despre care te-a
 *   avertizat HashingIntro.
 *
 *   Cache: lookup-urile pe unordered_map urmăresc pointeri prin
 *   noduri pe heap. Pentru n competitiv (10^5) e schimbul corect.
 *   Pentru n mic, o buclă imbricată peste un tablou prefix poate
 *   fi mai rapidă pentru că tabloul prefix e contig. Raționează
 *   despre n, apoi măsoară dacă contează.
 *
 *   Sămânța (0, 1) nu e un hack. E prefixul capului gol. S-o uiți
 *   sub-numără fiecare subtablou care începe la 0.
 *
 * Afișează doar numărul. Fără dump de debug al mapei.
 * Exemplul afișează 3.
 */

#include <iostream>
#include <unordered_map>
using namespace std;

typedef unordered_map<int, int> Freq;

int findSubarraySum(int arr[], int n, int sum) {
    Freq prevSum;
    prevSum[0] = 1;
    int res = 0;
    int currSum = 0;
    for (int i = 0; i < n; i++) {
        currSum += arr[i];
        int removeSum = currSum - sum;
        if (prevSum.count(removeSum)) {
            res += prevSum[removeSum];
        }
        prevSum[currSum]++;
    }
    return res;
}

int main() {
    int arr[] = {10, 2, -2, -20, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = -10;
    cout << findSubarraySum(arr, n, k) << "\n";
    return 0;
}
