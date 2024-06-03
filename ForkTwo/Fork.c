#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Error handling
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process PID: %d\n", getpid());
    } else {
        // Parent process
        printf("Parent process PID: %d\n", getpid());
    }

    return 0;
}