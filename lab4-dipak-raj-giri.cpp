#include <iostream>
#include <vector>

using namespace std;

class BullyAlgorithm {
private:
    int id;               // ID of the process starting the election
    int numProcesses;     // Total number of processes
    vector<int> processes; // List of all processes

public:
    BullyAlgorithm(int id, int numProcesses) {
        this->id = id;
        this->numProcesses = numProcesses;

        // Initializing processes array with process IDs
        for (int i = 1; i <= numProcesses; i++) {
            processes.push_back(i);
        }
    }

    void startElection() {
        cout << "Process " << id << " is starting the election." << endl;

        // Send election message to all processes with higher IDs
        vector<int> higherProcesses;
        for (int i = id + 1; i <= numProcesses; i++) {
            higherProcesses.push_back(i);
        }

        // Check if any higher process exists
        if (higherProcesses.empty()) {
            // No higher processes, this process becomes the leader
            cout << "No higher process responded. Process " << id << " becomes the leader!" << endl;
        } else {
            // There are higher processes, the election continues
            cout << "Process " << id << " sends election messages to: ";
            for (int p : higherProcesses) {
                cout << "Process " << p << " ";
            }
            cout << endl;

            // Assume the process with the highest ID becomes the leader
            int leader = *higherProcesses.rbegin();
            cout << "Process " << leader << " becomes the leader!" << endl;
        }
    }

    void simulate() {
        // Simulate the election process
        startElection();
    }
};

int main() {
    int numProcesses, id;

    // Get the number of processes from the user
    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    // Get the ID of the process that starts the election
    cout << "Enter the ID of the process that starts the election: ";
    cin >> id;

    // Validate input
    if (id <= 0 || id > numProcesses) {
        cout << "Invalid process ID!" << endl;
        return -1;
    }

    // Create a BullyAlgorithm object for the given process ID
    BullyAlgorithm process(id, numProcesses);

    // Simulate the election process
    process.simulate();

    return 0;
}
