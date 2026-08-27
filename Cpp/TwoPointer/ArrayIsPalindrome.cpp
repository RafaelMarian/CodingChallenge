/*
 * LECȚIE — Este un tablou de întregi palindrom?
 *
 * Studentule, un palindrom se citește la fel de la stânga la dreapta
 * și de la dreapta la stânga. Pentru un tablou de int-uri, asta e o
 * afirmație despre perechi de celule, nu despre șiruri.
 *
 * Problemă
 *   Întoarce true dacă și numai dacă nums[k] == nums[n-1-k] pentru
 *   fiecare k din [0, n). Un tablou gol și un tablou cu un element
 *   sunt palindroame: nu există nicio pereche care să poată să nu
 *   coincidă.
 *
 * Intuiție / Algoritm
 *   Nu trebuie să inversezi o copie și să compari. Pune i la 0 și j
 *   la n-1. Cât timp i < j, dacă cele două celule diferă, respinge.
 *   Altfel pășește spre interior. Dacă epuizezi perechile, toate
 *   egalitățile cerute au ținut.
 *
 *   E bucla de reverse, dar cu o comparație în loc de un swap. Invariantul
 *   e: toate perechile din afara lui [i, j] s-au potrivit deja.
 *
 * Complexitate
 *   Timp  O(n). Cazul cel mai bun e O(1) dacă capetele diferă deja;
 *   totuși cităm cazul cel mai rău.
 *   Memorie extra O(1). Nu construim o copie inversată. O copie
 *   inversată ar fi O(n) memorie extra și O(n) timp înainte de prima
 *   comparație. Asta e muncă irosită și memorie irosită.
 *
 * Memorie
 *   Parametrul e int nums[] plus int n. nums decade la int*: un
 *   pointer către prima celulă. Nu stochează lungimea, deci n e
 *   obligatoriu. Evităm vector dinadins. Doar încărcăm. Cele n int-uri
 *   rămân unde le-a pus apelantul (aici, un tablou pe stivă în main).
 *   Folosirea stivei în funcția asta sunt doi indici.
 *
 *   const pe int-urile pointeate ar fi un contract că apelatul nu
 *   scrie. Lecția asta oricum nu scrie. Octeții tot trăiesc unde i-a
 *   alocat apelantul.
 *
 * Teorie C — comparație, nu mutație; cache; UB
 *   Algoritmul ăsta nu mutează. Pe loc e o proprietate a celor care
 *   scriu. Aici fiecare acces e un load. E cel mai ieftin lucru pe
 *   care îl face un CPU cu memoria, în afară de a n-o atinge deloc.
 *
 *   i și j sunt indici, nu pointeri, dar hardware-ul face aritmetică
 *   de pointer: load-ul lui nums[i] e *(nums + i). Dacă i e în
 *   interval, adresa e înăuntrul tabloului. Dacă nu, load-ul e
 *   comportament nedefinit. Ținem i < j și j = n-1 cu n >= 2, deci
 *   ambii indici sunt valizi.
 *
 *   Capcana tabloului gol: n = 0, atunci n-1 e -1. Întoarcem true
 *   înainte să formăm indicele ăla. Overflow-ul signed pe int e
 *   comportament nedefinit; formarea lui -1 ca indice e pur și simplu
 *   adresa greșită. Știi cu care greșeală ai de-a face.
 *
 *   Cache: două fluxuri secvențiale de la capete, la fel ca la reverse.
 *   La un test de palindrom respingi adesea devreme, deci s-ar putea
 *   să nu atingi deloc mijlocul. Ieșirea timpurie e un cadou; nu o
 *   anula inversând mai întâi.
 *
 *   Egalitatea pe int e pe biți, în complement față de doi. Nu apare
 *   overflow pentru că nu adunăm niciodată elementele.
 */

#include <iostream>
using namespace std;

bool isPalindrome(int nums[], int n) {
    if (n < 2) {
        return true;
    }
    int i = 0;
    int j = n - 1;
    while (i < j) {
        if (nums[i] != nums[j]) {
            return false;
        }
        i++;
        j--;
    }
    return true;
}

int main() {
    int nums[] = {1, 2, 3, 4, 3, 2, 1};
    int n = sizeof(nums) / sizeof(nums[0]);
    if (isPalindrome(nums, n)) {
        cout << "true\n";
    } else {
        cout << "false\n";
    }
    return 0;
}
