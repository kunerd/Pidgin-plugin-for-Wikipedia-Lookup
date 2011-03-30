project(wplookup C)
cmake_minimum_required(VERSION 2.6)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_BINARY_DIR})

set (wplookup_VERSION_MAJOR 0)
set (wplookup_VERSION_MINOR 1)
set (wplookup_VERSION_PATCH 1)

set (SOURCE_FILES wplookup.c
					wikiinfo.c
					wpsettings.c
					wpview.c
					wputility.c)
 
# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/wpconf.h.in"
  "${PROJECT_BINARY_DIR}/wpconf.h"
  )


add_definitions(`pkg-config pidgin --cflags`) #...should be changed
#add_definitions(`pkg-config gtk+-2.0 --cflags`)
#add_definitions(`curl-config --cflags`)
#add_definitions(`pkg-config pidgin --libs`)
#add_definitions(`pkg-config gtk+-2.0 --libs`)
#add_definitions(`pkg-config --variable=libdir`)
#add_definitions(`curl-config --libs`)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${PROJECT_SOURCE_DIR}/findLibrary")

find_package(LIBXML2 REQUIRED)
include_directories(${LIBXML2_INCLUDE_DIRS})

find_package(PIDGIN REQUIRED)
include_directories(${PIDGIN_INCLUDE_DIRS})

find_package(GTK2 REQUIRED)
find_package(CURL REQUIRED)

add_library(wplookup SHARED ${SOURCE_FILES})

target_link_libraries(wplookup ${GTK2_LIBRARIES} ${CURL_LIBRARIES} ${LIBXML2_LIBRARIES})
#target_link_libraries(wplookup ${GTK2_LIBRARIES} ${CURL_LIBRARIES} xml2)

install (TARGETS wplookup LIBRARY DESTINATION ~/.purple/plugins)

add_custom_target(valgrind COMMAND valgrind --leak-check=summary --show-reachable=yes --tool=memcheck --leak-resolution=high --num-callers=20 --trace-children=no --child-silent-after-fork=yes --track-fds=yes pidgin -d >valgrind.log 2>&1)

INCLUDE(InstallRequiredSystemLibraries)

SET(CPACK_GENERATOR DEB TGZ)
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "wplookup")
SET(CPACK_INSTALL_PREFIX "/lib64/pidgin")
##SET(CPACK_INSTALL_CMAKE_PROJECTS "$ENV{HOME}/.purple/plugins;wplookup;ALL;/")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Hendrik Kunert <kunerd@users.sourceforge.net>")
SET(CPACK_PACKAGE_VENDOR "Hendrik Kunert <kunerd@users.sourceforge.net>")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/DESCRIPTION")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
SET(CPACK_PACKAGE_VERSION_MAJOR "${wplookup_VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${wplookup_VERSION_MINOR}")
SET(CPACK_PACKAGE_VERSION_PATCH "${wplookup_VERSION_PATCH}")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${CMake_VERSION_MAJOR}.${CMake_VERSION_MINOR}")
INCLUDE(CPack)
