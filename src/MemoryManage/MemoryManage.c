// Enable GNU Extensions
#define _GNU_SOURCE // NOLINT(*-reserved-identifier)
#include <sys/uio.h>
#include <stdint.h>
#include <signal.h>
#include <stdlib.h>

typedef pid_t process_t;

process_t openProcess(const pid_t pid) {
    // Checking for the existence of a process.
    // Killing with 0 just checks if it exists.
    const int result = kill(pid, 0);
    // If the kill was successful.
    if (result == 0) {
        // Return the pid.
        return pid;
    }
    // Error: return -1.
    return -1;
}

ssize_t readMemoryByLength(
    const process_t process,
    const uint64_t startAddress,
    const uint64_t lengthToRead,
    void* buffer
    ){
    // Make a remote iovec structure.
    const struct iovec remoteMemoryRegion[1] = {{.iov_base = (void*)startAddress,.iov_len = lengthToRead}};

    // Make a local iovec structure
    const struct iovec localMemoryRegion[1] = {{.iov_base = buffer,.iov_len = lengthToRead}};


    const ssize_t result = process_vm_readv(
        process,
        localMemoryRegion,
        1,
        remoteMemoryRegion,
        1,
        0
        );

    if (result < 1) {
        return result;
    }
    return 0;
}