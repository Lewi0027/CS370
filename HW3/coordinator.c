#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include "coordinator.h"
#include <string.h>

void coordinator(int divisor, int div0, int div1, int div2, int div3) {
    int dividendStrings[] = {div0, div1, div2, div3};
    char dividendStr[20];
    char divisorStr[20];
    
    //function to turn divisor into char string and then flip it to the correct order
    createString(divisor, divisorStr);
    reverseString(divisorStr);

    int pids[4];
    int sharedMemoryIds[4];
    int fd[4][2];
    
    for (int j = 0; j < 4; j++) {
        //function to turn dividend into char string and then flip it to the correct order
        createString(dividendStrings[j], dividendStr);
        reverseString(dividendStr);

        //create a pipe for each Checker instance
        pipe(fd[j]);

        //create a fork for each iteration through the loop
        pid_t pid = fork();        

        //parent write to pipe
        if (pid > 0 ) {
            pids[j] = pid;
            close(fd[j][0]);
            printf("Coordinator: forked process with ID %d.\n", pids[j]);
            fflush(stdout);

            //Create a unique shared memory segment for each Checker instance to store results
            int sharedMemoryId = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
            sharedMemoryIds[j] = sharedMemoryId;
            
            //write to pipe
            write(fd[j][1], &sharedMemoryId, sizeof(sharedMemoryId));
            
            //text output
            int *sharedMemoryPointer = (int*)shmat(sharedMemoryId, NULL, 0);
            printf("Coordinator: wrote shm ID %d to pipe (%ld bytes)\n", sharedMemoryId, sizeof(*sharedMemoryPointer));
            fflush(stdout);
            
            close(fd[j][1]);
        }
        //child
        if (pid == 0) {
            //close write-pipe
            close(fd[j][1]);

            //create buffer to pass to Child.c
            char buffer[20];
            sprintf(buffer, "%d", fd[j][0]);

            //run Child.c and replace executable image
            execlp("./checker", "checker", divisorStr, dividendStr, buffer, NULL);
        }
    }

    for (int k = 0; k < 4; k++) {
        //wait for child process to finish
        int status;
        printf("Coordinator: waiting on child process ID %d...\n", pids[k]);
        fflush(stdout);
        waitpid(pids[k], &status, 0);
        WIFEXITED(status);
        
        //determine if child returned 0 or 1
        int *sharedMemoryPointer = (int*)shmat(sharedMemoryIds[k], NULL, 0);
        if (*sharedMemoryPointer == 1) {
            printf("Coordinator: result 1 (divisible) read from shared memory.\n");
            fflush(stdout);
        }
        else {
            printf("Coordinator: result 0 (not divisible) read from shared memory.\n");
            fflush(stdout);
        }
        
        //destroy shared memory segment
        shmctl(*sharedMemoryPointer, IPC_RMID, NULL);

    }

    printf("Coordinator: exiting.\n");
}

// Helper function to turn int into a char array. In wrong order though.
void createString(int divisor, char* divStr) {
    int i = 0;
    int tempDiv = divisor;
    
    while (tempDiv != 0) {
        divStr[i] = (tempDiv % 10) + 48;
        tempDiv /= 10;
        i++;
    }
    divStr[i] = '\0';
}

// Helper function to flip around the order of character array strings.
// double-sided approach
void reverseString(char *str) {
    int length = strlen(str);
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

//main function. Just checks for correct number of arguments and passes them to coordinator.
int main(int argc, char **argv) {
    if (argc != 6)
    {
        printf("Incorrect number of arguments.\n");
        return -1;
    }

    int divisor = atoi(argv[1]);
    int div1 = atoi(argv[2]);
    int div2 = atoi(argv[3]);
    int div3 = atoi(argv[4]);
    int div4 = atoi(argv[5]);

    coordinator(divisor, div1, div2, div3, div4);

    return 0;
}