/*
 * LECȚIE — Cea mai lungă serie de 1
 *
 * Problemă
 *   Într-un tablou binar, întoarce lungimea celei mai lungi secvențe
 *   consecutive de unu.
 *
 * Intuiție
 *   O serie e o înșiruire neîntreruptă. Pe un 1, incrementează seria. Pe un 0,
 *   seria s-a încheiat: culege-o în `best`, resetează seria la 0. După buclă,
 *   culege încă o dată — tabloul poate să se termine pe o serie.
 *
 * Memorie
 *   Doi int. Nu stochezi seriile. Ții doar cea mai bună lungime văzută
 *   până acum. E ideea de sliding-window în miniatură: „fereastra” e seria
 *   curentă, și doar crește sau se resetează.
 *   `int nums[]` decade la un pointer, deci TREBUIE să transmiți n.
 *
 * Teorie C
 *   Un `if (count > best) best = count;` scris de mână e toată ideea de
 *   „păstrează-l pe cel mai mare.” Nu uita culesul final. Să-l uiți e
 *   un off-by-one clasic în mașini de stări: starea acceptoare nu e
 *   niciodată golită.
 *
 * Complexitate: O(n) timp, O(1) spațiu extra.
 */

#include <iostream>
using namespace std;

int maxOnes(int nums[], int n) {
    int best = 0;
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (nums[i] == 1) {
            count++;
        } else {
            if (count > best)
                best = count;
            count = 0;
        }
    }
    if (count > best)
        best = count;
    return best;
}

int main() {
    int nums[] = {1, 0, 1, 1, 1, 0, 1, 1, 1, 1};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << "ans" << maxOnes(nums, n) << "\n";  // ans4
    return 0;
}
