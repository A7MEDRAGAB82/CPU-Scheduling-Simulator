# CPU Scheduling Simulator

A powerful, interactive Command Line Interface (CLI) tool for simulating various CPU scheduling algorithms. This project is designed to help students and developers understand how operating systems manage process scheduling.

## 🚀 Features

- **Interactive CLI**: Easy-to-use menu-driven interface.
- **Process Entry**: Flexible input for multiple processes including PID, Arrival Time, Burst Time, Priority, and Queue Type.
- **Input Validation**: Robust handling to ensure valid data entry.
- **Detailed Statistics**: Calculates and displays Waiting Time, Turnaround Time, and Response Time.
- **Visual Output**: (If implemented) Formatted tables for clear result visualization.
- **Cross-Platform Support**: Optimized for Windows (with UTF-8 support) but structure allows for easy adaptation to Linux/macOS.

## 🧠 Supported Algorithms

1. **FCFS** (First-Come First-Served)
2. **SJF** (Shortest Job First) - Non-Preemptive
3. **SJF** (Shortest Job First) - Preemptive (SRTF)
4. **Priority Scheduling** - Non-Preemptive
5. **Priority Scheduling** - Preemptive
6. **Round Robin** (with customizable Time Quantum)
7. **Multi-Level Queue Scheduling** (System, Interactive, Batch queues)

## 🛠️ Getting Started

### Prerequisites

- A C++ Compiler (GCC, Clang, or MSVC).
- **Windows OS** is recommended for the best experience (due to specific console formatting), but the core logic is standard C++.

### Installation & Compilation

1. **Clone the repository** (or download usage files):
   ```sh
   git clone <repository-url>
   cd CPU-Scheduling-Simulator
   ```

2. **Compile the code**:
   
   Using **g++**:
   ```sh
   g++ -o simulator *.cpp
   ```
   
   Using **Visual Studio**:
   - Open the `.sln` file.
   - Build the solution (`Ctrl + Shift + B`).

### Usage

1. Run the executable:
   ```sh
   ./simulator.exe
   ```
2. **Enter Process Data**: Select option `1` to input your processes. You will be asked for:
   - Number of Processes
   - For each process: PID, Arrival Time, Burst Time, Priority (lower = higher), and Queue Type.
3. **Run Simulation**: Select option `2` and choose the algorithm you wish to simulate.
4. **View Results**: The simulator will process the data and display the scheduling order and time metrics.

## 📂 Project Structure

- `CPU-Scheduling-Simulator.cpp`: Main entry point and menu logic.
- `Scheduler.cpp` / `Scheduler.h`: Implementation of all scheduling algorithms.
- `Process.h`: Definition of the Process structure/class.
- `Utils.cpp` / `Utils.h`: Helper functions for UI and formatting.

## 🤝 Contributing

Contributions are welcome! Feel free to submit a Pull Request.

## 📄 License

This project is open-source and free to use for educational purposes.
