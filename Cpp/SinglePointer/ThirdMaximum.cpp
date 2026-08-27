/*
 * LECȚIE — Al treilea maxim: aceeași idee, încă un loc
 *
 * Problemă
 *   Urmărește primele trei valori dintr-o singură parcurgere stânga-dreapta.
 *
 * Intuiție
 *   O fereastră sortată de 3 elemente cu „cei mai buni de până acum.” O valoare
 *   nouă se inserează în locul potrivit, împingând pe cei mai slabi în jos.
 *   După n pași, fereastra ține răspunsul.
 *
 * De ce nu sortăm?
 *   Sortarea e unealta potrivită când îți trebuie ordinea întreagă. Pentru un
 *   k fix (aici k = 3) o parcurgere cu k locuri e O(n) vs O(n log n), și
 *   folosește O(1) memorie extra. Asta e selecție, nu sortare.
 *
 * Teorie C — ordinea atribuirilor e fluxul de date
 *   third = second; second = first; first = x;
 *   Inversează cele trei linii și calci peste first înainte să-l salvezi.
 *   Compilatoarele nu te avertizează. Desenează registrele pe hârtie o dată.
 *
 *   Aceeași capcană cu INT_MIN ca la FindingMaximum: dacă tabloul are mai
 *   puțin de trei elemente, întorci INT_MIN, ceea ce poate fi sau nu ce
 *   voia apelantul. Codul de producție ar verifica n >= 3.
 *
 *   `int nums[]` decade la un pointer, deci TREBUIE să transmiți n.
 *
 * Complexitate: O(n) timp, O(1) spațiu extra.
 */

#include <climits>
#include <iostream>
using namespace std;

int thirdMaximum(int nums[], int n) {
    int firstMax = INT_MIN;
    int secondMax = INT_MIN;
    int thirdMax = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (nums[i] > firstMax) {
            thirdMax = secondMax;
            secondMax = firstMax;
            firstMax = nums[i];
        } else if (nums[i] > secondMax) {
            thirdMax = secondMax;
            secondMax = nums[i];
        } else if (nums[i] > thirdMax) {
            thirdMax = nums[i];
        }
    }
    return thirdMax;
}

int main() {
    int nums[] = {8, 5, 3, 11, 9, 4, 16, 7, 12, 13};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << thirdMaximum(nums, n) << "\n";  // 12
    return 0;
}
