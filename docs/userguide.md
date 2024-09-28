---
hide:
  - toc
tags:
  - UserDocs
---
# User Guide

### All of these examples require the inclusion of the `<MemoryManage/MemoryManage.h>` header.
### Almost all functions here pass on the errors from the internal system call.
### You can read more about all of these functions in the [APIdocs](apidocs.md)

### Addresses should be a uint64_t. You can safely cast a pointer to this.

## Open a process
To open a process, you will need its PID (Process ID), once you have this, you can get a process_t to it in the following way.

`process_t myprocess = openProcess(<pid>);`
## Read Memory from a Process
### You can either read memory by using a length or by a start and end address.
#### Length:
`readMemoryByLength(<process>, <startaddress>, <length to read>, <output buffer>)`
#### Start and End
`readMemoryByStartAndEnd(<process>, <startaddress>, <length to read>, <output buffer>)`
### Write Memory to a Process
`writeMemory(<process>, <startaddress>, <output buffer>, <buffer length>)`

