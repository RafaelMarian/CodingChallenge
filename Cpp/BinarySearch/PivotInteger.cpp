/*
 * LECȚIE — Pivot integer prin căutare binară pe 1..n
 *
 * Studentule, găsește x în 1..n astfel încât 1+...+x să fie egal cu x+...+n, sau -1.
 * Algebră (vezi și Cpp/Gussai/PivotInteger.cpp): e echivalent cu
 * x * x == n * (n + 1) / 2. Partea dreaptă e al n-lea număr
 * triunghiular. Exemplul n = 50: T_50 = 1275 nu e pătrat, deci
 * -1.
 *
 * Intuiție
 *   Cauți pe linia numerelor [1, n], nu într-un tablou. Predicatul
 *   „mid * mid comparat cu total” e monoton: pătratele cresc.
 *   Căutare binară după o lovitură exactă. Dacă căutarea iese fără
 *   egalitate, nu există x întreg.
 *
 *   E aceeași identitate Gauss ca în lecția Gussai, cu căutarea
 *   scrisă ca algoritm, nu ca un comentariu lângă un tabel
 *   hardcodat. N-ai tablou pentru că fiecare „indice” e chiar
 *   candidatul x. Accesul aleator e o înmulțire.
 *
 * Complexitate
 *   O(log n) înmulțiri. Memorie extra O(1). Fără heap.
 *
 * Memorie
 *   O mână de întregi pe stivă. Nimic de alocat. „Structura de date”
 *   sunt întregii 1..n, pe care nu-i stochezi. Fără buffer, fără
 *   decay, fără lungime de transmis.
 *
 * Teorie C — overflow la m*m, overflow triunghiular, fără float
 *   total = n*(n+1)/2 în int dă overflow pentru n în jur de 2^16.
 *   Calculează 1LL * n * (n + 1LL) / 2 în long long. n + 1LL
 *   promovează înainte de adunare, deci n == INT_MAX nu dă overflow
 *   la adunare.
 *
 *   m * m în int dă overflow pentru m > 46340. Mereu 1LL * m * m.
 *   Overflow-ul pe signed e UB: programul n-ar mai avea sens, nu
 *   „se înfășoară și prinzi un răspuns greșit norocos”. Compilatorul
 *   îți poate șterge comparația. Înmulțirea pe long long e
 *   reparația, nu un cast după fapt: (long long)(m * m) înmulțește
 *   întâi în int.
 *
 *   Nu lua sqrt((double)total) și rotunji. Double are 53 de biți
 *   de mantisă; numerele triunghiulare mari nu sunt exacte, și ai
 *   testa întregul greșit. Înmulțire exactă pe 64 de biți și
 *   comparație e punctul fișierului ăsta.
 *
 *   mid = l + (h - l) / 2 pe domeniul de valori. l + h tot poate
 *   da overflow dacă l-ai scrie așa cu l și h aproape de INT_MAX.
 *
 *   N-ai lecție de cache dincolo de „n-ai buffer”. Aritmetica
 *   trăiește în registre. Aia e memoria cea mai ieftină pe care
 *   o ai.
 *
 * Exemplul afișează -1.
 */

#include <iostream>
using namespace std;

int pivotInteger(int n) {
    long long total = 1LL * n * (n + 1LL) / 2;
    int l = 1;
    int h = n;
    while (l <= h) {
        int m = l + (h - l) / 2;
        long long square = 1LL * m * m;
        if (square == total) {
            return m;
        }
        if (square < total) {
            l = m + 1;
        } else {
            h = m - 1;
        }
    }
    return -1;
}

int main() {
    cout << pivotInteger(50) << "\n";
    return 0;
}
