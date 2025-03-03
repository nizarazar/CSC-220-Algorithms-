#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

// This function calculates the minimum number of coins needed to make the given amount.
std::vector<int> coinChange(std::vector<int>& coins, int amount) {
    std::sort(coins.begin(), coins.end(), std::greater<int>());
    std::vector<int> result;
    int i = 0;
    while (amount > 0) {
        if (coins[i] <= amount) {
            result.push_back(coins[i]);
            // Subtract the value of coin from the amount
            amount -= coins[i];
        } else {
            // Move to the next coin
            i++;
        }
    }
    return result;
}

// This function tests the coinChange function
void testCoinChange() {
    // Define the coins and the amount
    std::vector<int> coins = {1, 2, 5, 10, 20, 50, 100, 200};
    int amount = 275;
    std::vector<int> result = coinChange(coins, amount);
    std::vector<int> expected = {200, 50, 20, 5};
    if (result == expected) {
        std::cout << "Test passed.\n";
    } else {
        std::cout << "Test failed.\n";
    }
}

int main() {
         auto start = std::chrono::high_resolution_clock::now();

    testCoinChange();
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Time taken by function: "
         << duration.count() << " microseconds" << std::endl;
    return 0;
}