#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
using namespace std;

#ifdef _WIN32
    #include <windows.h>
    void clearScreen() { system("CLS"); }
#else
    #include <unistd.h>
    void clearScreen() { system("clear"); }
#endif

// ANSI Escape Codes for Colors
#define RED     "\033[1;31m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
// #define GREEN   "\033[1;32m"
#define RESET   "\033[0m"

vector<int> generateRandomArray(int arraySize) {
    int maxNum = 9;
    vector<int> arr(arraySize); // Constructs a container with n elements
    srand(time(nullptr));       // Seed the random number generator

    for (int i = 0; i < arraySize; ++i) {
        arr[i] = rand() % maxNum + 1;   // Generate numbers between 1 and 10
    }

    return arr;
}

void displayHistogram(const vector<int>& arr, int pivotIndex = -1, int left = -1, int right = -1) {
    // clearScreen();
    int maxVal = 10;

    for (int row = maxVal; row > 0; --row) {
        for (int i = 0; size_t(i) < arr.size(); ++i) {
            if (arr[i] >= row) {
                if (i == pivotIndex) {
                    cout << RED << "* " << RESET; // Pivot in red
                } else if (i == left) {
                    cout << YELLOW << "* " << RESET; // Left pointer in yellow
                } else if (i == right) {
                    cout << BLUE << "* " << RESET; // Right pointer in blue
                } else {
                    cout << "* ";
                }
            } else {
                cout << "  "; // Space for alignment
            }
        }
        cout << endl;
    }
    
    cout << string(arr.size() * 2, '-') << endl; // Separator

    // Print array values below
    for (int num : arr) cout << num << " ";
    cout << endl;

    // this_thread::sleep_for(chrono::milliseconds(1000)); // Delay for visualization
}

int partition(vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    int pivot = arr[mid];           // Pivot as the middle value
    
    cout << "\nPivot selected!\n";
    displayHistogram(arr, mid);     // Show pivot selected
    
    cout << "\nMoving pivot to end..\n";
    // displayHistogram(arr, mid, -1, high);     // Show pivot moving to end

    swap(arr[mid], arr[high]);      // Move pivot to the end
    
    displayHistogram(arr, high);    // Show pivot move
    
    int i = low;
    for (int j = low; j < high; j++) {
        cout << "\nShowing left and right pointers\n";
        displayHistogram(arr, high, i, j); // Show left and right pointers
        if (arr[j] < pivot) {
            swap(arr[i], arr[j]);
            cout << "\nAfter swap\n";
            displayHistogram(arr, high, j, i); // Show swap
            i++;
        }
    }
    swap(arr[i], arr[high]); // Move pivot to its correct position
    cout << "\nAfter moving pivot to its correct position\n";
    displayHistogram(arr, i); // Show pivot placed
    return i;
}

void quicksort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIdx = partition(arr, low, high);
        quicksort(arr, low, pivotIdx - 1);
        quicksort(arr, pivotIdx + 1, high);
    }
}

int main() {

    int arraySize = 5;
    vector<int> arr = generateRandomArray(arraySize);

    cout << "Initial Array:" << endl;
    displayHistogram(arr);
    quicksort(arr, 0, (arraySize - 1));

    cout << "\nSorted Array:" << endl;
    displayHistogram(arr);
    
    return 0;
}