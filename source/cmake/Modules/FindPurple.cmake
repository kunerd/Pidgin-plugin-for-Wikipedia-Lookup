# - Try to find Purple Devel
# Once done this will define
#  PURPLE_FOUND - System has LibPurple
#  PURPLE_INCLUDE_DIRS - The LibPurple include directories
#  PURPLE_LIBRARIES - The libraries needed to use LibPurple
#  PURPLE_DEFINITIONS - Compiler switches required for using LibPurple

find_package(PkgConfig)
pkg_check_modules(PC_PURPLE libpurple QUIET)
set(PC_PURPLE_DEFINITIONS ${PC_PURPLE_CFLAGS_OTHER})


find_path(
	PURPLE_INCLUDE_DIR1 purple.h
	HINTS
		${CMAKE_FIND_ROOT_PATH}
		${PC_PURPLE_INCLUDEDIR}
		${PC_PURPLE_INCLUDE_DIRS}
	PATH_SUFFIXES
		libpurple
)

find_path(
	PURPLE_INCLUDE_DIR2 libpurple/purple.h
	HINTS
		${CMAKE_FIND_ROOT_PATH}
		${PC_PURPLE_INCLUDEDIR}
		${PC_PURPLE_INCLUDE_DIRS}
)

find_library(PURPLE_LIBRARY NAMES purple
             HINTS
		${CMAKE_FIND_ROOT_PATH} 
		${PC_PURPLE_INCLUDEDIR}
		${PC_PURPLE_INCLUDE_DIRS}
	PATH_SUFFIXES
		libpurple)

set(PURPLE_LIBRARIES ${PURPLE_LIBRARY})
set(PURPLE_INCLUDE_DIRS ${PURPLE_INCLUDE_DIR1} ${PURPLE_INCLUDE_DIR2})

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set PURPLE_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(Purple DEFAULT_MSG
                                    PURPLE_LIBRARY PURPLE_INCLUDE_DIR1 PURPLE_INCLUDE_DIR2)

mark_as_advanced(PURPLE_LIBRARY PURPLE_INCLUDE_DIR1 PURPLE_INCLUDE_DIR2)
