cmake_minimum_required(VERSION 3.29)
project(MemoryManage C)

include(CTest)

set(CMAKE_C_STANDARD 17)

add_library(MemoryManageStatic STATIC MemoryManage/MemoryManage.c
        include/MemoryManage.h)
add_library(MemoryManageShared SHARED MemoryManage/MemoryManage.c
        include/MemoryManage.h)

# Tests

add_executable(MemoryManageStaticTester test/testSame.c)
add_executable(MemoryManageDynamicTester test/testSame.c)

target_link_libraries(MemoryManageStaticTester MemoryManageStatic)
target_link_libraries(MemoryManageDynamicTester MemoryManageShared)


add_executable(MemoryManageOtherStaticTester test/testOther.c)
add_executable(MemoryManageOtherStaticTested test/testOtherTarget.c)
add_executable(MemoryManageOtherDynamicTester test/testOther.c)
add_executable(MemoryManageOtherDynamicTested test/testOtherTarget.c)

target_link_libraries(MemoryManageOtherStaticTester MemoryManageStatic)
target_link_libraries(MemoryManageOtherDynamicTester MemoryManageShared)



add_test(NAME TestSelfStatic COMMAND $<TARGET_FILE_NAME:MemoryManageStaticTester>)
add_test(NAME TestSelfDynamic COMMAND $<TARGET_FILE_NAME:MemoryManageDynamicTester>)

add_test(
        NAME TestOtherStatic COMMAND $<TARGET_FILE_NAME:MemoryManageOtherStaticTester>
        $<TARGET_FILE_DIR:MemoryManageOtherStaticTested>/$<TARGET_FILE_NAME:MemoryManageOtherStaticTested>
)