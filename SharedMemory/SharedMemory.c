#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

int main () {

    int sharedMemoryId = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666); //Create shared memory ID
    printf("sharedMemoryId: %d\n", sharedMemoryId);

    int fd[2];
    pipe(fd);

    pid_t pid = fork();

    if (pid < 0 ) printf("Fork failed!\n");
    else if (pid > 0) {
        printf("Parent!\n");
        close(fd[0]);
        write(fd[1], &sharedMemoryId, sizeof(sharedMemoryId));
        close(fd[1]);
    }
    else {
        printf("Child!\n");
        close(fd[1]);
        char buffer[8];
        sprintf(buffer, "%d", fd[0]);
        execlp("child", buffer, NULL);
    }

    // Wait for the child to finish
    if (pid > 0) {
        int status;
        wait(&status);
    }

    // Attach to the shared memory segment
    int *sharedMemoryPointer = (int*)shmat(sharedMemoryId, NULL, 0);

    // Read from the shared memory segment
    printf("shared Memory content: %d\n", *sharedMemoryPointer);

    // Destroy shared memory segment
    shmctl(*sharedMemoryPointer, IPC_RMID, NULL);

    return 0;
}