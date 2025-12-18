#include <iostream>
#include <vector>
#include "Process.h"

using namespace std;

int main() {
    vector<Process> processes;

    cout << "Please enter the number of processes: ";
    int numOfProcesses;
    cin >> numOfProcesses;

    for (int i = 0; i < numOfProcesses; i++) {
        int pid, at, bt, prio;
        cout << "Enter PID, ArrivalTime, BurstTime, Priority: ";
        cin >> pid >> at >> bt >> prio;

        if (bt <= 0) {
            cout << "Burst time must be positive.\n";
            i--;
            continue;
        }

        // Construct the Process object directly inside the vector
        processes.emplace_back(pid, at, bt, prio);
    }

    cout << "\nProcesses entered:\n";
    for (const auto& p : processes) {
        cout << "PID: " << p.pid
            << ", AT: " << p.arrivalTime
            << ", BT: " << p.burstTime
            << ", Priority: " << p.priority << endl;
    }

    return 0;
}
