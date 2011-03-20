
project(wplookup C)
cmake_minimum_required(VERSION 2.6)

include_directories(${PROJECT_SRC_DIR})
include_directories(${PROJECT_BUILD_DIR})

add_definitions(`pkg-config pidgin --cflags`)
add_definitions(`pkg-config gtk+-2.0 --cflags`)
add_definitions(`curl-config --cflags`)
add_definitions(`pkg-config pidgin --libs`)
add_definitions(`pkg-config gtk+-2.0 --libs`)
add_definitions(`pkg-config --variable=libdir`)
add_definitions(`curl-config --libs`)

find_package(GTK2)

add_library(wplookup SHARED wplookup.c wikiinfo.c)

target_link_libraries(wplookup ${GTK2_LIBRARIES} ${PROJECT_SRC_DIR} ${PROJECT_BUILD_DIR} curl xml2)

add_custom_target(valgrind COMMAND valgrind --leak-check=full --show-reachable=yes --tool=memcheck --leak-resolution=high --num-callers=20 --trace-children=no --child-silent-after-fork=yes --track-fds=yes pidgin -d >valgrind.log 2>&1)

