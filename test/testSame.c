#include "../include/MemoryManage/MemoryManage.h"

#include <unistd.h>
#include <stdio.h>

int main() {
    int test = 8;
    process_t self = openProcess(getpid());
    int buffer = 0;
    readMemoryByLength(self, (uint64_t)&test, sizeof test, &buffer);
    if (test != buffer) {
        printf("Test testSame failed: %d\n", test);
        return 1;
    }
    return 0;
}