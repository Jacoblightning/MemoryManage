add_executable(MemoryManageStaticTester testSame.c)
add_executable(MemoryManageDynamicTester testSame.c)

target_link_libraries(MemoryManageStaticTester MemoryManageStatic)
target_link_libraries(MemoryManageDynamicTester MemoryManageShared)


add_executable(MemoryManageOtherStaticTester testOther.c)
add_executable(MemoryManageOtherStaticTested testOtherTarget.c)
add_executable(MemoryManageOtherDynamicTester testOther.c)
add_executable(MemoryManageOtherDynamicTested testOtherTarget.c)

target_link_libraries(MemoryManageOtherStaticTester MemoryManageStatic)
target_link_libraries(MemoryManageOtherDynamicTester MemoryManageShared)



add_test(NAME TestSelfStatic COMMAND $<TARGET_FILE_NAME:MemoryManageStaticTester>)
add_test(NAME TestSelfDynamic COMMAND $<TARGET_FILE_NAME:MemoryManageDynamicTester>)

add_test(
        NAME TestOtherStatic COMMAND $<TARGET_FILE_NAME:MemoryManageOtherStaticTester>
        $<TARGET_FILE_DIR:MemoryManageOtherStaticTested>/$<TARGET_FILE_NAME:MemoryManageOtherStaticTested>
)

add_test(
        NAME TestOtherDynamic COMMAND $<TARGET_FILE_NAME:MemoryManageOtherDynamicTester>
        $<TARGET_FILE_DIR:MemoryManageOtherDynamicTested>/$<TARGET_FILE_NAME:MemoryManageOtherDynamicTested>
)