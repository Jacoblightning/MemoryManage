---
tags:
  - API
---
# The APIdocs for all the enums.
## PermissionFlags
### Implementation:
```c++
enum PermissionFlags {
    None     = 0,
    Read     = (1 << 0),
    Write    = (1 << 1),
    Execute  = (1 << 2),
    Private  = (1 << 3),
    Shared   = (1 << 4)
};
```
### Comments:
The flags for permissions on [mapped memory regions](https://wikiless.funami.tech/wiki/Virtual_memory?lang=en#Thrashing)
## 