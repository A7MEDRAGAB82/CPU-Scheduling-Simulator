# Project Structure

This document provides a detailed overview of the project structure and architecture.

## Directory Structure

```
CPU-Scheduling-Simulator/
│
├── 📄 CPU-Scheduling-Simulator.cpp  # Main program entry point
├── 📄 Process.h                      # Process structure definition
├── 📄 Scheduler.h                    # Scheduler function declarations
├── 📄 Scheduler.cpp                  # Algorithm implementations
├── 📄 Utils.h                        # Utility function declarations
├── 📄 Utils.cpp                      # Utility function implementations
│
├── 📄 README.md                      # Main documentation
├── 📄 CONTRIBUTING.md                # Contribution guidelines
├── 📄 LICENSE                        # MIT License
├── 📄 .gitignore                     # Git ignore rules
│
├── 📁 x64/                           # Build output directory
│   └── Debug/                        # Debug build artifacts
│
└── 📁 CPU-Sche.0ff8ef09/            # Visual Studio build files
```

## File Descriptions

### Core Source Files

#### `CPU-Scheduling-Simulator.cpp`
- **Purpose**: Main program entry point
- **Responsibilities**:
  - User input handling
  - Process data collection
  - Menu system for algorithm selection
  - Input validation
- **Key Functions**: `main()`

#### `Process.h`
- **Purpose**: Data structure definitions
- **Contents**:
  - `Process` struct: Represents a process with all scheduling attributes
  - `QueueType` enum: Defines queue types for Multi-Level Queue scheduling
- **Key Members**:
  - Process identification: `pid`
  - Timing: `arrivalTime`, `burstTime`, `remainingTime`
  - Priority: `priority`
  - Results: `completionTime`, `turnaroundTime`, `waitingTime`
  - Queue assignment: `queueType`

#### `Scheduler.h` / `Scheduler.cpp`
- **Purpose**: Scheduling algorithm implementations
- **Algorithms Implemented**:
  1. `FCFS()` - First-Come-First-Served
  2. `SJF_NonPreemptive()` - Shortest Job First (Non-Preemptive)
  3. `Priority_NonPreemptive()` - Priority Scheduling (Non-Preemptive)
  4. `RoundRobin()` - Round Robin with time quantum
  5. `SJF_Preemptive()` - Shortest Remaining Time First (SRTF)
  6. `Priority_Preemptive()` - Priority Scheduling (Preemptive)
  7. `MultiLevelQueue()` - Multi-Level Queue Scheduling
- **Supporting Structures**:
  - `SJFComparator`: Comparator for SJF priority queue
  - `PriorityComparator`: Comparator for priority-based scheduling

#### `Utils.h` / `Utils.cpp`
- **Purpose**: Utility functions
- **Functions**:
  - `sortByArrivalTime()`: Sorts processes by arrival time
  - `printResults()`: Displays scheduling results with statistics

## Architecture

### Design Patterns

1. **Modular Design**: Each algorithm is a separate function
2. **Separation of Concerns**: 
   - Data structures (Process.h)
   - Algorithms (Scheduler.cpp)
   - Utilities (Utils.cpp)
   - Main logic (CPU-Scheduling-Simulator.cpp)

### Data Flow

```
User Input → Process Creation → Algorithm Selection → 
Scheduling Simulation → Results Calculation → Output Display
```

### Key Design Decisions

1. **Process Structure**: All process data in one struct for simplicity
2. **Pointer Usage**: Using pointers in priority queues to avoid copying
3. **Sorting**: Processes sorted by arrival time before scheduling
4. **Time Tracking**: Discrete integer time units
5. **Result Storage**: Results stored directly in Process struct

## Build System

- **IDE**: Visual Studio 2019+
- **Project Type**: C++ Console Application
- **C++ Standard**: C++11 or later
- **Build Configurations**: Debug, Release

## Dependencies

- **Standard Library Only**: No external dependencies
- **Required Headers**:
  - `<iostream>` - Input/output
  - `<vector>` - Dynamic arrays
  - `<queue>` - Queue data structures
  - `<algorithm>` - Sorting and algorithms
  - `<climits>` - Integer limits

## Extension Points

The project is designed to be easily extensible:

1. **New Algorithms**: Add function to `Scheduler.h` and implement in `Scheduler.cpp`
2. **New Metrics**: Extend `Process` struct and update calculation logic
3. **New Output Formats**: Extend `printResults()` or create new output functions
4. **Input Methods**: Modify `main()` to support file input, GUI, etc.

## Code Organization Principles

- **Single Responsibility**: Each function does one thing
- **DRY (Don't Repeat Yourself)**: Common logic extracted to utilities
- **Clear Naming**: Functions and variables have descriptive names
- **Documentation**: Doxygen-style comments for all functions
- **Error Handling**: Input validation at entry points

