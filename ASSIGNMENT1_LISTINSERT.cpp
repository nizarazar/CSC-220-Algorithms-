#include <iostream>
#include <vector>
#include <windows.h>
#include <random>
using namespace std;

void insertionSort(vector<int> &arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        // Move elements of arr[0..i-1], that are greater than key,
        // to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main() {
        DWORD start = GetTickCount();

    mt19937 rng(time(0));

    // Define a uniform distribution for integers between a certain range
    uniform_int_distribution<int> dist(1, 10000); // Change the range as needed

    // Create a vector to store the random integers
    vector<int> arr;

    // Generate 100 random integers and store them in the vector
    for (int i = 0; i < 1000; ++i) {
        arr.push_back(dist(rng));
    }
     
   cout << "Original array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    insertionSort(arr);

    cout << "Sorted array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
    DWORD end = GetTickCount();

    // Calculate the elapsed time in milliseconds
    DWORD elapsedTime = end - start;

    // Output the elapsed time
    cout << "Elapsed time: " << elapsedTime << " milliseconds" << endl;
    return 0;
}