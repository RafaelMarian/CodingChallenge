/*
 * LECȚIE — k elemente cele mai apropiate de x într-un tablou sortat
 *
 * Studentule, „cele mai apropiate k” sună a un heap de mărime k. Când
 * tabloul e deja sortat, un heap e utilaj extra. Cele k cele mai
 * apropiate formează o fereastră contiguă, și poți găsi fereastra aia
 * micșorând de la capete.
 *
 * Problemă
 *   arr e sortat nedescrescător. Tipărește cele k elemente cele mai
 *   apropiate de x, în ordinea lor originală (sortată). Exemplu: arr =
 *   {1,3,5,7,9,11,13,15}, k = 3, x = 7, răspuns 5 7 9.
 *
 * Intuiție / Algoritm
 *   Răspunsul e un subtablou arr[l..r] de lungime k. Pornește cu tot
 *   intervalul l = 0, r = n-1. Cât timp fereastra e mai lungă decât k,
 *   aruncă capătul care e mai departe de x. Compară |arr[l] - x| și
 *   |arr[r] - x|. Dacă stânga e strict mai departe, l++; altfel r--
 *   (departajarea asta păstrează valoarea mai mică, care e convenția
 *   obișnuită când distanțele sunt egale). Când lungimea ferestrei e k,
 *   oprește-te. Ce rămâne e fereastra unică cea mai apropiată sub
 *   regula aia.
 *
 *   De ce o fereastră contiguă: într-un tablou sortat, distanța la x e
 *   destul de unimodală încât cele k valori cele mai apropiate ocupă
 *   indici consecutivi. N-ai sări un element din mijloc ținând și unul
 *   departe la stânga, și unul departe la dreapta.
 *
 *   Micșorarea greedy e corectă pentru că elementul pe care-l arunci
 *   e mai rău decât cel pe care-l ții la celălalt capăt, deci nu poate
 *   aparține niciunui set de k cele mai apropiate (cu departajarea documentată).
 *
 * Complexitate
 *   Timp  O(n - k): fiecare iterație aruncă un indice, și arunci n-k
 *   dintre ei. Pentru k aproape de n e ieftin; pentru k = 1 e o
 *   scanare completă, pe care ai putea-o înlocui cu binary search plus
 *   expansiune.
 *   Memorie extra O(1) dacă tipărești arr[l..r] direct. Umplerea unui
 *   al doilea tablou de k int-uri e opțională.
 *
 * Memorie
 *   int arr[] decade la un pointer; transmite n. Evităm vector dinadins.
 *   Nu copiem tabloul de n. După ce fereastra e de lungime k, tipărim
 *   celulele alea. Dacă trebuia doar să tipărești, nu aloci nimic.
 *
 * Teorie C — abs al diferențelor, overflow, ferestre, cache
 *   |a - x| pentru int a, x nu e abs(a - x) în general. Dacă a e
 *   INT_MIN și x e 1, a - x dă overflow înainte de abs. Overflow-ul
 *   signed e UB. Compară în long long:
 *     long long d = 1LL * arr[l] - x;
 *     if (d < 0) d = -d;
 *   1LL * arr[l] - x promovează înainte de scădere. Intervalul e cam
 *   +/- 2^32, care încape în long long. Negarea aia e definită.
 *   abs(INT_MIN) pe int pe 32 de biți rămâne UB; nu apelăm asta niciodată.
 *
 *   Lungimea ferestrei: r - l + 1 > k. Cu indici int, r >= l e
 *   menținut, deci scăderea e nenegativă. Test echivalent: r - l >= k,
 *   care e (r - l + 1) > k.
 *
 *   Gol sau k <= 0: nu tipări nimic. k > n: problema de obicei
 *   garantează k <= n. Micșorăm doar cât timp r - l + 1 > k și
 *   intervalul e valid.
 *
 *   Cache: încarci doar cele două capete până fereastra e mică, apoi
 *   streamezi k int-uri consecutive. Foarte local.
 *
 *   Fără mutație pe loc a lui arr. Fereastra e o privire asupra
 *   input-ului.
 *
 *   Alternativele cu binary-search găsesc muchia stângă a ferestrei în
 *   O(log n) comparații; învață mai întâi micșorarea liniară. E evident
 *   corectă și n-are overflow subtil de mijloc.
 */

#include <iostream>
using namespace std;

void findClosestElements(int arr[], int n, int k, int x) {
    if (n == 0 || k <= 0) {
        return;
    }
    int l = 0;
    int r = n - 1;
    while (r - l + 1 > k) {
        long long dleft = 1LL * arr[l] - x;
        if (dleft < 0) {
            dleft = -dleft;
        }
        long long dright = 1LL * arr[r] - x;
        if (dright < 0) {
            dright = -dright;
        }
        if (dleft > dright) {
            l++;
        } else {
            r--;
        }
    }
    for (int i = l; i <= r; i++) {
        if (i != l) {
            cout << ' ';
        }
        cout << arr[i];
    }
    cout << '\n';
}

int main() {
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    findClosestElements(arr, n, 3, 7);
    return 0;
}
