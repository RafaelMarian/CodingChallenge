/*
 * LECȚIE — Căutare rotită când duplicatele sunt permise (boolean)
 *
 * Studentule, același cadru sortat-rotit ca ModifiedBinarySearch, dar valorile
 * se pot repeta. Întoarce dacă target apare, nu indicele lui.
 * Exemplul {6,6,6,6,7,3,3,3,4,4,5,5,6,6,6} conține 6: afișează true.
 *
 * Intuiție
 *   Testul „o jumătate e sortată” folosea nums[l] <= nums[mid]. Când
 *   nums[l] == nums[mid] == nums[h], testul ăla nu-ți spune nimic:
 *   ambele jumătăți pot părea „sortate” și tot să ascundă cusătura,
 *   sau target, oriunde. Reparația e să strângi intervalul de la
 *   ambele capete:
 *
 *       if (nums[low] == nums[mid] && nums[mid] == nums[high]) {
 *           low++;
 *           high--;
 *           continue;
 *       }
 *
 *   Arunci două copii pe care le-ai comparat deja cu target
 *   (mid a fost testat; low și high egale cu mid, deci nici ele nu
 *   sunt target). Apoi reiei. Când cele trei nu sunt egale, cazi
 *   înapoi pe logica cu elemente distincte.
 *
 * Complexitate
 *   Media tot logaritmică pe date cuminți. Cazul cel mai rău O(n):
 *   un tablou de valori egale care nu sunt target, sau o serie
 *   lungă de egale la ambele capete, te forțează să strângi cu unu
 *   la fiecare pas. Duplicatele distrug invariantul pe jumătăți.
 *   Nu poți cita cinstit O(log n) ca bound de cel mai rău caz odată
 *   ce egalele sunt permise. Memoria extra tot O(1).
 *
 * Memorie
 *   int nums[], int n, trei indici. Fără buffer extra. Parcurgerea
 *   liniară din cazul cel mai rău e tot cam secvențială (capetele
 *   se apropie) plus mid-uri ocazionale. Fără alocare. Pointerul
 *   nu știe n; transmiți ambele.
 *
 * Teorie C — de ce egalele strică căutarea binară, overflow, UB
 *   Puterea căutării binare e un invariant: un predicat adevărat
 *   pe un prefix și fals pe un sufix (sau analogul cu jumătatea
 *   sortată). Duplicatele la cele trei puncte de sondă fac
 *   predicatul ilizibil. Strângerea de la ambele capete e
 *   recunoașterea cinstită că ai pierdut invariantul și trebuie
 *   să cheltui lucru liniar până se întoarce. Nu există un cel
 *   mai rău caz șmecher O(log n) pentru problema asta în modelul
 *   de comparații cu duplicate — bound-ul inferior devine liniar.
 *
 *   mid = low + (high - low) / 2. Aceeași lecție de overflow ca
 *   întotdeauna. După low++ și high--, intervalul poate deveni gol
 *   (low > high); while(low <= high) se oprește. Nu citi nums[high]
 *   după aia. Ar fi UB.
 *
 *   Întorci bool, nu un indice: cu duplicate, „indicele” nu e
 *   unic. Existența e întrebarea bine pusă.
 *
 * Exemplul afișează true.
 */

#include <iostream>
using namespace std;

bool search(int nums[], int n, int target) {
    int low = 0;
    int high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] == target) {
            return true;
        }
        if (nums[low] == nums[mid] && nums[mid] == nums[high]) {
            low++;
            high--;
            continue;
        }
        if (nums[low] <= nums[mid]) {
            if (nums[low] <= target && nums[mid] > target) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        } else if (nums[mid] < target && nums[high] >= target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return false;
}

int main() {
    int nums[] = {6, 6, 6, 6, 7, 3, 3, 3, 4, 4, 5, 5, 6, 6, 6};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << (search(nums, n, 6) ? "true" : "false") << "\n";
    return 0;
}
