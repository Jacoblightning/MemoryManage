#pragma once

// Enable GNU Extensions
#define _GNU_SOURCE
#include <sys/uio.h>
#include <stdint.h>

typedef pid_t process_t;

// TODO: Maybe rework this system in future
struct Device {
    unsigned char major;
    unsigned char minor;
};

struct Map {
    uint64_t start;
    uint64_t end;
    uint64_t offset;
    uint64_t inodeID;
    char* mappedPath;
    int permissions;
    struct Device* deviceID;
};

struct ProcessMaps {
    struct Map** maps;
    size_t mapCount;
};

enum PermissionFlags {
    None     = 0,
    Read     = (1 << 0),
    Write    = (1 << 1),
    Execute  = (1 << 2),
    Private  = (1 << 3),
    Shared   = (1 << 4)
};

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

struct ProcessMaps* getProcessMaps(const process_t process);
void freeMap(struct ProcessMaps *map);

void* searchForMemory(
    process_t process,
    const void* needle,
    uint64_t needleLength,
    uint64_t startAddress,
    uint64_t endAddress
    );