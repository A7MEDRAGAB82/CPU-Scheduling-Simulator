#include "Utils.h"
#include <iostream>
#include <algorithm>

void sortByArrivalTime(vector<Process>& processes) {
    sort(processes.begin(), processes.end(),
        [](const Process& a, const Process& b) {
            return a.arrivalTime < b.arrivalTime;
        });
}

void printResults(const vector<Process>& processes, const string& title) {
    cout << "\n" << title << " Scheduling Results:\n";
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
