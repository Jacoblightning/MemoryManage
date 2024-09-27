add_executable(MemoryManageSelfDynamicWriteByteFill testSame.c)
add_executable(MemoryManageSelfStaticWriteByteFill testSame.c)

target_link_libraries(MemoryManageSelfStaticWriteByteFill MemoryManageStatic)
target_link_libraries(MemoryManageSelfDynamicWriteByteFill MemoryManageShared)


add_executable(MemoryManageOtherStaticWriteByteFillTester testOther.c)
add_executable(MemoryManageOtherStaticWriteByteFillTested testOtherTarget.c)
add_executable(MemoryManageOtherDynamicWriteByteFillTester testOther.c)
add_executable(MemoryManageOtherDynamicWriteByteFillTested testOtherTarget.c)

target_link_libraries(MemoryManageOtherStaticWriteByteFillTester MemoryManageStatic)
target_link_libraries(MemoryManageOtherDynamicWriteByteFillTester MemoryManageShared)

add_test(NAME TestSelfStaticByteFill COMMAND $<TARGET_FILE:MemoryManageSelfStaticWriteByteFill>)
add_test(NAME TestSelfDynamicByteFill COMMAND $<TARGET_FILE:MemoryManageSelfDynamicWriteByteFill>)

add_test(
        NAME TestOtherStaticByteFill COMMAND $<TARGET_FILE:MemoryManageOtherStaticWriteByteFillTester>
        $<TARGET_FILE:MemoryManageOtherStaticWriteByteFillTested>
)

add_test(
        NAME TestOtherDynamicByteFill COMMAND $<TARGET_FILE_NAME:MemoryManageOtherDynamicWriteByteFillTester>
        $<TARGET_FILE:MemoryManageOtherDynamicWriteByteFillTested>
)