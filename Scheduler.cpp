#include "Scheduler.h"
#include <algorithm>
#include <iostream>

void FCFS(vector<Process>& processes)
{
    // Sort processes by Arrival Time (FCFS = First Come First Served)
    // If Arrival Time is the same, sort by PID
    sort(processes.begin(), processes.end(),
        [](const Process& a, const Process& b) {
            if (a.arrivalTime == b.arrivalTime)
                return a.pid < b.pid;
            return a.arrivalTime < b.arrivalTime;
        });

    int currentTime = 0; // Tracks the current CPU time during simulation

    // Simulate execution of each process
    for (auto& process : processes)
    {
        // If CPU is idle until the process arrives
        if (currentTime < process.arrivalTime)
            currentTime = process.arrivalTime;

        // Execute the process (advance currentTime by Burst Time)
        currentTime += process.burstTime;

        // Store results for each process
        process.completionTime = currentTime;
        process.turnaroundTime = process.completionTime - process.arrivalTime;
        process.waitingTime = process.turnaroundTime - process.burstTime;
    }

    // Print final scheduling results table
    cout << "\nFCFS Scheduling Results:\n";
    cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";

    for (const auto& p : processes) {
        cout << p.pid << "\t"
            << p.arrivalTime << "\t"
            << p.burstTime << "\t"
            << p.completionTime << "\t"
            << p.turnaroundTime << "\t"
            << p.waitingTime << endl;
    }
}
