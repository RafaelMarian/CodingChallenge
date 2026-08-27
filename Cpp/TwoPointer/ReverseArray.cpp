/*
 * LECȚIE — Inversează un tablou pe loc cu doi indici
 *
 * Studentule, începe de aici. Inversarea e cea mai simplă mutație cu
 * doi pointeri, iar fiecare algoritm pe loc din folderul ăsta e o
 * variație a aceleiași idei: doi indici, un invariant de buclă și
 * câteva atribuiri.
 *
 * Problemă
 *   Inversează secvența astfel încât primul element să ajungă ultimul,
 *   iar ultimul primul. Fă-o în buffer-ul existent. Nu aloca un al
 *   doilea tablou.
 *
 * Intuiție / Algoritm
 *   Pune i pe celula din stânga și j pe cea din dreapta. Cât timp i < j,
 *   schimbă cele două celule, apoi apropie-le: i++, j--. Când indicii
 *   se întâlnesc sau se încrucișează, fiecare pereche (k, n-1-k) a fost
 *   schimbată prin swap exact o dată.
 *   Un tablou de lungime impară lasă elementul din mijloc neatins, ceea
 *   ce e corect: e deja pe poziția lui finală.
 *
 *   Invariantul e: după t swap-uri, prefixul de lungime t și sufixul
 *   de lungime t sunt capetele inversate gata, iar intervalul deschis
 *   (i, j) e mijlocul încă neinversat.
 *
 * Complexitate
 *   Timp  O(n): fiecare element e citit și scris de un număr constant
 *   de ori.
 *   Memorie extra O(1): un int temporar, plus cei doi indici. Tabloul
 *   nu crește. Suprascriem aceleași n celule.
 *
 * Memorie
 *   Parametrul e int nums[] plus int n. În C și C++, un parametru
 *   tablou decade la un pointer către primul int. nums e de fapt int*.
 *   Pointerul nu știe câte celule urmează, de-asta transmitem n noi
 *   întotdeauna. Evităm vector dinadins: un tablou C în main e un
 *   bloc contig de int-uri (aceste exemple trăiesc pe stivă).
 *   Transmiterea lui nums transmite un pointer. Nu copiem cele n int-uri.
 *   Suprascriem celule. Fără alocare pe heap, fără destructor de ținut minte.
 *
 *   nums[i] e *(nums + i). Asta e aritmetică de pointer. i trebuie să
 *   rămână în [0, n). Lungimea stă în n, nu în pointer.
 *
 * Teorie C — swap, aliasing, XOR, cache
 *   Un swap corect a două int-uri sunt trei atribuiri printr-un temporar:
 *     int temp = a[i];
 *     a[i]     = a[j];
 *     a[j]     = temp;
 *   temp e o locală pe stivă, aproape sigur un registru. Două load-uri,
 *   două store-uri. Ăsta e codul mașină pe care îl vrei.
 *
 *   Nu face XOR-swap. Secvența din folclor
 *     x ^= y; y ^= x; x ^= y;
 *   eșuează dacă x și y sunt alias pentru același obiect: x ^= x golește
 *   celula la zero, și valoarea e dusă. Chiar când celulele sunt distincte,
 *   XOR creează un lanț de dependență serială de trei operații. Un temporar
 *   în registru e mai rapid pe orice CPU modern. XOR nu se generalizează
 *   nici la tipuri care nu sunt întregi pe biți. Tratează-l ca o curiozitate,
 *   nu ca o unealtă.
 *
 *   Întregii signed nu dau overflow aici: doar copiem biți dintr-o
 *   celulă în alta. Ieșirea din interval e UB-ul de care trebuie să
 *   te temi. Dacă ai scrie j = n fără -1, prima citire a lui nums[j]
 *   e după capăt. Compilatorul nu-ți datorează nimic: crash, corupere
 *   tăcută, sau „a mers pe mașina mea.” Păzește n < 2 înainte să
 *   calculezi n-1, ca să nu formezi un indice fals pe un tablou gol.
 *
 *   Parcurgerea e secvențială de la ambele capete. Fiecare capăt
 *   curge prin linii de cache (de obicei 64 de octeți, 16 int-uri).
 *   Două fluxuri secvențiale rămân prietenoase cu cache-ul. Un reverse
 *   pe listă înlănțuită ar urmări noduri pe heap și ar rata constant.
 *   Stocarea contiguă e tot punctul.
 *
 *   Mutația pe loc înseamnă că tabloul apelantului e output-ul. După
 *   ce reverse se întoarce, ordinea originală e dusă, decât dacă
 *   apelantul a copiat-o înainte.
 */

#include <iostream>
using namespace std;

void reverse(int nums[], int n) {
    if (n < 2) {
        return;
    }
    int i = 0;
    int j = n - 1;
    while (i < j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
        i++;
        j--;
    }
}

int main() {
    int nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(nums) / sizeof(nums[0]);
    reverse(nums, n);
    for (int i = 0; i < n; i++) {
        cout << nums[i] << '\n';
    }
    return 0;
}
