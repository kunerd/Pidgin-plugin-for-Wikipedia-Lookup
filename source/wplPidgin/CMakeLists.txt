project(wplPidgin C)
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_BINARY_DIR})

set (wplookup_VERSION_MAJOR 0)
set (wplookup_VERSION_MINOR 3)
set (wplookup_VERSION_PATCH 0)

set (SOURCE_FILES
    wplPreview.c
    wplSettings.c
)

set (WPLOOKUP_CONTACT "Hendrik Kunert <kunerd@users.sourceforge.net>")
set (WPLOOKUP_HOMEPAGE "http:\\\\\\\\sourceforge.net/projects/pidginpluginfor")

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

################ WebkitGtk install Check ####################
find_package(WebkitGtk REQUIRED)
if (WEBKITGTK_FOUND)
        add_definitions(${WEBKITGTK_DEFINITIONS})
        include_directories(${WEBKITGTK_INCLUDE_DIRS})
endif(WEBKITGTK_FOUND)

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
        ${WEBKITGTK_LIBRARIES}
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
        ${WEBKITGTK_LIBRARIES}
        ${PIDGIN_LIBRARIES}
        ${PURPLE_LIBRARIES}
        ${GIO2_LIBRARIES}
)

enable_testing()
add_subdirectory(tests)

if(UNIX)
        message("Installer will be build for Linux only")
        #if(NOT EXISTS CMAKE_INSTALL_PREFIX)
        #	message("Install prefix is not given, set to default!")
        #	set(CMAKE_INSTALL_PREFIX "value")
        #endif(NOT EXISTS CMAKE_INSTALL_PREFIX)
        install (TARGETS wplPidgin LIBRARY DESTINATION .purple/plugins)
        install (DIRECTORY ../resources DESTINATION .purple/wplookup)

        SET(CPACK_GENERATOR RPM TGZ)
        SET(CPACK_INSTALL_PREFIX "/lib64/pidgin")
        ##SET(CPACK_INSTALL_CMAKE_PROJECTS "$ENV{HOME}/.purple/plugins;wplookup;ALL;/")
        SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "${WPLOOKUP_CONTACT}")
        SET(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${CMake_VERSION_MAJOR}.${CMake_VERSION_MINOR}")
        set(CPACK_SOURCE_IGNORE_FILES ${CPACK_SOURCE_IGNORE_FILES}
                                        "\\\\.*~"
                                        "\\\\.git*"
                                        "\\\\.anjuta*"
                                        "\\\\.task"
                                        "\\\\build/*")
else(UNIX)
        if(WIN32)
                message("Installer will be build for Win32")

                set(CPACK_PACKAGE_INSTALL_DIRECTORY "Pidgin")

                #install (TARGETS wplookup
                #	 DESTINATION plugins)

                file(GLOB windows_dlls "${CMAKE_CURRENT_BINARY_DIR}/bin/*.dll")
                install(FILES ${windows_dlls}
                        DESTINATION ./)

                install (DIRECTORY ../resources
                         DESTINATION wplookup)

                set(CPACK_GENERATOR NSIS)
                #set(CPACK_NSIS_CREATE_ICONS "")
                set(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY} Wikipedia Lookup")
                set(CPACK_NSIS_HELP_LINK "${WPLOOKUP_HOMEPAGE}")
                set(CPACK_NSIS_URL_INFO_ABOUT "${WPLOOKUP_HOMEPAGE}")
                set(CPACK_NSIS_MODIFY_PATH OFF)
                set(CPACK_NSIS_CONTACT "${WPLOOKUP_CONTACT}")
        endif(WIN32)
endif(UNIX)

include(CPack)

