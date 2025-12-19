#include "Scheduler.h"
#include <algorithm>
#include <queue>
#include <iostream>
#include "Utils.h"
#include <climits>

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

void Priority_NonPreemptive(vector<Process>& processes)
{
   
    // Use PriorityComparator for the priority queue (min-heap based on priority)
    priority_queue<Process*, vector<Process*>, PriorityComparator> readyQueue;

    int currentTime = 0;
    int completed = 0;
    int i = 0;
    int n = processes.size();

    // Simulation loop
    while (completed < n)
    {
        // Add all arrived processes to the ready queue
        while (i < n && processes[i].arrivalTime <= currentTime) {
            readyQueue.push(&processes[i]);
            i++;
        }

        // CPU idle case
        if (readyQueue.empty()) {
            currentTime = processes[i].arrivalTime;
            continue;
        }

        // Select process with highest priority (lowest priority value)
        Process* p = readyQueue.top();
        readyQueue.pop();

        // Execute process (Non-Preemptive)
        currentTime += p->burstTime;

        // Calculate results
        p->completionTime = currentTime;
        p->turnaroundTime = p->completionTime - p->arrivalTime;
        p->waitingTime = p->turnaroundTime - p->burstTime;

        completed++;
    }

    // Print results
    printResults(processes, "Priority");
}

void RoundRobin(vector<Process>& processes, int timeQuantum) {
    int n = processes.size();
    int currentTime = 0;
    int completed = 0;

    queue<Process*> readyQueue;

    // Keep track of which processes have arrived
    vector<bool> inQueue(n, false);

    while (completed < n)
    {
        // Add arrived processes to the queue
        for (int i = 0; i < n; i++) {
            if (!inQueue[i] && processes[i].arrivalTime <= currentTime) {
                readyQueue.push(&processes[i]);
                inQueue[i] = true;
            }
        }

        // CPU idle case
        if (readyQueue.empty()) {
            // Move currentTime to the arrival time of the next process
            int nextArrival = INT32_MAX;
            for (int i = 0; i < n; i++) {
                if (!inQueue[i] && processes[i].arrivalTime < nextArrival) {
                    nextArrival = processes[i].arrivalTime;
                }
            }
            currentTime = nextArrival;
            continue;
        }

        // Get the first process from the queue
        Process* p = readyQueue.front();
        readyQueue.pop();

        // Execute for min(remainingTime, timeQuantum)
        int execTime = min(p->remainingTime, timeQuantum);
        p->remainingTime -= execTime;
        currentTime += execTime;

        // Add newly arrived processes to the queue during this time slice
        for (int i = 0; i < n; i++) {
            if (!inQueue[i] && processes[i].arrivalTime <= currentTime) {
                readyQueue.push(&processes[i]);
                inQueue[i] = true;
            }
        }

        // If process is not finished, push it back to the queue
        if (p->remainingTime > 0) {
            readyQueue.push(p);
        }
        else {
            // Process completed
            p->completionTime = currentTime;
            p->turnaroundTime = p->completionTime - p->arrivalTime;
            p->waitingTime = p->turnaroundTime - p->burstTime;
            completed++;
        }
    }

    // Print results
    printResults(processes, "Round Robin");
}

void SJF_Preemptive(vector<Process>& processes) {
    int n = processes.size();
    int completed = 0;
    int currentTime = 0;

    vector<bool> isCompleted(n, false);

    while (completed < n)
    {
        int idx = -1;
        int minRemaining = INT_MAX;

        // Find process with minimum remainingTime that has arrived
        for (int i = 0; i < n; i++) {
            if (!isCompleted[i] && processes[i].arrivalTime <= currentTime) {
                if (processes[i].remainingTime < minRemaining) {
                    minRemaining = processes[i].remainingTime;
                    idx = i;
                }
                else if (processes[i].remainingTime == minRemaining) {
                    // tie-breaker: earlier arrival
                    if (processes[i].arrivalTime < processes[idx].arrivalTime) {
                        idx = i;
                    }
                }
            }
        }

        if (idx == -1) {
            // No process ready ? CPU idle
            currentTime++;
            continue;
        }

        // Execute the process for 1 unit of time
        processes[idx].remainingTime--;
        currentTime++;

        // If process finished
        if (processes[idx].remainingTime == 0) {
            processes[idx].completionTime = currentTime;
            processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
            processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
            isCompleted[idx] = true;
            completed++;
        }
    }

    printResults(processes, "SJF Preemptive (SRTF)");
}

