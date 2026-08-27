/*
 * LECȚIE — Apa prinsă între ziduri, cu doi pointeri
 *
 * Studentule, apa care stă pe indicele i e mărginită de cel mai înalt
 * zid din stânga lui și cel mai înalt zid din dreapta lui: water[i] =
 * max(0, min(leftMax[i], rightMax[i]) - height[i]). Să construiești
 * cele două tablouri e O(n) memorie extra. Doi pointeri calculează
 * același total cu două maxime care rulează și O(1) cuvinte extra.
 *
 * Problemă
 *   O hartă de înălțimi. Unități de apă care se pot aduna (nu pot
 *   curge pe la capete). Exemplu: {4,0,8,0,1,6,2,5} prinde 18.
 *
 * Intuiție / Algoritm
 *   leftMax e bara cea mai înaltă din [0, left], rightMax din [right, n).
 *   Apa de pe o celulă e limitată de cel mai mic dintre cele două
 *   maxime care mărginesc, odată ce celula e sub ambele limite.
 *
 *   Dacă leftMax < rightMax, apa de la `left` e deja decisă: limita
 *   ei e leftMax, pentru că partea dreaptă poate oferi cel
 *   puțin rightMax, care e mai mare. Poți adăuga leftMax - height[left]
 *   (când e pozitiv, adică când nu ești pe un max nou) și apoi muta
 *   left spre interior, actualizând leftMax. Simetric, dacă
 *   rightMax <= leftMax, procesează `right` și mută right spre interior.
 *
 *   Procesezi întotdeauna partea al cărei max curent e mai mic. Următoarea
 *   celulă a părții ăleia are un min(leftMax, rightMax) cunoscut.
 *   Cealaltă parte e „cel puțin atât de înaltă,” ceea ce e de ajuns.
 *
 * Complexitate
 *   Timp  O(n): left și right împreună acoperă tabloul o dată.
 *   Memorie extra O(1): doi indici, două maxime, un acumulator.
 *   Tablourile de max pe prefix/sufix sunt roțile de antrenament cu
 *   spațiu O(n).
 *
 * Memorie
 *   int height[] decade la un pointer; transmite n. Doar încărcăm.
 *   Fără un tablou extra de n de leftMax. Cele n int-uri alea ar fi
 *   un alt buffer, o altă trecere rece, apoi o a treia trecere ca să
 *   aduni apa. Evităm vector dinadins. Să prăbușești tabelele în două
 *   valori care rulează e aceeași prăbușire pe care ai văzut-o când o
 *   recurență DP are nevoie doar de celula anterioară.
 *
 *   water e un long long care rulează. Trăiește într-un registru / slot
 *   pe stivă. Nimic de eliberat.
 *
 * Teorie C — limite, overflow, input gol, cache, UB
 *   height[0] și height[n-1] pe n == 0 e UB. n < 2: întoarce 0. n == 1:
 *   nu există interior de umplut, întoarce 0. Inițializăm leftMax și
 *   rightMax de la cele două capete doar după n >= 2, iar bucla e
 *   while left < right, deci n == 1 nu intră.
 *
 *   water += leftMax - height[left]. Ambele sunt int. Dacă leftMax e
 *   întotdeauna >= height[left] prin ordinea de actualizare, diferența
 *   e nenegativă, iar adunarea tot poate da overflow pe acumulator
 *   dacă apa totală trece de INT_MAX. Folosește long long pentru water
 *   în producție. Exemplul e mic; ținem un acumulator long long și-l
 *   tipărim ca valoarea API 18.
 *
 *   Ordinea de actualizare contează. Mută pointerul mai întâi (sau
 *   după comparația maximelor), apoi ridică max-ul sau adaugă apă.
 *   Dacă adaugi apă înainte ca celula să fie un interior candidat,
 *   numeri capetele de două ori. Urmărește exemplul cu un tabel de
 *   left, right, leftMax, rightMax, water până se potrivește cu 18.
 *
 *   Nu scădea într-o ordine care merge negativ și apoi clamp fără un
 *   motiv: dacă invariantul tău e leftMax >= height[left] când adaugi,
 *   scăderea e nenegativă și n-ar trebui să lovești un intermediar
 *   negativ. Dacă rupi invariantul, ai un bug de logică.
 *
 *   Cache: două fluxuri secvențiale de la capete. Aceeași formă ca
 *   problema cu containerul. Mutația pe loc nu e folosită; harta e
 *   doar citire. Povestea „pe loc” aici e pe loc în sensul de memorie
 *   extra, nu în sensul de a suprascrie height.
 *
 *   Pointeri: left și right sunt indici într-un tablou contig de int.
 *   left < right implică că amândoi sunt < n dată fiind inițializarea.
 */

#include <iostream>
using namespace std;

int trap(int height[], int n) {
    if (n < 2) {
        return 0;
    }
    int left = 0;
    int right = n - 1;
    int leftMax = height[left];
    int rightMax = height[right];
    long long water = 0;
    while (left < right) {
        if (leftMax < rightMax) {
            left++;
            if (height[left] > leftMax) {
                leftMax = height[left];
            } else {
                water += leftMax - height[left];
            }
        } else {
            right--;
            if (height[right] > rightMax) {
                rightMax = height[right];
            } else {
                water += rightMax - height[right];
            }
        }
    }
    return water;
}

int main() {
    int arr[] = {4, 0, 8, 0, 1, 6, 2, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << trap(arr, n) << '\n';
    return 0;
}
