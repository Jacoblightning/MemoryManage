#include <stdio.h>
#include <string.h>
#include <MemoryManage/MemoryManage.h>

#include <unistd.h>

int main() {
    volatile char modme[] = "Hello, World";
    const process_t self = openProcess(getpid());
    if (fillMemoryWithByteByLength(self, (uint64_t)modme, 12, 'A')==-1) {
        perror(NULL);
        return 1;
    }
#pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"
    if (strcmp(modme, "AAAAAAAAAAAA") != 0) {
#pragma GCC diagnostic pop
        return 1;
    }
    return 0;
}
