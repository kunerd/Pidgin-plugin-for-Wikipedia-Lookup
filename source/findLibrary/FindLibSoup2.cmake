# - Try to find Purple Devel
# Once done this will define
#  PURPLE_FOUND - System has LibXml2
#  PURPLE_INCLUDE_DIRS - The LibXml2 include directories
#  PURPLE_LIBRARIES - The libraries needed to use LibXml2
#  PURPLE_DEFINITIONS - Compiler switches required for using LibXml2

#find_package(PkgConfig)
#pkg_check_modules(PC_PURPLE QUIET purple)
#set(PC_PURPLE_DEFINITIONS ${PC_PURPLE_CFLAGS_OTHER})

find_path(LIBSOUP_INCLUDE_DIR libsoup/soup.h
          HINTS ${CMAKE_FIND_ROOT_PATH}
          PATH_SUFFIXES libsoup-2.4 )

find_library(LIBSOUP_LIBRARY NAMES libsoup-2.4
             HINTS ${CMAKE_FIND_ROOT_PATH})

set(LIBSOUP_LIBRARIES ${LIBSOUP_LIBRARY} )
set(LIBSOUP_INCLUDE_DIRS ${LIBSOUP_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set PURPLE_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(libsoup DEFAULT_MSG
                                   LIBSOUP_LIBRARIES LIBSOUP_INCLUDE_DIR)

mark_as_advanced(LIBSOUP_INCLUDE_DIR LIBSOUP_LIBRARY )
