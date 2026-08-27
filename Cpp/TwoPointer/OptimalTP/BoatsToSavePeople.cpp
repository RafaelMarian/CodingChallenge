/*
 * LECȚIE — Bărci ca să salvezi oamenii
 *
 * Studentule, fiecare barcă duce cel mult două persoane și cel mult
 * `limit` greutate totală. Împerecherea greedy a celei mai ușoare
 * persoane rămase cu cea mai grea persoană rămasă e optimală, iar
 * doi pointeri după un sort implementează greedy-ul ăla în timp extra
 * liniar.
 *
 * Problemă
 *   people[i] e o greutate. Numără numărul minim de bărci. Exemplu:
 *   {4,2,8,3,1,6,2,5}, limit 8, răspuns 5.
 *
 * Intuiție / Algoritm
 *   Sortează nedescrescător. i e cel mai ușor nefolosit, j cel mai
 *   greu nefolosit. Cea mai grea persoană are întotdeauna nevoie de
 *   o barcă. Dacă cea mai ușoară poate împărți barca aia
 *   (people[i] + people[j] <= limit), ia-i pe amândoi; altfel cea mai
 *   grea merge singură. În ambele cazuri consumă j. Doar cazul de
 *   împărțire consumă i. Repetă până i > j.
 *
 *   De ce e optimal: cea mai grea persoană nu poate împărți cu nimeni
 *   mai greu (nu există nimeni mai greu). Dacă nu poate împărți cu cea
 *   mai ușoară curentă, nu poate împărți cu nimeni. Dacă poate, ar
 *   trebui s-o împerechezi cu cineva, iar împerecherea cu cea mai
 *   ușoară lasă greutățile medii pentru alte împerecheri. Să trimiți
 *   cea mai grea singură când o pereche era posibilă irosește un loc
 *   de care cea mai ușoară s-ar putea să n-aibă nevoie mai târziu —
 *   de fapt demonstrația e: să-i dai celei mai grele pe cea mai ușoară
 *   ca partener (când e fezabil) nu strică niciodată, pentru că cea
 *   mai ușoară era cea mai probabilă să încapă.
 *
 *   Când i == j, rămâne o persoană. Codul tot numără o barcă.
 *   people[i] + people[j] e atunci de două ori persoana aia; dacă se
 *   întâmplă să fie <= limit tot incrementezi o dată și muți ambii
 *   pointeri, ceea ce e o barcă pentru o persoană. Corect, chiar dacă
 *   un pic accidental. Ramura else tot numără o barcă și decrementează
 *   j, lăsând i > j. Tot corect. Nu „împerechea” două copii ale ultimei
 *   persoane pe două locuri ale unei bărci ca și cum ar fi două persoane.
 *
 * Complexitate
 *   Timp  O(n log n) de la sort, apoi O(n) împerechere.
 *   Memorie extra O(1) pe lângă stiva lui sort, dacă sortăm pe loc.
 *
 * Memorie
 *   int people[] decade la un pointer. sort(people, people+n) sortează
 *   buffer-ul apelantului. Ordinea originală a oamenilor e pierdută.
 *   Dacă ai avea nevoie de ea, copiază mai întâi. Funcția nu alocă un
 *   al doilea tablou de people. Evităm vector dinadins. Doi indici și
 *   un contor pe stivă.
 *
 * Teorie C — sort, overflow-ul sumei perechii, cache, UB
 *   people[i] + people[j] ca int poate da overflow. O greutate de
 *   INT_MAX plus orice pozitiv e UB la adunarea signed. Compară cu
 *     1LL * people[i] + people[j] <= limit
 *   promovând limit la long long. Exemplul nu e nicăieri pe-acolo.
 *
 *   sort permutează cele n int-uri cu O(n log n) atribuiri. După aia
 *   trecerea cu doi pointeri e secvențială de la ambele capete: comportament
 *   bun de cache pe tabloul sortat. sort-ul însuși are localitate mai
 *   proastă; tot e unealta potrivită.
 *
 *   i și j ca int, buclă cât timp i <= j. Când sunt egali, amândoi
 *   indexează o celulă vie. După j-- de la 0, j devine -1. Condiția
 *   e verificată la cap: dacă i era 0 și j era 0, procesăm, j devine
 *   -1, și i <= j e 0 <= -1, care e fals. signed e potrivirea naturală
 *   pentru un indice înalt care se micșorează și poate trece de zero.
 *
 *   Gol: 0 bărci. Ne întoarcem 0 fără n-1.
 *
 *   Mutație pe loc: sort. Împerecherea n-are nevoie de scrieri
 *   ulterioare.
 */

#include <algorithm>
#include <iostream>
using namespace std;

int numRescueBoats(int people[], int n, int limit) {
    if (n == 0) {
        return 0;
    }
    sort(people, people + n);
    int i = 0;
    int j = n - 1;
    int boats = 0;
    long long cap = limit;
    while (i <= j) {
        if (1LL * people[i] + people[j] <= cap) {
            i++;
        }
        boats++;
        j--;
    }
    return boats;
}

int main() {
    int arr[] = {4, 2, 8, 3, 1, 6, 2, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << numRescueBoats(arr, n, 8) << '\n';
    return 0;
}
