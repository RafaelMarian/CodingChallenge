/*
 * LECȚIE — Căutare binară clasică pe un tablou sortat
 *
 * Studentule, tabloul e sortat nedescrescător. Întoarce indicele lui key, sau -1
 * dacă lipsește. Exemplul {2,3,5,6,7,8,9,11,13,14} cu key 10 dă -1:
 * 10 nu e acolo, și căutarea o dovedește aruncând jumătate din
 * intervalul rămas la fiecare pas.
 *
 * Intuiție
 *   Ține un interval închis [l, h] care trebuie să conțină key dacă
 *   key e undeva. Compară key cu elementul din mijloc. Dacă e egal,
 *   întoarce mid. Dacă key e mai mic, jumătatea dreaptă nu-l poate
 *   conține: h = mid - 1. Dacă key e mai mare, jumătatea stângă nu
 *   poate: l = mid + 1. Intervalul se strânge până e gol (l > h) sau
 *   dai de el.
 *
 *   Ai nevoie de acces aleator: trebuie să încarci nums[mid] în O(1).
 *   O listă înlănțuită n-are căutare binară utilă; ai petrece O(n)
 *   mergând până la mid. Un tablou C îți dă aritmetică pe pointeri:
 *   nums[mid] e *(nums + mid).
 *
 * Complexitate
 *   Timp O(log n): intervalul se înjumătățește la fiecare iterație.
 *   Memorie extra O(1). Recursivitatea ar folosi O(log n) cadre pe
 *   stivă; bucla nu.
 *
 * Memorie
 *   int nums[] într-un parametru e o minciună: decade la int*. Funcția
 *   nu poate recupera lungimea din pointer, deci transmiți int n.
 *   În main, nums e un tablou real pe stivă; sizeof(nums) /
 *   sizeof(nums[0]) e legal doar acolo. l, h, mid sunt int-uri
 *   automate. Căutarea binară sare prin buffer: întâi mijlocul, apoi
 *   un sfert, și tot așa. Pentru n mare, acele load-uri ratează cache.
 *   Căutarea liniară secvențială pe un tablou mic care stă deja în L1
 *   poate bate căutarea binară la cronometru, deși big-O e mai prost,
 *   pentru că face prefetch și are o buclă strânsă, previzibilă.
 *
 * Teorie C — overflow la mijloc, invarianți pe jumătăți, UB
 *   Forma naivă mid = (l + h) / 2 adună doi int. Dacă l și h sunt
 *   mari, l + h dă overflow. Overflow-ul pe signed e UB. Compilatorul
 *   poate presupune că nu se întâmplă niciodată. Forma sigură e
 *
 *       mid = l + (h - l) / 2
 *
 *   h - l e nenegativ și încape în int dacă încap și h și l. Apoi
 *   aduni l.
 *
 *   Condiția buclei e l <= h pentru că intervalul e închis. Dacă
 *   folosești l < h fără grijă, cazi ultimul element. Când pui
 *   h = mid - 1, excluzi mid (l-ai testat deja). Off-by-one aici e
 *   bug-ul clasic al căutării binare: buclă infinită sau celulă
 *   sărită.
 *
 *   Un mid în afara limitelor e UB. Invariantul buclei păstrează
 *   0 <= l <= h < n sau l > h (gol). Sortarea e o precondiție. Dacă
 *   tabloul nu e sortat, algoritmul tot „rulează” și întoarce un
 *   număr care nu înseamnă nimic. Asta nu e UB; e un răspuns greșit.
 *
 * Exemplul afișează -1.
 */

#include <iostream>
using namespace std;

int binarySearch(int nums[], int n, int key) {
    int l = 0;
    int h = n - 1;
    while (l <= h) {
        int mid = l + (h - l) / 2;
        if (key == nums[mid]) {
            return mid;
        }
        if (key < nums[mid]) {
            h = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return -1;
}

int main() {
    int nums[] = {2, 3, 5, 6, 7, 8, 9, 11, 13, 14};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << binarySearch(nums, n, 10) << "\n";
    return 0;
}
