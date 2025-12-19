#include "Scheduler.h"
#include <algorithm>
#include <iostream>

void FCFS(vector<Process>& processes)
{
    sort(processes.begin(), processes.end(),
        [](const Process& a, const Process& b) {
            if (a.arrivalTime == b.arrivalTime)
                return a.pid < b.pid;
            return a.arrivalTime < b.arrivalTime;
        });

    int currentTime = 0;

    for (auto& process : processes)
    {
        // CPU idle case
        if (currentTime < process.arrivalTime)
            currentTime = process.arrivalTime;

        // Execute process
        currentTime += process.burstTime;

        // results
        process.completionTime = currentTime;
        process.turnaroundTime = process.completionTime - process.arrivalTime;
        process.waitingTime = process.turnaroundTime - process.burstTime;
    }
}
