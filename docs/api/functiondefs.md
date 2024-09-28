---
tags:
  - API
---
# These are the definitions of all the functions in this project.

<!-- We use c++ language here because annoyingly my IDE (CLion) does not consider C a language. -->

## openProcess
```c++
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
```
## readMemoryByLength
```c++
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
```
## readMemoryByStartAndEnd
```c++
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
```
## writeMemory
```c++
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
```
## fillMemoryWithByteByLength
```c++
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
```
## fillMemoryWithByteByStartAndEnd
```c++
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
```
## searchForMemory
```c++
uint64_t searchForMemory(
    const process_t process,
    const void* needle,
    const uint64_t needleLength,
    const uint64_t startAddress,
    const uint64_t endAddress
    ) {
    if (startAddress == 0 && endAddress == 0) {
        // ReSharper disable once CppDFAMemoryLeak
        // Once again, there is no memory leak here.
        struct ProcessMaps *maps = getProcessMaps(process);

        if (maps == NULL) {
            fprintf(stderr, "Failed to get process maps\n");
            return 0; // Handle the error appropriately
        }

        printf("Number of maps: %lu\n", maps->mapCount);

        freeMap(maps);
        return 0;
    }
    const uint64_t size = endAddress - startAddress;
    void* buffer = malloc(size);
    if (buffer == NULL) {
        return 0;
    }
    if (readMemoryByLength(process, startAddress, size, buffer)==-1) {
        free(buffer);
        return 0;
    }
    const void* result = memmem(buffer, size, needle, needleLength);
    if(result == NULL) {
        free(buffer);
        return 0;
    }
    // Some fun pointer arithmetic
    // ReSharper disable once CppDFANullDereference
    // No, actually this pointer cannot be null.
    const uint64_t toret = startAddress + ((uint64_t)result - (uint64_t)buffer);
    free(buffer);
    return toret;
}
```
## getProcessMaps
```c++
struct ProcessMaps* getProcessMaps(const process_t process) {
    // ReSharper disable once CppDFAMemoryLeak
    // Reasonably sure that there is no memory leak here.
    struct ProcessMaps *maps = malloc(sizeof(struct ProcessMaps));
    if (maps == NULL) {
        return NULL; // Early return if allocation fails
    }

    char *procPath = malloc(19);
    if (procPath == NULL) {
        free(maps); // Free previously allocated memory
        return NULL; // Early return if allocation fails
    }

    sprintf(procPath, "/proc/%d/maps", process);
    FILE* file = fopen(procPath, "r");
    free(procPath); // Free procPath after using it
    if (file == NULL) {
        free(maps); // Free previously allocated memory
        return NULL; // Early return if fopen fails
    }

    int lines = 0;
    while (!feof(file)) {
        const int ch = fgetc(file);
        if (ch == '\n') {
            lines++;
        }
    }
    rewind(file);

    // Allocate memory for maps->maps
    maps->maps = calloc(lines, sizeof(struct Map));
    if (maps->maps == NULL) {
        free(maps); // Free previously allocated memory
        fclose(file); // Close the file
        return NULL; // Early return if allocation fails
    }

    maps->mapCount = lines;
    int line = 0;
    char buffer[2048];
    while (fgets(buffer, sizeof(buffer), file)) {
        struct Map *map = malloc(sizeof(struct Map));
        struct Device *device = malloc(sizeof(struct Device));

        if (map == NULL || device == NULL) {
            // Free previously allocated maps
            for (int i = 0; i < line; i++) {
                free(maps->maps[i]->deviceID);
                free(maps->maps[i]->mappedPath);
                free(maps->maps[i]);
            }
            free(maps->maps);
            free(maps);
            fclose(file);
            return NULL; // Early return if allocation fails
        }

        map->deviceID = device;

        // Initialize permissions and read from buffer
        map->permissions = 0;
        char perms[5];
        sscanf(buffer, "%llx-%llx %s %lx %hhx:%hhx %ld %ms", // NOLINT(*-err34-c)
               &map->start,
               &map->end,
               perms,
               &map->offset,
               &map->deviceID->major,
               &map->deviceID->minor,
               &map->inodeID,
               &map->mappedPath);

        // Set permissions based on the read string
        if (perms[0] == 'r') map->permissions |= Read;
        if (perms[1] == 'w') map->permissions |= Write;
        if (perms[2] == 'x') map->permissions |= Execute;
        if (perms[3] == 'p') map->permissions |= Private;
        if (perms[3] == 's') map->permissions |= Shared;

        maps->maps[line] = map;
        line++;
    }

    fclose(file); // Close the file after reading
    return maps; // Return the allocated ProcessMaps structure
}
```
## freeMap
```c++
void freeMap(struct ProcessMaps *map) {
    if (map == NULL) return; // Check for NULL pointer

    for (int i = 0; i < map->mapCount; i++) {
        if (map->maps[i] != NULL) { // Check if the map entry is not NULL
            free(map->maps[i]->deviceID); // Free the deviceID
            free(map->maps[i]->mappedPath); // Free the mappedPath
            free(map->maps[i]); // Free the Map structure itself
        }
    }
    free(map->maps); // Free the array of Map structures
    free(map); // Free the ProcessMaps structure
}
```