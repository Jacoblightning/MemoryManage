#include <MemoryManage/MemoryManage.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    int secret = 8675309;
    const int needle = 8675309;
    const process_t mypid = openProcess(getpid());
    const void* result = (void*)searchForMemory(
        mypid,
        &needle,
        sizeof needle,
        (uint64_t)((void*)&secret-2),
        (uint64_t)((void*)&secret+sizeof secret+2)
        );
    if (result == &secret) {
        return 0;
    }
    return 1;

}
