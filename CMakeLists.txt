cmake_minimum_required(VERSION 3.29)
project(MemoryManage C)

set(CMAKE_C_STANDARD 17)

message("Building from ${CMAKE_CURRENT_SOURCE_DIR}")

include_directories(include)
add_subdirectory(src)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    # We're in the root, define additional targets for developers.
    option(MemoryManage_BUILD_TESTS "whether or not tests should be built" ON)

    if(MemoryManage_BUILD_TESTS)
        enable_testing()
        add_subdirectory(test)
    endif()
endif()
