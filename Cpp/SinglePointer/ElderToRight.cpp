/*
 * LECȚIE — Lideri de la dreapta, și de ce inserția în față e o capcană
 *
 * Problemă
 *   Un lider-dreapta e mai mare decât tot ce are la *dreapta*. Scanează de
 *   la capăt, ține un max curent, adună liderii.
 *
 * Abordarea naivă: inserează fiecare lider nou în fața unui tablou care crește,
 * ca rezultatul să iasă stânga-dreapta. Asta e O(k) per inserție (deplasezi
 * fiecare element), O(k^2) în total.
 *
 * Varianta de inginer:
 *   Adaugă la capăt în timp ce scanezi dreapta-stânga (O(1) per scriere în
 *   `out[]`), apoi inversează primele `count` celule (O(k)). Aceeași ordine,
 *   O(n) timp.
 *
 * Memorie
 *   Apelantul dă `int out[]` dimensionat la n. Întoarcem câți lideri
 *   am scris. reverse e o buclă de swap pe loc; fără al doilea buffer.
 *   Nu folosim vector aici; ăsta e un tablou C.
 *
 * Teorie C — de ce add(0, x) doare
 *   Tablourile contigue fac append-ul ieftin și inserția în față scumpă.
 *   Listele înlănțuite fac inserția în față ieftină și scanarea secvențială
 *   scumpă (fără cache). Alege structura care se potrivește cu operația
 *   fierbinte. Aici operația fierbinte e „append, apoi reverse o dată.”
 *   `int nums[]` decade la un pointer, deci TREBUIE să transmiți n.
 *
 * Complexitate: O(n) timp, O(k) spațiu extra.
 */

#include <climits>
#include <iostream>
using namespace std;

int rightElder(int nums[], int n, int out[]) {
    int maxSoFar = INT_MIN;
    int count = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (nums[i] > maxSoFar) {
            maxSoFar = nums[i];
            out[count] = maxSoFar;
            count++;
        }
    }
    for (int i = 0; i < count / 2; i++) {
        int tmp = out[i];
        out[i] = out[count - 1 - i];
        out[count - 1 - i] = tmp;
    }
    return count;
}

int main() {
    int nums[] = {7, 5, 4, 17, 3, 8, 13, 2, 6, 9};
    int n = sizeof(nums) / sizeof(nums[0]);
    int out[10];
    int k = rightElder(nums, n, out);
    for (int i = 0; i < k; i++) {
        cout << out[i] << " ";
    }
    cout << "\n";
    return 0;
}
