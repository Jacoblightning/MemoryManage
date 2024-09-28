---
tags:
  - UserDocs
---
# Very Quick Start
### If you have not yet, head to [Installation](installing.md) to install MemoryManage.
### The following examples are written in C. It is assumed that you have a basic understanding.

## Open process:
`process_t openProcess(<pid>)`
## Read Memory
`readMemoryByLength(<process>, , <startaddress>, <length to read>, <output buffer>)`
## Write Memory
`writeMemory(<process>, <startaddress>, <buffer>, <buffer length>)`

## For more info, see the [User Guide](userguide.md)