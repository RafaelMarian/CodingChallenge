/*
 * LECȚIE — Tablou de numărare: valoarea cea mai frecventă când cheile sunt 0..U
 *
 * Studentule, dat un tablou ne-gol de int nenegativi, întoarce valoarea care
 * apare cel mai des (nu numărul; valoarea). La egalitate câștigă
 * valoarea cea mai mică, pentru că parcurgem buffer-ul de numărare
 * de la 0 și ținem un strict greater.
 *
 * Intuiție
 *   Dacă fiecare cheie e un întreg în 0..U, n-ai nevoie de o tabelă
 *   hash. Alocă un buffer de lungime U+1, zeroază-l, și fă hash[x]++
 *   pentru fiecare element. Apoi parcurge buffer-ul o dată: indicele
 *   cu cel mai mare count e răspunsul. E ideea counting-sort,
 *   oprită înainte de trecerea de scriere înapoi. Frecvența e un
 *   lookup de tablou, O(1), pentru că cheia *este* indicele.
 *
 *   Exemplul {8, 3, 11, 8, 7, 8, 14, 3, 9, 7}: U = 14. După numărare,
 *   hash[8] == 3 e maximul unic. Întoarce 8.
 *
 * Complexitate
 *   Timp O(n + U): o trecere peste nums, o trecere peste buffer-ul
 *   de numărare. Memorie extra O(U). Când U e O(n) ăsta e liniar.
 *   Când U e 10^9 și n e 10, tocmai ai alocat o fantezie.
 *
 * Memorie — new / malloc, și de ce eliberăm
 *   U depinde de date. Un tablou pe stivă int hash[U+1] e un VLA
 *   (nu C++ portabil) și poate sparge stiva dacă U e mare. Deci
 *   alocăm pe heap:
 *
 *       int *hash = new int[maxv + 1]();   // () zeroază fiecare slot
 *       ...
 *       delete[] hash;                     // un delete[] pe new[]
 *
 *   C e aceeași poveste cu altă ortografie:
 *
 *       int *hash = (int *)malloc((maxv + 1) * sizeof(int));
 *       memset(hash, 0, (maxv + 1) * sizeof(int));
 *       ...
 *       free(hash);                        // un free pe malloc
 *
 *   new[] întoarce un pointer la primul int. hash[x] e *(hash + x).
 *   Pointerul nu știe maxv; ținem maxv într-o locală. Ratezi
 *   delete[] și ai leak. Folosești delete (fără paranteze) pe new[]
 *   și corupești heap-ul. Folosești tabloul după delete[] și ai un
 *   pointer dangling: UB.
 *
 *   Pe exemplul ăsta maxv e 14, deci int hash[15] pe stivă ar
 *   merge și el. Alocăm pe heap dinadins ca să vezi durata de viață.
 *
 * Teorie C — mape dense, risipă rară, overflow al indicelui
 *   E un tablou folosit ca mapă de la cheie la count. E dens: fiecare
 *   întreg din 0..U are un slot, chiar și cheile care nu apar
 *   niciodată. Zerourile astea sunt spațiu irosit și timp de
 *   parcurgere irosit. E în regulă când U e mic și vrei indexare O(1)
 *   plus o parcurgere secvențială cu cache rece a unui buffer
 *   compact. Nu e în regulă când domeniul cheilor e rar sau uriaș.
 *   Atunci vrei o tabelă hash (vezi UsingMap.cpp) a cărei memorie
 *   e O(chei distincte), nu O(U).
 *
 *   Dacă x e negativ, indexezi înainte de buffer: UB, un underflow
 *   clasic pe heap. Dacă x > maxv, overflow pe heap. AddressSanitizer
 *   e cum prinzi asta într-un lab. Algoritmul ăsta e corect doar
 *   pentru chei în [0, maxv] unde maxv e valoarea maximă prezentă
 *   (deci fiecare cheie e un indice valid).
 *
 *   maxv+1 poate da overflow pe int dacă maxv == INT_MAX. Să transmiți
 *   o dimensiune uriașă allocatorului poate și ea să se înfășoare.
 *   Pentru date de clasă nu se întâmplă. Pentru date neîncrezute,
 *   verifică.
 *
 *   Cache: trecerea de increment e acces aleator în hash[], condus
 *   de nums[i]. Dacă nums e amestecat pe un U mare, ratezi cache
 *   aproape la fiecare ++. Dacă U e mic, hash[] încape în L1 și ++
 *   e ieftin. Ăsta e adevăratul „când e un tablou de numărare OK”:
 *   U destul de mic încât buffer-ul e fierbinte, și chei nenegative.
 *
 *   Numele hash: e un tablou de numărare, nu o tabelă hash. N-ai
 *   funcție hash. Funcția identitate e „hash-ul”. Păstrăm numele
 *   pentru că așa vorbește familia asta de lecții.
 *
 * Exemplul afișează 8.
 */

#include <iostream>
using namespace std;

int mostOccurring(int nums[], int n) {
    int maxv = nums[0];
    for (int i = 1; i < n; i++) {
        if (nums[i] > maxv) {
            maxv = nums[i];
        }
    }
    int *hash = new int[maxv + 1]();
    for (int i = 0; i < n; i++) {
        hash[nums[i]]++;
    }
    int best = 0;
    for (int i = 0; i <= maxv; i++) {
        if (hash[i] > hash[best]) {
            best = i;
        }
    }
    delete[] hash;
    return best;
}

int main() {
    int nums[] = {8, 3, 11, 8, 7, 8, 14, 3, 9, 7};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << mostOccurring(nums, n) << "\n";
    return 0;
}
