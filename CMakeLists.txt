project(wplookup C)
cmake_minimum_required(VERSION 2.6)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_BINARY_DIR})

set (wplookup_VERSION_MAJOR 0)
set (wplookup_VERSION_MINOR 1)
set (wplookup_VERSION_PATCH 1)
 
# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/wpconf.h.in"
  "${PROJECT_BINARY_DIR}/wpconf.h"
  )


add_definitions(`pkg-config pidgin --cflags`)
add_definitions(`pkg-config gtk+-2.0 --cflags`)
add_definitions(`curl-config --cflags`)
add_definitions(`pkg-config pidgin --libs`)
add_definitions(`pkg-config gtk+-2.0 --libs`)
add_definitions(`pkg-config --variable=libdir`)
add_definitions(`curl-config --libs`)

find_package(GTK2)

add_library(wplookup SHARED wplookup.c wikiinfo.c)

target_link_libraries(wplookup ${GTK2_LIBRARIES} curl xml2)

add_custom_target(valgrind COMMAND valgrind --leak-check=summary --show-reachable=yes --tool=memcheck --leak-resolution=high --num-callers=20 --trace-children=no --child-silent-after-fork=yes --track-fds=yes pidgin -d >valgrind.log 2>&1)

install (TARGETS wplookup DESTINATION ~/.purple/plugins)


set(CPACK_PACKAGE_NAME "wplookup")
set(CPACK_PACKAGE_VENDOR "CMake.org")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "MyLib - CPack Component Installation Example")
set(CPACK_COMPONENTS_ALL wplookup)

include(CPack)


