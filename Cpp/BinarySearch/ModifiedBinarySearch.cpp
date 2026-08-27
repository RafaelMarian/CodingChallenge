/*
 * LECȚIE — Căutare într-un tablou sortat rotit (elemente distincte)
 *
 * Studentule, tabloul a fost sortat crescător, apoi rotit la un pivot necunoscut:
 * un sufix a fost mutat în față. Exemplul
 * {6,7,8,9,11,13,14,2,3,5} e {2,3,5,6,7,8,9,11,13,14} rotit.
 * Găsește indicele lui key, sau -1. Exemplul cu key 3 e la indicele 8.
 *
 * Intuiție
 *   Într-un tablou rotit cu valori distincte, una dintre cele două
 *   jumătăți din jurul lui mid e mereu sortată (cealaltă conține
 *   cusătura de rotație). Testează care jumătate e sortată, apoi
 *   întreabă dacă key stă în jumătatea sortată. Dacă da, arunci
 *   cealaltă. Dacă nu, arunci jumătatea sortată. Tot arunci cam
 *   jumătate din interval la fiecare pas, deci căutarea e binară.
 *
 *   Cum recunoști o jumătate sortată: nums[l] <= nums[mid] înseamnă
 *   că [l, mid] e sortat (n-are cusătură acolo). Altfel cusătura e
 *   pe stânga și [mid, h] e sortat.
 *
 *   Apoi, pentru o jumătate stângă sortată, key e în ea când
 *   nums[l] <= key < nums[mid]. Simetric pe dreapta:
 *   nums[mid] < key <= nums[h]. Egalitățile de la capete sunt
 *   pentru că intervalul e închis; mid însuși a fost deja testat.
 *
 * Complexitate
 *   Timp O(log n), memorie extra O(1). Ca la căutarea binară obișnuită.
 *   Distincția e necesară ca testul „o jumătate e sortată” să fie
 *   decisiv. Duplicatele cer o altă lecție (SearchRotatedDuplicate.cpp).
 *
 * Memorie
 *   int nums[], int n, trei int. Fără alocare. Acces aleator într-un
 *   buffer contig, aceeași poveste de cache ca la căutarea binară
 *   clasică: load-uri logaritmice, nu o parcurgere liniară. Decay-ul
 *   tablou→pointer înseamnă că n e obligatoriu.
 *
 * Teorie C — rotație, invarianți, overflow, distincție
 *   Rotația nu amestecă. E o tăietură: concatenezi nums[k..n) cu
 *   nums[0..k). Ambele bucăți sunt sortate. De-asta o jumătate fără
 *   tăietură e sortată. Dacă ai vrea să derotezi, ai căuta minimul
 *   (FindMinRotatedArray.cpp) și apoi ai căuta binar într-una din
 *   cele două bucăți sortate. Varianta cu o singură buclă de mai jos
 *   face ambele treburile deodată.
 *
 *   mid = l + (h - l) / 2, niciodată (l + h) / 2. Overflow-ul pe
 *   signed al lui l + h e UB. Recitește BinarySearch.cpp dacă
 *   propoziția asta nu e încă automată.
 *
 *   Valori distincte: dacă nums[l] == nums[mid] nu poți spune care
 *   jumătate e sortată. Exemplul n-are duplicate, deci <= ajunge.
 *
 *   nums[mid] e *(nums + mid). Rotația e o proprietate a șirului,
 *   nu a pointerului.
 *
 * Exemplul afișează 8.
 */

#include <iostream>
using namespace std;

int modBinarySearch(int nums[], int n, int key) {
    int l = 0;
    int h = n - 1;
    while (l <= h) {
        int mid = l + (h - l) / 2;
        if (key == nums[mid]) {
            return mid;
        }
        if (nums[l] <= nums[mid]) {
            if (key >= nums[l] && key < nums[mid]) {
                h = mid - 1;
            } else {
                l = mid + 1;
            }
        } else if (key > nums[mid] && key <= nums[h]) {
            l = mid + 1;
        } else {
            h = mid - 1;
        }
    }
    return -1;
}

int main() {
    int nums[] = {6, 7, 8, 9, 11, 13, 14, 2, 3, 5};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << modBinarySearch(nums, n, 3) << "\n";
    return 0;
}
