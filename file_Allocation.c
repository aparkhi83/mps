#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100

// Structure for Sequential Allocation
struct SequentialFile {
    int start;
    int length;
};

// Structure for Indexed Allocation
struct IndexedFile {
    int indexBlock;
    int blocks[MAX_BLOCKS];
    int length;
};

// Structure for Linked Allocation
struct LinkedFile {
    int start;
    int length;
    int links[MAX_BLOCKS];
};

void display_blocks(int blocks[], int total_blocks) {
    printf("Allocated Blocks: ");
    for (int i = 0; i < total_blocks; i++) {
        if (blocks[i] == 1) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

void sequential_allocation(int blocks[], int total_blocks) {
    struct SequentialFile file;
    printf("Enter start block and length of the file: ");
    scanf("%d %d", &file.start, &file.length);
    
    if (file.start + file.length > total_blocks) {
        printf("File exceeds disk space!\n");
        return;
    }
    
    for (int i = file.start; i < file.start + file.length; i++) {
        if (blocks[i] == 1) {
            printf("Block %d is already allocated!\n", i);
            return;
        }
    }
    
    for (int i = file.start; i < file.start + file.length; i++) {
        blocks[i] = 1;
    }
    
    printf("File allocated using Sequential Allocation.\n");
    display_blocks(blocks, total_blocks);
}

void indexed_allocation(int blocks[], int total_blocks) {
    struct IndexedFile file;
    printf("Enter index block and number of blocks: ");
    scanf("%d %d", &file.indexBlock, &file.length);
    
    if (blocks[file.indexBlock] == 1) {
        printf("Index block is already allocated!\n");
        return;
    }
    
    printf("Enter %d block numbers: ", file.length);
    for (int i = 0; i < file.length; i++) {
        scanf("%d", &file.blocks[i]);
        if (blocks[file.blocks[i]] == 1) {
            printf("Block %d is already allocated!\n", file.blocks[i]);
            return;
        }
    }
    
    blocks[file.indexBlock] = 1;
    for (int i = 0; i < file.length; i++) {
        blocks[file.blocks[i]] = 1;
    }
    
    printf("File allocated using Indexed Allocation.\n");
    display_blocks(blocks, total_blocks);
}

void linked_allocation(int blocks[], int total_blocks) {
    struct LinkedFile file;
    printf("Enter start block and number of blocks: ");
    scanf("%d %d", &file.start, &file.length);
    
    if (blocks[file.start] == 1) {
        printf("Start block is already allocated!\n");
        return;
    }
    
    printf("Enter %d block numbers: ", file.length);
    for (int i = 0; i < file.length; i++) {
        scanf("%d", &file.links[i]);
        if (blocks[file.links[i]] == 1) {
            printf("Block %d is already allocated!\n", file.links[i]);
            return;
        }
    }
    
    blocks[file.start] = 1;
    for (int i = 0; i < file.length; i++) {
        blocks[file.links[i]] = 1;
    }
    
    printf("File allocated using Linked Allocation.\n");
    display_blocks(blocks, total_blocks);
}

int main() {
    int blocks[MAX_BLOCKS] = {0}; // 0 = free, 1 = allocated
    int total_blocks = MAX_BLOCKS;
    int choice;
    
    while (1) {
        printf("\nFile Allocation Methods:\n");
        printf("1. Sequential Allocation\n");
        printf("2. Indexed Allocation\n");
        printf("3. Linked Allocation\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                sequential_allocation(blocks, total_blocks);
                break;
            case 2:
                indexed_allocation(blocks, total_blocks);
                break;
            case 3:
                linked_allocation(blocks, total_blocks);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
