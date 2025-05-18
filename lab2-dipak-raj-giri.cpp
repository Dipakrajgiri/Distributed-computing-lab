#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Function to calculate the average time difference and synchronize clocks
void berkeleyAlgorithm(vector<int>& clocks) {
    int masterClock = clocks[0]; // Assume first clock as master
    int sum = 0;
    vector<int> offsets;

    // Calculate time offsets from the master clock
    for (int i = 0; i < clocks.size(); i++) {
        int offset = clocks[i] - masterClock;
        offsets.push_back(offset);
        sum += offset;
    }

    // Calculate average offset
    int avgOffset = sum / clocks.size();

    // Synchronize clocks
    for (int i = 0; i < clocks.size(); i++) {
        clocks[i] -= avgOffset+offsets[i]; // Adjust each clock
    }
}

int main() {
    vector<int> clocks = {100, 102, 98, 105, 97}; // Example clocks
    
    cout << "Clocks before synchronization: ";
    for (int time : clocks) {
        cout << time << " ";
    }
    cout << endl;

    berkeleyAlgorithm(clocks);
    
    cout << "Clocks after synchronization: ";
    for (int time : clocks) {
        cout << time << " ";
    }
    cout << endl;

    return 0;
}
