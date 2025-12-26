#include "Utils.h"
#include <iostream>
#include <algorithm>

/**
 * Sorts processes by arrival time in ascending order
 * This is a prerequisite for most scheduling algorithms
 * 
 * @param processes Vector of processes to sort
 */
void sortByArrivalTime(vector<Process>& processes) {
    sort(processes.begin(), processes.end(),
        [](const Process& a, const Process& b) {
            return a.arrivalTime < b.arrivalTime;
        });
}

/**
 * Prints scheduling results in a formatted table
 * Also calculates and displays average turnaround time and average waiting time
 * 
 * @param processes Vector of processes with calculated metrics
 * @param title Title of the scheduling algorithm
 */
void printResults(const vector<Process>& processes, const string& title) {
    cout << "\n" << string(60, '=') << "\n";
    cout << title << " Scheduling Results:\n";
    cout << string(60, '=') << "\n";
    cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";
    cout << string(60, '-') << "\n";

    double totalTAT = 0.0;
    double totalWT = 0.0;
    int n = processes.size();

    for (const auto& p : processes) {
        cout << p.pid << "\t"
            << p.arrivalTime << "\t"
            << p.burstTime << "\t"
            << p.completionTime << "\t"
            << p.turnaroundTime << "\t"
            << p.waitingTime << endl;
        
        totalTAT += p.turnaroundTime;
        totalWT += p.waitingTime;
    }

    cout << string(60, '-') << "\n";
    cout << "Average Turnaround Time: " << (totalTAT / n) << "\n";
    cout << "Average Waiting Time: " << (totalWT / n) << "\n";
    cout << string(60, '=') << "\n\n";
}
