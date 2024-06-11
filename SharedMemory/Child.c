#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char** argv) {

    // Pipe stuff (extract shared memory ID)
    // Get sharedMemoryId from parent
    int fd = atoi(argv[0]);
    int sharedMemoryId = atoi(argv[0]);

    read(fd, &sharedMemoryId, sizeof(sharedMemoryId));
    printf("sharedMemoryID from pipe: %d\n", sharedMemoryId);

    // Get a pointer to the shared memory
    int *sharedMemoryPointer = (int*)shmat(sharedMemoryId, NULL, 0);

    // Write to shared memory
    *sharedMemoryPointer = 1; //dereference

    // Detach
    shmdt(sharedMemoryPointer);

    return 0;
}