#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/wait.h>

int main () {

    pid_t pid = fork();

    if (pid == -1) {
        printf("Fork failed.\n");
    }
    if (pid == 0) {
        printf("Child Process beginning.\n");
        execlp("childTask", NULL);
        // sleep(2);
        printf("Child Process complete.\n");
    }
    else {
        printf("Parent Process beginning.\n");
        int status;
        wait(&status);
        int result = WEXITSTATUS(status);
        printf("Child returned: %d.\n", result);
        printf("Parent Process complete.\n");
    }

    return 0;
}