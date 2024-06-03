#include <stdio.h>
#include <unistd.h>

int main () {
    sleep(3);
    printf("child!");
    return 42;
}