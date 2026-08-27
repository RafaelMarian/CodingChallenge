/*
 * LECȚIE — Sume prefix: plătești O(n) memorie o dată, răspunzi sume de interval în O(1)
 *
 * Studentule, iată contractul. Dat nums[0..n), scrie prefix astfel încât
 *
 *     prefix[0] = nums[0]
 *     prefix[i] = prefix[i-1] + nums[i]     pentru i = 1 .. n-1
 *
 * După aia, suma oricărui interval închis [L, R] e
 *
 *     prefix[R]                 dacă L == 0
 *     prefix[R] - prefix[L-1]   dacă L > 0
 *
 * Scăderea aia e două load-uri și o adunare. Fără buclă. Buffer-ul
 * extra e prețul de intrare. Afișează o valoare prefix pe linie.
 *
 * Intuiție
 *   Un total care rulează e o integrală cumulativă a tabloului.
 *   Diferențele unei integrale cumulative recuperează sume de
 *   interval. Ai văzut asta la matematică discretă ca telescopare:
 *   (a0+...+aR) - (a0+...+aL-1) = aL+...+aR. Desenează tabloul ca
 *   un rând de întregi în memorie. prefix[i] e suma fiecărei celule
 *   de la început până la i. Odată ce rândul ăla există, un interval
 *   e o pereche de indici, nu o parcurgere.
 *
 * Complexitate
 *   Timp de construire:  O(n). O trecere secvențială, o adunare pe element.
 *   Timp pe interval:    O(1) după construire.
 *   Memorie extra:       O(n) întregi pentru buffer-ul prefix.
 *   Sume naive de interval fără prefix sunt O(n) pe interogare. Pentru Q
 *   interogări ăsta e O(nQ). Prefixul o face O(n + Q). Ăsta e schimbul.
 *
 * Memorie
 *   int nums[], int n, int prefix[]: doi pointeri și o lungime.
 *   Apelantul deține ambele buffer-e. În main, nums și prefix sunt
 *   tablouri pe stivă de aceeași lungime. Funcția scrie în prefix;
 *   nu alocă și nu întoarce un tablou nou. Din cauza decay-ului
 *   tablou→pointer, sizeof(prefix) în prefixSum e dimensiunea unui
 *   pointer, nu n * sizeof(int). De-asta n e argument.
 *
 *   Ambele buffer-e sunt contigue. Să parcurgi prefix[i], prefix[i+1],
 *   ... curge prin linii de cache (de obicei 64 de octeți, 16 int).
 *   O structură înlănțuită de sume parțiale ar fi același big-O și
 *   o mașină mai proastă.
 *
 * Teorie C — overflow, UB, și de ce buffer-ul e un tablou
 *   prefix[i] = prefix[i-1] + nums[i] e o adunare pe signed.
 *   Overflow-ul pe signed e UB. Dacă sumele adevărate nu încap în
 *   int pe 32 de biți, programul n-are sens: compilatorul poate
 *   presupune că overflow-ul nu se întâmplă niciodată și șterge
 *   ramuri „imposibile”. Pentru lucru real de sume de interval
 *   stochează prefix ca long long (cel puțin 64 de biți). Atunci
 *   un interval tot încape, decât dacă datele sunt adverse pe
 *   ordinul 2^63.
 *
 *   prefix[0] = nums[0] e legal doar dacă n > 0. Un input gol n-are
 *   nums[0]. Accesul ăla e în afara limitelor: UB. Nu tratăm golul
 *   aici pentru că exemplul e ne-gol; tu ar trebui, în producție.
 *
 *   În C e aceeași așezare:
 *       int prefix[N];
 *       prefix[0] = nums[0];
 *       for (int i = 1; i < n; i++) prefix[i] = prefix[i-1] + nums[i];
 *   a[i] e *(a + i). Compilatorul scalează i cu sizeof(int). Pointerul
 *   n-are lungime ascunsă. Varianta pe heap: malloc(n * sizeof *prefix)
 *   și free(prefix) când ai terminat.
 *
 *   Cache: și nums și prefix sunt secvențiale. Trecerea de construire
 *   e două fluxuri, ambele fierbinți. De-asta tablourile prefix sunt
 *   primul truc implicit în problemele pe tablouri, nu vreun arbore
 *   șmecher.
 *
 * Compilează și rulează. Apoi calculează prefix[5] - prefix[1] de mână
 * și verifică că e egal cu nums[2]+nums[3]+nums[4]+nums[5].
 */

#include <iostream>
using namespace std;

void prefixSum(int nums[], int n, int prefix[]) {
    prefix[0] = nums[0];
    for (int i = 1; i < n; i++) {
        prefix[i] = prefix[i - 1] + nums[i];
    }
}

int main() {
    int nums[] = {8, 7, 2, 1, 3, 6, 10, 4, 9, 5};
    int n = sizeof(nums) / sizeof(nums[0]);
    int prefix[sizeof(nums) / sizeof(nums[0])];
    prefixSum(nums, n, prefix);
    for (int i = 0; i < n; i++) {
        cout << prefix[i] << "\n";
    }
    return 0;
}
