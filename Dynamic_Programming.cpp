#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>


// Function for the rod cutting problem
int cutRod(const std::vector<int>& price, int n) {
    std::vector<int> val(n + 1);
    val[0] = 0;

    for (int i = 1; i <= n; i++) {
        int max_val = INT_MIN;
        for (int j = 0; j < i; j++)
            max_val = std::max(max_val, price[j] + val[i-j-1]);
        val[i] = max_val;
    }

    return val[n];
}

// Function for the LCS problem
std::string lcs(const std::string &X, const std::string &Y) {
    int m = X.size();
    int n = Y.size();
    std::vector<std::vector<int>> L(m + 1, std::vector<int>(n + 1));

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = std::max(L[i - 1][j], L[i][j - 1]);
        }
    }

    // Following code is used to print LCS
    int index = L[m][n];
    std::string lcs(index, ' ');

    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[index - 1] = X[i - 1];
            i--; j--; index--;
        }
        else if (L[i - 1][j] > L[i][j - 1])
            i--;
        else
            j--;
    }

    return lcs;
}

int main() {
    // Testing the rod cutting problem
    std::vector<int> prices = {1, 5, 8, 9, 10, 17, 17, 20};
    int length = 7;
     auto start = std::chrono::high_resolution_clock::now();

    std::cout << "Maximum revenue to be made: " << cutRod(prices, length) << std::endl;

    // Testing the LCS problem
    std::string X = "AGGTAB";
    std::string Y = "GXTXAYB";
    std::cout << "Length of LCS is " << lcs(X, Y) << std::endl;
    auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Time taken by function: "
         << duration.count() << " microseconds" << std::endl;
    return 0;
}
