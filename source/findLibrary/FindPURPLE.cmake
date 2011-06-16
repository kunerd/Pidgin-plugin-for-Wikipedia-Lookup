# - Try to find Purple Devel
# Once done this will define
#  PURPLE_FOUND - System has LibXml2
#  PURPLE_INCLUDE_DIRS - The LibXml2 include directories
#  PURPLE_LIBRARIES - The libraries needed to use LibXml2
#  PURPLE_DEFINITIONS - Compiler switches required for using LibXml2

find_package(PkgConfig)
pkg_check_modules(PC_PURPLE QUIET purple)
set(PC_PURPLE_DEFINITIONS ${PC_PURPLE_CFLAGS_OTHER})

find_path(PURPLE_INCLUDE_DIR purple.h
          HINTS ${PC_PIDGIN_INCLUDEDIR} ${PC_PURPLE_INCLUDE_DIRS}
          PATH_SUFFIXES libpurple )

find_library(PURPLE_LIBRARY NAMES purple
             HINTS ${PC_PURPLE_LIBDIR} ${PC_PURPLE_LIBRARY_DIRS} )

set(PURPLE_LIBRARIES ${PURPLE_LIBRARY} )
set(PURPLE_INCLUDE_DIRS ${PURPLE_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set PURPLE_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(pruple DEFAULT_MSG
                                   PURPLE_INCLUDE_DIR PURPLE_LIBRARIES)

mark_as_advanced(PURPLE_INCLUDE_DIR PURPLE_LIBRARY )
