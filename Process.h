#pragma once

// Represents a process in the CPU scheduling simulation
// Time is assumed to be discrete (integer time units)
struct Process {
    int pid;               // unique process ID

    int arrivalTime;       // time when process enters ready queue
    int burstTime;         // total CPU execution time
    int remainingTime;     // used for preemptive algorithms (RR, SJF preemptive)
    int priority;          // lower value = higher priority (assumption)

    int waitingTime;       // total time spent waiting in ready queue
    int turnaroundTime;    // completionTime - arrivalTime
    int completionTime;    // time when process finishes execution

    Process(int pid, int at, int bt, int prio)
        : pid(pid),
        arrivalTime(at),
        burstTime(bt),
        remainingTime(bt),
        priority(prio),
        waitingTime(0),
        turnaroundTime(0),
        completionTime(0) {}
};
