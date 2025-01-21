#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    void *initial_brk = sbrk(0); // Get the current end of the data segment
    printf("Initial break: %p\n", initial_brk);

    // Increase the data segment size
    size_t size = 1024; // 1 KB
    void *new_brk = initial_brk + size; // Calculate the new break address

    if (brk(new_brk) == -1) {
        perror("Failed to increase data segment");
        return 1;
    }

    new_brk = sbrk(0); // Get the new end of the data segment
    printf("New break after increasing: %p\n", new_brk);

    // Decrease the data segment size
    if (brk(initial_brk) == -1) {
        perror("Failed to decrease data segment");
        return 1;
    }

    new_brk = sbrk(0); // Get the new end of the data segment
    printf("New break after decreasing: %p\n", new_brk);

    return 0;
}
