# The APIdocs for all the structs.
## struct Device
### Implementation:
```c++
struct Device {
    unsigned char major;
    unsigned char minor;
};
```
### Comments:
A struct for holding a deviceID
## struct Map
### Implementation:
```c++
struct Map {
    unsigned long long start;
    unsigned long long end;
    uint64_t offset;
    uint64_t inodeID;
    char* mappedPath;
    int permissions;
    struct Device* deviceID;
};
```
### Comments:
A struct used for the memory map of a process.
## struct ProcessMaps
### Implementation:
```c++
struct ProcessMaps {
    struct Map** maps;
    size_t mapCount;
};
```
### Comments:
A struct for holding an array of [Maps](structs.md#struct-map)