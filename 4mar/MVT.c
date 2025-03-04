#include <stdio.h>
#include <stdlib.h>

struct Process {
    int id, size, allocatedPartition;
};

struct Partition {
    int id, size;
    int isFree;
};

void MVT(int memSize, int numProcesses, int processSizes[]) {
    struct Partition memory[100];
    int partitionCount = 1;
    
    memory[0].id = 1;
    memory[0].size = memSize;
    memory[0].isFree = 1;

    printf("\nMVT Allocation (Dynamic Partitioning):\n");

    for (int i = 0; i < numProcesses; i++) {
        int allocatedFlag = 0;
        for (int j = 0; j < partitionCount; j++) {
            if (memory[j].isFree && memory[j].size >= processSizes[i]) {
                int remaining = memory[j].size - processSizes[i];
                memory[j].isFree = 0;
                printf("Process %d (Size %d) → Partition %d\n", i + 1, processSizes[i], memory[j].id);

                if (remaining > 0) { 
                    memory[partitionCount].id = partitionCount + 1;
                    memory[partitionCount].size = remaining;
                    memory[partitionCount].isFree = 1;
                    partitionCount++;
                }

                allocatedFlag = 1;
                break;
            }
        }
        if (!allocatedFlag) {
            printf("Process %d (Size %d) Not Allocated\n", i + 1, processSizes[i]);
        }
    }
}

int main() {
    int memSize, partSize, numProcesses;
    printf("Enter Total Memory Size: ");
    scanf("%d", &memSize);

    printf("Enter Number of Processes: ");
    scanf("%d", &numProcesses);

    int processSizes[numProcesses];

    printf("Enter Process Sizes:\n");
    for (int i = 0; i < numProcesses; i++) {
        scanf("%d", &processSizes[i]);
    }
    MVT(memSize, numProcesses, processSizes);

    return 0;
}
