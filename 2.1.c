#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }

    const char *text = "Hello, this is a test file.\n";
    write(fd, text, sizeof(char)*27);
    close(fd); // Close the file

    printf("File created and text written successfully.\n");
    return 0;
}