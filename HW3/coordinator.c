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
    
    for (int j = 0; j < 4; j++) {
        //function to turn dividend into char string and then flip it to the correct order
        createString(dividendStrings[j], dividendStr);
        reverseString(dividendStr);

        //Create a unique shared memory segment for each Checker instance to store results
        int sharedMemoryId = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666); //Create shared memory ID

        //create a pipe for each Checker instance
        int fd[2];
        pipe(fd);

        //create a fork for each iteration through the loop
        pid_t pid = fork();

        if (pid == 0) { //check if daughter
            printf("Coordinator: forked process with ID %d.\n", getpid());
            fflush(stdout);
            printf("Coordinator: waiting for process [%d].\n", getpid());
            fflush(stdout);
            execlp("./checker", "checker", divisorStr, dividendStr, NULL);
        }
        if (pid > 0) { //check if parent and wait for daughter to finish completely.
            int status;
            wait(&status);
            int result = WEXITSTATUS(status);

            //cannot access getpid() for daughter so had to add j+1 to keep correct pid value...
            printf("Coordinator: child process %d returned %d.\n", getpid()+j+1, result);
            fflush(stdout);
        }
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