#pragma once

// Enable GNU Extensions
#define _GNU_SOURCE
#include <sys/uio.h>
#include <stdint.h>

typedef pid_t process_t;

process_t openProcess(pid_t pid);

ssize_t readMemoryByLength(process_t process, uint64_t startAddress, uint64_t lengthToRead, void* buffer);
