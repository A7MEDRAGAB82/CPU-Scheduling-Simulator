#include "Utils.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string>

using namespace std;

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
    // ANSI Color Codes
    const string RESET = "\033[0m";
    const string RED = "\033[31m";
    const string GREEN = "\033[32m";
    const string YELLOW = "\033[33m";
    const string BLUE = "\033[34m";
    const string MAGENTA = "\033[35m";
    const string CYAN = "\033[36m";
    const string WHITE = "\033[37m";
    const string BOLD = "\033[1m";

    // Box Drawing Characters (UTF-8)
    const string HL = "\u2550"; // Horizontal Line ═
    const string VL = "\u2551"; // Vertical Line ║
    const string TL = "\u2554"; // Top Left ╔
    const string TR = "\u2557"; // Top Right ╗
    const string BL = "\u255A"; // Bottom Left ╚
    const string BR = "\u255D"; // Bottom Right ╝
    const string T_DOWN = "\u2566"; // ╦
    const string T_UP = "\u2569";   // ╩
    const string T_CROSS = "\u256C";// ╬
    const string T_LEFT = "\u2560"; // ╠
    const string T_RIGHT = "\u2563";// ╣

    // Widths
    const int wPID = 6;
    const int wAT = 8;
    const int wBT = 8;
    const int wCT = 8;
    const int wTAT = 8;
    const int wWT = 8;
    const int wBar = 20; // Width for the visual bar

    // Helper to draw a horizontal separator
    auto drawLine = [&](string left, string mid, string right, string lineChar) {
        cout << left;
        cout << string(wPID, lineChar[0]) << mid;
        cout << string(wAT, min(lineChar[0], lineChar[0])) << mid; // hack to use char
        // Actually simpler to just loop or use repeat.
        // Let's just build the string manually for precision with UTF-8 chars which are multi-byte
        
        // C++ string constructor using fill char only works for single byte. 
        // We'll iterate.
        for(int i=0; i<wPID; i++) cout << lineChar; cout << mid;
        for(int i=0; i<wAT; i++) cout << lineChar; cout << mid;
        for(int i=0; i<wBT; i++) cout << lineChar; cout << mid;
        for(int i=0; i<wCT; i++) cout << lineChar; cout << mid;
        for(int i=0; i<wTAT; i++) cout << lineChar; cout << mid;
        for(int i=0; i<wWT; i++) cout << lineChar; cout << mid;
        for(int i=0; i<wBar; i++) cout << lineChar; 
        cout << right << "\n";
    };

    cout << "\n";
    cout << BOLD << MAGENTA << "  " << title << " Algorithm Results" << RESET << "\n";
    
    // Top Border
    cout << CYAN;
    drawLine(TL, T_DOWN, TR, HL);
    
    // Header
    cout << VL << WHITE << " " << left << setw(wPID-1) << "PID" << CYAN << VL
         << WHITE << " " << setw(wAT-1) << "Arr" << CYAN << VL
         << WHITE << " " << setw(wBT-1) << "Brst" << CYAN << VL
         << WHITE << " " << setw(wCT-1) << "Comp" << CYAN << VL
         << WHITE << " " << setw(wTAT-1) << "TAT" << CYAN << VL
         << WHITE << " " << setw(wWT-1) << "Wait" << CYAN << VL
         << WHITE << " " << setw(wBar-1) << "Visual (Wait|Burst)" << CYAN << VL << "\n";

    // Separator
    drawLine(T_LEFT, T_CROSS, T_RIGHT, HL);

    double totalTAT = 0.0;
    double totalWT = 0.0;
    int n = processes.size();

    // Rows
    for (const auto& p : processes) {
        // Prepare visual bar
        // Total width 20. 
        // Scale = (Wait + Burst) / Max(Wait+Burst) usually, but simple scaling:
        // Let's just say each # is 2 units? Or normalized to 20 chars max?
        // Let's try to fit (Wait + Burst) into 18 chars.
        
        string bar = "";
        int totalUnits = p.waitingTime + p.burstTime;
        if (totalUnits > 0) {
            int waitChars = (p.waitingTime * 18) / totalUnits;
            int burstChars = 18 - waitChars; 
            
            // Wait part (Red)
            if (waitChars > 0) bar += RED + string(waitChars, '.') + RESET;
            // Burst part (Green)
            if (burstChars > 0) bar += GREEN + string(burstChars, '#') + RESET;
        }
        
        int visibleBarLength = 0;
        int totalUnitsCalc = p.waitingTime + p.burstTime;
        if (totalUnitsCalc > 0) {
             // Re-calculate to be sure matches logic above
             int w = (p.waitingTime * 18) / totalUnitsCalc;
             int b = 18 - w; 
             if (w > 0) visibleBarLength += w;
             if (b > 0) visibleBarLength += b;
        }

        // Calculate padding needed for visual alignment
        int padding = wBar - visibleBarLength;
        if (padding < 0) padding = 0;

        cout << VL << YELLOW << " " << left << setw(wPID-1) << p.pid << CYAN << VL
             << RESET << " " << setw(wAT-1) << p.arrivalTime << CYAN << VL
             << RESET << " " << setw(wBT-1) << p.burstTime << CYAN << VL
             << RESET << " " << setw(wCT-1) << p.completionTime << CYAN << VL
             << RESET << " " << setw(wTAT-1) << p.turnaroundTime << CYAN << VL
             << RESET << " " << setw(wWT-1) << p.waitingTime << CYAN << VL
             << " " << bar << string(padding, ' ') << CYAN << VL << "\n"; 

        totalTAT += p.turnaroundTime;
        totalWT += p.waitingTime;
    }

    // Bottom Border
    drawLine(BL, T_UP, BR, HL);
    cout << RESET;

    // Averages
    cout << "\n";
    cout << YELLOW << "  Average Turnaround Time: " << BOLD << WHITE << fixed << setprecision(2) << (totalTAT / n) << RESET << "\n";
    cout << YELLOW << "  Average Waiting Time:    " << BOLD << WHITE << fixed << setprecision(2) << (totalWT / n) << RESET << "\n";
    cout << "\n";
}
