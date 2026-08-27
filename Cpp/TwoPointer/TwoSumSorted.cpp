/*
 * LECȚIE — Two-sum pe un tablou sortat, indici 1-based
 *
 * Studentule, two-sum nesortat vrea o tabelă hash. Two-sum sortat nu.
 * Ordinea e informație. Folosește-o.
 *
 * Problemă
 *   Intrarea e sortată nedescrescător. Tipărește o pereche de indici
 *   1-based i j, i < j, astfel încât nums[i-1] + nums[j-1] == target.
 *   Exemplul are un răspuns unic. Dacă nu există niciunul, tipărește
 *   0 0, care nu e o pereche 1-based validă.
 *
 * Intuiție / Algoritm
 *   i pornește de la cea mai mică valoare, j de la cea mai mare. Fie
 *   s suma lor. Pentru că tabloul e sortat:
 *     - dacă s == target, ai terminat;
 *     - dacă s < target, nu există un partener mai mare pentru nums[i]
 *       la stânga lui j, deci singura cale să crești s e i++;
 *     - dacă s > target, singura cale să scazi s e j--.
 *   Fiecare pas aruncă un indice pentru totdeauna. Examinezi O(n)
 *   perechi candidate, nu O(n^2).
 *
 *   De ce mutarea celuilalt pointer nu ajută: dacă s e prea mică,
 *   fiecare pereche (i, k) pentru k < j e și mai mică, deci perechile
 *   alea sunt moarte. Ordinea sortată face afirmația asta adevărată.
 *   Nesortat, e falsă, și algoritmul ăsta e incorect.
 *
 * Complexitate
 *   Timp  O(n) după ce tabloul e deja sortat. Dacă ar trebui să sortezi,
 *   ar fi O(n log n) și ar amesteca indicii originali; problema îți
 *   dă un tablou sortat și cere indici în el, deci nu trebuie să
 *   sortezi o copie pe care apoi o indexezi.
 *   Memorie extra O(1): doi indici. Îi tipărim. Nu-i împachetăm într-un
 *   obiect pair.
 *
 * Memorie
 *   int nums[] decade la int*. Transmite n pentru că pointerul n-are
 *   lungime. Evităm vector dinadins. Doar citire: fără copie, fără heap.
 *   Răspunsul sunt două int-uri pe care le tipărim. Buffer-ul de intrare
 *   rămâne unde l-a pus apelantul. Doar încărcăm.
 *
 * Teorie C — overflow-ul sumei, pointeri vs indici, cache
 *   Operația periculoasă e nums[i] + nums[j]. Ambele sunt int.
 *   Overflow-ul adunării signed e comportament nedefinit. INT_MAX + 1
 *   nu e garantat să se înfășoare; compilatorul poate șterge ramuri
 *   care presupun că nu se poate întâmpla. Calculează suma în long long:
 *     1LL * nums[i] + nums[j]
 *   1LL forțează prima înmulțire/promovare; restul adunării se
 *   întâmplă apoi pe cel puțin 64 de biți. INT_MAX + INT_MAX încape
 *   într-un long long signed pe 64 de biți.
 *
 *   Compară long long-ul ăla cu target după ce promovezi target, sau
 *   scrie sum == (long long)target. Comparația de lățimi mixte promovează
 *   int-ul.
 *
 *   Indici versus pointeri: ai putea umbla cu int *p = nums și
 *   int *q = nums + (n-1), și compara p < q. Comparația de pointeri
 *   e bine definită doar în interiorul aceluiași obiect tablou (sau
 *   one-past-end). Indicii sunt mai greu de greșit când ai nevoie și
 *   de output 1-based: răspunsul e i+1 și j+1. Aici i < n, deci i+1
 *   încape în int pentru dimensiunile din cursul ăsta.
 *
 *   Cache: i merge înainte, j merge înapoi, fiecare secvențial. Atingi
 *   fiecare element cel mult o dată. Liniar și bun pentru prefetch.
 *
 *   Indicii 1-based sunt o alegere de API (comună în enunțuri de tip
 *   „primul număr e pe poziția 1”). Off-by-one trăiește aici: să tipărești
 *   i și j fără +1 e un răspuns greșit tăcut, nu un crash. Verifică
 *   exemplul: {2,3,5,7,9,12,16,23,26,29} target 30 -> 4 8
 *   (valorile 7 și 23).
 */

#include <iostream>
using namespace std;

void twoSum(int nums[], int n, int target) {
    if (n < 2) {
        cout << "0 0\n";
        return;
    }
    int i = 0;
    int j = n - 1;
    long long need = target;
    while (i < j) {
        long long sum = 1LL * nums[i] + nums[j];
        if (sum == need) {
            cout << i + 1 << ' ' << j + 1 << '\n';
            return;
        }
        if (sum < need) {
            i++;
        } else {
            j--;
        }
    }
    cout << "0 0\n";
}

int main() {
    int nums[] = {2, 3, 5, 7, 9, 12, 16, 23, 26, 29};
    int n = sizeof(nums) / sizeof(nums[0]);
    twoSum(nums, n, 30);
    return 0;
}
