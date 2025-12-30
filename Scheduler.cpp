#include "Scheduler.h"
#include <algorithm>
#include <queue>
#include <iostream>
#include "Utils.h"
#include <climits>

using namespace std;

/**
 * Comparator for SJF (Shortest Job First) priority queue
 * Creates a min-heap based on burst time
 * Tie-breaker: earlier arrival time has higher priority
 */
struct SJFComparator {
    bool operator()(Process* a, Process* b) {
        if (a->burstTime == b->burstTime)
            return a->arrivalTime > b->arrivalTime; // Earlier arrival wins
        return a->burstTime > b->burstTime; // Shorter burst time wins
    }
};

/**
 * Comparator for Priority-based scheduling
 * Creates a min-heap based on priority value (lower value = higher priority)
 * Tie-breakers: arrival time, then PID
 */
struct PriorityComparator {
    bool operator()(Process* a, Process* b) {
        if (a->priority != b->priority)
            return a->priority > b->priority;   // Lower priority value = higher priority
        if (a->arrivalTime != b->arrivalTime)
            return a->arrivalTime > b->arrivalTime; // Tie-breaker: earlier arrival
        return a->pid > b->pid; // Tie-breaker: smaller PID
    }
};





/**
 * First-Come-First-Served (FCFS) Scheduling Algorithm
 * 
 * Processes are executed in the order they arrive in the ready queue.
 * This is the simplest scheduling algorithm - no preemption, no priority.
 * 
 * Time Complexity: O(n) where n is the number of processes
 * Space Complexity: O(1)
 * 
 * @param processes Vector of processes to schedule (must be sorted by arrival time)
 */
void FCFS(vector<Process>& processes)
{
    int currentTime = 0; // Tracks the current CPU time during simulation

    // Execute processes in order of arrival
    for (auto& process : processes)
    {
        // If CPU is idle, wait until the process arrives
        if (currentTime < process.arrivalTime)
            currentTime = process.arrivalTime;

        // Execute the process completely (advance currentTime by Burst Time)
        currentTime += process.burstTime;

        // Calculate performance metrics
        process.completionTime = currentTime;
        process.turnaroundTime = process.completionTime - process.arrivalTime;
        process.waitingTime = process.turnaroundTime - process.burstTime;
    }

    printResults(processes, "FCFS");
}

/**
 * Shortest Job First (SJF) Non-Preemptive Scheduling Algorithm
 * 
 * Selects the process with the shortest burst time from the ready queue.
 * Once a process starts executing, it runs to completion (non-preemptive).
 * 
 * Time Complexity: O(n log n) where n is the number of processes
 * Space Complexity: O(n) for the priority queue
 * 
 * @param processes Vector of processes to schedule (must be sorted by arrival time)
 */
void SJF_NonPreemptive(vector<Process>& processes)
{
    // Priority queue (min-heap) based on burst time
    // Shorter burst time = higher priority
    priority_queue<Process*, vector<Process*>, SJFComparator> readyQueue;

    int currentTime = 0;
    int completed = 0;
    int nextIndex = 0;
    int n = processes.size();

    // Simulation loop: continue until all processes are completed
    while (completed < n)
    {
        // Add all processes that have arrived by currentTime to ready queue
        while (nextIndex < n && processes[nextIndex].arrivalTime <= currentTime) {
            readyQueue.push(&processes[nextIndex]);
            nextIndex++;
        }

        // CPU idle case: no process is ready
        if (readyQueue.empty()) {
            if (nextIndex < n) {
                // Jump to next arrival time
                currentTime = processes[nextIndex].arrivalTime;
            } else {
                // All processes have arrived but not completed (shouldn't happen)
                break;
            }
            continue;
        }

        // Select process with shortest burst time
        Process* selected = readyQueue.top();
        readyQueue.pop();

        // Execute process completely (non-preemptive)
        currentTime += selected->burstTime;

        // Calculate performance metrics
        selected->completionTime = currentTime;
        selected->turnaroundTime = selected->completionTime - selected->arrivalTime;
        selected->waitingTime = selected->turnaroundTime - selected->burstTime;

        completed++;

        // IMPORTANT: Add any processes that arrived during execution
        while (nextIndex < n && processes[nextIndex].arrivalTime <= currentTime) {
            readyQueue.push(&processes[nextIndex]);
            nextIndex++;
        }
    }

    printResults(processes, "SJF (Non-Preemptive)");
}

/**
 * Priority Non-Preemptive Scheduling Algorithm
 * 
 * Selects the process with the highest priority (lowest priority value) from the ready queue.
 * Once a process starts executing, it runs to completion (non-preemptive).
 * 
 * Time Complexity: O(n log n) where n is the number of processes
 * Space Complexity: O(n) for the priority queue
 * 
 * @param processes Vector of processes to schedule (must be sorted by arrival time)
 */
