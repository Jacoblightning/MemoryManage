add_executable(MemoryManageStaticWriteTester testSame.c)
add_executable(MemoryManageDynamicWriteTester testSame.c)

target_link_libraries(MemoryManageStaticWriteTester MemoryManageStatic)
target_link_libraries(MemoryManageDynamicWriteTester MemoryManageShared)


add_executable(MemoryManageOtherStaticWriteTester testOther.c)
add_executable(MemoryManageOtherStaticWriteTested testOtherTarget.c)
add_executable(MemoryManageOtherDynamicWriteTester testOther.c)
add_executable(MemoryManageOtherDynamicWriteTested testOtherTarget.c)

target_link_libraries(MemoryManageOtherStaticWriteTester MemoryManageStatic)
target_link_libraries(MemoryManageOtherDynamicWriteTester MemoryManageShared)

add_test(NAME TestSelfStaticWrite COMMAND $<TARGET_FILE:MemoryManageStaticWriteTester>)
add_test(NAME TestSelfDynamicWrite COMMAND $<TARGET_FILE:MemoryManageDynamicWriteTester>)


add_test(
        NAME TestOtherStaticWrite COMMAND $<TARGET_FILE:MemoryManageOtherStaticWriteTester>
        $<TARGET_FILE:MemoryManageOtherStaticWriteTested>
)

add_test(
        NAME TestOtherDynamicWrite COMMAND $<TARGET_FILE_NAME:MemoryManageOtherDynamicWriteTester>
        $<TARGET_FILE:MemoryManageOtherDynamicWriteTested>
)