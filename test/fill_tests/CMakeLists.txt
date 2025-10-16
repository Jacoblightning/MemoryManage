add_executable(MemoryManageSelfDynamicWriteByteFill testSame.c)
add_executable(MemoryManageSelfStaticWriteByteFill testSame.c)

target_link_libraries(MemoryManageSelfStaticWriteByteFill MemoryManageStatic)
target_link_libraries(MemoryManageSelfDynamicWriteByteFill MemoryManageDynamic)


add_executable(MemoryManageOtherStaticWriteByteFillTester testOther.c)
add_executable(MemoryManageOtherStaticWriteByteFillTested testOtherTarget.c)
add_executable(MemoryManageOtherDynamicWriteByteFillTester testOther.c)
add_executable(MemoryManageOtherDynamicWriteByteFillTested testOtherTarget.c)

# IKD what but gcc does something to this file.
set_source_files_properties(testOtherTarget.c PROPERTIES COMPILE_FLAGS "-O0")

target_link_libraries(MemoryManageOtherStaticWriteByteFillTester MemoryManageStatic)
target_link_libraries(MemoryManageOtherDynamicWriteByteFillTester MemoryManageDynamic)

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
