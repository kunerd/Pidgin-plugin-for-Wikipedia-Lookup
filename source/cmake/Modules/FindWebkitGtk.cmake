# - Try to find Webkit
# Once done this will define
#  WEBKITGTK_FOUND - System has WebkitGtk
#  WEBKITGTK_INCLUDE_DIRS - The WebkitGtk include directories
#  WEBKITGTK_LIBRARIES - The libraries needed to use WebkitGtk
#  WEBKITGTK_DEFINITIONS - Compiler switches required for using WebkitGtk

find_package(PkgConfig)
pkg_check_modules(PC_PURPLE libwebkitgtk QUIET)
set(PC_WEBKITGTK_DEFINITIONS ${PC_WEBKITGTK_CFLAGS_OTHER})

find_path(
	WEBKITGTK_INCLUDE_DIR webkit/webkit.h
	HINTS
		${CMAKE_FIND_ROOT_PATH}
		${PC_WEBKITGTK_INCLUDEDIR}
		${PC_WEBKITGTK_INCLUDE_DIRS}
	PATH_SUFFIXES
		webkit-1.0
)

find_library(
	WEBKITGTK_LIBRARY NAMES webkitgtk-1.0
	HINTS
		${CMAKE_FIND_ROOT_PATH}
		${PC_WEBKITGTK_LIBDIR}
		${PC_WEBKITGTK_LIBRARY_DIRS}
)

set(WEBKITGTK_LIBRARIES ${WEBKITGTK_LIBRARY} )
set(WEBKITGTK_INCLUDE_DIRS ${WEBKITGTK_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set WEBKITGTK_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(WebkitGtk DEFAULT_MSG
                                  WEBKITGTK_LIBRARY WEBKITGTK_INCLUDE_DIR)

mark_as_advanced(WEBKITGTK_INCLUDE_DIR WEBKITGTK_LIBRARY)