void Priority_NonPreemptive(vector<Process>& processes)
{
    // Priority queue (min-heap) based on priority value
    // Lower priority value = higher priority
    priority_queue<Process*, vector<Process*>, PriorityComparator> readyQueue;

    int currentTime = 0;
    int completed = 0;
    int nextIndex = 0;
    int n = processes.size();

    // Simulation loop: continue until all processes are completed
    while (completed < n)
    {
        // Add all processes that have arrived by currentTime to ready queue
        while (nextIndex < n && processes[nextIndex].arrivalTime <= currentTime) {
            readyQueue.push(&processes[nextIndex]);
            nextIndex++;
        }

        // CPU idle case: no process is ready
        if (readyQueue.empty()) {
            if (nextIndex < n) {
                // Jump to next arrival time
                currentTime = processes[nextIndex].arrivalTime;
            } else {
                // All processes have arrived but not completed (shouldn't happen)
                break;
            }
            continue;
        }

        // Select process with highest priority (lowest priority value)
        Process* selected = readyQueue.top();
        readyQueue.pop();

        // Execute process completely (non-preemptive)
        currentTime += selected->burstTime;

        // Calculate performance metrics
        selected->completionTime = currentTime;
        selected->turnaroundTime = selected->completionTime - selected->arrivalTime;
        selected->waitingTime = selected->turnaroundTime - selected->burstTime;

        completed++;

        // IMPORTANT: Add any processes that arrived during execution
        while (nextIndex < n && processes[nextIndex].arrivalTime <= currentTime) {
            readyQueue.push(&processes[nextIndex]);
            nextIndex++;
        }
    }

    printResults(processes, "Priority (Non-Preemptive)");
}

/**
 * Round Robin (RR) Scheduling Algorithm
 * 
 * Each process gets a fixed time quantum. If a process doesn't complete
 * within its quantum, it's preempted and moved to the end of the queue.
 * This ensures fair CPU allocation and prevents starvation.
 * 
 * Time Complexity: O(n × q) where n is number of processes, q is time quantum
 * Space Complexity: O(n) for the ready queue
 * 
 * @param processes Vector of processes to schedule (must be sorted by arrival time)
 * @param timeQuantum Fixed time slice allocated to each process
 */
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
            int nextArrival = INT_MAX;
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

/**
 * Shortest Job First Preemptive (SRTF - Shortest Remaining Time First) Algorithm
 * 
 * Always executes the process with the shortest remaining time.
 * If a new process arrives with shorter remaining time, current process is preempted.
 * This is optimal for minimizing average waiting time in preemptive scheduling.
 * 
 * Time Complexity: O(n² × max_bt) where n is number of processes, max_bt is max burst time
 * Space Complexity: O(n)
 * 
 * @param processes Vector of processes to schedule (must be sorted by arrival time)
 */
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

/**
 * Priority Preemptive Scheduling Algorithm
 * 
 * Always executes the process with the highest priority (lowest priority value).
 * If a new process arrives with higher priority, current process is preempted.
 * Suitable for real-time systems where priority matters.
 * 
 * Time Complexity: O(n² × max_bt) where n is number of processes, max_bt is max burst time
 * Space Complexity: O(n)
 * 
 * @param processes Vector of processes to schedule (must be sorted by arrival time)
 */
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

/**
 * Multi-Level Queue Scheduling Algorithm
 * 
 * Divides processes into multiple queues based on process type:
 * - SYSTEM Queue: Round Robin with time quantum = 2 (highest priority)
 * - INTERACTIVE Queue: Priority Non-Preemptive (medium priority)
 * - BATCH Queue: FCFS (lowest priority)
 * 
 * Queues are served in priority order (SYSTEM > INTERACTIVE > BATCH)
 * 
 * Time Complexity: O(n × q) where n is number of processes, q is time quantum
 * Space Complexity: O(n)
 * 
 * @param processes Vector of processes to schedule (must be sorted by arrival time)
 */
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

            // Execute process completely (non-preemptive)
            currentTime += p->remainingTime;
            p->remainingTime = 0;

            p->completionTime = currentTime;
            p->turnaroundTime = p->completionTime - p->arrivalTime;
            p->waitingTime = p->turnaroundTime - p->burstTime;

            completed++;

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
        }

        /* ================= BATCH QUEUE (FCFS) ================= */
        else if (!batchQueue.empty())
        {
            Process* p = batchQueue.front();
            batchQueue.pop();

            // Wait if process hasn't arrived yet
            if (currentTime < p->arrivalTime)
                currentTime = p->arrivalTime;

            // Execute process completely
            currentTime += p->remainingTime;
            p->remainingTime = 0;

            p->completionTime = currentTime;
            p->turnaroundTime = p->completionTime - p->arrivalTime;
            p->waitingTime = p->turnaroundTime - p->burstTime;

            completed++;

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
        }

        /* ================= CPU IDLE ================= */
        else
        {
            // No process in any queue - jump to next arrival time
            if (i < n) {
                currentTime = processes[i].arrivalTime;
            } else {
                // All processes have arrived but not completed (shouldn't happen)
                currentTime++;
            }
        }
    }

    printResults(processes, "Multi-Level Queue");
}