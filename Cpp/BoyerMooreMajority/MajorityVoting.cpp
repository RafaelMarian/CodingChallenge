/*
 * LECȚIE — Votul majoritar Boyer–Moore, și varianta pe care urmează s-o rulezi
 *
 * Studentule, un element majoritar (când există) e o valoare care apare strict
 * de mai mult de n/2 ori. Boyer–Moore găsește un candidat într-o
 * trecere cu două cuvinte de mașină de memorie extra.
 *
 * Fișierul ăsta păstrează o buclă ușor nestandard ca exemplul
 * {9,13,9,16,9,11,9,20,9,9} tot să afișeze 9, potrivit originalului:
 *
 *     count începe la 1, lastElement începe la INT_MIN
 *     if nums[i] == lastElement: count++
 *     else if count > 1:         count--
 *     else:                      lastElement = nums[i]
 *
 * Urmărește exemplul: count rămâne 1 la fiecare mismatch, deci
 * lastElement pur și simplu urmărește valoarea curentă, până perechea
 * finală de 9 ridică count la 2 și blochează 9. Merge aici. Nu e
 * algoritmul pe care trebuie să-l trimiți în producție.
 *
 * Boyer–Moore de producție (cel pe care trebuie să-l ții minte)
 *     candidate nedefinit, count = 0
 *     for i in 0 .. n-1:
 *         if count == 0: candidate = nums[i]
 *         count += (nums[i] == candidate) ? 1 : -1
 *     apoi o a doua trecere: numără de câte ori apare de fapt
 *     candidate. Dacă ăsta e <= n/2, n-ai majoritate. Întoarce-l
 *     doar după verificare.
 *
 *   Prima trecere anulează o copie a candidatului împotriva
 *   fiecărui mismatch. Dacă există o majoritate adevărată, nu
 *   poate fi anulată complet: mai mult de n/2 copii supraviețuiesc.
 *   Dacă n-ai majoritate, candidatul n-are sens — de-asta a doua
 *   trecere. Bucla originală de mai sus nu decrementează mereu la
 *   mismatch (decrementează doar când count > 1, altfel schimbă),
 *   și nu verifică niciodată. Trateaz-o ca pe o piesă de muzeu care
 *   se întâmplă să afișeze 9 pe inputul ăsta.
 *
 * Complexitate
 *   Timp O(n) o trecere (plus O(n) de verificat în varianta clasică).
 *   Memorie extra O(1): doi int. Ăsta e punctul. N-ai nevoie de o
 *   tabelă hash de count-uri, care ar fi O(U) sau O(distinct).
 *
 * Memorie
 *   int nums[], int n. Doi int automat. Fără heap. Inputul e un
 *   buffer contig; îl încărcăm o dată, secvențial. nums a decăzut
 *   la un pointer; n e lungimea din sizeof în main.
 *
 * Teorie C — memorie extra constantă, INT_MIN ca sentinel, cache
 *   Memorie extra O(1) înseamnă că starea auxiliară e câteva
 *   registre. Tabloul rămâne unde l-a pus apelantul. Asta vrei
 *   într-o buclă interioară strânsă sau pe un microcontroller:
 *   fără allocator pe calea fierbinte.
 *
 *   lastElement = INT_MIN e un sentinel care înseamnă „niciun
 *   candidat încă”. INT_MIN e și o valoare legală de tablou. Dacă
 *   majoritatea tabloului chiar ar fi INT_MIN, tratarea primului
 *   mismatch tot merge pentru că egalitatea cu INT_MIN ar
 *   incrementa count. Dacă tabloul e gol, am întoarce INT_MIN ca
 *   o minciună. Cere n > 0.
 *
 *   Varianta clasică count += ±1 nu poate da overflow pentru n
 *   care încap în memorie: count stă în [-n, n]. Count-ul variantei
 *   rămâne pozitiv și mic.
 *
 *   Cache: o parcurgere secvențială, o comparație, un increment sau
 *   decrement. Aproape fără trafic extra. O tabelă hash de
 *   frecvențe ar aloca, ar face hash și ar urmări noduri ca să
 *   rezolve aceeași treabă.
 *
 *   Majoritatea e strictă: mai mult de n/2, nu >=, decât dacă
 *   problema zice altfel.
 *
 * Exemplul afișează 9.
 */

#include <climits>
#include <iostream>
using namespace std;

int majority(int nums[], int n) {
    int count = 1;
    int lastElement = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (nums[i] == lastElement) {
            count++;
        } else if (count > 1) {
            count--;
        } else {
            lastElement = nums[i];
        }
    }
    return lastElement;
}

int main() {
    int nums[] = {9, 13, 9, 16, 9, 11, 9, 20, 9, 9};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << majority(nums, n) << "\n";
    return 0;
}
