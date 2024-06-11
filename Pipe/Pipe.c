#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main () {
pid_t pid = fork();
    int fd[2];
    pipe(fd);

    pid_t pid = fork();

    if (pid < 0 ) printf("Fork failed!\n");
    else if (pid > 0) {
        printf("Parent!\n");
        close(fd[0]); //Close read-end of pipe
        int fav_number = 42; //Write this to pipe
        write(fd[1], &fav_number, sizeof(fav_number)); //Pass to the write end of the pipe
        close(fd[1]); //Close write-end of pipe
    }
    else {
        printf("Child!\n");
        char buffer[8];
        close(fd[1]);
        sprintf(buffer, "%d", fd[0]);
        execlp("child", buffer, NULL);
    }

    return 0;
}