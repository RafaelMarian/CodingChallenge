/*
 * LECȚIE — Partiție în trei (drapelul olandez)
 *
 * Studentule, partiționăm un tablou în trei benzi contigue:
 *
 *     [ valori < 2 | valori == 2 | valori > 2 ]
 *
 * Exemplul e 1, 2 și 3, nu colorarea din manual 0/1/2. Pivotul e 2.
 * Algoritmul nu-i pasă ce sunt cele trei etichete, doar că putem
 * testa < pivot, == pivot, > pivot.
 *
 * Intuiție
 *   Trei indici:
 *     low  — primul slot care încă nu e știut ca < 2
 *     mid  — cursorul; tot ce e în [low, mid) e == 2 deja
 *            de fapt: [0, low) e < 2, [low, mid) e == 2,
 *            (high, n) e > 2, iar [mid, high] e neexaminat.
 *     high — ultimul slot care încă nu e știut ca > 2
 *
 *   Bucla while (mid <= high) (intervalul închis neexaminat e ne-gol):
 *     nums[mid] <  2: swap cu nums[low], low++, mid++.
 *                     Valoarea pe care am adus-o prin swap a venit
 *                     de pe muchia stângă a benzii ==2. E un 2 pe
 *                     care l-am văzut deja, sau e aceeași celulă.
 *                     Oricum e examinată. Avansează mid.
 *     nums[mid] == 2: deja în banda din mijloc. mid++.
 *     nums[mid] >  2: swap cu nums[high], high--.
 *                     NU incrementa mid. Valoarea care tocmai a
 *                     sosit din dreapta e neexaminată. Poate fi
 *                     < 2, == 2 sau > 2. mid trebuie s-o vadă la
 *                     iterația următoare.
 *
 *   Ultimul punct e toată lecția. Swap-ul cu high trage un necunoscut
 *   pe scaunul lui mid. Swap-ul cu low trage un 2 cunoscut (sau
 *   același element) pe scaunul lui mid, deci mid poate avansa.
 *
 * Complexitate
 *   O trecere. Fiecare iterație fie mid++ fie high-- (sau ambele,
 *   pe ramura < 2). Intervalul neexaminat se strânge la fiecare pas.
 *   Timp O(n). Memorie extra O(1): trei indici și un temporar pentru
 *   swap. Pe loc. Tabloul apelantului e mutat.
 *
 * Memorie
 *   int nums[], int n: permutăm pe loc. Fără buffer extra. Swap-ul
 *   a doi int e trei mutări ale unui cuvânt de lățimea registrului;
 *   fără heap. Tabloul e contig, deci fiecare swap atinge două linii
 *   de cache în cel mai rău caz (low/mid/high pot sta departe). Tot
 *   spațiu extra O(1). nums a decăzut la int*; scrierile prin
 *   pointerul ăla schimbă tabloul din main. Asta e transmitere prin
 *   pointer, nu o copie.
 *
 * Teorie C — partiție, swap, aliasing, UB
 *   E partiția în trei a lui Dijkstra, aceeași idee care face
 *   quicksort 3-way rapid pe duplicate. Swap:
 *       int t = a[i]; a[i] = a[j]; a[j] = t;
 *
 *   Pointeri: low, mid, high ar putea fi int* în buffer în loc de
 *   indici. a[mid] e *(a + mid). Invariantul e despre intervale de
 *   adrese, nu despre obiecte.
 *
 *   De ce nu incrementezi mid pe swap-ul cu high: dacă ai face-o,
 *   ai sări o valoare neexaminată. Valoarea aia ar sta în banda
 *   din mijloc pentru totdeauna. Invariantul „[low, mid) e tot 2”
 *   ar fi fals. Ăsta e un bug de logică, nu un crash; output-ul ar
 *   fi prost partiționat. Urmărește {2,1,3} de mână în ambele feluri.
 *
 *   Limite: mid și high sunt valide cât timp mid <= high și ambele
 *   au pornit în tablou. După high--, high poate deveni -1; testul
 *   buclei mid <= high eșuează atunci. Nu citi nums[high] după aia.
 *   Condiția while e garda. Să citești nums[-1] e UB.
 *
 *   Cache: trei indici care se mișcă, nu o parcurgere secvențială.
 *   Tot atingeri liniare ale unui buffer contig. Mult mai bine decât
 *   să aloci trei tablouri de output și să le concatenezi.
 *
 * Exemplul {2,1,3,2,1,3,3,1,2,1} devine 1,1,1,1,2,2,2,3,3,3
 * afișat câte unul pe linie.
 */

#include <iostream>
using namespace std;

void arrangeColors(int nums[], int n) {
    int low = 0;
    int mid = 0;
    int high = n - 1;
    while (mid <= high) {
        if (nums[mid] < 2) {
            int t = nums[low];
            nums[low] = nums[mid];
            nums[mid] = t;
            low++;
            mid++;
        } else if (nums[mid] > 2) {
            int t = nums[high];
            nums[high] = nums[mid];
            nums[mid] = t;
            high--;
        } else {
            mid++;
        }
    }
}

int main() {
    int nums[] = {2, 1, 3, 2, 1, 3, 3, 1, 2, 1};
    int n = sizeof(nums) / sizeof(nums[0]);
    arrangeColors(nums, n);
    for (int i = 0; i < n; i++) {
        cout << nums[i] << "\n";
    }
    return 0;
}
