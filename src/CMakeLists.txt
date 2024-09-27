
set(SOURCES ${PROJECT_SOURCE_DIR}/src/MemoryManage/MemoryManage.c)
set(U1 "")
set(U2 "")

if (BUILD_STATIC_LIBS)
    set(U1 "MemoryManageStatic")
    add_library(MemoryManageStatic STATIC ${SOURCES})
    set_target_properties(MemoryManageStatic PROPERTIES PUBLIC_HEADER ${PROJECT_SOURCE_DIR}/include/MemoryManage/MemoryManage.h)

    target_include_directories(MemoryManageStatic PUBLIC
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
    )
endif ()
if (BUILD_SHARED_LIBS)
    set(U2 "MemoryManageShared")
    add_library(MemoryManageShared SHARED ${SOURCES})

    set_target_properties(MemoryManageShared PROPERTIES PUBLIC_HEADER ${PROJECT_SOURCE_DIR}/include/MemoryManage/MemoryManage.h)


    target_include_directories(MemoryManageShared PUBLIC
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
    )
endif ()

include(GNUInstallDirs)

install(
        TARGETS ${U1} ${U2}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)