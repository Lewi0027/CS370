#include <stdio.h>

int main (int argc, char **argv) {
    for (int i = 0; i <= argc+1; i++) {
        printf("Hello world! %s\n", argv[1]);
    }
    return 0;

}