void Priority_Preemptive(vector<Process>& processes) {
    int n = processes.size();
    int completed = 0;
    int currentTime = 0;

    vector<bool> isCompleted(n, false);

    while (completed < n)
    {
        int idx = -1;
        int highestPriority = INT_MAX;

        // Find process with highest priority (lowest value) that has arrived
        for (int i = 0; i < n; i++) {
            if (!isCompleted[i] && processes[i].arrivalTime <= currentTime) {
                if (processes[i].priority < highestPriority) {
                    highestPriority = processes[i].priority;
                    idx = i;
                }
                else if (processes[i].priority == highestPriority) {
                    // tie-breaker: shorter remainingTime
                    if (processes[i].remainingTime < processes[idx].remainingTime) {
                        idx = i;
                    }
                    else if (processes[i].remainingTime == processes[idx].remainingTime) {
                        // tie-breaker: earlier arrival
                        if (processes[i].arrivalTime < processes[idx].arrivalTime) {
                            idx = i;
                        }
                    }
                }
            }
        }

        if (idx == -1) {
            // CPU idle
            currentTime++;
            continue;
        }

        // Execute for 1 time unit
        processes[idx].remainingTime--;
        currentTime++;

        // If process finished
        if (processes[idx].remainingTime == 0) {
            processes[idx].completionTime = currentTime;
            processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
            processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
            isCompleted[idx] = true;
            completed++;
        }
    }

    printResults(processes, "Priority Preemptive");
}

void MultiLevelQueue(vector<Process>& processes) {
    // Ready queues
    queue<Process*> systemQueue;   // Round Robin
    priority_queue<Process*, vector<Process*>, PriorityComparator> interactiveQueue;
    queue<Process*> batchQueue;    // FCFS

    int currentTime = 0;
    int completed = 0;
    int n = processes.size();
    int i = 0;

    const int TIME_QUANTUM = 2; // fixed quantum for SYSTEM queue

    while (completed < n)
    {
        // Add arrived processes to their respective queues
        while (i < n && processes[i].arrivalTime <= currentTime)
        {
            if (processes[i].queueType == SYSTEM)
                systemQueue.push(&processes[i]);
            else if (processes[i].queueType == INTERACTIVE)
                interactiveQueue.push(&processes[i]);
            else
                batchQueue.push(&processes[i]);

            i++;
        }

        /* ================= SYSTEM QUEUE (Round Robin) ================= */
        if (!systemQueue.empty())
        {
            Process* p = systemQueue.front();
            systemQueue.pop();

            int execTime = min(TIME_QUANTUM, p->remainingTime);
            p->remainingTime -= execTime;
            currentTime += execTime;

            // Add newly arrived processes during execution
            while (i < n && processes[i].arrivalTime <= currentTime)
            {
                if (processes[i].queueType == SYSTEM)
                    systemQueue.push(&processes[i]);
                else if (processes[i].queueType == INTERACTIVE)
                    interactiveQueue.push(&processes[i]);
                else
                    batchQueue.push(&processes[i]);
                i++;
            }

            if (p->remainingTime > 0)
            {
                systemQueue.push(p); // not finished ? back to queue
            }
            else
            {
                p->completionTime = currentTime;
                p->turnaroundTime = p->completionTime - p->arrivalTime;
                p->waitingTime = p->turnaroundTime - p->burstTime;
                completed++;
            }
        }

        /* ================= INTERACTIVE QUEUE (Priority NP) ================= */
        else if (!interactiveQueue.empty())
        {
            Process* p = interactiveQueue.top();
            interactiveQueue.pop();

            currentTime += p->burstTime;

            p->completionTime = currentTime;
            p->turnaroundTime = p->completionTime - p->arrivalTime;
            p->waitingTime = p->turnaroundTime - p->burstTime;

            completed++;
        }

        /* ================= BATCH QUEUE (FCFS) ================= */
        else if (!batchQueue.empty())
        {
            Process* p = batchQueue.front();
            batchQueue.pop();

            if (currentTime < p->arrivalTime)
                currentTime = p->arrivalTime;

            currentTime += p->burstTime;

            p->completionTime = currentTime;
            p->turnaroundTime = p->completionTime - p->arrivalTime;
            p->waitingTime = p->turnaroundTime - p->burstTime;

            completed++;
        }

        /* ================= CPU IDLE ================= */
        else
        {
            currentTime++;
        }
    }

    printResults(processes, "Multi-Level Queue");
}