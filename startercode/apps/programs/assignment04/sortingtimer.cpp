#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>
#include <algorithm>

using namespace std;

// ============================================================
// O(n^2) SORTING ALGORITHMS
// ============================================================

// Selection Sort - O(n^2)
void selectionSort(vector<int>& data) {
    int n = data.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (data[j] < data[minIndex]) {
                minIndex = j;
            }
        }
        swap(data[i], data[minIndex]);
    }
}

// Bubble Sort - O(n^2)
void bubbleSort(vector<int>& data) {
    int n = data.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (data[j] > data[j + 1]) {
                swap(data[j], data[j + 1]);
            }
        }
    }
}

// Insertion Sort - O(n^2)
void insertionSort(vector<int>& data) {
    int n = data.size();
    for (int i = 1; i < n; i++) {
        int key = data[i];
        int j = i - 1;
        while (j >= 0 && data[j] > key) {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = key;
    }
}

// ============================================================
// O(n log n) SORTING ALGORITHM - QUICKSORT
// ============================================================

int partition(vector<int>& data, int start, int end) {
    int pivot = data[end];
    int pIndex = start;
    
    for (int i = start; i < end; i++) {
        if (data[i] <= pivot) {
            swap(data[i], data[pIndex]);
            pIndex++;
        }
    }
    swap(data[pIndex], data[end]);
    return pIndex;
}

void quicksortHelper(vector<int>& data, int start, int end) {
    if (start < end) {
        int pivotIndex = partition(data, start, end);
        quicksortHelper(data, start, pivotIndex - 1);
        quicksortHelper(data, pivotIndex + 1, end);
    }
}

void quicksort(vector<int>& data) {
    if (data.size() > 0) {
        quicksortHelper(data, 0, data.size() - 1);
    }
}

// ============================================================
// UTILITY FUNCTIONS
// ============================================================

// Fill vector with random integers
void fillWithRandomIntegers(vector<int>& data, int size) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100000);
    
    data.clear();
    data.reserve(size);
    for (int i = 0; i < size; i++) {
        data.push_back(dis(gen));
    }
}

// Time a sorting function
double timeSortingFunction(void (*sortFunc)(vector<int>&), vector<int> data) {
    auto start = chrono::high_resolution_clock::now();
    sortFunc(data);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> elapsed = end - start;
    return elapsed.count();
}

// ============================================================
// MAIN PROGRAM
// ============================================================

int main() {
    cout << "Sorting Algorithm Performance Comparison\n";
    cout << "=========================================\n\n";
    
    // Array sizes to test
    vector<int> sizes = {10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000, 250000};
    
    // Print header
    cout << setw(10) << "Size" << " | "
         << setw(15) << "Selection(ms)" << " | "
         << setw(15) << "Bubble(ms)" << " | "
         << setw(15) << "Insertion(ms)" << " | "
         << setw(15) << "Quicksort(ms)" << "\n";
    cout << string(85, '-') << "\n";
    
    // Test each size
    for (int size : sizes) {
        cout << setw(10) << size << " | ";
        
        // Generate random data
        vector<int> testData;
        fillWithRandomIntegers(testData, size);
        
        // Time Selection Sort
        if (size <= 50000) {  // Skip large sizes for O(n^2) sorts
            double selectionTime = timeSortingFunction(selectionSort, testData);
            cout << setw(15) << fixed << setprecision(3) << selectionTime << " | ";
        } else {
            cout << setw(15) << "skipped" << " | ";
        }
        
        // Time Bubble Sort
        if (size <= 50000) {  // Skip large sizes for O(n^2) sorts
            double bubbleTime = timeSortingFunction(bubbleSort, testData);
            cout << setw(15) << fixed << setprecision(3) << bubbleTime << " | ";
        } else {
            cout << setw(15) << "skipped" << " | ";
        }
        
        // Time Insertion Sort
        if (size <= 50000) {  // Skip large sizes for O(n^2) sorts
            double insertionTime = timeSortingFunction(insertionSort, testData);
            cout << setw(15) << fixed << setprecision(3) << insertionTime << " | ";
        } else {
            cout << setw(15) << "skipped" << " | ";
        }
        
        // Time Quicksort (can handle all sizes)
        double quicksortTime = timeSortingFunction(quicksort, testData);
        cout << setw(15) << fixed << setprecision(3) << quicksortTime << "\n";
    }
    
    cout << "\nNote: O(n^2) sorts skipped for sizes > 50000 due to excessive runtime\n";
    cout << "\nYou can copy this data into a spreadsheet to create graphs.\n";
    
    return 0;
}