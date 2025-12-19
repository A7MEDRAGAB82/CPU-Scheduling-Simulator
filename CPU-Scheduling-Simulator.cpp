#include <iostream>
#include <vector>
#include "Process.h"
#include "Scheduler.h"
#include "Utils.h"

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

    sortByArrivalTime(processes);
  
    // Menu for Algorithm Selection 
    int choice = 0;
    cout << "\nChoose Algorithm:\n";
    cout << "1. FCFS\n";
    cout << "2. SJF (Non-Preemptive)\n";
    cout << "3. Priority (Non-Preemptive)\n";
    cout << "4. RoundRobin\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        FCFS(processes);
        break;
    case 2:
        SJF_NonPreemptive(processes);
        break;
    case 3:
        Priority_NonPreemptive(processes);
        break;
    case 4:
        RoundRobin(processes);
        break;
    default:
        cout << "Invalid choice!\n";
        break;
    }

    return 0;
}
