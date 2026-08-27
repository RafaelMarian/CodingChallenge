/*
 * LECȚIE — Pivot integer: numere triunghiulare, nu un tabel de căutare
 *
 * Studentule, găsește x în 1..n astfel încât suma 1+...+x să fie egală cu suma
 * x+...+n. Dacă nu există un astfel de x, întoarce -1.
 *
 * Algebră, întâi, ca să vezi ce cauți
 *   1 + ... + x  =  x (x + 1) / 2                 (Gauss)
 *   x + ... + n  =  (1+...+n) - (1+...+(x-1))
 *                =  n(n+1)/2 - (x-1)x/2
 *   Pune-le egale:
 *       x(x+1)/2  =  n(n+1)/2 - x(x-1)/2
 *       x^2       =  n(n+1)/2
 *   Deci x e un pivot integer dacă și numai dacă x^2 egalează al n-lea număr
 *   triunghiular. x e rădăcina pătrată întreagă a lui T_n, când
 *   rădăcina aia e exactă.
 *
 * Funcția pe care nu trebuie s-o scrii
 *   Un lookup n==1 -> 1, n==8 -> 6, n==49 -> 35, n==288 -> 204,
 *   altfel -1. Ăstea sunt patru exemple din manual, nu un algoritm.
 *   Întoarce -1 pentru n==50, care se întâmplă să fie corect, și -1
 *   pentru n==1000000, pe care nu l-ai verificat. Hardcodarea nu e
 *   inginerie.
 *
 * Soluția reală — test de pătrat întreg, înmulțire pe 64 de biți
 *   Fie total = n * (n + 1) / 2, calculat în long long ca
 *   înmulțirea să nu dea overflow pe int (și ca n+1 să fie
 *   promovat înainte de adunare: scrie 1LL * n * (n + 1LL) / 2).
 *   Apoi caută x în 1..n pentru x * x == total, cu x * x tot în
 *   long long. Căutare binară pe linia numerelor; n-ai nevoie de
 *   un tablou. Dacă căutarea iese, total nu e un pătrat perfect:
 *   întoarce -1.
 *
 *   Nu folosi sqrt pe virgulă mobilă și „verifică întregii din
 *   jur” decât dacă ai o dovadă despre rotunjire. Înmulțire pe
 *   64 de biți plus comparație e exactă.
 *
 * Verificări
 *   n = 8:  T_8  = 36  = 6^2.  Pivot 6.
 *   n = 49: T_49 = 1225 = 35^2. Pivot 35.
 *   n = 50: T_50 = 1275, nu e pătrat. -1.
 *
 * Complexitate
 *   Hardcodat: O(1) și greșit ca funcție de n.
 *   Gauss + căutare binară: O(log n) înmulțiri. Memorie extra O(1).
 *
 * Memorie
 *   Fără tablouri. O mână de întregi pe stivă. Problema asta e
 *   aritmetică pură. Nimic de alocat și nimic de eliberat. Ăsta
 *   e cantitatea corectă de memorie. Fără decay, fără n din
 *   sizeof: singurul n e argumentul întreg.
 *
 * Teorie C — numere triunghiulare, overflow, împărțire întreagă
 *   Formula lui Gauss n(n+1)/2 e exactă pe întregi pentru că
 *   n(n+1) e mereu par. În aritmetică întreagă tot trebuie să
 *   înmulțești înainte să împarți, pe un tip destul de larg.
 *   n*(n+1)/2 în int, pentru n aproape de 2^16, deja dă overflow:
 *   overflow-ul pe signed e UB, și compilatorul poate șterge
 *   verificări ulterioare. 1LL * n * (n + 1LL) / 2 e obiceiul.
 *
 *   mid * mid în int dă overflow pentru mid > 46340 (pentru că
 *   46341^2 > 2^31-1). Compară 1LL * mid * mid cu total.
 *
 *   Împărțirea întreagă trunchiază spre zero. Împărțim doar
 *   produse pare la 2, deci n-ai rotunjire. Nu împărțim niciodată
 *   în bucla de căutare: comparăm pătrate.
 *
 *   Căutarea binară aici e pe intervalul de întregi [1, n], nu pe
 *   un tablou. Accesul aleator e o înmulțire de lățimea
 *   registrului, nu un load. N-ai poveste de cache pentru că n-ai
 *   buffer. Lecția e overflow, nu localitate.
 *
 * main afișează gauss(50), gauss(8), gauss(49) ca să vezi -1, 6, 35.
 */

#include <iostream>
using namespace std;

int gauss(int n) {
    long long total = 1LL * n * (n + 1LL) / 2;
    int lo = 1;
    int hi = n;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        long long square = 1LL * mid * mid;
        if (square == total) {
            return mid;
        }
        if (square < total) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return -1;
}

int main() {
    cout << gauss(50) << "\n";
    cout << gauss(8) << "\n";
    cout << gauss(49) << "\n";
    return 0;
}
