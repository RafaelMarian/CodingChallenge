/*
 * LECȚIE — Sortat și rotit: cel mult o „cădere”
 *
 * Problemă
 *   Un tablou sortat și rotit arată ca [5,6,7,8,9,12,15,2,3,5]: două
 *   serii crescătoare, iar îmbinarea e o singură coborâre. Duplicatele la
 *   înfășurare (last <= first) sunt permise de implementarea asta.
 *
 * Intuiție
 *   Numără de câte ori nums[i] > nums[i+1]. Mai mult de o cădere înseamnă că
 *   nu e o singură rotație a unui tablou sortat. Zero căderi: deja
 *   sortat. O cădere: înfășurarea trebuie să satisfacă last <= first.
 *
 * Memorie
 *   Un contor. Nu copiezi și nu rotești tabloul ca să-l testezi.
 *   `int nums[]` decade la un pointer, deci TREBUIE să transmiți n.
 *
 * Teorie C
 *   Asta e o scanare cu stări finite: verifici o *formă*, nu
 *   cauți o valoare. Inginerii fac asta pentru invariante
 *   („e buffer-ul ăsta un inel valid?”). Ieși devreme când count > 1, ca să
 *   nu plătești restul unui input evident invalid.
 *
 * Complexitate: O(n) timp, O(1) spațiu extra.
 */

#include <iostream>
using namespace std;

bool isSortedRotated(int nums[], int n) {
    int count = 0;
    for (int i = 0; i < n - 1; i++) {
        if (nums[i] > nums[i + 1]) {
            count++;
            if (count > 1)
                return false;
        }
    }
    if (count == 0)
        return true;
    return nums[n - 1] <= nums[0];
}

int main() {
    int nums[] = {5, 6, 7, 8, 9, 12, 15, 2, 3, 5};
    int n = sizeof(nums) / sizeof(nums[0]);
    bool ok = isSortedRotated(nums, n);
    cout << "ans" << (ok ? "true" : "false") << "\n";
    return 0;
}
