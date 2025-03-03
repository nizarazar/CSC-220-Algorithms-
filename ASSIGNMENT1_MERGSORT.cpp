#include <iostream>
#include <vector>
#include <windows.h>
#include <random>
using namespace std;

// Merge two sorted subarrays [left...mid] and [mid+1...right]
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;    // size of left subarray
    int n2 = right - mid;       // size of right subarray

    // Create temporary arrays
    vector<int> L(n1);
    vector<int> R(n2);

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left...right]
    int i = 0;  // Initial index of first subarray
    int j = 0;  // Initial index of second subarray
    int k = left; // Initial index of merged subarray

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Merge sort function
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
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

    mergeSort(arr, 0, arr.size() - 1);

    cout << "Sorted array: ";
    printArray(arr);
    DWORD end = GetTickCount();

    // Calculate the elapsed time in milliseconds
    DWORD elapsedTime = end - start;

    // Output the elapsed time
    cout << "Elapsed time: " << elapsedTime << " milliseconds" << endl;
    return 0;
}
