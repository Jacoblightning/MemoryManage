---
tags:
  - API
---
# The APIdocs for all the functions
### Unlike other APIdocs, the implementations are not in this file but [here](functiondefs.md).
## openProcess
### Signature:
```c++
process_t openProcess(pid_t pid);
```
### [Implementation](functiondefs.md#openprocess)
### Comments:
Used to get a [process_t](typedefs.md#process_t) type by checking if the pid exists


## readMemoryByLength
### Signature:
```c++
ssize_t readMemoryByLength(
    process_t process,
    uint64_t startAddress,
    uint64_t lengthToRead,
    void* buffer
    );
```
### [Implementation](functiondefs.md#readmemorybylength)
### Comments:
Reads <lengthToRead\> bytes of memory starting at address <startAddress\> from the process id <process\> and stores it in <buffer\>


## readMemoryByStartAndEnd
### Signature:
```c++
ssize_t readMemoryByStartAndEnd(
    process_t process,
    uint64_t startAddress,
    uint64_t endAddress,
    void* buffer
    );
```
### [Implementation](functiondefs.md#readmemorybystartandend)
### Comments:
Reads memory starting at address <startAddress\> and ending at address <endAddress\> from the process id <process\> and stores it in <buffer\>


## writeMemory
### Signature:
```c++
ssize_t writeMemory(
    process_t process,
    uint64_t startAddress,
    void* buffer,
    uint64_t bufferLength
    );
```
### [Implementation](functiondefs.md#writememory)
### Comments:
Writes memory into process id <process\> starting at address <startAddress\> from <buffer\> of length <bufferLength\>


## fillMemoryWithByteByLength
### Signature:
```c++
ssize_t fillMemoryWithByteByLength(
    process_t process,
    uint64_t startAddress,
    uint64_t lengthToWrite,
    unsigned char byteToFill
    );
```
### [Implementation](functiondefs.md#fillmemorywithbytebylength)
### Comments:
Memset for other processes

Sets memory in process <process\> starting at address <startAddress\> going for <lengthToWrite\> bytes to <byteToFill\>


## fillMemoryWithByteByStartAndEnd
### Signature:
```c++
ssize_t fillMemoryWithByteByStartAndEnd(
    process_t process,
    uint64_t startAddress,
    uint64_t endAddress,
    unsigned char byteToFill
    );
```
### [Implementation](functiondefs.md#fillmemorywithbytebystartandend)
### Comments:
Like [fillMemoryWithByteByLength](functions.md#fillmemorywithbytebylength) but 2 clock cycles slower :)

Sets memory in process <process\> starting at address <startAddress\> going to address <endAddress\> bytes to <byteToFill\>


## searchForMemory
### Signature:
```c++
uint64_t searchForMemory(
    process_t process,
    const void* needle,
    uint64_t needleLength,
    uint64_t startAddress,
    uint64_t endAddress
    );
```
### [Implementation](functiondefs.md#searchformemory)
### Comments:
Finds needle <needle\> of length <needleLength\> in process <process\> memory starting at <startAddress\> and ending at address <endAddress\>


## getProcessMaps
### Signature:
```c++
struct ProcessMaps* getProcessMaps(const process_t process);
```
### [Implementation](functiondefs.md#getprocessmaps)
### Comments:
Gets the memory maps of process <process\> and returns a [ProcessMaps struct](structs.md#struct-processmaps)


## freeMap
### Signature:
```c++
void freeMap(struct ProcessMaps *map);
```
### [Implementation](functiondefs.md#freemap)
### Comments:
Frees [ProcessMaps](structs.md#struct-processmaps) <map\>