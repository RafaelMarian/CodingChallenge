/*
 * LECȚIE — Fereastră glisantă de lungime fixă: O(n) amortizat, doi indici
 *
 * Studentule, problema e: dat un tablou și o lungime k, întoarce suma maximă a
 * oricărui subtablou contig de exact k elemente.
 *
 * Intuiție
 *   Fereastra de lungime k care începe la indicele i e nums[i .. i+k-1].
 *   Fereastra următoare, care începe la i+1, e aproape același tablou:
 *   a pierdut nums[i] pe stânga și a câștigat nums[i+k] pe dreapta.
 *
 *       sum(i+1) = sum(i) - nums[i] + nums[i+k]
 *
 *   Semănează prima fereastră cu o parcurgere O(k). Apoi glisează:
 *   o scădere, o adunare, o comparație, până muchia dreaptă lovește
 *   capătul. Nu re-parcurgi niciodată cele k-1 elemente comune.
 *
 *   Fereastra e doi indici. Numim muchia stângă i (elementul care
 *   urmează să iasă) și muchia dreaptă j (elementul care urmează
 *   să intre). Invariantul e j - i + 1 == k după sămânță, și fiecare
 *   glisare face i++, j++ împreună. Doi pointeri, un pas în pas.
 *
 * Complexitate
 *   Sămânță: O(k). Glisare: O(n - k) pași, O(1) lucru fiecare. Total O(n).
 *   Ăsta e O(1) amortizat pe element: fiecare indice intră în fereastră
 *   o dată și iese o dată. Naivul „pentru fiecare start, sumează k
 *   elemente” e O(n k). Același răspuns, aritmetică irosită.
 *   Memorie extra: O(1). Fereastra e indici, nu o copie a feliilor.
 *
 * Memorie
 *   int nums[], int n, int k: nu copiem buffer-ul. sum și max
 *   trăiesc în registre sau în cadrul de stivă. Fără alocare pe heap
 *   în funcție. CPU-ul vede un singur flux contig de int. nums a
 *   decăzut la un pointer; n e necesar pentru că sizeof(nums) în
 *   interiorul funcției e dimensiunea unui pointer.
 *
 * Teorie C — de ce glisarea e prietenoasă cu cache, și unde se ascunde overflow
 *   nums e un buffer contig (stivă în main-ul ăsta). Trecerea de
 *   sămânță citește nums[0..k). Fiecare glisare citește doi int
 *   distanțați cu k: nums[i] și nums[j]. i și j merg înainte
 *   secvențial, deci ambele fluxuri fac prefetch. Distanța k
 *   înseamnă că pot sta pe linii de cache diferite; tot două fluxuri
 *   secvențiale sunt, nu urmărire aleatoare de pointeri.
 *
 *   sum += nums[j] e o adunare pe signed. O fereastră de int mari
 *   poate da overflow pe int. Overflow-ul pe signed e UB. Dacă
 *   sumele adevărate de fereastră pot ieși din 32 de biți,
 *   acumulează în long long. Exemplul n-o face, deci int se
 *   potrivește cu aritmetica originală.
 *
 *   Limite: bucla de sămânță nu trebuie să treacă de n. Dacă k > n
 *   problema e prost pusă; dacă k == 0 nu trebuie să indexezi
 *   nums[0] dintr-o fereastră goală. În afara limitelor e UB — C
 *   nu aruncă. Exemplul are n = 10, k = 3.
 *
 *   Doi pointeri într-un tablou. nums[i] e *(nums + i). Fără
 *   container: doar indici și o lungime.
 *
 * Exemplu: {1,2,0,4,3,6,2,1,9,-1}, k = 3. Ferestre 3,6,7,13,11,9,12,9.
 * Maximul e 13.
 */

#include <iostream>
using namespace std;

int maxSubArray(int nums[], int n, int k) {
    int sum = 0;
    for (int j = 0; j < k; j++) {
        sum += nums[j];
    }
    int mx = sum;
    int i = 0;
    int j = k - 1;
    while (j + 1 < n) {
        sum -= nums[i];
        i++;
        j++;
        sum += nums[j];
        if (sum > mx) {
            mx = sum;
        }
    }
    return mx;
}

int main() {
    int nums[] = {1, 2, 0, 4, 3, 6, 2, 1, 9, -1};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << maxSubArray(nums, n, 3) << "\n";
    return 0;
}
