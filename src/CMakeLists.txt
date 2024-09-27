

add_library(MemoryManageStatic STATIC MemoryManage/MemoryManage.c
        ../include/MemoryManage/MemoryManage.h)
add_library(MemoryManageShared SHARED MemoryManage/MemoryManage.c
        ../include/MemoryManage/MemoryManage.h)

set_target_properties(MemoryManageStatic PROPERTIES PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include/MemoryManage.h)
set_target_properties(MemoryManageShared PROPERTIES PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include/MemoryManage.h)

include(GNUInstallDirs)

install(
        TARGETS MemoryManageShared MemoryManageStatic
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)