project(wplookup C)
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_BINARY_DIR})

set (wplookup_VERSION_MAJOR 0)
set (wplookup_VERSION_MINOR 0)
set (wplookup_VERSION_PATCH 1)

set (SOURCE_FILES
    wparticle.c
    wpopensearch.c
    wpxml.c
    wplinkedlist.c
)

set (WPLOOKUP_CONTACT "Hendrik Kunert <kunerd@users.sourceforge.net>")
set (WPLOOKUP_HOMEPAGE "http:\\\\\\\\sourceforge.net/projects/pidginpluginfor")

# configure a header file to pass some of the CMake settings
# to the source code
#configure_file (
#  "${PROJECT_SOURCE_DIR}/wpconf.h.in"
#  "${PROJECT_BINARY_DIR}/wpconf.h"
#  )

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

#add_subdirectory(wplPidgin)
#add_subdirectory(wpLookup)

################ Gtk2 install Check ####################
find_package(GTK2 REQUIRED)
if (GTK2_FOUND)
        add_definitions(${GTK2_DEFINITIONS})
        include_directories(${GTK2_INCLUDE_DIRS})
endif (GTK2_FOUND)

################ LIBXML2 install Check ####################
find_package(LibXml2 REQUIRED)
if (LIBXML2_FOUND)
        add_definitions(${LIBXML2_DEFINITIONS})
        include_directories(${LIBXML2_INCLUDE_DIRS})
endif (LIBXML2_FOUND)

################ Curl install Check ####################
find_package(CURL REQUIRED)
if (CURL_FOUND)
        add_definitions(${CURL_DEFINITIONS})
        include_directories(${CURL_INCLUDE_DIRS})
endif (CURL_FOUND)

################ Doxygen ###############################
find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(wpldoc ALL
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)

# used for linking into a shared library
add_definitions(-fPIC)

add_library(wplookup STATIC wplookup.c ${SOURCE_FILES})

target_link_libraries(
        wplookup
        ${GTK2_LIBRARIES}
        ${CURL_LIBRARIES}
        ${LIBXML2_LIBRARIES}
)

enable_testing()
add_subdirectory(tests)
