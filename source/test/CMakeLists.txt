add_executable(test_lib test.c)
set_target_properties (test_lib PROPERTIES LINK_FLAGS -Wl,-lcunit)
add_test (test_lib ${EXECUTABLE_OUTPUT_PATH}/test_lib)
