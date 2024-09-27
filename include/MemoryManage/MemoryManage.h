#pragma once

// Enable GNU Extensions
#define _GNU_SOURCE
#include <sys/uio.h>
#include <stdint.h>

typedef pid_t process_t;

process_t openProcess(pid_t pid);


ssize_t readMemoryByLength(
    process_t process,
    uint64_t startAddress,
    uint64_t lengthToRead,
    void* buffer
    );

ssize_t readMemoryByStartAndEnd(
    process_t process,
    uint64_t startAddress,
    uint64_t endAddress,
    void* buffer
    );

ssize_t writeMemory(
    process_t process,
    uint64_t startAddress,
    void* buffer,
    uint64_t bufferLength
    );

ssize_t fillMemoryWithByteByLength(
    process_t process,
    uint64_t startAddress,
    uint64_t lengthToWrite,
    unsigned char byteToFill
    );

ssize_t fillMemoryWithByteByStartAndEnd(
    process_t process,
    uint64_t startAddress,
    uint64_t endAddress,
    unsigned char byteToFill
    );