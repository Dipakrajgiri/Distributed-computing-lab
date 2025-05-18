#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;

class RicartAgrawala {
private:
    int num_processes;
    vector<int> request_time;
    vector<int> reply_count;
    vector<bool> flag;
    vector<int> timestamp;
    mutex mtx;
    condition_variable cv;

public:
    RicartAgrawala(int num) : num_processes(num) {
        request_time.resize(num_processes, 0);
        reply_count.resize(num_processes, 0);
        flag.resize(num_processes, false);
        timestamp.resize(num_processes, 0);
    }

    void requestCriticalSection(int id) {
        // Request for critical section
        cout << "Process " << id << " requesting critical section." << endl;

        unique_lock<mutex> lock(mtx);
        timestamp[id] = rand() % 100; // Random timestamp (to simulate time)
        request_time[id] = timestamp[id];
        flag[id] = true;

        // Send request to all processes
        for (int i = 0; i < num_processes; i++) {
            if (i != id) {
                cout << "Process " << id << " sends request to Process " << i << endl;
                // In actual systems, this would be a message to other processes.
                // Here we simulate it by setting the request_time and flag of others
                this_thread::sleep_for(chrono::milliseconds(100)); // Simulate network delay
            }
        }

        // Wait for replies from all other processes
        while (true) {
            bool received_all_replies = true;
            for (int i = 0; i < num_processes; i++) {
                if (i != id && reply_count[i] == 0) {
                    received_all_replies = false;
                    break;
                }
            }
            if (received_all_replies) {
                break;
            }
        }

        cout << "Process " << id << " entering critical section." << endl;
    }

    void releaseCriticalSection(int id) {
        unique_lock<mutex> lock(mtx);
        flag[id] = false; // Release critical section

        // Send replies to all processes
        for (int i = 0; i < num_processes; i++) {
            if (i != id) {
                cout << "Process " << id << " sends reply to Process " << i << endl;
                reply_count[i] = 1; // Simulating reply
            }
        }
        cout << "Process " << id << " has left the critical section." << endl;
    }
};

void process(RicartAgrawala &ra, int id) {
    // Simulate random delays
    this_thread::sleep_for(chrono::milliseconds(rand() % 500));

    ra.requestCriticalSection(id);
    // Critical section work
    this_thread::sleep_for(chrono::milliseconds(100));
    ra.releaseCriticalSection(id);
}

int main() {
    srand(time(0));

    int num_processes = 5;
    RicartAgrawala ra(num_processes);

    vector<thread> processes;
    for (int i = 0; i < num_processes; i++) {
        processes.push_back(thread(process, ref(ra), i));
    }

    for (auto &t : processes) {
        t.join();
    }

    return 0;
}
