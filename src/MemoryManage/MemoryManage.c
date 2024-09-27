#include <MemoryManage/MemoryManage.h>

#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


process_t openProcess(const pid_t pid) {
    // Checking for the existence of a process.
    // Killing with 0 just checks if it exists.
    const int result = kill(pid, 0);
    // If the "kill" was successful.
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

    if (result != -1 && result != lengthToRead) {
        errno = EIO;
        return -1;
    }
    return result;
}

ssize_t readMemoryByStartAndEnd(
    const process_t process,
    const uint64_t startAddress,
    const uint64_t endAddress,
    void* buffer
    ){

    //TODO: Maybe make this a macro in future?
    return readMemoryByLength(
        process,
        startAddress,
        endAddress - startAddress,
        buffer
        );
}

ssize_t writeMemory(
    const process_t process,
    const uint64_t startAddress,
    void* buffer,
    const uint64_t bufferLength
    ) {

    // Make a remote iovec structure.
    const struct iovec remoteMemoryRegion[1] = {{.iov_base = (void*)startAddress,.iov_len = bufferLength}};

    // Make a local iovec structure
    const struct iovec localMemoryRegion[1] = {{.iov_base = buffer,.iov_len = bufferLength}};

    const ssize_t result = process_vm_writev(
        process,
        localMemoryRegion,
        1,
        remoteMemoryRegion,
        1,
        0
        );

    if (result != -1 && result != bufferLength) {
        errno = EIO;
        return -1;
    }
    return result;

}

ssize_t fillMemoryWithByteByLength(
    const process_t process,
    const uint64_t startAddress,
    const uint64_t lengthToWrite,
    const unsigned char byteToFill
    ) {

    unsigned char* buffer = malloc(lengthToWrite);

    memset(buffer, byteToFill, lengthToWrite);

    // Make a remote iovec structure.
    const struct iovec remoteMemoryRegion[1] = {{.iov_base = (void*)startAddress,.iov_len = lengthToWrite}};

    // Make a local iovec structure
    const struct iovec localMemoryRegion[1] = {{.iov_base = buffer,.iov_len = lengthToWrite}};

    const ssize_t result = process_vm_writev(
        process,
        localMemoryRegion,
        1,
        remoteMemoryRegion,
        1,
        0
        );

    free(buffer);

    if (result != -1 && result != lengthToWrite) {
        errno = EIO;
        return -1;
    }
    return result;
}

ssize_t fillMemoryWithByteByStartAndEnd(
    const process_t process,
    const uint64_t startAddress,
    const uint64_t endAddress,
    const unsigned char byteToFill
    ) {

    //TODO: Maybe make this a macro in future?
    return fillMemoryWithByteByLength(
        process,
        startAddress,
        endAddress - startAddress,
        byteToFill
        );
}