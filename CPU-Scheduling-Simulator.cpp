#include <iostream>
#include <vector>
#include "Process.h"
#include "Scheduler.h"

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
            i--; // repeat input for this process
            continue;
        }

        // Construct the Process object directly inside the vector
        processes.emplace_back(pid, at, bt, prio);
    }

    // Call FCFS scheduler after all processes are entered
    FCFS(processes);

    // Testing tip:
    // - Run the program
    // - Input simple known example
    // - Verify that Waiting Time (WT) and Turnaround Time (TAT) are correct

    return 0;
}
