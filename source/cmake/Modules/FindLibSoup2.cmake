# - Try to find LibSoup2
# Once done this will define
#  LIBSOUP2_FOUND - System has LibSoup2
#  LIBSOUP2_INCLUDE_DIRS - The LibSoup2 include directories
#  LIBSOUP2_LIBRARIES - The libraries needed to use LibSoup2
#  LIBSOUP2_DEFINITIONS - Compiler switches required for using LibSoup2

find_package(PkgConfig)
pkg_check_modules(PC_LIBSOUP2 libsoup-2.4 QUIET)
set(PC_LIBSOUP2_DEFINITIONS ${PC_LIBSOUP2_CFLAGS_OTHER})

find_path(
	LIBSOUP2_INCLUDE_DIR libsoup/soup.h
	HINTS
		${CMAKE_FIND_ROOT_PATH}
		${PC_LIBSOUP2_INCLUDEDIR}
		${PC_LIBSOUP2_INCLUDE_DIRS}
	PATH_SUFFIXES
		libsoup-2.4
)

find_library(
	LIBSOUP2_LIBRARY NAMES soup-2.4 libsoup-2.4
	HINTS
		${CMAKE_FIND_ROOT_PATH}
		${PC_LIBSOUP2_LIBDIR}
		${PC_LIBSOUP2_LIBRARY_DIRS}
)

set(LIBSOUP2_LIBRARIES ${LIBSOUP2_LIBRARY})
set(LIBSOUP2_INCLUDE_DIRS ${LIBSOUP2_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBSOUP2_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(LibSoup2 DEFAULT_MSG
                                   LIBSOUP2_LIBRARY LIBSOUP2_INCLUDE_DIR)

mark_as_advanced(LIBSOUP2_INCLUDE_DIR LIBSOUP2_LIBRARY )
