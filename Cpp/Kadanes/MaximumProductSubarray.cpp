/*
 * LECȚIE — Produsul maxim de subtablou: două direcții, zerouri ca ziduri
 *
 * Studentule, întoarce produsul maxim al oricărui subtablou contig. Produsele
 * cresc (și își schimbă semnul) într-un fel în care sumele nu o
 * fac, deci „resetează când e negativ” de la Kadane e mutarea
 * greșită. Un prefix negativ poate deveni cel mai bun răspuns în
 * clipa în care înmulțești cu un alt negativ.
 *
 * Intuiție
 *   Trei fapte guvernează fiecare subtablou-produs:
 *
 *   1. Zerourile taie tabloul. Un 0 e un zid: produsul printr-un 0
 *      e 0, și următorul nenul începe un segment proaspăt. Resetăm
 *      produsul care rulează la 1 după un 0 (în codul ăsta: dacă
 *      produsul care rulează e 0 la începutul iterației următoare,
 *      pune-l pe 1 înainte de a înmulți).
 *
 *   2. Un număr par de negative într-un segment dă un produs
 *      pozitiv. Un număr impar lasă produsul total negativ.
 *      Cea mai bună felie atunci aruncă un prefix sau un sufix
 *      care conține negativul rămas — oricare aruncare doare mai
 *      puțin.
 *
 *   3. Un produs care rulează stânga-dreapta vede „aruncă un
 *      sufix”. Unul dreapta-stânga vede „aruncă un prefix”.
 *      Împreună acoperă ambele capete fără un tabel extra O(n).
 *      Considerăm și 0 însuși ca și candidat (un subtablou [0] are
 *      produs 0).
 *
 *   Exemplul {-2, 6, -3, -10, 0, 2}:
 *     Produse care rulează stânga-dreapta:  -2, -12, 36, -360, 0, 2.
 *     Dreapta-stânga:                        2, 0, -10, 30, 180, -360.
 *     Campionul e 180 = 6 * (-3) * (-10). O singură trecere
 *     stânga-dreapta nu raportează niciodată 180, pentru că felia
 *     aia nu începe la indicele 0 al segmentului ei. Trecerea
 *     inversă o găsește. De-asta două direcții nu sunt opționale.
 *
 * Complexitate
 *   Timp O(n): o trecere combinată (sau două treceri secvențiale).
 *   Memorie extra O(1): o mână de scalari long long. Fără tablou extra.
 *
 * Memorie
 *   int arr[], int n: fără copie a inputului. leftToRight, rightToLeft
 *   și maxProd sunt stocare automată. Cele două produse care rulează
 *   sunt doar întregi; nu stocăm tablourile de produse. Prăbușirea
 *   acelor tablouri la scalari e aceeași lecție ca Kadane. arr a
 *   decăzut la un pointer; n e lungimea.
 *
 * Teorie C — long long, overflow, zerouri și cache
 *   Produsele ies din int aproape imediat. 10 factori modești pot
 *   părăsi domeniul pe 32 de biți. Acumulăm în long long (cel puțin
 *   64 de biți). Overflow-ul pe signed al lui long long tot e UB;
 *   exemplul încape. Dacă produsele pot lovi 2^63, ai nevoie de o
 *   strategie mai mare (întregi mari, sau o constrângere a problemei
 *   care o interzice).
 *
 *   Resetul pe 0 e o decizie de control-flow, nu una de memorie.
 *   După ce înmulțești cu 0, produsul care rulează e 0; îl
 *   înregistrăm (0 poate fi răspunsul dacă tot restul e negativ),
 *   apoi restaurăm 1 ca următorul factor să înceapă un segment nou
 *   în loc să rămână 0 pentru totdeauna (0 * x == 0, care ar
 *   ascunde fiecare felie ulterioară).
 *
 *   Indexare de la ambele capete într-o buclă: arr[i] și arr[n-1-i].
 *   Ambele sunt valide cât timp i e în [0, n). Cele două fluxuri
 *   merg unul spre altul. Cache: două parcurgeri secvențiale ale
 *   unui buffer contig. E în regulă. Nu aloca două tablouri de
 *   produse de lungime n decât dacă ai nevoie de ele pentru o
 *   dovadă; scalarul ajunge.
 *
 *   INT_MIN ca factor: a nega INT_MIN pe 32 de biți e UB, dar noi
 *   înmulțim în long long, deci promovează întâi. arr[i] se
 *   convertește la long long pe *= cu un operand stâng long long.
 *
 * Exemplul afișează 180.
 */

#include <climits>
#include <iostream>
using namespace std;

long long maxProduct(int arr[], int n) {
    long long maxProd = LLONG_MIN;
    long long leftToRight = 1;
    long long rightToLeft = 1;
    for (int i = 0; i < n; i++) {
        if (leftToRight == 0) {
            leftToRight = 1;
        }
        if (rightToLeft == 0) {
            rightToLeft = 1;
        }
        leftToRight *= arr[i];
        int j = n - i - 1;
        rightToLeft *= arr[j];
        if (leftToRight > maxProd) {
            maxProd = leftToRight;
        }
        if (rightToLeft > maxProd) {
            maxProd = rightToLeft;
        }
    }
    return maxProd;
}

int main() {
    int arr[] = {-2, 6, -3, -10, 0, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << maxProduct(arr, n) << "\n";
    return 0;
}
