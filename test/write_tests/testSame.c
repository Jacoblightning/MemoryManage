#include <MemoryManage/MemoryManage.h>

#include <unistd.h>
#include <stdio.h>

int main() {
    volatile int test = 0;
    const process_t self = openProcess(getpid());
    int buffer = 8;
    if (writeMemory(self, (uint64_t)&test, &buffer, sizeof buffer) == -1) {
        perror(NULL);
        return 1;
    }
    if (test != buffer) {
        return 1;
    }
    return 0;
}