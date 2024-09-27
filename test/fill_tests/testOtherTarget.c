#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

void main() {
    volatile char modme[] = "Hello, World!";
    printf("%d %lu\n", getpid(), (uint64_t)&modme);
    fflush(stdout);
    while (true) {
#pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"
        if (strcmp(modme, "AAAAAAAAAAAAA") == 0) {
#pragma GCC diagnostic pop
            printf("1\n");
            fflush(stdout);
            return;
        }
    }
}
