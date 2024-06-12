#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// Return 1 if divisor%dividend == 0
// Return 0 if divisor%dividend != 0
int main(int argc, char *argv[]) {

    int divisor = atoi(argv[1]);
    int dividend = atoi(argv[2]);
    int fd = atoi(argv[3]);
    // int sharedMemoryId = atoi(argv[3]);

    // printf("Checker! divisor = %d, dividend = %d.\n", divisor, dividend);
    printf("Checker process [%d]: starting.\n", getpid());
    fflush(stdout);

    int sharedMemoryId;
    read(fd, &sharedMemoryId, sizeof(sharedMemoryId));
    close(fd);
    int *sharedMemoryPointer = (int *)shmat(sharedMemoryId, NULL, 0);

    printf("Checker process [%d]: read %ld bytes containing shm ID %d\n", getpid(), sizeof(*sharedMemoryPointer), sharedMemoryId);
    fflush(stdout);

    if (dividend % divisor == 0) {
        printf("Checker process [%d]: %d *IS* divisible by %d.\n", getpid(), dividend, divisor);
        printf("Checker process [%d]: wrote result (1) to shared memory.\n", getpid());
        fflush(stdout);
        *sharedMemoryPointer = 1;
    }
    else {
        printf("Checker process [%d]: %d *IS NOT* divisible by %d.\n", getpid(), dividend, divisor);
        printf("Checker process [%d]: wrote result (0) to shared memory.\n", getpid());
        fflush(stdout);
        *sharedMemoryPointer = 0;
    }

    shmdt(sharedMemoryPointer);
    return 0;
}