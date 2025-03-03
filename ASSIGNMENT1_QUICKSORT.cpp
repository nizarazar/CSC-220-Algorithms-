#include <iostream>
#include <vector>
#include <random>
#include <windows.h>
using namespace std;

// Function to partition the array and return the partition index
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];  // Select the rightmost element as pivot
    int i = low - 1;  // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than or equal to pivot
        if (arr[j] <= pivot) {
            i++;  // Increment index of smaller element
            swap(arr[i], arr[j]);  // Swap current element with element at index i
        }
    }
    swap(arr[i + 1], arr[high]);  // Swap pivot with element at index i+1
    return i + 1;  // Return partition index
}

// Function to perform Quick Sort
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);  // Partitioning index

        // Recursively sort elements before partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to print an array
void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    DWORD start = GetTickCount();

    mt19937 rng(time(0));

    // Define a uniform distribution for integers between a certain range
    uniform_int_distribution<int> dist(1, 1000); // Change the range as needed

    // Create a vector to store the random integers
    vector<int> arr;

    // Generate 100 random integers and store them in the vector
    for (int i = 0; i < 100; ++i) {
        arr.push_back(dist(rng));
    }
  

    cout << "Original array: ";
    printArray(arr);

    int n = arr.size();
    quickSort(arr, 0, n - 1);

    cout << "Sorted array: ";
    printArray(arr);
    DWORD end = GetTickCount();

    // Calculate the elapsed time in milliseconds
    DWORD elapsedTime = end - start;

    // Output the elapsed time
    cout << "Elapsed time: " << elapsedTime << " milliseconds" << endl;
    return 0;
}
