cmake_minimum_required(VERSION 3.29)
project(MemoryManage C)

set(CMAKE_C_STANDARD 17)

include(CMakeDependentOption)

if (EXISTS ${CMAKE_SOURCE_DIR}/.debugging)
    set(BUILD_TESTS ON)
endif ()

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    option(BUILD_TESTS "Whether or not tests should be built" OFF)
endif ()
cmake_dependent_option(BUILD_STATIC_LIBS "Build the static library" OFF "NOT BUILD_TESTS" ON)
cmake_dependent_option(BUILD_SHARED_LIBS "Build the shared library" ON "BUILD_STATIC_LIBS;NOT BUILD_TESTS" ON)

#cmake_dependent_option(RUN_TEMPERAMENTAL_TEST "Run test 11 which does not work on github actions for some reason." ON "BUILD_TESTS" OFF)

message("Building from ${PROJECT_SOURCE_DIR}")

include_directories(include)
add_subdirectory(src)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    if(BUILD_TESTS)
        enable_testing()
        add_subdirectory(test)
    endif()
endif()
