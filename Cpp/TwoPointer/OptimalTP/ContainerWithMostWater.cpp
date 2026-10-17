/*
 * LECȚIE — Containerul cu cea mai multă apă
 *
 * Studentule, forța brută e fiecare pereche de indici (l, r) ca cele
 * două ziduri, area = min(height[l], height[r]) * (r - l), ia max-ul.
 * Asta e O(n^2) perechi. Doi pointeri aruncă perechile care nu pot
 * bate best-ul curent, în O(n) pași.
 *
 * Problemă
 *   height[i] e o linie verticală la x = i. Alege două linii. Aria
 *   containerului e min-ul celor două înălțimi ori distanța dintre
 *   indici. Maximizează aria aia. Exemplu: {1,4,10,5,2,6,7,3}
 *   tipărește 28 (liniile de înălțime 10 și 7, lățime 4).
 *
 * Intuiție / Algoritm
 *   Pornește de la cel mai lat container: l = 0, r = n-1. Calculează
 *   aria aia. Apoi trebuie să micșorezi lățimea cu unu. Mutarea zidului
 *   mai înalt nu poate crește min-height (zidul scurt tot limitează)
 *   și scade strict lățimea, deci aria aia e mai proastă. Mutarea
 *   zidului mai scurt e singura mutare care ar putea ridica înălțimea
 *   limitatoare destul ca să compenseze lățimea pierdută. Dacă zidurile
 *   sunt egale, mutarea oricăruia e simetrică; mutăm unul dintre ele
 *   (aici, r).
 *
 *   Repetă până l și r se întâlnesc. Fiecare indice e un zid stânga
 *   sau dreapta candidat cel mult o dată. Maximul global e printre
 *   cele O(n) containere pe care le evaluezi, pentru că orice pereche
 *   interioară aruncată cu vechiul zid scurt stătea sub un min-height
 *   mai scurt sau egal și o lățime mai mică.
 *
 * Complexitate
 *   Timp  O(n). Memorie extra O(1): doi indici și max-ul care rulează.
 *
 * Memorie
 *   int height[] decade la un pointer; transmite n. Doar citire, fără
 *   copie, fără heap. Evităm vector dinadins. Răspunsul e un întreg.
 *   Doar locale pe stivă. Asta e o scanare pură de load-și-compară a
 *   buffer-ului apelantului.
 *
 *   În C: int max_area(int *h, int n). Aceleași load-uri.
 *
 * Teorie C — de ce să nu muți partea înaltă; overflow-ul ariei; cache; UB
 *   Fie h[l] < h[r]. Orice container (l, k) cu k < r are lățime mai
 *   mică decât (r-l) și min-height cel mult h[l], pentru că zidul
 *   stâng tot e cel scurt sau celălalt zid e și mai scurt. Deci ariile
 *   alea sunt <= h[l] * (r-l), pe care le-ai considerat deja (sau le
 *   vei considera, ca aria curentă). Să le arunci cu l++ e sigur.
 *   Ăsta e invariantul. Dacă ai muta r în schimb, ai arunca perechi
 *   care tot folosesc un zid drept înalt și un zid stâng mai bun pe
 *   care încă nu l-ai întâlnit.
 *
 *   Area = min(h[l], h[r]) * (r - l). Ambii factori pot fi mari.
 *   2^31 * n nu încape pe int pe 32 de biți. Overflow-ul signed al
 *   înmulțirii ăleia e UB. Calculează
 *     1LL * min_h * (r - l)
 *   în long long, apoi ține ans ca long long. Exemplul încape în
 *   int; tot acumulăm pe 64 de biți.
 *
 *   Gol sau n < 2: aria 0. Nu forma n-1.
 *
 *   Cache: două capete, spre interior secvențial, ca la reverse. Fiecare
 *   pas încarcă o celulă nouă. Excelent.
 *
 *   Fără mutație. Înălțimile nu sunt niciodată scrise. Fără overflow
 *   al valorilor de înălțime în sine; doar min și înmulțire pe 64 de biți.
 *
 *   Indici ca int, l < r înainte de orice height[r]. După l++ sau r--
 *   condiția buclei reverifică.
 */

#include <iostream>
using namespace std;

int maxArea(int height[], int n) {
    if (n < 2) {
        return 0;
    }
    int l = 0;
    int r = n - 1;
    long long ans = 0;
    while (l < r) {
        int min_h;
        if (height[l] < height[r]) {
            min_h = height[l];
        } else {
            min_h = height[r];
        }
        long long area = 1LL * min_h * (r - l);
        if (area > ans) {
            ans = area;
        }
        if (height[l] < height[r]) {
            l++;
        } else {
            r--;
        }
    }
    return ans;
}

int main() {
    int arr[] = {1, 4, 10, 5, 2, 6, 7, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << maxArea(arr, n) << '\n';
    return 0;
}
