#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <cstdlib>

#include "Process.h"
#include "Scheduler.h"
#include "Utils.h"

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif

// Function to clear the console (Windows specific, but can be adapted)
void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Enable UTF-8 Output for Windows
void setupConsole() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
}

// Function to pause and wait for user input
void pauseConsole() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

// Function to input processes safely
std::vector<Process> inputProcesses() {
    std::vector<Process> processes;
    int numOfProcesses;

    while (true) {
        std::cout << "\nEnter the number of processes: ";
        if (std::cin >> numOfProcesses && numOfProcesses > 0) {
            break;
        } else {
            std::cout << "Invalid input! Please enter a positive integer.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    for (int i = 0; i < numOfProcesses; i++) {
        int pid, at, bt, prio, qType;
        
        std::cout << "\n--- Process " << (i + 1) << " ---\n";
        
        // Input PID
        while (true) {
            std::cout << "PID: ";
            if (std::cin >> pid) break;
            std::cout << "Invalid PID! Enter a number.\n";
            std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        // Input Arrival Time
        while (true) {
            std::cout << "Arrival Time: ";
            if (std::cin >> at && at >= 0) break;
            std::cout << "Invalid Arrival Time! Must be non-negative.\n";
            std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        // Input Burst Time
        while (true) {
            std::cout << "Burst Time: ";
            if (std::cin >> bt && bt > 0) break;
            std::cout << "Invalid Burst Time! Must be positive.\n";
            std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        // Input Priority
        while (true) {
            std::cout << "Priority (lower value = higher priority): ";
            if (std::cin >> prio) break;
            std::cout << "Invalid Priority! Enter a number.\n";
            std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        // Input Queue Type
        while (true) {
            std::cout << "Queue Type (0 = SYSTEM, 1 = INTERACTIVE, 2 = BATCH): ";
            if (std::cin >> qType && qType >= 0 && qType <= 2) break;
            std::cout << "Invalid Queue Type! Enter 0, 1, or 2.\n";
            std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        processes.emplace_back(pid, at, bt, prio, static_cast<QueueType>(qType));
    }
    
    std::cout << "\nProcesses entered successfully!\n";
    pauseConsole();
    return processes;
}

void showAbout() {
    clearConsole();
    std::cout << "\n============================================\n";
    std::cout << "      CPU Scheduling Simulator - Help       \n";
    std::cout << "============================================\n";
    std::cout << "This generic CLI tool simulates various CPU scheduling algorithms.\n\n";
    std::cout << "Available Algorithms:\n";
    std::cout << "1. FCFS (First-Come First-Served)\n";
    std::cout << "2. SJF (Shortest Job First) - Non-Preemptive\n";
    std::cout << "3. Priority Scheduling - Non-Preemptive\n";
    std::cout << "4. Round Robin (Time Quantum)\n";
    std::cout << "5. SJF (Shortest Job First) - Preemptive (SRTF)\n";
    std::cout << "6. Priority Scheduling - Preemptive\n";
    std::cout << "7. Multi-Level Queue Scheduling\n\n";
    std::cout << "Note: Ensure you enter processes before running simulation.\n";
    pauseConsole();
}

int main() {
    setupConsole();
    std::vector<Process> originalProcesses;
    int choice;

    while (true) {
        clearConsole();
        std::cout << "\n============================================\n";
        std::cout << "       CPU SCHEDULING SIMULATOR CLI         \n";
        std::cout << "============================================\n";
        std::cout << "1. Enter Process Data\n";
        std::cout << "2. Run Simulation Algorithm\n";
        std::cout << "3. Help / About\n";
        std::cout << "4. Exit\n";
        std::cout << "============================================\n";
        std::cout << "Enter your choice: ";
        
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        switch (choice) {
        case 1:
            originalProcesses = inputProcesses();
            break;

        case 2:
            if (originalProcesses.empty()) {
                std::cout << "\n[ERROR] No processes loaded! Please enter data first.\n";
                pauseConsole();
            } else {
                int algoChoice;
                clearConsole();
                std::cout << "\nSelect Algorithm:\n";
                std::cout << "1. FCFS\n";
                std::cout << "2. SJF (Non-Preemptive)\n";
                std::cout << "3. Priority (Non-Preemptive)\n";
                std::cout << "4. Round Robin\n";
                std::cout << "5. SJF (Preemptive)\n";
                std::cout << "6. Priority (Preemptive)\n";
                std::cout << "7. Multi-Level Queue Scheduling\n";
                std::cout << "Enter choice: ";
                
                std::cin >> algoChoice;
                
                // Create a clean copy for simulation
                std::vector<Process> simProcesses = originalProcesses;
                // Pre-sort is often required by the logic
                sortByArrivalTime(simProcesses);
                
                int timeQuantum;

                switch (algoChoice) {
                case 1: FCFS(simProcesses); break;
                case 2: SJF_NonPreemptive(simProcesses); break;
                case 3: Priority_NonPreemptive(simProcesses); break;
                case 4: 
                    std::cout << "Enter Time Quantum: ";
                    std::cin >> timeQuantum;
                    RoundRobin(simProcesses, timeQuantum); 
                    break;
                case 5: SJF_Preemptive(simProcesses); break;
                case 6: Priority_Preemptive(simProcesses); break;
                case 7: MultiLevelQueue(simProcesses); break;
                default: std::cout << "Invalid Algorithm selection!\n"; break;
                }
                
                pauseConsole();
            }
            break;

        case 3:
            showAbout();
            break;

        case 4:
            std::cout << "Exiting...\n";
            return 0;

        default:
            std::cout << "Invalid choice! Try again.\n";
            pauseConsole();
            break;
        }
    }

    return 0;
}
