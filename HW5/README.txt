# Process Scheduling Program

This program implements three scheduling algorithms to calculate the following metrics:
- **Average Waiting Time**
- **Average Turnaround Time**
- **Throughput**

### Scheduling Algorithms:
1. **FCFS (First Come First Serve)**
2. **SJFP (Shortest Job First Preemptive)**
3. **Priority Scheduling (Preemptive)**

## Input Format
The input is a CSV file containing:
- **Process ID**, **Arrival Time**, **Burst Duration**, **Priority**

## How to Run
1. Compile the program with the Makefile.

## Output
The program will output the calculated metrics for each scheduling algorithm:
- Average Waiting Time
- Average Turnaround Time
- Throughput

## Code Structure
- **Process Struct:** Stores process data (ID, Arrival Time, Burst, etc.).
- **Algorithms:** Implements the scheduling algorithms.
- **Helper Functions:** Manages input, output, and calculations.
