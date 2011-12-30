project(wplookup C)
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_BINARY_DIR})

set (wplookup_VERSION_MAJOR 0)
set (wplookup_VERSION_MINOR 2)
set (wplookup_VERSION_PATCH 0)

set (SOURCE_FILES 
					wplanguage.c
					wpsettings.c
					wpview.c
					wputility.c
					wpweb.c)

set (WPLOOKUP_CONTACT "Hendrik Kunert <kunerd@users.sourceforge.net>")
set (WPLOOKUP_HOMEPAGE "http:\\\\\\\\sourceforge.net/projects/pidginpluginfor")
 
# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/wpconf.h.in"
  "${PROJECT_BINARY_DIR}/wpconf.h"
  )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/findLibrary")

find_package(LIBXML2 REQUIRED)
include_directories(${LIBXML2_INCLUDE_DIRS})

find_package(PIDGIN REQUIRED)
include_directories(${PIDGIN_INCLUDE_DIRS})

find_package(PURPLE REQUIRED)
include_directories(${PURPLE_INCLUDE_DIRS})

find_package(WEBKIT REQUIRED)
include_directories(${WEBKIT_INCLUDE_DIRS})

find_package(LibSoup2 REQUIRED)
include_directories(${LIBSOUP_INCLUDE_DIRS})

find_package(GTK2 REQUIRED)
include_directories(${GTK2_INCLUDE_DIRS})

find_package(GIO2 REQUIRED)
include_directories(${GIO2_INCLUDE_DIRS})

find_package(GTK2 REQUIRED)
include_directories(${GTK2_INCLUDE_DIRS})

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})

add_executable(standalone main-window.c ${SOURCE_FILES})

target_link_libraries(
	standalone
	${GTK2_LIBRARIES}
	${CURL_LIBRARIES}
	${LIBXML2_LIBRARIES}
	${LIBSOUP_LIBRARIES}
	${WEBKIT_LIBRARIES}
	${PIDGIN_LIBRARIES}
	${PURPLE_LIBRARIES}
	${GIO2_LIBRARIES}
)

add_library(wplookup SHARED wplookup.c ${SOURCE_FILES})

target_link_libraries(
	wplookup 
	${GTK2_LIBRARIES}
	${CURL_LIBRARIES}
	${LIBXML2_LIBRARIES}
	${LIBSOUP_LIBRARIES}
	${WEBKIT_LIBRARIES}
	${PIDGIN_LIBRARIES}
	${PURPLE_LIBRARIES}
	${GIO2_LIBRARIES}
)

add_custom_target(vg-standalone COMMAND valgrind --leak-check=summary --show-reachable=yes --tool=memcheck --leak-resolution=high --num-callers=20 --trace-children=no --child-silent-after-fork=yes --track-fds=yes standalone -d >valgrind.log 2>&1)

add_custom_target(valgrind COMMAND valgrind --leak-check=summary --show-reachable=yes --tool=memcheck --leak-resolution=high --num-callers=20 --trace-children=no --child-silent-after-fork=yes --track-fds=yes pidgin -d >valgrind.log 2>&1)

INCLUDE(InstallRequiredSystemLibraries)

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A third-party Pidgin plug-in which offers you the possibility to look up received and typed words from Wikipedia.")
set(CPACK_PACKAGE_VERSION_MAJOR "${wplookup_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${wplookup_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${wplookup_VERSION_PATCH}")
set(CPACK_PACKAGE_VENDOR "${WPLOOKUP_CONTACT}")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/DESCRIPTION")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
#set(CPACK_PACKAGE_EXECUTABLES "")

if(UNIX)
	message("Installer will be build for Linux")
	if(NOT EXISTS CMAKE_INSTALL_PREFIX)
		message("Install prefix is not given, set to default!")
		set(CMAKE_INSTALL_PREFIX "value")
	endif(NOT EXISTS CMAKE_INSTALL_PREFIX)
	install (TARGETS wplookup LIBRARY DESTINATION .purple/plugins)
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

		install (TARGETS wplookup
			 DESTINATION plugins)

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

		#set(CPACK_PACKAGE_NAME "WplookupInstaller")
		#set(CPACK_NSIS_PACKAGE_NAME "wplookupInstaller")
		set(CPACK_NSIS_CONTACT "${WPLOOKUP_CONTACT}")
	endif(WIN32)
endif(UNIX)

include(CPack)

