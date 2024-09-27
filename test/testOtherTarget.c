#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

void main() {
    int secret = 8675309;
    printf("%d %lu\n", getpid(), (uint64_t)&secret);
    fflush(stdout);
    while (true) {

    }
}