#include <iostream>
#include <vector>
#include <windows.h>
#include <random>
using namespace std;

void heapify(vector<int>& arr, int n, int i) {
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1; // left = 2*i + 1
    int right = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(arr[0], arr[i]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
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
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    heapSort(arr);

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