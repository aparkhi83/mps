#include <stdio.h>
#include <stdlib.h>

struct Process {
    int id, size, allocatedPartition;
};

struct Partition {
    int id, size;
    int isFree;
};

void MFT(int memSize, int partSize, int numProcesses, int processSizes[]) {
    int numPartitions = memSize / partSize;
    struct Partition partitions[numPartitions];
    struct Process allocated[numProcesses];

    for (int i = 0; i < numPartitions; i++) {
        partitions[i].id = i + 1;
        partitions[i].size = partSize;
        partitions[i].isFree = 1;
    }

    printf("\nMFT Allocation (Fixed Partition Size: %d):\n", partSize);
    
    for (int i = 0; i < numProcesses; i++) {
        int allocatedFlag = 0;
        for (int j = 0; j < numPartitions; j++) {
            if (partitions[j].isFree && processSizes[i] <= partSize) {
                partitions[j].isFree = 0;
                allocated[i].id = i + 1;
                allocated[i].size = processSizes[i];
                allocated[i].allocatedPartition = j + 1;
                allocatedFlag = 1;
                break;
            }
        }
        if (!allocatedFlag) {
            printf("Process %d (Size %d) Not Allocated\n", i + 1, processSizes[i]);
        } else {
            printf("Process %d (Size %d) → Partition %d\n", allocated[i].id, allocated[i].size, allocated[i].allocatedPartition);
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
    MFT(memSize, partSize, numProcesses, processSizes);

    return 0;
}
