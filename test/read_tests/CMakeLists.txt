add_executable(MemoryManageStaticReadTester testSame.c)
add_executable(MemoryManageDynamicReadTester testSame.c)

target_link_libraries(MemoryManageStaticReadTester MemoryManageStatic)
target_link_libraries(MemoryManageDynamicReadTester MemoryManageShared)


add_executable(MemoryManageOtherStaticReadTester testOther.c)
add_executable(MemoryManageOtherStaticReadTested testOtherTarget.c)
add_executable(MemoryManageOtherDynamicReadTester testOther.c)
add_executable(MemoryManageOtherDynamicReadTested testOtherTarget.c)

target_link_libraries(MemoryManageOtherStaticReadTester MemoryManageStatic)
target_link_libraries(MemoryManageOtherDynamicReadTester MemoryManageShared)



add_test(NAME TestSelfStaticRead COMMAND $<TARGET_FILE:MemoryManageStaticReadTester>)
add_test(NAME TestSelfDynamicRead COMMAND $<TARGET_FILE:MemoryManageDynamicReadTester>)

add_test(
        NAME TestOtherStaticRead COMMAND $<TARGET_FILE:MemoryManageOtherStaticReadTester>
        $<TARGET_FILE:MemoryManageOtherStaticReadTested>
)

add_test(
        NAME TestOtherDynamicRead COMMAND $<TARGET_FILE_NAME:MemoryManageOtherDynamicReadTester>
        $<TARGET_FILE:MemoryManageOtherDynamicReadTested>
)