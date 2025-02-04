#include <stdio.h>

struct Process {
    int pid, arrival_time, burst_time, priority, waiting_time, turnaround_time;
};

void FCFS(struct Process proc[], int n) {
    proc[0].waiting_time = 0;
    for (int i = 1; i < n; i++) {
        proc[i].waiting_time = proc[i - 1].waiting_time + proc[i - 1].burst_time;
    }
}

void SJF(struct Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].burst_time > proc[j + 1].burst_time) {
                struct Process temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }
    FCFS(proc, n);
}

void RR(struct Process proc[], int n, int quantum) {
    int remaining_bt[n];
    int t = 0, done;
    for (int i = 0; i < n; i++) remaining_bt[i] = proc[i].burst_time;
    do {
        done = 1;
        for (int i = 0; i < n; i++) {
            if (remaining_bt[i] > 0) {
                done = 0;
                if (remaining_bt[i] > quantum) {
                    t += quantum;
                    remaining_bt[i] -= quantum;
                } else {
                    t += remaining_bt[i];
                    proc[i].waiting_time = t - proc[i].burst_time;
                    remaining_bt[i] = 0;
                }
            }
        }
    } while (!done);
}

void Priority(struct Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].priority > proc[j + 1].priority) {
                struct Process temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }
    FCFS(proc, n);
}

void TT(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time;
    }
}

void printProcesses(struct Process proc[], int n) {
    printf("PID\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", proc[i].pid, proc[i].arrival_time, proc[i].burst_time, proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process proc[n];
    
    for (int i = 0; i < n; i++) {
        printf("Enter Process %d (AT BT Priority): ", i + 1);
        scanf("%d %d %d", &proc[i].arrival_time, &proc[i].burst_time, &proc[i].priority);
        proc[i].pid = i + 1;
    }
    
    printf("\nFCFS Scheduling:\n");
    FCFS(proc, n);
    TT(proc, n);
    printProcesses(proc, n);
    
    printf("\nSJF Scheduling:\n");
    SJF(proc, n);
    TT(proc, n);
    printProcesses(proc, n);
    
    printf("\nEnter Time Quantum for RR: ");
    scanf("%d", &quantum);
    printf("\nRound Robin Scheduling:\n");
    RR(proc, n, quantum);
    TT(proc, n);
    printProcesses(proc, n);
    
    printf("\nPriority Scheduling:\n");
    Priority(proc, n);
    TT(proc, n);
    printProcesses(proc, n);
    
    return 0;
}

