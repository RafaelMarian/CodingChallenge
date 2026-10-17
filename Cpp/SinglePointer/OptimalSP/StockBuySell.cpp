/*
 * LECȚIE — Cel mai bun moment să cumperi și să vinzi (o tranzacție)
 *
 * Problemă
 *   prices[i] e prețul în ziua i. Cumperi o dată, vinzi o dată mai târziu.
 *   Maximizează sell - buy. Dacă nu e posibil profit, întoarce 0.
 *
 * Intuiție
 *   Cea mai bună cumpărare pentru o vânzare în ziua i e prețul minim din [0..i-1].
 *   Urmărește `buy` = min de până acum, și `profit` = max(prices[i] - buy).
 *   O parcurgere. Nu-ți trebuie indicii zilelor decât dacă API-ul îi cere.
 *
 * Memorie
 *   Doi int. Contrast: varianta naivă „pentru fiecare buy, pentru fiecare
 *   sell ulterior” e O(n^2) și tot O(1) spațiu — aceeași memorie, timp
 *   groaznic. Minimul curent e algoritmul, nu un truc.
 *   `int prices[]` decade la un pointer, deci TREBUIE să transmiți n.
 *
 * Teorie C — greedy care e de fapt optimal
 *   Asta e o recurență de programare dinamică deghizată:
 *     min_prefix[i] = min(min_prefix[i-1], prices[i])
 *     best[i]       = max(best[i-1], prices[i] - min_prefix[i])
 *   Ținem doar ultima valoare a fiecărui șir, deci memoria extra e O(1).
 *   Când o recurență DP are nevoie doar de celula anterioară, *comprimă tabelul*.
 *   Așa transformă un inginer O(n) memorie în O(1).
 *
 * Complexitate: O(n) timp, O(1) spațiu extra.
 */

#include <iostream>
using namespace std;

int maxProfit(int prices[], int n) {
    if (n == 0)
        return 0;
    int buy = prices[0];
    int profit = 0;
    for (int i = 1; i < n; i++) {
        if (prices[i] < buy)
            buy = prices[i];
        else if (prices[i] - buy > profit)
            profit = prices[i] - buy;
    }
    return profit;
}

int main() {
    int prices[] = {5, 2, 3, 8, 1, 9};
    int n = sizeof(prices) / sizeof(prices[0]);
    cout << maxProfit(prices, n) << "\n";  // 8  (cumpără 1, vinde 9)
    return 0;
}
