/*
 * LESSON — Best time to buy and sell stock (one transaction)
 *
 * Problem
 *   prices[i] is the price on day i. Buy once, sell once later. Maximize
 *   sell - buy. If no profit is possible, return 0.
 *
 * Intuition
 *   The best buy for a sell on day i is the minimum price in [0..i-1].
 *   Track `buy` = min so far, and `profit` = max(prices[i] - buy).
 *   One pass. You never need the day indices unless the API asks for them.
 *
 * Memory
 *   Two ints. Contrast: the naive "for each buy, for each later sell"
 *   is O(n^2) and still O(1) space — same memory, terrible time. The
 *   running-min is the algorithm, not a trick.
 *
 * C theory — greed that is actually optimal
 *   This is a dynamic-programming recurrence in disguise:
 *     min_prefix[i] = min(min_prefix[i-1], prices[i])
 *     best[i]       = max(best[i-1], prices[i] - min_prefix[i])
 *   We keep only the last value of each sequence, so extra memory is O(1).
 *   When a DP recurrence only needs the previous cell, *collapse the table*.
 *   That is how an engineer turns O(n) memory into O(1).
 *
 * Complexity: O(n) time, O(1) extra space.
 */

#include <iostream>
#include <vector>

int maxProfit(const std::vector<int>& prices) {
    if (prices.empty()) {
        return 0;
    }
    int buy = prices[0];
    int profit = 0;
    for (std::size_t i = 1; i < prices.size(); ++i) {
        if (prices[i] < buy) {
            buy = prices[i];
        } else if (prices[i] - buy > profit) {
            profit = prices[i] - buy;
        }
    }
    return profit;
}

int main() {
    std::vector<int> prices{5, 2, 3, 8, 1, 9};
    std::cout << maxProfit(prices) << '\n';  // 8  (buy 1, sell 9)
    return 0;
}
