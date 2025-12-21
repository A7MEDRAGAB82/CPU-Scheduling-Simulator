# CPU Scheduling Simulator

A comprehensive CPU scheduling algorithms simulator implemented in C++. This project demonstrates and compares various CPU scheduling algorithms used in operating systems, providing detailed performance metrics for each algorithm.

## 📋 Table of Contents

- [Features](#features)
- [Supported Algorithms](#supported-algorithms)
- [Project Structure](#project-structure)
- [Requirements](#requirements)
- [Building the Project](#building-the-project)
- [Usage](#usage)
- [Algorithm Details](#algorithm-details)
- [Example](#example)
- [Performance Metrics](#performance-metrics)
- [Contributing](#contributing)
- [License](#license)

## ✨ Features

- **7 Different Scheduling Algorithms**: Implementations of the most common CPU scheduling algorithms
- **Interactive CLI**: User-friendly command-line interface for process input
- **Detailed Metrics**: Calculates and displays completion time, turnaround time, and waiting time for each process
- **Multi-Level Queue Support**: Advanced scheduling with priority-based queues
- **Preemptive & Non-Preemptive**: Support for both scheduling modes
- **Well-Structured Code**: Modular design with separate files for different components

## 🎯 Supported Algorithms

1. **FCFS (First-Come-First-Served)**
   - Non-preemptive scheduling
   - Processes executed in order of arrival
   - Simple and fair, but may cause convoy effect

2. **SJF Non-Preemptive (Shortest Job First)**
   - Non-preemptive scheduling
   - Selects process with shortest burst time
   - Optimal for minimizing average waiting time

3. **Priority Non-Preemptive**
   - Non-preemptive scheduling
   - Processes scheduled based on priority (lower value = higher priority)
   - Useful for real-time systems

4. **Round Robin**
   - Preemptive scheduling
   - Each process gets a fixed time quantum
   - Prevents starvation and provides fair CPU allocation

5. **SJF Preemptive (SRTF - Shortest Remaining Time First)**
   - Preemptive scheduling
   - Always executes process with shortest remaining time
   - Optimal for minimizing average waiting time

6. **Priority Preemptive**
   - Preemptive scheduling
   - Higher priority processes can preempt lower priority ones
   - Suitable for real-time systems with varying priorities

7. **Multi-Level Queue Scheduling**
   - Combines multiple scheduling algorithms
   - **SYSTEM Queue**: Round Robin (Time Quantum = 2)
   - **INTERACTIVE Queue**: Priority Non-Preemptive
   - **BATCH Queue**: FCFS
   - Processes assigned to queues based on type

## 📁 Project Structure

```
CPU-Scheduling-Simulator/
│
├── CPU-Scheduling-Simulator.cpp  # Main program entry point
├── Process.h                      # Process structure definition
├── Scheduler.h                    # Scheduler function declarations
├── Scheduler.cpp                  # Algorithm implementations
├── Utils.h                        # Utility function declarations
├── Utils.cpp                      # Utility function implementations
├── CPU-Scheduling-Simulator.sln   # Visual Studio solution file
├── CPU-Scheduling-Simulator.vcxproj # Visual Studio project file
└── README.md                      # This file
```

### File Descriptions

- **CPU-Scheduling-Simulator.cpp**: Main program that handles user input and menu navigation
- **Process.h**: Defines the `Process` structure and `QueueType` enum
- **Scheduler.h/cpp**: Contains all scheduling algorithm implementations
- **Utils.h/cpp**: Utility functions for sorting and displaying results

## 🔧 Requirements

- **Compiler**: C++11 or later compatible compiler
- **IDE**: Visual Studio 2019 or later (recommended)
- **Platform**: Windows (tested), Linux/macOS (with minor modifications)

## 🏗️ Building the Project

### Using Visual Studio

1. Open `CPU-Scheduling-Simulator.sln` in Visual Studio
2. Select your build configuration (Debug/Release)
3. Build the solution (Ctrl+Shift+B or Build → Build Solution)
4. The executable will be generated in `x64/Debug/` or `x64/Release/`

### Using Command Line (MSVC)

```bash
cl /EHsc CPU-Scheduling-Simulator.cpp Scheduler.cpp Utils.cpp /Fe:CPU-Scheduling-Simulator.exe
```

### Using GCC/Clang (Linux/macOS)

```bash
g++ -std=c++11 CPU-Scheduling-Simulator.cpp Scheduler.cpp Utils.cpp -o CPU-Scheduling-Simulator
```

## 🚀 Usage

1. Run the executable
2. Enter the number of processes
3. For each process, provide:
   - **PID**: Process ID (unique identifier)
   - **Arrival Time**: Time when process arrives in ready queue
   - **Burst Time**: Total CPU time required (must be positive)
   - **Priority**: Process priority (lower value = higher priority)
   - **Queue Type**: 
     - `0` = SYSTEM
     - `1` = INTERACTIVE
     - `2` = BATCH
4. Select the scheduling algorithm from the menu
5. For Round Robin, enter the time quantum when prompted
6. View the results table showing completion time, turnaround time, and waiting time

## 📊 Algorithm Details

### Process Structure

Each process contains:
- `pid`: Unique process identifier
- `arrivalTime`: Time when process enters the system
- `burstTime`: Total CPU execution time required
- `remainingTime`: Remaining execution time (used in preemptive algorithms)
- `priority`: Process priority level
- `queueType`: Queue assignment for Multi-Level Queue scheduling
- `completionTime`: Time when process finishes execution
- `turnaroundTime`: Total time in system (completionTime - arrivalTime)
- `waitingTime`: Time spent waiting in ready queue (turnaroundTime - burstTime)

### Tie-Breaking Rules

- **SJF**: If burst times are equal, earlier arrival time wins
- **Priority**: If priorities are equal, earlier arrival time wins, then smaller PID
- **Preemptive Algorithms**: Execute for 1 time unit, then re-evaluate

## 💡 Example

```
Please enter the number of processes: 5

Enter PID, ArrivalTime, BurstTime, Priority: 1 0 8 2
Queue Type (0 = SYSTEM, 1 = INTERACTIVE, 2 = BATCH): 1

Enter PID, ArrivalTime, BurstTime, Priority: 2 1 4 1
Queue Type (0 = SYSTEM, 1 = INTERACTIVE, 2 = BATCH): 0

Enter PID, ArrivalTime, BurstTime, Priority: 3 2 9 3
Queue Type (0 = SYSTEM, 1 = INTERACTIVE, 2 = BATCH): 2

Enter PID, ArrivalTime, BurstTime, Priority: 4 3 5 2
Queue Type (0 = SYSTEM, 1 = INTERACTIVE, 2 = BATCH): 1

Enter PID, ArrivalTime, BurstTime, Priority: 5 6 2 4
Queue Type (0 = SYSTEM, 1 = INTERACTIVE, 2 = BATCH): 0

Choose Algorithm:
1. FCFS
2. SJF (Non-Preemptive)
3. Priority (Non-Preemptive)
4. Round Robin
5. SJF (Preemptive)
6. Priority (Preemptive)
7. Multi-Level Queue Scheduling
Enter your choice: 2

SJF_NonPreemptive Scheduling Results:
PID     AT      BT      CT      TAT     WT
1       0       8       8       8       0
2       1       4       14      13      9
3       2       9       28      26      17
4       3       5       19      16      11
5       6       2       10      4       2
```

## 📈 Performance Metrics

The simulator calculates three key performance metrics:

1. **Completion Time (CT)**: Time when process finishes execution
2. **Turnaround Time (TAT)**: Total time process spends in system
   - Formula: `TAT = CT - AT`
3. **Waiting Time (WT)**: Time process spends waiting in ready queue
   - Formula: `WT = TAT - BT`

### Performance Comparison

- **FCFS**: Simple but may have high average waiting time
- **SJF**: Minimizes average waiting time (optimal for non-preemptive)
- **SRTF**: Minimizes average waiting time (optimal for preemptive)
- **Round Robin**: Fair allocation, prevents starvation
- **Priority**: Good for real-time systems
- **Multi-Level Queue**: Balances different process types

## 🔍 Algorithm Complexity

| Algorithm | Time Complexity | Space Complexity |
|-----------|-----------------|------------------|
| FCFS | O(n) | O(1) |
| SJF Non-Preemptive | O(n log n) | O(n) |
| Priority Non-Preemptive | O(n log n) | O(n) |
| Round Robin | O(n × q) | O(n) |
| SJF Preemptive | O(n² × max_bt) | O(n) |
| Priority Preemptive | O(n² × max_bt) | O(n) |
| Multi-Level Queue | O(n × q) | O(n) |

Where:
- `n` = number of processes
- `q` = time quantum (for Round Robin)
- `max_bt` = maximum burst time

## 🐛 Known Limitations

- Processes must have positive burst times
- Time is discrete (integer values only)
- No I/O operations or context switching overhead
- Priority values: lower number = higher priority

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request. Areas for improvement:

- Additional scheduling algorithms (e.g., Multilevel Feedback Queue)
- Graphical visualization of scheduling timeline
- Export results to CSV/JSON
- Unit tests
- Performance analysis tools

## 📝 License

This project is created for educational purposes as part of an Operating Systems course.

## 👨‍💻 Author

Developed as part of the Operating Systems course project.

## 🙏 Acknowledgments

- Operating Systems concepts and scheduling algorithms
- CPU scheduling theory and implementations

---

**Note**: This simulator is designed for educational purposes to understand CPU scheduling algorithms. For production use, consider additional factors like I/O operations, context switching overhead, and system-specific optimizations.

