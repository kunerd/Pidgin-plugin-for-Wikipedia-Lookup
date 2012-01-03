add_executable(wplookup_tests test.c)
set_target_properties(wplookup_tests PROPERTIES LINK_FLAGS -Wl,-lcunit)
target_link_libraries(wplookup_tests wplookup)
add_test(wplookup_tests ${EXECUTABLE_OUTPUT_PATH}/wplookup_tests)
