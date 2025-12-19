#include <iostream>
#include <vector>
#include "Process.h"
#include "Scheduler.h"
#include "Utils.h"

using namespace std;

int main() {
    vector<Process> processes;
    int timeQuantum = 0;

    cout << "Please enter the number of processes: ";
    int numOfProcesses;
    cin >> numOfProcesses;

    for (int i = 0; i < numOfProcesses; i++) {
        int pid, at, bt, prio, qType;

        cout << "\nEnter PID, ArrivalTime, BurstTime, Priority: ";
        cin >> pid >> at >> bt >> prio;

        if (bt <= 0) {
            cout << "Burst time must be positive. Re-enter process.\n";
            i--;
            continue;
        }

        cout << "Queue Type (0 = SYSTEM, 1 = INTERACTIVE, 2 = BATCH): ";
        cin >> qType;

        if (qType < 0 || qType > 2) {
            cout << "Invalid Queue Type. Re-enter process.\n";
            i--;
            continue;
        }

        processes.emplace_back(
            pid,
            at,
            bt,
            prio,
            static_cast<QueueType>(qType)
        );
    }

    // Always sort by arrival time once
    sortByArrivalTime(processes);

    // Menu for Algorithm Selection
    int choice = 0;
    cout << "\nChoose Algorithm:\n";
    cout << "1. FCFS\n";
    cout << "2. SJF (Non-Preemptive)\n";
    cout << "3. Priority (Non-Preemptive)\n";
    cout << "4. Round Robin\n";
    cout << "5. SJF (Preemptive)\n";
    cout << "6. Priority (Preemptive)\n";
    cout << "7. Multi-Level Queue Scheduling\n";
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
        cout << "Enter Time Quantum: ";
        cin >> timeQuantum;
        RoundRobin(processes, timeQuantum);
        break;

    case 5:
        SJF_Preemptive(processes);
        break;

    case 6:
        Priority_Preemptive(processes);
        break;

    case 7:
        MultiLevelQueue(processes);
        break;

    default:
        cout << "Invalid choice!\n";
        break;
    }

    return 0;
}
