add_library(MemoryManageStatic STATIC MemoryManage/MemoryManage.c
        ../include/MemoryManage.h)
add_library(MemoryManageShared SHARED MemoryManage/MemoryManage.c
        ../include/MemoryManage.h)