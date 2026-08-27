/*
 * LECȚIE — Al doilea maxim dintr-o singură parcurgere
 *
 * Problemă
 *   Întoarce a doua cea mai mare valoare. Implementarea asta nu sare
 *   duplicatele maximului, deci [5, 16, 16] dă 16 ca al doilea max.
 *   (La interviu, variantele vor adesea al doilea maxim *distinct* — decide
 *   ce contract implementezi înainte să scrii bucla.)
 *
 * Intuiție
 *   Doi campioni: firstMax și secondMax. Când sosește un first nou, vechiul
 *   first devine second. Când o valoare stă între ei, devine second.
 *   Niciodată două parcurgeri.
 *
 * Memorie
 *   Doi int. Ăsta e tot starea extra. Compară cu sortarea
 *   (O(n log n) timp, poate O(n) spațiu) doar ca să citești ultimele două
 *   celule. `int nums[]` decade la un pointer, deci TREBUIE să transmiți n.
 *
 * Teorie C
 *   Actualizarea a două variabile are o *ordine*. Trebuie să muți
 *   second <- first înainte să suprascrii first, altfel pierzi informație.
 *   Registrele sunt ieftine; valorile pierdute nu se recuperează. Gândește-te
 *   ca la o inserție mică într-o fereastră sortată de 2 locuri. INT_MIN din
 *   <climits> umple ambele locuri la start.
 *
 * Complexitate: O(n) timp, O(1) spațiu extra.
 */

#include <climits>
#include <iostream>
using namespace std;

int secMax(int nums[], int n) {
    int firstMax = INT_MIN;
    int secondMax = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (nums[i] > firstMax) {
            secondMax = firstMax;
            firstMax = nums[i];
        } else if (nums[i] > secondMax) {
            secondMax = nums[i];
        }
    }
    return secondMax;
}

int main() {
    int nums[] = {5, 9, 4, 7, 3, 11, 8, 16, 13, 12};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << secMax(nums, n) << "\n";  // 13
    return 0;
}
