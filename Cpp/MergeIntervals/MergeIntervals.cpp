/*
 * LECȚIE — Unește intervalele care se suprapun, pe loc, după o sortare
 *
 * Studentule, primești o listă de intervale închise [start, end] stocate ca un
 * tablou C cu două coloane: int nums[][2]. Intervalele care se
 * suprapun sau se ating se unesc într-unul. Întoarce noua lungime
 * a listei compactate. Intervalele care supraviețuiesc stau în
 * față, în același tablou.
 *
 * Intuiție
 *   După ce sortezi după start, suprapunerile devin o întrebare
 *   locală: intervalul curent începe înainte sau la capătul
 *   intervalului pe care-l întindem acum? Dacă prev.end >=
 *   cur.start, se suprapun (sau se ating). Întinde prev.end la
 *   max(prev.end, cur.end). Dacă nu se suprapun, avansează un
 *   indice de scriere și copiază cur în slotul ăla. Indicele de
 *   scriere e compactarea pe loc: suprascriem sloturi care țineau
 *   intervale deja absorbite.
 *
 *   Exemplul {{6,8},{1,9},{2,4},{4,7}}:
 *     sortat după start: {1,9}, {2,4}, {4,7}, {6,8}
 *     {1,9} înghite toate cele trei de mai târziu pentru că 9 >=
 *     fiecare start. Rămâne un interval: [1, 9].
 *
 * Complexitate
 *   Sortare O(n log n) în general; fișierul ăsta folosește un
 *   swap simplu O(n^2) pe rânduri la n = 4. Trecerea de unire O(n).
 *   Memorie extra O(1). Output-ul e scris peste input. Valoarea
 *   întoarsă e noua lungime logică. Apelanții trebuie să folosească
 *   lungimea întoarsă, nu n original.
 *
 * Memorie
 *   int nums[][2]: un bloc contig de n perechi de int. nums[i][0]
 *   e start, nums[i][1] e end. Într-un parametru prima dimensiune
 *   decade: tipul e pointer-la-tablou-de-2-int, int (*p)[2].
 *   sizeof(nums) în mergeOverlap e dimensiunea pointerului ăla,
 *   nu n * 2 * sizeof(int). Transmiți n. A doua dimensiune [2]
 *   rămâne în tip ca compilatorul să poată scala rândul i cu 8
 *   octeți.
 *
 *   De ce nu sort(nums, nums + n)? sort are nevoie de un tip de
 *   element asignabil. Un rând int[2] e un tablou; tablourile nu
 *   se pot asigna. Swap-uim noi cele două coloane. Ăsta e C cinstit.
 *
 *   Compactarea cu indice de scriere nu alocă. Copiază doi int
 *   într-un rând anterior. Fără rânduri noi.
 *
 * Teorie C — suprapunere, compactare pe loc, cache
 *   Așezare: patru intervale sunt opt int la rând în memorie:
 *       6, 8, 1, 9, 2, 4, 4, 7
 *   nums[i][j] e *(*(nums + i) + j), pe care compilatorul îl
 *   transformă într-un singur offset scalat de la bază. Struct-uri
 *   contigue {int s, e;} sunt aceiași octeți cu nume.
 *
 *   Suprapunere pentru intervale închise: prev.end >= cur.start.
 *   Dacă problema folosea semi-deschise [s, e), capetele care se
 *   ating n-ar suprapune și testul ar fi prev.end > cur.start.
 *   Știi în ce topologie ești. Exemplul tratează [2,4] și [4,7]
 *   ca suprapuse.
 *
 *   Compactarea pe loc e același tipar ca scoaterea duplicatelor
 *   cu un scriitor lent: un indice de citire i și un indice de
 *   scriere prevIdx. Sloturile din spatele lui prevIdx sunt
 *   terminate. Nu micșorăm tabloul; întoarcem câte sloturi sunt
 *   vii. Să citești peste lungimea aia e o eroare de logică (ai
 *   vedea rânduri rămase neunite). În afara limitelor tabloului
 *   însuși e UB; rândurile rămase tot sunt în limite.
 *
 *   Cache: trecerea de unire e secvențială pe un buffer contig cu
 *   2 coloane. start și end ale unui interval stau pe aceeași linie.
 *
 * Afișare: "The Merged Intervals are: " apoi perechi [start, end].
 * Exemplul afișează: The Merged Intervals are: [1, 9]
 */

#include <iostream>
using namespace std;

int mergeOverlap(int nums[][2], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (nums[j][0] < nums[i][0]) {
                int t0 = nums[i][0];
                int t1 = nums[i][1];
                nums[i][0] = nums[j][0];
                nums[i][1] = nums[j][1];
                nums[j][0] = t0;
                nums[j][1] = t1;
            }
        }
    }
    int prevIdx = 0;
    for (int i = 1; i < n; i++) {
        if (nums[prevIdx][1] >= nums[i][0]) {
            if (nums[i][1] > nums[prevIdx][1]) {
                nums[prevIdx][1] = nums[i][1];
            }
        } else {
            prevIdx++;
            nums[prevIdx][0] = nums[i][0];
            nums[prevIdx][1] = nums[i][1];
        }
    }
    return prevIdx + 1;
}

int main() {
    int nums[][2] = {{6, 8}, {1, 9}, {2, 4}, {4, 7}};
    int n = sizeof(nums) / sizeof(nums[0]);
    int newSize = mergeOverlap(nums, n);
    cout << "The Merged Intervals are: ";
    for (int i = 0; i < newSize; i++) {
        cout << "[" << nums[i][0] << ", " << nums[i][1] << "] ";
    }
    cout << "\n";
    return 0;
}
