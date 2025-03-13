#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

vector<int> generateRandomArray(int arraySize) {
    vector<int> arr(arraySize); // Constructs a container with n elements
    srand(time(nullptr));       // Seed the random number generator

    for (int i = 0; i < arraySize; ++i) {
        arr[i] = rand() % 10 + 1;   // Generate numbers between 1 and 10
    }

    return arr;
}

void displayHistogram(const vector<int>& arr) {
    int maxVal = 10; // Since numbers are between 1 and 10

    cout << "\nVertical Histogram:\n";

    // Print histogram from top (max value) to bottom (1)
    for (int row = maxVal; row > 0; --row) {
        for (int num : arr) {
            if (num >= row) {
                cout << " *";
            } else {
                cout << "  "; // Space for alignment
            }
        }
        cout << endl;
    }

    // Print a separator line
    cout << string(arr.size() * 2, '-') << '-' << endl;
}

int main() {

    int arraySize = 10;
    vector<int> randomArray = generateRandomArray(arraySize);

    displayHistogram(randomArray);    
    
    return 0;
}