# - Try to find Pidgin Development Files
# Once done this will define
#  PIDGIN_FOUND - System has Pidgin Development Files
#  PIDGIN_INCLUDE_DIRS - The Pidgin Development Files include directories
#  PIDGIN_LIBRARIES - The libraries needed to use Pidgin Development Files
#  PIDGIN_DEFINITIONS - Compiler switches required for using Pidgin Development Files

find_package(PkgConfig)
pkg_check_modules(PC_PIDGIN pidgin QUIET)
set(PC_PIDGIN_DEFINITIONS ${PC_PIDGIN_CFLAGS_OTHER})

find_path(
	PIDGIN_INCLUDE_DIR pidgin.h
	HINTS
		${CMAKE_FIND_ROOT_PATH}
		${PC_PIDGIN_INCLUDEDIR}
		${PC_PIDGIN_INCLUDE_DIRS}
	PATH_SUFFIXES
		pidgin
)

if(WIN32)
	find_path(
		PIDGIN_WIN32_INCLUDE_DIR gtkwin32dep.h
		HINTS
			${CMAKE_FIND_ROOT_PATH}
			${PC_PIDGIN_INCLUDEDIR}
			${PC_PIDGIN_INCLUDE_DIRS}
		PATH_SUFFIXES
			pidgin/win32
	)

	find_library(
		PIDGIN_LIBRARY NAMES pidgin
		HINTS
			${CMAKE_FIND_ROOT_PATH}
			${PC_PIDGIN_LIBDIR}
			${PC_PIDGIN_LIBRARY_DIRS}
		PATH_SUFFIXES
			pidgin
	)

	set(PIDGIN_LIBRARIES ${PIDGIN_LIBRARY})
	set(PIDGIN_INCLUDE_DIRS ${PIDGIN_INCLUDE_DIR} ${PIDGIN_WIN32_INCLUDE_DIR})
else(WIN32)
	set(PIDGIN_INCLUDE_DIRS ${PIDGIN_INCLUDE_DIR})
endif(WIN32)

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set PIDGIN_FOUND to TRUE
# if all listed variables are TRUE
if(WIN32)
	find_package_handle_standard_args(Pidgin DEFAULT_MSG
                                   PIDGIN_LIBRARY PIDGIN_INCLUDE_DIR PIDGIN_WIN32_INCLUDE_DIR)
else(WIN32)
	find_package_handle_standard_args(Pidgin DEFAULT_MSG
                                   PIDGIN_INCLUDE_DIR)
endif(WIN32)

mark_as_advanced(PIDGIN_INCLUDE_DIR PIDGIN_WIN32_INCLUDE_DIR PIDGIN_LIBRARY)
