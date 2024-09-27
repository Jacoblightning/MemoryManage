
set(SOURCES ${PROJECT_SOURCE_DIR}/src/MemoryManage/MemoryManage.c)

add_library(MemoryManageStatic STATIC ${SOURCES})
add_library(MemoryManageShared SHARED ${SOURCES})

set_target_properties(MemoryManageStatic PROPERTIES PUBLIC_HEADER ${PROJECT_SOURCE_DIR}/include/MemoryManage/MemoryManage.h)
set_target_properties(MemoryManageShared PROPERTIES PUBLIC_HEADER ${PROJECT_SOURCE_DIR}/include/MemoryManage/MemoryManage.h)

target_include_directories(MemoryManageStatic PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_include_directories(MemoryManageShared PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

include(GNUInstallDirs)

install(
        TARGETS MemoryManageShared MemoryManageStatic
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)