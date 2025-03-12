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

int main() {

    int arraySize = 10; // Example size
    vector<int> randomArray = generateRandomArray(arraySize);

    cout << "Random array: ";
    for (int num : randomArray) {
        cout << num << " ";
    }
    cout << endl;
    
    
    return 0;
}