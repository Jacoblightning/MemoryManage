#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

void main() {
    volatile int secret = 0;
    printf("%d %lu\n", getpid(), (uint64_t)&secret);
    fflush(stdout);
    while (true) {
        if (secret == 8675309) {
            printf("1\n");
            fflush(stdout);
            return;
        }
    }
}