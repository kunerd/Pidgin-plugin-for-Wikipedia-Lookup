project(wplPidginAll C)
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/wpLookup)
include_directories(${PROJECT_BINARY_DIR})


#set (wplookup_VERSION_MAJOR 0)
#set (wplookup_VERSION_MINOR 2)
#set (wplookup_VERSION_PATCH 0)


#set (WPLOOKUP_CONTACT "Hendrik Kunert <kunerd@users.sourceforge.net>")
#set (WPLOOKUP_HOMEPAGE "http:\\\\\\\\sourceforge.net/projects/pidginpluginfor")
 
# configure a header file to pass some of the CMake settings
# to the source code
#configure_file (
#  "${PROJECT_SOURCE_DIR}/wpconf.h.in"
#  "${PROJECT_BINARY_DIR}/wpconf.h"
#  )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

add_subdirectory(wplPidgin)
add_subdirectory(wpLookup)

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

################ WpLookup install Check ####################
#find_package(WpLookup REQUIRED)
#if (WPLOOKUP_FOUND)
#        add_definitions(${WPLOOKUP_DEFINITIONS})
#       include_directories(${WPLOOKUP_INCLUDE_DIRS})
#endif (WPLOOKUP_FOUND)

#add_executable(standalone main-window.c ${SOURCE_FILES})

#target_link_libraries(
#	standalone
#	${GTK2_LIBRARIES}
#	${CURL_LIBRARIES}
#	${LIBXML2_LIBRARIES}
#	${LIBSOUP_LIBRARIES}
#	${WEBKITGTK_LIBRARIES}
#	${PIDGIN_LIBRARIES}
#	${PURPLE_LIBRARIES}
#	${GIO2_LIBRARIES}
#)

#add_library(wplookup SHARED wplookup.c ${SOURCE_FILES})

#target_link_libraries(
#	wplookup
#	${GTK2_LIBRARIES}
#	${CURL_LIBRARIES}
#	${LIBXML2_LIBRARIES}
#	${LIBSOUP_LIBRARIES}
#	${WEBKITGTK_LIBRARIES}
#	${PIDGIN_LIBRARIES}
#	${PURPLE_LIBRARIES}
#	${GIO2_LIBRARIES}
#)

#enable_testing()
#add_subdirectory(test)

#add_custom_target(vg-standalone COMMAND valgrind --leak-check=summary --show-reachable=yes --tool=memcheck --leak-resolution=high --num-callers=20 --trace-children=no --child-silent-after-fork=yes --track-fds=yes standalone -d >valgrind.log 2>&1)

#add_custom_target(valgrind COMMAND valgrind --leak-check=summary --show-reachable=yes --tool=memcheck --leak-resolution=high --num-callers=20 --trace-children=no --child-silent-after-fork=yes --track-fds=yes pidgin -d >valgrind.log 2>&1)
