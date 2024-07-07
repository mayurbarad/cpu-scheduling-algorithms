# CPU Scheduling Algorithms

## Description
This project implements various CPU scheduling algorithms in C++:

- **First Come First Serve (FCFS)**
- **Shortest Job First (SJF)**
- **Shortest Reaming Time Next (SRTN)**
- **Priority Scheduling** (Preemptive)
- **Round Robin**

CPU scheduling algorithms manage the execution of processes on a CPU. Each algorithm aims to optimize different aspects of process scheduling, such as turnaround time, waiting time, throghput and CPU utilization.

## Algorithms

### First Come First Serve (FCFS)

FCFS is the simplest CPU scheduling algorithm where processes are executed in the order they arrive. It is non-preemptive, meaning once a process starts executing, it continues until it completes.

### Shortest Job First (SJF)

SJF selects the process with the smallest burst time next. once a process starts executing, it continues until it completes its execution. Processes are sorted based on their burst time (execution time) and executed in ascending order of burst times.

### Shortest Remaning Time Next (SRTN)

SRTF is a preemptive version of SJF where the scheduler selects the process with the smallest remaining burst time to execute next.Whenever a new process arrives or the current process completes its execution, the scheduler compares the remaining burst times of all processes and selects the one with the smallest remaining time.

### Priority Scheduling

Priority Scheduling assigns priorities to processes and selects the highest priority process for execution. It can be preemptive (where a higher priority process can interrupt a lower priority one) or non-preemptive (where the CPU is allocated to a process until it voluntarily relinquishes control or terminates).

### Round Robin

Round Robin scheduling allocates CPU time to each process in turn, with each process receiving a small unit of CPU time (time quantum). If a process doesn't complete within its time quantum, it's moved to the end of the queue.This ensures fairness among processes and prevents any single process from monopolizing the CPU. It's commonly used in time-sharing systems to balance responsiveness and system utilization.


## metrics
**Burst Time**: Time required for a process to complete its execution.  

**Completion Time**: Time at which a process finishes execution. It is the actual time when a process finishes its execution. It includes not only the burst time (time spent actively using the CPU) but also any time spent waiting in the ready queue or blocked for I/O operations.  

**Turn Around Time**: Total time taken from the submission of a process to its completion.  

**Waiting Time**: Total time a process spends waiting in the ready queue.  

**Throughput**: Number of processes completed per unit of time.                             
Throughput= Number of processes completed / Total Time(completion time)

**CPU Utilization**: Percentage of time CPU is busy processing tasks.
CPU = Total CPU time / Total Time * 100%


### Compilation:
Compile the source code using a C++ compiler (e.g., g++).

### Execution:
Run the compiled executable.
Follow the prompts to enter process details such as number ofprocesses, arrival time, burst time, and priority (if applicable).

### Output:
The program computes and displays metrics such as average turnaround time, average waiting time, throughput, and CPU utilization based on the selected scheduling algorithm.

## Input Format
-Select algorithm.
- Number of processes.
- For each process:
  - Process ID.
  - Arrival Time.
  - Burst Time.
  - Priority (for Priority Scheduling).

## Output Format
- Average Turnaround Time.
- Average Waiting Time.
- Throughput.
- CPU Utilization.
