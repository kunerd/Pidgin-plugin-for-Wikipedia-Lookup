# - Try to find Purple Devel
# Once done this will define
#  PURPLE_FOUND - System has LibXml2
#  PURPLE_INCLUDE_DIRS - The LibXml2 include directories
#  PURPLE_LIBRARIES - The libraries needed to use LibXml2
#  PURPLE_DEFINITIONS - Compiler switches required for using LibXml2

#find_package(PkgConfig)
#pkg_check_modules(PC_PURPLE QUIET purple)
#set(PC_PURPLE_DEFINITIONS ${PC_PURPLE_CFLAGS_OTHER})


find_path(PURPLE_INCLUDE_DIR1 purple.h
          HINTS ${CMAKE_FIND_ROOT_PATH}
	   PATH_SUFFIXES libpurple
)

find_path(PURPLE_INCLUDE_DIR2 libpurple/purple.h
          HINTS ${CMAKE_FIND_ROOT_PATH}
	   #PATH_SUFFIXES libpurple
)
set(PURPLE_INCLUDE_DIRS ${PURPLE_INCLUDE_DIR1} ${PURPLE_INCLUDE_DIR2})


find_library(PURPLE_LIBRARY NAMES purple
             HINTS ${CMAKE_FIND_ROOT_PATH} 
		PATH_SUFFIXES libpurple)

set(PURPLE_LIBRARIES ${PURPLE_LIBRARY} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set PURPLE_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(purple DEFAULT_MSG
                                    PURPLE_LIBRARY PURPLE_INCLUDE_DIR1 PURPLE_INCLUDE_DIR2)

#mark_as_advanced(PURPLE_INCLUDE_DIR PURPLE_LIBRARY )
