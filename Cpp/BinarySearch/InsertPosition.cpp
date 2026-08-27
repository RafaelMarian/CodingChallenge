/*
 * LECȚIE — Poziția de inserare (lower_bound)
 *
 * Studentule, întoarce indicele lui target dacă e prezent. Dacă nu, întoarce
 * indicele unde l-ai insera ca tabloul să rămână sortat.
 * Exemplul {3,4,6,7,10,11,13,15}, target 16: 16 stă la capăt,
 * indicele 8.
 *
 * Intuiție
 *   Asta e lower_bound: prima poziție unde elementul nu e mai mic
 *   decât target, adică primul i cu nums[i] >= target. Căutare
 *   binară ca de obicei. Pe nums[mid] == target întorci mid (orice
 *   indice egal e un „găsit” legal; lower_bound ar întoarce cel mai
 *   din stânga, pe care varianta asta nu-l garantează dacă există
 *   duplicate — exemplul n-are).
 *
 *   Când bucla se termină, l > h. Invariantul e: tot ce e la stânga
 *   lui l e < target, tot ce e la dreapta lui h e > target. Deci l
 *   e indicele de inserare. Întoarce l. Nu inspecta mid după buclă.
 *   mid e vechi: e ce-a calculat ultima iterație, iar un test de
 *   forma (target < nums[mid] ? mid : mid+1) e un mod fragil de a
 *   reconstrui ce e deja l. Pentru target 16, l se oprește la 8.
 *
 * Complexitate
 *   Timp O(log n), memorie extra O(1).
 *
 * Memorie
 *   int nums[], int n. Fără buffer extra. Nu inserăm; doar raportăm
 *   indicele. Inserarea în sine ar fi O(n) ca să muți un tablou
 *   contig. Aia e o altă funcție. nums a decăzut la int*; n e
 *   lungimea vie.
 *
 * Teorie C — lower_bound, one-past-the-end, overflow
 *   Dacă target e mai mare decât orice element, l devine n. Ăsta e
 *   un indice valid de inserare și nu un indice valid de acces. Nu
 *   întoarce nums[l] fără o verificare de limite. Să întorci l ca
 *   întreg e în regulă: apelantul decide dacă inserează.
 *
 *   Dacă target e mai mic decât orice element, l rămâne 0.
 *
 *   Analogul C e punctul de inserare într-un buffer sortat:
 *       int i = 0;
 *       while (i < n && a[i] < target) i++;
 *   ăsta e liniar. Căutarea binară e varianta logaritmică a
 *   aceluiași predicat „slotul ăsta e încă < target?”
 *
 *   mid = l + (h - l) / 2. (l + h) / 2 poate da overflow. Ai mai
 *   auzit asta pentru că e bug-ul care tot ajunge în producție.
 *
 * Exemplul afișează 8.
 */

#include <iostream>
using namespace std;

int searchInsert(int nums[], int n, int target) {
    int l = 0;
    int h = n - 1;
    while (l <= h) {
        int mid = l + (h - l) / 2;
        if (nums[mid] == target) {
            return mid;
        }
        if (nums[mid] > target) {
            h = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return l;
}

int main() {
    int nums[] = {3, 4, 6, 7, 10, 11, 13, 15};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << searchInsert(nums, n, 16) << "\n";
    return 0;
}
