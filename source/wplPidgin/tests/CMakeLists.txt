add_executable(test_settings test_settings.c ../wplSettings.c)
set_target_properties(test_settings PROPERTIES LINK_FLAGS -Wl,-lcunit)

target_link_libraries(
    test_settings
    wplookup
        ${GTK2_LIBRARIES}
        ${CURL_LIBRARIES}
        ${LIBXML2_LIBRARIES}
        ${LIBSOUP_LIBRARIES}
        ${WEBKITGTK_LIBRARIES}
        ${PIDGIN_LIBRARIES}
        ${PURPLE_LIBRARIES}
        ${GIO2_LIBRARIES}
)
add_test(linkedlist_tests ${EXECUTABLE_OUTPUT_PATH}/test_settings)

