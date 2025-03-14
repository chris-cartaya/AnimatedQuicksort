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

// ANSI Color Codes
#define RESET   "\033[0m"
#define RED     "\033[31m" // Pivot
#define YELLOW  "\033[33m" // Left pointer
#define BLUE    "\033[34m" // Right pointer
#define GREEN   "\033[32m" // Final sorted position
#define PURPLE  "\033[35m" // Swap target

vector<int> generateRandomArray(int arraySize) {
    int maxNum = 9;
    vector<int> arr(arraySize); // Constructs a container with n elements
    srand(time(nullptr));       // Seed the random number generator

    for (int i = 0; i < arraySize; ++i) {
        arr[i] = rand() % maxNum + 1;   // Generate numbers between 1 and 10
    }

    return arr;
}

void displayHistogram(const vector<int>& arr, int pivotIndex = -1, int left = -1, 
                      int right = -1, int swapTarget = -1, const vector<bool>& finalized = {}) {
    // clearScreen();

    int maxVal = 10;
    bool highlightPivot = pivotIndex != -1;    
    bool highlightLeft = left != -1;    
    bool highlightRight = right != -1;    
    bool highlightSwap = swapTarget != -1;    
    
    // Print histogram from top to bottom
    for (int row = maxVal; row > 0; --row) {
        for (int i = 0; size_t(i) < arr.size(); ++i) {
            if (arr[i] >= row) {
                if (size_t(i) < finalized.size() && finalized[i]) {
                    cout << GREEN << "* " << RESET;  // Finalized green
                } else if (highlightPivot && i == pivotIndex) {
                    cout << RED << "* " << RESET;  // Pivot red
                } else if (highlightLeft && i == left) {
                    cout << YELLOW << "* " << RESET; // Left pointer yellow
                } else if (highlightRight && i == right) {
                    cout << BLUE << "* " << RESET; // Right pointer blue
                } else if (highlightSwap && i == swapTarget) {
                    cout << PURPLE << "* " << RESET; // Swap target purple
                } else {
                    cout << "* ";
                }
            } else {
                cout << "  "; // Empty space
            }
        }
        cout << endl;
    }

    cout << string(arr.size() * 2, '-') << endl; // Separator line

    // Print array values below
    for (int num : arr) cout << num << " ";
    cout << endl;

    // this_thread::sleep_for(chrono::milliseconds(1000)); // Delay for visualization
}

int partition(vector<int>& arr, int low, int high, vector<bool>& finalized) {
    int pivotIndex = low + (high - low) / 2; // Middle element as pivot
    int pivotValue = arr[pivotIndex];

    cout << "\nPivot Selected: " << RED << pivotValue << RESET << "\n";
    displayHistogram(arr, pivotIndex, -1, -1, -1, finalized);
    
    cout << "\nMove pivot to end\n";
    displayHistogram(arr, pivotIndex, -1, -1, high, finalized);

    swap(arr[pivotIndex], arr[high]); // Move pivot to end temporarily
    
    cout << "\nAfter swapping pivot\n";
    displayHistogram(arr, high, -1, -1, pivotIndex, finalized);
    
    pivotIndex = high; 

    int left = low, 
        right = high - 1;
    
    cout << "\nFirst time showing left and right pointers\n";
    displayHistogram(arr, pivotIndex, left, right, -1, finalized);

    while (left <= right) {
        while (left <= right && arr[left] < pivotValue) {
            cout << "\nShowing left and right pointers\n";
            displayHistogram(arr, pivotIndex, left, right, -1, finalized);
            
            cout << "\nleft is moving up\n";
            left++;
        }
        while (left <= right && arr[right] > pivotValue) {
            cout << "\nShowing left and right pointers\n";
            displayHistogram(arr, pivotIndex, left, right, -1, finalized);
            
            cout << "\nright is moving down\n";
            right--;
        }
        if (left <= right) {
            cout << "\nAfter swapping left and right pointers\n";
            swap(arr[left], arr[right]);
            displayHistogram(arr, pivotIndex, left, right, -1, finalized);
            
            left++;
            right--;
        }
    }
    cout << "\nAfter looping\n";
    displayHistogram(arr, pivotIndex, left, right, -1, finalized);
    
    cout << "\nSelecting column to switch with pivot\n";
    displayHistogram(arr, pivotIndex, -1, -1, left, finalized);

    cout << "\nMove pivot to correct place\n";
    swap(arr[left], arr[pivotIndex]); // Move pivot to its correct place
    displayHistogram(arr, left, -1, -1, pivotIndex, finalized);
    
    finalized[left] = true; // Mark pivot as finalized
    cout << "\nAfter pivot finalized\n";
    displayHistogram(arr, left, -1, -1, -1, finalized);
    
    return left;
}

void quickSort(vector<int>& arr, int low, int high, vector<bool>& finalized) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high, finalized);

        quickSort(arr, low, pivotIndex - 1, finalized);
        quickSort(arr, pivotIndex + 1, high, finalized);
    }
}

int main() {

    int arraySize = 7;
    vector<int> arr = generateRandomArray(arraySize);
    vector<bool> finalized(arraySize, false); // To track finalized elements

    cout << "Original Array:\n";
    displayHistogram(arr);

    quickSort(arr, 0, (arraySize - 1), finalized);

    cout << "\nSorted Array:" << endl;
    displayHistogram(arr);
    
    return 0;
}