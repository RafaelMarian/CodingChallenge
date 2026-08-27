/*
 * LECȚIE — Partiționează negativele la stânga, pozitivele la dreapta
 *
 * Studentule, asta e ideea de partiție a lui Hoare aplicată la semn.
 * Nu e un sort stabil. Ordinea relativă din interiorul fiecărei părți
 * nu e păstrată. Dacă ai nevoie de ordine, ăsta e algoritmul greșit;
 * vezi RearrangePosNeg2 și apoi o partiție stabilă adevărată.
 *
 * Problemă
 *   Dat un tablou de întregi nenuli, rearanjează astfel încât fiecare
 *   valoare negativă să ocupe un prefix, iar fiecare valoare pozitivă
 *   să ocupe sufixul rămas. Pe loc. Ordinea într-o parte nu contează.
 *
 * Intuiție / Algoritm
 *   i pornește de la 0 și avansează cât timp celula e deja negativă
 *   (îi aparține stânga). j pornește de la n-1 și se retrage cât timp
 *   celula e deja pozitivă (îi aparține dreapta). Când amândoi se opresc,
 *   nums[i] e un pozitiv pe partea stângă a regiunii nepartiționate, iar
 *   nums[j] e un negativ pe partea dreaptă. Fă-le swap. Repetă până
 *   i >= j. Cei doi pointeri s-au încrucișat, deci tot tabloul e
 *   partiționat.
 *
 *   Ăsta e schema Hoare: crești un „stânga bun” din stânga, un „dreapta
 *   bun” din dreapta, și schimbi perechile puse greșit. Partiția originală
 *   din quicksort e același schelet, cu o comparație față de pivot în
 *   loc de un test de semn.
 *
 * Complexitate
 *   Timp  O(n): fiecare indice e scanat de cel mult un număr constant
 *   de ori.
 *   Memorie extra O(1): doi indici și un temporar pentru swap.
 *
 * Memorie
 *   int nums[] decade la un pointer. Store-uri pe loc, fără al doilea
 *   tablou. Cele n int-uri ale apelantului sunt reutilizate. Stivă: i,
 *   j, temp. Temporarul din swap e un int; nu e un tablou. Evităm
 *   vector dinadins.
 *
 *   Ai putea aloca două tablouri, copia negativele apoi pozitivele, și
 *   copia înapoi. Asta e O(n) memorie extra și două treceri. Partiția
 *   cu doi pointeri face treaba cu o mână de cuvinte.
 *
 * Teorie C — pointeri Hoare, zerouri, overflow, UB, cache
 *   Buclele interioare au nevoie de garda i < j (sau i < n, j >= 0).
 *   Fără ea, i poate fugi de capătul din dreapta căutând un pozitiv
 *   care nu există (toate celulele rămase negative). Citirea lui
 *   nums[i] cu i == n e comportament nedefinit. La fel pe stânga pentru j.
 *
 *   Zero: exemplul ăsta n-are zerouri. Un test strict < 0 / > 0 tratează
 *   0 ca „nu negativ” și „nu pozitiv,” deci ambele bucle interioare se
 *   opresc pe zero. Algoritmul ar face apoi swap pe zerouri fără o parte
 *   definită. Decide o politică (zerourile cu pozitivele, sau o partiție
 *   pe trei căi) înainte să trimiți asta. Dutch-national-flag e versiunea
 *   pe trei căi.
 *
 *   Swap prin temporar, nu XOR. Doi indici pot fi alias dacă ai face
 *   swap fără i < j; facem swap doar când i < j, deci celulele sunt
 *   distincte, dar XOR tot e obiceiul greșit.
 *
 *   Nicio aritmetică pe valorile elementelor în afară de testul de semn.
 *   Fără overflow. Valorile sunt copiate pe biți.
 *
 *   Cache: două fluxuri de la capete, ca la reverse. Swap-urile scriu
 *   două linii fierbinți. După un swap, i și j continuă, deci următoarele
 *   load-uri din bucla interioară sunt următoarele celule secvențiale.
 *   Localitate bună.
 *
 *   Mutația pe loc aruncă ordinea originală. Dacă apelantul încă are
 *   nevoie de ea, trebuie să copieze mai întâi. Documentează asta.
 *
 *   Formă C:
 *     void partition_sign(int a[], int n);
 *   Tablou gol: return înainte de n-1.
 */

#include <iostream>
using namespace std;

void rearrange(int arr[], int n) {
    if (n < 2) {
        return;
    }
    int i = 0;
    int j = n - 1;
    while (i < j) {
        while (i < j && arr[i] < 0) {
            i++;
        }
        while (i < j && arr[j] > 0) {
            j--;
        }
        if (i < j) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
}

int main() {
    int arr[] = {-2, 6, 3, -4, 1, 10, -5, 8, -7, -6};
    int n = sizeof(arr) / sizeof(arr[0]);
    rearrange(arr, n);
    for (int i = 0; i < n; i++) {
        if (i != 0) {
            cout << ' ';
        }
        cout << arr[i];
    }
    cout << '\n';
    return 0;
}
