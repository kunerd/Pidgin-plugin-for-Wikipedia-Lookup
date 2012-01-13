add_executable(wplookup_tests test.c)
set_target_properties(wplookup_tests PROPERTIES LINK_FLAGS -Wl,-lcunit)
target_link_libraries(
    wplookup_tests
    wplookup
)

add_test(wplookup_tests ${EXECUTABLE_OUTPUT_PATH}/wplookup_tests)

add_executable(linkedlist_tests testlinkedlist.c)
set_target_properties(linkedlist_tests PROPERTIES LINK_FLAGS -Wl,-lcunit)
target_link_libraries(
    linkedlist_tests
    wplookup
)
add_test(linkedlist_tests ${EXECUTABLE_OUTPUT_PATH}/linkedlist_tests)

set(MEMORYCHECK_COMMAND:FILEPATH=/bin/usr/valgrind)
