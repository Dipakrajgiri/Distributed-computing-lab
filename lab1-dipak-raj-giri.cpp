#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Process {
public:
    int id;
    int clock;
    
    Process(int id) {
        this->id = id;
        this->clock = 0;
    }

    void sendEvent(Process &receiver) {
        clock += 1;
        receiver.receiveEvent(clock);
        cout << "Process " << id << " sends event to Process " << receiver.id << " | Clocks: " << clock << " -> " << receiver.clock << endl;
    }

    void receiveEvent(int senderClock) {
        clock = max(clock, senderClock) + 1;
    }

    void executeEvent() {
        clock += 1;
        cout << "Process " << id << " executes internal event | Clock: " << clock << endl;
    }
};

int main() {
    Process p1(1), p2(2);
    
    p1.executeEvent();
    p2.executeEvent();
    p1.sendEvent(p2);
    p2.executeEvent();
    p2.sendEvent(p1);
    p1.executeEvent();
    
    return 0;
}
