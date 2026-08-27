/*
 * LECȚIE — Primul și ultimul indice al unui target într-un tablou sortat
 *
 * Studentule, tabloul e sortat. target poate apărea de zero sau mai multe ori.
 * Afișează primul și ultimul indice unde apare, sau -1 -1 dacă
 * lipsește. Exemplul {3,3,3,4,6,6,6,6,7}, target 6: primul 4, ultimul 7.
 *
 * Intuiție — varianta pe care o implementăm (fidelă, O(n) cel mai rău)
 *   Căutare binară până nums[mid] == target. Apoi mergi la stânga
 *   cât timp elementul anterior e tot target, și la dreapta cât timp
 *   următorul e tot target. Scrie cele două capete în out[0] și
 *   out[1]. Doi int, nu un tip pair.
 *
 *   Extinderea aia e simplă și se potrivește cu originalul. E O(n)
 *   în cazul cel mai rău: un tablou plin de target, plimbările
 *   ajung la ambele capete. Ai plătit o căutare binară și apoi ai
 *   aruncat log n pe platou.
 *
 * Varianta O(log n) pe care trebuie s-o știi
 *   Două căutări binare. lower_bound: primul indice cu nums[i] >=
 *   target. upper_bound: primul indice cu nums[i] > target. Apoi
 *   first = lower, last = upper - 1, după ce verifici că lower e
 *   în interval și nums[lower] == target. Fiecare căutare e O(log n),
 *   chiar dacă tot tabloul e target, pentru că nu parcurgi platoul:
 *   tot tai în două cu un predicat diferit.
 *
 * Complexitate
 *   Fișierul ăsta: O(log n) tipic, O(n) cel mai rău. Memorie extra O(1).
 *   Căutare binară pe două capete: O(log n) mereu, O(1) extra.
 *
 * Memorie
 *   int nums[], int n: tabloul a decăzut la un pointer plus o lungime.
 *   Scriem doi int în out[] (lungime 2). Fără tablou extra. Plimbările
 *   doar citesc. Extinderea nu alocă.
 *
 * Teorie C — platouri, overflow, limite pe plimbări
 *   Tablourile sortate transformă o serie de egale într-un platou
 *   contig. Căutarea binară aterizează undeva pe platoul ăla, nu
 *   neapărat pe muchia stângă. De-asta o singură lovitură nu ajunge
 *   pentru „primul” și „ultimul”.
 *
 *   Plimbare stânga: while (l > 0 && nums[l] == nums[l-1]) l--.
 *   l > 0 e garda împotriva lui nums[-1], care e UB.
 *   Plimbare dreapta: while (h + 1 < n && nums[h] == nums[h+1]) h++.
 *   h+1 < n e garda împotriva one-past-the-end.
 *
 *   mid = l + (h - l) / 2 în timpul căutării. Aceeași regulă de overflow.
 *
 *   C: umpli doi int *first, *last. Sau un buffer out[2], ca aici.
 *
 * Exemplul afișează 4 7.
 */

#include <iostream>
using namespace std;

void searchRange(int nums[], int n, int target, int out[]) {
    int l = 0;
    int h = n - 1;
    while (l <= h) {
        int mid = l + (h - l) / 2;
        if (target == nums[mid]) {
            l = mid;
            while (l > 0 && nums[l] == nums[l - 1]) {
                l--;
            }
            h = mid;
            while (h + 1 < n && nums[h] == nums[h + 1]) {
                h++;
            }
            out[0] = l;
            out[1] = h;
            return;
        }
        if (target < nums[mid]) {
            h = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    out[0] = -1;
    out[1] = -1;
}

int main() {
    int nums[] = {3, 3, 3, 4, 6, 6, 6, 6, 7};
    int n = sizeof(nums) / sizeof(nums[0]);
    int out[2];
    searchRange(nums, n, 6, out);
    cout << out[0] << " " << out[1] << "\n";
    return 0;
}
