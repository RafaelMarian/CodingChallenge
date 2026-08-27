/*
 * LECȚIE — Rotație la stânga cu k folosind trei inversări
 *
 * Studentule, deja știi rotate-by-one: salvezi capul, muți la stânga,
 * pui capul la coadă. Făcând asta de k ori e O(k n) atribuiri. Trei
 * inversări fac aceeași permutare în O(n) timp și O(1) memorie extra,
 * folosind reverse-ul cu doi pointeri pe care tocmai l-ai scris.
 *
 * Problemă
 *   Rotește tabloul la stânga cu k poziții. Indicele 0 se mută la
 *   indicele n-k (modulo n), și tot așa. Pentru {1,2,3,4} și k = 5,
 *   k modulo 4 e 1, deci rezultatul e {2,3,4,1}.
 *
 * Intuiție / Algoritm
 *   O rotație la stânga cu k e: prefixul de lungime k se mută la capăt,
 *   sufixul de lungime n-k se mută în față, ambele blocuri păstrându-și
 *   ordinea internă.
 *
 *   Identitate: reverse(reverse(A) + reverse(B)) = B + A pentru concatenare.
 *   Într-un tablou care e prefixul A de lungime k și sufixul B:
 *     reverse A, reverse B, reverse tot tabloul
 *   dă B apoi A, care e o rotație la stânga cu k.
 *
 *   Urmărește pe {1,2,3,4}, k = 1:
 *     reverse [0,0]:        {1,2,3,4}
 *     reverse [1,3]:        {1,4,3,2}
 *     reverse [0,3]:        {2,3,4,1}
 *
 *   k %= n ca rotația cu n, 2n, ... să fie un no-op, iar k = 5 pe n = 4
 *   e același lucru cu k = 1. Dacă k e negativ într-un API, ai converti
 *   la o rotație la stânga echivalentă în [0, n). Lecția asta ia k >= 0.
 *
 * Complexitate
 *   Timp  O(n): trei inversări liniare, fiecare O(n).
 *   Memorie extra O(1): temporarul din reverse. Fără al doilea buffer.
 *   Un tablou nou care scrie nums[(i+k)%n] în dst[i] e O(n) memorie
 *   extra. Metoda cu inversări evită alocarea aia.
 *
 * Memorie
 *   int nums[] decade la un pointer. Mutație pe loc a celor n celule
 *   ale apelantului. reverse scrie perechi de celule existente. Evităm
 *   vector dinadins. Fără resize. Proprietatea nu se schimbă pentru că
 *   nu există un obiect proprietar: tabloul e doar n int-uri.
 *
 *   Păzește n == 0 înainte de k %= n. Restul cu divisor 0 e comportament
 *   nedefinit în C și C++ (pe întregi). Un tablou gol n-are ce să
 *   rotească; return.
 *
 * Teorie C — modulo, limitele lui reverse, overflow, cache, memmove
 *   k %= n. Dacă k și n sunt int și n e pozitiv, rezultatul e în
 *   [0, n). Ține ambele tipuri int ca un k negativ să nu devină tăcut
 *   un rest unsigned uriaș.
 *
 *   reverse(0, k-1) pe k == 0: nu forma k-1. O rotație de lungime zero
 *   e un no-op; sari inversările sau fă reverse un no-op când intervalul
 *   e gol. Ne întoarcem devreme pe r == 0.
 *
 *   reverse-ul cu doi pointeri nu trebuie să citească după capete.
 *   Transmite indici inclusiv care sunt < n. Formarea lui lo + hi ca
 *   mijloc int nu e nevoie aici; doar umblăm spre interior.
 *
 *   Rotație pe blocuri cu memmove: salvează prefixul de k int-uri, mută
 *   sufixul la stânga cu k, copiază prefixul în coadă. Asta e tot O(n)
 *   timp și O(k) memorie extra pentru prefixul salvat (sau faci memmove
 *   cu overlap cu un temp de k). Trei inversări folosesc O(1) extra
 *   și doar swap-uri. memmove e permis să se suprapună; memcpy nu.
 *   Dacă vreodată muți cu memcpy pe intervale care se suprapun, ăsta
 *   e UB.
 *
 *   Cache: fiecare reverse e două fluxuri secvențiale. Trei dintre ele
 *   tot bat k deplasări complete. Permutarea e făcută cu localitate bună.
 *
 *   Overflow pe întregi: nu adunăm valorile elementelor. Indicii rămân
 *   în interval dacă reduci k și sari n == 0.
 *
 *   Pe loc: ordinea originală e înlocuită de ordinea rotită în aceleași
 *   celule.
 */

#include <iostream>
using namespace std;

void reverseRange(int nums[], int i, int j) {
    while (i < j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
        i++;
        j--;
    }
}

void rotateLeft(int nums[], int n, int k) {
    if (n == 0) {
        return;
    }
    int r = k % n;
    if (r == 0) {
        return;
    }
    reverseRange(nums, 0, r - 1);
    reverseRange(nums, r, n - 1);
    reverseRange(nums, 0, n - 1);
}

int main() {
    int nums[] = {1, 2, 3, 4};
    int n = sizeof(nums) / sizeof(nums[0]);
    rotateLeft(nums, n, 5);
    for (int i = 0; i < n; i++) {
        cout << nums[i] << '\n';
    }
    return 0;
}
