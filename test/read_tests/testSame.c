#include <MemoryManage/MemoryManage.h>

#include <unistd.h>
#include <stdio.h>

int main() {
    int test = 8;
    const process_t self = openProcess(getpid());
    int buffer = 0;
    if (readMemoryByLength(self, (uint64_t)&test, sizeof test, &buffer)==-1) {
        perror(NULL);
        return 1;
    }
    if (test != buffer) {
        return 1;
    }
    return 0;
}