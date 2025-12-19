#include "Scheduler.h"
#include <algorithm>
#include <queue>
#include <iostream>
#include "Utils.h"

// Comparator for priority queue (min-heap based on Burst Time)
struct SJFComparator {
    bool operator()(Process* a, Process* b) {
        if (a->burstTime == b->burstTime)
            return a->arrivalTime > b->arrivalTime; 
        return a->burstTime > b->burstTime;
    }
};

// Min-heap: lower priority value = higher priority
struct PriorityComparator {
    bool operator()(Process* a, Process* b) {
        if (a->priority != b->priority)
            return a->priority > b->priority;   // smaller value = higher priority
        if (a->arrivalTime != b->arrivalTime)
            return a->arrivalTime > b->arrivalTime; // tie-breaker: earlier arrival
        return a->pid > b->pid; // tie-breaker: smaller PID
    }
};





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

    printResults(processes, "FCFS");
}

void SJF_NonPreemptive(vector<Process>& processes)
{
    // Sort processes by Arrival Time
    sort(processes.begin(), processes.end(),
        [](const Process& a, const Process& b) {
            return a.arrivalTime < b.arrivalTime;
        });

    priority_queue<Process*, vector<Process*>, SJFComparator> availableProcess;

    int currentTime = 0;
    int completed = 0;
    int i = 0;
    int n = processes.size();

    // Simulation loop
    while (completed < n)
    {
        // Add all arrived processes to the priority queue
        while (i < n && processes[i].arrivalTime <= currentTime) {
            availableProcess.push(&processes[i]);
            i++;
        }

        // CPU idle case
        if (availableProcess.empty()) {
            currentTime = processes[i].arrivalTime;
            continue;
        }

        // Select process with minimum Burst Time
        Process* p = availableProcess.top();
        availableProcess.pop();

        // Execute process (Non-Preemptive)
        currentTime += p->burstTime;

        // Calculate results
        p->completionTime = currentTime;
        p->turnaroundTime = p->completionTime - p->arrivalTime;
        p->waitingTime = p->turnaroundTime - p->burstTime;

        completed++;
    }

    printResults(processes, "SJF_NonPreemptive");
   
    
}

void Priority_NonPreemptive(vector<Process>& processes) {

}