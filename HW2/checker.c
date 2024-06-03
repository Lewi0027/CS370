#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

// Return 1 if divisor%dividend == 0
// Return 0 if divisor%dividend != 0
int main(int argc, char *argv[]) { //divisor = argOne, dividend = argTwo

    int divisor = atoi(argv[1]);
    int dividend = atoi(argv[2]);

    // printf("Checker! divisor = %d, dividend = %d.\n", divisor, dividend);
    printf("Checker process [%d]: Starting.\n", getpid());
    if (dividend % divisor == 0) {
        printf("Checker process [%d]: %d *IS* divisible by %d.\n", getpid(), dividend, divisor);
        printf("Checker process [%d]: Returning 1.\n", getpid());
        return 1;
    }
    else {
        printf("Checker process [%d]: %d *IS NOT* divisible by %d.\n", getpid(), dividend, divisor);
        printf("Checker process [%d]: Returning 0.\n", getpid());
        return 0;
    }
}