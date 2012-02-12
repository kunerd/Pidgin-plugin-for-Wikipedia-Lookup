#
#  Wikipedia Lookup - A third-party Pidgin plug-in which offers
#  you the possibility to look up received and typed words on Wikipedia.
#
#  Copyright (C) 2011, 2012 Hendrik Kunert kunerd@users.sourceforge.net
#
#  This file is part of Wikipedia Lookup.
#
#  Wikipedia Lookup is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  Wikipedia Lookup is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with Wikipedia Lookup.  If not, see <http://www.gnu.org/licenses/>.
#

project(wplPidgin C)
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_BINARY_DIR})

set (wplPidgin_VERSION_MAJOR 0)
set (wplPidgin_VERSION_MINOR 3)
set (wplPidgin_VERSION_PATCH 0)

set (SOURCE_FILES
    wplSettings.c
)

set (WPLPIDGIN_CONTACT "Hendrik Kunert <kunerd@users.sourceforge.net>")
set (WPLPIDGIN_HOMEPAGE "http:\\\\\\\\sourceforge.net/projects/pidginpluginfor")

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/wpconf.h.in"
  "${PROJECT_BINARY_DIR}/wpconf.h"
  )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

################ LIBXML2 install Check ####################
find_package(LibXml2 REQUIRED)
if (LIBXML2_FOUND)
        add_definitions(${LIBXML2_DEFINITIONS})
        include_directories(${LIBXML2_INCLUDE_DIRS})
endif (LIBXML2_FOUND)

################ Pidgin install Check ####################
find_package(Pidgin REQUIRED)
if (PIDGIN_FOUND)
        add_definitions(${PIDGIN_DEFINITIONS})
        include_directories(${PIDGIN_INCLUDE_DIRS})
endif(PIDGIN_FOUND)

################ Purple install Check ####################
find_package(Purple REQUIRED)
if (PURPLE_FOUND)
        add_definitions(${PURPLE_DEFINITIONS})
        include_directories(${PURPLE_INCLUDE_DIRS})
endif(PURPLE_FOUND)

################ LibSoup2 install Check ####################
find_package(LibSoup2 REQUIRED)
if (LIBSOUP2_FOUND)
        add_definitions(${LIBSOUP2_DEFINITIONS})
        include_directories(${LIBSOUP2_INCLUDE_DIRS})
endif (LIBSOUP2_FOUND)

################ Gtk2 install Check ####################
find_package(GTK2 REQUIRED)
if (GTK2_FOUND)
        add_definitions(${GTK2_DEFINITIONS})
        include_directories(${GTK2_INCLUDE_DIRS})
endif (GTK2_FOUND)

################ Gio2 install Check ####################
# required for windows builds, not included in gtk2 find module
if (WIN32)
        find_package(GIO2 REQUIRED)
        include_directories(${GIO2_INCLUDE_DIRS})
endif (WIN32)

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
    add_custom_target(doc ALL
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)

add_library(wplPidgin SHARED wplPidgin.c ${SOURCE_FILES})
target_link_libraries(
        wplPidgin
        wplookup
        ${GTK2_LIBRARIES}
        ${CURL_LIBRARIES}
        ${LIBXML2_LIBRARIES}
        ${LIBSOUP_LIBRARIES}
        ${PIDGIN_LIBRARIES}
        ${PURPLE_LIBRARIES}
        ${GIO2_LIBRARIES}
)

add_executable(standalone standalone.c ${SOURCE_FILES})
target_link_libraries(
        standalone
        wplookup
        #wplPidgin
        ${GTK2_LIBRARIES}
        ${CURL_LIBRARIES}
        ${LIBXML2_LIBRARIES}
        ${LIBSOUP_LIBRARIES}
        ${PIDGIN_LIBRARIES}
        ${PURPLE_LIBRARIES}
        ${GIO2_LIBRARIES}
)

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Wikipedia Lookup Pidgin Plugin")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${PROJECT_SOURCE_DIR}/DESCRIPTION")
SET(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/COPYING")
SET(CPACK_PACKAGE_VERSION_MAJOR "${wplPidgin_VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${wplPidgin_VERSION_MINOR}")
SET(CPACK_PACKAGE_VERSION_PATCH "${wplPidgin_VERSION_PATCH}")

SET(CPACK_SOURCE_GENERATOR TGZ ZIP)
if(UNIX)
        message("Installer will be build for Linux only")
        install (TARGETS wplPidgin LIBRARY DESTINATION .purple/plugins)
        SET(CPACK_GENERATOR RPM TGZ)
        SET(CPACK_INSTALL_PREFIX "/lib64/pidgin")
        SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "${WPLPIDGIN_CONTACT}")
        SET(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${wplPidgin_VERSION_MAJOR}.${wplPidgin_VERSION_MINOR}")
        set(CPACK_SOURCE_IGNORE_FILES ${CPACK_SOURCE_IGNORE_FILES}
                                        "\\\\.*~"
                                        "\\\\.git*"
                                        "\\\\.anjuta*"
                                        "\\\\.task"
                                        "\\\\build/*"
                                        "\\\\CMakeLists.txt.user")
else(UNIX)
        if(WIN32)
                message("Installer will be build for Win32")

                set(CPACK_PACKAGE_INSTALL_DIRECTORY "Pidgin")

                install (TARGETS wplPidgin
                         DESTINATION plugins)

               file(GLOB windows_dlls "${CMAKE_BINARY_DIR}/../bin/*.dll")
               install(FILES ${windows_dlls}
                       DESTINATION ./)

                set(CPACK_GENERATOR NSIS)
                #set(CPACK_NSIS_CREATE_ICONS "")
                set(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY} Wikipedia Lookup")
                set(CPACK_NSIS_HELP_LINK "${WPLPIDGIN_HOMEPAGE}")
                set(CPACK_NSIS_URL_INFO_ABOUT "${WPLPIDGIN_HOMEPAGE}")
                set(CPACK_NSIS_MODIFY_PATH OFF)
                set(CPACK_NSIS_CONTACT "${WPLPIDGIN_CONTACT}")
        endif(WIN32)
endif(UNIX)

if(UNIX)
    enable_testing()
    add_subdirectory(tests)
endif(UNIX)

include(CPack)

